#include "../RobotMap.h"
#include <Math.h>
#include <Subsystems/ArmLifter.h>
#include "../utilities/StallableMotor.h"

ArmLifter::ArmLifter() :
		Subsystem("CanCollecterino") {
	SAFE_INIT(CAN_MOTOR_LIFT_LEFT_PORT,
			liftMotorLeft = new CAN_MOTOR_TYPE(CAN_MOTOR_LIFT_LEFT_PORT););
	SAFE_INIT(CAN_MOTOR_LIFT_RIGHT_PORT,
			liftMotorRight = new CAN_MOTOR_TYPE(CAN_MOTOR_LIFT_RIGHT_PORT););

	SAFE_INIT(CAN_LIFT_POT_PORT, liftPot = new AnalogInput(CAN_LIFT_POT_PORT););
	stallable = new StallableMotor(liftPot, 420, 20, liftMotorRight,
			liftMotorLeft);
	armPID = new PIDController(CAN_ARM_P, CAN_ARM_I, CAN_ARM_D, liftPot,
			stallable);

	armPID->SetOutputRange(-.7, .7);
	armPID->SetInputRange(CAN_POT_DOWN_POSITION, CAN_POT_UP_POSITION);
	armPID->SetPercentTolerance(5);

	toggleArms = true;
}

ArmLifter::~ArmLifter() {
	delete liftMotorLeft;
	delete liftMotorRight;
	delete armPID;
}

void ArmLifter::InitDefaultCommand() {

}

StallableMotor *ArmLifter::getStallable(){
	return stallable;
}

void ArmLifter::setArms(float value) {
	armPID->SetSetpoint(value);
	armPID->Enable();
}

AnalogInput *ArmLifter::getLiftPot() {
	return liftPot;
}

void ArmLifter::disableArms() {
	armPID->Disable();
}

bool ArmLifter::armsWithinBounds() {
	return armPID->OnTarget();
}

PIDController *ArmLifter::getArmPID() {
	return armPID;
}

void ArmLifter::doTheToggleArms() {
	if (toggleArms) {
		toggleArms = false;
	} else {
		toggleArms = true;
	}
}

bool ArmLifter::getToggleArms() {
	return toggleArms;
}

AnalogInput *ArmLifter::getPot() {
	return liftPot;
}

void ArmLifter::getDatStatus() {

}

double ArmLifter::getSetpoint() {
	return armPID->GetSetpoint();
}
