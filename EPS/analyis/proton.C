{
    int ev, vol, tr, st, code, c;
    double dE, E, x, y, z, t, px, py, pz, m;

    std::ifstream fOUT("./out50.data" , std::ios::in);

    TH1F* h_Tp = new TH1F("h_Tp",";T_{p}, MeV; Entries", 100, 900, 1000 ); 
    TH1F* h_Xp = new TH1F("h_Xp",";X_{p}, mm; Entries" , 1000, -1, 1 ); 
    TH1F* h_Ap = new TH1F("h_Ap",";#theta_{p_{p}}, mrad; Entries" , 150, 0, 150 ); 


    while( fOUT >> ev >> tr >> st >> vol >> dE >> code >> c >> E >> x >> y >> z >> t >> px >> py >> pz >> m ){
      if( !(ev%50000) && ev>0 ) {
          cout << ev << "\t" << sqrt(m*m+px*px+py*py+pz*pz)-m << endl;
      }
      if(code==2212){
          h_Tp->Fill(sqrt(m*m+px*px+py*py+pz*pz)-m);
          h_Xp->Fill(x);
          h_Ap->Fill( 1000.*asin( sqrt(px*px+py*py)/sqrt(px*px+py*py+pz*pz) ) );
      }
       
    }
    fOUT.close();

    TCanvas* canv = new TCanvas("canv","canv",900,300);
    canv->Divide(3);
    canv->cd(1);
    gPad->SetLogy();
    h_Tp->Draw();
    canv->cd(2);
    gPad->SetLogy();
    h_Xp->Draw();
    canv->cd(3);
    gPad->SetLogy();
    h_Ap->Draw();

    canv->Print("Proton50_v2.png");
    //gSystem->Exit(0);
    //G4ThreeVector world_pos ;  world_pos.set(0,0, 0                                );
}