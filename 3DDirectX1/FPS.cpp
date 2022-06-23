#include "FPS.h"

void FPS::Start()
{
	if (QueryPerformanceFrequency(&timeFreq) == FALSE) {
		return;
	}
	QueryPerformanceCounter(&timeStart);
}

void FPS::Ran()
{
	QueryPerformanceCounter(&timeEnd);
}

FPS* FPS::GetInstance()
{
	static FPS instance;

	return &instance;
}
