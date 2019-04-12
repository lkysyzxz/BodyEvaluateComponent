#pragma once
#include "Quaternion.h"
#include <fbxsdk.h>

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
	FbxAMatrix AddError() {
		return rotation.Quat2DCM();
	}
    void SetRotateion(const Quaternion &value){
        this->rotation = value;
    }
	void SetRotateion(const FbxAMatrix &matrix) {
		rotation.DCM2Quat(matrix);
	}
};