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
	DisplayThread::DisplayThread(Mutex& mutex_r, NaviData* naviData_p) : BaseThread(mutex_r, naviData_p)
	{
		printf("Constructing DisplayThread ...\n");
	}

	//-----------------------------------------------------------------------------------------
	// Destructor
	//-----------------------------------------------------------------------------------------
	DisplayThread::~DisplayThread()
	{
		printf("Destroying DisplayThread ...\n");
	}

	//-----------------------------------------------------------------------------------------
	// Overrides BaseThread's run() method
	//-----------------------------------------------------------------------------------------
	void* DisplayThread::run()
	{
		// dummy buffer
		string buffer[8];

		mutex.lock();

		int n = 10;
		while(n != 0)
		{
			printf("In the display while loop ...\n");
			int receivedPulse = MsgReceivePulse(getChannelId(), &buffer, sizeof(buffer), NULL);
			if (receivedPulse != 0)
				printf("Error receiving display pulse\n");
			else
			{
				printf("Display pulse %d received\n",  n);
				n--;
			}
		}

		printf("DisplayThread done %lu\n", (long unsigned int)getThreadId());
		mutex.unlock();
		return NULL;
	}
