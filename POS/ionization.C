{
    gStyle->SetOptStat(0);
    int ev, vol;
    double dE,x,y,z,t;

    double sc1_dE=0;
    double sc2_dE=0;
    double hyd_dE=0;

    int EVENT=0;


    std::ifstream fOUT("./out.data" , std::ios::in);

    TH1F* hE_sc1 = new TH1F("hE_sc1","Scintillators;E, MeV; Entries", 500, 0, 5 );
    TH1F* hE_sc2 = new TH1F("hE_sc2","Scintillators;E, MeV; Entries", 500, 0, 5 );
    TH1F* hE_hyd = new TH1F("hE_hyd","Hydrogen;E, MeV; Entries", 500, 0, 5 );

    hE_sc2->SetLineColor(2);

    while( fOUT >> ev >> vol >> dE >> x >> y >> z >> t ){
        if(ev>EVENT){
            hE_sc1->Fill(sc1_dE);
            hE_sc2->Fill(sc2_dE);
            hE_hyd->Fill(hyd_dE);
            // Reset the state
            sc1_dE = 0.;
            sc2_dE = 0.;
            hyd_dE = 0.;
            EVENT=ev;
        }

        if(vol==1) sc1_dE = sc1_dE + dE;
        if(vol==6) sc2_dE = sc2_dE + dE;
        if(vol==3) hyd_dE = hyd_dE + dE;
    }
    fOUT.close();

    TCanvas* canv = new TCanvas("canv","canv",900,450);
    gPad->SetLogy();
    gStyle->SetOptStat(0);
    canv->Divide(2);
    canv->cd(1);
    gPad->SetLogy();
    hE_sc1->Draw();
    hE_sc2->Draw("same");
    canv->cd(2);
    gPad->SetLogy();
    hE_hyd->Draw();
    canv->Update();
    canv->Print("TEMP.png");
    gSystem->Exit(0);

}
