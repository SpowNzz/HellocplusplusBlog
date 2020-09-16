#pragma once

#include <random>
#include <limits>

static std::random_device gRandomDevice;
static std::mt19937 mt(gRandomDevice());

inline float RandDeltaTime()
{
	static std::uniform_real_distribution<float> distribution(0.246666681f, 0.286666681f);
    return distribution(mt);
}

inline int RandInt()
{
	std::uniform_int_distribution<int> distribution(0, numeric_limits<int>::max());
	return distribution(mt);
}

inline int RandInt(const int inFrom, const int inTo)
{
	std::uniform_int_distribution<int> distribution(inFrom, inTo);
    return distribution(mt);
}

inline float RandFloat()
{
	static std::uniform_real_distribution<float> distribution(0, numeric_limits<float>::max());
	return distribution(mt);
}

inline float RandFloat(const float inFrom, const float inTo)
{
	static std::uniform_real_distribution<float> distribution(inFrom, inTo);
	return distribution(mt);
}


