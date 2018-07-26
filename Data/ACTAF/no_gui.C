#include "tpc_event.C"

TTree* h101;
tpcEvent *EVENT;
int fEventNumber =  2; // 
int fAnodNumber  = 66; // 
int fAnod1Number = 65; // 
int fAnod2Number = 66; // 
int fWindowWidth = 10; // 
double fThreshold   = 1.02; // 

void DoLoad(int evnt)
{
  Int_t hi;
  Double_t hx,hy;
  cout << "EVENT : " << evnt << "\n";
  EVENT->Reset();
  EVENT->SetEventNumber(evnt);
  EVENT->SetWindowWidth( fWindowWidth );
  EVENT->SetThresholdFactor( fThreshold );
  auto c2 = new TCanvas("cnvs2", "Traces", 1920, 1080);
  c2->Divide(10,7);
  gStyle->SetOptStat(0);
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
        EVENT->SetChannel(i,hx,hy);
      }
    }
  }
  EVENT->CheckAll();
  EVENT->Print();
  EVENT->DrawDisplay();
  c2->Close();
  Printf("Loaded");
}

void no_gui(TString file_name = "/home/user/Data/TPC/gen_0080.root")
{
   DoLoad(fEventNumber);
   gSystem->Exit(0);
}