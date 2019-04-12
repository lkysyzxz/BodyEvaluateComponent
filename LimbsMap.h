#pragma once
#include "Limbs.h"

class LimbsMap
{

  public:
    static float ErrorThrehold;

  private:
    Limbs *standard;
    Limbs *user;
	  int limbs_num;
	  std::string name;
    float errorValue;

  public:
    void Bind(Limbs *standard_, Limbs *user_, std::string);

    void UpdateErrorValue();

    float GetErrorValue();

    float GetSimilarity();
	  void SetLimbs_Num(int num);
	  int GetLimbs_Num();
	  bool IsError();
	  std::string GetName();
};

