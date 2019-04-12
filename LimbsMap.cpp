#include "LimbsMap.h"
float LimbsMap::ErrorThrehold = 0.06f;

void LimbsMap::Bind(Limbs *standard_, Limbs *user_, std::string name_)
{
    this->standard = standard_;
    this->user = user_;
	this->name = name_;
}

void LimbsMap::UpdateErrorValue()
{
    if (standard != NULL && user != NULL)
    {
        Joint **standardJoints = standard->GetJoints();
        Joint **userJoints = user->GetJoints();
        float sum = 0.0f;
        for (int i = 0; i < 3; i++)
        {
            float distance = Quaternion::DistanceBetween(standardJoints[i]->GetRotation(), userJoints[i]->GetRotation());
            float similarity = 1 - distance / 2.0f;
            sum += (1 - similarity) / 3.0f;
        }
        errorValue = sum;
		else if(errorCount>0) {
			errorCount=0;
		}
    }
}

float LimbsMap::GetErrorValue()
{
    return this->errorValue;
}

float LimbsMap::GetSimilarity()
{
    return 1 - this->errorValue;
}
int LimbsMap::GetLimbs_Num() {
	return limbs_num;
}
void LimbsMap::SetLimbs_Num(int num) {
	this->limbs_num = num;
}

bool LimbsMap::IsError() {
	return this->errorValue > LimbsMap::ErrorThrehold;
}
std::string LimbsMap::GetName() {
	return this->name;
}