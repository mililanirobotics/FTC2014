#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     irSensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     uSonic,         sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     right,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     left,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     rack,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     pulley,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorH,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_2,    rHook,                tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    lHook,                tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
// Things that might be performed during initialization include:
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving. For example, gyro sensor needs a few seconds to obtain the background
//      "bias" value.
//
// In many cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.
	//servo[goalHook] = 0;

  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the autonomous robot operation. Customize as appropriate for
// your specific robot.
//
// The types of things you might do during the autonomous phase (for the 2008-9 FTC competition)
// are:
//
//   1. Have the robot follow a line on the game field until it reaches one of the puck storage
//      areas.
//   2. Load pucks into the robot from the storage bin.
//   3. Stop the robot and wait for autonomous phase to end.
//
// This simple template does nothing except play a periodic tone every few seconds.
//
// At the end of the autonomous period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
void open()
{
	servo[rHook] = 180;
  servo[lHook] = 120;
}
void close()
{
	servo[rHook] = 8;
  servo[lHook] = 8;
}
void closeMore()
{
		servo[rHook] = 200;
		servo[lHook] = 0;
}
void stopDrive(int wait)
{
	motor[right] = 0;
	motor[left] = 0;
	wait10Msec(wait);
}
void driveForward(int wait)
{
	motor[left] = 100;
  	motor[right] = 100;
  	wait10Msec(wait);
  	stopDrive(5);
}
void driveBackwardSlow(int wait)
{
	motor[left] = -50;
  	motor[right] = -50;
  	wait10Msec(wait);
 	stopDrive(5);
}
void driveBackward(int wait)
{
	motor[left] = -100;
  	motor[right] = -100;
  	wait10Msec(wait);
 	stopDrive(5);
}
void turnLeftFast(int wait)
{
	motor[left] = 100;
	motor[right] = -100;
	wait10Msec(wait);
	stopDrive(5);
}
void turnRightFast(int wait)
{
	motor[right] = 100;
	motor[left] = -100;
	wait10Msec(wait);
	stopDrive(5);
}
void shiRight(int i)
{
	for(int j = 0; j < i; j++)
	{
		turnRightFast(10);
		stopDrive(3);
		driveForward(8);
		stopDrive(3);
	}
}
void shiLeft(int i)
{
	for(int j = 0; j < i; j++)
	{
		turnLeftFast(15);
		stopDrive(3);
		driveBackward(8);
		stopDrive(3);
	}
}
void starting()
{
	motor[rack] = -50;
	wait10Msec(120);
	motor[rack] = 0;
	wait10Msec(10);
	driveForward(185);
	stopDrive(20);
  //shimmee into the "sweet spot"
  turnRightFast(53);
	stopDrive(15);
  //shiLeft(6);
  driveBackward(90);
  wait10Msec(70);
}
task main()
{
	initializeRobot();
	waitForStart(); // Wait for the beginning of autonomous phase.
  	//Robot goes down ramp , just past the tape
  starting();
  close();
  int dist = SensorValue[uSonic];
	int dir = SensorValue[irSensor];
	if(dir >= 6) //stick is at position 2
	{
		while(dist > 60)
		{
			turnRightFast(10);
			wait10Msec(3);
			dist = SensorValue[uSonic];
		}
		turnLeftFast(10);
		driveBackwardSlow(90);
	}
	else if(dist <= 40 || dir == 5) //stick is at position 1
	{
		while(dist < 28)
		{
			driveForward(10);
			dist = SensorValue[uSonic];
		}
		turnLeftFast(32);
  		driveBackward(60);
  		dist = SensorValue[uSonic];
		while(dist > 100)
		{
			turnRightFast(10);
			dist = SensorValue[uSonic];
		}
		//turnLeftFast(15);
		driveForward(30);
		wait10Msec(50);
		driveBackward(120);
	}
	else if(dist > 40) //stick is at position 3
	{
		turnLeftFast(25);
		driveBackward(70);
		turnRightFast(75);
		driveBackward(90);
	}
}