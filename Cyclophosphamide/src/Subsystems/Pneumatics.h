#ifndef Pneumatics_H
#define Pneumatics_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
/**
 * compressor will actuate and  get value pressure.
 */
class Pneumatics: public Subsystem {
private:
	DigitalInput *pressureSwitch;
	Compressor *relay;
public:
	Pneumatics();
	~Pneumatics();
	void InitDefaultCommand();
	void setState(bool state);
	bool isBelowPressure();
	bool isCompressorOn();
};

#endif
