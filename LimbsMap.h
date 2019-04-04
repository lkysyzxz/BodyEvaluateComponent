#include "Limbs.h"
class LimbsMap
{

  public:
    static float ErrorThrehold;

  private:
    Limbs *standard;
    Limbs *user;

    float errorValue;

  public:
    void Bind(Limbs *standard_, Limbs *user_)
    {
        this->standard = standard_;
        this->user = user_;
    }

    void UpdateErrorValue()
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

    float GetErrorValue()
    {
        return this->errorValue;
    }

    float GetSimilarity()
    {
        return 1 - this->errorValue;
    }
};