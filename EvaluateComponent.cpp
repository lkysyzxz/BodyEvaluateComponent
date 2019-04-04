#include "EvaluateComponent.h"
float EvaluateComponent::ErrorValueThrehold = 0.35f;

EvaluateComponent::EvaluateComponent(Body *standard, Body *user)
{
    this->bodyMap.Bind(standard->GetBody(), user->GetBody());
    this->leftArmMap.Bind(standard->GetLeftArm(), user->GetLeftArm());
    this->rightArmMap.Bind(standard->GetRightArm(), user->GetRightArm());
    this->leftLegMap.Bind(standard->GetLeftLeg(), user->GetLeftLeg());
    this->rightLegMap.Bind(standard->GetRightLeg(), user->GetRightLeg());
    this->lastErrorLimbs = NULL;
    this->mapping[0] = &(this->bodyMap);
    this->mapping[1] = &(this->leftArmMap);
    this->mapping[2] = &(this->rightArmMap);
    this->mapping[3] = &(this->leftLegMap);
    this->mapping[4] = &(this->rightLegMap);
}

LimbsMap *EvaluateComponent::Compare()
{
    if (this->lastErrorLimbs != NULL && this->lastErrorLimbs->GetErrorValue() >= 0.35f)
    {
        return this->lastErrorLimbs;
    }
    else
    {
        this->lastErrorLimbs = NULL;
    }

    LimbsMap *errorLimbs = NULL;
    float maxErrorValue = 0.0f;

    if (this->lastErrorLimbs == NULL)
    {
        for (int i = 0; i < 5; i++)
        {
            if (this->mapping[i]->GetErrorValue() > 0.35f && this->mapping[i]->GetErrorValue() > maxErrorValue)
            {
                errorLimbs = this->mapping[i];
                maxErrorValue = this->mapping[i]->GetErrorValue();
            }
        }
    }

    if (errorLimbs != NULL)
    {
        this->lastErrorLimbs = errorLimbs;
    }
    return errorLimbs;
}