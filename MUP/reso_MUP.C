TVector3 Vertex(TVector3 a, TVector3 ea, TVector3 c, TVector3 ec){

    TVector3 v_res, v_vvv;
    TVector3 b = (ea - a).Unit();
    TVector3 d = (ec - c).Unit();

    TVector3 u = (b.Cross(d)).Unit() ;
    double g = (a-c).Dot(u);
    // g = (a.x()-c.x())*u.x() + (a.y()-c.y())*u.y() + (a.z()-c.z())*u.z();

    double t,s;
    t = ( b.z()*(g*u.x()+a.x()-c.x()) - b.x()*(g*u.z()+a.z()-c.z()) ) / ( d.x()*b.z() - d.z()*b.x() );
    s = ( c.x()+d.x()*t - g*u.x()- a.x() ) / b.x();
    v_vtx = a + b*s + g*u;
    v_vvv = c + d*t ;


   double best_z = -5000.;
   double min_d  = 1000;
   double dst;
   TVector3 pnt;
   for(double ss=3000.; ss<9000.; ss=ss+1){
      pnt = a + b*ss;
      dst = ( (c-pnt)-((c-pnt).Dot(d))*d ).Mag();
      if(dst<min_d){
         best_z = pnt.Z();
         v_vtx=pnt;
         min_d=dst;
      }
   }
    return v_vtx;
}

void reso_MUP(){

    int ev, vol, tr, st, code, c;
    double dE, E, xi, yi, zi, ti, xf, yf, zf, tf;
    int n_steps;
    double xc;

    std::ifstream fOUT("./out.data" , std::ios::in);

    TH1F* hANG  = new TH1F("hANG" ,";Angle, #murad;Events",40, 0, 200);
    TH1F* hSEC  = new TH1F("hSEC" ,";Angle, mrad;Events",40, 0, 200);
    TH1F* hFAKE = new TH1F("hFAKE",";Angle, #murad;Events",230, 0, 230);
    TH1F* hALL  = new TH1F("hALL",";Angle, #murad;Events",230, 0, 2300);

    TH1F* hPART  = new TH1F("hPART" ,";Momentum, MeV/c;Events", 100, 0, 1000);
    TH1F* hLEPTO = new TH1F("hLEPTO",";Momentum, MeV/c;Events", 100, 0, 1000);
    TH1F* hGAMMA = new TH1F("hGAMMA",";Momentum, MeV/c;Events", 100, 0, 1000);

    TH1F* hZfake  = new TH1F("hZfake" ,";Z, mm;Events", 200, -1000, 1000);
    TH1F* hZtrue  = new TH1F("hZtrue" ,";Z, mm;Events", 20, -1000, 1000);


    hGAMMA->SetLineColor(1);
    hGAMMA->SetFillColor(1);
    hGAMMA->SetFillStyle(3005);


    TCanvas* canv = new TCanvas("canv","canv",600,600);
    //TH2F* hSDV = new TH2F("hSDV",";#Delta x, mm; StdDev, mm", 50, 0, 50, 50, 0, 25);
    hANG->SetMarkerStyle(20);

    TVector3 vec_beam; vec_beam.SetXYZ(0,0,1.);
    TVector3 vec_part;
    TVector3 vec_ini, vec_out;
    TVector3 ww0, ww1, ww2, ww3;
    double xx[4], sx[4];
    double yy[4], sy[4];
    bool fired[4] = {false, false, false, false};
    bool secnd[4] = {false, false, false, false};

    double ideal = 0.;
    double real  = 0.;
    double Ev    = 0.;

    int vrtx=0;
    int cntr=0.;
    int rate[5]=0.;
    int mult[7] = {0,0,0,0,0,0,0};
    double m1[1000],m2[1000];
    double mv1,sdv1,m2,sdv2,df,sdf;
    double vrtx_z_true = 0;

    int nSec  = 0;
    int nThr  = 0;
    int EVENT = 0;
    while( fOUT >> ev >> tr >> st >> vol >> dE >> code >> c >> E >> xi >> yi >> zi >> ti >> xf >> yf >> zf >> tf ){
      if(ev>EVENT){

          if( fired[0] && fired[1] && fired[2] && fired[3] ){
              vec_ini.SetXYZ( xx[1]-xx[0] , yy[1]-yy[0], 5000.);
              vec_out.SetXYZ( xx[3]-xx[2] , yy[3]-yy[2], 5000.);
              hANG->Fill( 1000.*1000.*vec_out.Angle(vec_ini)  );
              hALL->Fill( 1000.*1000.*vec_out.Angle(vec_ini)  );
              if( 1000.*1000.*vec_out.Angle(vec_ini)<2000.){
                  if(1000.*1000.*vec_out.Angle(vec_ini)>100.) rate[0]++;
                  if(1000.*1000.*vec_out.Angle(vec_ini)>200.) rate[1]++;
                  if(1000.*1000.*vec_out.Angle(vec_ini)>300.) rate[2]++;
                  if(1000.*1000.*vec_out.Angle(vec_ini)>330.) rate[3]++;
                  if(1000.*1000.*vec_out.Angle(vec_ini)>400.) rate[4]++;

                  if(1000.*1000.*vec_out.Angle(vec_ini)>330.){
                      ww0.SetXYZ( xx[0]+gRandom->Gaus( 0, 0.016 ), yy[0]+gRandom->Gaus( 0, 0.016 ), -6250.);
                      ww1.SetXYZ( xx[1]+gRandom->Gaus( 0, 0.016 ), yy[1]+gRandom->Gaus( 0, 0.016 ), -1250.);
                      ww2.SetXYZ( xx[2]+gRandom->Gaus( 0, 0.016 ), yy[2]+gRandom->Gaus( 0, 0.016 ),  1250.);
                      ww3.SetXYZ( xx[3]+gRandom->Gaus( 0, 0.016 ), yy[3]+gRandom->Gaus( 0, 0.016 ),  6250.);
                      vrtx_z_true = Vertex(ww0,ww1,ww2,ww3).z() ;
                      if( vrtx_z_true>-1000 && vrtx_z_true<1000 )
                          hZtrue->Fill( vrtx_z_true );
                  }

              }
          }
          if( secnd[2] && secnd[3] ){
              if( (sx[2]*sx[2]+sy[2]*sy[2])<900 && (sx[3]*sx[3]+sy[3]*sy[3])<900){
                    vec_ini.SetXYZ(           0 ,           0, 5000.);
                    vec_out.SetXYZ( sx[3]-sx[2] , sy[3]-sy[2], 5000.);
                    hSEC->Fill( 1000.*vec_out.Angle(vec_ini)  );
                    nSec++;
              }
          }
          if( fired[0] && fired[1] && fired[2] && fired[3] && (secnd[2] || secnd[3] ) ){
              nThr++;
              vec_ini.SetXYZ( xx[1]-xx[0] , yy[1]-yy[0], 5000.);
              if( secnd[2] )
                  vec_out.SetXYZ( xx[3]-sx[2] , yy[3]-sy[2], 5000.);
              else
                  vec_out.SetXYZ( sx[3]-xx[2] , sy[3]-yy[2], 5000.);
              hFAKE->Fill( 1000.*1000.*vec_out.Angle(vec_ini)  );
              hALL->Fill( 1000.*1000.*vec_out.Angle(vec_ini)  );
             // if( 1000.*1000.*vec_out.Angle(vec_ini)<2000.){
             //     if(1000.*1000.*vec_out.Angle(vec_ini)>100.) rate[0]++;
              //    if(1000.*1000.*vec_out.Angle(vec_ini)>200.) rate[1]++;
              //    if(1000.*1000.*vec_out.Angle(vec_ini)>300.) rate[2]++;
              //    if(1000.*1000.*vec_out.Angle(vec_ini)>330.) rate[3]++;
              //    if(1000.*1000.*vec_out.Angle(vec_ini)>400.) rate[4]++;
             // }
          }

          if( fired[0] && fired[1] &&  secnd[2] && fired[3] && false){
              ww0.SetXYZ( xx[0]+gRandom->Gaus( 0, 0.016 ), yy[0]+gRandom->Gaus( 0, 0.016 ), -6250.);
              ww1.SetXYZ( xx[1]+gRandom->Gaus( 0, 0.016 ), yy[1]+gRandom->Gaus( 0, 0.016 ), -1250.);
              ww2.SetXYZ( sx[2]+gRandom->Gaus( 0, 0.016 ), sy[2]+gRandom->Gaus( 0, 0.016 ),  1250.);
              ww3.SetXYZ( xx[3]+gRandom->Gaus( 0, 0.016 ), yy[3]+gRandom->Gaus( 0, 0.016 ),  6250.);
              hZfake->Fill( Vertex(ww0,ww1,ww2,ww3).z() );
              vrtx++;
          }

          if( fired[0] && fired[1] &&  secnd[3] && fired[2] && false){
              ww0.SetXYZ( xx[0]+gRandom->Gaus( 0, 0.016 ), yy[0]+gRandom->Gaus( 0, 0.016 ), -6250.);
              ww1.SetXYZ( xx[1]+gRandom->Gaus( 0, 0.016 ), yy[1]+gRandom->Gaus( 0, 0.016 ), -1250.);
              ww2.SetXYZ( xx[2]+gRandom->Gaus( 0, 0.016 ), yy[2]+gRandom->Gaus( 0, 0.016 ),  1250.);
              ww3.SetXYZ( sx[3]+gRandom->Gaus( 0, 0.016 ), sy[3]+gRandom->Gaus( 0, 0.016 ),  6250.);
              hZfake->Fill( Vertex(ww0,ww1,ww2,ww3).z() );
              vrtx++;
          }

          //if( !(vrtx%100) ) cout << " vrtx " << vrtx << endl;

          for(int ii=0;ii<4;ii++){ fired[ii] = false; secnd[ii] = false; }
          EVENT = ev;
      }

      if(tr == 1){
          xx[vol] = xi;
          yy[vol] = yi;
          fired[vol] = true;
      }
      else{
          hPART->Fill( sqrt(xf*xf+yf*yf+zf*zf) );
          vec_part.SetXYZ( xf, yf, zf );
//          if(E>0.010 && (xi*xi + yi*yi)<900 && vec_part.Angle(vec_beam)<0.002 ){
          if( (xi*xi + yi*yi)<900 && vol==3 ){
              if(code == 11 || code==-11) hLEPTO->Fill( sqrt(xf*xf+yf*yf+zf*zf) );
              if(code == 22 ) hGAMMA->Fill( sqrt(xf*xf+yf*yf+zf*zf) );
              //cout << "  -> "<< code << endl;
          }
          if(E>0.010 && (xi*xi + yi*yi)<900){
              sx[vol] = xi;
              sy[vol] = yi;
              secnd[vol] = true;
          }
      }

    }
    fOUT.close();
    hZtrue->Draw();
    canv->Print("Ztrue.png");
    hZfake->Draw();
    canv->Print("Zfake.png");
    hANG->Draw();
    canv->Print("TEMP.png");
    hSEC->Draw();
    canv->Print("SECN.png");
    gPad->SetLogy();
    hFAKE->Draw();
    canv->Print("FAKE.png");
    hLEPTO->Draw();
    hGAMMA->Draw("same");
    canv->Print("PART.png");
    hALL->Draw();
    canv->Print("ALL.png");
    cout << "Num.sec = " << nSec << endl;
    cout << "Three hits = " << nThr << endl;
    for(int uu=0;uu<5;uu++)
        cout << "   --> " << rate[uu] << endl;
    gSystem->Exit(0);

}
