
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "DisplayThread.h"
#include "AcceleratorThread.h"
#include "PulseTimer.h"

int main(void)
{
	cout << "Main thread started!" << endl;

	Mutex mutex;

	DisplayThread* displayThread = new DisplayThread(mutex);
	AcceleratorThread* acceleratorThread = new AcceleratorThread(mutex);

	PulseTimer* displayTimer = new PulseTimer(1.2, displayThread->getChannelId());
	PulseTimer* acceleratorTimer = new PulseTimer(1.5, acceleratorThread->getChannelId());

	displayThread->start();
	displayTimer->start();
	delay(1);
	acceleratorThread->start();
	acceleratorTimer->start();

	displayThread->join();
	acceleratorThread->join();

	delete displayTimer;
	delete acceleratorTimer;
	delete displayThread;
	delete acceleratorThread;

	cout << "Main thread done!" << endl;
	return EXIT_SUCCESS;
}
