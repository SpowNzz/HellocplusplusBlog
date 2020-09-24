#include "dod_boat.h"
#include <cassert>

void BoatRentalDataStore::CreateBoatMonthlyRentalInfo(const string& inName,
													  unsigned int inNrOfRents,
													  float inMaintenanceCostPerRent,
													  float inEarningsPerRent)
{
	m_BoatNames.push_back(inName);
	m_MaintenanceCostData.push_back({ inNrOfRents, inMaintenanceCostPerRent });
	m_EarningsData.push_back({ inNrOfRents, inEarningsPerRent });
}

float BoatRentalDataStore::CalculateAverageReturnOnInvestent() const
{
	float combined_costs = 0.0f;
	for (auto &data : m_MaintenanceCostData)
		combined_costs += data.m_NrOfRents * data.m_MaintenanceCostPerRent;

	float combined_earnings = 0.0f;
	for (auto &data : m_EarningsData)
		combined_earnings += data.m_NrOfRents * data.m_EarningsPerRent;

	return (combined_earnings / combined_costs) * 100.0f - 100.0f;
}

void BoatRentalDataStore::SetEstimatedAverageReturnOnInvestment(const float inValue)
{
	m_EstimatedAverageReturnOnInvestment = inValue;
}