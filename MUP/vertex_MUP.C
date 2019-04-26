TVector3 MatrixTimesVector3(TVector3 c1, TVector3 c2, TVector3 c3, TVector3 v){

    TVector3 r;

    r.SetX( c1.x()*v.x() + c2.x()*v.y() + c3.x()*v.z() );
    r.SetY( c1.y()*v.x() + c2.y()*v.y() + c3.y()*v.z() );
    r.SetZ( c1.z()*v.x() + c2.z()*v.y() + c3.z()*v.z() );

    return r;
}

TVector3 Det3( TVector3 c1, TVector3 c2, TVector3 c3){

    double r = 0;

    r = r + c1.x()*c2.y()*c3.z();
    r = r + c2.x()*c3.y()*c1.z();
    r = r + c3.x()*c1.y()*c2.z();
    r = r - c3.x()*c2.y()*c1.z();
    r = r - c2.x()*c1.y()*c3.z();
    r = r - c1.x()*c3.y()*c2.z();

    return r;
}

TVector3 InvCol1(TVector3 c1, TVector3 c2, TVector3 c3){

    double det = Det3(c1,c2,c3);
    TVector3 r;

    r.SetX( det*( c2.y()*c3.z()-c3.y()*c2.z() ) );
    r.SetY( det*(-c1.y()*c3.z()+c3.y()*c1.z() ) );
    r.SetZ( det*( c1.y()*c2.z()-c2.y()*c1.z() ) );

    return r;
}


TVector3 InvCol2(TVector3 c1, TVector3 c2, TVector3 c3){

    double det = Det3(c1,c2,c3);
    TVector3 r;

    r.SetX( det*(-c2.x()*c3.z()+c3.x()*c2.z() ) );
    r.SetY( det*( c1.x()*c3.z()-c3.x()*c1.z() ) );
    r.SetZ( det*(-c1.x()*c2.z()+c2.x()*c1.z() ) );

    return r;
}


TVector3 InvCol3(TVector3 c1, TVector3 c2, TVector3 c3){

    double det = Det3(c1,c2,c3);
    TVector3 r;

    r.SetX( det*( c2.x()*c3.y()-c3.x()*c2.y() ) );
    r.SetY( det*(-c1.x()*c3.y()+c3.x()*c1.y() ) );
    r.SetZ( det*( c1.x()*c2.y()-c2.x()*c1.y() ) );

    return r;
}


TVector3 Vertex2(TVector3 a, TVector3 ea, TVector3 c, TVector3 ec){

    TVector3 b = (ea - a).Unit();
    TVector3 d = (ec - c).Unit();

    TVector3 b1; b1.SetXYZ( 1.-b.x()*b.x(),   -b.x()*b.y(),   -b.x()*b.z() );
    TVector3 b2; b2.SetXYZ(   -b.x()*b.y(), 1.-b.y()*b.y(),   -b.y()*b.z() );
    TVector3 b3; b3.SetXYZ(   -b.x()*b.z(),   -b.y()*b.z(), 1.-b.z()*b.z() );

    TVector3 d1; d1.SetXYZ( 1.-d.x()*d.x(),   -d.x()*d.y(),   -d.x()*d.z() );
    TVector3 d2; d2.SetXYZ(   -d.x()*d.y(), 1.-d.y()*d.y(),   -d.y()*d.z() );
    TVector3 d3; d3.SetXYZ(   -d.x()*d.z(),   -d.y()*d.z(), 1.-d.z()*d.z() );

    TVector3 s1 = MatrixTimesVector3(b1,b2,b3,a);
    TVector3 s2 = MatrixTimesVector3(d1,d2,d3,c);
    TVector3 en = s1 + s2 ;

    TVector3 f1 = b1 + d1;
    TVector3 f2 = b2 + d2;
    TVector3 f3 = b3 + d3;

    TVector3 i1 = InvCol1(f1,f2,f3);
    TVector3 i2 = InvCol2(f1,f2,f3);
    TVector3 i3 = InvCol3(f1,f2,f3);


    TVector3 v = MatrixTimesVector3(i1,i2,i3,en);
    return v;
}

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

    cout << "----------> s=" << s << "\tt=" << t << "\t\t g = "<< g << endl;
    cout << "a     : " << a.x() << "\t" << a.y() << "\t" << a.z() << endl;
    cout << "b     : " << b.x() << "\t" << b.y() << "\t" << b.z() << endl;
    cout << "u     : " << u.x() << "\t" << u.y() << "\t" << u.z() << endl;
    cout << "c     : " << c.x() << "\t" << c.y() << "\t" << c.z() << endl;
    cout << "d     : " << d.x() << "\t" << d.y() << "\t" << d.z() << endl;
    cout << "line 1: " << v_vtx.x() << "\t" << v_vtx.y() << "\t" << v_vtx.z() << endl;
    cout << "line 2: " << v_vvv.x() << "\t" << v_vvv.y() << "\t" << v_vvv.z() << endl;
//l2 = c+d*t;
//    v_vtx = l1+g*u/2.;
    return v_vtx;
}

void vertex_MUP(){

    int ev, vol, tr, st, code, c;
    double dE, E, xi, yi, zi, ti, xf, yf, zf, tf;
    int n_steps;
    double xc;

    std::ifstream fOUT("./out.data" , std::ios::in);

    TH1F* hVTX  = new TH1F("hVTX" ,"; z, mm;Events", 600, -300, 300);

    TCanvas* canv = new TCanvas("canv","canv",600,600);
    TH2F* hL = new TH2F("hL",";t;s", 1000, 0, 10000, 1000, 0, 10000);

    TVector3 vec_ini, vec_out, v_vtx;
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
      if(ev>EVENT && ev<5000000){

          if( fired[0] && fired[1] && fired[2] && fired[3] ){
              vv0.SetXYZ( xx[0] , yy[0], -5450.);
              vv1.SetXYZ( xx[1] , yy[1], - 450.);
              vv2.SetXYZ( xx[2] , yy[2],   450.);
              vv3.SetXYZ( xx[3] , yy[3],  5450.);
              v_vtx = Vertex2( vv0, vv1, vv2, vv3);

              hVTX->Fill( v_vtx.z() );
          }

          for(int ii=0;ii<4;ii++){ fired[ii] = false; secnd[ii] = false; }
          EVENT = ev;
          if( !(ev%100) ) cout << ev << endl;
      }

      if(tr < 3){
          xx[vol] = xi;
          yy[vol] = yi;
          fired[vol] = true;
      }

    }
    fOUT.close();
    hVTX->Draw();
    canv->Print("VRTX.png");
//    gPad->SetLogz();
//    hL->Draw("colz");
//    canv->Print("VRTX.png");
    gSystem->Exit(0);

}
