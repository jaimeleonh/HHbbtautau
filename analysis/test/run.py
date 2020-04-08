import sys, os
import time
import ROOT as r
from ROOT import gSystem
r.gROOT.SetBatch(True)
from subprocess import call
from samples import samples
from collections import OrderedDict
import plotTools

import argparse
parser = argparse.ArgumentParser(description='Plotter options')
parser.add_argument('-n','--ntuples', action='store_true', default = False)
parser.add_argument('-c','--copy', action='store_true', default = False)
parser.add_argument('-m','--merge', action='store_true', default = False)
parser.add_argument('-p','--plots', action='store_false', default = True)
parser.add_argument('-d','--directory', dest='userCopyPath', default = '')
my_namespace = parser.parse_args()

if my_namespace.ntuples == True :
    print ("Starting ntuplizer for every sample in input")
    time.sleep(2)
    r.gInterpreter.ProcessLine(".x loadExampleAnalysis.C")
    dir_path = os.path.dirname(os.path.realpath(__file__))
    gSystem.Load(dir_path + "analysisCode_C.so")
    from ROOT import analysisCode
else : 
  print("Not making ntuples. If you want to make them, restart with 'yes' as first argument ")
  time.sleep(2)

#path = '/eos/home-j/jleonhol/HHbbtautau/2017/'
path = '/eos/home-c/camendol/SKIMS_Thesis2017/'
#path = '/eos/home-c/camendol/SKIMS_Legacy2018/SKIMS_30Jan2020/'
eosPath = '/eos/home-j/jleonhol/HHbbtautau/'
plotPath = './plots/'


categories = ["baseline","noSelection"]
#categories = ["baseline","noSelection","s1b1jresolvedMcut", "s2b0jresolvedMcut", "VBFtight_DNN", "VBFloose_DNN", "sboostedLLMcut", "VBFloose", "VBFtight"]

if my_namespace.userCopyPath == '' : 
  copyPath = '/eos/home-j/jleonhol/www/HHbbtautau/2017'
else : 
  copyPath = '/eos/home-j/jleonhol/www/HHbbtautau/' + my_namespace.userCopyPath + '/'

if (my_namespace.copy == True) :
  rc = call('mkdir ' + copyPath, shell=True)
  rc = call('cp -r /eos/home-j/jleonhol/backup/index_HHbbtautau_php ' + copyPath +  '/index.php' , shell=True)
  for cat in categories : 
    rc = call('mkdir ' + copyPath +  '/' + cat + '/' , shell=True)
    rc = call('cp -r /eos/home-j/jleonhol/backup/index_HHbbtautau_php ' + copyPath + '/' + cat + '/index.php' , shell=True)



rc = call('mkdir ' + plotPath, shell=True) 
rc = call('mkdir ' + eosPath + '2017/', shell=True)

files = []

if 'allVBF' in copyPath : 
  files.append("GGHSM_xs")
  files.append("VBF_CV_1_C2V_1_C3_1")
  files.append("VBF_CV_1_5_C2V_1_C3_1")
  files.append("VBF_CV_1_C2V_1_C3_0")
  files.append("VBF_CV_1_C2V_1_C3_2")
  files.append("VBF_CV_1_C2V_0_C3_2")
  files.append("VBF_CV_1_C2V_2_C3_1")
else : 
  #files.append("GGHSM_xs")
  #files.append("VBF_CV_1_C2V_1_C3_1")
  #files.append("ttHJetToBB")
  #files.append("PrivateGluGlu12JetsHHTo2B2Taus2017_SKIM")
  files += ["TT_fullyHad", "TT_semiLep", "TT_fullyLep"]

  #files += ["DYJets_0j0b_allgenjets_0b", "DYJets_1j0b_allgenjets_0b", "DYJets_1j1b_allgenjets_0b", "DYJets_2j0b_allgenjets_0b", "DYJets_2j1b_allgenjets_0b", "DYJets_2j2b_allgenjets_0b", "DYJets_3j0b_allgenjets_0b", "DYJets_3j1b_allgenjets_0b", "DYJets_3j2b_allgenjets_0b", "DYJets_3j3b_allgenjets_0b", "DYJets_4j0b_allgenjets_0b", "DYJets_4j1b_allgenjets_0b", "DYJets_4j2b_allgenjets_0b", "DYJets_4j3b_allgenjets_0b", "DYJets_4j4b_allgenjets_0b"]
  #files += ["DYJets_0j0b_allgenjets_1b", "DYJets_1j0b_allgenjets_1b", "DYJets_1j1b_allgenjets_1b", "DYJets_2j0b_allgenjets_1b", "DYJets_2j1b_allgenjets_1b", "DYJets_2j2b_allgenjets_1b", "DYJets_3j0b_allgenjets_1b", "DYJets_3j1b_allgenjets_1b", "DYJets_3j2b_allgenjets_1b", "DYJets_3j3b_allgenjets_1b", "DYJets_4j0b_allgenjets_1b", "DYJets_4j1b_allgenjets_1b", "DYJets_4j2b_allgenjets_1b", "DYJets_4j3b_allgenjets_1b", "DYJets_4j4b_allgenjets_1b"]
  #files += ["DYJets_0j0b_allgenjets_2b", "DYJets_1j0b_allgenjets_2b", "DYJets_1j1b_allgenjets_2b", "DYJets_2j0b_allgenjets_2b", "DYJets_2j1b_allgenjets_2b", "DYJets_2j2b_allgenjets_2b", "DYJets_3j0b_allgenjets_2b", "DYJets_3j1b_allgenjets_2b", "DYJets_3j2b_allgenjets_2b", "DYJets_3j3b_allgenjets_2b", "DYJets_4j0b_allgenjets_2b", "DYJets_4j1b_allgenjets_2b", "DYJets_4j2b_allgenjets_2b", "DYJets_4j3b_allgenjets_2b", "DYJets_4j4b_allgenjets_2b"]

  mergingCategories = OrderedDict()
  mergingCategories["ggHSM"] = ["GGHSM_xs"]
  mergingCategories["VBFSM"] = ["VBF_CV_1_C2V_1_C3_1"]
  mergingCategories["ttHJetToBB"] = ["ttHJetToBB"]
  mergingCategories["ggF+2jets"] = ["PrivateGluGlu12JetsHHTo2B2Taus2017_SKIM"]
  mergingCategories["TT"] = ["TT_fullyHad", "TT_semiLep", "TT_fullyLep"]
  mergingCategories["DY+0b"] = ["DYJets_0j0b_allgenjets_0b", "DYJets_1j0b_allgenjets_0b", "DYJets_1j1b_allgenjets_0b", "DYJets_2j0b_allgenjets_0b", "DYJets_2j1b_allgenjets_0b", "DYJets_2j2b_allgenjets_0b", "DYJets_3j0b_allgenjets_0b", "DYJets_3j1b_allgenjets_0b", "DYJets_3j2b_allgenjets_0b", "DYJets_3j3b_allgenjets_0b", "DYJets_4j0b_allgenjets_0b", "DYJets_4j1b_allgenjets_0b", "DYJets_4j2b_allgenjets_0b", "DYJets_4j3b_allgenjets_0b", "DYJets_4j4b_allgenjets_0b"]
  mergingCategories["DY+1b"] = ["DYJets_0j0b_allgenjets_1b", "DYJets_1j0b_allgenjets_1b", "DYJets_1j1b_allgenjets_1b", "DYJets_2j0b_allgenjets_1b", "DYJets_2j1b_allgenjets_1b", "DYJets_2j2b_allgenjets_1b", "DYJets_3j0b_allgenjets_1b", "DYJets_3j1b_allgenjets_1b", "DYJets_3j2b_allgenjets_1b", "DYJets_3j3b_allgenjets_1b", "DYJets_4j0b_allgenjets_1b", "DYJets_4j1b_allgenjets_1b", "DYJets_4j2b_allgenjets_1b", "DYJets_4j3b_allgenjets_1b", "DYJets_4j4b_allgenjets_1b"]
  mergingCategories["DY+2b"] = ["DYJets_0j0b_allgenjets_2b", "DYJets_1j0b_allgenjets_2b", "DYJets_1j1b_allgenjets_2b", "DYJets_2j0b_allgenjets_2b", "DYJets_2j1b_allgenjets_2b", "DYJets_2j2b_allgenjets_2b", "DYJets_3j0b_allgenjets_2b", "DYJets_3j1b_allgenjets_2b", "DYJets_3j2b_allgenjets_2b", "DYJets_3j3b_allgenjets_2b", "DYJets_4j0b_allgenjets_2b", "DYJets_4j1b_allgenjets_2b", "DYJets_4j2b_allgenjets_2b", "DYJets_4j3b_allgenjets_2b", "DYJets_4j4b_allgenjets_2b"]

if not my_namespace.plots : sys.exit(0)

for fil in files :
  if my_namespace.ntuples == True :
    print ('Obtaining plot ntuples for ' + fil)
    time.sleep(2) 
    if (fil != 'PrivateGluGlu12JetsHHTo2B2Taus2017_SKIM') : analysis = analysisCode(path + 'SKIM_' + fil, eosPath + '2017/' + fil + '.root')
    else : analysis = analysisCode( '/eos/home-j/jleonhol/HHbbtautau/2017/' + fil, eosPath + '2017/' + fil + '.root')
    analysis.Loop()




whatToPlot = []


if 'Chiara' in copyPath : #plots from Chiara's thesis 
  stuff = ['tau1', 'tau2', 'bjet1', 'bjet2', 'additionalJet1','additionalJet2','VBFjet1', 'VBFjet2','additionalVBFjet1']
  variables = ['pt','eta','z']
  for st in stuff :  
    for var in variables : 
      whatToPlot.append(st+'_'+var)

  whatToPlot+=['tau1_iso','tau2_iso','bjets_deltaEta','bjets_eta1eta2']
  whatToPlot+=['VBFjj_deltaEta', 'VBFjj_eta1eta2', 'VBFjj_mass']
  whatToPlot+=['additionalJets_deltaEta', 'additionalJets_eta1eta2', 'additionalJets_mass']
  whatToPlot+=['tauH_mass', 'tauH_pt', 'tauH_z', 'bH_mass', 'bH_pt', 'bH_z']
  whatToPlot+=['HH_mass','HH_pt','HH_z','HH_AHH']

if 'Giles' in copyPath:  #plots from Giles' Github
  whatToPlot+=["dR_hbb_sv","dR_l1_l2_x_sv_pT","dphi_sv_met","dR_l1_l2_boosted_htt_met","dphi_hbb_sv","deta_b1_b2","costheta_l2_htt","dphi_l1_met","costheta_htt_hh_met","dR_hbb_httmet","costheta_b1_hbb","deta_hbb_httmet","costheta_met_htt","boosted","channel"]

  
  
else :  #plots we obtained before looking at Chiara's thesis
  stuff = ['HH','tauH','tauH_SVFIT','bH','HHsvfit','HHkinsvfit', 'VBFjet1', 'VBFjet2']
  variables = ['pt','eta','mass','phi']
  for st in stuff : 
    for var in variables : 
      if 'VBFjet' in st and var == 'mass' : continue 
      whatToPlot.append(st+'_'+var)

  whatToPlot += ["VBFjj_mass","VBFjj_deltaPhi", "VBFjj_deltaEta", "VBFgenjj_deltaPhi", "VBFjj_deltaR"]
  whatToPlot += ["HH_deltaPhi", "HH_deltaEta", "HH_deltaR"]
  whatToPlot += ['HHkinsvfit_bHmass','HHsvfit_deltaPhi', 'HHKin_mass_raw', 'HHKin_chi2'] 
  whatToPlot += ['VBFjb_deltaR', 'VBFjTau_deltaR']


plottingStuff = { 'lowlimityaxis' : 0,
            'highlimityaxis' : 1,
            'markersize': 1,
	          'yaxistitleoffset': 1.5,
	          'legxlow' : 0.3075 + 1 * 0.1975,
	          #'legxlow' : 0.3075 + 2 * 0.1975,
	          'legylow': 0.75,
	          'legxhigh': 0.9,
	          'legyhigh': 0.9,
	          'markertypedir':{},
	          'markercolordir':{}, 
   	        }   

t0 = 0
for plot in whatToPlot : 
  for cat in categories : 
    listOfPlots = []
    if my_namespace.merge == True :
      legends = mergingCategories.keys() 
      for merge in mergingCategories :
        plotTools.makePlot(listOfPlots, eosPath + '2017/', mergingCategories[merge] , plot+'_'+cat, merge=True, normalize=True)
    else :
      legends = files
      for fil in files :
        plotTools.makePlot(listOfPlots, eosPath + '2017/', fil + '.root', plot+'_'+cat, merge=False, normalize=True)
    plotTools.combinePlots (listOfPlots, legends, plottingStuff, plotPath, plot+'_'+cat) 
    plotTools.combinePlots (listOfPlots, legends, plottingStuff, plotPath, plot+'_'+cat, logy=True) 


    if my_namespace.copy == True: 
      for ext in ['.png','.pdf'] : 
      #for ext in ['.png','.pdf','.root'] : 
        rc = call('cp ' + plotPath + plot + '_' + cat + ext + ' ' + copyPath + '/' + cat + '/', shell=True)
        rc = call('cp ' + plotPath + plot + '_' + cat + '_logy' + ext + ' ' + copyPath + '/' + cat + '/', shell=True)
      print 'Copying ' +  plotPath + plot + '_' + cat + '.* to ' + copyPath + '/' + cat 
  


