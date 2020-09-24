#include "ood_boat.h"

BoatRentalMonthlyInfo::BoatRentalMonthlyInfo(const string& inName, 
											 unsigned int inNrOfRents, 
											 float inMaintenanceCostPerRent,
											 float inCrewCostPerRent,
											 float inEarningsPerRent)
	: m_BoatName(inName)
	, m_NrOfRents(inNrOfRents)
	, m_MaintenanceCostPerRent(inMaintenanceCostPerRent)
	, m_CrewCostPerRent(inCrewCostPerRent)
	, m_EarningsPerRent(inEarningsPerRent)
{
}

float BoatRentalMonthlyInfo::CalculateReturnOnInvestment() const
{
	const float earnings = CalculateEarning();
	const float cost = CalculateMaintenanceCost() + CalculateCrewCost();
	return (earnings / cost) * 100.0f - 100.0f;
}

float BoatRentalMonthlyInfo::CalculateEarning() const
{
	return m_NrOfRents * m_EarningsPerRent;
}

float BoatRentalMonthlyInfo::CalculateMaintenanceCost() const
{
	return m_NrOfRents * m_MaintenanceCostPerRent;
}

float BoatRentalMonthlyInfo::CalculateCrewCost() const
{
	return m_NrOfRents * m_CrewCostPerRent;
}