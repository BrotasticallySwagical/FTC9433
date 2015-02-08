#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     irSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     touch,          sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     liftLeftBottom, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     liftLeftTop,   tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     frontLeft,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     backLeft,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     frontRight,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     backRight,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     liftRightTop,  tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     liftRightBottom, tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S2_C1_1,    latchRight,           tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    latchLeft,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    intakeLeft,           tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C1_6,    intakeRight,          tServoContinuousRotation)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/* December 19th, 2014 (Friday no-school!)
 Just added lift and the joystick-if-statement
 
 Janurary 5th, 2014
 Changed driver thing to (maybe) be better. I think it's just more aesthetically pleasing
 
 Janurary 6th, 2014
 They finally got the robot (kind of) done (not really)! Added buttons for the servos that latch onto the rolling goal,
 and we were able to go backards onto the ramp! Hurray~
 Oh... and I realized I didn't do progress 2, 3, 4.... idk how many... so this will just be progress 2!
 
 Janurary 8th, 2014
 Still working on the robot QQ. Changing intake from nxt motors to continuous servos... lift keeps unchaining... no LEDs
 yet... so much to fix and what-nots, but we have to move on! I didn't really change anything except the in/outtake because
 the intake thing changed
 */

#include "JoystickDriver.c"
#define BOUND(input, min, max) input > max ? max : (input < min ? min : input)
//Bound: takes the input and either returns max (if input is greater than max), min (if input is less than min), or input (if it fits in the range)
void intake() {
	servo[intakeLeft] = 0;
	servo[intakeRight] = 255;
}
void output() {
	servo[intakeLeft] = 127 + 100;
	servo[intakeRight] = 127 - 100;
}

int threshold = 10;
int joyy1;
int joyx2;
int mode = 1;

task main() {
	StopTask(displayDiagnostics);
	while (true) {
		getJoystickSettings(joystick);

		if (abs(joystick.joy1_y1) > threshold) {
			joyy1 = BOUND(joystick.joy1_y1, -100, 100);
			//joyy1 = joystick.joy1_y1; //We probably don't have to limit the joystick value because we're limiting it when we set the motors
		} else {
			joyy1 = 0;
		}
		if (abs(joystick.joy1_x2) > threshold) {
			joyx2 = BOUND(joystick.joy1_x2, -100, 100);
			//joyx2 = joystick.joy1_x2;
		} else {
			joyx2 = 0;
		}

		motor[frontLeft] = BOUND(joyy1 + joyx2, -100, 100);
		motor[frontRight] = BOUND(joyy1 - joyx2, -100, 100);
		motor[backLeft] = BOUND(joyy1 + joyx2, -100, 100);
		motor[backRight] = BOUND(joyy1 - joyx2, -100, 100);

		if (joy1Btn(1) == 1) {
			output();
		} else {
			intake();
		}

		if (joy1Btn(4) == 1) {
			if (mode == 1) {
				mode = 4;
			} else {
				mode = 1;
			}
			wait1Msec(250);
		}

		if (joy2Btn(6) == 1) {
			motor[liftLeftTop] = 30;
			motor[liftLeftBottom] = 60;
			motor[liftRightTop] = 30;
			motor[liftRightBottom] = 60;
		} else if (joy2Btn(8) == 1) {
			motor[liftLeftTop] = -30;
			motor[liftLeftBottom] = -30;
			motor[liftRightTop] = -60;
			motor[liftRightBottom] = -60;
		} else {
			motor[liftLeftTop] = 0;
			motor[liftLeftBottom] = 0;
			motor[liftRightTop] = 0;
			motor[liftRightBottom] = 0;
		}

		if (joy2Btn(5) == 1 && servo[latchLeft] < 255) {
			servo[latchRight] = servo[latchRight] - 10;
			servo[latchLeft] = servo[latchLeft] + 10;
			nxtDisplayString(1, "RServo: %3d", servo[latchRight]);
			nxtDisplayString(2, "LServo: %3d", servo[latchLeft]);
			wait1Msec(25);
		}
		if (joy2Btn(7) == 1 && servo[latchRight] < 255) {
			servo[latchRight] = servo[latchRight] + 10;
			servo[latchLeft] = servo[latchLeft] - 10;
			nxtDisplayString(1, "RServo: %3d", servo[latchRight]);
			nxtDisplayString(2, "LServo: %3d", servo[latchLeft]);
			wait1Msec(25);
		}
	}
}
