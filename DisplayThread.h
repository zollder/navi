#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "BaseThread.h"

#ifndef displaythread_h
#define displaythread_h

//-----------------------------------------------------------------------------------------
// DisplayThread interface.
//-----------------------------------------------------------------------------------------
class DisplayThread : public BaseThread
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		DisplayThread(Mutex&, NaviData*);

		// destructor
		~DisplayThread();

		// overrides BaseThread's run() method
		void* run();
};

#endif
