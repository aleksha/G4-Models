{
    gStyle->SetOptStat(0);
    int ev, code;
    double dE,x,y,z;
    double totE=0.;

    int    idxs[1000];
    double engs[1000];
    int idx=0;
    double Engs[5];

    int EVENT=0;

    int layer1=0;

    TString canv2_name;

    std::ifstream fOUT("./hyd.data" , std::ios::in);

    TH1F* hE   = new TH1F("hE",";E, MeV; Entries", 1000, 0, 1 );
    TH2F* h_xz = new TH2F("h_xz",";z, mm; x, mm", 100, 0, 100, 100, -50, 50 );
    TH2F* h_yz = new TH2F("h_yz",";z, mm; y, mm", 100, 0, 100, 100, -50, 50 );

    TCanvas* canv2 = new TCanvas("canv2","canv2",800,400);
    canv2->Divide(2);

    while( fOUT >> ev >> dE >> code >> x >> y >> z ){
        if(ev>EVENT){
            hE->Fill(totE);
            if(totE>0.4){
                layer1++;
                // Dump codes
                for(int ii=0;ii<idx;ii++){
                    if( idxs[ii] ==   13 ) Engs[0] = Engs[0] + engs[ii]*1000.;
                    if( idxs[ii] ==   11 ) Engs[1] = Engs[1] + engs[ii]*1000.;
                    if( idxs[ii] ==  -11 ) Engs[2] = Engs[2] + engs[ii]*1000.;
                    if( idxs[ii] == 2212 ) Engs[3] = Engs[3] + engs[ii]*1000.;
                    if( idxs[ii] == 211 || idxs[ii] == -211 ) Engs[4] = Engs[4] + engs[ii]*1000.;
                    //if(EVENT==21143) cout << "\t" << idxs[ii] << " \t" << engs[ii] << endl;
                };
                cout << "\n\n Len " << idx << endl;
                cout << "\t Muons     : " << Engs[0] << " keV" << endl;
                cout << "\t Electrons : " << Engs[1] << " keV" << endl;
                cout << "\t Positrons : " << Engs[2] << " keV" << endl;
                cout << "\t Protons   : " << Engs[3] << " keV" << endl;
                cout << "\t Pions     : " << Engs[4] << " keV" << endl;
                cout << "\t ---------------------------------" << endl;
                cout << "\t Total     : " << 1000.*totE << " keV\n" << endl;
                // Print event canvas
                canv2->cd(1); h_xz->Draw("colz");
                canv2->cd(2); h_yz->Draw("colz");
                canv2_name.Form("%d.png",ev-1);
                canv2->Update(); canv2->Print(canv2_name);
            }
            // Reset the state
            for(int ii=0;ii<1000;ii++){idxs[ii]=0;engs[ii]=0;};
            for(int ii=0;ii<5   ;ii++) Engs[ii]=0;
            idx=0;
            h_xz->Reset(); h_yz->Reset();
            totE = 0.;
            EVENT=ev;
        }

        if( sqrt(x*x+y*y)<100 ){
            h_xz->Fill(z,x,dE*1000.); h_yz->Fill(z,y,dE*1000.);
            totE = totE + dE;
            idxs[idx]=code; engs[idx]=dE; idx++;
        }

    }
    fOUT.close();
    canv2->Close();

    cout << "\n\n Layer 1: " << layer1 << endl;

    TCanvas* canv = new TCanvas("canv","canv",600,600);
    gPad->SetLogy();
    gStyle->SetOptStat(0);

    hE->Draw();
    canv->Update();
    canv->Print("TEMP.png");
    gSystem->Exit(0);

}
