#include "DriveBase.h"
#include "../RobotMap.h"
#include "../Commands/Drivebase/MecanumDrive.h"
#include <cmath>

DriveBae::DriveBae() :
		Subsystem("DriveBae") {
	SAFE_INIT(DRIVE_MOTOR_FRONT_LEFT,
			motorFrontLeft = new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_FRONT_LEFT););
	SAFE_INIT(DRIVE_MOTOR_FRONT_RIGHT,
			motorFrontRight = new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_FRONT_RIGHT););
	SAFE_INIT(DRIVE_MOTOR_BACK_LEFT,
			motorBackLeft = new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_BACK_LEFT););
	SAFE_INIT(DRIVE_MOTOR_BACK_RIGHT,
			motorBackRight = new DRIVE_MOTOR_TYPE(DRIVE_MOTOR_BACK_RIGHT););
	motorFrontLeft->ConfigEncoderCodesPerRev(ENCODER_TICKS_PER_REV);
	motorFrontRight->ConfigEncoderCodesPerRev(ENCODER_TICKS_PER_REV);
	motorBackLeft->ConfigEncoderCodesPerRev(ENCODER_TICKS_PER_REV);
	motorBackRight->ConfigEncoderCodesPerRev(ENCODER_TICKS_PER_REV);
	setModeAll(CANSpeedController::kPosition);

	// Initialize gyro stuff
	serialPort = new SerialPort(57600, SerialPort::kMXP);
	uint8_t update_rate_hz = 50; // ayy lmao
	gyro = new IMU(serialPort, update_rate_hz);
	gyroEnabled = gyro != NULL;

	rotPID = new PIDController(DRIVE_ROT_P, DRIVE_ROT_I, DRIVE_ROT_D, gyro,
			this);

	rotPID->SetOutputRange(-180.0, 180.0);
	rotPID->SetInputRange(-180.0, 180.0);
	rotPID->SetContinuous(true);
	rotPID->SetSetpoint(0.0);

	forward = 0.0;
	right = 0.0;
	clockwise = 0.0;
}

DriveBae::~DriveBae() {
	delete motorFrontLeft;
	delete motorFrontRight;
	delete motorBackLeft;
	delete motorBackRight;
	delete rotPID;
	delete serialPort;
	delete gyro;
}

void DriveBae::InitDefaultCommand() {
	SetDefaultCommand(new MecanumDrive);
}

void DriveBae::setSpeed(double speedFrontLeft, double speedFrontRight,
		double speedBackLeft, double speedBackRight) {
	// Normalize to the max
	double max = fabs(speedFrontLeft);
	if (fabs(speedFrontRight) > max) {
		max = fabs(speedFrontRight);
	}
	if (fabs(speedBackLeft) > max) {
		max = fabs(speedBackLeft);
	}
	if (fabs(speedBackRight) > max) {
		max = fabs(speedBackRight);
	}

	if (max >= 1) {
		speedFrontLeft /= max;
		speedFrontRight /= max;
		speedBackLeft /= max;
		speedBackRight /= max;
	}

	motorFrontLeft->Set(-speedFrontLeft);
	motorFrontRight->Set(speedFrontRight);
	motorBackLeft->Set(-speedBackLeft);
	motorBackRight->Set(speedBackRight);
}

IMU *DriveBae::getGyro() {
	return gyro;
}

void DriveBae::setGyroEnabled(bool enable) {
	gyroEnabled = enable;
}

bool DriveBae::isGyroEnabled() {
	return gyroEnabled;
}

void DriveBae::setPIDAll(double P, double I, double D) {
	motorFrontLeft->SetPID(P, I, D);
	motorFrontRight->SetPID(P, I, D);
	motorBackLeft->SetPID(P, I, D);
	motorBackRight->SetPID(P, I, D);
}

void DriveBae::setAll(double setPoint) {
	motorFrontLeft->Set(setPoint);
	motorFrontRight->Set(setPoint);
	motorBackLeft->Set(setPoint);
	motorBackRight->Set(setPoint);
}

void DriveBae::setModeAll(CANSpeedController::ControlMode mode) {
	motorFrontLeft->SetControlMode(mode);
	motorFrontRight->SetControlMode(mode);
	motorBackLeft->SetControlMode(mode);
	motorBackRight->SetControlMode(mode);
}

void DriveBae::zeroEncoders() {
	motorFrontLeft->SetPosition(0);
	motorFrontRight->SetPosition(0);
	motorBackLeft->SetPosition(0);
	motorBackRight->SetPosition(0);
}

bool DriveBae::withinThreshhold(double driveThreshhold, double targetDistance,
		EncoderZero* billy) {
	SmartDashboard::PutNumber("EncoderTest", motorBackLeft->GetEncPosition());
	if ((motorBackLeft->GetEncPosition() - billy->backLeft) - targetDistance
			< driveThreshhold
			|| (motorFrontLeft->GetEncPosition() - billy->frontLeft)
					- targetDistance < driveThreshhold
			|| (motorFrontRight->GetEncPosition() - billy->backRight)
					- targetDistance < driveThreshhold
			|| (motorBackRight->GetEncPosition() - billy->frontRight)
					- targetDistance < driveThreshhold) {
		return true;
	}
	return false;
}

DriveBae::EncoderZero* DriveBae::getZero() {
	EncoderZero* foo = new DriveBae::EncoderZero();
	foo->backLeft = motorBackLeft->GetEncPosition();
	foo->backRight = motorBackRight->GetEncPosition();
	foo->frontLeft = motorFrontLeft->GetEncPosition();
	foo->frontRight = motorFrontRight->GetEncPosition();
	return foo;
}

void DriveBae::enablePIDAll(bool state) {
	if (state) {
		motorFrontLeft->EnableControl();
		motorFrontRight->EnableControl();
		motorBackLeft->EnableControl();
		motorBackRight->EnableControl();
	} else {
		motorFrontLeft->Disable();
		motorFrontRight->Disable();
		motorBackLeft->Disable();
		motorBackRight->Disable();
	}
}

void DriveBae::setTargetAngle(double theta) {
	rotPID->SetSetpoint(theta);
}

void DriveBae::stopPID() {
	rotPID->Disable();
}

void DriveBae::startPID() {
	rotPID->Enable();
}

double DriveBae::getError() {
	return (gyro->GetYaw() - rotPID->GetSetpoint());
}

void DriveBae::setForward(double f) {
	forward = f;
}

void DriveBae::setRight(double r) {
	right = r;
}

void DriveBae::setClockwise(double c) {
	clockwise = c;
}

double DriveBae::getClockwise() {
	return clockwise;
}

void DriveBae::execute() {
// 'Kinematic transformation'
	double frontLeft = forward + clockwise - right;
	double frontRight = forward - clockwise + right;
	double backLeft = forward + clockwise + right;
	double backRight = forward - clockwise - right;

	setSpeed(frontLeft, frontRight, backLeft, backRight);
}
void DriveBae::PIDWrite(float output) {
	output /= 180.0;
	SmartDashboard::PutNumber("PID output", output);
	setClockwise(-output);
}

double DriveBae::PIDGet() {
	return gyro->GetYaw();
}

double DriveBae::getSetpoint() {
	return rotPID->GetSetpoint();
}

void DriveBae::setSetpoint(float f) {
	rotPID->SetSetpoint(f);
}

DRIVE_MOTOR_TYPE *DriveBae::getMotor(MotorSide side) {
	switch (side) {
	case MotorSide::FRONT_LEFT:
		return motorFrontLeft;
	case MotorSide::FRONT_RIGHT:
		return motorFrontRight;
	case MotorSide::BACK_LEFT:
		return motorBackLeft;
	case MotorSide::BACK_RIGHT:
		return motorBackRight;
	}
}
