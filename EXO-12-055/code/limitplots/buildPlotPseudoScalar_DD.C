
double const mtop = 173.34;
double const mb   = 4.18;

bool STOP=false;
double WidthDM(double mMED, double mF){
	double fac = (1- 4*mF*mF/(mMED*mMED));
	double vev = 246.;
	return TMath::Sqrt(fac)*mMED/(8*TMath::Pi());
}
double Width(double mMED, double mF){
	double fac = (1- 4*mF*mF/(mMED*mMED));
	double vev = 246.;
	return TMath::Sqrt(fac)*mF*mF*mMED/(8*TMath::Pi()*vev*vev);
}

double vecF(double mMED,double mDM){

	if (! mMED>0) return 10;
	if (2*mDM > 0.99*mMED) {

		mMED = 2*mDM; //return 10;
		STOP=true;
	}
	double iGamma = 1;
	if (mMED < 2.*mtop) iGamma = 3*Width(mMED,mb) + WidthDM(mMED,mDM) ;
	else iGamma = 3*Width(mMED,mb) + 3*Width(mMED,mtop) + WidthDM(mMED,mDM) ;

        double  lVal    = 0.5*1./TMath::Pi()*3;
        double  lDenom  = (mMED*mMED-4.*mDM*mDM)*(mMED*mMED-4.*mDM*mDM);
	lDenom += mMED*mMED*iGamma*iGamma;
	lVal /= lDenom;
 	lVal *= mMED *mMED;
 	//lVal *= iCoupl*iCoupl;
 	lVal *= TMath::Sqrt(1.-(4.2*4.2)/mDM/mDM);
 	 //Adding Yukawa Copulings
 	lVal *= (4.2/246.)*(4.2/246.);
 	lVal *= (mDM/246.)*(mDM/246.);
	
	double c = 1.167E-17;
//	std::cout <<  iGamma << " but if MMED = 125, mDM = 1, " << WidthDM(125,1)++3*Width(125,mb) << " " ;
 	return c*lVal;
}

void majoranatodirac(TGraph* gr){
	double X;
	double Y;
	double fac = 2;
	for (int p=0;p<gr->GetN();p++){
		gr->GetPoint(p,X,Y);	
		gr->SetPoint(p,X,fac*Y);
	}
}

TGraph * makeOBV(TGraph *Graph1){

	STOP=false;
	TGraph *gr = new TGraph();
	double X;
	double Y;
	int pp=0;
	Graph1->GetPoint(0,X,Y);
	for (double MDM=0.1;MDM<=Y;MDM+=0.1){

		gr->SetPoint(pp,MDM,vecF(X,MDM));
		pp++;
	}
	for (int p =0;p<Graph1->GetN();p++){
		Graph1->GetPoint(p,X,Y);
		if (!(X >0)) continue;
		
		std::cout << " mMED = " << X << " mDM =  " << Y << std::endl;
		std::cout << " width/x-sec = "<< vecF(X,Y) << std::endl;
		if (STOP) continue;
		gr->SetPoint(pp,Y,vecF(X,Y));	
		pp++;
	}
	gr->GetXaxis()->SetTitle("m_{DM}");
	gr->GetYaxis()->SetTitle("#sigma_{SD}");
	gr->SetName(Form("%s_DD",Graph1->GetName()));
	gr->SetLineStyle(Graph1->GetLineStyle());
	gr->SetLineColor(Graph1->GetLineColor());
	gr->SetLineWidth(Graph1->GetLineWidth());

	return gr;	
}

void buildPlotPseudoScalar_DD(){

	TH2F *dummyHist = new TH2F("dum","",1,6,400,1,1E-30,20E-26);
	dummyHist->GetYaxis()->SetTitle("Annihilation Cross Section (cm^{3}/s)");
	dummyHist->GetXaxis()->SetTitle("m_{DM} (GeV)");
	dummyHist->GetYaxis()->SetTitleOffset(1.5);
	dummyHist->GetYaxis()->SetTitleSize(0.046);
	dummyHist->GetXaxis()->SetTitleSize(0.046);
	dummyHist->GetYaxis()->SetTitleOffset(1.5);
	dummyHist->GetXaxis()->SetTitleOffset(1.25);
	dummyHist->GetYaxis()->SetTitleSize(0.045);
	dummyHist->GetXaxis()->SetTitleSize(0.045);
	dummyHist->GetYaxis()->SetLabelSize(0.04);
	dummyHist->GetXaxis()->SetLabelSize(0.04);

	gROOT->ProcessLine(".x paperStyle.C"); 
	gStyle->SetOptStat(0);
	gStyle->SetPalette(51);


	TFile *fiFL = TFile::Open("FermiLat.root");
	TGraph *DDA = (TGraph*)fiFL->Get("FermiLAT8Y");
	DDA->SetLineColor(kGreen+2);
	DDA->SetLineWidth(3);
	
	TFile *fi = TFile::Open("MassLimit_1_806_0_Both.root");

	TCanvas *can = new TCanvas();
	dummyHist->Draw("AXIS");
	
	TGraph *combinedD 	= makeOBV(combined_obs); combinedD->SetLineColor(1); combinedD->SetName("EXP");
	TGraph *combined_obsD 	= makeOBV(combined); combined_obsD->SetLineColor(1);combined_obsD->SetName("OBS");
	TGraph *monojetD 	= makeOBV(monojet); monojetD->SetLineColor(kBlue); monojetD->SetName("mjet");
	TGraph *monovD 		= makeOBV(monov); monovD->SetLineColor(kRed); monovD->SetName("MV");
	TGraph *fermionD 	= makeOBV(fermionic); fermionD->SetLineColor(kOrange); fermionD->SetName("FER");

	/* other lines */
	combinedD->Draw("csame"); 
	combined_obsD->Draw("csame"); 
	monojetD->Draw("csame"); 
	monovD->Draw("csame"); 
	fermionD->Draw("csame"); 
	DDA->Draw("lsame");

	
	double X;
	double Y;

	gROOT->ProcessLine(".L bounds.C");
	//draw(fermilat0(),kGreen,0.48,0.65,"Fermilat best fit",true);  
	TGraph *grFT = (TGraph*)fermilat0(); //tautau
	grFT->SetFillColor(kMagenta);
	grFT->SetLineColor(kMagenta);
	TGraph *grFT1 = (TGraph*)fermilat1(); //qq
	grFT1->SetFillColor(kGreen+3);
	grFT1->SetLineColor(kGreen+3);
	TGraph *grFT2 = (TGraph*)fermilat3(); //bb
	grFT2->SetFillColor(kRed+2);
	grFT2->SetLineColor(kRed+2);
	grFT->Draw("sameFC");
	grFT1->Draw("sameFC");
	grFT2->Draw("sameFC");
	
	majoranatodirac(grFT);
	majoranatodirac(grFT1);
	majoranatodirac(grFT2);

	TLegend *leg = new TLegend(0.59,0.18,0.89,0.47,NULL,"brNDC");
	leg->SetFillStyle(0);
	leg->AddEntry(combinedD,"Median Expected","L");
	leg->AddEntry(combined_obsD,"Observed","L");
	leg->AddEntry(monojetD,"Monojet","L");
	leg->AddEntry(monovD,"V-tagged","L");
	leg->AddEntry(fermionD,"Fermion Only","L");
	leg->AddEntry(DDA,"FermiLAT Exclusion","L");
	leg->AddEntry(grFT,"FermiLAT Best Fit (#tau#tau)","F");
	leg->AddEntry(grFT1,"FermiLAT Best Fit (qq)","F");
	leg->AddEntry(grFT2,"FermiLAT Best Fit (bb)","F");
	leg->Draw();
	
   	TLatex *   texCMS = new TLatex(0.20,0.84,"#bf{CMS}");
   	//TLatex *   texCMS = new TLatex(0.20,0.84,"#bf{CMS}#it{Preliminary}");
	TLegend *WHITEBOX = new TLegend(0.20,0.83,0.42,0.89);
	WHITEBOX->SetFillColor(kWhite);
	WHITEBOX->Draw();
	texCMS->SetNDC();
   	texCMS->SetTextFont(42);
   	texCMS->SetLineWidth(2);
   	texCMS->SetTextSize(0.042); texCMS->Draw();
	//tex->SetFillColor(kWhite);
	TLatex * tex = new TLatex();
	tex->SetNDC();
   	tex->SetTextFont(42);
   	tex->SetLineWidth(2);
   	tex->SetTextSize(0.035);
	tex->Draw();
   	tex->DrawLatex(0.69,0.94,"19.7 fb^{-1} (8 TeV)");
   	tex->DrawLatex(0.20,0.8,"g_{DM}=g_{q}=1");
   	tex->DrawLatex(0.20,0.62,"Pseudoscalar");
	
	can->SetRightMargin(0.11);
	can->SetLogx();
	can->SetLogy();
	can->RedrawAxis();	

	can->SaveAs("MassLimit_1_806_0_Both_DD.pdf");	
	
/*
 KEY: TCanvas	A;1	A
  KEY: TGraph	DD_mass;1	DD_mass
  KEY: TGraph	DD;1	DD
  KEY: TGraph	monojet;1	monojet
  KEY: TGraph	resolved;1	resolved
  KEY: TGraph	boosted;1	boosted
  KEY: TGraph	monov;1	monov
  KEY: TGraph	combined;1	combined
  KEY: TGraph	combinedUp;1	combinedUp
  KEY: TGraph	combinedDown;1	combinedDown
  KEY: TGraph	monojet_obs;1	monojet_obs
  KEY: TGraph	resolved_obs;1	resolved_obs
  KEY: TGraph	boosted_obs;1	boosted_obs
  KEY: TGraph	monov_obs;1	monov_obs
  KEY: TGraph	combined_obs;1	combined_obs
  KEY: TGraph2D	2D;1	2D	
*/	

}


