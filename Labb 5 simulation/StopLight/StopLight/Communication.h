#pragma once

#include <pthread.h>

class Communication {
	private:
		int serial_port;
		
	public:
		Communication();
		pthread_mutex_t transmiterMutex = PTHREAD_MUTEX_INITIALIZER;
		void transmit(int);
		pthread_mutex_t reciverMutex = PTHREAD_MUTEX_INITIALIZER;
		int recieve();
		
};