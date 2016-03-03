
double vecF(double mMED,double mDM){

	if (! mMED>0) return 10;
	mMED/=1000;
	double mR = (0.939*mDM)/(0.939+mDM);
	double c = 4.6E-41;
	return c*mR*mR/(mMED*mMED*mMED*mMED);


}


TGraph * makeOBV(TGraph *Graph1){

	TGraph *gr = new TGraph();
	double X;
	double Y;
	int pp=0;
	Graph1->GetPoint(1,X,Y);
	for (double MDM=1;MDM<=Y;MDM+=0.1){

		gr->SetPoint(pp,MDM,vecF(X,MDM));
		pp++;
	}
	for (int p =1;p<Graph1->GetN();p++){
		Graph1->GetPoint(p,X,Y);
		if (!(X >1)) continue;
		
		std::cout << X << "  " << Y << std::endl;
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

void buildPlotAxial_DD(){

	TH2F *dummyHist = new TH2F("dum","",1,1,900,1,6E-43,1E-37);
	dummyHist->GetYaxis()->SetTitle("#sigma_{SD} (cm^{2})");
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
	
	TFile *fiDD = TFile::Open("MassLimit_1_801_0_Both_updatePICO.root");
	TGraph *DDF = (TGraph*)fiDD->Get("DD");

	TFile *fi = TFile::Open("MassLimit_1_801_0_Both.root");

	TCanvas *can = new TCanvas();
	dummyHist->Draw("AXIS");
	
	TGraph *combinedD 	= makeOBV(combined_obs); combinedD->SetLineColor(1); combinedD->SetName("EXP");
	TGraph *combined_obsD 	= makeOBV(combined); combined_obsD->SetLineColor(1);combined_obsD->SetName("OBS");
	TGraph *monojetD 	= makeOBV(monojet); monojetD->SetLineColor(kBlue); monojetD->SetName("mjet");
	// Phil swapped boosted and resolved
	TGraph *boostedD 	= makeOBV(resolved); boostedD->SetLineColor(kMagenta); boostedD->SetName("bjet");
	TGraph *resolvedD 	= makeOBV(boosted); resolvedD->SetLineColor(kGreen); resolvedD->SetName("rjet");
	TGraph *monovD 		= makeOBV(monov); monovD->SetLineColor(kRed); monovD->SetName("MV");

	/* other lines */
	combinedD->Draw("lsame"); 
	combined_obsD->Draw("lsame"); 
	monojetD->Draw("lsame"); 
	boostedD->Draw("lsame"); 
	resolvedD->Draw("lsame"); 
	monovD->Draw("lsame"); 
	DDF->Draw("lsame");
	

	TLegend *leg = new TLegend(0.19,0.40,0.51,0.63,NULL,"brNDC");
	leg->SetFillStyle(0);
	leg->AddEntry(combinedD,"Median Expected","L");
	leg->AddEntry(combined_obsD,"Observed","L");
	leg->AddEntry(monojetD,"Monojet","L");
	leg->AddEntry(boostedD,"Boosted","L");
	leg->AddEntry(resolvedD,"Resolved","L");
	leg->AddEntry(monovD,"V-tagged","L");
	leg->AddEntry(DDF,"PICO-2L","L");
	leg->Draw();
	
   	TLatex *   texCMS = new TLatex(0.20,0.84,"#bf{CMS}");
	//TLegend *WHITEBOX = new TLegend(0.18,0.83,0.3,0.89);
   	//TLatex *   texCMS = new TLatex(0.20,0.84,"#bf{CMS}#it{Preliminary}");
	TLegend *WHITEBOX = new TLegend(0.18,0.83,0.42,0.89);
	WHITEBOX->SetFillColor(kWhite);
	//WHITEBOX->Draw();
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
   	tex->DrawLatex(0.20,0.8,"g_{DM}=g_{SM}=1");
   	tex->DrawLatex(0.20,0.7,"Axial");
	
	can->SetRightMargin(0.11);
	can->SetLogx();
	can->SetLogy();
	can->RedrawAxis();	

	can->SaveAs("MassLimit_1_801_0_Both_DD.pdf");
	
        TFile *rout = new TFile("axialDD_out.root","RECREATE");
        rout->WriteTObject(combined_obsD,"combined");
        rout->WriteTObject(combinedD,"combined_expected"); 
        rout->WriteTObject(DDF,"DD_mass");
	rout->Close();
	
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


