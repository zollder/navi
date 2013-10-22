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

		double* acceleratorData;
		//vector<float> acceleratorData;

		// constructor
		AcceleratorThread(Mutex&, NaviData*);

		// destructor
		~AcceleratorThread();

		// overrides BaseThread's run() method
		void* run();
};

#endif
