void editCanvas(TDirectory* dir, std::string category, int crN, std::string crname,double MIN){

  dir->cd();
  TCanvas *can = (TCanvas*)dir->Get(Form("c_ControlRegion_%d",crN));

  ((TH1F*)((TPad*)can->GetListOfPrimitives()->At(0))->GetPrimitive(Form("%s_data_control_region_ControlRegion_%d",category.c_str(),crN)))->GetYaxis()->SetTitleSize(0.05);
  ((TH1F*)((TPad*)can->GetListOfPrimitives()->At(0))->GetPrimitive(Form("%s_data_control_region_ControlRegion_%d",category.c_str(),crN)))->SetMinimum(MIN);
  ((TH1F*)((TPad*)can->GetListOfPrimitives()->At(0))->GetPrimitive(Form("%s_data_control_region_ControlRegion_%d",category.c_str(),crN)))->GetYaxis()->SetTitleOffset(0.8);
  ((TH1F*)((TPad*)can->GetListOfPrimitives()->At(1))->GetPrimitive(Form("%s_data_control_region_ControlRegion_%d",category.c_str(),crN)))->GetYaxis()->SetTitle("Data/Expected");
  ((TH1F*)((TPad*)can->GetListOfPrimitives()->At(1))->GetPrimitive(Form("%s_data_control_region_ControlRegion_%d",category.c_str(),crN)))->GetYaxis()->SetTitleOffset(0.25);
  can->Draw();

  TLatex *tex = new TLatex(0.64,0.026,"fake MET (GeV)");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();

 // can->cd();
  ((TPad*)can->GetListOfPrimitives()->At(0))->cd();

  TPave *wbox = new TPave(); //(0.1,0.91,0.8,0.94);
  //wbox->SetNDC();
  wbox->SetX1NDC(0.1);
  wbox->SetX2NDC(0.8);
  wbox->SetY1NDC(0.91);
  wbox->SetY2NDC(0.96);
  wbox->SetShadowColor(0);
  wbox->SetLineColor(kWhite);
  wbox->SetFillColor(kWhite);
  //wbox->SetOption("NDC");
  wbox->Draw();

  TLatex *titleLat = new TLatex();
//  titleLat->SetFillColor(10);
  titleLat->SetNDC();
  titleLat->SetTextFont(42);
  titleLat->SetTextSize(0.05);
  titleLat->DrawLatex(0.1,0.92,Form("%s category",category.c_str()));
  titleLat->DrawLatex(0.66,0.92,"19.7 fb^{-1} (8TeV)");

  titleLat->SetTextSize(0.06);
  titleLat->DrawLatex(0.18,0.8,"#bf{CMS}");
  can->SaveAs(Form("post_fit_%s_%s.pdf",crname.c_str(),category.c_str()));
}

void remakeThosePlots(){

  gStyle->SetOptStat(0);
  gROOT->SetBatch(1);
  TFile *fi = TFile::Open("../fittedPlots/photon_dimuon_vBin.root");
  editCanvas((TDirectory*)fi->Get("category_monojet"),"monojet",0,"photon",0.2);
  editCanvas((TDirectory*)fi->Get("category_boosted"),"boosted",0,"photon",0.02);
  editCanvas((TDirectory*)fi->Get("category_resolved"),"resolved",0,"photon",0.02);
  editCanvas((TDirectory*)fi->Get("category_monojet"),"monojet",1,"zmm",0.002);
  editCanvas((TDirectory*)fi->Get("category_boosted"),"boosted",1,"zmm",0.002);
  editCanvas((TDirectory*)fi->Get("category_resolved"),"resolved",1,"zmm",0.0002);
  editCanvas((TDirectory*)fi->Get("Wcategory_monojet"),"monojet",0,"wmn",0.02);
  editCanvas((TDirectory*)fi->Get("Wcategory_boosted"),"boosted",0,"wmn",0.02);
  editCanvas((TDirectory*)fi->Get("Wcategory_resolved"),"resolved",0,"wmn",0.002);
}
