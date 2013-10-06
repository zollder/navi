navi
====

Source code for a QNX navi project

Initial value of position (3D co-ordinates)
X= 0.0, Y = 0.0, Z = 0.0
Initial value of velocity (on the 3 axes)
Vx= 0.0, Vy = 0.0, Vz = 0.0

Design consists of two tasks:
-----------------------------
1 - Data Acquisition and Processing (DAP)
2 - Data Display

DAP (Producer)
---
	Every 2 second performs the following:
	Updates velocity and Position
		Vx = Vx + Ax * T
		Vy = Vy + Ay * T
		Vz = Vz + (Az − g) * T
		X = X + Vx * T
		Y = Y + Vy * T
		Z = Z + Vz * T
	Get Accelerometer Data Acquire
		Simulated here with three assignment statements
		can also be obtained from an array
		Ax = −2.0
		Ay = 4.0
		Az = 10.5

	Here T=2.0 sec is the sampling period.
	g=9.8 m/sec2 is gravity. 
	All of the above variables are double (Double precision floating–point).

Display (Consumer)
-------
	The Data Display thread shows velocity and position data on screen.
	cout << X, Y, Z, Vx, Vy and Vz every 6 seconds

Timers
------
	Time creation and setup
	Two timer objects producing pulse at 2sec and 6sec
	Pulse generation and receipt using asynchronous message passing channels
	Execution time measurement

Threads
-------
	pthread_create(id, attr, func, args)
	pthread_join(id, exit_value)

Mutex
-----
	m = PTHREAD_MUTEX_INITIALIZER
	pthread_mutex_lock(&m)
	pthread_mutex_unlock(&m)
	
Requirements
-------------
	You must follow object–oriented programming methodology
		i.e.For instance, you should create classes for threads and timers.
	Use a mutex to ensure that the threads do not gain access to the position and velocity variables simultaneously.

What to Submit
--------------
Submit the following on the day of project demonstration:
	1. A brief report explaining your program and results. 
	Discuss timer creation and the procedure used for measuring the computation times.
	2. Source codes (with comments), Makefiles and README files of your project. 
	Make sure your program compiles.
	3. Run the program for 30 seconds and submit the output.
	4. An “Expectations of Originality” form with your report.
	All submissions should be done electronically on Moodle. 
	The originality form may be submitted as a scanned copy.
	
Grading
-------
	The program works and is well designed [8 pts]
		-Threads for DAP and DD have been created
		-Velocity and position variable access has been protected
		-Timer classes created and objects instantiated, connected to DAP and DD
		-Must run for 30 seconds
			*Display all timer pulses and their time annotation
		-Minimum needed to pass the course
	Timing measurement [4 pts]
		-Proper calculation of DAP and DD execution time
		-Individual iterations only
		-Calculate best/worst/average over 30 seconds of execution
	Understanding of the design [4 pts]
		-Based on Q&A at the time of demonstration
		-Grades may be different for students in the same group
		
References
----------
[1] QNX: http://www.qnx.com
[2] QNX Realtime Platform: http://www.qnx.com/developers/docs/6.3.2/neutrino/
[3] C Library Reference: http://www.qnx.com/developers/docs/6.3.2/neutrino/lib ref/about.html
[4] ECE Real-time Systems Lab: http://users.encs.concordia.ca/~realtime/
