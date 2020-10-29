{
  std::ofstream myESEPP;
  myESEPP.open( "esepp.data"   , std::ios::trunc );

  TNtuple * ntp = (TNtuple*)_file0->Get("ntp;1");
  ntp->Print();

  Float_t th,ph,E,Trec;

  ntp->SetBranchAddress("theta_p",&th);
  ntp->SetBranchAddress("phi_p",&ph);
  ntp->SetBranchAddress("E_p",&E);

  for(int ev=0;ev<ntp->GetEntries();ev++){
//  for(int ev=0;ev<50;ev++){
    ntp->GetEntry(ev);
    Trec = E-938.272088;
    if(Trec>4.88 && Trec<5.08) myESEPP << th << " " << ph << " " << Trec << "\n";
  }
  myESEPP.close();
}
