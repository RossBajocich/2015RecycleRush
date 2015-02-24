/*
 * ProtoRobot.cpp
 *
 *  Created on: Jan 11, 2015
 *      Author: Administrator
 */

#include <Commands/Automatic/TimedDrive.h>
#include <Commands/Drivebase/ZeroGyro.h>
#include <Commands/CanCollecterino/MoveArmsAndCollect.h>
#include <Commands/ToteHandling/ToteIntake.h>
#include <Commands/ToteHandling/DownUp.h>
#include <OmegaSupreme.h>
#include "WPILib.h"
#include "Commands/Command.h"

#include "Commands/Autonomous/Scripting.h"

#include "CommandBase.h"
#include "RobotMap.h"
#include <stdio.h>

#include "Commands/Autonomous/Autonomous.h"

OmegaSupreme::OmegaSupreme() {
	PIDChange = 0;
	lw = NULL;
	chooser = NULL;
	autonomousCommand = NULL;
}

OmegaSupreme::~OmegaSupreme() {
	delete autonomousCommand;
	delete chooser;
}

void OmegaSupreme::RobotInit() {
	CommandBase::init();
	lw = LiveWindow::GetInstance();

	input1 = new DigitalInput(1);
	input2 = new DigitalInput(2);

	// Create autonomous
	chooser = new SendableChooser();
	chooser->AddDefault("CRAAAAAZY AUTO", Autonomous::createStartWithCan());
	chooser->AddObject("Blank", new Autonomous());
	chooser->AddObject("Drive forward 24 inches",
			Autonomous::createDriveDistance(24, BestDrive::forward));
	chooser->AddObject("Drive forward 1 second",
			Autonomous::createDriveDuration(1.0f, -90.0f));
	chooser->AddObject("Turn 90 degrees", Autonomous::createTurnTo(90.0));
	SmartDashboard::PutData("Auto Modes", chooser);

	//chooser = Scripting::generateAutonomousModes(AUTO_SCRIPT_LOCATIONS);

	CommandBase::oi->registerButtonListeners();

	if (CommandBase::driveBae != NULL) {
		SmartDashboard::PutData("Zero yaw", new ZeroGyro);
		bool zeroed = false;
		double initialTime = GetFPGATime();
		while (!zeroed) {
			bool isCalibrating =
					CommandBase::driveBae->getGyro()->IsCalibrating();
			if (!isCalibrating /*|| GetFPGATime() - initialTime > GYRO_TIMEOUT*/) {
				Wait(0.2);
				CommandBase::driveBae->getGyro()->ZeroYaw();
				//CommandBase::driveBae->startRotPID(); // enable the pid. May want to move this
				zeroed = true;
			}
		}
	}
}

void OmegaSupreme::AutonomousInit() {
	Scheduler::GetInstance()->RemoveAll();
	//((ScriptRunner*) chooser->GetSelected())->startCommand();

	//autonomousCommand = (Command *) chooser->GetSelected();
	autonomousCommand = new BestDrive(24, BestDrive::Direction::forward);
	autonomousCommand->Start();
	/*
	 float startingOffset = SmartDashboard::GetNumber("Auto angle offset", 0.0);
	 CommandBase::driveBae->getGyro()->SetYawPitchRoll(startingOffset, 0.0f,
	 0.0f, 0.0f);
	 */
	SmartDashboard::PutNumber("driveEncoder",
			CommandBase::driveBae->getMotor(DriveBae::MotorSide::FRONT_LEFT)->GetEncPosition());
}

void OmegaSupreme::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
	SmartDashboard::PutNumber("driveEncoder",
			CommandBase::driveBae->getMotor(DriveBae::MotorSide::FRONT_LEFT)->GetEncPosition());
	WatchDogg();
}

void OmegaSupreme::TeleopInit() {
	if (autonomousCommand != NULL) {
		autonomousCommand->Cancel();
	}
	Scheduler::GetInstance()->RemoveAll();
	CommandBase::driveBae->getGyro()->ZeroYaw();
	SmartDashboard::PutData(CommandBase::craaaw);
	SmartDashboard::PutData("Can up", new MoveArmsAndCollect(true));
	SmartDashboard::PutData("Can down", new MoveArmsAndCollect(false));
	SmartDashboard::PutData("Tote intake", new ToteIntake(ToteIntake::forward));
	SmartDashboard::PutData("Get next tote", new DownUp(DownUp::load));
	SmartDashboard::PutData("Get last tote", new DownUp(DownUp::carry));
}

void OmegaSupreme::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();

	SmartDashboard::PutNumber("motorLEFTCurrentOMG",
			CommandBase::toteLifterino->getLeftMotor()->GetOutputCurrent());
	SmartDashboard::PutNumber("motorRIGHTCurrentOMG",
			CommandBase::toteLifterino->getRightMotor()->GetOutputCurrent());

	SmartDashboard::PutNumber("intake",
			CommandBase::toteIntakerino->getEncoder()->Get());
	SmartDashboard::PutBoolean("has tote",
			CommandBase::toteIntakerino->isLoaded());

	SmartDashboard::PutNumber("armPot",
			CommandBase::canCollecterino->getLiftPot()->PIDGet());


	SmartDashboard::PutBoolean("Digital input1", input1->Get());
	SmartDashboard::PutBoolean("Digital input2", input2->Get());

	SmartDashboard::PutNumber("Can arm pot",
			CommandBase::canCollecterino->getLiftPot()->GetValue());



	SmartDashboard::PutNumber("elevatorEnc",
			CommandBase::toteLifterino->getEncoder()->Get());
	SmartDashboard::PutBoolean("Coop mode",
			CommandBase::toteLifterino->isCoop());

	SmartDashboard::PutNumber("lifter pos",
			CommandBase::toteLifterino->getPosition());

	SmartDashboard::PutNumber("Gyro Angle", CommandBase::driveBae->getGyro()->GetYaw());
	WatchDogg();
}

void OmegaSupreme::DisabledInit() {
	Scheduler::GetInstance()->RemoveAll();
}

void OmegaSupreme::TestInit() {
	Scheduler::GetInstance()->RemoveAll();
}

void OmegaSupreme::TestPeriodic() {
	lw->Run();
}

void OmegaSupreme::WatchDogg() {
// there are now doggs to watch
// lmao XDDD
	/*if (CommandBase::stackPusher->getValue()
	 == DoubleSolenoid::kForward&& CommandBase::canCollecterino->getArmPID()->GetSetpoint() == CAN_POT_UP_POSITION) {
	 CommandBase::canCollecterino->disableArms();
	 }
	 if (CommandBase::toteIntakerino->isLoaded()
	 && (CommandBase::toteLifterino->getPID()->GetSetpoint()
	 < TOTE_LIFTER_STACK_HEIGHT
	 && CommandBase::toteLifterino->getEncoder()->Get()
	 >= TOTE_LIFTER_STACK_HEIGHT - 100)) {
	 CommandBase::toteLifterino->enablePID(false);
	 } else if (CommandBase::toteIntakerino->isLoaded()
	 && (CommandBase::toteLifterino->getPID()->GetSetpoint()
	 < TOTE_LIFTER_STACK_HEIGHT)) {
	 CommandBase::toteLifterino->setSetPoints(TOTE_LIFTER_STACK_HEIGHT);
	 }*/
}

START_ROBOT_CLASS(OmegaSupreme);
