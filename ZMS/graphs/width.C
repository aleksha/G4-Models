
{
  double x[6] = {0, 1, 2, 3, 4, 5};
  double dx[6] = {0,0,0,0,0,0};
  double y[6]={2607, 2615, 2640, 2679, 2734, 2803};
  double dy[6] = {22, 25, 28, 32, 38, 42};

  g = new TGraphErrors(6,x,y,dx,dy);
  g->SetLineWidth(2);
  g->SetLineColor(1);
  g->SetMarkerColor(1);
  g->SetMarkerStyle(21);

  g->GetXaxis()->SetTitle("Angla, deg.");
  g->GetYaxis()->SetTitle("Signal length, ns");
  g->SetTitle("5 MeV proton");

  TCanvas* canv = new TCanvas("canv","canv", 700,700);
  g->Draw("APL");
  canv->Print("Length_5MeV.png");
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
