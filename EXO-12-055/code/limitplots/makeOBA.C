double vecF(double mMED,double mDM){

	if (! mMED>0) return 10;
	mMED/=1000;
	double mR = (0.939*mDM)/(0.939+mDM);
	double c = 4.6E-41;
	return c*mR*mR/(mMED*mMED*mMED*mMED);


}

void makeOBA(){
	TFile *fi = TFile::Open("aline.root");
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
	gr->GetYaxis()->SetTitle("#sigma_{SD}");
	gr->SetLineWidth(2);
	gr->SetMarkerSize(1.0);
	gr->Draw("AL");
}
