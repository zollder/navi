#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
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
		// initialize time tracking variables
		float elapse = 0;
		float bcet = 1;
		float wcet = 0;
		float accumulator = 0;
		int count = 0;

		// dummy buffer
		string buffer[8];

		int counter = 0;
		while(counter < (duration+1))
		{
			// wait for the pulse to fire
			int receivedPulse = MsgReceivePulse(getChannelId(), &buffer, sizeof(buffer), NULL);

			// clock stamp execution start
			current_cycles = ClockCycles();

			if (receivedPulse != 0)
			{
				printf("Error receiving display pulse\n");
			}
			else
			{
				printf("\nDisplay pulse %d received at time %d seconds\n",  counter+1 , time(NULL)-startTime  );

				// fetch navi data from shared object
				mutex.lock();
				x = naviData->getDistanceData()->x;
				y = naviData->getDistanceData()->y;
				z = naviData->getDistanceData()->z;

				Vx = naviData->getVelocityData()->Vx;
				Vy = naviData->getVelocityData()->Vy;
				Vz = naviData->getVelocityData()->Vz;
				mutex.unlock();

				// Display distance and velocity (shared data object)
				printf("Distance: x: %f, y: %f, z: %f \n", x, y, z);
				printf("Velocity: Vx: %f, Vy: %f, Vz: %f \n", Vx, Vy, Vz);

				//Clock stamp execution stop
				last_cycles = ClockCycles();

			    //Calculate execution time
			    elapse = ( last_cycles - current_cycles) / cpu_freq;
		    	printf("Display Execution time %f seconds\n\n", elapse );

		    	// worst execution time tracker
		    	if (wcet < elapse)
		    		wcet = elapse;
		    	// best execution time tracker
		    	if (bcet > elapse)
		    		bcet = elapse;
		    	// exec time accumulator
		    	accumulator = accumulator + elapse;
		    	count++;

		    	counter++;
			}
		}

		printf("\nDisplayThread done %lu\n", (long unsigned int)getThreadId());

		// show time measurements
		printf("\nDD Worst-case execution time: %f", wcet);
		printf("\nDD Best-case execution time: %f", bcet);
		printf("\nDD Average execution time: %f\n", accumulator/count);

		return NULL;
	}
