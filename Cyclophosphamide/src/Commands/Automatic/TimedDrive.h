#ifndef AutoDrive_H
#define AutoDrive_H

#include "../../CommandBase.h"
#include "WPILib.h"

class TimedDrive: public CommandBase
{
private:
	long targetTime;
	long timePassed;
	long duration;
	double forwardSlashSpeed;
	double backSlashSpeed;

	// TODO remove when we get encoders
	unsigned long getTime();
public:
	TimedDrive(float duration, float heading);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif