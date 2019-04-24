void reso_MUP(){

    int ev, vol, tr, st, code, c;
    double dE, E, xi, yi, zi, ti, xf, yf, zf, tf;
    int n_steps;
    double xc;

    std::ifstream fOUT("./out.data" , std::ios::in);

    TH1F* hANG = new TH1F("hANG",";Angle, mrad;Events",100, 0, 1);

    TCanvas* canv = new TCanvas("canv","canv",600,600);
    //TH2F* hSDV = new TH2F("hSDV",";#Delta x, mm; StdDev, mm", 50, 0, 50, 50, 0, 25);
    hANG->SetMarkerStyle(20);

    TVector3 vec_ini, vec_out;
    double xx[4];
    double yy[4];
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
          if( fired[0] && fired[1] && fired[2] && fired[3] ){
              vec_ini.SetXYZ( xx[1]-xx[0] , yy[1]-yy[0], 5000.);
              vec_out.SetXYZ( xx[3]-xx[2] , yy[3]-yy[2], 5000.);
              hANG->Fill( 1000.*vec_out.Angle(vec_ini)  );
          }
          for(int ii=0;ii<4;ii++) fired[ii] = false;
          EVENT = ev;
      }

      if(tr == 1){
          xx[vol] = xi;
          yy[vol] = yi;
          fired[vol] = true;
      }

    }
    fOUT.close();
    hANG->Draw();
    canv->Print("TEMP.png");
    gSystem->Exit(0);

}
