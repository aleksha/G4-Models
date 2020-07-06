
{
  double x[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double dx[9] = {0,0,0,0,0,0};
  double y[9]={35835, 71481, 107167, 142944, 178423, 214227, 249698, 285985, 320650};
  double dy[9] = {702, 1032, 1023, 1306, 1983, 1703, 2376, 2228, 3193};

  g = new TGraphErrors(9,x,y,dx,dy);
  g->SetLineWidth(2);
  g->SetLineColor(1);
  g->SetMarkerColor(1);
  g->SetMarkerStyle(24);

  g->GetXaxis()->SetTitle("T_{p}, MeV");
  g->GetYaxis()->SetTitle("E, a.u.");
  g->SetTitle(" ");

  TF1* f1 = new TF1("f1","[0]*x",0,20);

  TCanvas* canv = new TCanvas("canv","canv", 700,700);
  g->Draw("AP");
  g->Fit("pol1");
  g->Fit(f1);
  canv->Print("Energy_vs_Tp.png");
  canv->Close();

  gSystem->Exit(0);

}


/*
Pad 0   49818.3 48575.6
Pad     13.921  27.6678

Pad 0   49832.5 48589.6
Pad     13.8504 27.3557

Pad 0   49846.8 48603.1
Pad     13.8435 27.192

Pad 0   49860.8 48617
Pad     13.8452 27.057

Pad 0   49875   48630.4
Pad     13.8813 27.1938

Pad 0   49889.2 48643.6
Pad     14.0177 27.1619
*/
