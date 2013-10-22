

#include "NaviData.h"

//---------------------------------------------------------------------------------------------
// NaviData class implementation.
//---------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	NaviData::NaviData()
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
	}

	//-----------------------------------------------------------------------------------------
	// Destructor
	//-----------------------------------------------------------------------------------------
	NaviData::~NaviData()
	{
		printf("Destroying NaviData ... \n");

		delete velocityData;
		delete distanceData;
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
