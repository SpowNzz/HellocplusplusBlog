#pragma once

#include "ood_car.h"
#include "random.h"
#include "benchmark.h"
#include <vector>
#include <chrono>
#include <memory>
#include <iostream>

using namespace std;

static void OOD_NoInheritanceStackCar(benchmark::State& inState)
{
    // Get the inputs
    const auto num_of_cars = inState.range(0);
    const auto num_of_frames_to_sumulate = inState.range(1);

    // Initialize the cars. 
    // NOTE: This is not part of the measurement.
    vector<Car> cars;
    for (unsigned int car_index = 0; car_index < num_of_cars; ++car_index)
    {
        // Create a car
        const long long id = RandInt();
        const auto pos = Vector2D(RandFloat(), RandFloat());
        const auto dir = Vector2D(RandFloat(), RandFloat()).Normalized();
        cars.emplace_back(Car(id, pos, dir));

        // Deactivate every other car
        if (car_index % 2)
            cars[car_index].SetToDeactivated();
    }

    // Random inputs used by the simulation.
    const float steering_input = RandFloat(-2.5f, 2.5f);
    const float velocity_modification = RandFloat(0.0f, 0.2f);

    for (auto _ : inState)
    {
        for (unsigned int update_index = 0; update_index < num_of_frames_to_sumulate; ++update_index)
        { 
            const float delta_time = RandDeltaTime();
			for (unsigned int car_index = 0; car_index < num_of_cars; ++car_index)
			{
                // Damage every other car
				if (car_index % 2 == 0 && !cars[car_index].IsDead())
					cars[car_index].TakeDamage(7.0f);

                // Update the current car
                cars[car_index].UpdateSteering(steering_input);
                cars[car_index].UpdateVelocity(velocity_modification);
				cars[car_index].UpdateMovement(delta_time);
			}

            benchmark::DoNotOptimize(update_index);
            benchmark::DoNotOptimize(delta_time);
        }
        benchmark::DoNotOptimize(cars);
    }
}
