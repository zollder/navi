
#include "BaseThread.h"

//---------------------------------------------------------------------------------------------
// BaseThread class implementation.
//---------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	BaseThread::BaseThread()
	{
		cout << "Constructing BaseThread ..." << endl;
		setThreadId(0);
		setRunning(false);
		setDetached(false);
	}

	//-----------------------------------------------------------------------------------------
	// Destroys thread object.
	// - if the thread is running, mark it as detached to reclaim its storage upon termination
	// - terminate thread, if it's running
	//-----------------------------------------------------------------------------------------
	BaseThread::~BaseThread()
	{
		cout << "Destroying BaseThread ..." << endl;

		if (isRunning() && !isDetached())
			pthread_detach(threadId);

		if (isRunning())
			pthread_cancel(threadId);
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
	// Returns thread id for display or logging purposes.
	//-----------------------------------------------------------------------------------------
	void BaseThread::setThreadId(int id)
	{
		threadId = id;
	}


