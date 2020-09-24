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
						  float inEarningsPerRent);

	// Public query API
	float CalculateReturnOnInvestment() const;
	float CalculateEarning() const;
	float CalculateMaintenanceCost() const;

	// Public modification API
	void SetEstimatedReturnOnInvestment(const float inValue);

private:
	// Estimate based on the previous month
	float m_EstimatedReturnOnInvestment;
	
	// Monthly info
	string m_BoatName;
	unsigned int m_NrOfRents;
	float m_MaintenanceCostPerRent;
	float m_EarningsPerRent;
};