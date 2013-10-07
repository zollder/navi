#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "BaseThread.h"
#include "Mutex.h"

#ifndef acceleratorthread_h
#define acceleratorthread_h

//-----------------------------------------------------------------------------------------
// AcceleratorThread interface.
//-----------------------------------------------------------------------------------------
class AcceleratorThread : public BaseThread
{
		Mutex& mutex;

	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		AcceleratorThread(Mutex& mutexRef);

		// destructor
		~AcceleratorThread();

		// overrides BaseThread's run() method
		void* run();
};

#endif
