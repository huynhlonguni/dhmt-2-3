#pragma once

#include <time.h>

class Clock {
private:
	struct timespec timeStart, timeEnd;

public:
	void start() {
		clock_gettime(CLOCK_MONOTONIC, &timeStart);
	}

	double end() {
		clock_gettime(CLOCK_MONOTONIC, &timeEnd);
		long long elapsed_ns = (timeEnd.tv_sec - timeStart.tv_sec) * 1000000000LL + (timeEnd.tv_nsec - timeStart.tv_nsec);
		return (double)elapsed_ns / 1000000.0;
	}
};