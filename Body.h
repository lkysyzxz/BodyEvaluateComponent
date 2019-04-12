#pragma once
#include "Limbs.h"

class Body
{
  private:
    Joint spine;
    Joint chest;
    Joint head;

    Joint leftShoulder;
    Joint leftElbow;
    Joint leftWrist;

    Joint rightShoulder;
    Joint rightElbow;
    Joint rightWrist;

    Joint leftThigh;
    Joint leftKnee;
    Joint leftAnkle;

    Joint rightThigh;
    Joint rightKnee;
    Joint rightAnkle;

    Limbs body;
    Limbs leftArm;
    Limbs rightArm;
    Limbs leftLeg;
    Limbs rightLeg;

  public:
    Body(){
		SetupLimbs();
    }

	void SetupLimbs() {
		body.SetJoints(&spine, &chest, &head);
		leftArm.SetJoints(&leftShoulder, &leftElbow, &leftWrist);
		rightArm.SetJoints(&rightShoulder, &rightElbow, &rightWrist);
		leftLeg.SetJoints(&leftThigh, &leftKnee, &leftAnkle);
		rightLeg.SetJoints(&rightThigh, &rightKnee, &rightAnkle);
	}
    Limbs* GetBody(){
        return &this->body;
    }

    Limbs* GetLeftArm(){
        return &this->leftArm;
    }

    Limbs* GetRightArm(){
        return &this->rightArm;
    }

    Limbs* GetLeftLeg(){
        return &this->leftLeg;
    }

    Limbs* GetRightLeg(){
        return &this->rightLeg;
    }

    Joint* GetSpine(){
        return &this->spine;
    }

    Joint* GetChest(){
        return &this->chest;
    }

    Joint* GetHead(){
        return &this->head;
    }

    Joint* GetLeftShoulder(){
        return &this->leftShoulder;
    }

    Joint* GetLeftElbows(){
        return &this->leftElbow;
    }

    Joint* GetLeftWrist(){
        return &this->leftWrist;
    }

    Joint* GetRightShoulder(){
        return &this->rightShoulder;
    }

    Joint* GetRightElbows(){
        return &this->rightElbow;
    }

    Joint* GetRightWrist(){
        return &this->rightWrist;
    }

    Joint* GetLeftThigh(){
        return &this->leftThigh;
    }

    Joint* GetLeftKnee(){
        return &this->leftKnee;
    }

    Joint* GetLeftAnkle(){
        return &this->leftAnkle;
    }

    Joint* GetRightThigh(){
        return &this->rightThigh;
    }

    Joint* GetRightKnee(){
        return &this->rightKnee;
    }

    Joint* GetRightAnkle(){
        return &this->rightAnkle;
    }
};