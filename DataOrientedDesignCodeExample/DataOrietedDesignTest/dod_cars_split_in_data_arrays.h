#pragma once

#include "dod_car_data.h"
#include "random.h"
#include <vector>
#include <chrono>
#include <memory>
#include <iostream>

using namespace std;

static void DOD_CarSplitInDataArrays(benchmark::State& inState)
{
    // Get the inputs
    const auto num_of_cars = inState.range(0);
    const auto num_of_frames_to_sumulate = inState.range(1);

    // Initialize the cars. 
    // This is not part of the measurement.
    CarsStore store;
    vector<float> steering_input;
    vector<float> velocity_modifications;
    for (unsigned int car_index = 0; car_index < num_of_cars; ++car_index)
    {
        // Create a car
        // We use random values because they don't matter for the purpose of this example
        const uint64_t id = RandInt();
        const auto pos = Vector2D(RandFloat(), RandFloat());
        const auto dir = Vector2D(RandFloat(), RandFloat()).Normalized();
        store.CreateCar(id, pos, dir);

        // Deactivate every other car
		if (car_index % 2)
			store.SetCarToDeactivatedState(car_index);

        // Create random simulated input that is going to be used to update the cars
        steering_input.push_back(RandFloat(-2.5f, 2.5f));
        velocity_modifications.push_back(RandFloat(0.0f, 0.2f));
    }
    

    for (auto _ : inState)
    {
        for (unsigned int update_index = 0; update_index < num_of_frames_to_sumulate; ++update_index)
        {
            // Damage every other car
            for (unsigned int car_index = 0; car_index < num_of_cars; ++car_index)
            {
                if (car_index % 2 == 0 && !store.IsCarDead(car_index))
                    store.DamageCar(car_index, 7.0f);
            }

			// Update the cars
            const float delta_time = RandDeltaTime();
            store.UpdateCars(delta_time, steering_input, velocity_modifications);

            benchmark::DoNotOptimize(update_index);
            benchmark::DoNotOptimize(delta_time);
        }
        benchmark::DoNotOptimize(store);
    }
}
