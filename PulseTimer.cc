
#include "PulseTimer.h"

//---------------------------------------------------------------------------------------------
// Periodic PulseTimer class implementation.
//---------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	PulseTimer::PulseTimer(double interval, int channelId)
	{
		printf("Creating and initializing PulseTimer ...\n");

		// connect client to the channel
		connectionAttach(channelId);

		// convert interval to seconds and nanoseconds and initialize corresponding members
		setInterval(interval);

		// initialize notification structure and create timer
		createTimer();

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
		printf("Destroying PulseTimer ...\n");

		// detaches the connection
		if (ConnectDetach(getConnectionId()) < 0)
			printf("Error detaching connection \n");

		// 0 <=> success, -1 <=> failure
		if (timer_delete(timerId) != 0)
			printf("Error removing timer \n");
	}

	//-----------------------------------------------------------------------------------------
	// Connects client (pulse timer) to the server (corresponding thread).
	// Establishes a connection between the calling process and the channel specified by chId.
	//-----------------------------------------------------------------------------------------
	void PulseTimer::connectionAttach(int chId)
	{
		int connectId = ConnectAttach(0, 0, chId, 0, 0);
		if (connectId == -1)
		{
			printf("Error attaching connection \n");
			setDetached(true);
			exit(EXIT_FAILURE);
		}
		else
		{
			printf("Connection attached successfully \n");
			setConnectionId(connectId);
			setDetached(false);
		}
	}

	//-----------------------------------------------------------------------------------------
	// Converts specified time interval into seconds and nanoseconds
	//-----------------------------------------------------------------------------------------
	void PulseTimer::setInterval(double interval)
	{
		seconds = floor(interval);
		nanoseconds = (interval - seconds)*pow(10,9);
	}

	//-----------------------------------------------------------------------------------------
	// Initializes notification.
	// Creates timer object within the kernel and initializes timerId (returns reference to timerId)
	//-----------------------------------------------------------------------------------------
	void PulseTimer::createTimer()
	{
		SIGEV_PULSE_INIT(&event, getConnectionId(), SIGEV_PULSE_PRIO_INHERIT, PULSE_FROM_TIMER, NULL);

		int timer = timer_create(CLOCK_REALTIME, &event, &timerId);
		if (timer == -1)
		{
			printf("Timer creation error \n");
			exit(EXIT_FAILURE);
		}
		else
			printf("Timer created successfully \n");
	}

	//-----------------------------------------------------------------------------------------
	// Starts timer and updates its running status.
	//-----------------------------------------------------------------------------------------
	int PulseTimer::start()
	{
		// (re)initializes timer structure
		reset();

		// start the timer and running status accordingly
		int result = timer_settime(timerId, 0, &timer, NULL);
		if (result != 0)
		{
			printf("Error creating timer \n");
			exit(EXIT_FAILURE);
		}
		else
		{
			this->setRunning(true);
			printf("Timer started \n");
		}

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
	void PulseTimer::reset()
	{
		// periodic timer: will go off in 1 sec and then again every sec+nanosec
		timer.it_value.tv_sec = 1;
		timer.it_value.tv_nsec = 0;
		timer.it_interval.tv_sec = getSeconds();
		timer.it_interval.tv_nsec = getNanoseconds();
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
	long PulseTimer::getSeconds()
	{
		return seconds;
	}

	//-----------------------------------------------------------------------------------------
	// Returns nanoseconds portion (converted) of the timer interval.
	//-----------------------------------------------------------------------------------------
	long PulseTimer::getNanoseconds()
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
