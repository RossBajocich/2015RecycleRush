#include "MecanumDrive.h"
#include "ResetGyro.h"
#include <math.h>

MecanumDrive::MecanumDrive() :
		CommandBase("MecanumDrive") {
	Requires(driveBase);
}

void MecanumDrive::Initialize() {
	driveBase->setSpeed(0.0, 0.0, 0.0, 0.0);
}

void MecanumDrive::Execute() {
	double forward;
	double right;
	double clockwise;

#if ONE_STICK
		forward = -oi->getJoystickLeft()->GetAxis(Joystick::kYAxis);
		right = oi->getJoystickLeft()->GetAxis(Joystick::kXAxis);
		clockwise = oi->getJoystickLeft()->GetAxis(Joystick::kZAxis);
#else
		forward = -oi->getJoystickLeft()->GetAxis(Joystick::kYAxis);
		right = oi->getJoystickLeft()->GetAxis(Joystick::kXAxis);
		clockwise = oi->getJoystickRight()->GetAxis(Joystick::kZAxis);
#endif

	if (fabs(forward) < OI_JOYSTICK_DRIVE_DEADBAND) {
		forward = 0;
	}
	if (fabs(right) < OI_JOYSTICK_DRIVE_DEADBAND) {
		right = 0;
	}
	if (fabs(clockwise) < OI_JOYSTICK_ROT_DEADBAND) {
		clockwise = 0;
	} else {
		double sign = clockwise > 0 ? 1.0 : -1.0;
		clockwise -= OI_JOYSTICK_ROT_DEADBAND*sign;
	}

	clockwise = pow(clockwise, 3.0);
	clockwise *= JOYSTICK_DEGREES_PER_TICK;

	forward = pow(forward, 3.0);
	right = pow(right, 3.0);

	if(driveBase->getClockwise() < 0.9) {
		double targetAngle = driveBase->GetSetpoint() + clockwise;
		if(targetAngle > 180.0 ) {
			targetAngle += 180.0;
			targetAngle = fmod(targetAngle, 360.0);
			targetAngle -= 180.0;
		} else if (targetAngle < -180.0) {
			targetAngle -= 180.0;
			targetAngle = fmod(targetAngle, 360.0);
			targetAngle += 180.0;
		}

		driveBase->SetSetpoint(targetAngle);
	}

	SmartDashboard::PutNumber("PID setpoint", driveBase->GetSetpoint());

#if FIELD_ORIENTED
	// Field-oriented corrections
	double theta = driveBase->getGyro()->GetYaw();
	SmartDashboard::PutNumber("Gyro Angle", theta);
	theta *= M_PI / 180.0;
	double temp = forward*cos(theta) + right*sin(theta);
	right = -forward*sin(theta) + right*cos(theta);
	forward = temp;
#endif

	/*
	 * Correct for driving faster than driving left/right due to the
	 * shape of the drivebase
	 */
	forward *= DRIVE_ASPECT_RATIO;

	driveBase->setForward(-forward);
	driveBase->setRight(right);
	driveBase->execute();

	SmartDashboard::PutNumber("PID error", driveBase->getError());
}

bool MecanumDrive::IsFinished() {
	return false;
}

void MecanumDrive::End() {
	driveBase->setSpeed(0.0, 0.0, 0.0, 0.0);
}

void MecanumDrive::Interrupted() {
	driveBase->setSpeed(0.0, 0.0, 0.0, 0.0);
}