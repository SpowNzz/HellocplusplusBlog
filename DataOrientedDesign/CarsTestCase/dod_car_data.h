#pragma once

#include "vector2.h"
#include "car_info.h"
#include <vector>
#include <memory>

using namespace std;

// Forward declaration
// Stores one frame transient data
// This is intermediate data used by the update pipeline every frame and discarded at the end
// Note that this class in defined in the .cpp file because only the store needs to see it
namespace Details
{
	struct CarsStoreTransientData;
}

// Stores all car related data
class CarsStore
{
public:
	// Car active state
	enum class State
	{
		Activated,
		Deactivated
	};

	// Constructor
	CarsStore();

	// Destructor
	~CarsStore();

	// Public modification API
	void CreateCar(const uint64_t inID, const Vector2D& inPosition, const Vector2D& inDirection);
	void SetCarToActivedState(const unsigned int inCarIndex);
	void SetCarToDeactivatedState(const unsigned int inCarIndex);
	void DamageCar(const unsigned int inCarIndex, const float inDamage);

	// Public update API
	void UpdateCars(const float inDeltaTime, const vector<float>& ioSteeringData, const vector<float>& ioVelocityModificationData);

	// Public query API
	bool IsCarActivated(const unsigned int inCarIndex) const;
	bool DoesCarHaveFuel(const unsigned int inCarIndex) const;
	bool IsCarDead(const unsigned int inCarIndex) const;

private:
	// Store data
	unsigned int m_NumOfCars;
	vector<uint64_t> m_IDs;
	vector<State> m_ActivationStates;
	vector<Vector2D> m_Positions;
	vector<Vector2D> m_Directions;
	vector<float> m_Veloctities;
	vector<float> m_Fuel;
	vector<float> m_FuelConsumptionPerMeter;
	vector<float> m_HealthData;
	vector<CarInfo> m_InfoData;

	// Stores one frame transient data
	// This is intermediate data used by the update pipeline every frame and discarded at the end
	unique_ptr<Details::CarsStoreTransientData> m_TransientData;
};