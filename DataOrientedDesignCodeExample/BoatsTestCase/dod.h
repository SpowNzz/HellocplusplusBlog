#pragma once

#include "dod_boat.h"
#include "random.h"
#include <vector>
#include <chrono>
#include <memory>
#include <iostream>

using namespace std;

static void DOD(benchmark::State& inState)
{
	// Get the inputs
	const auto num_of_boats = inState.range(0);

	// Initialize the boats data. 
	// NOTE: This is not part of the measurement.
	BoatRentalDataStore store;
	for (unsigned int boat_index = 0; boat_index < num_of_boats; ++boat_index)
	{
		store.CreateBoatMonthlyRentalInfo
		(
			GetRandomBoatName(),                            // Name
			static_cast<unsigned int>(RandInt(10, 100)),    // Number of rents
			RandFloat(20.0f, 100.0f),                       // Maintenance cost per rent
			RandFloat(400.0f, 1000.0f)                      // Earnings per rent
		);
	}
	benchmark::DoNotOptimize(store);

	// This is the code we measure with Google Benchmark
	float average_return_on_investment_ptc = 0.0f;
    for (auto _ : inState)
    {
		average_return_on_investment_ptc = store.CalculateAverageReturnOnInvestent();
		benchmark::DoNotOptimize(average_return_on_investment_ptc);
    }

	// Used to make sure entire code is not optimized out
	// This is not part of the measurement
	store.SetEstimatedAverageReturnOnInvestment(average_return_on_investment_ptc);
}
