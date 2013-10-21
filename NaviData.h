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

	struct Accelerator
	{
		double Ax;
		double Ay;
		double Az;
	};

	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		NaviData(double);

		// destructor
		~NaviData();

		static const float gravity = 9.8;

		// returns a pointer to a velocity structure that holds calculated velocity values
		Velocity* getVelocityData();

		// returns a pointer to a distance structure that holds calculated distance values
		Distance* getDistanceData();

		// returns a list of objects of predefined 3D acceleration values
		std::list<Accelerator*>* getAcceleratorData();


	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
	private:
		Velocity* velocityData;
		Distance* distanceData;
		list<Accelerator*>* acceleratorData;

		// initializes accelerator data list
		list<Accelerator*>* initAcceleratorData(double);

		// deletes accelerator data list members
		void deleteAcceleratorData();
};

#endif
