#pragma once

#include "ood_boat.h"
#include "random.h"
#include "benchmark.h"
#include <vector>
#include <chrono>
#include <memory>
#include <iostream>

using namespace std;

static void OOD(benchmark::State& inState)
{
    // Get the inputs
    const auto num_of_boats = inState.range(0);

    // Initialize the boats data. 
    // NOTE: This is not part of the measurement.
    vector<BoatMonthlyRentalInfo> boats_info;
    for (unsigned int boat_index = 0; boat_index < num_of_boats; ++boat_index)
    {
        boats_info.push_back
        ({ 
            GetRandomBoatName(),                            // Name
            static_cast<unsigned int>(RandInt(10, 100)),    // Number of rents
            RandFloat(20.0f, 100.0f),                       // Maintenance cost per rent;
            RandFloat(100.0f, 350.0f),                      // Crew cost per rent;
            RandFloat(400.0f, 1000.0f)                      // Earnings per rent;
        });
    }

    for (auto _ : inState)
    {
        float average_return_on_investment_ptc = 0.0f;
        for (unsigned int boat_index = 0; boat_index < num_of_boats; ++boat_index)
        {
            const float return_ptc = boats_info[boat_index].CalculateReturnOnInvestment();
            average_return_on_investment_ptc += return_ptc;
            benchmark::DoNotOptimize(average_return_on_investment_ptc);
        }
        average_return_on_investment_ptc /= num_of_boats;
    }

}
