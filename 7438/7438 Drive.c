	#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     right,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     left,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     rack,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     pulley,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     basket,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_2,    hook,                 tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    hook2,                tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    gate,                 tServoStandard)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c" //Joystick is included in this program

task main()
{
  int threshold = 15; //to avoid unnecessary movement

  while(true) //infinite loop
  {
    getJoystickSettings(joystick); //retrieves data from the joystick
    if(abs(joystick.joy1_y1) > threshold || abs(joystick.joy1_x2) > threshold)
    {
    	motor[left] = 1 * joystick.joy1_y1;
    	motor[right] = 1 * joystick.joy1_y1;
    	if(abs(joystick.joy1_x2) > threshold)
    	{
    		motor[left] = -joystick.joy1_x2;
				motor[right] = joystick.joy1_x2;
			}
    }
    else
    {
    	motor[left] = 0;
    	motor[right] = 0;
    }
    //Upper Right Trigger makes the slide go up
    if(joy1Btn(6))
    {
    	motor[rack] = -50;
    }

    //Lower Right Trigger makes the slide go down
    else if(joy1Btn(8))
  	{
			motor[rack] = 50;
		}
		else
		{
			motor[rack] = 0;
		}
		//A is spit out (for basket)
		if(joy1Btn(3))
		{
			motor[basket] = 75;
		}
		//B is go in (for basket)
		else if(joy1Btn(2))
		{
			motor[basket] = -75;
		}
		else
		{
			motor[basket] = 0;
		}
		if(joy1Btn(1)) // press X to close basket bottom /* TEST PENDING
		{
			servo[gate] = 16;
		}
		if(joy1Btn(4)) // press Y to open basket bottom /* TEST PENDING
		{
			servo[gate] = 122;
		}
		wait10Msec(3);
  }
}
