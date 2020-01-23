void x_ESP(){

    TVector3 vtx;
    double vtx_z;
    double reso_si = 0.016;

    int ev, vol, tr, st, code, c;
    double dE, E, xi, yi, zi, ti, xf, yf, zf, tf;
    int n_steps;
    double xc;

    std::ifstream fOUT("./out.data" , std::ios::in);

    TH1F* hX      = new TH1F("Parameters" ,"10^{4} of 720 MeV/c electrons;x, mm;Events", 100, -50, 50);

    TCanvas* canv = new TCanvas("canv","canv",600,600);
    //TH2F* hSDV = new TH2F("hSDV",";#Delta x, mm; StdDev, mm", 50, 0, 50, 50, 0, 25);
    //hTHETAx->SetMarkerStyle(20);

    TVector3 vec_ini, vec_out;
    int    nh[4];
    double xx[4][5];
    double yy[4][5];
    double zz[4][5];
    int    cd[4][5];
    bool fired[4] = {false, false, false, false};

    double ideal = 0.;
    double real  = 0.;
    double Ev    = 0.;

    TVector3 v_in[25], v_out[25];
    TVector3 vv[4][25] ;
    bool     t_in[25], t_out[25];
    int      n_in   , n_out   ;
    double Angle;

    int cntr=0.;
    int mult[7] = {0,0,0,0,0,0,0};
    double m1[1000],m2[1000];
    double mv1,sdv1,m2,sdv2,df,sdf;

    int nTOT=0;
    int nADD=0;
    int EVENT = 0;
    int high_multp = 0;
    while( fOUT >> ev >> tr >> st >> vol >> dE >> code >> c >> E >> xi >> yi >> zi >> ti >> xf >> yf >> zf >> tf ){
      hX->Fill(xi);
    }
    TCanvas *canv = new TCanvas("canv","canv",600,600);
    hX->Draw();
    canv->Print("TEMP.png");
    gSystem->Exit(0);

}
