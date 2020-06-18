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

int MY_EVTS = 1;
double Calib = 200./151.;

TH1F* hFADC[9];
TH1F* hDIFF[9];
TH1F* hTEMP[9];
TH1F* hDEMP[9];

struct fadc_info
{
    double average;
    double peak;
    double mbp; // maximum bin position
    double base;
    double start;
    bool is_fired;
};

void print_info(fadc_info i){
    std::cout << "f: " << i.is_fired << "  ";
    std::cout << "a: " << i.average  << "  ";
    std::cout << "b: " << i.base     << "  ";
    std::cout << "p: " << i.peak     << "  ";
    std::cout << "m: " << i.mbp      << "  ";
    std::cout << "s: " << i.start    << "\n";
}


double find_peak(TH1F* h){
    TGraph* gn;
    TF1* poln;
    double pn_x[21];
    double pn_y[21];
    int nn_min;
    double xn_min, xn_max, xn_len;

    nn_min = h->GetMaximumBin()-10 ;

    xn_min = h->GetXaxis()->GetBinCenter( nn_min );
    xn_max = h->GetXaxis()->GetBinCenter( h->GetMaximumBin()+10  );

    xn_len = xn_max-xn_min;

    poln = new TF1("poln","[0]+[1]*x+[2]*x*x", xn_min-0.05*xn_len, xn_max+0.05*xn_len);

    for(int g=0;g<21;g++){
        pn_x[g] = h->GetXaxis()->GetBinCenter( nn_min + g );
        pn_y[g] = h->GetBinContent           ( nn_min + g );
    }
    gn = new TGraph(21,pn_x,pn_y);
    gn->Fit( poln , "Q");

    return (-0.5)*poln->GetParameter(1) / poln->GetParameter(2) ;

}

bool check_fired(TH1F*h, fadc_info i, double threshold=1.02, int window = 10, int nbins=2550){
  bool isf = false;
  double running_sum=0;
  for(int bin=1;bin<window+1;bin++){
      running_sum += ( h->GetBinContent(bin)*(1./window) );
  }
  for(int bin=1;bin<nbins-window+1;bin++){
      if( running_sum > i.average*threshold ) isf = true ;
      running_sum -= ( h->GetBinContent( bin )              ) / window;
      running_sum += ( h->GetBinContent( bin + window + 1 ) ) / window;
  }
  return isf;
}

double correct_base(TH1F* h, int ch_left=50, int ch_right=100, int nbins=2550){
  int max_bin = h->GetMaximumBin() ;
  int bin_low = max_bin - ch_left  ;
  int bin_high= max_bin + ch_right ;
  double base = 0;
  int counted_bins = 0;
  for(int bin=1;bin<nbins+1;bin++){
      if( (bin < bin_low) || ( bin > bin_high) ){
          base += h->GetBinContent(bin);
          counted_bins++;
          //std::cout << "  ---> " << bin  << " " << max_bin << "\n";
      }
  }

  return base/counted_bins;
}

double find_start( TH1F* h, fadc_info i, int ch_left=50 ){
  double start = -1;
  return start ;
}

fadc_info info[9];

fadc_info eval_info(TH1F* h, int nbins=2550){
    fadc_info h_info;
    h_info.is_fired = false;

    h_info.average = 0;
    for(int bin=1;bin<nbins+1;bin++) h_info.average += h->GetBinContent(bin);
    h_info.average = h_info.average / nbins;

    h_info.mbp = h->GetXaxis()->GetBinCenter( h->GetMaximumBin() ) ;
    h_info.peak = find_peak( h );

    h_info.is_fired = check_fired( h, h_info );

    if( h_info.is_fired ){
        h_info.base  = correct_base( h         );
        h_info.start = find_start  ( h, h_info );
    }
    else{
        h_info.base  = h_info.average;
        h_info.start = -1;
    }

    return h_info;
}

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

double find_base(){return 0;}
double is_fired(){return 0;}
double correct_base(){return 0;}
double find_time(){return 0;}

void allpads3( int Evts=MY_EVTS ){

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

    for(int pad=0;pad<9;pad++){
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

        hFADC[pad] = new TH1F(pFADC," ;time, ns; voltage, a.u.", 2550, 0., 40.*2550. );
        hDIFF[pad] = new TH1F(pDIFF," ;time, ns; voltage, a.u.", 2550, 0., 40.*2550. );

        hDIFF[pad]->SetLineColor(2);
    }

    double Val;



    while( fOUT >> ev >> vol >> dE >> xi >> yi >> zi >> ti >> xf >> yf >> zf >> tf ){
        if(ev>EVENT){


            for(int p=0;p<9;p++){
                for(int nbin=1;nbin<2694;nbin++){
                    fNOI >> Val;
                    if(nbin<2551){
                        hFADC[p]->SetBinContent( nbin, hFADC[p]->GetBinContent(nbin) + Val );
                        hDIFF[p]->SetBinContent( nbin, hDIFF[p]->GetBinContent(nbin) + Val );
                    }
                }
                info[p] = eval_info( hDIFF[p] );
//                if(p==0) print_info(info[p]) ;
                std::cout << "pad:" << p << "  "; print_info(info[p]) ;
            }

            if( !(ev%10) ) std::cout << "PROCESSED: "<< ev << " events\n";

            if(ev==Evts) break;

            for(int p=0;p<9;p++){
                hFADC[p]->Reset();
                hDIFF[p]->Reset();
            }
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


    TFile* f = new TFile("AllPads.root","RECREATE");
    for(int p=0;p<9;p++){
        hFADC[p]->Write();
        hDIFF[p]->Write();
    }
    f->Write();
    f->Close();


    gSystem->Exit(0);

}
