#include "ood_car.h"

Car::Car(const uint64_t inID, const Vector2D& inPosition, const Vector2D& inDirection)
	: m_ID(inID)
	, m_CarInfo(GetRandomCarInfo())
	, m_IsActivated(true)
	, m_Position(inPosition)
	, m_Direction(inDirection)
	, m_Speed(0.0f)
	, m_RemainingFuel(100.0f)
	, m_FuelPctConsumptionPerMeter(2.0f)
	, m_RemainignHealth(100.0f)
{
}

void Car::UpdateSteering(const float inDrivingWheelAngle)
{
	if (IsActivated() && HaveFuel() && !IsDead())
		m_Direction.RotateDeg(inDrivingWheelAngle);
}

void Car::UpdateSpeed(const float inModification)
{
	if (IsActivated() && HaveFuel() && !IsDead())
		m_Speed += inModification;
}

void Car::UpdateMovement(const float inDeltaTime)
{
	if (IsActivated() && HaveFuel() && !IsDead())
	{
		const float frame_speed = m_Speed * inDeltaTime;
		const Vector2D new_position = m_Position + m_Direction * frame_speed;
		const float distance_traveled = (m_Position - new_position).Length();
		m_RemainingFuel -= distance_traveled * m_FuelPctConsumptionPerMeter;
		m_Position = new_position;
	}
}

void Car::TakeDamage(const float inDamage)
{
	m_RemainignHealth -= inDamage;
}

void Car::SetToActivated()
{
	m_IsActivated = true;
}

void Car::SetToDeactivated()
{
	m_IsActivated = false;
}

bool Car::IsActivated() const
{
	return m_IsActivated == true;
}

bool Car::IsDead() const
{
	return m_RemainignHealth <= 0.0f;
}

bool Car::HaveFuel() const
{
	return m_RemainingFuel > 0.0f;
}