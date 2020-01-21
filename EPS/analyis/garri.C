
// Gatti formula from 
// E. Matheison, J.S. Gordon, Nucl. Inst. Meth. 227 (1984) 277-282 
double Gatti(double lambda, double K3 = 0.45){
    double sK3 = TMath::Sqrt(K3) ;
    double K2 = 0.5*TMath::Pi()*( 1.-0.5*sK3);
    double K1 = 0.25*K2*sK3*TMath::ATan(sK3);
    double tKl = TMath::Power( TMath::TanH(K2*lambda) ,2 );
    double Gamma = K1*(1.-tKl)/(1.+K3*tKl);

    return Gamma;
}


void garri(){
    double xx[601], yd[601], yp[601], ym[601];
    for(int ii=0;ii<601;ii++){
        xx[ii] = 0.01*ii-3.;
        yd[ii] = Gatti( xx[ii] , 0.45 ); 
        yp[ii] = Gatti( xx[ii] , 0.50 ); 
        ym[ii] = Gatti( xx[ii] , 0.40 ); 
    }

    gd = new TGraph(601,xx,yd);
    gp = new TGraph(601,xx,yp);
    gm = new TGraph(601,xx,ym);

    gd->SetTitle("");
    gd->GetXaxis()->SetTitle("#lambda");
    gd->GetYaxis()->SetTitle("#Gamma(#lambda)");

    gd->SetLineWidth(3);
    gp->SetLineWidth(3);
    gm->SetLineWidth(3);

    gp->SetLineColor(4);
    gm->SetLineColor(2);

    TCanvas* canv = new TCanvas("canv","canv",600,600);
    gd->Draw("AL");
    gm->Draw("same L");
    gp->Draw("same L");

    canv->Print("Gatti.C");
    gSystem->Exit(0);
}