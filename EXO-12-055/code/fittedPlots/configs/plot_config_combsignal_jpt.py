import ROOT as r
directory = "category_monojet"
signals = {	 
           # "signal_ggH": ["ggH",r.kAzure+10	,0] 
           #,"signal_vbf": ["VBF",r.kRed		,0] 
           #,"signal_wh":  ["WH",r.kMagenta+1	,0] 
           #,"signal_zh":  ["ZH",r.kOrange	,0] 
 	   "#splitline{Vector Mediator}{m_{med}=1 TeV, m_{DM}=10 GeV}":[
	   	[#"mono-x-vtagged.root:category_$CAT/signal_ggH"
		#,"mono-x-vtagged.root:category_$CAT/signal_vbf"
               "Signals_D11.root:jetpt"  
		] ,r.kRed+1,0,19700]
	   }

key_order = ["Z(#rightarrow ll)+jets","QCD","Dibosons","top","W(#rightarrow l#nu)+jets","Z(#rightarrow #nu#nu)+jets"]

backgrounds = { 
		"top":			  [["signal_top$VAR"],		r.kOrange,   0]
		,"Dibosons":		  [["signal_dibosons$VAR"],	r.kGray,    0]
		,"Z(#rightarrow ll)+jets":[["signal_zll$VAR"],		r.kGreen+3, 0]
		,"W(#rightarrow l#nu)+jets":  [["signal_wjets$VAR"], 	r.kAzure-3, 0]
		,"Z(#rightarrow #nu#nu)+jets":  [["signal_zjets$VAR"],	r.kBlue-9,   0]
		,"QCD":	  		  [["signal_qcd$VAR"],		r.kMagenta+2,   0]

	      }

dataname  = "signal_data$VAR"
