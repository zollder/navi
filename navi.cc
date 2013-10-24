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

	//Creating DAP and DD individual coexisting threads
	DisplayThread* displayThread = new DisplayThread(mutex, naviData);
	AcceleratorThread* acceleratorThread = new AcceleratorThread(mutex, naviData);

	//Creating two timers to send pulse for the two existing threads with different timing constraints
	PulseTimer* displayTimer = new PulseTimer(6, displayThread->getChannelId());
	PulseTimer* acceleratorTimer = new PulseTimer(2, acceleratorThread->getChannelId());

	//Start program
	displayThread->start();
	displayTimer->start();
	delay(1);
	printf("\t-------------Begin---------------\n");
	acceleratorThread->start();
	acceleratorTimer->start();

	//End program
	displayThread->join();
	acceleratorThread->join();
	printf("\t-------------END-----------------\n");

	//Removing memory allocated objects
	delete displayTimer;
	delete acceleratorTimer;
	delete displayThread;
	delete acceleratorThread;
	delete naviData;


	printf("Main thread done!\n");
	return EXIT_SUCCESS;
}
