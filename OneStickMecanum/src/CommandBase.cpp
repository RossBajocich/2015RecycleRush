#include "CommandBase.h"
#include "Subsystems/DriveBase.h"
#include "Commands/Scheduler.h"

// Initialize a single static instance of all of your subsystems to NULL
DriveBae* CommandBase::driveBase = NULL;
OI* CommandBase::oi = NULL;
StackPusher* CommandBase::stackPusher = NULL;
Pneumatics* CommandBase::pneumatics = NULL;

CommandBase::CommandBase(char const *name) :
		Command(name)
{
}

CommandBase::CommandBase() :
		Command()
{

}

CommandBase::~CommandBase() {
	delete driveBase;
	delete oi;
	delete stackPusher;
	delete pneumatics;
}

void CommandBase::init()
{
	driveBase = new DriveBae();
	oi = new OI();
	stackPusher = new StackPusher();
	pneumatics = new Pneumatics();
}
