#pragma once

#include <vector>
#include <memory>

using namespace std;

class BoatRentalDataStore
{
public:
	// Default constructor
	BoatRentalDataStore() = default;

	// Create a new data entry
	void CreateBoatMonthlyRentalInfo(const string& inName,
									 unsigned int inNrOfRents,
									 float inMaintenanceCostPerRent,
									 float inEarningsPerRent);

	// Public query API
	float CalculateAverageReturnOnInvestent() const;

	// Public modification API
	void SetEstimatedAverageReturnOnInvestment(const float inValue);

private:
	// Helper structure to hold data for calculating the maintenance cost
	struct MaintenanceCostData
	{
		unsigned int m_NrOfRents;
		float m_MaintenanceCostPerRent;
	};

	// Helper structure to hold data for calculating the maintenance cost
	struct EarningsData
	{
		unsigned int m_NrOfRents;
		float m_EarningsPerRent;
	};

	float m_EstimatedAverageReturnOnInvestment;
	vector<string> m_BoatNames;
	vector<MaintenanceCostData> m_MaintenanceCostData;
	vector<EarningsData> m_EarningsData;
};