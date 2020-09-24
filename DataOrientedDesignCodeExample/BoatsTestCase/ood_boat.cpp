#include "ood_boat.h"

BoatRentalMonthlyInfo::BoatRentalMonthlyInfo(const string& inName, 
											 unsigned int inNrOfRents, 
											 float inMaintananceCostPerRent, 
											 float inCrewCostPerRent,
											 float inEarningsPerRent)
	: m_BoatName(inName)
	, m_NrOfRents(inNrOfRents)
	, m_MaintananceCostPerRent(inMaintananceCostPerRent)
	, m_CrewCostPerRent(inCrewCostPerRent)
	, m_EarningsPerRent(inEarningsPerRent)
{
}

float BoatRentalMonthlyInfo::CalculateEarning() const
{
	return m_NrOfRents * m_EarningsPerRent;
}

float BoatRentalMonthlyInfo::CalculateMaintenanceCost() const
{
	return m_NrOfRents * m_MaintananceCostPerRent;
}

float BoatRentalMonthlyInfo::CalculateCrewCost() const
{
	return m_NrOfRents * m_CrewCostPerRent;
}