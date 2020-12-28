#include "ood_boat.h"

BoatMonthlyRentalInfo::BoatMonthlyRentalInfo(const string& inName, 
											 unsigned int inNrOfRents, 
											 float inMaintenanceCostPerRent,
											 float inEarningsPerRent)
	: m_EstimatedReturnOnInvestment(0.0f)
	, m_BoatName(inName)
	, m_NrOfRents(inNrOfRents)
	, m_MaintenanceCostPerRent(inMaintenanceCostPerRent)
	, m_EarningsPerRent(inEarningsPerRent)
{
}

float BoatMonthlyRentalInfo::CalculateReturnOnInvestment() const
{
	const float earnings = CalculateEarning();
	const float cost = CalculateMaintenanceCost();
	return (earnings / cost) * 100.0f - 100.0f;
}

float BoatMonthlyRentalInfo::CalculateEarning() const
{
	return m_NrOfRents * m_EarningsPerRent;
}

float BoatMonthlyRentalInfo::CalculateMaintenanceCost() const
{
	return m_NrOfRents * m_MaintenanceCostPerRent;
}

void BoatMonthlyRentalInfo::SetEstimatedReturnOnInvestment(const float inValue)
{
	m_EstimatedReturnOnInvestment = inValue;
}