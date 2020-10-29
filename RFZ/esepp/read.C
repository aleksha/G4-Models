{

 TH1F*h = new TH1F("h",";T, MeV; entries",150,1.5,3);
 TNtuple * ntp = (TNtuple*)_file0->Get("ntp;1");
// ntp->Print();
 TCanvas* canv = new TCanvas();
 ntp->Draw("E_p-938.272>>h");
 canv->Print("TEMP.png");
}
