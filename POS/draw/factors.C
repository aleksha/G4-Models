{

  double x[6] = {1,2,3,4,5,6};
  double y[6] = {-1.21191, -6.21637, -10.9567, -15.9309, -19.381, -22.2515};
  double w[6] = {-1.57,  -5.64, -11.96, -16.99, -20.73, -23.60};
  double z[6] = {-1.3312, -4.67887, -8.95333, -14.1763, -16.7262, -19.4285};

  gw = new TGraph(6,x,w);
  gy = new TGraph(6,x,y);
  gz = new TGraph(6,x,z);

  gw->SetTitle(" ");
  gy->SetTitle(" ");
  gz->SetTitle(" ");

  gy->GetXaxis()->SetTitle("Factor");
  gy->GetYaxis()->SetTitle("Shift of maximum position");

  gw->SetLineWidth(2);
  gy->SetLineWidth(2);
  gz->SetLineWidth(2);

  gw->SetLineColor(kGreen+3);
  gy->SetLineColor(2);
  gz->SetLineColor(4);

  gw->SetMarkerColor(kGreen+3);
  gy->SetMarkerColor(2);
  gz->SetMarkerColor(4);

  gw->SetMarkerStyle(22);
  gy->SetMarkerStyle(20);
  gz->SetMarkerStyle(21);

  TCanvas* canv = new TCanvas("canv","canv",800,800);
  gy->Draw("APL");
  gz->Draw("same PL");
  gw->Draw("same PL");
  canv->Print("Factors.png");
  canv->Close();
  gSystem->Exit(0);

}

//x1
//Pad  0  62321.3 62322.5         -1.21191
//Pad 16  62330.4 62331.7         -1.3312

//x2
//Pad  0  62321.3 62327.5         -6.21637
//Pad 16  62330.4 62335.1         -4.67887

//x3
//Pad  0  62321.3 62332.2         -10.9567
//Pad 16  62330.4 62339.4         -8.95333

//x4
//Pad  0  	62319.1 	62335           -15.9309
//Pad 16  	62322.4 	62336.6         -14.1763

//x5
//Pad  0  62321.3 62340.6         -19.381
//Pad 16  62330.4 62347.1         -16.7262

//x6
//Pad  0  62321.3 62343.5         -22.2515
//Pad 16  62330.4 62349.8         -19.4285


