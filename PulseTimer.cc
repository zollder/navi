
#include "PulseTimer.h"

//---------------------------------------------------------------------------------------------
// PulseTimer class implementation.
//---------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	PulseTimer::PulseTimer(double interval, int channelId)
	{
		cout << "Creating and initializing PulseTimer ..." << endl;

		// attach channel to the timer
		setConnectionId(ConnectAttach(0, 0, channelId, 0, 0));
		setDetached(false);

		// initialize notification structure
		SIGEV_PULSE_INIT(&event, getConnectionId(), SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_TIMER, NULL);

		// create timer object within the kernel and initialize timerId (returns reference to timerId)
		timer_create(CLOCK_REALTIME, &event, &timerId);

		// convert interval to seconds and nanoseconds and initialize corresponding members
		setInterval(interval);

		setRunning(false);
	}

	//-----------------------------------------------------------------------------------------
	// Destroys timer object.
	// 1. Detaches previously attached timer by specified connectionId (if not already detached).
	// 2. Removes it from the  timer_create() function by specified timerId.
	// (the timer is moved from  the active system timer list to the free list of available timers.)
	//-----------------------------------------------------------------------------------------
	PulseTimer::~PulseTimer()
	{
		cout << "Destroying PulseTimer ..." << endl;

		// detaches the connection
		if (ConnectDetach(getConnectionId()) < 0)
			printf("Error detaching connection \n");

		// 0 <=> success, -1 <=> failure
		if (timer_delete(timerId) != 0)
			printf("Error removing timer \n");
	}


	//-----------------------------------------------------------------------------------------
	// Starts timer or updates its running status.
	//-----------------------------------------------------------------------------------------
	int PulseTimer::start()
	{
		// (re)initializes timer structure
		reset();

		// start the timer and running status accordingly
		int result = timer_settime(timerId, 0, &timer, NULL);
		if (result == 0)
			this->setRunning(true);
		else
			printf("Error creating timer \n");

		return result;
	}

	//-----------------------------------------------------------------------------------------
	// Stops timer by nullifying its timer values and updating active system timer.
	//-----------------------------------------------------------------------------------------
	int PulseTimer::stop()
	{
		timer.it_value.tv_sec = 0;
		timer.it_value.tv_nsec = 0;
		timer.it_interval.tv_sec = 0;
		timer.it_interval.tv_nsec = 0;

		int result = timer_settime(timerId, 0, &timer, NULL);
		if (result == 0)
			this->setRunning(false);
		else
			printf("Error stopping timer \n");

		return result;
	}

	//-----------------------------------------------------------------------------------------
	// (Re)Initializes the guts of the timer structure.
	//-----------------------------------------------------------------------------------------
	int PulseTimer::reset()
	{
		timer.it_value.tv_sec = getSeconds();
		timer.it_value.tv_nsec = getNanoseconds();
		timer.it_interval.tv_sec = 0;
		timer.it_interval.tv_nsec = 0;
	}

	//-----------------------------------------------------------------------------------------
	// Detaches the connection specified by the connectionId.
	// If any threads are blocked on the connection at the time the connection is detached,
	// the send fails and returns with an error (see QNX doc for ConnectDetach()).
	//-----------------------------------------------------------------------------------------
	int PulseTimer::detach()
	{
		int result = ConnectDetach(getConnectionId());
		if (result == 0)
			this->setDetached(true);
		else
			printf("Error detaching connection \n");

		return result;
	}

	//-----------------------------------------------------------------------------------------
	// Returns timer id for display or logging purposes.
	//-----------------------------------------------------------------------------------------
	timer_t PulseTimer::getTimerId()
	{
		return timerId;
	}

	//-----------------------------------------------------------------------------------------
	// Returns timer's connection id.
	//-----------------------------------------------------------------------------------------
	int PulseTimer::getConnectionId()
	{
		return connectionId;
	}

	//-----------------------------------------------------------------------------------------
	// Returns seconds portion (converted) of the timer interval.
	//-----------------------------------------------------------------------------------------
	int PulseTimer::getSeconds()
	{
		return seconds;
	}

	//-----------------------------------------------------------------------------------------
	// Returns nanoseconds portion (converted) of the timer interval.
	//-----------------------------------------------------------------------------------------
	int PulseTimer::getNanoseconds()
	{
		return nanoseconds;
	}

	//-----------------------------------------------------------------------------------------
	// Returns timer's's running status.
	//-----------------------------------------------------------------------------------------
	bool PulseTimer::isRunning()
	{
		return running;
	}

	//-----------------------------------------------------------------------------------------
	// Returns timer's detached status.
	//-----------------------------------------------------------------------------------------
	bool PulseTimer::isDetached()
	{
		return detached;
	}

	//-----------------------------------------------------------------------------------------
	// Sets connection id.
	//-----------------------------------------------------------------------------------------
	void PulseTimer::setConnectionId(int id)
	{
		connectionId = id;
	}

	//-----------------------------------------------------------------------------------------
	// Sets timer's running state.
	//-----------------------------------------------------------------------------------------
	void PulseTimer::setRunning(bool runningState)
	{
		running = runningState;
	}

	//-----------------------------------------------------------------------------------------
	// Sets timer's detached flag (1=true, 0=false).
	//-----------------------------------------------------------------------------------------
	void PulseTimer::setDetached(bool detachedState)
	{
		detached = detachedState;
	}

	//-----------------------------------------------------------------------------------------
	// Converts specified time interval into seconds and nanoseconds
	//-----------------------------------------------------------------------------------------
	void PulseTimer::setInterval(double interval)
	{
		seconds = floor(interval);
		nanoseconds = (interval - seconds)*pow(10,9);
	}


