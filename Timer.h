#pragma once
#include <chrono>

class Timer
{
	std::vector<std::chrono::steady_clock::time_point> timesNoted;
public:
	void addCurrentTime();
	int lastTwoTimes();
	int fullTime();
};

void Timer::addCurrentTime()
{
	auto time = std::chrono::high_resolution_clock::now();
	this->timesNoted.push_back(time);
}

int Timer::lastTwoTimes()
{
	auto temp2 = timesNoted[timesNoted.size() - 1] - timesNoted[timesNoted.size() - 2];
	return std::chrono::duration_cast<std::chrono::milliseconds>(temp2).count();
}

int Timer::fullTime()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(timesNoted.back() - timesNoted.front()).count();
}