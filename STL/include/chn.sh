mv CSCActionInitialization.hh   STLActionInitialization.hh  ; sed -i 's/CSC/STL/g' STLActionInitialization.hh  ;
mv CSCDetectorConstruction.hh   STLDetectorConstruction.hh  ; sed -i 's/CSC/STL/g' STLDetectorConstruction.hh  ;
mv CSCEventAction.hh            STLEventAction.hh           ; sed -i 's/CSC/STL/g' STLEventAction.hh           ;
mv CSCPrimaryGeneratorAction.hh STLPrimaryGeneratorAction.hh; sed -i 's/CSC/STL/g' STLPrimaryGeneratorAction.hh;
mv CSCRunAction.hh              STLRunAction.hh             ; sed -i 's/CSC/STL/g' STLRunAction.hh             ;
mv CSCSteppingAction.hh         STLSteppingAction.hh        ; sed -i 's/CSC/STL/g' STLSteppingAction.hh        ;
