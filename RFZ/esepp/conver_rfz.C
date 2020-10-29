{
  std::ofstream myESEPP;
  myESEPP.open( "esepp.data"   , std::ios::trunc );

  TNtuple * ntp = (TNtuple*)_file0->Get("ntp;1");
  ntp->Print();

  Float_t th,ph,E,Trec;
  Float_t thE,phE,EE;

  ntp->SetBranchAddress("theta_p",&th);
  ntp->SetBranchAddress("phi_p",&ph);
  ntp->SetBranchAddress("E_p",&E);

  ntp->SetBranchAddress("theta_l",&thE);
  ntp->SetBranchAddress("phi_l",&phE);
  ntp->SetBranchAddress("E_l",&EE);

  for(int ev=0;ev<ntp->GetEntries();ev++){
//  for(int ev=0;ev<50;ev++){
    ntp->GetEntry(ev);
    Trec = E-938.272088;
//    if(Trec>4.88+0.05 && Trec<5.08-0.05){
    if(Trec>4.88 && Trec<5.08){
//    if(Trec>5.88 && Trec<6.08){
//    if(Trec>6.88 && Trec<7.08){
//    if(Trec>7.88 && Trec<8.08){
//    if(Trec>8.88 && Trec<9.08){
//    if(Trec>9.88 && Trec<10.08){
//    if(Trec>9.4 && Trec<9.6){
//    if(Trec>8.4 && Trec<8.6){
//    if(Trec>7.4 && Trec<7.6){
//    if(Trec>6.4 && Trec<6.6){
//    if(Trec>5.4 && Trec<5.6){
      myESEPP << th  << " " << ph  << " " << Trec << " "  ;
      myESEPP << thE << " " << phE << " " << EE   << "\n" ;
    }
  }
  myESEPP.close();
}
