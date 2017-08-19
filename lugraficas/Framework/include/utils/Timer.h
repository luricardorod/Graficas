#ifndef PATO_TIMER_H
#define PATO_TIMER_H

#include "../Config.h"

#ifdef OS_WINDOWS
#include <windows.h>
#elif defined(OS_LINUX)
#include <sys/time.h>
#endif

class Timer
{
public:
	void Init();
	void Update();

	float	GetDTSecs();

	#ifdef OS_WINDOWS
	LARGE_INTEGER	StartTime;
	#elif defined(OS_LINUX)
	timeval	        StartTime;
	#endif
	double Frequency;
	double Dt;
	double DtSecs;
};

#endif