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
		//initialization of local temporary variables
		x=0, y=0, z=0;
		vx=0, vy=0, vz=0;
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
				printf("Display pulse %d received\n",  counter );

				//retrieve the coordinates from the shared storage
				mutex.lock();
				x = naviData->getDistanceData()->x;
				y = naviData->getDistanceData()->y;
				z = naviData->getDistanceData()->z;

				vx = naviData->getVelocityData()->Vx;
				vy = naviData->getVelocityData()->Vy;
				vz = naviData->getVelocityData()->Vz;
				mutex.unlock();

				//display the ready up to date distance and velocity
				printf("Distance: x: %f, y: %f, z: %f \n",x,y,z);
				printf("Velocity: Vx: %f, Vy: %f, Vz: %f \n\n",vx,vy,vz);
			}
		}

		printf("DisplayThread done %lu\n", (long unsigned int)getThreadId());
		return NULL;
	}
