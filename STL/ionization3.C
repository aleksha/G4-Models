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
    int pos[3]; double max_E=0; int csz=3;

    TString canv2_name;

    std::ifstream fOUT("./hyd.data" , std::ios::in);

    TH1F* hE   = new TH1F("hE",";E, MeV; Entries", 1000, 0, 1 );
    TH1F* hM   = new TH1F("hM",";E, keV; Entries", 300 , 0, 3000 );

    TH2F* hXY = new TH2F("hXY","H_{2} layer;x, mm;y, mm",160,-400,400,160,-400,400);
    TH3F* hCh = new TH3F("hCh","Chamber",160,-400,400,160,-400,400,10,10,60);

    TBox* box = new TBox(0,0,1,1);
    box->SetLineColor(1); box->SetLineWidth(2);
    box->SetFillStyle(0);
    TCanvas* canv2 = new TCanvas("canv2","canv2",800,800);

    while( fOUT >> ev >> dE >> code >> x >> y >> z ){
        if(ev>EVENT){
            hE->Fill(totE);
            if(totE>0.4){
                layer1++;
                // Dump codes
                double EE=0;
                for(int ii=1;ii<161;ii++){
                    for(int jj=1;jj<161;jj++){
                        for(int kk=1;kk<11;kk++){
                            if(EE<hCh->GetBinContent(ii,jj,kk)){
                                EE = hCh->GetBinContent(ii,jj,kk);
                                pos[0]=ii; pos[1]=jj; pos[2]=kk;
                }}}}
                for(int ii=pos[0]-csz;ii<pos[0]+csz+1;ii++){
                    for(int jj=pos[1]-csz;jj<pos[1]+csz+1;jj++){
                        for(int kk=pos[2]-csz;kk<pos[2]+csz+1;kk++){
                            max_E = max_E + hCh->GetBinContent(ii,jj,kk);
                }}}

                // Print event canvas
                if(max_E>200){

                    for(int ii=0;ii<idx;ii++){
                        if( idxs[ii] ==   13 ) Engs[0] = Engs[0] + engs[ii]*1000.;
                        if( idxs[ii] ==   11 ) Engs[1] = Engs[1] + engs[ii]*1000.;
                        if( idxs[ii] ==  -11 ) Engs[2] = Engs[2] + engs[ii]*1000.;
                        if( idxs[ii] == 2212 ) Engs[3] = Engs[3] + engs[ii]*1000.;
                        if( idxs[ii] == 211 || idxs[ii] == -211 ) Engs[4] = Engs[4] + engs[ii]*1000.;
                        //if(EVENT==21143) cout << "\t" << idxs[ii] << " \t" << engs[ii] << endl;
                    };
                    cout << "\n\n Len " << idx << endl;
                    cout << " Max "     << max_E << endl;
                    cout << "\t Muons     : " << Engs[0] << " keV" << endl;
                    cout << "\t Electrons : " << Engs[1] << " keV" << endl;
                    cout << "\t Positrons : " << Engs[2] << " keV" << endl;
                    cout << "\t Protons   : " << Engs[3] << " keV" << endl;
                    cout << "\t Pions     : " << Engs[4] << " keV" << endl;
                    cout << "\t ---------------------------------" << endl;
                    cout << "\t Total     : " << 1000.*totE << " keV\n" << endl;

                    hM->Fill(max_E);
                    hXY->Draw("colz");
                    box->SetX1(-400+(pos[0]-csz)*5); box->SetY1(-400+(pos[1]-csz)*5);
                    box->SetX2(-400+(pos[0]+csz)*5); box->SetY2(-400+(pos[1]+csz)*5);
                    box->Draw("same");
                    canv2_name.Form("%d.png",ev-1);
                    canv2->Update(); canv2->Print(canv2_name);
                }
            }
            // Reset the state
            for(int ii=0;ii<1000;ii++){idxs[ii]=0;engs[ii]=0;};
            for(int ii=0;ii<5   ;ii++) Engs[ii]=0;
            idx=0;
            hCh->Reset(); hXY->Reset();
            pos[0]=0; pos[1]=0; pos[2]=0; max_E=0;
            totE = 0.;
            EVENT=ev;
        }

        if( sqrt(x*x)<400 && sqrt(y*y)<400 ){
            hCh->Fill(x,y,z,1000.*dE);
            hXY->Fill(x,y,1000.*dE);
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

    hM->Draw();
    canv->Update();
    canv->Print("TEMP.png");
    gSystem->Exit(0);

}
