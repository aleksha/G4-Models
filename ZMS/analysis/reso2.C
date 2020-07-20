
{

  double y4[3] = { 73, 67, 171};
  double y5[4] = { 91, 42, 164, 258};
  double y7[6] = {131, 40, 112, 223, 383, 429};
  double y9[8] = {159, 46, 105, 250, 459, 483, 513, 622};

  double x4[3] = {0, 1, 2};
  double x5[4] = {0, 1, 2, 3};
  double x7[6] = {0, 1, 2, 3, 4, 5};
  double x9[8] = {0, 1, 2, 3, 4, 5, 6, 7};


  g4 = new TGraphErrors(3,x4,y4);
  g5 = new TGraphErrors(4,x5,y5);
  g7 = new TGraphErrors(6,x7,y7);
  g9 = new TGraphErrors(8,x9,y9);

  g4->SetLineWidth(2);
  g5->SetLineWidth(2);
  g7->SetLineWidth(2);
  g9->SetLineWidth(2);

  g4->SetLineColor(1);
  g5->SetLineColor(2);
  g7->SetLineColor(kGreen+3);
  g9->SetLineColor(4);

  g9->GetXaxis()->SetTitle("Pad number");
  g9->GetYaxis()->SetRangeUser(0,700);
  g9->SetTitle("Resolutio for Start Time");

  TCanvas* canv = new TCanvas("canv","canv", 700,700);
  g9->Draw("AL");
  g7->Draw("same L");
  g5->Draw("same L");
  g4->Draw("same L");
  canv->Print("Reso_StartTime_pad.png");
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
