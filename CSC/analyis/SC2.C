struct hit { int xi; int xf; double dE;};
struct hits{ hit h[100]; short n;      };

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

void SC2(){

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
    bool isSC3 = false;

    bool trSC1 = false;
    bool trCSC = false;
    bool trSC2 = false;
    bool trSC3 = false;

    double dE_SC1 = 0.;
    double dE_CSC = 0.;
    double dE_SC2 = 0.;
    double dE_SC3 = 0.;

    double ideal  = 0.;
    double missed = 0.;
    double real   = 0.;
    double triple = 0.;
    double lost_p = 0.;
    double Ev     = 0.;

    hits Hits;
    short  Steps[100];
    for(int qq=0;qq<100;qq++){ Steps[qq]=0;
      Hits.h[qq].xi=0; Hits.h[qq].xf=0; Hits.h[qq].dE=0; Hits.n=0; }

    TCanvas* canv = new TCanvas("canv","canv",700,700);

    TH1F* hCSC = new TH1F("hCSC",";x, mm;sihnal", 600, -30, 30);

    TH1F* hNtr = new TH1F("hNtr",";N_{trk};events",7,-0.5,6.5);
    TH1F* hCnd = new TH1F("hCnd",";N_{trk};events",7,-0.5,6.5);

    TH1F* hp_E = new TH1F("hp_E",";#DeltaE, keV;N", 99, 30, 3000);
    TH1F* hh_E = new TH1F("hh_E",";#DeltaE, keV;N", 99, 30, 3000);
    TH1F* he_E = new TH1F("he_E",";#DeltaE, keV;N", 99, 30, 3000);
    TH1F* ht_E = new TH1F("ht_E",";#DeltaE, keV;N", 99, 30, 3000);

    TH1F* hh_T = new TH1F("hh_T",";time, ns;Hits", 100, 0, 30);
    TH1F* he_T = new TH1F("he_T",";time, ns;Hits", 100, 0, 30);
    TH1F* ht_T = new TH1F("ht_T",";time, ns;Hits", 100, 0, 30);

    hp_E->SetLineWidth(2);
    hh_E->SetLineWidth(2);
    he_E->SetLineWidth(2);
    ht_E->SetLineWidth(2);

    hh_E->SetLineColor(4);
    he_E->SetLineColor(2);
    ht_E->SetLineColor(1);
    hp_E->SetLineColor(kGreen+3);

    hp_E->SetFillColor(kGreen+3);
    hh_E->SetFillColor(4);
    he_E->SetFillColor(2);

    hp_E->SetFillStyle(3004);
    hh_E->SetFillStyle(3004);
    he_E->SetFillStyle(3005);

    hh_T->SetLineWidth(2);
    he_T->SetLineWidth(2);
    hh_T->SetLineColor(4);
    he_T->SetLineColor(2);
    hh_T->SetFillColor(4);
    he_T->SetFillColor(2);
    ht_T->SetFillColor(kGreen+3);
    ht_T->SetLineWidth(2);
    ht_T->SetLineColor(kGreen+3);
    hh_T->SetFillStyle(3004);
    he_T->SetFillStyle(3005);


    hCnd->SetLineWidth(2);
    hCnd->SetLineColor(1);
    hCnd->SetFillColor(1);
    hCnd->SetFillStyle(3004);

    double dE_had = 0;
    double dE_em  = 0;
    double dE_in  = 0;

    int EVENT = 0;
    while( fOUT >> ev >> tr >> st >> vol >> dE >> code >> c >> E >> xi >> yi >> zi >> ti>> xf >> yf >> zf >> tf ){
      if(ev>EVENT){

          if(!(ev%500)) cout << "ev " << ev << endl;

          hNtr->Fill( nTrk(hCSC) );
          if (isSC1 && isSC3) hCnd->Fill( nTrk(hCSC) );

          Steps[Hits.n]++;
//          if(dE_had==0){ he_E->Fill( 1000.*dE_em  ); }
//          else{          hh_E->Fill( 1000.*dE_had ); }

          hp_E->Fill( 1000.*dE_in  );
          he_E->Fill( 1000.*dE_em  );
          hh_E->Fill( 1000.*dE_had );
          ht_E->Fill( 1000.*(dE_em + dE_had ) );


          dE_had = 0.; dE_em = 0.; dE_in = 0.;

          if (trSC1 &&  trCSC && trSC2) ideal = ideal  + 1.;
          if (isSC1 &&  isCSC && isSC2) real  = real   + 1.;
          if (isSC1 && !isCSC && isSC2) missed = missed + 1.;

          if (isSC1 &&  isCSC && isSC2 && isSC3) triple = triple  + 1.;


          if(isSC1 &&  isCSC && isSC2 && !trCSC && !trSC2){
             lost_p = lost_p + 1.;
             //cout << "====> " << EVENT << endl;
          }

          isSC1 = false; dE_SC1=0.;
          isCSC = false; dE_CSC=0.;
          isSC2 = false; dE_SC2=0.;
          isSC3 = false; dE_SC3=0.;

          trSC1 = false;
          trCSC = false;
          trSC2 = false;
          trSC3 = false;

          for(int qq=0;qq<100;qq++){
            Hits.h[qq].xi=0; Hits.h[qq].xf=0; Hits.h[qq].dE=0; Hits.n=0; }

          hCSC->Reset();
          EVENT = ev;
      }

      if(vol==6){
        Hits.h[Hits.n].xi = xi;  Hits.h[Hits.n].xf = xf;
        Hits.h[Hits.n].dE = dE;  Hits.n++;
        int n_steps = 1000.*1000.*dE / 30.;
        for(int step = 0; step<n_steps; step++){
          xc = xi + (0.5+step)*(xf-xi)/double(n_steps);
          if(xc>-30 && xc<30) hCSC->Fill( xc );
        }
      }//vol6

      if(vol == 0) { dE_SC1 += dE ; isSC1 = true; }
      if(vol == 6) { dE_CSC += dE ; isCSC = true; }
      if(vol ==15) { dE_SC2 += dE ; isSC2 = true; }
      if(vol ==16) { dE_SC3 += dE ; isSC3 = true; }

      if(vol == 0 && code == 2212 && tr==1 ) { trSC1 = true; }
      if(vol == 6 && code == 2212 && tr==1 ) { trCSC = true; }
      if(vol ==15 && code == 2212 && tr==1 ) { trSC2 = true; }
      if(vol ==16 && code == 2212 && tr==1 ) { trSC3 = true; ht_T->Fill(tf); dE_in = dE_in + dE;}

      if( vol==16 && dE>0 && (code == 2212 || code == 211 || code ==-211) ){
        dE_had = dE_had + dE;
        hh_T->Fill(tf);
      }
      if( vol==16 && dE>0 && (code ==   22 || code ==  11 || code == -11) ){
        dE_em  = dE_em  + dE;
        he_T->Fill(tf);
      }

    } fOUT.close();

    gStyle->SetOptStat(0);
    gPad->SetLogy();

    ht_E->Draw();
    //hh_E->Draw("same");
    //he_E->Draw("same");
    hp_E->Draw("same");
    canv->Print("Eloss_SC2_4c.png");

    hh_T->Draw();
    //he_T->Draw("same");
    ht_T->Draw("same");
    canv->Print("Time_SC2_4C.png");

    hNtr->Draw();
    hCnd->Draw("same");
    canv->Print("nTracks.png");

    cout << "\n\n\n";
    cout << "---> All fired    "  << 100.*real  /ev  << " %  ( " << real   << " )" << endl;
    cout << "---> Triple fired "  << 100.*triple/ev  << " %  ( " << triple << " )" << endl;
    cout << "---> True proton  "  << 100.*ideal /ev  << " %  ( " << ideal  << " )" << endl;
    cout << "---> Lost proton  "  << 100.*lost_p/ev  << " %  ( " << lost_p << " )" << endl;
    cout << "---> No CSC       "  << 100.*missed/ev  << " %  ( " << missed << " )" << endl;

//    cout << "\n\n\n";
//    for(int qq=0;qq<100;qq++)
//      cout << "~~> " << qq << " " << Steps[qq] << endl;

    gSystem->Exit(0);
}
