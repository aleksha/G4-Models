void fadc(double Position = 100., int Evts=1000){

  double l, X, Y, Z, t_anod;

  double w_f = 1.0 ;
  double scaling_factor = 1.00 ;
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

  double Digi[125];
  double tt = 0.02;
  double DS = 0 ;
  for(int ii=0; ii<125; ii++){
    Digi[ii] = 0.04*ft->Eval(tt);
    DS = DS + Digi[ii];
    tt = tt + 0.04;
  }

    int ev, vol;
    double dE,x,y,z,t;

    double sc1_dE=0;
    double sc2_dE=0;
    double hyd_dE=0;

    int EVENT=0;

    std::ifstream fOUT("./out.data" , std::ios::in);

    TH1F* hFADC = new TH1F("hFADC"," ;time, 10*ns; energy, a.u.", 2550, 0., 4.*2550. );
    TH1F* hTEMP = new TH1F("hTEMP"," ;time, 10*ns; energy, a.u.", 2550, 0., 4.*2550. );

    while( fOUT >> ev >> vol >> dE >> x >> y >> z >> t ){
        if(ev>EVENT){
            if(sc1_dE>1 && sc2_dE>1){
                for(int bin=1;bin<2551;bin++)
                    hFADC->SetBinContent( bin, hFADC->GetBinContent(bin) + hTEMP->GetBinContent(bin) );
            }
            sc1_dE = 0.;
            sc2_dE = 0.;
            hTEMP->Reset();
            EVENT=ev;
        }

        if(EVENT==Evts) break;


        if(vol==1) sc1_dE = sc1_dE + dE;
        if(vol==6) sc2_dE = sc2_dE + dE;
        if(vol==3){
            X = z; Y = y; Z = Position - x;
            t_anod = 0.1*(t + (Z-z_anod-3.) / W1 + 3./W2 );
            l = sqrt(X*X+Y*Y);
            if(l<100){
                tt = 2;
                for(int iii = 0 ; iii<125; iii++  ){
                    hTEMP->Fill(t_anod + tt, dE*Digi[iii]);
                    tt = tt + 4 ;
                }
            }
        }
    }
    fOUT.close();

    cout << "Mean: " << hFADC->GetMean() ;
    cout << " +/- " << hFADC->GetMeanError() << endl ;

    TCanvas* canv = new TCanvas("canv","canv",1200,300);
    gStyle->SetOptStat(0);
    //gPad->SetGridy();
    //gPad->SetLogy();
    hFADC->Draw();
    canv->Print("FADC.png");
    gSystem->Exit(0);

}
