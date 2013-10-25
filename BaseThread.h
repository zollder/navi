#include <cstdlib>
#include <iostream.h>
#include <pthread.h>
#include <sys/neutrino.h>
#include <sstream>
#include <time.h>
#include <sys/netmgr.h>
#include <sys/syspage.h>

#include "Mutex.h"
#include "NaviData.h"

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

		static const int duration = 5;
		static const float gravity = 9.8;
		static const double interval = 2;

		// constructor
		BaseThread(Mutex&, NaviData*);

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

		Mutex& mutex;
		NaviData* naviData;
		stringstream outputStream;

		//timing variables
		_uint64 last_cycles;
		_uint64 current_cycles;
		float cpu_freq;
		time_t startTime;

		// local data holders
		double x, y, z;
		double Vx, Vy, Vz;

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
