#include "dod_car_data.h"
#include <cassert>

// Forward declarations for utility functions used by the update pipeline
namespace Details
{
	// Helper structs to store parts of the transient data
	struct FuelDataForCarsToUpdate
	{
		float m_RemainingFuel;
		const float m_FuelConsumptionPerMeter;
		const float m_DistanceTraveled;
	};

	struct MovementDataForCarsToUpdate
	{
		Vector2D m_Position;
		const Vector2D m_Diretion;
		const float m_Speed;
		float m_DistanceTraveled;
	};
	
	// Stores one frame transient data
	// This is intermediate data used by the update pipeline every frame and discarded at the end
	// Note that this class in defined in the .cpp file because only the store needs to see it
	struct CarsStoreTransientData
	{
		vector<unsigned int> m_CarsToUpdate;
		vector<Vector2D> m_DirectionsToUpdate;
		vector<float> m_VelocitiesToUpdate;
		vector<MovementDataForCarsToUpdate> m_MovementDataForCarsToUpdate;
		vector<FuelDataForCarsToUpdate> m_FuelDataForCarsToUpdate;

		void Clear()
		{
			m_CarsToUpdate.clear();
			m_DirectionsToUpdate.clear();
			m_VelocitiesToUpdate.clear();
			m_MovementDataForCarsToUpdate.clear();
			m_FuelDataForCarsToUpdate.clear();
		}
	};

	// Select all cars that need an update
	void SelectCarsToUpdate(const CarsStore& inStore,
							const unsigned int inNumOfCars,
							vector<unsigned int>& outCarsToUpdate);

	// Prapare the steering data and update cars' steering
	void PreapareDirectionsToUpdate(const vector<unsigned int>& inCarsToUpdate,
									const vector<Vector2D>& inDirections,
									vector<Vector2D>& outDirectionsToUpdate);

	void UpdateSteering(const float inDeltaTime,
						const vector<float>& ioSteeringData,
						vector<Vector2D>& outDirectionsToUpdate);

	// Prepare the speed data and update cars' speed
	void PreapareVelocitiesToUpdate(const vector<unsigned int>& inCarsToUpdate,
									const vector<float>& inVeloctities,
									vector<float>& outVelocitiesToUpdate);

	void UpdateSpeed(const float inDeltaTime,
						const vector<float>& ioSpeedModificationData,
						vector<float>& outVelocitiesToUpdate);

	// Prepare the movement data and update cars' position
	void PreapareMovementDataForCarsToUpdate(const vector<unsigned int>& inCarsToUpdate,
											 const vector<Vector2D>& inPositions,
											 const vector<Vector2D>& inDirections,
											 const vector<float>& inVeloctities,
											 vector<MovementDataForCarsToUpdate>& outMovementDataForCarsToUpdate);

	void UpdateMovements(const float inDeltaTime, vector<MovementDataForCarsToUpdate>& outMovementDataForCarsToUpdate);

	// Prepare the fuel data and update cars' fuel
	void PreapareFuelForCarsToUpdate(const vector<unsigned int>& inCarsToUpdate,
									 const vector<float>& inFuel,
									 const vector<float>& inFuelConsumptionPerMeter,
									 const vector<MovementDataForCarsToUpdate>& inMovementDataForCarsToUpdate,
									 vector<FuelDataForCarsToUpdate>& outFuelDataForCarsToUpdate);

	void UpdateFuel(const float inDeltaTime, vector<FuelDataForCarsToUpdate>& outFuelDataForCarsToUpdate);
}

CarsStore::CarsStore()
	: m_NumOfCars(0)
	, m_TransientData(make_unique<Details::CarsStoreTransientData>())
{
}

CarsStore::~CarsStore() = default;

void CarsStore::CreateCar(const uint64_t inID, const Vector2D& inPosition, const Vector2D& inDirection)
{
	m_IDs.push_back(inID);
	m_Positions.push_back(inPosition);
	m_Directions.push_back(inDirection);
	m_Veloctities.push_back(0.0f);
	m_Fuel.push_back(100.0f);
	m_FuelConsumptionPerMeter.push_back(2.0f);
	m_ActivationStates.push_back(State::Activated);
	m_HealthData.push_back(100.0f);
	m_InfoData.push_back(GetRandomCarInfo());
	++m_NumOfCars;
}

void CarsStore::SetCarToActivedState(const unsigned int inCarIndex)
{
	m_ActivationStates[inCarIndex] = State::Activated;
}

void CarsStore::SetCarToDeactivatedState(const unsigned int inCarIndex)
{
	m_ActivationStates[inCarIndex] = State::Deactivated;
}

void CarsStore::DamageCar(const unsigned int inCarIndex, const float inDamage)
{
	m_HealthData[inCarIndex] -= inDamage;
}

void CarsStore::UpdateCars(const float inDeltaTime, const vector<float>& ioSteeringData, const vector<float>& ioSpeedModificationData)
{
	using namespace Details;

	// Select which cars need to be updated this frame
	SelectCarsToUpdate
	(	
		*this, 
		m_NumOfCars, 
		m_TransientData->m_CarsToUpdate
	);

	// Prepare the directions data of the cars that need to be updated
	PreapareDirectionsToUpdate
	(
		m_TransientData->m_CarsToUpdate, 
		m_Directions, 
		m_TransientData->m_DirectionsToUpdate
	);
	// Update the directions data of the cars selected for update
	UpdateSteering
	(
		inDeltaTime, 
		ioSteeringData, 
		m_TransientData->m_DirectionsToUpdate
	);

	// Prepare the velocities data of the cars that need to be updated
	PreapareVelocitiesToUpdate
	(
		m_TransientData->m_CarsToUpdate, 
		m_Veloctities, 
		m_TransientData->m_VelocitiesToUpdate
	);
	// Update the velocities data of the cars selected for update
	UpdateSpeed
	(
		inDeltaTime, 
		ioSpeedModificationData,
		m_TransientData->m_VelocitiesToUpdate
	);

	// Prepare the movement data of the cars that need to be updated
	PreapareMovementDataForCarsToUpdate
	(
		m_TransientData->m_CarsToUpdate, 
		m_Positions, 
		m_Directions, 
		m_Veloctities, 
		m_TransientData->m_MovementDataForCarsToUpdate
	);
	// Update the movement data of the cars selected for update
	UpdateMovements
	(
		inDeltaTime, 
		m_TransientData->m_MovementDataForCarsToUpdate
	);

	// Prepare the fuel data of the cars that need to be updated
	PreapareFuelForCarsToUpdate
	(
		m_TransientData->m_CarsToUpdate, 
		m_Fuel, 
		m_FuelConsumptionPerMeter, 
		m_TransientData->m_MovementDataForCarsToUpdate, 
		m_TransientData->m_FuelDataForCarsToUpdate
	);
	// Update the fuel data of the cars selected for update
	UpdateFuel
	(
		inDeltaTime, 
		m_TransientData->m_FuelDataForCarsToUpdate
	);

	// Copy the transient data into the store data
	unsigned int data_index = 0;
	for (unsigned int car_index : m_TransientData->m_CarsToUpdate)
	{
		m_Directions[car_index] = m_TransientData->m_DirectionsToUpdate[data_index];
		m_Veloctities[car_index] = m_TransientData->m_VelocitiesToUpdate[data_index];
		m_Positions[car_index] = m_TransientData->m_MovementDataForCarsToUpdate[data_index].m_Position;
		m_Fuel[car_index] = m_TransientData->m_FuelDataForCarsToUpdate[data_index].m_RemainingFuel;
		++data_index;
	}

	// Clear the transient data and make it ready to be used for the next frame
	m_TransientData->Clear();
}

bool CarsStore::IsCarActivated(const unsigned int inCarIndex) const
{
	return m_ActivationStates[inCarIndex] == State::Activated;
}

bool CarsStore::DoesCarHaveFuel(const unsigned int inCarIndex) const
{
	return m_Fuel[inCarIndex] > 0.0f;
}

bool CarsStore::IsCarDead(const unsigned int inCarIndex) const
{
	return m_HealthData[inCarIndex] <= 0.0f;
}

namespace Details
{
	void SelectCarsToUpdate(const CarsStore& inStore,
							const unsigned int inNumOfCars,
							vector<unsigned int>& outCarsToUpdate)
	{
		for (unsigned int car_index = 0; car_index < inNumOfCars; ++car_index)
		{
			if (inStore.IsCarActivated(car_index) &&
				inStore.DoesCarHaveFuel(car_index) &&
				!inStore.IsCarDead(car_index))
			{
				outCarsToUpdate.push_back(car_index);
			}
		}
	}

	void PreapareDirectionsToUpdate(const vector<unsigned int>& inCarsToUpdate,
									const vector<Vector2D>& inDirections,
									vector<Vector2D>& outDirectionsToUpdate)
	{
		for (unsigned int car_index : inCarsToUpdate)
			outDirectionsToUpdate.push_back(inDirections[car_index]);
	}

	void UpdateSteering(const float inDeltaTime,
						const vector<float>& ioSteeringData,
						vector<Vector2D>& outDirectionsToUpdate)
	{
		unsigned int index = 0;
		for (Vector2D& direction : outDirectionsToUpdate)
			direction.RotateDeg(ioSteeringData[index++]);
	}

	void PreapareVelocitiesToUpdate(const vector<unsigned int>& inCarsToUpdate,
									const vector<float>& inVeloctities,
									vector<float>& outVelocitiesToUpdate)
	{
		for (unsigned int car_index : inCarsToUpdate)
			outVelocitiesToUpdate.push_back(inVeloctities[car_index]);
	}

	void UpdateSpeed(const float inDeltaTime,
						const vector<float>& ioSpeedModificationData,
						vector<float>& outVelocitiesToUpdate)
	{
		unsigned int index = 0;
		for (float& speed : outVelocitiesToUpdate)
			speed += ioSpeedModificationData[index++];
	}

	void PreapareMovementDataForCarsToUpdate(const vector<unsigned int>& inCarsToUpdate,
											 const vector<Vector2D>& inPositions,
											 const vector<Vector2D>& inDirections,
											 const vector<float>& inVeloctities,
											 vector<MovementDataForCarsToUpdate>& outMovementDataForCarsToUpdate)
	{
		for (unsigned int car_index : inCarsToUpdate)
		{
			outMovementDataForCarsToUpdate.push_back
			({
				inPositions[car_index],
				inDirections[car_index],
				inVeloctities[car_index]
			});
		}
	}

	void UpdateMovements(const float inDeltaTime, vector<MovementDataForCarsToUpdate>& outMovementDataForCarsToUpdate)
	{
		for (auto& movement_data : outMovementDataForCarsToUpdate)
		{
			const Vector2D& pos = movement_data.m_Position;
			const Vector2D& dir = movement_data.m_Diretion;
			const float vel = movement_data.m_Speed * inDeltaTime;
			const Vector2D new_position = pos + dir * vel;
			movement_data.m_DistanceTraveled = (pos - new_position).Length();
			movement_data.m_Position = new_position;
		}
	}

	void PreapareFuelForCarsToUpdate(const vector<unsigned int>& inCarsToUpdate,
									 const vector<float>& inFuel,
									 const vector<float>& inFuelConsumptionPerMeter,
									 const vector<MovementDataForCarsToUpdate>& inMovementDataForCarsToUpdate,
									 vector<FuelDataForCarsToUpdate>& outFuelDataForCarsToUpdate)
	{
		unsigned int movement_data_index = 0;
		for (unsigned int car_index : inCarsToUpdate)
		{
			outFuelDataForCarsToUpdate.push_back
			({
				inFuel[car_index],
				inFuelConsumptionPerMeter[car_index],
				inMovementDataForCarsToUpdate[movement_data_index].m_DistanceTraveled
			});
			++movement_data_index;
		}
	}

	void UpdateFuel(const float inDeltaTime, vector<FuelDataForCarsToUpdate>& outFuelDataForCarsToUpdate)
	{
		for (auto& fuel_data : outFuelDataForCarsToUpdate)
			fuel_data.m_RemainingFuel -= fuel_data.m_DistanceTraveled * fuel_data.m_FuelConsumptionPerMeter;
	}
}