#pragma once

#include <string>

using namespace std;

class BoatRentalMonthlyInfo
{
public:
	// Constructor
	BoatRentalMonthlyInfo(const string& inName, 
						  unsigned int inNrOfRents, 
						  float inMaintananceCostPerRent, 
						  float inCrewCostPerRent, 
						  float inEarningsPerRent);

	// Public query API
	float CalculateEarning() const;
	float CalculateMaintenanceCost() const;
	float CalculateCrewCost() const;

private:
	// Data
	string m_BoatName;
	unsigned int m_NrOfRents;
	float m_MaintananceCostPerRent;
	float m_CrewCostPerRent;
	float m_EarningsPerRent;
};