#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#ifndef acceleratorthread_h
#define acceleratorthread_h

#include "BaseThread.h"

//-----------------------------------------------------------------------------------------
// AcceleratorThread interface.
//-----------------------------------------------------------------------------------------
class AcceleratorThread : public BaseThread
{
	public:
		// constructor
		AcceleratorThread();

		// virtual destructor
		~AcceleratorThread();

		// overriding base class method
		void* run();
};

#endif
