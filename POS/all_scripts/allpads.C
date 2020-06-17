#include <fstream>
#include <iostream>
#include <iomanip>

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

double Calib = 200./151.;

TH1F* hFADC[17];
TH1F* hDIFF[17];
TH1F* hTEMP[17];
TH1F* hDEMP[17];

TH1F* hZ01;
TH1F* hZ16;

int get_pad2(double x, double y){
    // central pad R = 10 mm
    // other width = 40 mm
    // numberinf left-to-right (increasing x) :
    //   1, 2, ... , 8, 0, 9, ... , 16

    double l;
    l = sqrt(x*x+y*y);

    if(x<0  && l>290)           return  1;
    if(x<0  && l>250 && l<=290) return  2;
    if(x<0  && l>210 && l<=250) return  3;
    if(x<0  && l>170 && l<=210) return  4;
    if(x<0  && l>130 && l<=170) return  5;
    if(x<0  && l> 90 && l<=130) return  6;
    if(x<0  && l> 50 && l<= 90) return  7;
    if(x<0  && l> 10 && l<= 50) return  8;
    if(x<0  && l<= 10)          return  0;
    if(x>=0 && l<= 10)          return  0;
    if(x>=0 && l> 10 && l<= 50) return  9;
    if(x>=0 && l> 50 && l<= 90) return 10;
    if(x>=0 && l> 90 && l<=130) return 11;
    if(x>=0 && l>130 && l<=170) return 12;
    if(x>=0 && l>170 && l<=210) return 13;
    if(x>=0 && l>210 && l<=250) return 14;
    if(x>=0 && l>250 && l<=290) return 15;
    if(x>=0 && l>290)           return 16;


}

int get_pad(double x, double y){
    // central pad R = 10 mm
    // other width = 40 mm
    // numberinf left-to-right (increasing x) :
    //   1, 2, ... , 8, 0, 9, ... , 16

    double l;
    l = sqrt(x*x+y*y);

    if(l<10) return 0;
    if(x>0){
        if(l< 50) return  9;
        if(l< 90) return 10;
        if(l<130) return 11;
        if(l<170) return 12;
        if(l<210) return 13;
        if(l<250) return 14;
        if(l<290) return 15;
        return 16;
    }
    if(l< 50) return 8;
    if(l< 90) return 7;
    if(l<130) return 6;
    if(l<170) return 5;
    if(l<210) return 4;
    if(l<250) return 3;
    if(l<290) return 2;
    return 1;
}

void allpads(double Position = 250., int Evts=1){

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

    int fpad;

    std::ifstream fOUT("./out.data" , std::ios::in);

    TString pFADC,pDIFF,pTEMP,pDEMP;

    hZ01 = new TH1F("hZ01",";Z_{Ionization-Anode};Electrons",200,240,260);
    hZ16 = new TH1F("hZ16",";Z_{Ionization-Anode};Electrons",200,240,260);

    for(int pad=0;pad<17;pad++){
        if(pad<10){
            pFADC.Form ("hFADS_0%d", pad);
            pDIFF.Form ("hDIFF_0%d", pad);
            pTEMP.Form ("hTEPM_0%d", pad);
            pDEMP.Form ("hDEMP_0%d", pad);
        }
        else{
            pFADC.Form ("hFADS_0%d", pad);
            pDIFF.Form ("hDIFF_0%d", pad);
            pTEMP.Form ("hTEPM_0%d", pad);
            pDEMP.Form ("hDEMP_0%d", pad);
        }

        hFADC[pad] = new TH1F(pFADC," ;time, ns; charge, e", 2550, 0., 40.*2550. );
        hDIFF[pad] = new TH1F(pDIFF," ;time, ns; charge, e", 2550, 0., 40.*2550. );
        hTEMP[pad] = new TH1F(pTEMP," ;time, ns; charge, e", 2550, 0., 40.*2550. );
        hDEMP[pad] = new TH1F(pDEMP," ;time, ns; charge, e", 2550, 0., 40.*2550. );

        hDIFF[pad]->SetLineColor(2);
    }

    while( fOUT >> ev >> vol >> dE >> xi >> yi >> zi >> xf >> yf >> zf >> t ){
        if(ev>EVENT){
            for(int p=0;p<17;p++){
                for(int bin=1;bin<2551;bin++){
                    hFADC[p]->SetBinContent( bin, hFADC[p]->GetBinContent(bin) + hTEMP[p]->GetBinContent(bin) );
                    hDIFF[p]->SetBinContent( bin, hDIFF[p]->GetBinContent(bin) + hDEMP[p]->GetBinContent(bin) );
                }
                hTEMP[p]->Reset();
                hDEMP[p]->Reset();
            }
            EVENT=ev;
        }

        if(EVENT==Evts) break;


        if(vol==3){
            N_e = int( dE/ I_av );
            if(N_e>0){
                dx = (xf-xi)/N_e;
                dy = (yf-yi)/N_e;
                dz = (zf-zi)/N_e;
                N_s = 0;
                for(int ee=0;ee<N_e;ee++){
                    x = xi + 0.5*dx + dx*ee;
                    y = yi + 0.5*dy + dy*ee;
                    z = zi + 0.5*dz + dz*ee;
                    // go to TPC frame
                    X = z; Y = y; Z = Position - x;
                    //std::cout << X << " " << Y <<  " " << sqrt(X*X+Y*Y) << " " << get_pad(X,Y) << " " << get_pad2(X,Y) << "\n";
                    fpad = get_pad2(X,Y);
                    if(fpad== 1) hZ01->Fill(Z);
                    if(fpad==16) hZ16->Fill(Z);
                    t_anod = (t + (Z-z_anod-10.) / W1 ) ;
                    // --->>  sigma_Z = 0.008*sqrt(Z)   [Z]=[sigma_Z]=cm
                    //d_anod = (t + (Z-z_anod-10.) / W1 ) ;
                    d_anod = (t + (Z+gRandom->Gaus(0,0.08*sqrt(Position/10.))-z_anod-10.) / W1 ) ;
                    tt = 20;
                    for(int iii = 0 ; iii<125; iii++  ){
                        hTEMP[fpad]->Fill(t_anod + tt, Calib*Digi[iii]);
                        hDEMP[fpad]->Fill(d_anod + tt, Calib*Digi[iii]);
                        tt = tt + 40 ;
                    }
                }
            }
        }
    }
    fOUT.close();

    TCanvas* canv = new TCanvas("canv","canv",1200,300);
    gStyle->SetOptStat(0);

    for(int p=0;p<17;p++){
        hFADC[p]->Draw();
        hDIFF[p]->Draw("same");
        if(p<10){pFADC.Form("FADS_0%d.png",p);}
        else{ pFADC.Form("FADS_%d.png",p);}
        canv->Print( pFADC );
    }
    canv->Close();

    TCanvas* canvZ = new TCanvas("canvZ","canvZ",800,800);
    gStyle->SetOptStat(0);
    hZ16->SetLineWidth(2);
    hZ01->SetLineWidth(2);
    hZ01->SetLineColor(2);
    hZ01->SetFillColor(2);
    hZ01->SetFillStyle(3005);
    hZ01->Draw();
    hZ16->Draw("same");
    canvZ->Print("DistoZ.png");
    canvZ->Close();
    std::cout << "\n\n\n";
    std::cout << "Pad 01 : mean = " << hZ01->GetMean() << "\t rms = " << hZ01->GetRMS() << "\n";
    std::cout << "Pad 16 : mean = " << hZ16->GetMean() << "\t rms = " << hZ16->GetRMS() << "\n";


    TFile* f = new TFile("AllPads.root","RECREATE");
    for(int p=0;p<17;p++){
        hFADC[p]->Write();
        hDIFF[p]->Write();
    }
    f->Write();
    f->Close();


    double peak_n[17];
    double peak_d[17];

    TGraph* gn[17];
    TGraph* gd[17];
    TF1* poln[17];
    TF1* pold[17];
    double pn_x[21];
    double pn_y[21];
    double pd_x[21];
    double pd_y[21];
    int nn_min, nd_min;
    double xn_min, xn_max, xn_len;
    double xd_min, xd_max, xd_len;
    for(int p=0;p<17;p++){
        nn_min = hFADC[p]->GetMaximumBin()-10 ;
        nd_min = hDIFF[p]->GetMaximumBin()-10 ;

        xn_min = hFADC[p]->GetXaxis()->GetBinCenter( nn_min );
        xd_min = hDIFF[p]->GetXaxis()->GetBinCenter( nd_min );
        xn_max = hFADC[p]->GetXaxis()->GetBinCenter( hFADC[p]->GetMaximumBin()+10  );
        xd_max = hDIFF[p]->GetXaxis()->GetBinCenter( hFADC[p]->GetMaximumBin()+10  );

        xn_len = xn_max-xn_min;
        xd_len = xd_max-xd_min;
        poln[p] = new TF1("poln","[0]+[1]*x+[2]*x*x", xn_min-0.05*xn_len, xn_max+0.05*xn_len);
        pold[p] = new TF1("pold","[0]+[1]*x+[2]*x*x", xd_min-0.05*xd_len, xd_max+0.05*xd_len);

        for(int g=0;g<21;g++){
            pn_x[g] =  hFADC[p]->GetXaxis()->GetBinCenter( nn_min + g );
            pn_y[g] =  hFADC[p]->GetBinContent           ( nn_min + g );
            pd_x[g] =  hDIFF[p]->GetXaxis()->GetBinCenter( nd_min + g );
            pd_y[g] =  hDIFF[p]->GetBinContent           ( nd_min + g );
        }
        gn[p] = new TGraph(21,pn_x,pn_y);
        gd[p] = new TGraph(21,pd_x,pd_y);

        gn[p]->Fit( poln[p] );
        gd[p]->Fit( pold[p] );

        peak_n[p] = (-0.5)*poln[p]->GetParameter(1) / poln[p]->GetParameter(2) ;
        peak_d[p] = (-0.5)*pold[p]->GetParameter(1) / pold[p]->GetParameter(2) ;


    }

    std::cout << "\n\n\n";
    for(int p=0;p<17;p++){
        if(p<10) std::cout << "Pad  " << p  << "\t"  << peak_n[p] << "\t" << peak_d[p] << "\t\t" << peak_n[p]-peak_d[p] << "\n";
        else     std::cout << "Pad "  << p  << "\t"  << peak_n[p] << "\t" << peak_d[p] << "\t\t" << peak_n[p]-peak_d[p] << "\n";
    }
    gSystem->Exit(0);

}
