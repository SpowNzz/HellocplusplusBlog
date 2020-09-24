#pragma once

#include <string>

using namespace std;

class BoatMonthlyRentalInfo
{
public:
	// Constructor
	BoatMonthlyRentalInfo(const string& inName, 
						  unsigned int inNrOfRents, 
						  float inMaintenanceCostPerRent,
						  float inCrewCostPerRent, 
						  float inEarningsPerRent);

	// Public query API
	float CalculateReturnOnInvestment() const;
	float CalculateEarning() const;
	float CalculateMaintenanceCost() const;
	float CalculateCrewCost() const;

private:
	// Data
	string m_BoatName;
	unsigned int m_NrOfRents;
	float m_MaintenanceCostPerRent;
	float m_CrewCostPerRent;
	float m_EarningsPerRent;
};