#include <pthread.h>

#ifndef mutex_h
#define mutex_h

//-----------------------------------------------------------------------------------------
// Mutex class definition and implementation.
// Works as a wrapper around standard pthread_mutex functions.
//-----------------------------------------------------------------------------------------
class Mutex
{
	public:
		//-----------------------------------------------------------------------------------------
		// Constructor (initializes mutex)
		//-----------------------------------------------------------------------------------------
		Mutex()
		{
			pthread_mutex_init(&mutex, NULL);
		}

		//-----------------------------------------------------------------------------------------
		// Destructor
		//-----------------------------------------------------------------------------------------
		virtual ~Mutex()
		{
			pthread_mutex_destroy(&mutex);
		}

		//-----------------------------------------------------------------------------------------
		// Locks mutex, returns 0 (success) or error code (failure).
		//-----------------------------------------------------------------------------------------
		int lock()
		{
			return pthread_mutex_lock(&mutex);
		}

		//-----------------------------------------------------------------------------------------
		// Unlocks mutex, returns 0 (success) or error code (failure).
		//-----------------------------------------------------------------------------------------
		int unlock()
		{
			return pthread_mutex_unlock(&mutex);
		}

		//-----------------------------------------------------------------------------------------
		// Tries to lock mutex, returns 0 (success) or error code (failure).
		//-----------------------------------------------------------------------------------------
		int trylock()
		{
			return pthread_mutex_lock(&mutex);
		}

	private:
		pthread_mutex_t  mutex;
};

#endif
