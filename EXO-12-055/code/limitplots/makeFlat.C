void makeFlat() {
  int i0  = -1; 
  double *lX = new double[10];
  double *lY = new double[10];
  i0++; lX[i0] = 5.940936682915401;  lY[i0] = 5.327748435480107e-27;
  i0++; lX[i0] = 10.085111886363121; lY[i0] = 5.366193678576881e-27;
  i0++; lX[i0] = 27.14982024633708;  lY[i0] = 9.257381621176723e-27;
  i0++; lX[i0] = 99.02569607590183;  lY[i0] = 2.192661565077832e-26;
  i0++; lX[i0] = 381.97262231787647; lY[i0] = 7.332326097821541e-26;
  i0++; lX[i0] = 888.0077551456894;  lY[i0] = 1.7261067393082356e-25;
  i0++; lX[i0] = 1844.4870040729274; lY[i0] = 4.319193757622729e-25;
  i0++; lX[i0] = 4007.4444161740003; lY[i0] = 1.1512695903823756e-24;
  i0++; lX[i0] = 8229.43461127228;   lY[i0] = 3.3680576212576776e-24;
  for(int iN = 0; iN < i0; iN++) lY[iN] *= 2.;
  TGraph *lG0 = new TGraph(i0,lX,lY);
  lG0->SetTitle("FermiLAT8Y");
  lG0->SetName ("FermiLAT8Y");
  lG0->SetLineColor(kRed);
  lG0->SetLineWidth(2);
  lG0->Draw("alp");
  
  TFile *lFile = new TFile("FermiLat.root","RECREATE");
  lG0->Write();
}

