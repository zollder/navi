
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "DisplayThread.h"
#include "AcceleratorThread.h"

int main()
{
	cout << "Main thread started!" << endl;

	Mutex mutex;
	DisplayThread* displayThread = new DisplayThread(mutex);
	AcceleratorThread* acceleratorThread = new AcceleratorThread(mutex);

	displayThread->start();
	delay(1);
	acceleratorThread->start();

	displayThread->join();
	acceleratorThread->join();

	delete displayThread;
	delete acceleratorThread;

	cout << "Main thread done!" << endl;
	exit(0);
}
