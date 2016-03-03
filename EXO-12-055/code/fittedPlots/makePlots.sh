#!/bin/bash
python makePlot.py mlfit.root  plot_config -c monojet -o monojet -b -x "E_{T}^{miss} (GeV)" --wasfitted  --min 0.02 --max 20000 --ratzoom
python makePlot.py mlfit.root  plot_config -c boosted -o boosted -b -x "E_{T}^{miss} (GeV)"  --wasfitted --min 0.02 --max 80
python makePlot.py mlfit.root  plot_config -c resolved -o resolved -b -x "E_{T}^{miss} (GeV)" --wasfitted --min 0.02 --max 80 


python makePlot.py mono-x.root plot_config_combsignal     -d category_monojet  		  -x "E_{T}^{miss} (GeV)"   -b  --min 0.02 --max 20000 # -o label -> Will use the Zmumu+gjet CR result for Zvv template, -g == blind 
python makePlot.py mono-x.root plot_config_combsignal_jpt -d category_monojet  -v jet1pt  -x "Lead Jet p_{T} (GeV)" -b --shift  --min 0.02 --max 20000 # -o label -> Will use the Zmumu+gjet CR result for Zvv template, -g == blind 
#python makePlot.py mono-x.root plot_config_combsignal_jpt -d category_monojet  -v njets  -o NJETS -x "N Jets" -b  --nospec  # -o label -> Will use the Zmumu+gjet CR result for Zvv template, -g == blind 
