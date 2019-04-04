#include "Quaternion.h"
class Joint{
  private:
    Quaternion rotation;
  public:
    Joint(){
        
    }

    Joint(const Quaternion &rot):rotation(rot){

    }

    const Quaternion& GetRotation(){
      return this->rotation;
    }
    
    void SetRotateion(const Quaternion &value){
        this->rotation = value;
    }
};