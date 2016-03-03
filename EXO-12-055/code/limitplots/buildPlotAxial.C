
void buildPlotAxial(){

	TH2F *dummyHist = new TH2F("dum","",1,50,2200,1,20,1000);
	dummyHist->GetXaxis()->SetTitle("m_{med} (GeV)");
	dummyHist->GetYaxis()->SetTitle("m_{DM} (GeV)");
	dummyHist->GetYaxis()->SetTitleOffset(1.5);
	dummyHist->GetYaxis()->SetTitleSize(0.046);
	dummyHist->GetXaxis()->SetTitleSize(0.046);
	dummyHist->GetYaxis()->SetTitleOffset(1.5);
	dummyHist->GetXaxis()->SetTitleOffset(1.25);
	dummyHist->GetYaxis()->SetTitleSize(0.045);
	dummyHist->GetXaxis()->SetTitleSize(0.045);
	dummyHist->GetYaxis()->SetLabelSize(0.04);
	dummyHist->GetYaxis()->SetNdivisions(505);
	dummyHist->GetXaxis()->SetNdivisions(505);
	dummyHist->GetXaxis()->SetLabelSize(0.04);

	gROOT->ProcessLine(".x paperStyle.C"); 
	gStyle->SetOptStat(0);
	gStyle->SetPalette(51);
   int ncontours = 999;

   double stops[5]   = {0.0 ,  0.25,   0.5  , .75    , 1.0    }; 
   double blue[5]    = {1.0 ,  1.  ,   1.0  , 1.0     , 1.00   };
   double green[5]   = {0.25 , 0.3 ,   0.5  , 0.75    , 1.00   };
   double red [5]    = {0.05,  0.1 ,   0.33 , 0.6     , 1.00   };

   int npoints = 5;
   TColor::CreateGradientColorTable(npoints, stops, red, green, blue, ncontours);
   gStyle->SetNumberContours(ncontours);
	
	TFile *fiDD = TFile::Open("MassLimit_1_801_0_Both_updatePICO.root");
	TGraph *DD_Fmass = (TGraph*)fiDD->Get("DD_mass");
	

	TFile *fi = TFile::Open("MassLimit_1_801_0_Both.root");
	// Blue scale 
	TGraph2D *gr2D = (TGraph2D*)fi->Get("2D");
	TH2D *hblue = (TH2D*)gr2D->GetHistogram();
	hblue->SetMaximum(5); hblue->SetMinimum(0.001);
	hblue->SetTitle("");	

	TCanvas *can = new TCanvas();
	dummyHist->Draw("AXIS");

   	TLatex *   tex2 = new TLatex();
   	tex2->SetNDC();
   	tex2->SetTextFont(42);
   	tex2->SetLineWidth(2);
   	tex2->SetTextSize(0.052);
   	tex2->SetTextAngle(270);
   	tex2->DrawLatex(0.95,0.92,"#mu_{up}");
	
 	hblue->Draw("colzsame");

//	TGraph* combined = (TGraph*)fi->Get("monojet");
	
	/* other lines */
	combinedUp->SetLineStyle(1); 
	combinedDown->SetLineStyle(1);
	combinedUp->SetLineWidth(2); 
	combinedDown->SetLineWidth(2);
	combined->SetLineColor(1);combined->Draw("lsame"); 
	combinedUp->SetLineColor(2); combinedUp->Draw("lsame");
	combinedDown->SetLineColor(2);combinedDown->Draw("lsame");
	combined_obs->SetLineColor(1); combined_obs->Draw("lsame");	
	DD_Fmass->Draw("lsame");
	
	/* WMAP */
	
   	TFile *fi2 = TFile::Open("relicContour_A_g1.root");
	TList *storegraphs = new TList();	
	for (int i=0;i<((TList*)fi2->Get("mytlist"))->GetSize();i++){
   	 TGraph *gr_T = (TGraph*)( ((TList*)fi2->Get("mytlist"))->At(i) ); 
	 gr_T->SetName(Form("relic_graph_%d",i));
   	 gr_T->SetLineColor(kMagenta);
   	 gr_T->SetFillColor(kMagenta);
   	 gr_T->SetLineStyle(1);
   	 gr_T->SetLineWidth(-1002);
   	 gr_T->SetFillStyle(3005);
	// ((TGraph*)( ((TList*)fi2->Get("mytlist"))->At(i) ))->Draw("L");
	storegraphs->Add(gr_T);
	}
	for (int i=0;i<((TList*)fi2->Get("mytlist"))->GetSize();i++){
		(TGraph *)storegraphs->At(i)->Draw("L");
	}
   	TGraph *gr_T = (TGraph*)storegraphs->At(0) ; 
   	

		// Note, Phile swapped observed and expected :), not a bug!!!
	TLegend *leg = new TLegend(0.51,0.68,0.81,0.87,NULL,"brNDC");
	leg->SetFillStyle(0);
	leg->AddEntry(combined_obs,"Median Expected (#mu_{up}=1)","L");
	leg->AddEntry(combinedUp,"+/- Scale Uncertainty","L");
	leg->AddEntry(combined,"Observed","L");
	//leg->AddEntry(DD_Fmass,"PICASSO+COUPP+SIMPLE","L");
	leg->AddEntry(DD_Fmass,"PICO-2L","L");
	leg->AddEntry(gr_T,"Planck+WMAP Relic","F");
	leg->Draw();
	
   	//TLatex *   texCMS = new TLatex(0.25,0.84,"#bf{CMS}#it{Preliminary}");
   	TLatex *   texCMS = new TLatex(0.25,0.84,"#bf{CMS}");
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
   	tex->DrawLatex(0.25,0.8,"g_{DM}=g_{SM}=1");
   	tex->DrawLatex(0.25,0.7,"Axial");
	
//	can->SetLogx();
	can->SetLogz();
	can->RedrawAxis();	

	can->SaveAs("MassLimit_1_801_0_Both.pdf");	
        TFile *rout = new TFile("axial_out.root","RECREATE");
        rout->WriteTObject(combined_obs,"combined_expected");
        rout->WriteTObject(combined);
        rout->WriteTObject(DD_mass);
	for (int i=0;i<((TList*)fi2->Get("mytlist"))->GetSize();i++){
		((TGraph *)storegraphs->At(i))->SetName(Form("wmap_%d",i));
		((TGraph *)storegraphs->At(i))->Write();
	}
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


