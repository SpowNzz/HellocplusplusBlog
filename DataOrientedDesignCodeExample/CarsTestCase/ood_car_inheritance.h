#pragma once

#include "vector2.h"
#include "car_info.h"
#include <memory>

using namespace std;

class CarBase
{
public:
	// Constructor
	CarBase(const uint64_t inID, const Vector2D& inPosition, const Vector2D& inDirection);

	// Destructor
	virtual ~CarBase() = default;

	// Modification API
	virtual void UpdateSteering(const float inDrivingWheelAngle) = 0;
	virtual void UpdateSpeed(const float inModification) = 0;
	virtual void UpdateMovement(const float inDeltaTime) = 0;
	void SetToActivated();
	void SetToDeactivated();
	void TakeDamage(const float inDamage);

	// Query API
	bool IsActivated() const;
	bool IsDead() const;

private:
	// Private base car data
	const uint64_t m_ID;
	bool m_IsActivated;
	float m_RemainignHealth;

protected:
	// Base car data
	CarInfo m_CarInfo;
	Vector2D m_Position;
	Vector2D m_Direction;
	float m_Velocity;
};

class PetrolCar : public CarBase
{
public:
	// Constructor
	PetrolCar(const uint64_t inID, const Vector2D& inPosition, const Vector2D& inDirection);

	// Destructor
	virtual ~PetrolCar() = default;

	// Modification API Override
	virtual void UpdateSteering(const float inDrivingWheelAngle) override;
	virtual void UpdateSpeed(const float inModification) override;
	virtual void UpdateMovement(const float inDeltaTime) override;

	// Additonal Query API
	bool HaveFuel() const;

private:
	// Fuel data
	float m_RemainingFuel;
	float m_FuelPctConsumptionPerMeter;
};