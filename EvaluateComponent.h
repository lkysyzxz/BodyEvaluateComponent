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
  public:

    EvaluateComponent(Body *standard,Body *user);

    LimbsMap *Compare();
};