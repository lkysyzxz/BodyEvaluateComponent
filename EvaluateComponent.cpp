#include "EvaluateComponent.h"
#include <vector>
#include <map>
float EvaluateComponent::ErrorValueThrehold = 0.06f;

EvaluateComponent::EvaluateComponent(Body *standard, Body *user)
{
	this->bodyMap.Bind(standard->GetBody(), user->GetBody(), "Body");
	this->leftArmMap.Bind(standard->GetLeftArm(), user->GetLeftArm(), "Left Arm");
	this->rightArmMap.Bind(standard->GetRightArm(), user->GetRightArm(), "Right Arm");
	this->leftLegMap.Bind(standard->GetLeftLeg(), user->GetLeftLeg(), "Left Leg");
	this->rightLegMap.Bind(standard->GetRightLeg(), user->GetRightLeg(), "Right Leg");
	this->lastErrorLimbs = NULL;
	this->mapping[0] = &(this->leftArmMap);
	this->mapping[1] = &(this->rightArmMap);
	this->mapping[2] = &(this->leftLegMap);
	this->mapping[3] = &(this->rightLegMap);
	this->mapping[4] = &(this->bodyMap);
	for (int i = 0; i < 5; i++) {
		this->mapping[i]->SetLimbs_Num(i + 1);
		this->errorCount[i]=0;
	}
}

LimbsMap *EvaluateComponent::Compare()
{
	if (this->lastErrorLimbs != NULL)
		this->lastErrorLimbs->UpdateErrorValue();
	if (this->lastErrorLimbs != NULL && this->lastErrorLimbs->GetErrorValue() > ErrorValueThrehold)
	{
		return this->lastErrorLimbs;
	}
	else
	{
		this->lastErrorLimbs = NULL;
	}

	LimbsMap *errorLimbs = NULL;
	float maxErrorValue = -0.1f;

	if (this->lastErrorLimbs == NULL)
	{
		for (int i = 0; i < 5; i++)
		{
			this->mapping[i]->UpdateErrorValue();
			if (this->mapping[i]->GetErrorValue() > ErrorValueThrehold && this->mapping[i]->GetErrorValue() > maxErrorValue)
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

void EvaluateComponent::SamplingErrorBone(){
    LimbsMap *result = this->Compare();
    int index = result->GetLimbs_Num() - 1;
	this->errorCount[index]++;
}

LimbsMap * EvaluateComponent::ExtractErrorBone(){
	int index = this->PickErrorIndex();
	this->ClearErrorCount();
	if(index == -1)return NULL;
	else return this.mapping[index];
}

void EvaluateComponent::ClearErrorCount(){
	for(int i=0;i < 5;i++){
		this->errorCount[i] = 0;
	}
}
    
int EvaluateComponent::PickErrorIndex(){
	std::vector<std::pair<int,int>> cache;
	for(int i = 0;i < 5;i++){
		if(this->errorCount[i] > 1){
			cache.push_back(std::make_pair(i,this->errorCount[i]));
		}
	}
	if(cache.size()==0)return -1;
	int res = 0;
	int maxCnt = 0;
	for(int i=0;i<cache.size();i++){
		if(cache[i]->second>maxCnt){
			res = i;
		}
	}
	return res;
}