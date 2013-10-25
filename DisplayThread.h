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

	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
    private:
		// local data holders (distance and velocity)
		double x,y,z;
		double Vx,Vy,Vz;
};

#endif
