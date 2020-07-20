
{
  double x[6] = {0, 1, 2, 3, 4, 5};
  double dx[6] = {0,0,0,0,0,0};
  double y[6]={48571.9, 48702.7, 48824.8, 48938.3, 49043.5, 49139.8};
  double dy[6] = {42, 39, 36, 34, 32, 31};
  double z[6]={48880, 49014.7, 49145.4, 49272.8, 49396.9, 49516.3};
  double dz[6] = {64, 63, 63, 63, 63, 62};

  g = new TGraphErrors(6,x,y,dx,dy);
  h = new TGraphErrors(6,x,z,dx,dz);
  g->SetLineWidth(2);
  g->SetLineColor(1);
  g->SetMarkerColor(1);
  g->SetMarkerStyle(20);

  h->SetLineWidth(2);
  h->SetLineColor(2);
  h->SetMarkerColor(2);
  h->SetMarkerStyle(24);

  g->GetXaxis()->SetTitle("Angla, deg.");
  g->GetYaxis()->SetRangeUser(48500, 49600);
  //g->GetYaxis()->SetTitle("Start time, ns");
  g->SetTitle("5 MeV proton");

  TCanvas* canv = new TCanvas("canv","canv", 700,700);
  g->Draw("APL");
  h->Draw("same PL");
  canv->Print("Z_bias_5MeV.png");
  canv->Close();

  gSystem->Exit(0);

}


/*
4
Pad 0   49828.2 48568.1
Pad     192.58  72.5043

Pad 1   49821.3 48575.8
Pad     75.0593 67.4105

Pad 2   49822.8 48580.3
Pad     171.234 171.726

5

Pad 0   49816.1 48563.6
Pad     37.1028 90.5692

Pad 1   49815.1 48571.9
Pad     39.7973 42.4058

Pad 2   49812   48567.8
Pad     190.565 164.984

Pad 3   49822.9 48576.3
Pad     257.558 258.627

7

Pad 0   49816.3 48555
Pad     50.2158 131.009

Pad 1   49818.3 48575.4
Pad     33.0894 39.7246

Pad 2   49827.4 48583.7
Pad     109.814 111.853

Pad 3   49839.7 48591.1
Pad     218.594 223.22

Pad 4   49850.4 48603.2
Pad     396.133 383.25

Pad 5   49869.2 48620.3
Pad     418.629 429.444

9

Pad 0   49817.8 48551.6
Pad     62.7255 158.811

Pad 1   49817   48573.2
Pad     26.2966 45.5264

Pad 2   49825.3 48577
Pad     111.194 104.639

Pad 3   49834.7 48597.1
Pad     334.037 250.337

Pad 4   49819.1 48601
Pad     267.737 459.791

Pad 5   49818.2 48603.1
Pad     415.996 486.863

Pad 6   49837.8 48601.8
Pad     540.482 513.198

Pad 7   49831.8 48621.
Pad     676.489 622.239
*/
