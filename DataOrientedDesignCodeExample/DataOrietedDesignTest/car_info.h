#pragma once

using namespace std;

#include <array>
#include <string>
#include <utility>
#include <chrono>
#include <ctime>  
#include "random.h"

struct CarInfo
{
	string m_ManufacturerName;
	string m_ModelName;
	string m_ManufactoringDate;
};

inline CarInfo GetRandomCarInfo()
{
	static const int number_of_manufacturers = 7;
	static const int number_of_models_per_manufacturers = 3;
	static pair<string, array<string, number_of_models_per_manufacturers>> car_models[number_of_manufacturers] =
	{
		{"Peugeot", {"308", "208", "3008"}},
		{"Suzuki", {"Swift", "Ignis", "Cross"}},
		{"Honda", {"Civic", "CR-V", "HR-V"}},
		{"Ford", {"Mustang", "Focus", "Ranger"}},
		{"General Motors", {"Hammer H2", "Chevrolet Camaro", "Pontiac Firebird"}},
		{"Renault", {"Clio", "Megan", "Kadjar"}},
		{"Audi", {"A3", "A4", "A6"}}
	};

	const auto current_time = chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	const int rand_manufacturer = RandInt(0, number_of_manufacturers - 1);
	const int rand_model = RandInt(0, number_of_models_per_manufacturers - 1);
	return CarInfo 
	{ 
		car_models[rand_manufacturer].first, 
		car_models[rand_manufacturer].second[rand_model],
		std::ctime(&current_time) 
	};
}