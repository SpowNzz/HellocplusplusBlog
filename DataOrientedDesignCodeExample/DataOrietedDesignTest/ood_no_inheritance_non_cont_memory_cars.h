#pragma once

#include "ood_car.h"
#include "random.h"
#include "benchmark.h"
#include <vector>
#include <chrono>
#include <memory>
#include <iostream>

using namespace std;

static void OOD_NoInheritanceNonContMemoryCar(benchmark::State& inState)
{
    // Get the inputs
    const auto num_of_cars = inState.range(0);
    const auto num_of_frames_to_sumulate = inState.range(1);

    // Storage for the cars
    vector<unique_ptr<Car>> cars;

    // Storage for dummy cars. Used to cause memory fragmentation
    vector<unique_ptr<Car>> dummy_cars1;
    vector<unique_ptr<Car>> dummy_cars2;
    vector<unique_ptr<Car>> dummy_cars3;

    // Initialize the cars
    for (unsigned int car_index = 0; car_index < num_of_cars; ++car_index)
    {
        const uint64_t id = RandInt();
        const auto pos = Vector2D(RandFloat(), RandFloat());
        const auto dir = Vector2D(RandFloat(), RandFloat()).Normalized();
        cars.push_back(make_unique<Car>(id, pos, dir));
        if (car_index % 2)
            cars[car_index]->SetToDeactivated();

        dummy_cars1.push_back(make_unique<Car>(id, pos, dir));
        dummy_cars2.push_back(make_unique<Car>(id, pos, dir));
        dummy_cars3.push_back(make_unique<Car>(id, pos, dir));
    }

    const float steering_input = RandFloat(-2.5f, 2.5f);
    const float velocity_modification = RandFloat(0.0f, 0.2f);

    for (auto _ : inState)
    {
        for (unsigned int update_index = 0; update_index < num_of_frames_to_sumulate; ++update_index)
        {
            const float delta_time = RandDeltaTime();
			for (unsigned int car_index = 0; car_index < num_of_cars; ++car_index)
			{
				if (car_index % 2 == 0 && !cars[car_index]->IsDead())
					cars[car_index]->TakeDamage(7.0f);

                cars[car_index]->UpdateSteering(steering_input);
                cars[car_index]->UpdateVelocity(velocity_modification);
				cars[car_index]->UpdateMovement(delta_time);
			}

            benchmark::DoNotOptimize(update_index);
            benchmark::DoNotOptimize(delta_time);
        }
        benchmark::DoNotOptimize(cars);
        benchmark::DoNotOptimize(dummy_cars1);
        benchmark::DoNotOptimize(dummy_cars2);
        benchmark::DoNotOptimize(dummy_cars3);
    }
}
