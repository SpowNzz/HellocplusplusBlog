#pragma once

#include "vector2.h"
#include "car_info.h"

class Car
{
public:
    // Constructor
    Car(const long long inID, const Vector2D& inPosition, const Vector2D& inDirection);

    // Modification API
    void UpdateSteering(const float inDrivingWheelAngle);
    void UpdateVelocity(const float inModification);
    void UpdateMovement(const float inDeltaTime);
    void TakeDamage(const float inDamage);
    void SetToActivated();
    void SetToDeactivated();

    // Query API
	bool IsActivated() const;
	bool IsDead() const;
	bool HaveFuel() const;

private:
    // Car data
    const long long m_ID;
    CarInfo m_CarInfo;
    bool m_IsActivated;
    Vector2D m_Position;
    Vector2D m_Direction;
    float m_Velocity;
    float m_RemainingFuel;
	float m_FuelPctConsumptionPerMeter;
    float m_RemainignHealth;
};

