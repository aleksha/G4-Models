#include "TSystem.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TVector3.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"

#include <iostream>
#include <fstream>
using namespace std;

int PROCESS = 10000;

TVector3 Vertex(TVector3 p1, TVector3 b, TVector3 p2, TVector3 d){

    TVector3 d1, d2, n1, n2, c1, c2, rr;

    d1 = ( b - p1 ).Unit();
    d2 = ( d - p2 ).Unit();

    n1 = d1.Cross( d2.Cross(d1) );
    n2 = d2.Cross( d1.Cross(d2) );

    c1 = p1 + d1 * ( ( ( p2 - p1 ) * n2 ) / ( d1*n2 ) );
    c2 = p2 + d2 * ( ( ( p1 - p2 ) * n1 ) / ( d2*n1 ) );

    rr = (c1+c2)*0.5 ;

    return rr;
}

void fast_vertex(){

    int ev, vol, tr, st, code, c;
    double dE, E, xi, yi, zi, ti, xf, yf, zf, tf;
    int n_steps;
    double xc;

    std::ifstream fOUT("./out.data" , std::ios::in);

    //TH1F* hVTX  = new TH1F("hVTX" ,"; z, mm;Events", 60, 400, 1000);
    //TH1F* hANG  = new TH1F("hANG" ,"; angle, #murad;Events", 60, 200, 500);
    //TH1F* hVTX2 = new TH1F("hVTX2","; z, mm;Events", 60, 400, 1000);
    //TH1F* hANG2 = new TH1F("hANG2","; angle, #murad;Events", 60, 200, 500);

    //TH1F* hVTX  = new TH1F("hVTX" ,"; z, mm;Events", 60,-200, 400);
    //TH1F* hANG  = new TH1F("hANG" ,"; angle, #murad;Events", 60, 1850, 2150);
    //TH1F* hVTX2 = new TH1F("hVTX2","; z, mm;Events", 60,-200, 400);
    //TH1F* hANG2 = new TH1F("hANG2","; angle, #murad;Events", 60, 1850, 2150);

    TH1F* hVTX  = new TH1F("hVTX" ,"; z, mm;Events", 80, -400, 400);
    TH1F* hANG  = new TH1F("hANG" ,"; angle, #murad;Events", 60, 200, 500);
    TH1F* hVTX2 = new TH1F("hVTX2","; z, mm;Events", 80, -400, 400);
    TH1F* hANG2 = new TH1F("hANG2","; angle, #murad;Events", 60, 200, 500);

    //TH1F* hVTX  = new TH1F("hVTX" ,"; z, mm;Events", 60, 450, 1050);
    //TH1F* hANG  = new TH1F("hANG" ,"; angle, #murad;Events", 60, 200, 500);
    //TH1F* hVTX2 = new TH1F("hVTX2","; z, mm;Events", 60, 450, 1050);
    //TH1F* hANG2 = new TH1F("hANG2","; angle, #murad;Events", 60, 200, 500);

    TH1F* hPHI  = new TH1F("hPHI" ,"; #phi-angle, mrad;Events", 60,-150, 150);
    TH1F* hPHI2 = new TH1F("hPHI2","; #phi-angle, mrad;Events", 60,-150, 150);


    hVTX2->SetLineColor( kGreen+3 );
    hANG2->SetLineColor( kGreen+3 );
    hPHI2->SetLineColor( kGreen+3 );
    hVTX2->SetFillColor( kGreen+3 );
    hANG2->SetFillColor( kGreen+3 );
    hPHI2->SetFillColor( kGreen+3 );
    hVTX2->SetFillStyle( 3005     );
    hANG2->SetFillStyle( 3005     );
    hPHI2->SetFillStyle( 3005     );

    TCanvas* canv = new TCanvas("canv","canv",600,600);
    TH2F* hL = new TH2F("hL",";t;s", 1000, 0, 10000, 1000, 0, 10000);

    TVector3 vINI, vOUT, v_vtx;
    TVector3 wINI, wOUT, w_vtx;
    TVector3 vv0,vv1,vv2,vv3,tv;
    TVector3 ww0,ww1,ww2,ww3;
    double xx[4], sx[4];
    double yy[4], sy[4];
    double zz[4], sz[4];
    bool fired[4] = {false, false, false, false};
    bool secnd[4] = {false, false, false, false};

    double ideal = 0.;
    double real  = 0.;
    double Ev    = 0.;

    int cntr=0.;
    int mult[7] = {0,0,0,0,0,0,0};
//    double m1[1000], m2[1000];
//    double mv1,sdv1,m2,sdv2,df,sdf;

    int nSec  = 0;
    int nThr  = 0;
    int EVENT = 0;
    while( fOUT >> ev >> tr >> st >> vol >> dE >> code >> c >> E >> xi >> yi >> zi >> ti >> xf >> yf >> zf >> tf ){
      if(ev>EVENT && ev<PROCESS){

          if( fired[0] && fired[1] && fired[2] && fired[3] ){

              vv0.SetXYZ( xx[0] , yy[0], zz[0]);
              vv1.SetXYZ( xx[1] , yy[1], zz[1]);
              vv2.SetXYZ( xx[2] , yy[2], zz[2]);
              vv3.SetXYZ( xx[3] , yy[3], zz[3]);
              ww0.SetXYZ( sx[0] , sy[0], sz[0]);
              ww1.SetXYZ( sx[1] , sy[1], sz[1]);
              ww2.SetXYZ( sx[2] , sy[2], sz[2]);
              ww3.SetXYZ( sx[3] , sy[3], sz[3]);

//              vINI.SetXYZ( xx[1]-xx[0] , yy[1]-yy[0], -5000.);
//              vOUT.SetXYZ( xx[3]-xx[2] , yy[3]-yy[2], -5000.);
              vINI.SetXYZ( xx[1]-xx[0] , yy[1]-yy[0], -3000.);
              vOUT.SetXYZ( xx[3]-xx[2] , yy[3]-yy[2], -3000.);
              v_vtx = Vertex( vv0, vv1, vv2, vv3);

//              wINI.SetXYZ( sx[1]-sx[0] , sy[1]-sy[0], -5000.);
//              wOUT.SetXYZ( sx[3]-sx[2] , sy[3]-sy[2], -5000.);
              wINI.SetXYZ( sx[1]-sx[0] , sy[1]-sy[0], -3000.);
              wOUT.SetXYZ( sx[3]-sx[2] , sy[3]-sy[2], -3000.);
              w_vtx = Vertex( ww0, ww1, ww2, ww3);

              hVTX->Fill(  v_vtx.z() );
              hANG->Fill(  1000.*1000.*vOUT.Angle( vINI ) );
              hPHI->Fill(  1000.*((vOUT - vINI ).Phi() -0.5*TMath::Pi()));

              hVTX2->Fill( w_vtx.z() );
              hANG2->Fill( 1000.*1000.*wOUT.Angle( wINI ) );
              hPHI2->Fill(  1000.*( (wOUT - wINI ).Phi() -0.5*TMath::Pi()));
              if( !(ev%50) ) cout << ev << "\t" <<  1000.*((wOUT - wINI ).Phi() - 0.5*TMath::Pi()) << endl;
          }

          for(int ii=0;ii<4;ii++){ fired[ii] = false; secnd[ii] = false; }
          EVENT = ev;
      }

      if(tr < 3){
          xx[vol] = xi;
          yy[vol] = yi;
          zz[vol] = zi;
          if(vol>-1){
//          sx[vol] = xi + gRandom->Gaus( 0, 0.0001);  sy[vol] = yi + gRandom->Gaus( 0, 0.0001);
//          sx[vol] = xi + gRandom->Gaus( 0, 0.008 );  sy[vol] = yi + gRandom->Gaus( 0, 0.008 );
            sx[vol] = xi + gRandom->Gaus( 0, 0.016 );  sy[vol] = yi + gRandom->Gaus( 0, 0.016 );
            sz[vol] = zi;
          }
          else{
          sx[vol] = xi;
          sy[vol] = yi;
          sz[vol] = zi;
          }
          fired[vol] = true;
      }

    }

//    hANG->GetYaxis()->SetRangeUser(0,400);
//    hVTX->GetYaxis()->SetRangeUser(0,150);

    fOUT.close();
    hANG->Draw();
    hANG2->Draw("same");
//    hANG->Fit("gaus");
    hANG2->Fit("gaus");
    canv->Print("RECO.png");
    hPHI->Draw();
    hPHI2->Draw("same");
    hPHI2->Fit("gaus");
    canv->Print("PHIa.png");
    hVTX->Draw();
    hVTX2->Draw("same");
//    hVTX->Fit("gaus");
    hVTX2->Fit("gaus");
    canv->Print("VRTX.png");
//    gPad->SetLogz();
//    hL->Draw("colz");
//    canv->Print("VRTX.png");
    gSystem->Exit(0);

}
