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

int MY_EVTS = 100000;
double Calib = 200./151.;

TH1F* hSIGN;
TH1F* hTOYS;
TH1F* hTRUE;
TH1F* hSHIFT;
TH1F* hMEANT;
TH1F* hFADC;
TH1F* hNOIS;
TH1F* hDIST;
TH1F* hDERV;


void test(double Position = 250., int Evts=MY_EVTS){

    std::ifstream fNOI("/home/user/Data/Noise/MERGED/noise.data" , std::ios::in);
    std::ifstream fSIG("./dump_fadc_100k_new.txt" , std::ios::in);

    hSIGN = new TH1F("hSIGN"," ;time, ns; charge, e", 2550, 0., 40.*2550. );
    hTOYS = new TH1F("hTOYS"," ;time, ns; charge, e", 2550, 0., 40.*2550. );
    hTRUE = new TH1F("hTRUE"," ;time, ns; charge, e", 2550, 0., 40.*2550. );
    hFADC = new TH1F("hFADC"," ;time, ns; charge, e", 2550, 0., 40.*2550. );
    hNOIS = new TH1F("hNOIS"," ;time, ns; charge, e", 2550, 0., 40.*2550. );
    hDERV = new TH1F("hDERV"," ;time, ns; #Delta e", 2550, 0., 40.*2550. );
    hDIST = new TH1F("hDIST"," ;charge / average charge, %; entries", 1000, -0.05, 0.05 );
    hSHIFT = new TH1F("hSHIFT"," ; shift, ns; entries", 40, -20, 20 );
    hMEANT = new TH1F("hMEANT"," ; shift, ns; entries", 100, -50, 50 );

    hTRUE->SetLineColor(8);
    hMEANT->SetLineColor(2);
    hMEANT->SetFillColor(2);
    hMEANT->SetFillStyle(3005);


    int EVENT=0;
    double Val;
    double SumVal = 0.;
    int nbin=0;
    while( fNOI >> Val ){
        nbin++;
        if(nbin<2551){
            hFADC->SetBinContent( nbin, hFADC->GetBinContent(nbin) + Val );
        }
        if(nbin==2693){ nbin=0; EVENT++;}
        if(EVENT==Evts) break;
    }
    fNOI.close();

    for(int bin=1; bin<2551; bin++){
        SumVal = SumVal + hFADC->GetBinContent(bin);
    }
    SumVal = SumVal / 2550.;

    for(int bin=1; bin<2551; bin++){
        hNOIS->SetBinContent( bin, hFADC->GetBinContent(bin) -SumVal );
        hFADC->SetBinContent( bin, (hFADC->GetBinContent(bin)-SumVal)/SumVal);
    }

    for(int bin=1; bin<2550; bin++){
        hDERV->SetBinContent( bin, hFADC->GetBinContent(bin+1) - hFADC->GetBinContent(bin) );
    }

    for(int bin=1; bin<2551; bin++){
        if( !(bin%50) ) {std::cout << 100.*hFADC->GetBinContent(bin) << "\n";};
        hDIST->Fill(100.*hFADC->GetBinContent(bin));
    }


    nbin=1;
    while( fSIG >> Val ){
        hSIGN->SetBinContent(nbin, Val);
        nbin++;
    }
    fSIG.close();
    double peak_Y[31];
    for(int bin=1; bin<2551; bin++){
        for(int bb=0;bb<31;bb++){
            peak_Y[bb] = hSIGN->GetBinContent( hSIGN->GetMaximumBin()-15+bb  );
        }
    }



    TGraph* gn;
    TGraph* gd;
    TF1* poln;
    TF1* pold;
    double pn_x[21];
    double pn_y[21];
    double pd_x[21];
    double pd_y[21];
    int nn_min, nd_min;
    double xn_min, xn_max, xn_len;
    double xd_min, xd_max, xd_len;
    int xOffset;
    double peak_n, peak_d;
    double mean_n, mean_d;
    double summ_n, summ_d;

    TString stoy;
    TCanvas* canvP = new TCanvas("canvP","canvP",800,800);
    for(int p=0;p<100;p++){
        stoy.Form("TOYS_%d.png",p);
        for(int bin=1;bin<2551;bin++){
            hTOYS->SetBinContent(bin, 0 );
            hTRUE->SetBinContent(bin, 0 );
        }

        for(int bin=1;bin<2551;bin++){
            hTOYS->SetBinContent(bin, hNOIS->GetBinContent(bin) );
        }

        xOffset = int( 50 + 2300.*gRandom->Rndm() );
        for(int bb=0;bb<31;bb++){
            hTOYS->SetBinContent( xOffset+bb, hTOYS->GetBinContent(xOffset+bb) + peak_Y[bb] );
            hTRUE->SetBinContent( xOffset+bb,  peak_Y[bb] );
        }


        nn_min = hTOYS->GetMaximumBin()-10 ;
        nd_min = hTRUE->GetMaximumBin()-10 ;

        xn_min = hTOYS->GetXaxis()->GetBinCenter( nn_min );
        xd_min = hTRUE->GetXaxis()->GetBinCenter( nd_min );
        xn_max = hTOYS->GetXaxis()->GetBinCenter( hTOYS->GetMaximumBin()+10  );
        xd_max = hTRUE->GetXaxis()->GetBinCenter( hTRUE->GetMaximumBin()+10  );

        xn_len = xn_max-xn_min;
        xd_len = xd_max-xd_min;
        poln = new TF1("poln","[0]+[1]*x+[2]*x*x", xn_min-0.05*xn_len, xn_max+0.05*xn_len);
        pold = new TF1("pold","[0]+[1]*x+[2]*x*x", xd_min-0.05*xd_len, xd_max+0.05*xd_len);


        summ_d=0; summ_n=0; mean_d=0; mean_n=0;
        for(int g=0;g<21;g++){
            pn_x[g] =  hTOYS->GetXaxis()->GetBinCenter( nn_min + g );
            pn_y[g] =  hTOYS->GetBinContent           ( nn_min + g );
            pd_x[g] =  hTRUE->GetXaxis()->GetBinCenter( nd_min + g );
            pd_y[g] =  hTRUE->GetBinContent           ( nd_min + g );
            mean_n  = mean_n + pn_x[g]*pn_y[g];
            mean_d  = mean_d + pd_x[g]*pd_y[g];
            summ_n  = summ_n + pn_y[g];
            summ_d  = summ_d + pd_y[g];
        }
        mean_n = mean_n / summ_n;
        mean_d = mean_d / summ_d;


        gn = new TGraph(21,pn_x,pn_y);
        gd = new TGraph(21,pd_x,pd_y);

        gn->SetMarkerStyle(20);
        gd->SetMarkerStyle(24);

        gn->SetMarkerColor(4);
        gd->SetMarkerColor(8);

        poln->SetLineColor(4);
        pold->SetLineColor(8);

        gn->Draw("AP");
        gd->Draw("same P");

        gn->Fit( poln );
        gd->Fit( pold );

        peak_n = (-0.5)*poln->GetParameter(1) / poln->GetParameter(2) ;
        peak_d = (-0.5)*pold->GetParameter(1) / pold->GetParameter(2) ;

        std::cout << "  peak  --> " << peak_n << "\t" << peak_d << "\t" <<  peak_n-peak_d << "\n";
        std::cout << "  mean      " << mean_n << "\t" << mean_d << "\t" <<  mean_n-mean_d << "\n";

        hMEANT->Fill(mean_n-mean_d);
        hSHIFT->Fill(peak_n-peak_d);

//        hTOYS->Draw();
//        hTRUE->Draw("same");
//        canvP->Print(stoy);

        hTOYS->Reset();
        hTRUE->Reset();
    }
    canvP->Close();

    TCanvas* canv6 = new TCanvas("canv6","canv6",900,900);
    hMEANT->Draw();
    hSHIFT->Draw("same");
    canv6->Print( "SHIFT.png" );
    canv6->Close();

    std::cout << "RMS   " << hMEANT->GetRMS() << "\t" << hSHIFT->GetRMS() << "\n";




    TCanvas* canv2 = new TCanvas("canv2","canv2",900,900);
    gPad->SetGridx();
    gPad->SetGridy();
//    hDIST->Draw();
    hDIST->Draw();
    canv2->Print( "DISTO.png" );
    canv2->Close();






    TCanvas* canv = new TCanvas("canv","canv",1200,300);
    gStyle->SetOptStat(0);
    gPad->SetGridy();
    hNOIS->Draw();
    canv->Print( "NOISE.png" );
    canv->Close();


    hSIGN->SetLineColor(1);
    TCanvas* canv4 = new TCanvas("canv4","canv4",1200,300);
    gStyle->SetOptStat(0);
    //gPad->SetGridy();
    hSIGN->Draw();
    canv4->Print( "SIGNAL_10k.png" );
    canv4->Close();

    TCanvas* canv3 = new TCanvas("canv3","canv3",1200,300);
    gStyle->SetOptStat(0);
    gPad->SetGridy();
    hDERV->Draw();
    canv3->Print( "DERIV.png" );
    canv3->Close();


    gSystem->Exit(0);

}
