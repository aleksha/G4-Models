{
    int ev, vol, tr, code ;
    double dE;

    std::ifstream fOUT("./out.data" , std::ios::in);

    TH1F* h_1 = new TH1F("h_1",";#DeltaE, MeV; Entries", 150, 0, 300 );
    TH1F* h_2 = new TH1F("h_2",";#DeltaE, MeV; Entries", 150, 0, 300 );
    TH1F* h_3 = new TH1F("h_3",";#DeltaE, MeV; Entries", 150, 0, 300 );

    h_1->SetLineWidth(2); h_1->SetLineColor(1); // h_1->SetFillColor(1); h_1->SetFillStyle(3004);
    h_2->SetLineWidth(2); h_2->SetLineColor(2); h_2->SetFillColor(2); h_2->SetFillStyle(3004);
    h_3->SetLineWidth(2); h_3->SetLineColor(4); h_3->SetFillColor(4); h_3->SetFillStyle(3005);


    double e1,e2,e3;
    bool cond;
    int EVENT=0;

    while( fOUT >> ev >> tr >> vol >> dE >> code ){

      if( ev>EVENT ) {
          if(e1>0) h_1->Fill(e1);
          if(e2>0) h_2->Fill(e2);
          if(e3>0) h_3->Fill(e3);
          e1=0.; e2=0.; e3=0.;
          EVENT=ev;
      }

      cond = tr>1;

      if(vol ==  7 && cond ) e1 = e1+dE*1000.;
      if(vol ==  9 && cond ) e2 = e2+dE*1000.;
      if(vol == 11 && cond ) e3 = e3+dE*1000.;
    }

    fOUT.close();
    TCanvas* canv = new TCanvas("canv","canv",600,600);
//    gPad->SetLogy();
    gStyle->SetOptStat(0);

    h_1->Draw();
    h_2->Draw("same");
    h_3->Draw("same");

    cout << "Layer 1 :  " << h_1->GetMean() << " +- " << h_1->GetMeanError() << "\n";
    cout << "Layer 2 :  " << h_2->GetMean() << " +- " << h_2->GetMeanError() << "\n";
    cout << "Layer 3 :  " << h_3->GetMean() << " +- " << h_3->GetMeanError() << "\n";

}
