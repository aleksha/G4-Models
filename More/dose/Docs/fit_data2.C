#define n 48
#define Xmin 0.143791
#define Xmax 2.18736
#define Ymin 0.150418
#define Ymax 3.12535
void fit_data2(TString mode = "looks"){

    double x,y;
    std::ifstream fOUT("./data.txt" , std::ios::in);

    double xx[n], yy[n];
    int cntr = 0;

    double xmin = 100000000000.;
    double xmax =-100000000000.;
    double ymin = 100000000000.;
    double ymax =-100000000000.;

    if(mode=="look"){
      while( fOUT >> x >> y ){
        cntr++;
        if(x<xmin) xmin=x;
        if(y<ymin) ymin=y;
        if(x>xmax) xmax=x;
        if(y>ymax) ymax=y;
      } fOUT.close();
      cout << "LOOK: " << cntr << " (x,y)-data points found.\n";
      cout << "#define Xmin " << xmin << "\n";
      cout << "#define Xmax " << xmax << "\n";
      cout << "#define Ymin " << ymin << "\n";
      cout << "#define Ymax " << ymax << "\n";
    }
    else{
      while( fOUT >> x >> y ){
        xx[cntr] = x ; yy[cntr] = y/Ymax;
        cntr++;
      } fOUT.close();
      cout << "LOAD: " << cntr << " (x,y)-data points loaded.\n";

      gr = new TGraph(n,xx,yy);
      gr->SetMarkerStyle(20);
      gr->SetTitle(" ");
      gr->GetXaxis()->SetTitle("T_{e}, MeV");
      gr->GetXaxis()->SetRangeUser(0,2.5);
      gr->GetYaxis()->SetTitle("Yelds, a.u.");
      TCanvas* canv = new TCanvas("canv","canv",700,700);
      gStyle->SetOptStat(0);
      //gPad->SetLogy();

      TSpline *s3 = new TSpline3("s3",gr);
      s3->SetLineColor(kOrange+2);
      s3->SetLineWidth(3);

      gr->Draw("AP");
      s3->Draw("same");
      canv->Print("c.png");
    }


    gSystem->Exit(0);
}
