mv STLActionInitialization.cc   ZMSActionInitialization.cc  ; sed -i 's/STL/ZMS/g' ZMSActionInitialization.cc  ;
mv STLDetectorConstruction.cc   ZMSDetectorConstruction.cc  ; sed -i 's/STL/ZMS/g' ZMSDetectorConstruction.cc  ;
mv STLEventAction.cc            ZMSEventAction.cc           ; sed -i 's/STL/ZMS/g' ZMSEventAction.cc           ;
mv STLPrimaryGeneratorAction.cc ZMSPrimaryGeneratorAction.cc; sed -i 's/STL/ZMS/g' ZMSPrimaryGeneratorAction.cc;
mv STLRunAction.cc              ZMSRunAction.cc             ; sed -i 's/STL/ZMS/g' ZMSRunAction.cc             ;
mv STLSteppingAction.cc         ZMSSteppingAction.cc        ; sed -i 's/STL/ZMS/g' ZMSSteppingAction.cc        ;
