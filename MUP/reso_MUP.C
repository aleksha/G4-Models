void reso_MUP(){

    int ev, vol, tr, st, code, c;
    double dE, E, xi, yi, zi, ti, xf, yf, zf, tf;
    int n_steps;
    double xc;

    std::ifstream fOUT("./out.data" , std::ios::in);

    TH1F* hANG  = new TH1F("hANG" ,";Angle, #murad;Events",40, 0, 200);
    TH1F* hSEC  = new TH1F("hSEC" ,";Angle, mrad;Events",40, 0, 200);
    TH1F* hFAKE = new TH1F("hFAKE",";Angle, mrad;Events",300, 0, 300);

    TCanvas* canv = new TCanvas("canv","canv",600,600);
    //TH2F* hSDV = new TH2F("hSDV",";#Delta x, mm; StdDev, mm", 50, 0, 50, 50, 0, 25);
    hANG->SetMarkerStyle(20);

    TVector3 vec_ini, vec_out;
    double xx[4], sx[4];
    double yy[4], sy[4];
    bool fired[4] = {false, false, false, false};
    bool secnd[4] = {false, false, false, false};

    double ideal = 0.;
    double real  = 0.;
    double Ev    = 0.;

    int cntr=0.;
    int mult[7] = {0,0,0,0,0,0,0};
    double m1[1000],m2[1000];
    double mv1,sdv1,m2,sdv2,df,sdf;

    int nSec  = 0;
    int nThr  = 0;
    int EVENT = 0;
    while( fOUT >> ev >> tr >> st >> vol >> dE >> code >> c >> E >> xi >> yi >> zi >> ti >> xf >> yf >> zf >> tf ){
      if(ev>EVENT){

          if( fired[0] && fired[1] && fired[2] && fired[3] ){
              vec_ini.SetXYZ( xx[1]-xx[0] , yy[1]-yy[0], 5000.);
              vec_out.SetXYZ( xx[3]-xx[2] , yy[3]-yy[2], 5000.);
              hANG->Fill( 1000.*1000.*vec_out.Angle(vec_ini)  );
          }
          if( secnd[2] && secnd[3] ){
              if( (sx[2]*sx[2]+sy[2]*sy[2])<900 && (sx[3]*sx[3]+sy[3]*sy[3])<900){
                    vec_ini.SetXYZ(           0 ,           0, 5000.);
                    vec_out.SetXYZ( sx[3]-sx[2] , sy[3]-sy[2], 5000.);
                    hSEC->Fill( 1000.*vec_out.Angle(vec_ini)  );
                    nSec++;
              }
          }
          if( fired[0] && fired[1] && fired[2] && fired[3] && (secnd[2] || secnd[3] ) ){
              nThr++;
              vec_ini.SetXYZ( xx[1]-xx[0] , yy[1]-yy[0], 5000.);
              if( secnd[2] )
                  vec_out.SetXYZ( xx[3]-sx[2] , yy[3]-sy[2], 5000.);
              else
                  vec_out.SetXYZ( sx[3]-xx[2] , sy[3]-yy[2], 5000.);
              hFAKE->Fill( 1000.*1000.*vec_out.Angle(vec_ini)  );
          }

          for(int ii=0;ii<4;ii++){ fired[ii] = false; secnd[ii] = false; }
          EVENT = ev;
      }

      if(tr == 1){
          xx[vol] = xi;
          yy[vol] = yi;
          fired[vol] = true;
      }
      else{
          if(E>0.010 && (xi*xi + yi*yi)<900){
              sx[vol] = xi;
              sy[vol] = yi;
              secnd[vol] = true;
          }
      }

    }
    fOUT.close();
    hANG->Draw();
    canv->Print("TEMP.png");
    hSEC->Draw();
    canv->Print("SECN.png");
    gPad->SetLogy();
    hFAKE->Draw();
    canv->Print("FAKE.png");
    cout << "Num.sec = " << nSec << endl;
    cout << "Three hits = " << nThr << endl;
    gSystem->Exit(0);

}
