#include <cstdlib>
#include <iostream.h>
#include <time.h>
#include <sys/siginfo.h>
#include <sys/neutrino.h>

// include -lmath linker option at compile time to avoid "undefined reference" error
#include <math.h>

#ifndef pulsetimer_h
#define pulsetimer_h

// pulse from timer (check the pulse's code value upon message receipt)
#define PULSE_FROM_TIMER 1

//-----------------------------------------------------------------------------------------
// PulseTimer interface.
//-----------------------------------------------------------------------------------------
class PulseTimer
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		PulseTimer(double interval, int channelId);

		// destructor
		~PulseTimer();

		// starts timer
		int start();

		// stops timer
		int stop();

		// (re)initializes the guts of the timer structure
		void reset();

		// detaches timer from the channel.
		int detach();

		// returns a handle to the current timer instance (itself)
		timer_t getTimerId();

		// returns connection id
		int getConnectionId();

		// returns seconds portion of the time interval
		long getSeconds();

		// returns nanoseconds portion of the time interval
		long getNanoseconds();

		// returns timer's running state
		bool isRunning();

		// returns timer's detached state
		bool isDetached();

	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
	private:

		timer_t timerId;
		struct itimerspec timer;
		struct sigevent event;
		int connectionId;

		long seconds;
		long nanoseconds;

		bool running;
		bool detached;

	//-----------------------------------------------------------------------------------------
	// Protected members
	//-----------------------------------------------------------------------------------------
	protected:

		// attaches connection
		void connectionAttach(int);

		// sets seconds portion of the time interval
		void setInterval(double interval);

		// creates timer
		void createTimer();

		// sets connection id
		void setConnectionId(int id);

		// sets timer's running flag (1=true, 0=false)
		void setRunning(bool);

		// sets timer's detached flag (1=true, 0=false)
		void setDetached(bool);
};

#endif
