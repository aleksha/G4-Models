{
   gROOT->cd(); //make sure that the Tree is memory resident

   TTree *gen = new TTree("gen","gen");
   Float_t angle,energy,zpos;
   gen->Branch("angle"  ,&angle ,"angle/F" );
   gen->Branch("energy" ,&energy,"energy/F");
   gen->Branch("zpos"   ,&zpos  ,"zpos/F"  );

   std::ifstream fGEN("./gen.data" , std::ios::in);
   while (fGEN >> angle >> energy >> zpos ) {
      gen->Fill();
   }

   TFile *tfile = new TFile("gen.root","RECREATE");
   gen->Write();
   tfile->Write();
   tfile->Close();
   gSystem->Exit(0);
}
