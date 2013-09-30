#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <pthread.h>
#include <unistd.h>

//---------------------------------------------------------------------------------------------
// AcceleratorThread subclass implementation.
//---------------------------------------------------------------------------------------------

	#include "AcceleratorThread.h"

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	AcceleratorThread::AcceleratorThread()
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
		for (int i = 0; i < 5; i++)
		{
			printf("AcceleratorThread %lu running - %d\n",  (long unsigned int)getThreadId(), i+1);
			sleep(2);
		}

		printf("AcceleratorThread done %lu\n", (long unsigned int)getThreadId());
		return NULL;
	}
