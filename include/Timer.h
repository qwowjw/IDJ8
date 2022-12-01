#pragma once
class Timer {
public:
	Timer(float offset = 0);
	void Update(float dt);
	void Restart();
	float Get();
private:
	float time;
};