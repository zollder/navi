navi
====

Source code for a QNX navi project

Initial value of position (3D co-ordinates)
X= 0.0, Y = 0.0, Z = 0.0
Initial value of velocity (on the 3 axes)
Vx= 0.0, Vy = 0.0, Vz = 0.0
Design consists of two tasks:
#Data Acquisition and Processing (DAP)
    Updates X, Y, Z, Vx, Vy and Vz every 1 second
#Data Display
    Displays X, Y, Z, Vx, Vy and Vz every 5 seconds

Get accelerometer data
----------------------
Simulated here with three assignment statements
can also be obtained from an array
  Ax = −2.0
  Ay = 4.0
  Az = 10.5

Update velocity and position
----------------------------
Vx = Vx + Ax * T
Vy = Vy + Ay * T
Vz = Vz + (Az − g) * T
X = X + Vx * T
Y = Y + Vy * T
Z = Z + Vz * T

Here T=2.0 sec is the sampling period and g=9.8 m/sec2 is gravity. 
Initially, X=0.0, Y=0.0, Z=0.0, Vx=0.0, Vy=0.0 and Vz=0.0.
<b>All of the above variables are double (Double precision floating–point). </b>
The Data Display thread shows velocity and position data on screen.
Use a mutex to ensure that the threads do not gain access to the position and velocity variables simultaneously. 

Requirement 1
-------------
You must follow object–oriented programming methodology
  i.e.For instance, you should create classes for threads and timers.
