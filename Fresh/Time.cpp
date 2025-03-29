#include "Time.h"
double Time::currentTime;
double Time::lastFrameTime;
double Time::sum;
double Time::dt;
int Time::FPS;

void Time::Update() {
	currentTime = Time::Now();
	dt = currentTime - lastFrameTime;
	sum += dt;
	lastFrameTime = currentTime;

	if (sum >= 1) {
		//Engine::ClearConsole();
		//std::cout << "FPS: " << FPS << " ";
		FPS = 0;
		sum = 0;
	}
	FPS++;
}
double Time::Now() {
	return glfwGetTime();
}
void Time::Wait(unsigned int milliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

Time::ScopeTimer::ScopeTimer() {
	start = std::chrono::high_resolution_clock::now();
}
Time::ScopeTimer::~ScopeTimer() {
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;
	auto s = duration.count();
	std::cout << s << "s";
}