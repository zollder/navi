
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "DisplayThread.h"
#include "AcceleratorThread.h"
#include "PulseTimer.h"
#include "NaviData.h"

int main(void)
{
	printf("Main thread started!\n");

	Mutex mutex;
	NaviData* naviData = new NaviData();

	// creating DAP and DD threads
	//DisplayThread* displayThread = new DisplayThread(mutex, naviData);
	AcceleratorThread* acceleratorThread = new AcceleratorThread(mutex, naviData);

	// creating timers for each thread with specified pulse interval
	//PulseTimer* displayTimer = new PulseTimer(6, displayThread->getChannelId());
	PulseTimer* acceleratorTimer = new PulseTimer(2, acceleratorThread->getChannelId());

	printf("\n\n\t-------------Begin---------------\n\n");

	// start timers and threads
	//displayThread->start();
	//displayTimer->start();
	acceleratorThread->start();
	acceleratorTimer->start();

	// terminate threads
	//displayThread->join();
	acceleratorThread->join();

	printf("\n\n\t-------------END-----------------\n\n");

	// cleanup
	//delete displayTimer;
	delete acceleratorTimer;
	//delete displayThread;
	delete acceleratorThread;
	delete naviData;

	printf("Main thread done!\n");
	return EXIT_SUCCESS;
}
