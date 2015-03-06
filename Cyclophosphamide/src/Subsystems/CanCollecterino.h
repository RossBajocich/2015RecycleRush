#ifndef COLLECTERINO_ARMS_H
#define COLLECTERINO_ARMS_H

#include "WPILib.h"
#include "RobotMap.h"

/**
 * Motor arms raise up/down
 * Arm PID controls the arms up and down.
 * can sensor
 * Pneumatics (double solenoid)  wrist open and close to collect the recycle can.
 */

class CanCollecterino: public Subsystem
{
private:
	CAN_MOTOR_TYPE *liftMotorLeft;
	CAN_MOTOR_TYPE *liftMotorRight;
	DoubleSolenoid *wrists;

	AnalogInput *liftPot;
	PIDController *armPID;

	DigitalInput *canSensor;

	float setpoint;
	bool toggleArms;
	bool toggleWrist;
public:
	CanCollecterino();
	~CanCollecterino();
	void InitDefaultCommand();

	void setWrist(DoubleSolenoid::Value value);
	void setArms(float value);

	void disableArms();
	bool armsWithinBounds();
	void brakeArms(bool brake);

	AnalogInput *getLiftPot();

	PIDController *getArmPID();

	bool getToggleArms();
	void doTheToggleArms();

	bool getWristToggle();
	void doTheToggleWrist();
	void getDatStatus();
};

#endif
