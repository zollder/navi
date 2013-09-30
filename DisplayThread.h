#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#ifndef displaythread_h
#define displaythread_h

#include "BaseThread.h"

//-----------------------------------------------------------------------------------------
// DisplayThread interface.
//-----------------------------------------------------------------------------------------
class DisplayThread : public BaseThread
{
	public:
		// constructor
		DisplayThread();

		// virtual destructor
		~DisplayThread();

		// overriding base class method
		void* run();
};

#endif
