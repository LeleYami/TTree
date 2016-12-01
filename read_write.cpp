/*
*This is a script to show you how to write and read objects by tree
*/

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "Mymath.h"

void write_it(){
   std::cout<<"write it..."<<std::endl;
   //create a new file
   TFile* f=TFile::Open("test.root","recreate");

   //define some simple structures
   typedef struct {
       Float_t x;
   } POINT1;
   static POINT1 point1;
   
   typedef struct{
       Float_t y;
   }POINT2;
   static POINT2 point2;
   
   typedef struct{
       Float_t z;
   }POINT3;
   static POINT3 point3;
   
   //create a root tree
   TTree* t=new TTree("t","A ROOT Tree With a few branches");
   t->Branch("x",&point1,"Float_t x");   
   t->Branch("y",&point2,"Float_t y");   
   t->Branch("z",&point3,"Float_t z");   
   
   //create the objects
   Mymath* obj=new Mymath();
   for(Int_t i=0;i<5;i++){
   obj->SetX(1.23+i);
   obj->SetY(32.1+i);
   obj->SetZ(1.23+i,32.1+i,(1.23+i)*(1.23+i)+(32.1+i)*(32.1+i));

   //fill structures
   point1.x=obj->GetX();
   point2.y=obj->GetY();
   point3.z=obj->GetZ();
   
   //fill the tree
   t->Fill();
   }
   obj->Write("anObject");
   
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
   delete obj;
}

void read_write(){
    write_it();
    read_it();
}

int main(){
    read_write();
}
