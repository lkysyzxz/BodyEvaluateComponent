#include "LimbsMap.h"
#include "Body.h"
class EvaluteComponent{
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
  public:
    EvaluteComponent(Body *standard,Body *user){
      this->bodyMap.Bind(standard->GetBody(),user->GetBody());
      this->leftArmMap.Bind(standard->GetLeftArm(), user->GetLeftArm());
      this->rightArmMap.Bind(standard->GetRightArm(),user->GetRightArm());
      this->leftLegMap.Bind(standard->GetLeftLeg(),user->GetLeftLeg());
      this->rightLegMap.Bind(standard->GetRightLeg(),user->GetRightLeg());
    }

    void Compare(){
      
    }
};