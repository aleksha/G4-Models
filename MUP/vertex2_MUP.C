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
//    v_vtx = a + b*s + 0.5*g*u ;
//    v_vvv = c + d*t - 0.5*g*u ;
    v_vtx = a + b*s + g*u;
//    v_vtx = a + b*s ;
    v_vvv = c + d*t ;

//    cout << "----------> s=" << s << "\tt=" << t << "\t\t g = "<< g << endl;
//    cout << "a     : " << a.x() << "\t" << a.y() << "\t" << a.z() << endl;
//    cout << "b     : " << b.x() << "\t" << b.y() << "\t" << b.z() << endl;
//    cout << "u     : " << u.x() << "\t" << u.y() << "\t" << u.z() << endl;
//    cout << "c     : " << c.x() << "\t" << c.y() << "\t" << c.z() << endl;
//    cout << "d     : " << d.x() << "\t" << d.y() << "\t" << d.z() << endl;
//    cout << "line 1: " << v_vtx.x() << "\t" << v_vtx.y() << "\t" << v_vtx.z() << endl;
//    cout << "line 2: " << v_vvv.x() << "\t" << v_vvv.y() << "\t" << v_vvv.z() << endl;

   double best_z = -5000.;
   double min_d  = 1000;
   double dst;
   TVector3 pnt;
   for(double ss=5500.; ss<7000.; ss=ss+1){
      pnt = a + b*ss;
      dst = ( (c-pnt)-((c-pnt).Dot(d))*d ).Mag();
      if(dst<min_d){
         best_z = pnt.Z();
         v_vtx=pnt;
         min_d=dst;
      }
   }
//l2 = c+d*t;
//    v_vtx = l1+g*u/2.;
    return v_vtx;
}

void vertex2_MUP(){

    int ev, vol, tr, st, code, c;
    double dE, E, xi, yi, zi, ti, xf, yf, zf, tf;
    int n_steps;
    double xc;

    std::ifstream fOUT("./out.data" , std::ios::in);

    TH1F* hVTX  = new TH1F("hVTX" ,"; z, mm;Events", 200, -100, 300);
    TH1F* hANG  = new TH1F("hANG" ,"; angle, #murad;Events", 200, 0, 600);

    TCanvas* canv = new TCanvas("canv","canv",600,600);
    TH2F* hL = new TH2F("hL",";t;s", 1000, 0, 10000, 1000, 0, 10000);

    TVector3 vINI, vOUT, v_vtx;
    TVector3 vv0,vv1,vv2,vv3,tv;
    double xx[4], sx[4];
    double yy[4], sy[4];
    bool fired[4] = {false, false, false, false};
    bool secnd[4] = {false, false, false, false};

    double ideal = 0.;
    double real  = 0.;
    double Ev    = 0.;

    int cntr=0.;
    int mult[7] = {0,0,0,0,0,0,0};
    double m1[1000],m2[1000];
    double mv1,sdv1,m2,sdv2,df,sdf;

    int nSec  = 0;
    int nThr  = 0;
    int EVENT = 0;
    while( fOUT >> ev >> tr >> st >> vol >> dE >> code >> c >> E >> xi >> yi >> zi >> ti >> xf >> yf >> zf >> tf ){
      if(ev>EVENT && ev<1000){

          if( fired[0] && fired[1] && fired[2] && fired[3] ){
              vv0.SetXYZ( xx[0] , yy[0], -5900.);
              vv1.SetXYZ( xx[1] , yy[1], - 900.);
              vv2.SetXYZ( xx[2] , yy[2],   900.);
              vv3.SetXYZ( xx[3] , yy[3],  5900.);
              vINI.SetXYZ( xx[1]-xx[0] , yy[1]-yy[0], -5000.);
              vOUT.SetXYZ( xx[3]-xx[2] , yy[3]-yy[2], -5000.);
              v_vtx = Vertex( vv0, vv1, vv2, vv3);

              hVTX->Fill( v_vtx.z() );
              hANG->Fill( 1000.*1000.*vOUT.Angle( vINI ) );
          }

          for(int ii=0;ii<4;ii++){ fired[ii] = false; secnd[ii] = false; }
          EVENT = ev;
          if( !(ev%50) ) cout << ev << endl;
      }

      if(tr < 3){
          xx[vol] = xi;
          yy[vol] = yi;
          fired[vol] = true;
      }

    }
    fOUT.close();
    hANG->Draw();
    hANG->Fit("gaus");
    canv->Print("RECO.png");
    hVTX->Draw();
    hVTX->Fit("gaus");
    canv->Print("VRTX.png");
//    gPad->SetLogz();
//    hL->Draw("colz");
//    canv->Print("VRTX.png");
    gSystem->Exit(0);

}
