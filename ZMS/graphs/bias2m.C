
{
  double x[6] = {0, 1, 2, 3, 4, 5};
  double dx[6] = {0,0,0,0,0,0};
  double y[6]={49815.1, 49950.8, 50087.5, 50225.2, 50364.3, 50504.9};
  double dy[6] = {40, 40, 41, 41, 42, 43};

  g = new TGraphErrors(6,x,y,dx,dy);
  g->SetLineWidth(2);
  g->SetLineColor(1);
  g->SetMarkerColor(1);
  g->SetMarkerStyle(24);

  g->GetXaxis()->SetTitle("Angla, deg.");
  //g->GetYaxis()->SetTitle("Start time, ns");
  g->SetTitle("5 MeV proton");

  TCanvas* canv = new TCanvas("canv","canv", 700,700);
  g->Draw("APL");
  canv->Print("Z_bias_5MeV.png");
  canv->Close();

  gSystem->Exit(0);

}

/*
Pad 1   49815.1 48571.9
Pad     39.7973 42.4058

Pad 1   49950.8 48702.7
Pad     40.2503 39.3675

Pad 1   50087.5 48824.8
Pad     40.6367 36.626

Pad 1   50225.2 48938.3
Pad     41.2133 34.1278

Pad 1   50364.3 49043.5
Pad     41.7027 32.1574

Pad 1   50504.9 49139.8
Pad     42.5258 31.3711


*/
