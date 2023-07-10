#include "Stats.h"
#include "GovernData.h"
#include <vector>
#include <algorithm>


void Stats::initialize() {
    for (int i = 0; i < 27; i++)
    {
        string govName = Stats::governorates[i];
        Stats::govData[govName] = new GovernData(govName);
    }
}

const string Stats::governorates[27] = { "Cairo", "Giza", "Alexandria", "Assiut","Aswan","Beheira","Bani-Suef","Daqahliya","Damietta",
								"Fayyoum","Gharbiya","Ismailia","Kafr-El-Sheikh","Luxor","Marsa-Matrouh",
								"Minya","Monofiya","New-Valley","North-Sinai","Port-Said","Qalioubiya","Qena","Red-Sea",
								"Sharqiya","Sohag","South-Siani","Suez" };

int Stats::usersCount = 0;

int Stats::numOfFullyvaccinated = 0;

int Stats::numOfUnvaccinated = 0;

int Stats::numOfFemales = 0;

map<string, Stats::GovernData*> Stats::govData;




void Stats::onInsert(UserData* userData)
{
    GovernData* gov = Stats::govData[userData->governorate];
    gov->usersCount++;
    Stats::usersCount++;
    if (userData->doseCount == 2) {
        Stats::numOfFullyvaccinated++;
        gov->fullVaccNum++;
    }
    else if (userData->doseCount == 0) {
        Stats::numOfUnvaccinated++;
        Stats::firstDoseWaitingList[userData->id] = userData->getFullName();
    }
    else {
        Stats::secondDoseWaitingList[userData->id] = userData->getFullName();
    }
    if (!userData->isMale) {
        Stats::numOfFemales++;
    }
}

void Stats::onDelete(UserData* userData)
{
    GovernData* gov = Stats::govData[userData->governorate];
    gov->usersCount--;
    Stats::usersCount--;
    if (userData->doseCount == 2) {
        Stats::numOfFullyvaccinated--;
        gov->fullVaccNum--;
    }
    else if (userData->doseCount == 0) {
        Stats::numOfUnvaccinated--;
        map<string, string>::iterator it = Stats::firstDoseWaitingList.find(userData->id);
        Stats::firstDoseWaitingList.erase(it);
    }
    else {
        map<string, string>::iterator it = Stats::secondDoseWaitingList.find(userData->id);
        Stats::secondDoseWaitingList.erase(it);
    }
    if (!userData->isMale) {
        Stats::numOfFemales--;
    }
}

void Stats::onUpdate(UserData* oldData, UserData* newData)
{
    onDelete(oldData);
    onInsert(newData);
}


float Stats::getUnvaccinatedPerc() {
    float ratio = numOfUnvaccinated / (float)usersCount;
    return toPercentage(ratio);
}
float Stats::getVaccinatedPerc() {
    float ratio = (usersCount - numOfUnvaccinated) / (float)usersCount;
    return toPercentage(ratio);
}
float Stats::getFullyVaccinatedPerc() {
    float ratio = numOfFullyvaccinated / (float)usersCount;
    return toPercentage(ratio);
}

float Stats::getFemalesPerc() {
    float ratio = numOfFemales / (float)usersCount;
    return toPercentage(ratio);
}

float Stats::toPercentage(float ratio) {
    ratio *= 10000.0;
    ratio = floor(ratio) / 100.0;
    return ratio;
}


bool Stats::sortByVaccPercent(pair<string, GovernData*>& a, pair<string, GovernData*>& b)
{
    return a.second->vaccPercent() > b.second->vaccPercent();
}

vector<pair<string, float>> Stats::getTopLeastGoverns() {

    vector<pair<string, GovernData*>> vec;
    vector<pair<string, float>> result(6);

    for (auto& it : govData) {
        vec.emplace_back(it);
    }

    sort(vec.begin(), vec.end(), sortByVaccPercent);

    result[0] = { vec[0].first , vec[0].second->vaccPercent()};
    result[1] = { vec[1].first , vec[1].second->vaccPercent() };
    result[2] = { vec[2].first , vec[2].second->vaccPercent() };
    result[5] = { vec[24].first , vec[24].second->vaccPercent() };
    result[4] = { vec[25].first , vec[25].second->vaccPercent() };
    result[3] = { vec[26].first , vec[26].second->vaccPercent() };

    return result;
}

map<string, string> Stats::firstDoseWaitingList;

map<string, string> Stats::secondDoseWaitingList;
