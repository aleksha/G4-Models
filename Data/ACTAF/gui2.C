#include <TApplication.h>
#include <TGClient.h>
#include <TGButton.h>
#include <TGLabel.h>
#include <TGResourcePool.h>

#include "tpc_event.C"


class GUIWindow {
private:
   TGMainFrame    *fMain       ; // main frame
   TGNumberEntry  *fEventNumber; // 
   TGNumberEntry  *fAnodNumber ; // 
   TGNumberEntry  *fAnod1Number; // 
   TGNumberEntry  *fAnod2Number; // 
   TGNumberEntry  *fWindowWidth; // 
   TGNumberEntry  *fThreshold  ; // 
   tpcEvent *EVENT;

public:
   GUIWindow(TString file_name);
   virtual ~GUIWindow();

   void DoLoad();
   void DoFind();
   void DoAll();
   void DrawDisplay();
   void DrawAnod();
   void DrawPair();
   void DrawCentral();

   void DoSec01();
   void DoSec02();
   void DoSec03();
   void DoSec04();
   void DoSec05();
   void DoSec06();
   void DoSec07();
   void DoSec08();
   void DoSec09();
   void DoSec10();
   void DoSec11();
   void DoSec12();
   void DoSec13();
   void DoSec14();
   void DoSec15();
   void DoSec16();

   TTree* h101;

   ClassDef(GUIWindow, 0);
};


//______________________________________________________________________________
GUIWindow::~GUIWindow()
{
   // Destructor.
   delete fMain;
}
//______________________________________________________________________________
void GUIWindow::DoLoad()
{
  Int_t hi;
  Double_t hx,hy;
  int evnt = fEventNumber->GetNumberEntry()->GetIntNumber();
  cout << "EVENT : " << evnt << "\n";
  EVENT->Reset();
  EVENT->SetEventNumber(evnt);
  EVENT->SetWindowWidth( fWindowWidth->GetNumberEntry()->GetIntNumber() );
  EVENT->SetThresholdFactor( fThreshold->GetNumberEntry()->GetNumber() );
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
//______________________________________________________________________________
void GUIWindow::DoFind()
{ 
  EVENT->SetWindowWidth( fWindowWidth->GetNumberEntry()->GetIntNumber() );
  EVENT->SetThresholdFactor( fThreshold->GetNumberEntry()->GetNumber() );

  EVENT->Print();
  EVENT->CheckAll();
  EVENT->DrawDisplay();
  Printf("Display Updated");
}
//______________________________________________________________________________
void GUIWindow::DrawDisplay()
{
  EVENT->DrawDisplay();
  Printf("Display Updated");
}
//______________________________________________________________________________
void GUIWindow::DrawAnod()
{
  EVENT->DrawHist(fAnodNumber->GetNumberEntry()->GetIntNumber());
  Printf("Display Updated");
}
//______________________________________________________________________________
void GUIWindow::DrawPair()
{
  EVENT->DrawTwo(fAnod1Number->GetNumberEntry()->GetIntNumber(),
                 fAnod2Number->GetNumberEntry()->GetIntNumber());
  Printf("Display Updated");
}
//______________________________________________________________________________
void GUIWindow::DrawCentral()
{
  EVENT->DrawTwo(65,66);
  Printf("Display Updated");
}
//______________________________________________________________________________
void GUIWindow::DoAll()
{
  EVENT->DrawAll();
  Printf("Display Updated");
}//______________________________________________________________________________
void GUIWindow::DoSec01(){ EVENT->DrawSector(  1 ); Printf("Display Updated"); }
void GUIWindow::DoSec02(){ EVENT->DrawSector(  2 ); Printf("Display Updated"); }
void GUIWindow::DoSec03(){ EVENT->DrawSector(  3 ); Printf("Display Updated"); }
void GUIWindow::DoSec04(){ EVENT->DrawSector(  4 ); Printf("Display Updated"); }
void GUIWindow::DoSec05(){ EVENT->DrawSector(  5 ); Printf("Display Updated"); }
void GUIWindow::DoSec06(){ EVENT->DrawSector(  6 ); Printf("Display Updated"); }
void GUIWindow::DoSec07(){ EVENT->DrawSector(  7 ); Printf("Display Updated"); }
void GUIWindow::DoSec08(){ EVENT->DrawSector(  8 ); Printf("Display Updated"); }
void GUIWindow::DoSec09(){ EVENT->DrawSector(  9 ); Printf("Display Updated"); }

void GUIWindow::DoSec10(){ EVENT->DrawSector( 10 ); Printf("Display Updated"); }
void GUIWindow::DoSec11(){ EVENT->DrawSector( 11 ); Printf("Display Updated"); }
void GUIWindow::DoSec12(){ EVENT->DrawSector( 12 ); Printf("Display Updated"); }
void GUIWindow::DoSec13(){ EVENT->DrawSector( 13 ); Printf("Display Updated"); }
void GUIWindow::DoSec14(){ EVENT->DrawSector( 14 ); Printf("Display Updated"); }
void GUIWindow::DoSec15(){ EVENT->DrawSector( 15 ); Printf("Display Updated"); }
void GUIWindow::DoSec16(){ EVENT->DrawSector( 16 ); Printf("Display Updated"); }
//______________________________________________________________________________
GUIWindow::GUIWindow(TString file_name)
{
   // Main Canvas
   EVENT   = new tpcEvent();
   
   // Main Window.
   fMain = new TGMainFrame(gClient->GetRoot(), 10, 10, kVerticalFrame);
   fMain->SetCleanup(kDeepCleanup); // delete all subframes on exit

   // Create Frames
   TGHorizontalFrame *event_frame = new TGHorizontalFrame(fMain);
   fMain->AddFrame(event_frame, new TGLayoutHints(kLHintsLeft, 1, 1, 1, 1));
   TGHorizontalFrame *sec_frame = new TGHorizontalFrame(fMain);
   fMain->AddFrame(sec_frame, new TGLayoutHints(kLHintsLeft, 1, 1, 1, 1));
   TGHorizontalFrame *anod_frame = new TGHorizontalFrame(fMain);
   fMain->AddFrame(anod_frame, new TGLayoutHints(kLHintsLeft, 1, 1, 1, 1));

   // Event Frame
   TGLabel *eventLabel = new TGLabel(event_frame, "Event:");
   event_frame->AddFrame(eventLabel, new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 
                          5, 2, 2, 2));

   fEventNumber = new TGNumberEntry(event_frame, 0, 4, 999, 
                                    TGNumberFormat::kNESInteger,
                                    TGNumberFormat::kNEANonNegative, 
                                    TGNumberFormat::kNELLimitMinMax, 0, 9999);


   event_frame->AddFrame(fEventNumber, new TGLayoutHints(kLHintsTop | kLHintsLeft,
                         5, 5, 5, 5));

   TGTextButton *load = new TGTextButton(event_frame, "&Load");
   load->Connect("Clicked()", "GUIWindow", this, "DoLoad()");
   event_frame->AddFrame(load, new TGLayoutHints(kLHintsCenterY  | kLHintsLeft, 5, 5, 3, 4));

   TGLabel *windowLabel = new TGLabel(event_frame, "Window:");
   event_frame->AddFrame(windowLabel, new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 
                          5, 2, 2, 2));

   fWindowWidth = new TGNumberEntry(event_frame, 10, 4, 998, 
                                    TGNumberFormat::kNESInteger,
                                    TGNumberFormat::kNEANonNegative, 
                                    TGNumberFormat::kNELLimitMinMax, 0, 999);

   fWindowWidth->SetNumber( EVENT->GetWindowWidth() );
   event_frame->AddFrame(fWindowWidth, new TGLayoutHints(kLHintsCenterY  | kLHintsLeft,
                         5, 5, 5, 5));


   TGLabel *thresholdLabel = new TGLabel(event_frame, "Threshold:");
   event_frame->AddFrame(thresholdLabel, new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 
                          5, 2, 2, 2));

   fThreshold = new TGNumberEntry(event_frame, 10, 4, 999, 
                                    TGNumberFormat::kNESReal,
                                    TGNumberFormat::kNEANonNegative, 
                                    TGNumberFormat::kNELLimitMinMax, 1.0, 100.0);

   fThreshold->SetNumber( EVENT->GetThresholdFactor() );
   event_frame->AddFrame(fThreshold, new TGLayoutHints(kLHintsCenterY  | kLHintsLeft,
                         5, 5, 5, 5));




   TGTextButton *find = new TGTextButton(event_frame, "&Find Hits");
   find->Connect("Clicked()", "GUIWindow", this, "DoFind()");
   event_frame->AddFrame(find, new TGLayoutHints(kLHintsCenterY  | kLHintsLeft, 5, 5, 3, 4));

   TGTextButton *sall = new TGTextButton(event_frame, "&ShowAll");
   sall->Connect("Clicked()", "GUIWindow", this, "DoAll()");
   event_frame->AddFrame(sall, new TGLayoutHints(kLHintsCenterY  | kLHintsLeft, 5, 5, 3, 4));

   TGTextButton *disp = new TGTextButton(event_frame, "&Anod Display");
   disp->Connect("Clicked()", "GUIWindow", this, "DrawDisplay()");
   event_frame->AddFrame(disp, new TGLayoutHints(kLHintsCenterY  | kLHintsLeft, 5, 5, 3, 4));

   // Event Frame
   TGLabel *secLabel = new TGLabel(sec_frame, "Draw sector");
   sec_frame->AddFrame(secLabel, new TGLayoutHints(kLHintsCenterY | kLHintsLeft,
                          5, 2, 2, 2));

   TGTextButton *s01 = new TGTextButton(sec_frame, "&01");
   TGTextButton *s02 = new TGTextButton(sec_frame, "&02");
   TGTextButton *s03 = new TGTextButton(sec_frame, "&03");
   TGTextButton *s04 = new TGTextButton(sec_frame, "&04");
   TGTextButton *s05 = new TGTextButton(sec_frame, "&05");
   TGTextButton *s06 = new TGTextButton(sec_frame, "&06");
   TGTextButton *s07 = new TGTextButton(sec_frame, "&07");
   TGTextButton *s08 = new TGTextButton(sec_frame, "&08");
   TGTextButton *s09 = new TGTextButton(sec_frame, "&09");
   TGTextButton *s10 = new TGTextButton(sec_frame, "&10");
   TGTextButton *s11 = new TGTextButton(sec_frame, "&11");
   TGTextButton *s12 = new TGTextButton(sec_frame, "&12");
   TGTextButton *s13 = new TGTextButton(sec_frame, "&13");
   TGTextButton *s14 = new TGTextButton(sec_frame, "&14");
   TGTextButton *s15 = new TGTextButton(sec_frame, "&15");
   TGTextButton *s16 = new TGTextButton(sec_frame, "&16");

   s01->Connect("Clicked()", "GUIWindow", this, "DoSec01()");
   s02->Connect("Clicked()", "GUIWindow", this, "DoSec02()");
   s03->Connect("Clicked()", "GUIWindow", this, "DoSec03()");
   s04->Connect("Clicked()", "GUIWindow", this, "DoSec04()");
   s05->Connect("Clicked()", "GUIWindow", this, "DoSec05()");
   s06->Connect("Clicked()", "GUIWindow", this, "DoSec06()");
   s07->Connect("Clicked()", "GUIWindow", this, "DoSec07()");
   s08->Connect("Clicked()", "GUIWindow", this, "DoSec08()");
   s09->Connect("Clicked()", "GUIWindow", this, "DoSec09()");
   s10->Connect("Clicked()", "GUIWindow", this, "DoSec10()");
   s11->Connect("Clicked()", "GUIWindow", this, "DoSec11()");
   s12->Connect("Clicked()", "GUIWindow", this, "DoSec12()");
   s13->Connect("Clicked()", "GUIWindow", this, "DoSec13()");
   s14->Connect("Clicked()", "GUIWindow", this, "DoSec14()");
   s15->Connect("Clicked()", "GUIWindow", this, "DoSec15()");
   s16->Connect("Clicked()", "GUIWindow", this, "DoSec16()");

   sec_frame->AddFrame(s01, new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 3, 4));
   sec_frame->AddFrame(s02, new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 3, 4));
   sec_frame->AddFrame(s03, new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 3, 4));
   sec_frame->AddFrame(s04, new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 3, 4));
   sec_frame->AddFrame(s05, new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 3, 4));
   sec_frame->AddFrame(s06, new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 3, 4));
   sec_frame->AddFrame(s07, new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 3, 4));
   sec_frame->AddFrame(s08, new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 3, 4));
   sec_frame->AddFrame(s09, new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 3, 4));
   sec_frame->AddFrame(s10, new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 3, 4));
   sec_frame->AddFrame(s11, new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 3, 4));
   sec_frame->AddFrame(s12, new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 3, 4));
   sec_frame->AddFrame(s13, new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 3, 4));
   sec_frame->AddFrame(s14, new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 3, 4));
   sec_frame->AddFrame(s15, new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 3, 4));
   sec_frame->AddFrame(s16, new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 3, 4));

   // Anod Frame
   TGLabel *anodLabel = new TGLabel(anod_frame, "Anod");
   anod_frame->AddFrame(anodLabel, new TGLayoutHints(kLHintsCenterY | kLHintsLeft,
                          5, 2, 2, 2));
   fAnodNumber = new TGNumberEntry(anod_frame, 1, 2,8,
                                    TGNumberFormat::kNESInteger,
                                    TGNumberFormat::kNEANonNegative,
                                    TGNumberFormat::kNELLimitMinMax, 1, 66);
   anod_frame->AddFrame(fAnodNumber, new TGLayoutHints(kLHintsCenterY | kLHintsLeft,
                         5, 5, 5, 5));


   TGTextButton *anod = new TGTextButton(anod_frame, "&Draw");
   anod->Connect("Clicked()", "GUIWindow", this, "DrawAnod()");
   anod_frame->AddFrame(anod, new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 5, 5, 3, 4));


   TGLabel *anod1Label = new TGLabel(anod_frame, "A1");
   anod_frame->AddFrame(anod1Label, new TGLayoutHints(kLHintsCenterY | kLHintsLeft,
                          5, 2, 2, 2));
   fAnod1Number = new TGNumberEntry(anod_frame, 1, 2,8,
                                    TGNumberFormat::kNESInteger,
                                    TGNumberFormat::kNEANonNegative,
                                    TGNumberFormat::kNELLimitMinMax, 1, 66);
   anod_frame->AddFrame(fAnod1Number, new TGLayoutHints(kLHintsCenterY | kLHintsLeft,
                         5, 5, 5, 5));

   TGLabel *anod2Label = new TGLabel(anod_frame, "A2");
   anod_frame->AddFrame(anod2Label, new TGLayoutHints(kLHintsCenterY | kLHintsLeft,
                          5, 2, 2, 2));
   fAnod2Number = new TGNumberEntry(anod_frame, 1, 2,8,
                                    TGNumberFormat::kNESInteger,
                                    TGNumberFormat::kNEANonNegative,
                                    TGNumberFormat::kNELLimitMinMax, 1, 66);
   anod_frame->AddFrame(fAnod2Number, new TGLayoutHints(kLHintsCenterY | kLHintsLeft,
                         5, 5, 5, 5));


   TGTextButton *pair = new TGTextButton(anod_frame, "&Draw pair");
   pair->Connect("Clicked()", "GUIWindow", this, "DrawPair()");
   anod_frame->AddFrame(pair, new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 5, 5, 3, 4));

   TGTextButton *cent = new TGTextButton(anod_frame, "&Draw central");
   cent->Connect("Clicked()", "GUIWindow", this, "DrawCentral()");
   anod_frame->AddFrame(cent, new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 5, 5, 3, 4));

   // Final Magic

   TFile *oldfile  = new TFile(file_name);
   h101 = (TTree*)oldfile->Get("h101");
   // Final Magic
   fMain->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
   fMain->DontCallClose();

   fMain->MapSubwindows();
   fMain->Resize(600, 100);

   // set  minimum size of main window
   fMain->SetWMSizeHints(event_frame->GetDefaultWidth(),
                         fMain->GetDefaultHeight(), 1000, 1000, 0 ,0);

   fMain->SetWindowName("ACTAF");
   fMain->MapRaised();
}

////////////////////////////////////////////////////////////////////////////////
void gui2(TString file_name = "/home/user/Data/TPC/gen_0080.root")
{
   // Main program.
   //TString file_name = "beam_2245_300evnt.root";
   new GUIWindow(file_name);
}

