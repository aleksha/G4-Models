{
   gROOT->cd(); //make sure that the Tree is memory resident

   TTree *gen = new TTree("gen","gen");
   Float_t xPOS,yPOS,zPOS;
   Float_t Tp,THETAp,PHIp;
   Float_t Ee,THETAe,PHIe;

   gen->Branch( "Tp"     , &Tp     ,"Tp/F"     );
   gen->Branch( "THETAp" , &THETAp ,"THETAp/F" );
   gen->Branch( "PHIp"   , &PHIp   ,"PHIp/F"   );
   gen->Branch( "Ee"     , &Ee     ,"Ee/F"     );
   gen->Branch( "THETAe" , &THETAe ,"THETAe/F" );
   gen->Branch( "PHIe"   , &PHIe   ,"PHIe/F"   );
   gen->Branch( "xPOS"   , &xPOS   ,"xPOS/F"   );
   gen->Branch( "yPOS"   , &yPOS   ,"yPOS/F"   );
   gen->Branch( "zPOS"   , &zPOS   ,"zPOS/F"   );

   std::ifstream fGEN("./gen.data" , std::ios::in);
   while (fGEN >> THETAp >> PHIp >> Tp >> THETAe >> PHIe >> Ee >> xPOS >> yPOS >> zPOS ) {
      gen->Fill();
   }

   TFile *tfile = new TFile("gen.root","RECREATE");
   gen->Write();
   tfile->Write();
   tfile->Close();
   gSystem->Exit(0);
}
