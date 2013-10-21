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
	AcceleratorThread::AcceleratorThread(Mutex& mutex_r, NaviData* naviData_p) : BaseThread(mutex_r, naviData_p)
	{
		printf("Constructing AcceleratorThread ...\n");
	}

	//-----------------------------------------------------------------------------------------
	// Destructor
	//-----------------------------------------------------------------------------------------
	AcceleratorThread::~AcceleratorThread()
	{
		printf("Destroying AcceleratorThread ...\n");
	}

	//-----------------------------------------------------------------------------------------
	// Overrides BaseThread's run() method
	//-----------------------------------------------------------------------------------------
	void* AcceleratorThread::run()
	{
		// dummy buffer
		string buffer[8];

		mutex.lock();

		int n = 10;
		while(n != 0)
		{
			printf("In the accelerator while loop ...\n");
			int receivedPulse = MsgReceivePulse(getChannelId(), &buffer, sizeof(buffer), NULL);
			if (receivedPulse != 0)
				printf("Error receiving accelerator pulse\n");
			else
			{
				printf("Accelerator pulse %d received\n",  n);
				n--;
			}
		}

		printf("AcceleratorThread done %lu\n", (long unsigned int)getThreadId());
		mutex.unlock();
		return NULL;
	}
