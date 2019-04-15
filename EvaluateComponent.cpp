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
	for (int i = 0; i < 5; i++)
	{
		this->mapping[i]->SetLimbs_Num(i + 1);
		this->errorCount[i] = 0;
	}
}

LimbsMap *EvaluateComponent::Compare()
{
	// if (this->lastErrorLimbs != NULL)
	// 	this->lastErrorLimbs->UpdateErrorValue();
	// if (this->lastErrorLimbs != NULL && this->lastErrorLimbs->GetErrorValue() > ErrorValueThrehold)
	// {
	// 	return this->lastErrorLimbs;
	// }
	// else
	// {
	// 	this->lastErrorLimbs = NULL;
	// }

	LimbsMap *errorLimbs = NULL;
	float maxErrorValue = -0.1f;

	// if (this->lastErrorLimbs == NULL)
	// {
	for (int i = 0; i < 5; i++)
	{
		this->mapping[i]->UpdateErrorValue();
		if (this->mapping[i]->GetErrorValue() > ErrorValueThrehold && this->mapping[i]->GetErrorValue() > maxErrorValue)
		{
			errorLimbs = this->mapping[i];
			maxErrorValue = this->mapping[i]->GetErrorValue();
		}
	}
	// }

	// if (errorLimbs != NULL)
	// {
	// 	this->lastErrorLimbs = errorLimbs;
	// }

	return errorLimbs;
}

void EvaluateComponent::SamplingErrorBone()
{
	LimbsMap *result = this->Compare();
	int index = result->GetLimbs_Num() - 1;
	this->errorCount[index]++;
}

LimbsMap *EvaluateComponent::ExtractErrorBone()
{
	if (this->missCache.size() > 0)
	{
		for (int i = 0; i < this->missCache.size(); i++)
		{
			int index = this->missCache[i];
			LimbsMap *tmp = this->mapping[index];
			tmp->UpdateErrorValue();
			if (tmp->GetErrorValue() > ErrorValueThrehold)
			{
				this->errorCount[index] += 2;
			}
		}
		this->missCache.clear();
	}
	int res = -1;
	std::vector<std::pair<int, int>> filtedIndex = FiltErrorCount();
	if (filtedIndex.size() > 0)
	{
		while (filtedIndex.size() > 0)
		{
			int index = this->PickErrorIndex(filtedIndex);
			int side = this->GetSide(index + 1);
			if (this->lastExtractSide == 0 || (this->lastExtractSide != 0 && this->lastExtractSide == side))
			{
				res = index;
				break;
			}
			else
			{
				this->missCache.push_back(index);
			}
		}
	}

	if (res == -1 && this->missCache.size() > 0)
	{
		auto it = this->missCache.begin();
		res = it->first;
		this->missCache.erase(it);
	}

	if (res == -1)
	{
		return NULL;
	}
	else
	{
		this->lastExtractSide = this->GetSide(res + 1);
		return this->mapping[res];
	}
	// int index = this->PickErrorIndex();
	// this->ClearErrorCount();
	// if (index == -1)
	// 	return NULL;
	// else
	// 	return this.mapping[index];
}

std::vector<std::pair<int, int>> EvaluateComponent::FiltErrorCount()
{
	std::vector<std::pair<int, int>> cache;
	for (int i = 0; i < 5; i++)
	{
		if (this->errorCount[i] > 1)
		{
			cache.push_back(std::make_pair(i, this->errorCount[i]));
		}
	}
	return cache;
}

int EvaluateComponent::GetSide(int num)
{
	if (num == 1 || num == 3)
		return 1;
	if (num == 2 || num == 4)
		return 2;
	else if (num == 5)
		return 0;
}

int EvaluateComponent::PickErrorIndex(std::vector<std::pair<int, int>> &cache)
{
	int res = 0;
	int maxCnt = 0;
	std::vector<std::pair<int, int>>::iterator selected;
	for (std::vector<std::pair<int, int>>::iterator it = cache.begin(); it != cache.end(); it++)
	{
		if (it->second > maxCnt)
		{
			res = it->first;
			maxCnt = it->second;
			selected = it;
		}
	}
	cache.erase(selected);
}

void EvaluateComponent::ClearErrorCount()
{
	for (int i = 0; i < 5; i++)
	{
		this->errorCount[i] = 0;
	}
}

int EvaluateComponent::PickErrorIndex()
{
	std::vector<std::pair<int, int>> cache;
	for (int i = 0; i < 5; i++)
	{
		if (this->errorCount[i] > 1)
		{
			cache.push_back(std::make_pair(i, this->errorCount[i]));
		}
	}
	if (cache.size() == 0)
		return -1;
	int res = 0;
	int maxCnt = 0;
	for (int i = 0; i < cache.size(); i++)
	{
		if (cache[i]->second > maxCnt)
		{
			res = i;
		}
	}
	return res;
}