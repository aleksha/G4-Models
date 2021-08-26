#define PROCESS 500

#include "TTree.h"
#include "TFile.h"
#include "TGraph.h"
#include "TStyle.h"
#include "TSystem.h"

#include <fstream>
#include <iostream>
using namespace std;

#include "tpc_event.C"


TTree* h101;
tpcEvent *EVENT= new tpcEvent();;
int fEventNumber   =  2; //
int fSector        = 15; //
int fAnodNumber    = 66; //
int fAnod1Number   = 65; //
int fAnod2Number   = 66; //
int fWindowWidth   = 10; //
double fThreshold  =  1.02; //

TCanvas* c2 ;


void DoLoad(int evnt, bool  draw, int anode, int a1, int a2, int sct)
{
  Int_t hi;
  Double_t hx,hy;

  if(!(evnt%20)) cout << "EVENT PROCESSED : " << evnt << "\n";

//  EVENT->Reset();
//  EVENT->SetEventNumber(evnt);
//  EVENT->SetWindowWidth( fWindowWidth );
//  EVENT->SetThresholdFactor( fThreshold );


  int padno = 1;
  for (int i = 1; i <= 69; i++) {
    if (true) {
      int fadc = ((int) (i-1)/16) + 1;
      int ch = i - fadc*16 + 16;
      char *hist = new char[256];
      sprintf(   hist, "at_a%dc%dsv:at_a%dc%dsI", fadc, ch, fadc, ch);
      c2->cd(padno);
      h101->Draw(hist, "", "L", 1, evnt);
      padno++;
      TGraph *gtemp = (TGraph*)gPad->GetPrimitive("Graph");
      for(int jj=0;jj<gtemp->GetN(); jj++ ){
        hi = gtemp->GetPoint(jj,hx,hy);
//        EVENT->SetChannel(i,hx,hy);
      }
    }
  }

//  EVENT->CheckAll();

  //Printf("Loaded");
}

//void no_gui(TString file_name = "/home/user/Data/TPC/gen_0080.root")
void no_gui2(TString file_name = "./alp_0290.root")
{
   c2 = new TCanvas("cnvs2", "Traces", 1920, 1080);
   c2->Divide(10,7);
   gStyle->SetOptStat(0);

   TFile *oldfile  = new TFile(file_name);
   h101 = (TTree*)oldfile->Get("h101");

//   DoLoad(fEventNumber, true, fAnodNumber, fAnod1Number, fAnod2Number, fSector);
   for(int ev=0; ev<PROCESS;ev++)
     DoLoad(ev,false,66,65,66,16);

   c2->Close();
   gSystem->Exit(0);
}
