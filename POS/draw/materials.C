{

  double x[6] = {0,6,14,29,47,74};
  double w[6] = {-1.57, -1.41, -1.47, -0.62, -0.15, -1.04};
  double y[6] = {-1.30, -0.61, -0.25, -1.48, -0.32, -2.93};
  double z[6] = {-1.38, -0.04, -0.29, -0.61, -0.14,  2.68};

  gw = new TGraph(6,x,w);
  gy = new TGraph(6,x,y);
  gz = new TGraph(6,x,z);

  gw->SetTitle(" ");
  gy->SetTitle(" ");
  gz->SetTitle(" ");

  gy->GetXaxis()->SetTitle("Z of material in front of H_{2}");
  gy->GetYaxis()->SetTitle("Shift of maximum position");
  gy->GetYaxis()->SetRangeUser(-25,5);

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
  canv->Print("Materials.png");
  canv->Close();
  gSystem->Exit(0);

}



//No material
//Pad  1  62316.6 62318.2         -1.57268
//Pad  7  62321.6 62322.9         -1.30293
//Pad 15  62328.8 62330.2         -1.37671

//Carbon
//Pad  1  62319.6 62321           -1.41484
//Pad  7  62332.3 62332.9         -0.613941
//Pad 15  62344.2 62344.2         -0.0432466

//Siliclon
//Pad  1  62319.6 62321           -1.4693
//Pad  7  62322.6 62322.9         -0.252632
//Pad 15  62321.2 62321.5         -0.287339

//Copper
//Pad  1  62329.4 62330           -0.624483
//Pad  7  62356.6 62355.1         1.48586
//Pad 15  62274.2 62274.8         -0.606117

//Silver
//Pad  1  62379.5 62379.7         -0.146748
//Pad  7  62224.7 62233           -8.31598
//Pad 15  61920.8 61920.9         -0.137715

//Tungstern
//Pad  1  62278.5 62279.6         -1.03711
//Pad  7  60988.4 60991.3         -2.932
//Pad 15  59923.9 59921.2         2.68198

