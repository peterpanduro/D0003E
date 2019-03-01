/*
 *
 * tinythreads.h
 *
 */

#ifndef _TINYTHREADS_H
#define _TINYTHREADS_H
#define DISABLE()       cli()
#define ENABLE()        sei()

struct thread_block;
typedef struct thread_block *thread;
void spawn(void (*code)(int), int arg);
void yield(void);

#endif

