#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     irSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     touch,          sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     liftLeftBottom, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     liftLeftTop,   tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     frontLeft,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     backLeft,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     frontRight,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     backRight,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     liftRightTop,  tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     liftRightBottom, tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S2_C1_1,    latchRight,           tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    latchLeft,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    intakeLeft,           tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C1_4,    intakeRight,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/* February 7th, 2015
 * Chris: I put the code onto GitHub a few days ago (well, yesterday, 2/6) and now imported it
 * onto Eclipse! I'm still getting use to the whole integration thing, but I think this will
 * help with format and doing it at home (where I don't have the robotics netbook).
 *
 * SO... this 3rd autonomous is supposed to be amazing (relative terms)! We plan on having
 * different sections of code to run based on what we want to do that specific round (E.g.
 * getting the 30cm goal instead, or going for the center goal. Rough draft)
 * Parts from our last autonomous (v2) will likely borrowed, such as the PID
 */

#define BOUND(num, low, high) (num < low) ? low : ((num > high) ? high : num)   //We don't want to set the motors higher than -100 or 100, so limit it!
const float ENCODER_TICKS_PER_INCH = 152.788745368;	//[1440 / wheel circumference (in inches)]
const int perfect90 = 1980; // [16.5 inches * pi (circle that a point turn makes) / 4 (90 degrees is 360 degrees divided by 4)] * ENCODER_TICKS_PER_INCH

const float kp = 1.0;	//Proportional constant for driving straight
const float ki = .01;	//Integral constant for driving straight
const float kd = .5;	//Derivative constant for driving straight
const float kpd = 1;	//Proportional constant for driving a certain distance (slowing down as approaching)
short controllable = 1000;	//Only use PID if the error is within the controllable range
short lastError = 0;
short error = 0;	//error is difference between the two motors
short distError = 0;	//distError is the (set point - average of encoders)
short integral = 0;	//Sum of all past errors
short derivative = 0;	//Rate of change ("slope"/"prediction")
short speed = 0;

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "lib/prematch.h"	//The methods for deciding the routine before the match
#include "lib/functions.h"	//General functions (forward/turn/etc)

task main()
{
	//Choose stuff. Displays selection stuff on NXT. Functions used are in "lib/prematch.h"
	int strategy = chooseStrategy();	//1=nothing, 2=points, 3=defend[start on parking zone]
	int start = chooseStart();	//1=platform, 2=parking zone
	int goals = chooseGoals();	//1=60cm, 2=30cm, 3=both, 4=none
	int delay = chooseDelay();	//1=0sec, 2=1sec, 3=4sec, 4=9sec, 5=16sec
}