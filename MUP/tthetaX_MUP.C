TVector3 Vertex(TVector3 a, TVector3 ea, TVector3 c, TVector3 ec){

    TVector3 v_res, v_vvv;
    TVector3 b = (ea - a).Unit();
    TVector3 d = (ec - c).Unit();

    TVector3 u = (b.Cross(d)).Unit() ;
    double g = (a-c).Dot(u);

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
//l2 = c+d*t;                                                                                            
//    v_vtx = l1+g*u/2.;                                                                                 
    return v_vtx;                                                                                        
}                                                                                                        
void tthetaX_MUP(){

    TVector3 vtx;
    double vtx_z;
    double reso_si = 0.016;

    int ev, vol, tr, st, code, c;
    double dE, E, xi, yi, zi, ti, xf, yf, zf, tf;
    int n_steps;
    double xc;

    std::ifstream fOUT("./out.data" , std::ios::in);

    TH1F* hZx     = new TH1F("hZx"    ,";z, mm;Events", 40, -1000,1000);
    TH1F* hZs     = new TH1F("hZs"    ,";z, mm;Events", 40, -1000,1000);
    TH1F* hTHETAx = new TH1F("hTHETAx",";#theta, mrad;Events", 125, 0, 2.5);
    TH1F* hTHETAs = new TH1F("hTHETAs",";#theta, mrad;Events", 125, 0, 2.5);
    TH1F* hX      = new TH1F("Parameters" ,"10^{6} of 100 GeV/c muons;x, #mum;Events", 400, -200, 200);
    TH1F* hXs     = new TH1F("hXs"        ,"10^{6} of 100 GeV/c muons;x, #mum;Events", 400, -200, 200);

    TCanvas* canv = new TCanvas("canv","canv",600,600);
    //TH2F* hSDV = new TH2F("hSDV",";#Delta x, mm; StdDev, mm", 50, 0, 50, 50, 0, 25);
    //hTHETAx->SetMarkerStyle(20);

    TVector3 vec_ini, vec_out;
    int    nh[4];
    double xx[4][5];
    double yy[4][5];
    double zz[4][5];
    int    cd[4][5];
    bool fired[4] = {false, false, false, false};

    double ideal = 0.;
    double real  = 0.;
    double Ev    = 0.;

    TVector3 v_in[25], v_out[25];
    TVector3 vv[4][25] ;
    bool     t_in[25], t_out[25];
    int      n_in   , n_out   ;
    double Angle;

    int cntr=0.;
    int mult[7] = {0,0,0,0,0,0,0};
    double m1[1000],m2[1000];
    double mv1,sdv1,m2,sdv2,df,sdf;

    int nTOT=0;
    int nADD=0;
    int EVENT = 0;
    int high_multp = 0;
    while( fOUT >> ev >> tr >> st >> vol >> dE >> code >> c >> E >> xi >> yi >> zi >> ti >> xf >> yf >> zf >> tf ){
      if(ev>EVENT){

          // for X distribution
          if( fired[2] ){
            for(int hh=0;hh<nh[2];hh++){
              hX->Fill( 1000.*xx[2][hh]  );
              if( cd[2][hh]!=13 )
                hXs->Fill( 1000.*xx[2][hh] );
            }
          }

          // for theta distribution
          if( fired[0] && fired[1] && fired[2] && fired[3] ){
            n_in = 0;
            for(int hh0=0;hh0<nh[0];hh0++){
              for(int hh1=0;hh1<nh[1];hh1++){
//                vv[0][n_in].SetXYZ( xx[0][hh0], yy[0][hh0], zz[0][hh0]);
//                vv[1][n_in].SetXYZ( xx[1][hh1], yy[1][hh1], zz[1][hh1]);
                vv[0][n_in].SetXYZ( xx[0][hh0]+gRandom->Gaus(0,reso_si), yy[0][hh0]+ gRandom->Gaus(0,reso_si), zz[0][hh0]);
                vv[1][n_in].SetXYZ( xx[1][hh1]+gRandom->Gaus(0,reso_si), yy[1][hh1]+ gRandom->Gaus(0,reso_si), zz[1][hh1]);
                v_in[n_in].SetX( xx[1][hh1] - xx[0][hh0] );
                v_in[n_in].SetY( yy[1][hh1] - yy[0][hh0] );
                v_in[n_in].SetZ( zz[1][hh1] - zz[0][hh0] );
                if( cd[0][hh0]!=13 || cd[1][hh1]!=13 ){t_in[n_in]=false;} else {t_in[n_in]=true;}
                n_in++;
            }}
            n_out=0;
            for(int hh2=0;hh2<nh[2];hh2++){
              for(int hh3=0;hh3<nh[3];hh3++){
//                vv[2][n_out].SetXYZ( xx[2][hh2], yy[2][hh2], zz[2][hh2] );
//                vv[3][n_out].SetXYZ( xx[3][hh3], yy[3][hh3], zz[3][hh3] );
                vv[2][n_out].SetXYZ( xx[2][hh2] + gRandom->Gaus(0,reso_si), yy[2][hh2]+ gRandom->Gaus(0,reso_si), zz[2][hh2] );
                vv[3][n_out].SetXYZ( xx[3][hh3] + gRandom->Gaus(0,reso_si), yy[3][hh3]+ gRandom->Gaus(0,reso_si), zz[3][hh3] );
                v_out[n_out].SetX( xx[3][hh3] - xx[2][hh2] );
                v_out[n_out].SetY( yy[3][hh3] - yy[2][hh2] );
                v_out[n_out].SetZ( zz[3][hh3] - zz[2][hh2] );
                if( cd[2][hh2]!=13 || cd[3][hh3]!=13 ){t_out[n_out]=false;} else {t_out[n_out]=true;}
                n_out++;
            }}
           for(int ii=0;ii<n_in;ii++){
              for(int jj=0;jj<n_out;jj++){
                  Angle =  v_out[jj].Angle( v_in[ii] )*1000. ;
                  if (Angle>0.33 && Angle<0.633 ){
                    nTOT++;
                    vtx_z = Vertex( vv[0][ii], vv[1][ii], vv[2][jj], vv[3][jj] ).Z();
                    if( vtx_z > -1000. && vtx_z<1000 ){
                      if (Angle>0.33 && Angle<0.43 )
                        hZx->Fill( vtx_z );
                      if (Angle>0.43 && Angle<0.63 )
                        hZs->Fill( vtx_z );
                    }
                    cout << nTOT << endl;
                  }
                  hTHETAx->Fill( Angle );
                  if( !t_in[ii] || !t_out[jj] ){
                    if (Angle>0.33 && Angle<2.0 ) nADD++;
                      hTHETAs->Fill( Angle );
                  }
            }}
          }

          for(int ii=0;ii<4;ii++){
            fired[ii] = false;
            nh[ii]    = 0;
          }

          n_in=0; n_out=0;
          EVENT = ev;
      }

//      if(tr == 1){
      if( tr > 0 && dE>0.01){
        if(nh[vol]>4){
            high_multp++;
        }
        else{
          xx[vol][nh[vol]] = xi;
          yy[vol][nh[vol]] = yi;
          zz[vol][nh[vol]] = zi;
          cd[vol][nh[vol]] = code;
          fired[vol] = true;
          nh[vol]++;
        }
      }

    }

    cout << "Number of MUONS  " << EVENT      << endl;
    cout << "  High Multp.    " << high_multp << endl;
    cout << " total         : " << nTOT << endl;
    cout << "   true muons  : " << nTOT-nADD << endl;
    cout << "   additional  : " << nADD << endl;
    fOUT.close();

    hZx->SetLineColor(4);
    hZs->SetLineColor(2);
    hZs->SetFillColor(2);
    hZs->SetFillStyle(3005);
    hZx->Draw();
    hZs->Draw("same");
    canv->Print("POSZ.png");

}
