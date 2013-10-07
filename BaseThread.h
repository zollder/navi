#include <cstdlib>
#include <iostream.h>
#include <pthread.h>

#ifndef basethread_h
#define basethread_h

//-----------------------------------------------------------------------------------------
// BaseThread interface.
//-----------------------------------------------------------------------------------------
class BaseThread
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		BaseThread();

		// virtual destructor
		// forces subclass destructor call upon object deletion through a base class pointer
		virtual ~BaseThread();

		// starts thread
		int start();

		// joins thread
		int join();

		// detaches thread
		int detach();

		// sets thread id
		void setThreadId(int id);

		// returns reference to instantiated thread object (itself)
		pthread_t getThreadId();

		// sets thread's running flag (1=true, 0=false)
		void setRunning(bool);

		// returns thread's running state
		bool isRunning();

		// sets thread's detached flag (1=true, 0=false)
		void setDetached(bool);

		// returns thread's detached state
		bool isDetached();

		// forces the class to be abstract and requires the run() to be overridden by a subclass;
		virtual void* run() = 0;

	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
	private:
		pthread_t threadId;
		bool running;
		bool detached;
};

#endif
