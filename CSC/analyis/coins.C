void coins(){


    int ev, vol, tr, st, code, c;
    double dE, E, xi, yi, zi, ti, xf, yf, zf, tf;
    int n_steps;
    double xc;

    std::ifstream fOUT("./sci.data" , std::ios::in);

    double ideal  = 0.;
    double missed = 0.;
    double real   = 0.;
    double Ev     = 0.;

    int cntr=0.;
    int mult[7] = {0,0,0,0,0,0,0};
    double m1[1000],m2[1000];
    double mv1,sdv1,m2,sdv2,df,sdf;

    bool isSC1 = false;
    bool isCSC = false;
    bool isSC2 = false;

    bool trSC1 = false;
    bool trCSC = false;
    bool trSC2 = false;

    double dE_SC1 = 0.;
    double dE_CSC = 0.;
    double dE_SC2 = 0.;

    int EVENT = 0;
    while( fOUT >> ev >> tr >> st >> vol >> dE >> code >> c >> E >> xf >> yf >> zf >> tf ){
      if(ev>EVENT){

          if (trSC1 &&  trCSC && trSC2) ideal = ideal  + 1.;
          if (isSC1 &&  isCSC && isSC2) real  = real   + 1.;
          if (isSC1 && !isCSC && isSC2) missed = missed + 1.;

          isSC1 = false; dE_SC1=0.;
          isCSC = false; dE_CSC=0.;
          isSC2 = false; dE_SC2=0.;

          trSC1 = false;
          trCSC = false;
          trSC2 = false;

          EVENT = ev;
      }

      if(vol == 0) { dE_SC1 += dE ; isSC1 = true; }
      if(vol == 6) { dE_CSC += dE ; isCSC = true; }
      if(vol ==15) { dE_SC2 += dE ; isSC2 = true; }

      if(vol == 0 && code == 2212 && tr==1 ) { trSC1 = true; }
      if(vol == 6 && code == 2212 && tr==1 ) { trCSC = true; }
      if(vol ==15 && code == 2212 && tr==1 ) { trSC2 = true; }

    }
    fOUT.close();

    cout << "---> All fired   "  << 100.*real  /ev  << " %"<< endl;
    cout << "---> True proton "  << 100.*ideal /ev  << " %"<< endl;
    cout << "---> No CSC      "  << 100.*missed/ev  << " %"<< endl;

    gSystem->Exit(0);
}
