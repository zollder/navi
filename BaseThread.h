#include <cstdlib>
#include <iostream.h>
#include <pthread.h>
#include <sys/neutrino.h>

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

		// returns reference to instantiated thread object (itself)
		pthread_t getThreadId();

		// returns thread's running state
		bool isRunning();

		// returns thread's detached state
		bool isDetached();

		// returns channel id
		int getChannelId();

		// forces the class to be abstract and requires the run() to be overridden by a subclass;
		virtual void* run() = 0;

	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
	private:
		pthread_t threadId;
		bool running;
		bool detached;
		int channelId;

	//-----------------------------------------------------------------------------------------
	// Protected members
	//-----------------------------------------------------------------------------------------
	protected:
		// sets thread id
		void setThreadId(int id);

		// sets thread's running flag (1=true, 0=false)
		void setRunning(bool);

		// sets thread's detached flag (1=true, 0=false)
		void setDetached(bool);

		// sets channel id
		void setChannelId(int);

		// creates communication channel
		int createChannel();
};

#endif
