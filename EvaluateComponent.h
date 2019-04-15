#pragma once
#include "LimbsMap.h"
#include "Body.h"

class EvaluateComponent{
  private:
    static float ErrorValueThrehold;
  private:
    // Body standard;
    // Body user;
    LimbsMap bodyMap;
    LimbsMap leftArmMap;
    LimbsMap rightArmMap;
    LimbsMap leftLegMap;
    LimbsMap rightLegMap;
    LimbsMap* mapping[5];

    LimbsMap *lastErrorLimbs;

    int errorCount[5];
    int lastExtractSide;
    std::vector<int> missCache;
    
  public:

    EvaluateComponent(Body *standard,Body *user);

    LimbsMap *Compare();

    void SamplingErrorBone();

    LimbsMap *ExtractErrorBone();

  private:
    void ClearErrorCount();
    
    std::vector<std::pair<int,int>> FiltErrorCount();

    int GetSide(int num);
    
    int PickErrorIndex(std::vector<std::pair<int,int>> &vec);

    int PickErrorIndex();
};