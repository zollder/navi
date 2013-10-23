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

		acceleratorData = new double[duration];
		for (int i = 0; i <= duration; i++)
		{
			acceleratorData[i] = log(i+1);
			printf("init value: %f \n", acceleratorData[i]);
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
		while(++ counter <= duration)
		{
			printf("In the accelerator while loop ...\n");

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

				double Vx = naviData->getVelocityData()->Vx + acceleratorData[counter] * calculation_period;
				double Vy = naviData->getVelocityData()->Vy + acceleratorData[counter] * calculation_period;
				double Vz = naviData->getVelocityData()->Vz + (acceleratorData[counter] - gravity) * calculation_period;

				naviData->getVelocityData()->Vx = Vx;
				naviData->getVelocityData()->Vy = Vy;
				naviData->getVelocityData()->Vz = Vz;

				double x = naviData->getDistanceData()->x + Vx * calculation_period;
				double y = naviData->getDistanceData()->y + Vy * calculation_period;
				double z = naviData->getDistanceData()->z + Vz * calculation_period;

				naviData->getDistanceData()->x = x;
				naviData->getDistanceData()->y = y;
				naviData->getDistanceData()->z = z;

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

		printf("AcceleratorThread done %lu\n", (long unsigned int)getThreadId());

		return NULL;
	}
