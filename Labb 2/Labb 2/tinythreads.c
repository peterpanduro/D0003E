#include <setjmp.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "tinythreads.h"

#define NULL            0
#define DISABLE()       cli()
#define ENABLE()        sei()
#define STACKSIZE       80
#define NTHREADS        4
#define SETSTACK(buf,a) *((unsigned int *)(buf)+8) = (unsigned int)(a) + STACKSIZE - 4; \
                        *((unsigned int *)(buf)+9) = (unsigned int)(a) + STACKSIZE - 4

struct thread_block {
    void (*function)(int);   // code to run
    int arg;                 // argument to the above
    thread next;             // for use in linked lists
    jmp_buf context;         // machine state
    char stack[STACKSIZE];   // execution stack space
};

struct thread_block threads[NTHREADS];
struct thread_block initp;

thread freeQ   = threads;
thread readyQ  = NULL;
thread current = &initp;

int initialized = 0;

static void initialize(void) {
    int i;
    for (i=0; i<NTHREADS-1; i++)
        threads[i].next = &threads[i+1];
    threads[NTHREADS-1].next = NULL;

	// Enable logical interrupt for joystick down. Source PCINT15 (7th bit on PORTB)
	PORTB = 0x80 | PORTB;
	PCMSK1 = 0x80 | PCMSK1;
	EIMSK |= (1<<PCIE1);
	
	// Enable timer interrupt at 50 ms interval
	TCCR1A |= (1<<COM1A0); // OC1A Compare Match
	TCCR1B |= (1<<WGM12); // CTC
	TCCR1B |= (1<<CS12) | (1<<CS10); // 1024 prescaling
	// OCRnA = (fclk_io / 2*N*fOCnA) - 1 = 8*10^6/(2*1024*200) = 194,3125 ~ 0xc2
	// OCR1AH = 0x00; //OCR1A[15:8]
	OCR1AL = 0xc2; //OCR1A[7:0]
	//OCR1A=0x07a0;
	TIMSK1 |= (1<<OCIE1A); //Output Compare A Match Interrupt Enable
	//Reset CLK
	CLKPR = 0x80;
	CLKPR = 0x00;

    initialized = 1;
}

static void enqueue(thread p, thread *queue) {
    p->next = NULL;
    if (*queue == NULL) {
        *queue = p;
    } else {
        thread q = *queue;
        while (q->next)
            q = q->next;
        q->next = p;
    }
}

static thread dequeue(thread *queue) {
    thread p = *queue;
    if (*queue) {
        *queue = (*queue)->next;
    } else {
        // Empty queue, kernel panic!!!
        while (1) ;  // not much else to do...
    }
    return p;
}

static void dispatch(thread next) {
    if (setjmp(current->context) == 0) {
        current = next;
        longjmp(next->context,1);
    }
}

void spawn(void (* function)(int), int arg) {
    thread newp;

    DISABLE();
    if (!initialized) initialize();

    newp = dequeue(&freeQ);
    newp->function = function;
    newp->arg = arg;
    newp->next = NULL;
    if (setjmp(newp->context) == 1) {
        ENABLE();
        current->function(current->arg);
        DISABLE();
        enqueue(current, &freeQ);
        dispatch(dequeue(&readyQ));
    }
    SETSTACK(&newp->context, &newp->stack);

    enqueue(newp, &readyQ);
    ENABLE();
}

void yield(void) {
	DISABLE();
	enqueue(current, &readyQ);
	dispatch(dequeue(&readyQ));
	ENABLE();
}

void lock(mutex *m) {
	DISABLE();
	if (m->locked) {	
		enqueue(current, &m->waitQ);
		dispatch(dequeue(&readyQ));	
	} else {
		m->locked=1;
	}
	ENABLE();
}

void unlock(mutex *m) {
	DISABLE();
	if (m->waitQ) {	
		enqueue(current, &readyQ);
		dispatch(dequeue(&m->waitQ));	
	} else {
		m->locked = 0;
	}
	ENABLE();
}

ISR(PCINT1_vect) {
	if (!((PINB >> 7) & 1U)) {
		yield();
	}
}

ISR(TIMER1_COMPA_vect) {
	yield();
}