mv ZMSActionInitialization.cc   RFZActionInitialization.cc  ; sed -i 's/ZMS/RFZ/g' RFZActionInitialization.cc  ;
mv ZMSDetectorConstruction.cc   RFZDetectorConstruction.cc  ; sed -i 's/ZMS/RFZ/g' RFZDetectorConstruction.cc  ;
mv ZMSEventAction.cc            RFZEventAction.cc           ; sed -i 's/ZMS/RFZ/g' RFZEventAction.cc           ;
mv ZMSPrimaryGeneratorAction.cc RFZPrimaryGeneratorAction.cc; sed -i 's/ZMS/RFZ/g' RFZPrimaryGeneratorAction.cc;
mv ZMSRunAction.cc              RFZRunAction.cc             ; sed -i 's/ZMS/RFZ/g' RFZRunAction.cc             ;
mv ZMSSteppingAction.cc         RFZSteppingAction.cc        ; sed -i 's/ZMS/RFZ/g' RFZSteppingAction.cc        ;
