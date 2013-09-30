
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "DisplayThread.h"
#include "AcceleratorThread.h"

int main()
{
	cout << "Main thread started!" << endl;

	DisplayThread* displayThread = new DisplayThread();
	AcceleratorThread* acceleratorThread = new AcceleratorThread();

	displayThread->start();
	acceleratorThread->start();

	displayThread->join();
	acceleratorThread->join();

	delete displayThread;
	delete acceleratorThread;

	cout << "Main thread done!" << endl;
	exit(0);
}
