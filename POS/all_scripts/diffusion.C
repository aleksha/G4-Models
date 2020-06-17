#include <fstream>
#include <iostream>
#include <iomanip>

#include "TH1F.h"
#include "TH1S.h"
#include "TH2S.h"
#include "TF1.h"
#include "TSystem.h"
#include "TRandom.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TVector3.h"
#include "TStyle.h"
#include "TLatex.h"

void diffusion(double Position = 250., int Evts=100000){

  double I_av = 36.5*0.001*0.001; // MeV --> 36.5 eV to create e-ion pair
  int N_e;
  int N_s=0;

  double l, X, Y, Z, t_anod, d_anod;

  double w_f = 1.0 ;
  double scaling_factor = 1.00 ;
  double W1 = w_f*scaling_factor*4.0*0.001; // mm/ns
  double z_anod = 0.;

//==============================================================================
// read digitization
//==============================================================================

  double Digi[175];
  int channel ;
  double digi,tt;

    std::ifstream fDIGI("./Digi.txt" , std::ios::in);

    while( fDIGI >> channel >> digi ){
      Digi[channel]=digi;
    }
    fDIGI.close();

//==============================================================================
// read digitization
//==============================================================================

    int ev, vol;
    double dE,x,y,z,t;
    double xi,yi,zi,xf,yf,zf;
    double dx, dy, dz;

    double sc1_dE=0;
    double sc2_dE=0;
    double hyd_dE=0;

    int EVENT=0;
    int tEv=0;
    int nToys=0;

    std::ifstream fOUT("./out.data" , std::ios::in);

    TH1F* hMean = new TH1F("hMean"," Mean;time; Toys", 2000, 8100., 8300. );
    TH1F* hMea2 = new TH1F("hMea2"," Mean;time; Toys", 2000, 8100., 8300. );
    TH1F* hMode = new TH1F("hMode"," Mode;time; Toys", 2000, 8100., 8300. );
    TH1F* hFADC = new TH1F("hFADC"," ;time, ns; charge, e", 2550, 0., 40.*2550. );
    TH1F* hDIFF = new TH1F("hDIFF"," ;time, ns; charge, e", 2550, 0., 40.*2550. );
    TH1F* hTEMP = new TH1F("hTEMP"," ;time, ns; charge, e", 2550, 0., 40.*2550. );
    TH1F* hDEMP = new TH1F("hDEMP"," ;time, ns; charge, e", 2550, 0., 40.*2550. );
    TH1F* hSign = new TH1F("hSign"," ;time, ns; charge, e", 200., 8200.-300., 8200.+500. );

    hDIFF->SetLineColor(2);

    while( fOUT >> ev >> vol >> dE >> xi >> yi >> zi >> xf >> yf >> zf >> t ){
        if(ev>EVENT){
//            cout << "EV: " << EVENT << endl;
            if(sc2_dE>1){
                for(int bin=1;bin<2551;bin++){
                    hFADC->SetBinContent( bin, hFADC->GetBinContent(bin) + hTEMP->GetBinContent(bin) );
                    hDIFF->SetBinContent( bin, hDIFF->GetBinContent(bin) + hDEMP->GetBinContent(bin) );
//                    if(bin>2000 && bin<2201){
//                        hSign->SetBinContent(bin-2000, hFADC->GetBinContent(bin) + hTEMP->GetBinContent(bin));
//                    }
                    if(bin>1976 && bin<2177){
                        hSign->SetBinContent(bin-1976, hFADC->GetBinContent(bin) + hTEMP->GetBinContent(bin));
                    }
                }
            }
            sc1_dE = 0.;
            sc2_dE = 0.;
            hTEMP->Reset();
            hDEMP->Reset();
            tEv++;
            if(tEv==Evts){
                hMean->Fill( hFADC->GetMean() );
                hMea2->Fill( hSign->GetMean() );

                hMode->Fill( hFADC->GetXaxis()->GetBinCenter( hFADC->GetMaximumBin() ) );
                std::cout << "Charge on Flash ADC " << hFADC->Integral() << std::endl;


                hFADC->GetXaxis()->SetRangeUser(61000,63000);
//                hFADC->Divide(hDIFF);
//                hFADC->GetYaxis()->SetRangeUser(0,100000);
                TCanvas* canvs = new TCanvas("canvs","canvs",800,800);
//                TCanvas* canvs = new TCanvas("canvs","canvs",1200,300);
                gStyle->SetOptStat(0);
//                hSign->Draw();
                hFADC->Draw();
                hDIFF->Draw("same");
//                canvs->Print("Sign.png");
                canvs->Print("FADS.png");
                canvs->Print("FADS.C");
                canvs->Close();

                hFADC->Reset();
                hDIFF->Reset();
                hSign->Reset();
                nToys++;
                if(nToys>2){std::cout << "Toys: " << nToys ;
                            std::cout<< "\tmean " <<  hMean->GetMean() << " +/- " << hMean->GetRMS() ;
                            std::cout<< "\tmea2 " <<  hMea2->GetMean() << " +/- " << hMea2->GetRMS() ;
                            std::cout<< "\tmode " <<  hMode->GetMean() << " +/- " << hMode->GetRMS() << std::endl;}
                else{ std::cout << "Toys: " << nToys << std::endl;}
                tEv=0;
            }
            EVENT=ev;
        }

        //if(EVENT==Evts) break;


        if(vol==1) sc1_dE = sc1_dE + dE;
        if(vol==6) sc2_dE = sc2_dE + dE;
        if(vol==3){
            //xs=0.5*(xf+xi); ys=0.5*(yf+yi); zs=0.5*(zf+zi);
            N_e = int( dE/ I_av );
            if(N_e>0){
                dx = (xf-xi)/N_e;
                dy = (yf-yi)/N_e;
                dz = (zf-zi)/N_e;
//                cout << "  N_e: " << N_e << " ---> " ;
                N_s = 0;
                for(int ee=0;ee<N_e;ee++){
                    x = xi + 0.5*dx + dx*ee;
                    y = yi + 0.5*dy + dy*ee;
                    z = yi + 0.5*dz + dz*ee;
                    // go to TPC frame
                    X = z; Y = y; Z = Position - x;
                    l = sqrt(X*X+Y*Y);
                    if(l<10){
                        N_s++;
                        t_anod = (t + (Z-z_anod-10.) / W1 ) ;
                        // --->>  sigma_Z = 0.008*sqrt(Z)   [Z]=[sigma_Z]=cm
                        //d_anod = (t + (Z-z_anod-10.) / W1 ) ;
                        d_anod = (t + (Z+gRandom->Gaus(0,0.08*sqrt(Position/10.))-z_anod-10.) / W1 ) ;
                        tt = 20;
                        for(int iii = 0 ; iii<125; iii++  ){
                            hTEMP->Fill(t_anod + tt, Digi[iii]);
                            hDEMP->Fill(d_anod + tt, Digi[iii]);
                            tt = tt + 40 ;
                        }
                    }
                }
//                cout << N_s << endl ;
            }
        }
    }
    fOUT.close();

    TCanvas* canv = new TCanvas("canv","canv",1200,300);
    gStyle->SetOptStat(0);
    //gPad->SetGridy();
    //gPad->SetLogy();
    hFADC->Draw();
    canv->Print("FADC.png");
    gSystem->Exit(0);

}
