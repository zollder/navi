
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "DisplayThread.h"
#include "AcceleratorThread.h"
#include "PulseTimer.h"
#include "NaviData.h"

int main(void)
{
	printf("Main thread started!");


	Mutex mutex;
	NaviData* naviData = new NaviData();

	DisplayThread* displayThread = new DisplayThread(mutex, naviData);
	AcceleratorThread* acceleratorThread = new AcceleratorThread(mutex, naviData);

	PulseTimer* displayTimer = new PulseTimer(6, displayThread->getChannelId());
	PulseTimer* acceleratorTimer = new PulseTimer(2, acceleratorThread->getChannelId());

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

	delete naviData;

	printf("Main thread done!\n");
	return EXIT_SUCCESS;
}
