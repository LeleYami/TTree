#include <iostream>
#include "../include/TObject.h"

class Mymath:public TObject{
  private:
     Float_t px;
     Float_t py;
     Float_t pz;
  public:
     Mymath() { px = py = pz = 0; }
     void Print() const;
     void SetX(float x) { px=x; }
     void SetY(float y) { py=y; }
     void SetZ(float z) { pz=z; }
     void SetZ(float x,float y,float z) { z=x*x+y*y; } 

ClassDef(Mymath,1) 
};
