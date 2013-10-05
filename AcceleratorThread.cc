#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <unistd.h>
#include <pthread.h>

#include "AcceleratorThread.h"

//---------------------------------------------------------------------------------------------
// AcceleratorThread subclass implementation.
//---------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	AcceleratorThread::AcceleratorThread(Mutex& mutexRef) : mutex(mutexRef)
	{
		cout << "Constructing AcceleratorThread ..." << endl;
	}

	//-----------------------------------------------------------------------------------------
	// Destructor
	//-----------------------------------------------------------------------------------------
	AcceleratorThread::~AcceleratorThread()
	{
		cout << "Destroying AcceleratorThread ..." << endl;
	}

	//-----------------------------------------------------------------------------------------
	// Overrides BaseThread's run() method
	//-----------------------------------------------------------------------------------------
	void* AcceleratorThread::run()
	{
		mutex.lock();
		for (int i = 0; i < 10; i++)
		{
			printf("AcceleratorThread %lu running - %d\n",  (long unsigned int)getThreadId(), i+1);
			sleep(1);
		}

		printf("AcceleratorThread done %lu\n", (long unsigned int)getThreadId());
		mutex.unlock();
		return NULL;
	}
