#ifndef ROBOTMAP_H
#define ROBOTMAP_H
#include "WPILib.h"

#define DOESNT_EXIST 0x420

#define SAFE_INIT(port, thingy) \
	if (port != 0x420) { \
		thingy \
	}

// Autonomous Configuration Settings
#define AUTO_SCRIPT_MAXLENGTH	(256)
#define AUTO_SCRIPT_MAXLINES	(64)
#define AUTO_SCRIPT_COMMAND_MAXLENGTH	(20)
#define AUTO_SCRIPT_LOCATIONS	"/Commands/Autonomous/"
#define AUTO_SCRIPT_CHARMASK(a,b) ((((int)a) << 8) | ((int)b))

#define AUTONOMOUS_DEFAULT_DISTANCE 5 //units?
#define AUTONOMOUS_DEFAULT_TIME 5 //units?

// C++ changes
#define floaterino float
#define returnerino return

// DriveBase
#define DRIVE_MOTOR_TYPE CANTalon
#define DRIVE_MOTOR_FRONT_LEFT_PORT 14
#define DRIVE_MOTOR_FRONT_RIGHT_PORT 0
#define DRIVE_MOTOR_BACK_LEFT_PORT 15
#define DRIVE_MOTOR_BACK_RIGHT_PORT 1

#define DRIVE_ROT_P  3.0
#define DRIVE_ROT_I 0.0
#define DRIVE_ROT_D 5.0

#define DRIVE_DRIVE_P 0.5
#define DRIVE_DRIVE_I 0.0
#define DRIVE_DRIVE_D 0.0

#define DRIVE_ASPECT_RATIO (0.5)
#define DRIVE_TICKS_TO_DISTANCE 420
#define GYRO_TIMEOUT 5000 // milliseconds
#define ENCODER_TICKS_PER_REV 360.0

//Tote Intake
#define TOTE_INTAKE_ENCODER_PORT 4, 5
#define TOTE_INTAKE_MOTOR_PORT 10

#define TOTE_INTAKE_MOTOR_FULL 0.3
#define TOTE_INTAKE_MOTOR_NONE 0.0
#define TOTE_INTAKE_ENCODER_TICKS_PER_REV 1024
#define TOTE_INTAKE_P 0.001
#define TOTE_INTAKE_I 0.0
#define TOTE_INTAKE_D 0.0

// Tote Lifter
#define TOTE_LIFTER_LEFT_PORT 3
#define TOTE_LIFTER_RIGHT_PORT 12
#define TOTE_LIFTER_SENSOR_PORT DOESNT_EXIST
#define TOTE_LIFTER_ENCODER_CA 0
#define TOTE_LIFTER_ENCODER_CB 1
#define TOTE_LIFTER_TOTE_INPUT_PORT 6
#define TOTE_LIFTER_ENCODER_PORTS 0,1

#define TOTE_LIFTER_MAX_DISTANCE 1600
#define TOTE_LIFTER_END_TOLERANCE 30

#define TOTE_LIFTER_ENCODER_DEADBAND 5000
#define TOTE_LIFTER_TICKS_PER_REV 1024

#define TOTE_LIFTER_PID_P .01
#define TOTE_LIFTER_PID_I 0.0
#define TOTE_LIFTER_PID_D .01

#define TOTE_LIFTER_HIGH 10
#define TOTE_LIFTER_MID 5
#define TOTE_LIFTER_LOW 1
#define TOTE_LIFTER_FLOOR 0
#define TOTE_LIFTER_ELEVATOR_TOP_INPUT_PORT 4

#define TOTE_INTAKE_TICKS_PER_INCH 64
// Mecanum
#define ONE_STICK false
#define FIELD_ORIENTED true
#define LOAD_LEFT_ANGLE 30.0
#define LOAD_RIGHT_ANGLE -30.0

// Auto
#define AUTO_DRIVE_SPEED (0.25)
#define AUTO_TURN_SLOW_DOWN (12)
#define AUTO_TURN_SPEED_MIN (0.2)
#define AUTO_TURN_SPEED_MAX (0.5)
#define AUTO_TURN_SPEED_RANGE (AUTO_TURN_SPEED_MAX - AUTO_TURN_SPEED_MIN)
#define AUTO_TURN_GYRO_THRESHOLD (0.25)

// OI
#define OI_JOYSTICK_LEFT (0)
#define OI_JOYSTICK_RIGHT (1)
#define OI_JOYSTICK_DRIVE_DEADBAND (0.05)
#define OI_JOYSTICK_ROT_DEADBAND (0.15)
#define JOYSTICK_DEGREES_PER_TICK 5.0

#define OI_JOYSTICKBUTTON_PUSHBUTTON 11
#define OI_JOYSTICKBUTTON_PULLBUTTON 12
#define OI_JOYSTICKBUTTON_ACTUATEBUTTON 2
#define OI_JOYSTICKBUTTON_UNACTUATEBUTTON 3
#define OI_JOYSTICKBUTTON_LIFTARMSBUTTON 4
#define OI_JOYSTICKBUTTON_LOWERARMSBUTTON 5
#define OI_JOYSTICKBUTTON_TOTEINTAKE_BUTTON_FORWARD 8
#define OI_JOYSTICKBUTTON_TOTEINTAKE_BUTTON_REVERSE 7
#define OI_JOYSTICKBUTTON_TOTELIFTERBUTTON 6
#define OI_JOYSTICKBUTTON_MOTORFOWARDBUTTON 1
#define OI_JOYSTICKBUTTON_MOTORBACKWARDBUTTON 2
#define OI_JOYSTICKBUTTON_WRISTINBUTTON 3
#define OI_JOYSTICKBUTTON_WRISTOUTNBUTTON 4
#define OI_JOYSTICKBUTTON_ARMSUPBUTTON 5
#define OI_JOYSTICKBUTTON_ARMSDOWNBUTTON 6
#define OI_LOAD_LEFT 11
#define OI_LOAD_RIGHT 12
#define OI_JOYSTICK_STACK 2
#define OI_LINEARPOT_MAX 4.20
#define OI_LINEARPOT_TOTE_LIFTER_OVR_PORT 2

// Can Collector
#define CAN_MOTOR_TYPE CANTalon
#define CAN_MOTOR_LIFT_LEFT_PORT 13
#define CAN_MOTOR_LIFT_RIGHT_PORT 2

#define CAN_MOTOR_GRAB_LEFT_PORT DOESNT_EXIST
#define CAN_MOTOR_GRAB_RIGHT_PORT DOESNT_EXIST
#define CAN_WRIST_SOLENOID_PORT DOESNT_EXIST, DOESNT_EXIST
#define CAN_LIFT_POT_PORT 0

#define CAN_SENSOR_PORT 0

#define CAN_POT_UP_POSITION 4.915
#define CAN_POT_DOWN_POSITION 2.0

#define CAN_LIFT_THRESHOLD 0.1

#define CAN_UP_SPEED 1.0
#define CAN_DOWN_SPEED -1.0
#define CAN_GRAB_SPEED 0.2

#define CAN_ARM_P 0.5
#define CAN_ARM_I 0.0
#define CAN_ARM_D 0.0

// Auto Canerino
#define AUTO_CAN_MOTOR_TYPE Talon


//Downward Dog Craaaw
#define CRAAAW_CAN_DETECTOR_PORT 0
#define CRAAAW_LOCK_LEFT_PORT 0 // todo figure out what these are
#define CRAAAW_LOCK_RIGHT_PORT 1

//stack pusher
#define PUSHER_LEFT_PORT 0
#define PUSHER_RIGHT_PORT 1

// Pneumatics
#define COMPRESSOR_PRESSURE_SENSOR_PORT 0
#define COMPRESSOR_RELAY_PORT 0

// Stallable Motor
#define STALLABLE_MOVE_THRESHOLD 20000
#define STALLABLE_TIME_STOP 1500

#endif
