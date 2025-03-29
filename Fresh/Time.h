#pragma once
#include "glfw3.h"
#include <thread>
#include <chrono>
#include <iostream>

class Time {
public:
	static double dt;
	static int FPS;

	static void Update();
	static double Now();
	static void Wait(unsigned int milliseconds);

	class ScopeTimer {
	public:
		std::chrono::time_point<std::chrono::steady_clock> start, end;
		std::chrono::duration<double> duration;

		ScopeTimer();
		~ScopeTimer();
	};

private:
	static double currentTime, lastFrameTime, sum;
};