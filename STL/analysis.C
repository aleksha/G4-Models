{
    int ev, vol, tr, st, code, c;
    double dE, E, x, y, z, t, px, py, pz, m;

    std::ifstream fOUT("./out.data" , std::ios::in);

    TH1F* h_Eg = new TH1F("h_Eg",";E, MeV; Entries", 150, 0, 150 );
    TH1F* h_Ee = new TH1F("h_Ee",";E, MeV; Entries", 150, 0, 150 );
    TH1F* h_Ep = new TH1F("h_Ep",";E, MeV; Entries", 150, 0, 150 );

    TH1F* hAng = new TH1F("hAng",";#theta_{#mu}, #murad; Entries", 250, 0, 500 );

    h_Eg->SetLineWidth(2); h_Eg->SetLineColor(1); h_Eg->SetFillColor(1); h_Eg->SetFillStyle(3004);
    h_Ee->SetLineWidth(2); h_Ee->SetLineColor(2); h_Ee->SetFillColor(2); h_Ee->SetFillStyle(3005);
    h_Ep->SetLineWidth(2); h_Ep->SetLineColor(4); h_Ep->SetFillColor(4); h_Ep->SetFillStyle(3144);

    int cntr[3] = {0,0,0};

    while( fOUT >> ev >> tr >> st >> vol >> dE >> code >> c >> E >> x >> y >> z >> t >> px >> py >> pz >> m ){
      if( !(ev%50001) && ev>0) {
          cout << ev << "\t" << 1.*cntr[0]/ev << "\t" << 1.*cntr[1]/ev << "\t" << 1.*cntr[2]/ev  << endl;
      }
      if(code == 22){ h_Eg->Fill( sqrt(m*m+px*px+py*py+pz*pz) ); cntr[0]++; }
      if(code == 11){ h_Ee->Fill( sqrt(m*m+px*px+py*py+pz*pz) ); cntr[1]++; }
      if(code ==-11){ h_Ep->Fill( sqrt(m*m+px*px+py*py+pz*pz) ); cntr[2]++; }

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

    h_Ee->Draw();
    h_Eg->Draw("same");
    h_Ep->Draw("same");

    double Y_pos = h_Ee->GetMaximum()*0.8;
    TString s0; s0.Form("%d #gamma"    ,cntr[0]);
    TString s1; s1.Form("%d e^{#minus}",cntr[1]);
    TString s2; s2.Form("%d e^{#plus}" ,cntr[2]);

    tt = new TLatex(20, Y_pos     , "1M muons on wall");
    t0 = new TLatex(40, Y_pos/3.  , s0 );
    t1 = new TLatex(40, Y_pos/9.  , s1 ); t1->SetTextColor(2);
    t2 = new TLatex(40, Y_pos/27. , s2 ); t2->SetTextColor(4);

    tt.Draw(); t0.Draw(); t1.Draw(); t2.Draw();
    canv->Update();
    canv->Print("TEMP.png");
    gSystem->Exit(0);

}
