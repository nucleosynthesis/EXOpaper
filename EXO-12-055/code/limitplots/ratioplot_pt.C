{
//=========Macro generated from canvas: c1/c1
//=========  (Sat Sep 26 15:16:35 2015) by ROOT version5.34/18
// 
   gROOT->ProcessLine(".x paperStyle.C"); 
   gStyle->SetOptStat(0);
   TCanvas *c1 = new TCanvas();
   c1->SetHighLightColor(2);
   c1->Range(99.99999,0.0,1100,0.1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   Double_t xAxis1[10] = {200, 225, 250, 275, 300, 350, 400, 450, 500, 1000}; 
   c1->SetBottomMargin(0.2);//0.02);
   
   TH1F *zmm_data__1 = new TH1F("zmm_data__1","",9, xAxis1);
   zmm_data__1->SetBinContent(0,0.0397712);
   zmm_data__1->SetBinContent(1,0.03038293);
   zmm_data__1->SetBinContent(2,0.03409961);
   zmm_data__1->SetBinContent(3,0.03724847);
   zmm_data__1->SetBinContent(4,0.0381051);
   zmm_data__1->SetBinContent(5,0.04057143);
   zmm_data__1->SetBinContent(6,0.04218534);
   zmm_data__1->SetBinContent(7,0.0393362);
   zmm_data__1->SetBinContent(8,0.04382228);
   zmm_data__1->SetBinContent(9,0.0450771);
   zmm_data__1->SetBinError(0,0.001109934);
   zmm_data__1->SetBinError(1,0.0009498921);
   zmm_data__1->SetBinError(2,0.001080193);
   zmm_data__1->SetBinError(3,0.001339668);
   zmm_data__1->SetBinError(4,0.001646976);
   zmm_data__1->SetBinError(5,0.00170477);
   zmm_data__1->SetBinError(6,0.002571923);
   zmm_data__1->SetBinError(7,0.003609472);
   zmm_data__1->SetBinError(8,0.005330765);
   zmm_data__1->SetBinError(9,0.005343304);
   zmm_data__1->SetEntries(1429.614);
   zmm_data__1->SetDirectory(0);
   zmm_data__1->SetStats(0);
   zmm_data__1->SetLineWidth(3);
   zmm_data__1->SetMarkerStyle(20);
   zmm_data__1->SetMarkerSize(1.2);
   zmm_data__1->GetXaxis()->SetTitle("p_{T}^{#mu#mu/#gamma} (GeV)");
   zmm_data__1->GetXaxis()->SetLabelFont(42);
   zmm_data__1->GetXaxis()->SetLabelSize(0.045);
   zmm_data__1->GetXaxis()->SetTitleSize(0.05);
   zmm_data__1->GetXaxis()->SetTitleOffset(1.22);
   zmm_data__1->GetXaxis()->SetTitleFont(42);
   zmm_data__1->GetYaxis()->SetTitle("Ratio Z( #rightarrow #mu#mu)/#gamma");
   zmm_data__1->GetYaxis()->SetLabelFont(42);
   zmm_data__1->GetYaxis()->SetLabelSize(0.045);
   zmm_data__1->GetYaxis()->SetTitleSize(0.045);
   zmm_data__1->GetYaxis()->SetTitleFont(42);
   zmm_data__1->GetZaxis()->SetLabelFont(42);
   zmm_data__1->GetZaxis()->SetLabelSize(0.035);
   zmm_data__1->GetZaxis()->SetTitleSize(0.035);
   zmm_data__1->GetZaxis()->SetTitleFont(42);
   zmm_data__1->GetYaxis()->SetRangeUser(0.021,0.08);
   zmm_data__1->Draw("pel");
   Double_t xAxis2[10] = {200, 225, 250, 275, 300, 350, 400, 450, 500, 1000}; 
   
   TH1F *zmm_mc__2 = new TH1F("zmm_mc__2","",9, xAxis2);
   zmm_mc__2->SetBinContent(0,0.03271026);
   zmm_mc__2->SetBinContent(1,0.03147259);
   zmm_mc__2->SetBinContent(2,0.03418575);
   zmm_mc__2->SetBinContent(3,0.03531151);
   zmm_mc__2->SetBinContent(4,0.03874044);
   zmm_mc__2->SetBinContent(5,0.03998208);
   zmm_mc__2->SetBinContent(6,0.043356);
   zmm_mc__2->SetBinContent(7,0.04201782);
   zmm_mc__2->SetBinContent(8,0.04505077);
   zmm_mc__2->SetBinContent(9,0.04705767);
   zmm_mc__2->SetBinContent(10,0.7183223);
   zmm_mc__2->SetBinError(0,0.000635359);
   zmm_mc__2->SetBinError(1,0.00273892);
   zmm_mc__2->SetBinError(2,0.003016961);
   zmm_mc__2->SetBinError(3,0.003174314);
   zmm_mc__2->SetBinError(4,0.003587147);
   zmm_mc__2->SetBinError(5,0.003846864);
   zmm_mc__2->SetBinError(6,0.004399754);
   zmm_mc__2->SetBinError(7,0.004506154);
   zmm_mc__2->SetBinError(8,0.005080386);
   zmm_mc__2->SetBinError(9,0.005981716);
   zmm_mc__2->SetBinError(10,0.7870104);
   zmm_mc__2->SetEntries(12898.36);
   zmm_mc__2->SetDirectory(0);
   zmm_mc__2->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#cccccc");
   zmm_mc__2->SetFillColor(ci);

   ci = TColor::GetColor("#000099");
   zmm_mc__2->SetLineColor(ci);
   zmm_mc__2->SetLineWidth(3);
   zmm_mc__2->GetXaxis()->SetTitle("ptll");
   zmm_mc__2->GetXaxis()->SetLabelFont(42);
   zmm_mc__2->GetXaxis()->SetLabelSize(0.035);
   zmm_mc__2->GetXaxis()->SetTitleSize(0.035);
   zmm_mc__2->GetXaxis()->SetTitleFont(42);
   zmm_mc__2->GetYaxis()->SetTitle(" R Z(#rightarrow#mu#mu)/#gamma");
   zmm_mc__2->GetYaxis()->SetLabelFont(42);
   zmm_mc__2->GetYaxis()->SetLabelSize(0.035);
   zmm_mc__2->GetYaxis()->SetTitleSize(0.035);
   zmm_mc__2->GetYaxis()->SetTitleFont(42);
   zmm_mc__2->GetZaxis()->SetLabelFont(42);
   zmm_mc__2->GetZaxis()->SetLabelSize(0.035);
   zmm_mc__2->GetZaxis()->SetTitleSize(0.035);
   zmm_mc__2->GetZaxis()->SetTitleFont(42);
   zmm_mc__2->Draw("sameE2");
   Double_t xAxis3[10] = {200, 225, 250, 275, 300, 350, 400, 450, 500, 1000}; 
   
   TH1F *zmm_mc__3 = new TH1F("zmm_mc__3","",9, xAxis3);
   zmm_mc__3->SetBinContent(0,0.03271026);
   zmm_mc__3->SetBinContent(1,0.03147259);
   zmm_mc__3->SetBinContent(2,0.03418575);
   zmm_mc__3->SetBinContent(3,0.03531151);
   zmm_mc__3->SetBinContent(4,0.03874044);
   zmm_mc__3->SetBinContent(5,0.03998208);
   zmm_mc__3->SetBinContent(6,0.043356);
   zmm_mc__3->SetBinContent(7,0.04201782);
   zmm_mc__3->SetBinContent(8,0.04505077);
   zmm_mc__3->SetBinContent(9,0.04705767);
   zmm_mc__3->SetBinContent(10,0.7183223);
   zmm_mc__3->SetBinError(0,0.000635359);
   zmm_mc__3->SetBinError(1,0.0003244437);
   zmm_mc__3->SetBinError(2,0.0003463139);
   zmm_mc__3->SetBinError(3,0.000429066);
   zmm_mc__3->SetBinError(4,0.0005888199);
   zmm_mc__3->SetBinError(5,0.0005830763);
   zmm_mc__3->SetBinError(6,0.0009181342);
   zmm_mc__3->SetBinError(7,0.001223402);
   zmm_mc__3->SetBinError(8,0.001820686);
   zmm_mc__3->SetBinError(9,0.001772041);
   zmm_mc__3->SetBinError(10,0.7870104);
   zmm_mc__3->SetEntries(12898.36);
   zmm_mc__3->SetDirectory(0);
   zmm_mc__3->SetStats(0);
   zmm_mc__3->SetLineColor(4);
   zmm_mc__3->SetLineWidth(3);
   zmm_mc__3->GetXaxis()->SetTitle("ptll");
   zmm_mc__3->GetXaxis()->SetLabelFont(42);
   zmm_mc__3->GetXaxis()->SetLabelSize(0.035);
   zmm_mc__3->GetXaxis()->SetTitleSize(0.035);
   zmm_mc__3->GetXaxis()->SetTitleFont(42);
   zmm_mc__3->GetYaxis()->SetTitle(" R Z(#rightarrow#mu#mu)/#gamma");
   zmm_mc__3->GetYaxis()->SetLabelFont(42);
   zmm_mc__3->GetYaxis()->SetLabelSize(0.035);
   zmm_mc__3->GetYaxis()->SetTitleSize(0.035);
   zmm_mc__3->GetYaxis()->SetTitleFont(42);
   zmm_mc__3->GetZaxis()->SetLabelFont(42);
   zmm_mc__3->GetZaxis()->SetLabelSize(0.035);
   zmm_mc__3->GetZaxis()->SetTitleSize(0.035);
   zmm_mc__3->GetZaxis()->SetTitleFont(42);
   zmm_mc__3->Draw("samehist");
   Double_t xAxis4[10] = {200, 225, 250, 275, 300, 350, 400, 450, 500, 1000}; 
   
   TH1F *zmm_mc_RAW__4 = new TH1F("zmm_mc_RAW__4","",9, xAxis4);
   zmm_mc_RAW__4->SetBinContent(0,0.03868002);
   zmm_mc_RAW__4->SetBinContent(1,0.03681828);
   zmm_mc_RAW__4->SetBinContent(2,0.03940803);
   zmm_mc_RAW__4->SetBinContent(3,0.04110828);
   zmm_mc_RAW__4->SetBinContent(4,0.04482157);
   zmm_mc_RAW__4->SetBinContent(5,0.04626221);
   zmm_mc_RAW__4->SetBinContent(6,0.05006813);
   zmm_mc_RAW__4->SetBinContent(7,0.04780184);
   zmm_mc_RAW__4->SetBinContent(8,0.05180016);
   zmm_mc_RAW__4->SetBinContent(9,0.05204501);
   zmm_mc_RAW__4->SetBinContent(10,0.7983887);
   zmm_mc_RAW__4->SetBinError(0,0.0007495728);
   zmm_mc_RAW__4->SetBinError(1,0.0003793217);
   zmm_mc_RAW__4->SetBinError(2,0.0003991718);
   zmm_mc_RAW__4->SetBinError(3,0.0004993628);
   zmm_mc_RAW__4->SetBinError(4,0.0006812025);
   zmm_mc_RAW__4->SetBinError(5,0.0006745002);
   zmm_mc_RAW__4->SetBinError(6,0.001059801);
   zmm_mc_RAW__4->SetBinError(7,0.001391668);
   zmm_mc_RAW__4->SetBinError(8,0.002093334);
   zmm_mc_RAW__4->SetBinError(9,0.001939642);
   zmm_mc_RAW__4->SetBinError(10,0.8746792);
   zmm_mc_RAW__4->SetEntries(13270.18);
   zmm_mc_RAW__4->SetDirectory(0);
   zmm_mc_RAW__4->SetStats(0);

   ci = TColor::GetColor("#ffcc00");
   zmm_mc_RAW__4->SetLineColor(ci);
   zmm_mc_RAW__4->SetLineWidth(3);
   zmm_mc_RAW__4->GetXaxis()->SetTitle("ptll");
   zmm_mc_RAW__4->GetXaxis()->SetLabelFont(42);
   zmm_mc_RAW__4->GetXaxis()->SetLabelSize(0.035);
   zmm_mc_RAW__4->GetXaxis()->SetTitleSize(0.035);
   zmm_mc_RAW__4->GetXaxis()->SetTitleFont(42);
   zmm_mc_RAW__4->GetYaxis()->SetTitle(" R Z(#rightarrow#mu#mu)/#gamma");
   zmm_mc_RAW__4->GetYaxis()->SetLabelFont(42);
   zmm_mc_RAW__4->GetYaxis()->SetLabelSize(0.035);
   zmm_mc_RAW__4->GetYaxis()->SetTitleSize(0.035);
   zmm_mc_RAW__4->GetYaxis()->SetTitleFont(42);
   zmm_mc_RAW__4->GetZaxis()->SetLabelFont(42);
   zmm_mc_RAW__4->GetZaxis()->SetLabelSize(0.035);
   zmm_mc_RAW__4->GetZaxis()->SetTitleSize(0.035);
   zmm_mc_RAW__4->GetZaxis()->SetTitleFont(42);
   zmm_mc_RAW__4->Draw("samehist");
   Double_t xAxis5[10] = {200, 225, 250, 275, 300, 350, 400, 450, 500, 1000}; 
   
   TH1F *zmm_data__5 = new TH1F("zmm_data__5","",9, xAxis5);
   zmm_data__5->SetBinContent(0,0.0397712);
   zmm_data__5->SetBinContent(1,0.03038293);
   zmm_data__5->SetBinContent(2,0.03409961);
   zmm_data__5->SetBinContent(3,0.03724847);
   zmm_data__5->SetBinContent(4,0.0381051);
   zmm_data__5->SetBinContent(5,0.04057143);
   zmm_data__5->SetBinContent(6,0.04218534);
   zmm_data__5->SetBinContent(7,0.0393362);
   zmm_data__5->SetBinContent(8,0.04382228);
   zmm_data__5->SetBinContent(9,0.0450771);
   zmm_data__5->SetBinError(0,0.001109934);
   zmm_data__5->SetBinError(1,0.0009498921);
   zmm_data__5->SetBinError(2,0.001080193);
   zmm_data__5->SetBinError(3,0.001339668);
   zmm_data__5->SetBinError(4,0.001646976);
   zmm_data__5->SetBinError(5,0.00170477);
   zmm_data__5->SetBinError(6,0.002571923);
   zmm_data__5->SetBinError(7,0.003609472);
   zmm_data__5->SetBinError(8,0.005330765);
   zmm_data__5->SetBinError(9,0.005343304);
   zmm_data__5->SetEntries(1429.614);
   zmm_data__5->SetDirectory(0);
   zmm_data__5->SetStats(0);
   zmm_data__5->SetLineWidth(3);
   zmm_data__5->SetMarkerStyle(20);
   zmm_data__5->SetMarkerSize(1.2);
   zmm_data__5->GetXaxis()->SetTitle("ptll");
   zmm_data__5->GetXaxis()->SetLabelFont(42);
   zmm_data__5->GetXaxis()->SetLabelSize(0.035);
   zmm_data__5->GetXaxis()->SetTitleSize(0.035);
   zmm_data__5->GetXaxis()->SetTitleFont(42);
   zmm_data__5->GetYaxis()->SetTitle(" R Z(#rightarrow#mu#mu)/#gamma");
   zmm_data__5->GetYaxis()->SetLabelFont(42);
   zmm_data__5->GetYaxis()->SetLabelSize(0.035);
   zmm_data__5->GetYaxis()->SetTitleSize(0.035);
   zmm_data__5->GetYaxis()->SetTitleFont(42);
   zmm_data__5->GetZaxis()->SetLabelFont(42);
   zmm_data__5->GetZaxis()->SetLabelSize(0.035);
   zmm_data__5->GetZaxis()->SetTitleSize(0.035);
   zmm_data__5->GetZaxis()->SetTitleFont(42);
   zmm_data__5->Draw("pelsame");
   
   TLegend *leg = new TLegend(0.46,0.62,0.82,0.89,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("zmm_data","Data #pm (stat + exp syst)","pel");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(3);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1.2);
   entry->SetTextFont(42);
   entry=leg->AddEntry("zmm_mc_RAW","Raw Simulation","L");

   ci = TColor::GetColor("#ffcc00");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(3);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   //entry=leg->AddEntry("zmm_mc","NLO corrected, theory #pm 1#sigma","lf");
   entry=leg->AddEntry("zmm_mc","Corrected Simulation","L");
   entry->SetFillStyle(1001);
   entry->SetLineColor(4);
   entry->SetLineStyle(1);
   entry->SetLineWidth(3);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
   TH1F *f = new TH1F("d","d",1,0,1);
   f->SetFillColor(kGray);
   f->SetLineColor(kGray);
   leg->AddEntry(f,"Theory #pm 1#sigma","f");

   	TLatex *   texCMS = new TLatex(0.2,0.84,"#bf{CMS}");
	texCMS->SetNDC();
   	texCMS->SetTextFont(42);
   	texCMS->SetLineWidth(2);
   	texCMS->SetTextSize(0.042); texCMS->Draw();
   c1->RedrawAxis();	
}
