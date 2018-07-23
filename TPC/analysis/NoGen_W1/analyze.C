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


double startTPC = 0. ;

TH1F* hTPC = new TH1F("hTPC"," ;time, 10*ns; energy, a.u.", 2550, 0., 4.*2550. );
TH1F* hGEN = new TH1F("hGEN"," ;time, 10*ns; energy, a.u.", 2550, 0., 4.*2550. );

TH1F* hINT = new TH1F("hINT"," ;time, 10*ns; energy, a.u.", 2550, 0., 4.*2550. );
TH1F* hWLL = new TH1F("hWLL"," ;time, 10*ns; energy, a.u.", 2550, 0., 4.*2550. );
TH1F* hWGG = new TH1F("hWGG"," ;time, 10*ns; energy, a.u.", 2550, 0., 4.*2550. );

TH1F* hSig = new TH1F("hSig"," ;energy, a.u.; events", 200, 1., 3. );
TH1F* hTime = new TH1F("hTime"," ;time, 10*ns; energy, a.u.", 2.*2550, -4.*2550., 4.*2550. );


void findTPCtracks(){

  hGEN->SetLineColor(2);
  hGEN->SetFillColor(2);
  hGEN->SetFillStyle(3004);
  hTPC->SetMinimum(0);
  hINT->SetMinimum(0);

  hWGG->SetMinimum(0);
  hWLL->SetMinimum(0);

  hWGG->SetLineColor(2);
  hWLL->SetLineColor(1);


  int    ev, id ;
  double ed;
  double x1,y1,z1,t1;
  double x2,y2,z2,t2;
  double time;

  int    n_steps = 100;
  double dx, dy, dz, dt,de;
  double x, y, z, t, t_anod, l, tt;
  double t_wgg, t_wll;

  double Digi[125];

  double w_f = 1.2 ;
  double scaling_factor = 0.85 ; 
  double start_delay = 1000.;
  double W1 = w_f*scaling_factor*3.08*0.001; // mm/ns
  double W2 =     scaling_factor*7.50*0.001; // mm/ns
  double z_anod = 0.;

//==============================================================================
// create digitization
//==============================================================================
  TF1 *f_e1 = new TF1("f_e1"," 0.02207760*exp(-3.64674*0.673286*x)"                        ,0,5);
  TF1 *f_e2 = new TF1("f_e2","-0.02525950*exp(-3.35196*0.673286*x)*cos(1.74266*0.673286*x)",0,5);
  TF1 *f_e3 = new TF1("f_e3"," 0.00318191*exp(-2.32467*0.673286*x)*cos(3.57102*0.673286*x)",0,5);
  TF1 *f_e4 = new TF1("f_e4"," 0.01342450*exp(-3.35196*0.673286*x)*sin(1.74266*0.673286*x)",0,5);
  TF1 *f_e5 = new TF1("f_e5","-0.00564406*exp(-2.32467*0.673286*x)*sin(3.57102*0.673286*x)",0,5);
  TF1 *ft   = new TF1("ft"  ,"636.252*(f_e1 + f_e2 + f_e3 + f_e4 + f_e5)"                  ,0,5);

  tt = 0.02;
  double DS = 0 ;
  for(int ii=0; ii<125; ii++){
    Digi[ii] = 0.04*ft->Eval(tt);
    DS = DS + Digi[ii];
    tt = tt + 0.04;
  }



//==============================================================================
// loop on trigger event
//==============================================================================

  std::ifstream frTPC("../rest.data"      , std::ios::in);

  int n_ev = 0;
  int EVENT = 0;
  int process_ev = 1;
  double c_time = -8.*2550.;
  double time_shift = 0.;

  double frqs[6] = {    60,    123,    342,    706,   1000,   1500};
  
  double freq = 1000.*frqs[5];
  
  bool add_gen     = false ;
  bool calc_energy = false ;
  double sum   = 0;
  double signal= 0;
  double base_l= 0;
  double h_max = 0;
  int jj_bins  = 0;
  int jj_max  = 0;
  int kk;

  bool go_left,go_right;

  hTime->Fill(c_time);
  //std::cout << "EVENT: " << EVENT << "\t" << c_time << "\n";
  ev = 0;
  while(n_ev<process_ev){
    frTPC >> ev >> id >> x1 >> y1 >> z1 >> t1 >> x2 >> y2 >> z2 >> t2 >> ed ;
    
    if(ev>EVENT){
      time_shift = gRandom->Exp( 1000.*1000.*100. / freq );
      c_time = c_time + time_shift;
      //std::cout << "EVENT: " << EVENT << "\t" << c_time << "\n";
      hTime->Fill(c_time);
      if(c_time>4.*2550.){

        if(add_gen){
          de = 1.5;
          tt = 2;
          for(int iii = 0 ; iii<125; iii++  ){
            hTPC->Fill( 6000. + tt , de*Digi[iii]);
            tt = tt + 4 ;
          }      
        }

        if(calc_energy){
          signal = 0.;
          //--- find maximum and baseline ---
          sum = 0.; jj_bins=0;
          for(int jj=1;jj<2551;jj++){
            if( jj*4 < 6000 || jj*4 > 6600) {
              sum = sum + hTPC->GetBinContent(jj);
              jj_bins++;
            }
            if( hTPC->GetBinContent(jj)>h_max ){
              jj_max = jj;
              h_max  = hTPC->GetBinContent(jj);
            }
          }
          base_l = sum / jj_bins;
          //--- find maximum and baseline ---
          go_left = true; kk = jj_max - 1;
          while(go_left){
            if( hTPC->GetBinContent(kk) < base_l || signal>500){ go_left = false; }
            else{
              signal = signal + hTPC->GetBinContent(kk) - base_l; 
              hGEN->SetBinContent(kk, hTPC->GetBinContent(kk) - base_l );
            }
            kk--;
          }
          go_right = true; kk = jj_max ;
          while(go_right){
            if( hTPC->GetBinContent(kk) < base_l || signal>499 ){ go_right = false; }
            else{
              signal = signal + hTPC->GetBinContent(kk) - base_l ;
              hGEN->SetBinContent(kk, hTPC->GetBinContent(kk) - base_l );
            }
            kk++;
          }

          hSig->Fill(signal);
          std::cout << " ev "    << ev ;
          std::cout << "   n_ev "<< n_ev ;
          std::cout << "   max " << jj_max << "  " << h_max << "   base " << base_l ;
          std::cout << "   sig " << signal << "\n";
         
        }
        if(n_ev == -25){
          TCanvas *cnv = new TCanvas("cnv","cnv",900,300);
          hTPC->Draw("hist");
          hGEN->Draw("same");
          cnv->Print("SELECTED_EVENT.C");
          cnv->Close();

        }
        for(int jj=1;jj<2551;jj++){
          hTPC->SetBinContent(jj,0);
          hTPC->SetBinError(jj,0);
          hGEN->SetBinContent(jj,0);
          hGEN->SetBinError(jj,0);
        }
        
        c_time = -8.*2550.;
        n_ev++;
      }
      EVENT = ev;
    }

    dx = (x2-x1) / n_steps; dy = (y2-y1) / n_steps;  dz = (z2-z1) / n_steps;
    dt = (t2-t1) / n_steps; de = ed      / n_steps;

    for(int i=0;i<n_steps;i++){
      x = x1 + dx*(0.5+i); y = y1 + dy*(0.5+i); z = z1 + dz*(0.5+i);
      t = t1 + dt*(0.5+i);

      t_anod = 0.1*(t + (z-z_anod-3.) / W1 + 3./W2 );
      t_wll  = 0.1*(t + (z-z_anod-3.) / (0.8*W1) + 3./W2 );
      t_wgg  = 0.1*(t + (z-z_anod-3.) / (1.2*W1) + 3./W2 );

      l = sqrt(x*x+y*y);

      if(l>0 && l<10.){
        tt = 2;
        for(int iii = 0 ; iii<125; iii++  ){
          hTPC->Fill(start_delay + t_anod + tt + c_time, de*Digi[iii]);

          hINT->Fill(start_delay + t_anod + tt + c_time, de*Digi[iii]);
          hWLL->Fill(start_delay + t_wll  + tt + c_time, de*Digi[iii]);
          hWGG->Fill(start_delay + t_wgg  + tt + c_time, de*Digi[iii]);
          tt = tt + 4 ;
        }
      }
    }
  }

  frTPC.close();
}


TCanvas* canv = new TCanvas("canv","canv",900,400);

void analyze(){
  findTPCtracks();

  hINT->Draw("hist");
  hWLL->Draw("hist same");
  hWGG->Draw("hist same");

//  hTime->Draw();

 // gSystem->Exit(0);

}
