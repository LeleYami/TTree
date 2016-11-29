#include <iostream>
#include "../include/TObject.h"

class Mymath:public TObject{
  private:
     Float_t px;
     Float_t py;
     Float_t pz;
  public:
     Mymath() { px = py = pz = 0; }
     
     void SetX(float x) {
           px=x;
           }
     float GetX(){
           return px;
           }
     
     void SetY(float y) {
           py=y; 
           }
     float GetY(){
           return py;
           }
  
     void SetZ(float x,float y,float z) {
           if(z==x*x+y*y){
             pz=z;
             }
           }
     float GetZ() {
           return pz;
           } 
  
     void Print() const;

ClassDef(Mymath,1) 
};
