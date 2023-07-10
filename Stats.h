#pragma once
#include <string>
#include <map>
#include <vector>

#include "UserData.h"
using namespace std;

class Stats
{

public: 
	class GovernData;
	

public:

	static void initialize();

	static const string governorates[27];

	static int usersCount;

	static int numOfUnvaccinated;

	static int numOfFullyvaccinated;

	static int numOfFemales;

	//Update Stats on Any UserData Change
	static void onInsert(UserData* userData);

	static void onDelete(UserData* userData);

	static void onUpdate(UserData* oldData, UserData* newData);


	//get calculated statistics

	static float getUnvaccinatedPerc();

	static float getVaccinatedPerc();

	static float getFullyVaccinatedPerc();

	static float getFemalesPerc();

	static vector<pair<string, float>> getTopLeastGoverns();

	static map<string, string> firstDoseWaitingList;

	static map<string, string> secondDoseWaitingList;

private:
	static map<string, GovernData*> govData;

	

	static bool sortByVaccPercent(pair<string, GovernData*>& a, pair<string, GovernData*>& b);

	static float toPercentage(float ratio);

};

