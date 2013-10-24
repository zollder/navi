
#include "BaseThread.h"

//---------------------------------------------------------------------------------------------
// BaseThread class implementation.
//---------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	BaseThread::BaseThread(Mutex& mutex_r, NaviData* naviData_p) : mutex(mutex_r)
	{
		printf("Constructing BaseThread ...\n");

		setThreadId(1);
		setRunning(false);
		setDetached(false);
		setChannelId(createChannel());
		mutex = mutex_r;
		naviData = naviData_p;
		last_cycles=-1;
	}

	//-----------------------------------------------------------------------------------------
	// Destroys thread object.
	// - if the thread is running, mark it as detached to reclaim its storage upon termination
	// - terminate thread, if it's running
	// - destroy communication channel if it was successfully created by constructor
	//-----------------------------------------------------------------------------------------
	BaseThread::~BaseThread()
	{
		printf("Destroying BaseThread ...\n");

		if (isRunning() && !isDetached())
			pthread_detach(threadId);

		if (isRunning())
			pthread_cancel(threadId);

		int chId = getChannelId();
		if (chId != -1)
			ChannelDestroy(chId);
	}

	//-----------------------------------------------------------------------------------------
	// Makes the current Thread instance runnable
	//-----------------------------------------------------------------------------------------
	static void* runThread(void* arg)
	{
		return ((BaseThread*)arg)->run();
	}

	//-----------------------------------------------------------------------------------------
	// Starts a new thread or updates thread running status if the thread is already running.
	// - threadId <=> reference to runThread for its future calls
	// - runThread <=> target function that makes this class instance 'runnable'
	// - this <=> void pointer to BaseThread instance, required to call run() within runThread
	// - result = 0 => successful creation, result > 0 => failed to create thread
	//-----------------------------------------------------------------------------------------
	int BaseThread::start()
	{
		int result = pthread_create(&threadId, NULL, runThread, this);
		if (result == 0)
			this->setRunning(true);

		return result;
	}

	//-----------------------------------------------------------------------------------------
	// Waits for the thread to complete and sets detached flag since pthread_join detaches it.
	//-----------------------------------------------------------------------------------------
	int BaseThread::join()
	{
		int result = -1;
		if (isRunning())
		{
			result = pthread_join(threadId, NULL);
			if (result == 0)
				setDetached(true);
		}

		return result;
	}

	//-----------------------------------------------------------------------------------------
	// Detaches a running and non-detached thread before it completes execution.
	// Sets 'detached' flag if the operation is successful.
	//-----------------------------------------------------------------------------------------
	int BaseThread::detach()
	{
		int result = -1;
		if (isRunning() && !isDetached())
		{
			result = pthread_detach(threadId);
			if (result == 0)
				setDetached(true);
		}

		return result;
	}

	//-----------------------------------------------------------------------------------------
	// Returns thread's running status.
	//-----------------------------------------------------------------------------------------
	bool BaseThread::isRunning()
	{
		return running;
	}

	//-----------------------------------------------------------------------------------------
	// Sets thread's running state.
	//-----------------------------------------------------------------------------------------
	void BaseThread::setRunning(bool runningState)
	{
		running = runningState;
	}

	//-----------------------------------------------------------------------------------------
	// Returns thread's detached status.
	//-----------------------------------------------------------------------------------------
	bool BaseThread::isDetached()
	{
		return detached;
	}

	//-----------------------------------------------------------------------------------------
	// Sets thread's detached state.
	//-----------------------------------------------------------------------------------------
	void BaseThread::setDetached(bool detachedState)
	{
		detached = detachedState;
	}

	//-----------------------------------------------------------------------------------------
	// Returns thread id for display or logging purposes.
	//-----------------------------------------------------------------------------------------
	pthread_t BaseThread::getThreadId()
	{
		return threadId;
	}

	//-----------------------------------------------------------------------------------------
	// Sets thread id for display or logging purposes.
	//-----------------------------------------------------------------------------------------
	void BaseThread::setThreadId(int id)
	{
		threadId = id;
	}

	//-----------------------------------------------------------------------------------------
	// Returns channel id.
	//-----------------------------------------------------------------------------------------
	int BaseThread::getChannelId()
	{
		return channelId;
	}

	//-----------------------------------------------------------------------------------------
	// Sets channel id.
	//-----------------------------------------------------------------------------------------
	void BaseThread::setChannelId(int chId)
	{
		channelId = chId;
	}

	//-----------------------------------------------------------------------------------------
	// Creates a channel that can receive messages and pulses.
	// ConnectAttach() should be called from the timer object in order to establish connection.
	//-----------------------------------------------------------------------------------------
	int BaseThread::createChannel()
	{
		// disable priority inheritance with _NTO_CHF_FIXED_PRIORITY option
		int chId = ChannelCreate(_NTO_CHF_FIXED_PRIORITY);
		if (chId == -1)
				printf("Error creating channel \n");
		else
			// for debugging purpose only
			printf("Channel successfully created \n");

		return chId;
	}
