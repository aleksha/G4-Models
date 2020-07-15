#include <fstream>
#include <iostream>
#include <iomanip>

#include "fadc.cc"
#include "histo_funcs.cc"

#include "TGraph.h"
#include "TH1F.h"
#include "TH1S.h"
#include "TH2S.h"
#include "TF1.h"
#include "TSystem.h"
#include "TRandom.h"
#include "TMath.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TVector3.h"
#include "TStyle.h"
#include "TLatex.h"

//bool ADD_NOISE = false;
bool ADD_NOISE = true;
int MY_EVTS    = 100;
double Calib   = 200./151.;
double AnodeGrid = 10.;

TH1F* hFADC[9];
TH1F* hDIFF[9];
TH1F* dDIFF[9];
TH1F* sDIFF[9];
TH1F* hTEMP[9];
TH1F* hDEMP[9];

TH1F* tMax[9];
TH1F* tStart[9];
TH1F* tEnergy[9];
TH1F* tTotal;


fadc_info info[9];


int get_pad2(double x, double y){
    // central pad R = 10 mm
    // other rinrs with width = 40 mm
    // numberinf inner-to-outer

    double l;
    l = sqrt(x*x+y*y);

    if( l>290 && l<=330) return  8;
    if( l>250 && l<=290) return  7;
    if( l>210 && l<=250) return  6;
    if( l>170 && l<=210) return  5;
    if( l>130 && l<=170) return  4;
    if( l> 90 && l<=130) return  3;
    if( l> 50 && l<= 90) return  2;
    if( l> 10 && l<= 50) return  1;
    if( l<= 10)          return  0;

    return -1;
}


void allpads( int Evts=MY_EVTS, bool AddNoise=ADD_NOISE ){

  double I_av = 36.5*0.001*0.001; // MeV --> 36.5 eV to create e-ion pair
  int N_e;
  int N_s=0;

  double l, X, Y, Z, t_anod, d_anod;

  double W1 = 4.0*0.001; // mm/ns
  double z_anod = 0.;

//==============================================================================
// read digitization
//==============================================================================

  double Digi[175];
  int channel ;
  double digi,tt;

  if(AnodeGrid==20.) std::ifstream fDIGI("./Digi2.txt", std::ios::in);
  else               std::ifstream fDIGI("./Digi.txt" , std::ios::in);

  while( fDIGI >> channel >> digi ){
    Digi[channel]=digi;
  }
  fDIGI.close();

//==============================================================================
// read digitization
//==============================================================================

    int ev, vol;
    double dE,x,y,z,t;
    // initial and final space-time points for a step
    double xi,yi,zi,ti,xf,yf,zf,tf;
    double dx, dy, dz, dt;
    double xd, yd; // smeared by transverse diffusion
    double hyd_dE=0;

    int EVENT=0;
    int tEv=0;
    int nToys=0;

    int fpad,dpad;

    std::ifstream fOUT("./out.data" , std::ios::in);
    std::ifstream fNOI("/home/user/Data/Noise/MERGED/noise.data" , std::ios::in);

    TString pFADC,pDIFF,pTEMP,pDEMP;
    TString pdDIFF, psDIFF;
    TString pMax, pStart, pEnergy;

    for(int pad=0;pad<9;pad++){
        if(pad<10){
            pFADC.Form ("hFADS_0%d", pad);
            pDIFF.Form ("hDIFF_0%d", pad);
            pdDIFF.Form ("dDIFF_0%d", pad);
            psDIFF.Form ("sDIFF_0%d", pad);
            pTEMP.Form ("hTEPM_0%d", pad);
            pDEMP.Form ("hDEMP_0%d", pad);
            pMax.Form ("tMax_0%d", pad);
            pEnergy.Form ("tEnergy_0%d", pad);
            pStart.Form ("tStart_0%d", pad);
        }
        else{
            pFADC.Form ("hFADS_%d", pad);
            pDIFF.Form ("hDIFF_%d", pad);
            pdDIFF.Form ("dDIFF_%d", pad);
            psDIFF.Form ("sDIFF_%d", pad);
            pTEMP.Form ("hTEPM_%d", pad);
            pDEMP.Form ("hDEMP_%d", pad);
            pMax.Form ("tMax_%d", pad);
            pEnergy.Form ("tEnergy_%d", pad);
            pStart.Form ("tStart_%d", pad);
        }

        hFADC[pad] = new TH1F( pFADC," ;time, ns; voltage, a.u.", 2550, 0., 40.*2550. );
        hDIFF[pad] = new TH1F( pDIFF," ;time, ns; voltage, a.u.", 2550, 0., 40.*2550. );
        dDIFF[pad] = new TH1F(pdDIFF," ;time, ns; voltage, a.u.", 2550, 0., 40.*2550. );
        sDIFF[pad] = new TH1F(psDIFF," ;time, ns; voltage, a.u.", 2550, 0., 40.*2550. );

        tMax   [pad] = new TH1F(pMax   ," ;time, ns; evts", 400, 47000, 51000 );
        tStart [pad] = new TH1F(pStart ," ;time, ns; evts", 400, 47000, 51000 );
        tEnergy[pad] = new TH1F(pEnergy," ;energy, a.u.; evts", 1300, 0, 130000 );

        hDIFF[pad]->SetLineColor(2);
    }
    tTotal = new TH1F("tTotal"," ;energy, a.u.; evts", 10000, 0, 1000000 );

    TH1F* hd1 = new TH1F("hd1","pad 1; signal length, ns; events",80,2500,2900);

    double Val;

    double Slope;
    int MaxDervBin;

    double cp[1000],fp[1000],mp[1000],ep[1000];
    double TotalE=0;

    while( fOUT >> ev >> vol >> dE >> xi >> yi >> zi >> ti >> xf >> yf >> zf >> tf ){
        if(ev>EVENT){


            for(int p=0;p<9;p++){
                for(int nbin=1;nbin<2694;nbin++){
                    fNOI >> Val;
                    if(nbin<2551 && AddNoise){
                        hFADC[p]->SetBinContent( nbin, hFADC[p]->GetBinContent(nbin) + Val );
                        hDIFF[p]->SetBinContent( nbin, hDIFF[p]->GetBinContent(nbin) + Val );
                    }
                }

                info[p] = eval_info( hDIFF[p] );
                smearTH1(hDIFF[p],sDIFF[p]);
                derivTH1(sDIFF[p],dDIFF[p]);
                MaxDervBin = dDIFF[p]->GetMaximumBin();
                Slope = dDIFF[p]->GetBinContent( MaxDervBin );
                if(info[p].is_fired){
//                    info[p].start = eval_start2( hDIFF[p], info[p] );
//                    info[p].end   = eval_end2  ( hDIFF[p], info[p] );
                    tMax[p]->Fill(info[p].peak);
                    tStart[p]->Fill(info[p].start);
                    tEnergy[p]->Fill(info[p].energy);
                    TotalE += info[p].energy;
//                    std::cout << "----> " << p << "\t" << info[p].energy << "\n";
                }

//                if(p==0) print_info(info[p]) ;
//                std::cout << "pad:" << p << "  "; print_info(info[p]) ;
            }
//            std::cout << "pad: 1\t" << info[1].start << "\t" << info[1].end << "\t\t" << info[1].end-info[1].start << "\n";
            tTotal->Fill(TotalE);

            hd1->Fill(info[1].end-info[1].start);
            cp[EVENT] = info[0].start;
            fp[EVENT] = info[1].start;
            mp[EVENT] = info[1].peak ;
            ep[EVENT] = info[1].end - info[1].start ;

            if( !(ev%10) ) std::cout << "PROCESSED: "<< ev << " events\n";

            if(ev==Evts) break;

            for(int p=0;p<9;p++){
                hFADC[p]->Reset();
                hDIFF[p]->Reset();
                dDIFF[p]->Reset();
                sDIFF[p]->Reset();
            }
            TotalE=0;
            EVENT=ev;
        }


        if(vol==0){
            N_e = int( dE/ I_av );
            if(N_e>0){
                dx = (xf-xi)/N_e;
                dy = (yf-yi)/N_e;
                dz = (zf-zi)/N_e;
                dt = (tf-ti)/N_e;
                N_s = 0;
                for(int ee=0;ee<N_e;ee++){
                    x = xi + 0.5*dx + dx*ee;
                    y = yi + 0.5*dy + dy*ee;
                    z = zi + 0.5*dz + dz*ee;
                    t = ti + 0.5*dt + dt*ee;
                    fpad = get_pad2(x,y);
                    xd = x + gRandom->Gaus(0,0.06*sqrt(z/10.));
                    yd = y + gRandom->Gaus(0,0.06*sqrt(z/10.));
                    dpad = get_pad2(xd,yd);
                    t_anod = (t + (z-z_anod-10.) / W1 ) ;
                    d_anod = (t + (z+gRandom->Gaus(0,0.08*sqrt(z/10.))-z_anod-10.) / W1 ) ;
                    tt = 20;
                    for(int iii = 0 ; iii<125; iii++  ){
                        hFADC[fpad]->Fill(t_anod + tt, Calib*Digi[iii]);
                        hDIFF[dpad]->Fill(d_anod + tt, Calib*Digi[iii]);
                        tt = tt + 40 ;
                    }
                }
            }
        }
    }
    fOUT.close();
    fNOI.close();



    TCanvas* canv = new TCanvas("canv","canv",1200,300);
    gStyle->SetOptStat(0);
    for(int p=0;p<9;p++){
        hFADC[p]->Draw();
        hDIFF[p]->Draw("same");
        if(p<10){pFADC.Form("FADS_0%d.png",p);}
        else{ pFADC.Form("FADS_%d.png",p);}
        canv->Print( pFADC );
    }
    canv->Close();


    TCanvas* canvD = new TCanvas("canvD","canvD",1200,300);
    gStyle->SetOptStat(0);
    for(int p=0;p<9;p++){
        dDIFF[p]->Draw();
        if(p<10){pFADC.Form("dFADS_0%d.png",p);}
        else{ pFADC.Form("dFADS_%d.png",p);}
        canvD->Print( pFADC );
    }
    canvD->Close();


    TFile* f = new TFile("AllPads.root","RECREATE");
    for(int p=0;p<9;p++){
        hFADC[p]->Write();
        hDIFF[p]->Write();
    }
    f->Write();
    f->Close();

    TCanvas* canvT = new TCanvas("canvT","canvT",800,600);
    gStyle->SetOptStat(0);
    for(int p=0;p<9;p++){
        tMax[p]  ->SetLineColor(2);
        tStart[p]->SetLineColor(4);
        tMax[p]  ->SetFillColor(2);
        tStart[p]->SetFillColor(4);
        tMax[p]  ->SetFillStyle(3004);
        tStart[p]->SetFillStyle(3005);
//        tStart[p]->Draw();
        tMax[p]->Draw();
//        tMax[p]->Draw("same");
        tStart[p]->Draw("same");
        std::cout << "Pad " << p << "\t" << tMax[p]->GetMean() << "\t" << tStart[p]->GetMean() << std::endl;
        std::cout << "Pad  \t"           << tMax[p]->GetRMS()  << "\t" << tStart[p]->GetRMS()  << std::endl;
        if(p<10){pFADC.Form("Time_0%d.png",p);}
        else{ pFADC.Form("Time_%d.png",p);}
        canvT->Print( pFADC );
        tEnergy[p]->Draw();
        if(p<10){pFADC.Form("Energy_0%d.png",p);}
        else{ pFADC.Form("Energy_%d.png",p);}
        std::cout << "Pad  \t"  << tEnergy[p]->GetMean()  << "\t" << tEnergy[p]->GetRMS()  << std::endl;
        canvT->Print( pFADC );
    }
    canvD->Close();

    TGraph* gp = new TGraph(Evts,cp,fp);
    TGraph* gc = new TGraph(Evts,mp,fp);
    TGraph* ge = new TGraph(Evts,ep,fp);
    gp->SetMarkerStyle(20);
    gc->SetMarkerStyle(24);
    ge->SetMarkerStyle(21);
    gp->SetTitle("Central vs 1st pad");
    gc->SetTitle("Pad 1: start vs peak");
    ge->SetTitle("Pad 1: start vs length");
    TCanvas* canvS = new TCanvas("canvS","canvS",800,800);
    gStyle->SetOptStat(0);
    gp->Draw("ap");
    canvS->Print( "Scatter_0vs1.png" );
    gc->Draw("ap");
    canvS->Print( "Corr_PEAKvsSTART.png" );
    ge->Draw("ap");
    canvS->Print( "Corr_LENGTHvsSTART.png" );
    canvS->Close();


    TH1F* hA = new TH1F("hA",";angle, deg.; Events", 200,-10,10);
    for(int e=0;e<Evts;e++){
        hA->Fill( atan( (fp[e]-cp[e])*W1/25. )*180./3.14159265);
    }
    TCanvas* canvA = new TCanvas("canvA","canvA",800,800);
    hA->SetLineWidth(2);
    hA->SetLineColor(1);
    hA->SetFillColor(1);
    hA->SetFillStyle(3005);
    hA->Draw();
    std::cout << "mean : " << hA->GetMean() << "\t rms : " << hA->GetRMS() << "\n";
    canvA->Print( "Angle_0vs1.png" );
    canvA->Close();

    TCanvas* canvW = new TCanvas("canvW","canvW",800,800);
    hd1->SetLineWidth(2);
    hd1->SetLineColor(2);
    hd1->SetFillColor(2);
    hd1->SetFillStyle(3004);
    hd1->Draw();
    std::cout << "mean : " << hd1->GetMean() << "\t rms : " << hd1->GetRMS() << "\n";
    canvW->Print( "Length_01.png" );
    canvW->Close();

    std::cout << "Energy: " << tTotal->GetMean() << " +- " << tTotal->GetRMS() << "\n";

    gSystem->Exit(0);

}
