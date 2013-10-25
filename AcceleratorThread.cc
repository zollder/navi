#include <stdio.h>
#include <cstdlib>
#include <iostream.h>
#include <unistd.h>
#include <pthread.h>

#include "AcceleratorThread.h"
#include "PulseTimer.h"

//---------------------------------------------------------------------------------------------
// AcceleratorThread subclass implementation.
//---------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	AcceleratorThread::AcceleratorThread(Mutex& mutex_r, NaviData* naviData_p) : BaseThread(mutex_r, naviData_p)
	{
		printf("Constructing AcceleratorThread ...\n");

		// initialize accelerator data holders
		acceleratorDataX = new double[duration*3];
		acceleratorDataY = new double[duration*3];
		acceleratorDataZ = new double[duration*3];

		// fill arrays with dummy sensor data (for simulation purposes only)
		for (int i = 0; i <= duration*3; i++)
		{
			acceleratorDataX[i] = 20 + log(i+1);
			acceleratorDataY[i] = 20 + log(i+2);
			acceleratorDataZ[i] = 9 + 3*log(i+1);
			printf("Ax: %f, Ay: %f, Az %f \n", acceleratorDataX[i], acceleratorDataY[i], acceleratorDataZ[i]);
		}
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

		int counter = 0;
		while(counter != duration*3)
		{
			// wait for the pulse to fire
			int receivedPulse = MsgReceivePulse(getChannelId(), &buffer, sizeof(buffer), NULL);

			if (receivedPulse != 0)
			{
				printf("Error receiving accelerator pulse\n");
				exit(EXIT_FAILURE);
			}
			else
			{
				printf("\nAccelerator pulse %d received at time %d seconds\n", counter+1 , time(NULL)-startTime );

				// (measurements) clock stamp start
				current_cycles = ClockCycles();

				mutex.lock();

				// calculate
				Vx = naviData->getVelocityData()->Vx + acceleratorDataX[counter] * interval;
				Vy = naviData->getVelocityData()->Vy + acceleratorDataY[counter] * interval;
				Vz = naviData->getVelocityData()->Vz + (acceleratorDataZ[counter] - gravity) * interval;

				x = naviData->getDistanceData()->x + Vx * interval;
				y = naviData->getDistanceData()->y + Vy * interval;
				z = naviData->getDistanceData()->z + Vz * interval;

				// persist
				naviData->getVelocityData()->Vx = Vx;
				naviData->getVelocityData()->Vy = Vy;
				naviData->getVelocityData()->Vz = Vz;

				naviData->getDistanceData()->x = x;
				naviData->getDistanceData()->y = y;
				naviData->getDistanceData()->z = z;

				// simulate target system execution time
				for (int i = 0; i < 100000; i++)
				{
					i = i + 1;
					i = i - 1;
				}

				mutex.unlock();

				// (measurements) clock stamp end
				last_cycles = ClockCycles();

			    // calculate and log execution time
			    float elapse = ( last_cycles - current_cycles) / cpu_freq;
		    	printf("Accelerator Execution time %f seconds\n", elapse );

		    	counter++;
			}
		}

		printf("\nAcceleratorThread %lu done at %d seconds\n", (long unsigned int)getThreadId() , time(NULL)-startTime );

		return NULL;
	}
