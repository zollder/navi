

#include "NaviData.h"

//---------------------------------------------------------------------------------------------
// NaviData class implementation.
//---------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	NaviData::NaviData(double duration)
	{
		printf("Initializing NaviData ... \n");

		// initialize velocity data holder
		velocityData = new Velocity();
		velocityData -> Vx = 0;
		velocityData -> Vy = 0;
		velocityData -> Vz = 0;

		// initialize distance data holder
		distanceData = new Distance();
		distanceData -> x = 0;
		distanceData -> y = 0;
		distanceData -> z = 0;

		acceleratorData = initAcceleratorData(duration);
	}

	//-----------------------------------------------------------------------------------------
	// Destructor
	//-----------------------------------------------------------------------------------------
	NaviData::~NaviData()
	{
		printf("Destroying NaviData ... \n");

		delete velocityData;
		delete distanceData;
		deleteAcceleratorData();
		delete acceleratorData;
	}

	//-----------------------------------------------------------------------------------------
	// returns a pointer to velocity data holder.
	//-----------------------------------------------------------------------------------------
	NaviData::Velocity* NaviData::getVelocityData()
	{
		return velocityData;
	}

	//-----------------------------------------------------------------------------------------
	// returns a pointer to distance data holder.
	//-----------------------------------------------------------------------------------------
	NaviData::Distance* NaviData::getDistanceData()
	{
		return distanceData;
	}

	//-----------------------------------------------------------------------------------------
	// Returns a pointer to a list of accelerator data holder pointers.
	//-----------------------------------------------------------------------------------------
	std::list<NaviData::Accelerator*>* NaviData::getAcceleratorData()
	{
		return acceleratorData;
	}

	//-----------------------------------------------------------------------------------------
	// initializes a list of predefined accelerator data holder pointers.
	//-----------------------------------------------------------------------------------------
	std::list<NaviData::Accelerator*>* NaviData::initAcceleratorData(double duration)
	{
		std::list<Accelerator*>* dataList = new std::list<Accelerator*>();
		for (int i = 1; i <= (int) duration; i++)
		{
			Accelerator* dataMember = new Accelerator();
			double result = log2(i);
			dataMember->Ax = result;
			dataMember->Ay = result;
			dataMember->Az = result;

			dataList->push_back(dataMember);
		}

		return dataList;
	}

	//-----------------------------------------------------------------------------------------
	// Cleans up accelerator data holder list.
	//-----------------------------------------------------------------------------------------
	void NaviData::deleteAcceleratorData()
	{
		std::list<Accelerator*>::iterator position = acceleratorData->begin();
		while (position != acceleratorData->end())
		{
			delete *position;
			position++;
		}

		acceleratorData->clear();
	}
