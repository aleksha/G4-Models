{
    int ev, vol, tr, st, code, c;
    double dE, E, x, y, z, t, px, py, pz, m;
    double Energy, Momentum, Kinetic;

    std::ifstream fOUT("./out.data" , std::ios::in);

    TH1F* h_Eg = new TH1F("h_Eg",";E, MeV; Entries", 250, 0, 500 );
    TH1F* h_Ee = new TH1F("h_Ee",";E, MeV; Entries", 250, 0, 500 );
    TH1F* h_Ep = new TH1F("h_Ep",";E, MeV; Entries", 250, 0, 500 );

    TH1F* h_Tpr = new TH1F("h_Tpr","Protons;T, MeV; Entries", 100, 0, 2000 );
    TH1F* h_Tpi = new TH1F("h_Tpi","Pions;T, MeV; Entries", 100, 0, 2000 );

    TH1F* hAng = new TH1F("hAng",";#theta_{#mu}, #murad; Entries", 250, 0, 500 );

    h_Eg->SetLineWidth(2); h_Eg->SetLineColor(1); h_Eg->SetFillColor(1); h_Eg->SetFillStyle(3004);
    h_Ee->SetLineWidth(2); h_Ee->SetLineColor(2); h_Ee->SetFillColor(2); h_Ee->SetFillStyle(3005);
    h_Ep->SetLineWidth(2); h_Ep->SetLineColor(4); h_Ep->SetFillColor(4); h_Ep->SetFillStyle(3144);

    int cntr[6] = {0,0,0,0,0,0};
    int m020=0;
    int m050=0;
    int m100=0;
    int m200=0;
    int m300=0;
    int m500=0;
    int m1k =0;

    while( fOUT >> ev >> tr >> st >> vol >> dE >> code >> c >> E >> x >> y >> z >> t >> px >> py >> pz >> m ){
      //if( !(ev%500000) && ev>0)  cout << ev << "\t" << 1.*cntr[0]/ev << "\t" << 1.*cntr[1]/ev << "\t" << 1.*cntr[2]/ev  << endl;
      Energy   = sqrt(m*m+px*px+py*py+pz*pz);
      Momentum = sqrt(px*px+py*py+pz*pz);
      Kinetic = Energy - m;
      if(code == 22){ h_Eg->Fill( Energy ); cntr[0]++; }
      if(code == 11){ h_Ee->Fill( Energy ); cntr[1]++; }
      if(code ==-11){ h_Ep->Fill( Energy ); cntr[2]++; }
      if(code == -211 || code == 211){ cntr[3]++; h_Tpi->Fill( Kinetic ); }//cout << "pion event " << ev << endl; }
      if(code == 2212 ){ cntr[4]++; h_Tpr->Fill(Kinetic); ; cout << "proton event " << ev << endl; }
      if(code == 13 ){ cntr[5]++; }
      if(code == -11 || code == 11){
          if( Energy>  20 )  m020++;
          if( Energy>  50 )  m050++;
          if( Energy> 100 )  m100++;
          if( Energy> 200 )  m200++;
          if( Energy> 300 )  m300++;
          if( Energy> 500 )  m500++;
          if( Energy>1000 )  m1k++;
      }


      if( tr==1 )    { hAng->Fill( 1000000.*sqrt(x*x+y*y)/z );}
    }
    fOUT.close();

    TCanvas* canv = new TCanvas("canv","canv",800,400);
    canv->Divide(2);
    canv->cd(1);
    gPad->SetLogy();
    hAng->Draw();
    canv->cd(2);
    gPad->SetLogy();
    gStyle->SetOptStat(0);

    h_Ee->GetXaxis()->SetRangeUser(10,h_Ee->GetMaximum());
    h_Ee->Draw();
    h_Eg->Draw("same");
    h_Ep->Draw("same");

    double Y_pos = h_Ee->GetMaximum()*0.8;
    TString s0; s0.Form("%d #gamma"    ,cntr[0]);
    TString s1; s1.Form("%d e^{#minus}",cntr[1]);
    TString s2; s2.Form("%d e^{#plus}" ,cntr[2]);

    tt = new TLatex(150, Y_pos     , "10M muons on wall");
    t0 = new TLatex(250, Y_pos/3.  , s0 );
    t1 = new TLatex(250, Y_pos/9.  , s1 ); t1->SetTextColor(2);
    t2 = new TLatex(250, Y_pos/27. , s2 ); t2->SetTextColor(4);

    tt.Draw(); t0.Draw(); t1.Draw(); t2.Draw();
    canv->Update();
    canv->Print("TEMP.png");
    canv->Close();

    TCanvas* canv2 = new TCanvas("canv2","canv2",800,400);
    canv2->Divide(2);
    canv2->cd(1);
    gPad->SetLogy();
    gStyle->SetOptStat(0);
    h_Tpi->Draw();
    canv2->cd(2);
    gPad->SetLogy();
    gStyle->SetOptStat(0);
    h_Tpr->Draw();
    canv2->Update();
    canv2->Print("HADRONS.png");
    canv2->Close();



    cout << "\n\n"               ;
    cout << "   SUMMARY:\n"      ;
    cout << "   --------\n"    ;
    cout << " mu     : " << cntr[5] << endl;
    cout << " gamma  : " << cntr[0] << endl;
    cout << " e-     : " << cntr[1] << endl;
    cout << " e+     : " << cntr[2] << endl;
    cout << " pion   : " << cntr[3] << endl;
    cout << " proton : " << cntr[4] << endl;
    cout << "\n\n";
    cout << "   Table for e- and e+:\n"      ;
    cout << "   --------------------\n"    ;
    cout << " > 20 MeV : " << m020 << endl;
    cout << " > 50 MeV : " << m050 << endl;
    cout << " >100 MeV : " << m100 << endl;
    cout << " >200 MeV : " << m200 << endl;
    cout << " >300 MeV : " << m300 << endl;
    cout << " >500 MeV : " << m500 << endl;
    cout << " >1   GeV : " << m1k  << endl;
    gSystem->Exit(0);

}
