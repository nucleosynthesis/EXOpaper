import ROOT

ROOT.gStyle.SetOptStat(0)
ROOT.gROOT.SetBatch(1)

def getNormalizedHist(hist, templatehist):
  nb = hist.GetNbinsX()
  thret = templatehist.Clone()
  for b in range(1,nb+1): 
    sfactor = 1./templatehist.GetBinWidth(b)
    thret.SetBinContent(b,hist.GetBinContent(b)*sfactor)
    thret.SetBinError(b,hist.GetBinError(b)*sfactor)
  thret.GetYaxis().SetTitle("Events/GeV")
  return thret


procs = ["ggH", "wh"]
sys = ["hpt","Met"]
lab = ["p_{T} Shape","E_{T}^{miss} recoil modelling"]
plab = ["ggH#rightarrow inv (m_{H} = 125 GeV)","WH#rightarrow inv (m_{H} = 125 GeV)"]
cats = ["monojet","boosted","resolved"]
#cats = ["boosted","resolved"]
for c in cats:

  fi = ROOT.TFile.Open("card_%s.root"%c)
  keys = fi.GetListOfKeys()
  for j,p in enumerate(procs):
    for i,sy in enumerate(sys):

  	cycle = 1
  	if sy=="hpt" and p!="ggH" : continue
	if p=="ggH" :cycle=2 
	else :cycle=1
	scycle = cycle
	if sy=="hpt": scycle = 1
	
	print c, p, sy, cycle
	for k in keys: 
	  if k.GetName()=="signal_%s"%p and k.GetCycle()==cycle: 
	  	hn=k.ReadObj()
		break
	for k in keys: 
	  if k.GetName()=="signalSYS_%s_%sUp"%(p,sy)and k.GetCycle()==scycle: 
	  	hu=k.ReadObj()
		break
	for k in keys: 
	  if k.GetName()=="signalSYS_%s_%sDown"%(p,sy)and k.GetCycle()==scycle: 
	  	hd=k.ReadObj()
		break

	hn = getNormalizedHist(hn,hn)
	hu = getNormalizedHist(hu,hu)
	hd = getNormalizedHist(hd,hd)
	hu.SetLineColor(2);
	hd.SetLineColor(2);
	hu.SetLineWidth(2);
	hd.SetLineWidth(2);

	hn.SetLineColor(1)
	hn.SetLineWidth(2)
	hn.SetTitle("")
	hn.GetXaxis().SetTitle("E_{T}^{miss} (GeV)");
	hn.GetYaxis().SetTitle("Events/GeV");

 	can = ROOT.TCanvas("c_%s"%(c+p+sy),"c_%s"%(c+p+sy),800,800)
 	leg = ROOT.TLegend(0.52,0.7,0.89,0.89); leg.SetFillColor(0); leg.SetTextFont(42)
 	leg.SetBorderSize(0)
 	leg.AddEntry(hn,plab[j],"L")
 	leg.AddEntry(hu,"%s Up/Down"%lab[i],"L")

 	pad1 = ROOT.TPad("p1","p1",0,0.28,1,1)
 	#pad1.SetBottomMargin(0.01)
 	pad1.SetCanvas(can)
 	pad1.Draw()
 	pad1.cd()

	hn.Draw("hist")
	hu.Draw("histsame")
	hd.Draw("histsame")
	leg.Draw()

 	can.cd()
	pad2 = ROOT.TPad("p2","p2",0,0.068,1,0.28)
 	#pad2.SetTopMargin(0.02)
 	pad2.SetCanvas(can)
 	pad2.Draw()
 	pad2.cd()


 	ratio = hn.Clone()
 	ratiou = hu.Clone()
	ratiod = hd.Clone()
	ratiou.Divide(hn)
	ratiod.Divide(hn)

	ratio.GetYaxis().SetTitle("Ratio to nominal");
	for b in range(ratio.GetNbinsX()): ratio.SetBinContent(b+1,1);
 	ratio.GetYaxis().SetNdivisions(5)
 	ratio.GetYaxis().SetLabelSize(0.1)
 	ratio.GetYaxis().SetTitleSize(0.12)
 	ratio.GetYaxis().SetTitleOffset(0.3)
 	ratio.GetXaxis().SetTitleOffset(3.5)
 	ratio.GetXaxis().SetTitleSize(0.085)
 	ratio.GetXaxis().SetLabelSize(0.12)
	ratio.SetMaximum(1.299)
	ratio.SetMinimum(0.701)
	ratio.Draw("hist")
	ratiou.Draw("samehist")
	ratiod.Draw("samehist")
   	#raw_input()

	can.SaveAs("proc_%s_cat_%s_sys_%s.pdf"%(p,c,sy))
 
