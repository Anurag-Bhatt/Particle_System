#pragma once

#include <random>

class Random {

public:

	static void init() {
		get_engine();
	}
	
	static float Float(float min, float max) {
		std::uniform_real_distribution<float> distribution(min, max);
		return distribution(get_engine());
	}

	static float Float() {
		return Float(0.0f, 1.0f);
	}

	static int Int(int min, int max) {
		std::uniform_int_distribution<int> distribution(min, max);
		return distribution(get_engine());
	}

private:

	static std::mt19937& get_engine() {
		thread_local std::random_device rd;
		thread_local std::mt19937 engine(rd());
		return engine;
	}
};