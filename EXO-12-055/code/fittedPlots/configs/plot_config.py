import ROOT as r
directory = "shapes_fit_b"
#directory = "shapes_prefit"

signals = {
# 	   "VBF+gg H #rightarrow inv, m_{H}=125 GeV":[
#	   	["mono-x-vtagged.root:category_$CAT/signal_ggH"
#		,"mono-x-vtagged.root:category_$CAT/signal_vbf"
                #,"mono-x-vtagged.root:category_$CAT/signal_wh"
	
               #,"mono-x-vtagged.root:category_$CAT/signal_zh"  
#		] ,r.kOrange	,0],
 #	   "VH #rightarrow inv, m_{H}=125 GeV":[
#	   	[#"mono-x-vtagged.root:category_$CAT/signal_ggH"
		#,"mono-x-vtagged.root:category_$CAT/signal_vbf"
 #               "mono-x-vtagged.root:category_$CAT/signal_wh"
 #              ,"mono-x-vtagged.root:category_$CAT/signal_zh"  
#		] ,r.kGreen+9	,0],
 	   "#splitline{Vector Mediator}{m_{med}=1 TeV, m_{DM}=10 GeV}":[
	   	[#"mono-x-vtagged.root:category_$CAT/signal_ggH"
		#,"mono-x-vtagged.root:category_$CAT/signal_vbf"
                "signal_V_$CAT.root:signal_ggH"
               ,"signal_V_$CAT.root:signal_zh"  
               ,"signal_V_$CAT.root:signal_wh"  
		] ,r.kRed+1,0]
 	   #"#splitline{Scalar Mediator}{m_{MED}=925 GeV, m_{DM}=10 GeV}":[
	   #	["card_$CAT.root:signal_ggH"
	   
	   #] ,r.kAzure+10	,0,1000]
	   }

key_order = ["Z(#rightarrow ll)+jets","QCD","Dibosons","top","W(#rightarrow l#nu)+jets","Z(#rightarrow #nu#nu)+jets"]

backgrounds = { 
		"top":			  	[["$CAT/top"],		r.kOrange,   0]
		,"Dibosons":		  	[["$CAT/dibosons"],	r.kGray,    0]
		,"Z(#rightarrow ll)+jets":	[["$CAT/zll"],		r.kGreen+3, 0]
		,"W(#rightarrow l#nu)+jets":    [["$CAT/wjets"], 	r.kAzure-3, 0]
		,"Z(#rightarrow #nu#nu)+jets":  [["$CAT/zjets"],	r.kBlue-9,   0]
		,"QCD":	  		        [["$CAT/qcd"],		r.kMagenta+2,   0]

	      }

dataname  = "mono-x-vtagged.root:category_$CAT/signal_data"
