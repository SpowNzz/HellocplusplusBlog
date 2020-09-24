#pragma once

#include <random>
#include <limits>
#include <array>

static std::random_device gRandomDevice;
static std::mt19937 mt(gRandomDevice());

inline int RandInt()
{
	std::uniform_int_distribution<int> distribution(0, std::numeric_limits<int>::max());
	return distribution(mt);
}

inline int RandInt(const int inFrom, const int inTo)
{
	std::uniform_int_distribution<int> distribution(inFrom, inTo);
    return distribution(mt);
}

inline float RandFloat()
{
	std::uniform_real_distribution<float> distribution(0, std::numeric_limits<float>::max());
	return distribution(mt);
}

inline float RandFloat(const float inFrom, const float inTo)
{
	std::uniform_real_distribution<float> distribution(inFrom, inTo);
	return distribution(mt);
}

inline std::string GetRandomBoatName()
{
	static const int number_of_possible_names = 25;
	array<string, number_of_possible_names> names =
	{
		"Mary", "Patricia", "Jennifer", "Linda", "Elizabeth", "Barbara", "Susan",
		"Jessica", "Sarah", "Karen", "Nancy", "Lisa", "Margaret", "Betty", "Sandra",
		"Ashley", "Dorothy", "Kimberly", "Emily", "Donna", "Michelle", "Carol",
		"Amanda", "Melissa", "Deborah"
	};

	const int rand_name_index = RandInt(0, number_of_possible_names - 1);
	return names[rand_name_index];
}



