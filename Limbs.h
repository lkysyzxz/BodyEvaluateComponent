#pragma once
#include "Joint.h"

class Limbs{
    private:
        Joint* joints[3];
    public:
        void SetJoints(Joint *a,Joint *b,Joint *c){
            joints[0]=a;
            joints[1]=b;
            joints[2]=c;
        }

        Joint** GetJoints(){
            return this->joints;
        }
};