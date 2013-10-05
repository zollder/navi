#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <unistd.h>
#include <pthread.h>

#include "DisplayThread.h"

//---------------------------------------------------------------------------------------------
// DisplayThread subclass implementation.
//---------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	DisplayThread::DisplayThread(Mutex& mutexRef) : mutex(mutexRef)
	{
		cout << "Constructing DisplayThread ..." << endl;
	}

	//-----------------------------------------------------------------------------------------
	// Destructor
	//-----------------------------------------------------------------------------------------
	DisplayThread::~DisplayThread()
	{
		cout << "Destroying DisplayThread ..." << endl;
	}

	//-----------------------------------------------------------------------------------------
	// Overrides BaseThread's run() method
	//-----------------------------------------------------------------------------------------
	void* DisplayThread::run()
	{
		mutex.lock();
		for (int i = 0; i < 10; i++)
		{
			printf("DisplayThread %lu running - %d\n",  (long unsigned int)getThreadId(), i+1);
			sleep(1);
		}

		printf("DisplayThread done %lu\n", (long unsigned int)getThreadId());
		mutex.unlock();
		return NULL;
	}
