#include <cstdlib>
#include <iostream.h>
#include <list>
#include <math.h>

#ifndef navidata_h
#define navidata_h

//-----------------------------------------------------------------------------------------
// NaviData interface.
//-----------------------------------------------------------------------------------------
class NaviData
{
	// structures are private and their members are public by default

	// velocity structure declaration: data-holder for calculated  velocity values
	struct Velocity
	{
		double Vx;
		double Vy;
		double Vz;
	};

	// distance structure declaration: data-holder for calculated  distance values
	struct Distance
	{
		double x;
		double y;
		double z;
	};

	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		NaviData();

		// destructor
		~NaviData();

		// returns a pointer to a velocity structure that holds calculated velocity values
		Velocity* getVelocityData();

		// returns a pointer to a distance structure that holds calculated distance values
		Distance* getDistanceData();


	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
	private:
		Velocity* velocityData;
		Distance* distanceData;
};

#endif
