#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <pthread.h>
#include <unistd.h>

//---------------------------------------------------------------------------------------------
// DisplayThread subclass implementation.
//---------------------------------------------------------------------------------------------

	#include "DisplayThread.h"

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	DisplayThread::DisplayThread()
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
		for (int i = 0; i < 5; i++)
		{
			printf("DisplayThread %lu running - %d\n",  (long unsigned int)getThreadId(), i+1);
			sleep(2);
		}

		printf("DisplayThread done %lu\n", (long unsigned int)getThreadId());
		return NULL;
	}
