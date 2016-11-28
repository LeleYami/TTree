/*
*This is a script to show you how to write and read objects by tree
*/

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "Mymath.h"
#include "TRandom.h"

void write_it(){
   std::cout<<"write it..."<<std::endl;
   //create a new file
   TFile* f=TFile::Open("test.root","recreate");

   //define some simple structures
   typedef struct {
       Float_t x,y,z;
   } POINT;
   static POINT point;

   //create a root tree
   TTree* t=new TTree("t","A ROOT Tree With a few branches");
   t->Branch("point",&point,"x:y:z");   
   
   Float_t px,py,pz;
   static Float_t p[3];
   
   //create the objects
   Mymath* obj=new Mymath();
   obj->SetX(1.23);
   px=1.23;
   obj->SetY(32.1);
   py=32.1;
   obj->SetZ(1.23,32.1,1.23*1.23+32.1*32.1);
   pz=1.23,32.1,1.23*1.23+32.1*32.1;
   obj->Write("anObject");

   //fill the tree
   p[0]=px;
   p[1]=py;
   p[2]=pz; 
   point.x=1;
   point.y=2;
   point.z=3;
   
   //fill the tree
   t->Fill();

   //save all objects in this file 
   f->Write();

   //close the file
   f->Close();
   std::cout<<"write it done"<<std::endl;
}

void read_it(){
   std::cout<<"read it..."<<std::endl;
   //open the file
   TFile* f=TFile::Open("test.root");
   if(!f){
      std::cerr<<"Can't open file test.root"<<std::endl;
      return; 
   }

   Mymath* obj=dynamic_cast<Mymath*>(f->Get("anObject"));
   if(!obj){
      std::cerr<<"Can't find the object anObject"<<std::endl;
      return;
   }   

   //open the tree
   TTree* t=(TTree*)f->Get("t");
   if(!t){
      std::cerr<<"Can't find the tree t."<<std::endl;
      return;
   }   
   //print entries from the tree
   Int_t nentries=(Int_t)t->GetEntries();
   for(Int_t i=0;i<nentries;i++){
      t->GetEntry(i);
      t->Print();
   }

   obj->Print();
   std::cout<<"read it done."<<std::endl;   
}

void read_write(){
    write_it();
    read_it();
}

int main(){
    read_write();
}
