mv CSCActionInitialization.cc   STLActionInitialization.cc  ; sed -i 's/CSC/STL/g' STLActionInitialization.cc  ;
mv CSCDetectorConstruction.cc   STLDetectorConstruction.cc  ; sed -i 's/CSC/STL/g' STLDetectorConstruction.cc  ;
mv CSCEventAction.cc            STLEventAction.cc           ; sed -i 's/CSC/STL/g' STLEventAction.cc           ;
mv CSCPrimaryGeneratorAction.cc STLPrimaryGeneratorAction.cc; sed -i 's/CSC/STL/g' STLPrimaryGeneratorAction.cc;
mv CSCRunAction.cc              STLRunAction.cc             ; sed -i 's/CSC/STL/g' STLRunAction.cc             ;
mv CSCSteppingAction.cc         STLSteppingAction.cc        ; sed -i 's/CSC/STL/g' STLSteppingAction.cc        ;
