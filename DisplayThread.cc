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

		int counter = 0;
		while( ++counter <= duration)
		{
			int receivedPulse = MsgReceivePulse(getChannelId(), &buffer, sizeof(buffer), NULL);
			if (receivedPulse != 0)
			{
				printf("Error receiving display pulse\n");
			}
			else
			{
				printf("Display pulse %d received\n",  counter);

				mutex.lock();
				printf("Distance: x: %f, y: %f, z: %f \n",
						naviData->getDistanceData()->x,
						naviData->getDistanceData()->y,
						naviData->getDistanceData()->z);
				printf("Velocity: Vx: %f, Vy: %f, Vz: %f \n\n",
						naviData->getVelocityData()->Vx,
						naviData->getVelocityData()->Vy,
						naviData->getVelocityData()->Vz);
				mutex.unlock();
			}
		}

		printf("DisplayThread done %lu\n", (long unsigned int)getThreadId());
		return NULL;
	}
