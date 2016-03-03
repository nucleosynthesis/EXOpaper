import sys
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-d","--tdir",default='',help="pick histos from a different directory (will be catgeory of course!)")
parser.add_option("-c","--cat",default='',help="pick up a category name for $CAT")
parser.add_option("","--min",default=0.1,type=float)
parser.add_option("","--max",default=1000,type=float)
parser.add_option("-v","--var",default='DEFAULT',help="pick up a variable name for $VAR")
parser.add_option("-o","--outext",default='',help="Add Extension to output name")
parser.add_option("-x","--xlab",default='',help="Set the Label for X-axis")
parser.add_option("-b","--batch",default=False,action='store_true',help="always run in batch and save .pdf with config name instead of drawing canvas")
parser.add_option("-g","--gendata",default=False,action='store_true',help="Generate Pretend data from the background")
parser.add_option("-p","--pull",default=False,action='store_true',help="replace the ratio plot with a pull (data-background)/(sigma_{data+bkg})")
parser.add_option("","--stacksig",default=False,action='store_true',help="Stack the signal on top")
parser.add_option("","--nolog",default=False,action='store_true',help="Turn of log plot")
parser.add_option("","--nospec",default=False,action='store_true',help="Don't make a spectrum plot")
parser.add_option("","--fit",default="expo",help="Fit the QCD with something to re-distribute")
parser.add_option("","--wasfitted",default=False,action='store_true')
parser.add_option("","--ratzoom",default=False,action='store_true')
parser.add_option("","--shift",default=False,action='store_true')
(options,args) = parser.parse_args()

import ROOT as r 
r.gStyle.SetOptStat(0)

r.gROOT.ProcessLine(".L statsCalc.h+");
from ROOT import calculateExpectedSignificance 
from ROOT import calculateExpectedLimit 

fi = r.TFile.Open(args[0])
di = fi #.Get("mjw_1jet")

def getNormalizedHist(hist, templatehist):
  nb = hist.GetNbinsX()
  thret = templatehist.Clone()
  for b in range(1,nb+1): 
    sfactor = 1./templatehist.GetBinWidth(b)
    if options.nospec: sfactor = 1
    thret.SetBinContent(b,hist.GetBinContent(b)*sfactor)
    thret.SetBinError(b,hist.GetBinError(b)*sfactor)
  thret.GetYaxis().SetTitle("Events/GeV")
  if options.nospec: 
        thret.GetYaxis().SetTitle("Events")
  thret.GetYaxis().SetTitleSize(0.05)
  thret.GetYaxis().SetTitleOffset(0.9)
  thret.GetYaxis().SetLabelSize(0.045)
  return thret

sys.path.append("configs")
configs = args[1:]
canvs = []
if len(configs) > 1:
  print "Moving to batch mode, will save pdfs as name of config"
  options.batch = True

if options.batch:
  r.gROOT.SetBatch(1)

for ic,config in enumerate(configs) :
 print "Run Config", config
 x = __import__(config)
 if options.tdir: x.directory = options.tdir
 procs=[]
 # first run through signals, backgrounds and data to check if we need to replace things
 for sl in x.signals.keys():
  for si,s in enumerate(x.signals[sl][0]):
   snew  =  s.replace("$CAT",options.cat)
   if options.var!="DEFAULT" : snew  =  snew.replace("$VAR",options.var)
   print snew
   snew  =  snew.replace("$DIRECTORY",options.tdir)

   x.signals[sl][0][si] = snew; 
 print x.signals

 for b in x.backgrounds.keys():
  for i in range(len(x.backgrounds[b][0])):
   x.backgrounds[b][0][i]=x.backgrounds[b][0][i].replace("$CAT",options.cat)
   x.backgrounds[b][0][i]=x.backgrounds[b][0][i].replace("$VAR",options.var)
   x.backgrounds[b][0][i]=x.backgrounds[b][0][i].replace("$DIRECTORY",options.tdir)
 x.dataname = x.dataname.replace("$CAT",options.cat)
 x.dataname = x.dataname.replace("$VAR",options.var)
 x.dataname = x.dataname.replace("$DIRECTORY",options.tdir)

 print x.signals

 if x.directory!="":x.directory+="/"
 if ":" in x.dataname: 
   fi,datnam = x.dataname.split(":")
   tfi = r.TFile.Open(fi)
   dataO = tfi.Get(datnam)
 else:
   dataO = di.Get(x.directory+x.dataname)
   print x.directory+x.dataname
 data 	    = getNormalizedHist(dataO,dataO)
 data.SetTitle("")
 origlabel = data.GetXaxis().GetTitle()
 #if options.xlab: data.GetXaxis().SetTitle(options.xlab)
 data.GetXaxis().SetTitle("")
 data.GetXaxis().SetLabelSize(0)
 data.GetYaxis().SetTickLength(0.03)

 can = r.TCanvas("c_%d"%ic,"c_%d"%ic,800,800)
 leg = r.TLegend(0.43,0.41,0.88,0.89); leg.SetFillColor(0); leg.SetTextFont(42)
 leg.SetBorderSize(0)
 leg.AddEntry(data,"Data","PEL")
 legentries = []
 lat = r.TLatex(); lat.SetNDC()
 lat.SetTextFont(42)
 lat.SetTextSize(0.04)
 if options.xlab: label = options.xlab
 else: label = origlabel
 # make 2 pads
 pad1 = r.TPad("p1","p1",0,0.28,1,1)
 pad1.SetBottomMargin(0.01)
 pad1.SetCanvas(can)
 pad1.Draw()
 pad1.cd()


 data.SetMinimum(options.min)
 data.SetMaximum(options.max)
 data.Draw()

 thstack = r.THStack("bkg","backgroundstack")
 thstack.SetTitle("")
 totalbkg = 0; totalc=0
 print "	Nevents ", data.GetName(), data.Integral("width")

 totalbackground = 0
 totalbackground_PF = 0
 for bkgtype_i,bkg in enumerate(x.key_order):
  nullhist = 0; nullc = 0

  for thist in x.backgrounds[bkg][0]:
    if ":" in thist:
     fi,datnam = thist.split(":")
     tfi = r.TFile.Open(fi)
     tmp = tfi.Get(datnam)
     print "trying...",datnam
    elif "Purity=" in thist:
       val = float(thist.split("=")[-1])
       tmp = dataO.Clone()
       tmp.Scale(1-val)
    else: 
       tmp = di.Get(x.directory+thist)
       print "trying...",x.directory+thist, "from",di.GetName()
    tmp.SetLineColor(1)
    if len(x.backgrounds[bkg])>3:  # last one is a scale-factor, from fit?
       tmp.Scale(x.backgrounds[bkg][3])
    if nullc == 0 : 	
        print "Starting ", tmp.GetName(), tmp.Integral("")
    	nullhist = tmp.Clone()
    else:
        #print "  ... Adding ", tmp.GetName(), tmp.Integral("")
    	nullhist.Add(tmp)
    nullc+=1
  if bkgtype_i==0 :
  	totalbackground = nullhist.Clone()
	totalbackground.Sumw2();
  else : totalbackground.Add(nullhist)

  nullhist = getNormalizedHist(nullhist,data)
  if "QCD" in bkg:
	totatl = nullhist.Integral()
	#nullhist.Smooth()
    	tmp2 = nullhist.Clone(); tmp2.SetName("QCD_FITTY")
	#ffunc = r.TF1("func","[0]*TMath::Exp( -1*([1]-x)*([1]-x)/([2]*[2]) )+ (TMath::Exp(-[3]*x))",nullhist.GetXaxis().GetXmin(), nullhist.GetXaxis().GetXmax())
	ffunc = r.TF1("func","[0]*(TMath::Exp(-[1]*x))",nullhist.GetXaxis().GetXmin(), nullhist.GetXaxis().GetXmax())
	#ffunc.SetParameter(1,)
    	tmp2.Fit("func","L")
	for b in range(nullhist.GetNbinsX()):
	 nullhist.SetBinContent(b+1,tmp2.GetFunction("func").Eval(nullhist.GetBinCenter(b+1)))
	 nullhist.SetBinError(b+1,0)
	#cnvtmp = r.TCanvas()
	#tmp2.Draw()
	#raw_input()
	if options.fit == "landau": nullhist.SetBinContent(1,nullhist.GetBinContent(2)*0.9)
	nullhist.Scale(totatl/nullhist.Integral())
  print "	Nevents ", bkg, nullhist.Integral("width")
  procs.append([bkg,nullhist.Integral("width"),nullhist.GetBinError(1)*nullhist.GetBinWidth(1)])
  nullhist.SetLineColor(1)
  nullhist.SetLineWidth(2)
  nullhist.SetFillColor(x.backgrounds[bkg][1])
  nullhist.SetFillStyle(1001)
  if totalc==0: totalbkg=nullhist.Clone()
  else : totalbkg.Add(nullhist)
  totalbkg.Sumw2()
  x.backgrounds[bkg][2]=nullhist.Clone()
  thstack.Add(x.backgrounds[bkg][2])
  legentries.append([x.backgrounds[bkg][2].Clone(),bkg,"F"])

  totalc+=1
 
 legentries.reverse()
 for le in legentries: leg.AddEntry(le[0],le[1],le[2])
 
 allsignal = 0
 for sig_i,sig_t in enumerate(x.signals.keys()):
  totalsignal = 0
  for sig_s_i,sig in enumerate(x.signals[sig_t][0]):
   if ":" in sig:
     fi,datnam = sig.split(":")
     tfi = r.TFile.Open(fi)
     print "Getting signal %s"%tfi.GetName()+datnam
     tmp = tfi.Get(datnam)
   else: 
    print "Getting signal %s"%x.directory+sig
    tmp = di.Get(x.directory+sig)
   if sig_s_i==0: totalsignal = tmp.Clone()
   else: totalsignal.Add(tmp)
  totalsignal = getNormalizedHist(totalsignal,data)

  totalsignal.SetLineColor(x.signals[sig_t][1])
  totalsignal.SetLineStyle(7)
  totalsignal.SetLineWidth(5)
  if len(x.signals[sig_t])>3:  # last one is a scale-factor
       totalsignal.Scale(x.signals[sig_t][3])
  x.signals[sig_t][2]=totalsignal.Clone()
  #x.signals[sig_t][2].Draw("samehist")
  legentries.append(x.signals[sig_t][2].Clone())
  leg.AddEntry(legentries[-1],sig_t,"L")
  print "	Nevents ", sig_t, totalsignal.Integral("width")
   #procs.append([tmp.GetName(),tmp.Integral("width")])
  allsignal = totalsignal

 if options.stacksig and allsignal!=0: 
   allsignal.SetLineColor(1)
   allsignal.SetFillColor(x.signals[x.signals.keys()[0]][1])
   thstack.Add(allsignal)
   thstack.Draw("histFsame")
 else:
   thstack.Draw("histFsame")
   for sig in x.signals.keys(): 
 	x.signals[sig][2].Draw("samehist")

 normtotalback = getNormalizedHist(totalbackground,data)
 print "Total Background " , normtotalback.Integral("width")
 procs.append(["total bkg",normtotalback.Integral("width"),normtotalback.GetBinError(1)*normtotalback.GetBinWidth(1)])
 procs.append([data.GetName(), data.Integral("width"),0])

 # now set totalbackground errors to 0 
 for b in range(normtotalback.GetNbinsX()):
   totalbkg.SetBinError(b+1,0)

 if options.gendata: 
 	for b in range(1, totalbkg.GetNbinsX()+1):
		data.SetBinContent(b,normtotalback.GetBinContent(b))
		data.SetBinError(b,((normtotalback.GetBinContent(b))**0.5)/data.GetBinWidth(b))

 normtotalback.SetFillStyle(3144);
 normtotalback.SetFillColor(1);
 normtotalback.SetMarkerSize(0);
 normtotalback.Draw("E2same");

 data.SetMarkerColor(r.kBlack)
 data.SetLineColor(1)
 data.SetLineWidth(1)
 data.SetMarkerSize(0.9)
 data.SetMarkerStyle(20)
 data.Draw("same")
 leg.Draw()
 if not options.nolog: pad1.SetLogy()
 pad1.RedrawAxis()

 lat2 = r.TLatex()
 lat2.SetNDC()
 lat2.SetTextFont(42)
 lat2.SetTextSize(0.05)
 lat2.DrawLatex(0.17,0.82,"#bf{CMS}") 
 if options.cat : lat.DrawLatex(0.1,0.92,options.cat+" category") 
 lat.DrawLatex(0.72,0.92,"19.7 fb^{-1} (8 TeV)") 

 can.cd()
 pad2 = r.TPad("p2","p2",0,0.068,1,0.28)
 pad2.SetTopMargin(0.02)
 pad2.SetCanvas(can)
 pad2.Draw()
 pad2.cd()

 ratio = data.Clone()
 ratioErr = normtotalback.Clone()
 ratioErr.SetFillStyle(1001);
 ratioErr.SetFillColor(r.kGray);

 if not options.pull:
  if options.ratzoom: ratio.GetYaxis().SetRangeUser(0.81,1.19)
  else: ratio.GetYaxis().SetRangeUser(0.21,1.79)
  ratio.Divide(totalbkg)
  ratio.GetYaxis().SetTitle("Data/Bkg")
  ratioErr.Divide(totalbkg)

 else: 
  ratio.GetYaxis().SetRangeUser(-5,5)
  ratio.GetYaxis().SetTitle("(Data-Bkg)/#sigma")
  ratio.GetYaxis().SetTitleOffset(1.2)
  for b in range(1,ratio.GetNbinsX()+1):
    val = ratio.GetBinContent(b)-totalba
    err = ((ratio.GetBinError(b))**2 + (totalbackground.GetBinError(b))**2)**0.5
    ratio.SetBinContent(b,val/err) 
    ratio.SetBinError(b,1) 

 r.gStyle.SetOptStat(0)
 ratio.GetYaxis().SetNdivisions(5)
 ratio.GetYaxis().SetLabelSize(0.12)
 ratio.GetYaxis().SetTitleSize(0.12)
 ratio.GetXaxis().SetTitleSize(0.085)
 ratio.GetXaxis().SetLabelSize(0.12)

 # draw the sub-plot 
 #if options.xlab: ratio.GetXaxis().SetTitle(options.xlab)
 ratio.GetXaxis().SetTitle("")
 if options.wasfitted: ratio.GetYaxis().SetTitle("Data/Prediction")
 else: ratio.GetYaxis().SetTitle("Data/MC")
 ratio.GetYaxis().SetTitleOffset(0.3)
 ratio.Draw()
 if not options.pull : ratioErr.Draw("sameE2")
 ratio.Draw("same")

 if options.pull: line = r.TLine(data.GetXaxis().GetXmin(),0,data.GetXaxis().GetXmax(),0)
 else  :line = r.TLine(data.GetXaxis().GetXmin(),1,data.GetXaxis().GetXmax(),1)
 line.SetLineColor(2)
 line.SetLineWidth(3)
 line.Draw()
 ratio.Draw("same")
 pad2.RedrawAxis()
 # add Label
 can.cd()
 if options.shift: lat.DrawLatex(0.62,0.02,label)
 else: lat.DrawLatex(0.72,0.02,label)
 #lat.DrawLatex(0.5,0.5,"#bold{CMS} #emph{Preliminary}") 
 canvs.append(can)
#can.SaveAs("metdist.pdf")
 can.Draw()
 if allsignal != 0 : print "	Expected Significance ", calculateExpectedSignificance(totalsignal,totalbackground), " sigma"
 if allsignal != 0 : print "	Expected Limit mu  <  ", calculateExpectedLimit(0.01,0.5,totalsignal,totalbackground)
# if totalsignal.Integral()>0 : print "	Expected Significance (incbkg) ", calculateExpectedSignificance(totalsignal,totalbackground,1), " sigma"
 if options.batch: can.SaveAs("%s_%s%s.pdf"%(config,options.tdir,options.outext))
 if options.batch: can.SaveAs("%s_%s%s.png"%(config,options.tdir,options.outext))
 if options.batch: can.SaveAs("%s_%s%s.C"%(config,options.tdir,options.outext))
 print "expectations"
 for pp in procs:
   print "%30s   %10.1f +/- %.1f"%(pp[0],pp[1],pp[2])
if not options.batch:raw_input("Press enter")
