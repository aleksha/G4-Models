//point-like
//Pad  1  62316.6 62318.2         -1.57268
//Pad  7  62321.6 62322.9         -1.30293
//Pad 16  62330.4 62331.7         -1.3312

//100 um
//Pad  1  62303.7 62305.4         -1.67679
//Pad  7  62307.6 62309.2         -1.558
//Pad 16  62309.7 62311           -1.23959

//200 um
//Pad  1  62293.8 62295.2         -1.3708
//Pad  7  62297.5 62299           -1.45029
//Pad 16  62299.5 62300.7         -1.24429

//400um
//Pad  1  62273.1 62274.8         -1.69118
//Pad  7  62276.5 62277.8         -1.31406
//Pad 16  62278.2 62279.5         -1.31228

//1 mm
//Pad  1  62211.4 62213           -1.59131
//Pad  7  62214.1 62215.4         -1.30392
//Pad 16  62217.9 62219.1         -1.2201

//2 mm
//Pad  1  62105.8 62107.2         -1.40202
//Pad  7  62107.1 62108.4         -1.31527
//Pad 16  62108.7 62109.9         -1.19596
{

  double x[6] = {0,0.1,0.2,0.4,1,2};
  double w[6] = {-1.57, -1.68, -1.37, -1.69, -1.59, -1.40};
  double y[6] = {-1.30, -1.65, -1.45, -1.31, -1.30, -1.31};
  double z[6] = {-1.33, -1.23, -1.24, -1.31, -1.22, -1.20};

  gw = new TGraph(6,x,w);
  gy = new TGraph(6,x,y);
  gz = new TGraph(6,x,z);

  gw->SetTitle(" ");
  gy->SetTitle(" ");
  gz->SetTitle(" ");

  gy->GetXaxis()->SetTitle("Beam radius, mm");
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
  canv->Print("Beams.png");
  canv->Close();
  gSystem->Exit(0);

}

//point-like
//Pad  1  62316.6 62318.2         -1.57268
//Pad  7  62321.6 62322.9         -1.30293
//Pad 16  62330.4 62331.7         -1.3312

//100 um
//Pad  1  62303.7 62305.4         -1.67679
//Pad  7  62307.6 62309.2         -1.558
//Pad 16  62309.7 62311           -1.23959

//200 um
//Pad  1  62293.8 62295.2         -1.3708
//Pad  7  62297.5 62299           -1.45029
//Pad 16  62299.5 62300.7         -1.24429

//400um
//Pad  1  62273.1 62274.8         -1.69118
//Pad  7  62276.5 62277.8         -1.31406
//Pad 16  62278.2 62279.5         -1.31228

//1 mm
//Pad  1  62211.4 62213           -1.59131
//Pad  7  62214.1 62215.4         -1.30392
//Pad 16  62217.9 62219.1         -1.2201

//2 mm
//Pad  1  62105.8 62107.2         -1.40202
//Pad  7  62107.1 62108.4         -1.31527
//Pad 16  62108.7 62109.9         -1.19596

