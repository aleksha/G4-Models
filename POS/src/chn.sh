mv STLActionInitialization.cc   POSActionInitialization.cc  ; sed -i 's/STL/POS/g' POSActionInitialization.cc  ;
mv STLDetectorConstruction.cc   POSDetectorConstruction.cc  ; sed -i 's/STL/POS/g' POSDetectorConstruction.cc  ;
mv STLEventAction.cc            POSEventAction.cc           ; sed -i 's/STL/POS/g' POSEventAction.cc           ;
mv STLPrimaryGeneratorAction.cc POSPrimaryGeneratorAction.cc; sed -i 's/STL/POS/g' POSPrimaryGeneratorAction.cc;
mv STLRunAction.cc              POSRunAction.cc             ; sed -i 's/STL/POS/g' POSRunAction.cc             ;
mv STLSteppingAction.cc         POSSteppingAction.cc        ; sed -i 's/STL/POS/g' POSSteppingAction.cc        ;
