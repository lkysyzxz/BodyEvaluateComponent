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
    void Bind(Limbs *standard_, Limbs *user_);

    void UpdateErrorValue();

    float GetErrorValue();

    float GetSimilarity();
};

