TVector3 Vertex(TVector3 a, TVector3 ea, TVector3 c, TVector3 ec){

    TVector3 v_res, l1, l2;
    TVector3 b = (ea - a);
    TVector3 d = (ec - c);

    TVector3 u = (b.Cross(d)).Unit() ;
    TVector3 g = (a-c).Dot(u);

    double t,s;
    t = ( b.y()*(g*u.x()+a.x()-c.x()) - b.x()*(g*u.y()+a.y()-c.y()) ) / ( d.x()*b.y() - d.y()*b.x() );
    s = ( c.x()+d.x()*t - g*u.x()- a.x() ) / b.x();

    l1 = a+b*s; l2 = c+d*t;
    v_vtx = (l1+l2)/2.;
    return v_vtx;
}

void vertex_MUP(){

    int ev, vol, tr, st, code, c;
    double dE, E, xi, yi, zi, ti, xf, yf, zf, tf;
    int n_steps;
    double xc;

    std::ifstream fOUT("./out.data" , std::ios::in);

    TH1F* hVTX  = new TH1F("hVTX" ,"; z, mm;Events",100, 0, 100);

    TCanvas* canv = new TCanvas("canv","canv",600,600);
    //TH2F* hSDV = new TH2F("hSDV",";#Delta x, mm; StdDev, mm", 50, 0, 50, 50, 0, 25);
    hANG->SetMarkerStyle(20);

    TVector3 vec_ini, vec_out, v_vtx;
    TVector3 vv0,vv1,vv2,vv3;
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
      if(ev>EVENT){

          if( fired[0] && fired[1] && fired[2] && fired[3] ){
              vv0.SetXYZ( xx[0] , yy[0], -5450.);
              vv1.SetXYZ( xx[1] , yy[1], - 450.);
              vv2.SetXYZ( xx[2] , yy[2],   450.);
              vv3.SetXYZ( xx[3] , yy[3],  5450.);
              v_vtx = Vertex( vv0, vv1, vv2, vv3);

              hVTX>Fill( v_vtx.z() );
          }

          for(int ii=0;ii<4;ii++){ fired[ii] = false; secnd[ii] = false; }
          EVENT = ev;
      }

      if(tr == 1){
          xx[vol] = xi;
          yy[vol] = yi;
          fired[vol] = true;
      }
      else{
          if(E>0.010 && (xi*xi + yi*yi)<900){
              sx[vol] = xi;
              sy[vol] = yi;
              secnd[vol] = true;
          }
      }

    }
    fOUT.close();
    hVTX->Draw();
    canv->Print("VRTX.png");
    gSystem->Exit(0);

}
