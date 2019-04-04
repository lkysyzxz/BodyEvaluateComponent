#include "LimbsMap.h"
float LimbsMap::ErrorThrehold = 0.35f;

void LimbsMap::Bind(Limbs *standard_, Limbs *user_)
{
    this->standard = standard_;
    this->user = user_;
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
            float similarity = distance / 2.0f;
            sum += (1 - similarity) / 3.0f;
        }
        errorValue = sum;
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