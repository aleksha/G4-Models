{
  gStyle->SetOptStat(0);

  double Lag = 10.0; // mm
  double W2  =  7.5; // mm/us

  double Tag = Lag / W2; // Time of the drift btw. Grid and Anode
  int Nag = Tag / 0.04; // Number of 40 ns channels

//==============================================================================
// create digitization
//==============================================================================
  TF1 *f_e1 = new TF1("f_e1"," 0.02207760*exp(-3.64674*0.673286*x)"                        ,0,7);
  TF1 *f_e2 = new TF1("f_e2","-0.02525950*exp(-3.35196*0.673286*x)*cos(1.74266*0.673286*x)",0,7);
  TF1 *f_e3 = new TF1("f_e3"," 0.00318191*exp(-2.32467*0.673286*x)*cos(3.57102*0.673286*x)",0,7);
  TF1 *f_e4 = new TF1("f_e4"," 0.01342450*exp(-3.35196*0.673286*x)*sin(1.74266*0.673286*x)",0,7);
  TF1 *f_e5 = new TF1("f_e5","-0.00564406*exp(-2.32467*0.673286*x)*sin(3.57102*0.673286*x)",0,7);
  TF1 *ft   = new TF1("ft"  ,"636.252*(f_e1 + f_e2 + f_e3 + f_e4 + f_e5)"                  ,0,7);

  cout << "Func.Integral = " << ft->Integral(0,7) << endl;

  TH1F* hft = new TH1F("hft",";time;response", 175, 0, 7 );
  TH1F* sft = new TH1F("sft",";time;response", 175, 0, 7 );
  TH1F* dft = new TH1F("dft",";time;response", 175, 0, 7 );
  TH1F* cft = new TH1F("cft",";time;response", 175, 0, 7 );

  sft->SetLineColor(2);
  hft->SetLineColor(2);
  cft->SetLineColor(4);

  sft->SetLineWidth(2);
  hft->SetLineWidth(2);
  cft->SetLineWidth(2);

  double Digi[175];

  double tt = 0.02;
  double DS = 0 ;
  for(int ii=0; ii<175; ii++){
    Digi[ii] = ft->Eval(tt);
    DS = DS + Digi[ii];
    tt = tt + 0.04;
    sft->SetBinContent( Nag + ii+1, Digi[ii] );
    hft->SetBinContent( ii+1, Digi[ii] );
  }

  double Charge = 0.;
  double ttg = 0.04;
  double sum = 0.;
  for(int ii=0; ii<Nag; ii++){
    sum = sum + 0.04*(2.*ttg/pow(Tag,2));
    Charge = 0.04*2.*ttg/pow(Tag,2);
    dft->SetBinContent( ii+1, Charge/0.04 );

    tt = 0.02;
    for(int jj=0; jj<175; jj++){
        Digi[jj] = ft->Eval(tt);
        tt = tt + 0.04;
        cft->SetBinContent( ii+jj+1,  cft->GetBinContent(ii+jj+1) + Charge*Digi[jj] );
    }

    ttg = ttg + 0.04;
  }

  cout << "Integral " << sum << "\n\n\n\n"<< endl;

  double shft = 0;
  double scft = 0;
  for(int ii=0; ii<175; ii++){
    shft = shft + 0.04*hft->GetBinContent( ii+1 );
    scft = scft + 0.04*cft->GetBinContent( ii+1 );
    cout << ii << " " << 0.04*cft->GetBinContent( ii+1 ) << endl;
  }

  cout << "\n\n\n\n";
  cout << "Integral hft = " << shft << endl;
  cout << "Integral cft = " << scft << endl;


  TCanvas* canv = new TCanvas("canv","canv",800,800);
  sft->Draw();
  cft->Draw("same");
  canv->Print("Resp.png");
  canv->Close();

  gSystem->Exit(0);
}
