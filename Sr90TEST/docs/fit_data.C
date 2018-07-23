#define n 48
#define Xmin 0.143791
#define Xmax 2.18736
#define Ymin 0.150418
#define Ymax 3.12535
void fit_data(TString mode = "looks"){

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
        xx[cntr] = (x-Xmin)/(Xmax-Xmin) ; yy[cntr] = y/Ymax;
        cntr++;
      } fOUT.close();
      cout << "LOAD: " << cntr << " (x,y)-data points loaded.\n";

      TF1* func = new TF1("func","pol6[0]",0,1);
      TF1* ber4 = new TF1("ber4","[0]*x**4+[1]*4*x**3*(1-x)+[2]*6*x**2*(1-x)**2+[3]*4*x*(1-x)**3+[4]*(1-x)**4",0,1);
      TF1* ber5 = new TF1("ber5","[0]*x**5+[1]*5*x**4*(1-x)+[2]*10*x**3*(1-x)**2+[3]*10*x**2*(1-x)**3+[4]*5*x*(1-x)**4+[5]*(1-x)**5",0,1);
      TF1* ber6 = new TF1("ber6","[0]*x**6+[1]*6*x**5*(1-x)+[2]*15*x**4*(1-x)**2+[3]*20*x**3*(1-x)**3+[4]*15*x**2*(1-x)**4+[5]*6*x*(1-x)**5+[6]*(1-x)**6",0,1);


      ber4->SetParLimits(0,0,10);
      ber4->SetParLimits(1,0,10);
      ber4->SetParLimits(2,0,10);
      ber4->SetParLimits(3,0,10);
      ber4->SetParLimits(4,0,10);

      ber5->SetParLimits(0,0,10);
      ber5->SetParLimits(1,0,10);
      ber5->SetParLimits(2,0,10);
      ber5->SetParLimits(3,0,10);
      ber5->SetParLimits(4,0,10);
      ber5->SetParLimits(5,0,10);

      ber6->SetParLimits(0,0,10);
      ber6->SetParLimits(1,0,10);
      ber6->SetParLimits(2,0,10);
      ber6->SetParLimits(3,0,10);
      ber6->SetParLimits(4,0,10);
      ber6->SetParLimits(5,0,10);
      ber6->SetParLimits(6,0,10);

      func->SetLineWidth(2);
      func->SetLineColor(2);
      ber4->SetLineWidth(2);
      ber4->SetLineColor(4);
      ber5->SetLineWidth(2);
      ber5->SetLineColor(kGreen+3);
      ber6->SetLineWidth(2);
      ber6->SetLineColor(1);

      gr = new TGraph(n,xx,yy);
      gr->SetMarkerStyle(20);
      gr->SetTitle(" ");
      gr->GetXaxis()->SetTitle("T_{e}, MeV");
      gr->GetXaxis()->SetRangeUser(0,1);
      gr->GetYaxis()->SetTitle("Yelds, a.u.");
      TCanvas* canv = new TCanvas("canv","canv",700,700);
      gStyle->SetOptStat(0);
      //gPad->SetLogy();
      gr->Fit("func");
      gr->Fit("ber4","M");
      gr->Fit("ber5","M");
      gr->Fit("ber6","M");
      gr->Draw("AP");
      func->Draw("same");
      ber4->Draw("same");
      ber5->Draw("same");
      ber6->Draw("same");
      canv->Print("c.png");
    }


    gSystem->Exit(0);
}
