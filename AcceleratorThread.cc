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

		x = 0; y = 0; z = 0;
		Vx = 0; Vy = 0; Vz = 0;

		// initialize accelerator data arrays
		acceleratorDataX = new double[duration];
		acceleratorDataY = new double[duration];
		acceleratorDataZ = new double[duration];

		// fill arrays with dummy sensor data (for simulation purposes only)
		for (int i = 0; i <= duration; i++)
		{
			acceleratorDataX[i] = 20 + log(i+1);
			acceleratorDataY[i] = 20 + log(i+2);
			acceleratorDataZ[i] = 9 + 2*log(i+1);
			printf("Ax: %f, Ay: %f, Az %f \n", acceleratorDataX[i], acceleratorDataY[i], acceleratorDataZ[i]);
		}
	}

	//-----------------------------------------------------------------------------------------
	// Destructor
	//-----------------------------------------------------------------------------------------
	AcceleratorThread::~AcceleratorThread()
	{
		printf("Destroying AcceleratorThread ...\n");
		delete acceleratorDataX;
		delete acceleratorDataY;
		delete acceleratorDataZ;
	}

	//-----------------------------------------------------------------------------------------
	// Overrides BaseThread's run() method
	//-----------------------------------------------------------------------------------------
	void* AcceleratorThread::run()
	{
		// dummy buffer
		string buffer[8];

		int counter = 0;
		while(counter <= duration)
		{
			int receivedPulse = MsgReceivePulse(getChannelId(), &buffer, sizeof(buffer), NULL);

			if (receivedPulse != 0)
			{
				printf("Error receiving accelerator pulse\n");
				exit(EXIT_FAILURE);
			}
			else
			{
				printf("Accelerator pulse %d received\n", counter);

				mutex.lock();

				// calculate
				Vx = naviData->getVelocityData()->Vx + acceleratorDataX[counter] * calculation_period;
				Vy = naviData->getVelocityData()->Vy + acceleratorDataY[counter] * calculation_period;
				Vz = naviData->getVelocityData()->Vz + (acceleratorDataZ[counter] - gravity) * calculation_period;

				double x = naviData->getDistanceData()->x + Vx * calculation_period;
				double y = naviData->getDistanceData()->y + Vy * calculation_period;
				double z = naviData->getDistanceData()->z + Vz * calculation_period;

				// save calculated values
				naviData->getVelocityData()->Vx = Vx;
				naviData->getVelocityData()->Vy = Vy;
				naviData->getVelocityData()->Vz = Vz;

				naviData->getDistanceData()->x = x;
				naviData->getDistanceData()->y = y;
				naviData->getDistanceData()->z = z;

				// simulate extra time
				for (int i = 0; i < 100000; i++)
				{
					i = i + 1;
					i = i - 1;
				}

				mutex.unlock();

				// print results, for logging purposes
				printf("Distance: x: %f, y: %f, z: %f \n",
						naviData->getDistanceData()->x,
						naviData->getDistanceData()->y,
						naviData->getDistanceData()->z);
				printf("Velocity: Vx: %f, Vy: %f, Vz: %f \n\n",
						naviData->getVelocityData()->Vx,
						naviData->getVelocityData()->Vy,
						naviData->getVelocityData()->Vz);

				++counter;
			}
		}

		printf("AcceleratorThread done %lu\n", (long unsigned int)getThreadId());

		return NULL;
	}
