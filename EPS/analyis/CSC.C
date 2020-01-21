

double Gatti(double lambda, double K3 = 0.45){
    double sK3 = TMath::Sqrt(K3) ;
    double K2 = 0.5*TMath::Pi()*( 1.-0.5*sK3);
    double K1 = 0.25*K2*sK3*TMath::ATan(sK3);
    double tKl = TMath::Power( TMath::TanH(K2*lambda) ,2 );
    double Gamma = K1*(1.-tKl)/(1.+K3*tKl);

    return Gamma;
}

int nTrk(TH1F* histo){
    int switch_sign = 0;
    for(int jj=1;jj<histo->GetNbinsX()-1;jj++){
        if(histo->GetBinContent(jj)==0 && histo->GetBinContent(jj+1)>0){
            switch_sign++;
        }
    }
    return switch_sign;
}

int Gap(TH1F* histo){
    int switch_sign = 0;
    int bins=0;
    for(int jj=1;jj<histo->GetNbinsX()-1;jj++){
        if(switch_sign==1 && histo->GetBinContent(jj+1)==0) bins++;
        if(histo->GetBinContent(jj)==0 && histo->GetBinContent(jj+1)>0){
            if(switch_sign==1){return bins;}
            switch_sign++;
        }
    }
    return -1;
}

void CSC(){

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

          // smear raw histogram with Gatti function

          // get charge on strips

          if(ev==100){
//              hrCSC2->Draw();
              //cout << "---> " << ideal/Ev << "  " << real/Ev << endl;
              for(int tt=0;tt<7;tt++) cout << "---> " << tt << "  " << mult[tt] << endl;
              //hrCSC1->Draw();
              canv->Print("EVENT.C");
              gSystem->Exit(0);
              for(int kk=0;kk<cntr;kk++){

              }

          }
          mult[nTrk( hrCSC1 )]++;

          if(nTrk( hrCSC1 )==2){
              //cout << "****> " << EVENT << "  " << 100.*Gap( hrCSC1 )/4000. << " mm" << endl;
              hSDV->Fill(100.*Gap( hrCSC1 )/4000., hsCSC1->GetStdDev() );
              //hSDV->Draw();
              //canv->Update();
          }

          if(nTrk( hrCSC1 )==1){
              //cout << "****> " << EVENT << "  " << 100.*Gap( hrCSC1 )/4000. << " mm" << endl;
              hOTE->Fill( hsCSC1->GetStdDev() );
              hOTE->Draw();
              canv->Update();
          }

          //cout << ev << "  " << nTrk( hrCSC1 ) << endl;
          /*if( nTrk( hrCSC1 )==1  && nTrk( hrCSC2 )==1 ){
             ideal += 1000.*hrCSC1->GetMeanError();
             real  += 1000.*hsCSC1->GetMeanError();
             m1[cntr] = 1000.*hsCSC1->GetMeanError(); mv1+=m1[cntr];
             m2[cntr] = 1000.*hsCSC2->GetMeanError(); mv1+=m1[cntr];
             cntr++;
             Ev += 1.; 
          }
          else{
              cout << EVENT << endl;
              cout << ev << "\t" << 1000.*hrCSC1->GetMean() << "+-" << 1000.* hrCSC1->GetMeanError()
                         << "\t" << 1000.*hrCSC2->GetMean() << "+-" << 1000.* hrCSC2->GetMeanError() << endl;
              cout << ev << "\t" << 1000.*hsCSC1->GetMean() << "+-" << 1000.* hsCSC1->GetMeanError()
                         << "\t" << 1000.*hsCSC2->GetMean() << "+-" << 1000.* hsCSC2->GetMeanError() << endl;
          }*/
          if(!(ev%101)){
              int ss = 0;
              int ms = 0;
             
              for(int tt=0;tt<7;tt++)  ss = ss + mult[tt];

              ms = ev - ss;
              //cout << ms << endl;
              //cout << "---> 0  " << 100.*ms/(ev-1) << " %"<< endl;
              //for(int tt=1;tt<7;tt++)  cout << "---> " << tt << "  " << 100.*mult[tt]/(ev-1) << " %"<< endl;
              //cout << endl;
          }
          hrCSC1->Reset(); hrCSC2->Reset();
          hsCSC1->Reset(); hsCSC2->Reset();
          EVENT = ev;
      }

      n_steps = int(dE*1000.*1000./15.);
    //  cout << n_steps << endl;

      for(int step = 0; step<n_steps; step++){
          xc = xi + (0.5+step)*(xf-xi)/double(n_steps);

          if(xc>-30 && xc<30){
              if(vol == 2){ hrCSC1->Fill( xc ); }
              if(vol == 3){ hrCSC2->Fill( xc ); }

              for(int jj=0;jj<601;jj++){
                  if(vol == 2){ hsCSC1->Fill( xc+xx[jj], yd[jj] ); }
                  if(vol == 3){ hsCSC2->Fill( xc+xx[jj], yd[jj] ); }
              }
          }
      }

       
    }
    fOUT.close();

}