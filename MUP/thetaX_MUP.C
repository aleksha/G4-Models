void thetaX_MUP(){

    int ev, vol, tr, st, code, c;
    double dE, E, xi, yi, zi, ti, xf, yf, zf, tf;
    int n_steps;
    double xc;

    std::ifstream fOUT("./out.data" , std::ios::in);

    TH1F* hTHETAx = new TH1F("hTHETAx",";#theta_{x}, #murad;Events", 320, -80, 80);

    TCanvas* canv = new TCanvas("canv","canv",600,600);
    //TH2F* hSDV = new TH2F("hSDV",";#Delta x, mm; StdDev, mm", 50, 0, 50, 50, 0, 25);
    //hTHETAx->SetMarkerStyle(20);

    TVector3 vec_ini, vec_out;
    double xx[4];
    double yy[4];
    double zz[4];
    bool fired[4] = {false, false, false, false};

    double ideal = 0.;
    double real  = 0.;
    double Ev    = 0.;

    int cntr=0.;
    int mult[7] = {0,0,0,0,0,0,0};
    double m1[1000],m2[1000];
    double mv1,sdv1,m2,sdv2,df,sdf;

    int EVENT = 0;
    while( fOUT >> ev >> tr >> st >> vol >> dE >> code >> c >> E >> xi >> yi >> zi >> ti >> xf >> yf >> zf >> tf ){
      if(ev>EVENT){
          if( fired[2] ){
              hTHETAx->Fill( 1000.*1000.*xx[2]/(zz[2]+885.)  );
          }
          for(int ii=0;ii<4;ii++) fired[ii] = false;
          EVENT = ev;
      }

      if(tr == 1){
          xx[vol] = xi;
          yy[vol] = yi;
          zz[vol] = zi;
          fired[vol] = true;
      }

    }
    fOUT.close();
    hTHETAx->Draw();
    hTHETAx->Fit("gaus");
    canv->Print("TEMP.png");
    gSystem->Exit(0);

}
