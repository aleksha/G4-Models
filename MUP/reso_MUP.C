void reso_MUP(){

    double h = 3.; // anode-cathode distance

    double ll[601], xx[601], yd[601];
    double sum = 0.;
    for(int ii=0;ii<601;ii++){
        ll[ii] = 0.1*ii-3.;
        xx[ii] = h*ll[ii];
        yd[ii] = Gatti( ll[ii] , 0.45 ); 
        sum = sum + yd[ii];
    }

    for(int ii=0;ii<601;ii++){
        yd[ii] = yd[ii]/sum; 
    }

    int ev, vol, tr, st, code, c;
    double dE, E, xi, yi, zi, ti, xf, yf, zf, tf;
    int n_steps;
    double xc;

    std::ifstream fOUT("./csc50.data" , std::ios::in);

    TH1F* hrCSC1 = new TH1F("hrCSC1",";x,mm; #Delta E, electrons", 4000, -50., 50 ); 
    TH1F* hsCSC1 = new TH1F("hsCSC1",";x,mm; #Delta E, electrons", 40 ,  -50., 50 ); 
    TH1F* hhCSC1 ;

    TH1F* hrCSC2 = new TH1F("hrCSC2",";x,mm; #Delta E, electrons", 4000, -50., 50 ); 
    TH1F* hsCSC2 = new TH1F("hsCSC2",";x,mm; #Delta E, electrons", 40  , -50., 50 ); 
    TH1F* hhCSC2 ;

    TH1F* hOTE = new TH1F("hOTE",";StdDev, mm;Events",80, 0, 4);

    TCanvas* canv = new TCanvas("canv","canv",600,600);
    TH2F* hSDV = new TH2F("hSDV",";#Delta x, mm; StdDev, mm", 50, 0, 50, 50, 0, 25);
    hSDV->SetMarkerStyle(20);

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
          if( fired[0] && firef[1] && fired[2] && fired[3] ){
              vec_ini.SetXYZ( xx[1]-xx[0] , yy[1]-yy[0], 5000.)
              vec_out.SetXYZ( xx[3]-xx[2] , yy[3]-yy[2], 5000.)
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
    canv->Print("TEMP.png");
    gSystem->Exit(0);

}
