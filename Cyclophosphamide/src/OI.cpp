#include <Buttons/JoystickButton.h>
#include <Commands/Automatic/TurnToThenDrive.h>
#include <Commands/CanCollecterino/Arms/Induct.h>
#include <Commands/CanCollecterino/Arms/MoveArms.h>
#include <Commands/CanCollecterino/Arms/MoveWrist.h>
#include <Commands/CanCollecterino/Arms/Whack.h>
#include <Commands/CanCollecterino/CanToCraaawTransfer.h>
#include <Commands/CanCollecterino/Craaaw/CraaawActuate.h>
#include <Commands/CanCollecterino/MoveArmsFancy.h>
#include <Commands/Score.h>
#include <Commands/ToteHandling/DownUp.h>
#include <Commands/ToteHandling/LiftToHeightVelocity.h>
#include <Commands/ToteHandling/ResetElevatorEncoder.h>
#include <Commands/ToteHandling/SafeDownUp.h>
#include <Commands/ToteHandling/SafeLiftToHeight.h>
#include <Commands/ToteHandling/ToteIntake.h>
#include <Commands/CanCollecterino/Collect.h>
#include <DoubleSolenoid.h>
#include <Joystick.h>
#include <OI.h>

#define SAFE_BUTTON(name, cmd) {if (name!=NULL){cmd;}}

OI::OI() {
	joystickLeft = new Joystick(0);
	joystickRight = new Joystick(1);
	joystickOperator = new Joystick(2);

	alignTote = new JoystickButton(joystickOperator, 14);
	getNext = new JoystickButton(joystickOperator, 13);
	getLast = new JoystickButton(joystickOperator, 12);
	toteLifterFloor = new JoystickButton(joystickRight, 4);
	toteLifterCarry = new JoystickButton(joystickOperator, 11);
	toteLifterTwoTotes = new JoystickButton(joystickOperator, 8);
	toteLifterOneTote = new JoystickButton(joystickOperator, 10);

	toteLifterUp = new JoystickButton(joystickLeft, 4);
	toteLifterDown = new JoystickButton(joystickLeft, 5);

	pushSwitch = new JoystickButton(joystickOperator, 7);
	wrist = new JoystickButton(joystickOperator, 2);
	canCollector = new JoystickButton(joystickOperator, 1);
	//collect = new JoystickButton(joystickOperator, 1);
	canCollectFwd = new JoystickButton(joystickOperator, 4);
	canCollectRvs = new JoystickButton(joystickOperator, 3);
	score = new JoystickButton(joystickOperator, 5);
	canToCraaawTransfer = new JoystickButton(joystickOperator, 9);
	craaawOverride = new JoystickButton(joystickOperator, 16);
	shoulderOverride = new JoystickButton(joystickOperator, 15);

	leftLoadButton = new JoystickButton(joystickRight, 5);
	rightLoadButton = new JoystickButton(joystickRight, 6);
	moveArmsWhackMode = new JoystickButton(joystickLeft, 1);
	zeroLifter = new JoystickButton(joystickRight, 5);
}

OI::~OI() {
	delete joystickLeft;
	delete joystickRight;
	delete joystickOperator;
	delete pushSwitch;
	delete alignTote;
	delete toteLifterFloor;
	delete toteLifterCarry;
	delete toteLifterTwoTotes;
	delete toteLifterOneTote;
	delete moveArmsWhackMode;
	delete leftLoadButton;
	delete rightLoadButton;
	delete getLast;
	delete getNext;
	delete canCollector;
	delete collect;
	delete canCollectFwd;
	delete canCollectRvs;
	delete wrist;
	delete canToCraaawTransfer;
	delete armsToggle;
	delete score;
	delete shoulderOverride;
	delete toteLifterUp;
	delete toteLifterDown;
	delete zeroLifter;
}

Joystick *OI::getJoystickOperator() {
	return joystickOperator;
}

Joystick *OI::getJoystickLeft() {
	return joystickLeft;
}

Joystick *OI::getJoystickRight() {
	return joystickRight;
}

double OI::getAnalogValue(int input) {
	//find input at port %input%
	//return analog value for that device
	return 0.0;
}

void OI::registerButtonListeners() {
	// Can manipulation
	SAFE_BUTTON(canCollector,
			canCollector->WhenPressed(new MoveArmsFancy(true)));
	SAFE_BUTTON(canCollector,
			canCollector->WhenReleased(new MoveArmsFancy(false)));
	SAFE_BUTTON(canCollectFwd, canCollectFwd->WhenPressed(new Collect()));
	SAFE_BUTTON(canCollectFwd, canCollectFwd->WhenReleased(new Collect()));
	SAFE_BUTTON(canToCraaawTransfer,
			canToCraaawTransfer->WhenPressed(new CanToCraaawTransfer()));

	// Loading/stacking
	SAFE_BUTTON(alignTote,
			alignTote->WhenPressed(new ToteIntake(ToteIntake::forward)));
	SAFE_BUTTON(alignTote,
			alignTote->WhenReleased(new ToteIntake(ToteIntake::stopped)));
	SAFE_BUTTON(getNext,
			getNext->WhenPressed(new SafeDownUp(DownUp::load)));
	SAFE_BUTTON(getLast,
			getLast->WhenPressed(new SafeDownUp(DownUp::carry)));
	SAFE_BUTTON(score, score->WhenPressed(new Score()));

	// Scoring
	SAFE_BUTTON(toteLifterTwoTotes,
			toteLifterTwoTotes->WhenReleased(new SafeLiftToHeight(TOTE_LIFTER_TWO_TOTE, true)));
	SAFE_BUTTON(toteLifterOneTote,
			toteLifterOneTote->WhenReleased(new SafeLiftToHeight(TOTE_LIFTER_ONE_TOTE)));

	// Overrides
	SAFE_BUTTON(wrist, wrist->WhenPressed(new MoveWrist(MoveWrist::close)));
	SAFE_BUTTON(wrist, wrist->WhenReleased(new MoveWrist(MoveWrist::open)));
	SAFE_BUTTON(canCollectRvs,
			canCollectRvs->WhenPressed(new Induct(Induct::reverse)));
	SAFE_BUTTON(canCollectRvs,
			canCollectRvs->WhenReleased(new Induct(Induct::stopped)));
	SAFE_BUTTON(craaawOverride,
			craaawOverride->WhenPressed(
					new CraaawActuate(DoubleSolenoid::kReverse)));
	SAFE_BUTTON(craaawOverride,
			craaawOverride->WhenReleased(
					new CraaawActuate(DoubleSolenoid::kForward)));
	SAFE_BUTTON(shoulderOverride,
			shoulderOverride->WhenPressed(new MoveArms(CAN_POT_UP_POSITION)));
	SAFE_BUTTON(shoulderOverride,
			shoulderOverride->WhenReleased(new MoveArms(CAN_POT_DOWN_POSITION)));
	SAFE_BUTTON(toteLifterUp,
			toteLifterUp->WhileHeld(new LiftToHeightVelocity(.5)));
	SAFE_BUTTON(toteLifterUp,
			toteLifterUp->WhenReleased(new LiftToHeightVelocity(0)));
	SAFE_BUTTON(toteLifterDown,
			toteLifterDown->WhileHeld(new LiftToHeightVelocity(-.5)));
	SAFE_BUTTON(toteLifterDown,
			toteLifterDown->WhenReleased(new LiftToHeightVelocity(0)));

	// Special driver buttons
	SAFE_BUTTON(leftLoadButton,
			leftLoadButton->WhenReleased(new TurnToThenDrive(LOAD_LEFT_ANGLE)));
	SAFE_BUTTON(rightLoadButton,
			rightLoadButton->WhenReleased(new TurnToThenDrive(LOAD_RIGHT_ANGLE)));
	SAFE_BUTTON(moveArmsWhackMode, moveArmsWhackMode->WhenPressed(new Whack()));
	SAFE_BUTTON(zeroLifter, zeroLifter->WhenPressed(new ResetElevatorEncoder()));
}

bool OI::isJoystickButtonPressed(bool isLeft, int val) {
	if (isLeft) {
		return val > 0 && val < joystickLeft->GetButtonCount()
				&& joystickLeft->GetRawButton(val);
	} else {
		return val > 0 && val < joystickRight->GetButtonCount()
				&& joystickRight->GetRawButton(val);
	}
}

