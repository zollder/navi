#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <sys/syspage.h>

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

		// --- Get CPU frequency in order to do precise time calculation
		cpu_freq =  SYSPAGE_ENTRY( qtime )->cycles_per_sec;
		startTime = time(NULL);


		 // --- Get CPU frequency in order to do precise time calculation
		int counter = 0;
		while( ++counter <= duration/3 )
		{
			//Wait for signal / pulse set by the timer
			int receivedPulse = MsgReceivePulse(getChannelId(), &buffer, sizeof(buffer), NULL);

			//Clock stamp execution start
			current_cycles = ClockCycles();
			if (receivedPulse != 0)
			{
				printf("Error receiving display pulse\n");
			}
			else
			{
				printf("Display pulse %d received at time %d seconds\n",  counter , time(NULL)-startTime  );

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
				printf("Velocity: Vx: %f, Vy: %f, Vz: %f \n",vx,vy,vz);

				//Clock stamp execution stop
				last_cycles = ClockCycles();

			    //Calculate execution time
			    float elapse = ( last_cycles - current_cycles) / cpu_freq;
		    	printf("Display Execution time %f seconds\n\n", elapse );




			}
		}

		printf("DisplayThread %lu done at %d seconds\n", (long unsigned int)getThreadId() , time(NULL)-startTime );
		return NULL;
	}
