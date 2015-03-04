#include <Commands/CanCollecterino/CanToCraaawTransfer.h>
#include <Commands/ToteLifting/LiftRelative.h>
#include "RobotMap.h"
#include "Arms/MoveWrist.h"
#include "Arms/MoveArms.h"
#include "Craaaw/CraaawActuate.h"

CanToCraaawTransfer::CanToCraaawTransfer() {
	AddSequential(new CraaawActuate(DoubleSolenoid::kForward));
	AddParallel(new MoveWrist(MoveWrist::open));
	AddSequential(new LiftRelative(BOUNCE_HEIGHT));
	AddSequential(new LiftRelative(-BOUNCE_HEIGHT));
}