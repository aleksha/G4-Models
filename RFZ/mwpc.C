#include <fstream>
#include <iostream>
#include <iomanip>

#include "fadc.cc"
#include "histo_funcs.cc"

#include "TGraph.h"
#include "TH1F.h"
#include "TH1S.h"
#include "TH2F.h"
#include "TF1.h"
#include "TSystem.h"
#include "TRandom.h"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TVector3.h"
#include "TStyle.h"
#include "TLatex.h"

TH2F* hCSC;
TTree* out;
TFile *tfile;

void mwpc(){

    int ev, vol, trk;
    double dE,x,y,z,t;
    // initial and final space-time points for a step
    double xi,yi,zi,ti,xf,yf,zf,tf;

    int EVENT=0;
    int nHits[6]={0,0,0,0,0,0};
    double dElist[10];
    int hits=0;


    std::ifstream fCSC("./csc.data" , std::ios::in);


    out = new TTree("out","out");
    Float_t xCSC; out->Branch("xCSC" ,&xCSC , "xCSC/F"  );
    Float_t yCSC; out->Branch("yCSC" ,&yCSC , "yCSC/F"  );
    Int_t  evCSC; out->Branch("evCSC",&evCSC, "evCSC/I" );

//    hCSC = new TH2F("hCSC","; x, mm; y, mm",60000,-300., 300., 60000, -300., 300.);


    while( fCSC >> ev >> vol >> dE >> trk >> xi >> yi >> zi >> ti >> xf >> yf >> zf >> tf ){
        if(ev>EVENT){
          if( ev-EVENT == 2) nHits[0]++  ;
          if( ev-EVENT == 3) nHits[0]+=2 ;

          if(hits>4) hits = 4;
          nHits[hits]++;

          evCSC = EVENT;
          out->Fill();

          hits=0;
          xCSC = 0; yCSC=0;
//          hCSC->Reset();
          EVENT=ev;
        }

        if(vol==5 && trk==2){
          hits++;
          if(xCSC<=0 && yCSC<=0){
            xCSC =  (xf+xi)/2. ;
            yCSC =  (yf+yi)/2. ;
          }
//          hCSC->Fill( (xf-xi)/2., dE) ;
//          hCSC->Fill( (yf-yi)/2., dE) ;
        }

//        if(vol==5 && trk!=2 && ev<1000)
//          std::cout << "--> " << ev << "\n";

    }

//---- LAST EVENT ----
    if(hits>3) hits = 3;
    nHits[hits]++;
    evCSC = EVENT;
    out->Fill();
    fCSC.close();
//---- LAST EVENT ----

    std::cout << "\n\n =============\n" ;
    std::cout <<     " CSC summary :\n" ;
    std::cout <<     " =============\n" ;
    int nTot = 0;
    for(int h=0;h<5;h++){
      nTot += nHits[h];
      std::cout << "\t" << h << " hits: " << nHits[h] << "\n";
    }
    std::cout << "----------------------------\n";
    std::cout << "\t" << "  Total: " << nTot << " events\n\n";


    tfile = new TFile("csc.root","RECREATE");
    out->Write();
    tfile->Write();
    tfile->Close();

/*
    TCanvas* canv = new TCanvas("canv","canv",1200,300);
    gStyle->SetOptStat(0);
    for(int p=0;p<9;p++){
//        hFADC[p]->SetFillColor(1);
//        hFADC[p]->GetXaxis()->SetRangeUser(47000,50000);
        hFADC[p]->Draw("hist");
        hDIFF[p]->Draw("same");
        if(p<10){pFADC.Form("FADS_0%d.png",p);}
        else{ pFADC.Form("FADS_%d.png",p);}
        canv->Print( pFADC );
    }
    canv->Close();
*/

    gSystem->Exit(0);

}
