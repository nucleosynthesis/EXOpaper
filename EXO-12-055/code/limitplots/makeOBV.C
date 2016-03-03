double vecF(double mMED,double mDM){

	if (! mMED>0) return 10;
	//mMED/=1000;
	double mR = (0.939*mDM)/(0.939+mDM);
	//double c = 1.1E-39;
	double c = 0.3984e-27;
	return (c*(9./3.14159)*(mR*mR/(mMED*mMED*mMED*mMED)));


}

void makeOBV(){
	TFile *fi = TFile::Open("vline.root");
	TGraph *Graph1 = (TGraph*)fi->Get("Graph1");
	TGraph *gr = new TGraph();
	double X;
	double Y;
	int pp=0;
	for (int p =0;p<Graph1->GetN();p++){
		Graph1->GetPoint(p,X,Y);
		if (!(X >1)) continue;
		
		std::cout << X << "  " << Y << std::endl;
		gr->SetPoint(pp,Y,vecF(X,Y));	
		pp++;
	}
	gr->GetXaxis()->SetTitle("m_{DM}");
	gr->GetYaxis()->SetTitle("#sigma_{SI}");
	gr->SetLineWidth(2);
	gr->SetMarkerSize(1.0);
	gr->Draw("AL");
}
