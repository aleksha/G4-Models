{

 TH2F*h = new TH2F("h",";#theta_R, deg.; #theta_e, deg.",200,70,90.,200,4,24);
 TNtuple * ntp = (TNtuple*)_file0->Get("ntp;1");
// ntp->Print();
 TCanvas* canv = new TCanvas();
// ntp->Draw("(180.*theta_l/3.14159265):(180.*theta_p/3.14159265)","(180.*theta_p/3.14159265)>80");
 ntp->Draw("(E_p-938.272):(180.*theta_p/3.14159265)","(180.*theta_p/3.14159265)>80");
 canv->Print("TEMP.png");
}
