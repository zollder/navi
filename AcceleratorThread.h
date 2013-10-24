#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "BaseThread.h"

#ifndef acceleratorthread_h
#define acceleratorthread_h

//-----------------------------------------------------------------------------------------
// AcceleratorThread interface.
//-----------------------------------------------------------------------------------------
class AcceleratorThread : public BaseThread
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		AcceleratorThread(Mutex&, NaviData*);

		// destructor
		~AcceleratorThread();

		// overrides BaseThread's run() method
		void* run();

	private:
		//acceleration simulated variables
		double* acceleratorDataX;
		double* acceleratorDataY;
		double* acceleratorDataZ;

		//local storage temporary variables
		double x, y, z;
		double Vx, Vy, Vz;
};

#endif
