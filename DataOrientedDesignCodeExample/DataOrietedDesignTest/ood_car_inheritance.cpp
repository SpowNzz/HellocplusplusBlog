#include "ood_car_inheritance.h"

CarBase::CarBase(const uint64_t inID, const Vector2D& inPosition, const Vector2D& inDirection)
	: m_ID(inID)
	, m_CarInfo(GetRandomCarInfo())
	, m_IsActivated(true)
	, m_RemainignHealth(100.0f)
	, m_Position(inPosition)
	, m_Direction(inDirection)
	, m_Velocity(0.0f)
{
}

void CarBase::SetToActivated()
{
	m_IsActivated = true;
}

void CarBase::SetToDeactivated()
{
	m_IsActivated = false;
}

bool CarBase::IsActivated() const
{
	return m_IsActivated;
}

void CarBase::TakeDamage(const float inDamage)
{
	m_RemainignHealth -= inDamage;
}

bool CarBase::IsDead() const
{
	return m_RemainignHealth <= 0.0f;
}

PetrolCar::PetrolCar(const uint64_t inID, const Vector2D& inPosition, const Vector2D& inDirection)
	: CarBase(inID, inPosition, inDirection)
	, m_RemainingFuel(100.0f)
	, m_FuelPctConsumptionPerMeter(2.0f)
{
}

void PetrolCar::UpdateSteering(const float inDrivingWheelAngle)
{
	if (IsActivated() && HaveFuel() && !IsDead())
		m_Direction.RotateDeg(inDrivingWheelAngle);
}

void PetrolCar::UpdateVelocity(const float inModification)
{
	if (IsActivated() && HaveFuel() && !IsDead())
		m_Velocity += inModification;
}

void PetrolCar::UpdateMovement(const float inDeltaTime)
{
	if (IsActivated() && HaveFuel() && !IsDead())
	{
		const Vector2D new_position = m_Position + m_Direction * (m_Velocity * inDeltaTime);
		float distance_traveled = (m_Position - new_position).Length();
		m_RemainingFuel -= distance_traveled * m_FuelPctConsumptionPerMeter;
		m_Position = new_position;
	}
}

bool PetrolCar::HaveFuel() const
{
	return m_RemainingFuel > 0.0f;
}