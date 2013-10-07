#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#include "BaseThread.h"
#include "Mutex.h"

#ifndef displaythread_h
#define displaythread_h

//-----------------------------------------------------------------------------------------
// DisplayThread interface.
//-----------------------------------------------------------------------------------------
class DisplayThread : public BaseThread
{
		Mutex& mutex;

	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		DisplayThread(Mutex& mutexRef);

		// destructor
		~DisplayThread();

		// overrides BaseThread's run() method
		void* run();
};

#endif
