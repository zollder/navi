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

		int n = 10;
		while(n != 0)
		{
			int receivedPulse = MsgReceivePulse(getChannelId(), &buffer, sizeof(buffer), NULL);
			if (receivedPulse != 0)
			{
				printf("Error receiving display pulse\n");
			}
			else
			{
				printf("Display pulse %d received\n",  n);

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

				n--;
			}
		}

		printf("DisplayThread done %lu\n", (long unsigned int)getThreadId());
		return NULL;
	}
