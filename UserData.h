#pragma once
#include <string>
using namespace std;

class UserData
{
public:
	string id, password, firstName, lastName, governorate;
	bool isMale;
	int age;
	int doseCount = 0;

	string getFullName() {
		return firstName + " " + lastName;
	}
};

