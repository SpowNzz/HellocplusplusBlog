#pragma once

#include "dod_car_data.h"
#include "random.h"
#include <vector>
#include <chrono>
#include <memory>
#include <iostream>

using namespace std;

static void DOD(benchmark::State& inState)
{
    // Get the inputs
    const auto num_of_cars = inState.range(0);
    const auto num_of_frames_to_sumulate = inState.range(1);

    for (auto _ : inState)
    {
        for (unsigned int update_index = 0; update_index < num_of_frames_to_sumulate; ++update_index)
        {
			for (unsigned int car_index = 0; car_index < num_of_cars; ++car_index)
            {
            }

            benchmark::DoNotOptimize(update_index);
        }
        //benchmark::DoNotOptimize(store);
    }
}
