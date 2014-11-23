#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     right,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     left,          tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C1_1,     barre,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     motorG,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c" //Joystick is included in this program

task main()
{
	getJoystickSettings(joystick);
  while(true)
  {
  	int threshold = 20; //to avoid unnecessary movement
  	if(abs(joystick.joy1_y1) > threshold || abs(joystick.joy1_y2) > threshold)
    {
      motor[left] = joystick.joy1_y1;
      motor[right] = joystick.joy1_y2;
    }
    /* Right joystick
    else if(abs(joystick.joy1_y2) > threshold)
    {
      motor[right] = joystick.joy1_y2;
    }
    */
    else
    {
      motor[left] = 0;
      motor[right] = 0;
    }
  	if(joy1Btn(1))
    {
    	motor[barre] = 75;
    }
    if(joy1Btn(2))
  	{
    	motor[barre] = -75;
  	}
  	if(joy1Btn(4))
  	{
    	motor[barre] = 0;
  	}
  }
}
