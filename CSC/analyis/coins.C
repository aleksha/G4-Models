void coins(){


    int ev, vol, tr, st, code, c;
    double dE, E, xi, yi, zi, ti, xf, yf, zf, tf;
    int n_steps;
    double xc;

    std::ifstream fOUT("./sci.data" , std::ios::in);

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

    double ideal  = 0.;
    double missed = 0.;
    double real   = 0.;
    double lost_p = 0.;
    double Ev     = 0.;

    struct PType{ int Code; double dE_CSC; double dE_SC2; int n_CSC; int n_SC2; };
    PType AllTypes[6];
    for(int ii=0;ii<6;ii++){
      AllTypes[ii].Code   = 0 ;
      AllTypes[ii].dE_CSC = 0.;
      AllTypes[ii].dE_SC2 = 0.;
      AllTypes[ii].n_CSC  = 0 ;
      AllTypes[ii].n_SC2  = 0 ;
    };
    bool isIN = false;


    int EVENT = 0;
    while( fOUT >> ev >> tr >> st >> vol >> dE >> code >> c >> E >> xf >> yf >> zf >> tf ){
      if(ev>EVENT){

          if (trSC1 &&  trCSC && trSC2) ideal = ideal  + 1.;
          if (isSC1 &&  isCSC && isSC2) real  = real   + 1.;
          if (isSC1 && !isCSC && isSC2) missed = missed + 1.;

          if(isSC1 &&  isCSC && isSC2 && !trCSC && !trSC2){
             lost_p = lost_p + 1.;
             //cout << "====> " << EVENT << endl;
          }

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


      if(dE>0){
        isIN = false;
        for(int ii=0;ii<6;ii++){
          if(AllTypes[ii].Code==code && !isIN){
            isIN = true;
            if(vol==6){
              AllTypes[ii].dE_CSC = ( AllTypes[ii].dE_CSC*AllTypes[ii].n_CSC + dE ) / (1. + AllTypes[ii].n_CSC);
              AllTypes[ii].n_CSC++;
            }
            if(vol==15){
              AllTypes[ii].dE_SC2 = ( AllTypes[ii].dE_SC2*AllTypes[ii].n_SC2 + dE ) / (1. + AllTypes[ii].n_SC2);
              AllTypes[ii].n_SC2++;
            }
          }
        }
        if( !isIN ){
          for(int ii=0;ii<6;ii++){
            if( !isIN && AllTypes[ii].Code==0){
              AllTypes[ii].Code = code;
              if(vol==6){
                AllTypes[ii].dE_CSC = ( AllTypes[ii].dE_CSC*AllTypes[ii].n_CSC + dE ) / (1. + AllTypes[ii].n_CSC);
                AllTypes[ii].n_CSC++;
              }
              if(vol==15){
                AllTypes[ii].dE_SC2 = ( AllTypes[ii].dE_SC2*AllTypes[ii].n_SC2 + dE ) / (1. + AllTypes[ii].n_SC2);
                AllTypes[ii].n_SC2++;
              }
              isIN = true;
            }
          }
        }
      }


    } fOUT.close();

    cout << "\n\n\n";
    cout << "---> All fired   "  << 100.*real  /ev  << " %  ( " << real   << " )" << endl;
    cout << "---> True proton "  << 100.*ideal /ev  << " %  ( " << ideal  << " )" << endl;
    cout << "---> Lost proton "  << 100.*lost_p/ev  << " %  ( " << lost_p << " )" << endl;
    cout << "---> No CSC      "  << 100.*missed/ev  << " %  ( " << missed << " )" << endl;
// ---> All fired   66.1973 %  ( 33098 )
// ---> True proton 50.135 %  ( 25067 )
// ---> No CSC      0.402008 %  ( 201 )

    cout << "\n\n\n";
    for(int ii = 0;ii<6;ii++)
      if(AllTypes[ii].Code!=0)
        cout << "Code: " << AllTypes[ii].Code
             << "\t CSC: " << 1000.*AllTypes[ii].dE_CSC << " keV "
             << "  ( " << AllTypes[ii].n_CSC << " )"<< endl;


    cout << "\n\n\n";
    for(int ii = 0;ii<6;ii++)
      if(AllTypes[ii].Code!=0)
        cout << "Code: " << AllTypes[ii].Code
             << "\t SC2: " << 1000.*AllTypes[ii].dE_SC2 << " keV "
             << "  ( " << AllTypes[ii].n_SC2 << " )"<< endl;



    gSystem->Exit(0);
}
