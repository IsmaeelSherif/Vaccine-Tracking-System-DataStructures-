#pragma once
#include <string>
#include "Stats.h"
using namespace std;

class Stats::GovernData
{
public:
	string name;
	int usersCount;
	int fullVaccNum;

	GovernData(string name) {
		this->name = name;
		usersCount = 0;
		fullVaccNum = 0;
	}

	float vaccPercent() {
		float result = fullVaccNum / (double) usersCount;
		return Stats::toPercentage(result);
	}

};
