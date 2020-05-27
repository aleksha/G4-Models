mv STLActionInitialization.hh   POSActionInitialization.hh  ; sed -i 's/STL/POS/g' POSActionInitialization.hh  ;
mv STLDetectorConstruction.hh   POSDetectorConstruction.hh  ; sed -i 's/STL/POS/g' POSDetectorConstruction.hh  ;
mv STLEventAction.hh            POSEventAction.hh           ; sed -i 's/STL/POS/g' POSEventAction.hh           ;
mv STLPrimaryGeneratorAction.hh POSPrimaryGeneratorAction.hh; sed -i 's/STL/POS/g' POSPrimaryGeneratorAction.hh;
mv STLRunAction.hh              POSRunAction.hh             ; sed -i 's/STL/POS/g' POSRunAction.hh             ;
mv STLSteppingAction.hh         POSSteppingAction.hh        ; sed -i 's/STL/POS/g' POSSteppingAction.hh        ;
