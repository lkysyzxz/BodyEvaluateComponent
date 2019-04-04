#include <math.h>
class Quaternion{
  private:
    static float Pow2(float x){return x*x;}
    
    static float Sqrt(float x){return sqrt(x);}
  
  public:
  
    static Quaternion MakeFromMatrix(){
    }

    static float DistanceBetween(const Quaternion &a, const Quaternion &b){
        return Sqrt(Pow2(a.x - b.x) + Pow2(a.y - b.y) + Pow2(a.z - b.z) + Pow2(a.w - b.w));
    }

  private:
    float x;
    float y;
    float z;
    float w;
  public:
    Quaternion(float _x = 0.0f,float _y = 0.0f,float _z = 0.0f ,float _w = 1.0f)
      :x(_x),y(_y),z(_z),w(_w){
    }
};