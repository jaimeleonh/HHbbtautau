import sys, os
import time
import ROOT as r
from ROOT import gSystem
r.gROOT.SetBatch(True)
from subprocess import call
from samples import samples
from collections import OrderedDict
import plotTools
import datetime

import argparse
parser = argparse.ArgumentParser(description='Plotter options')
parser.add_argument('-n','--ntuples', action='store_true', default = False)
parser.add_argument('-c','--copy', action='store_true', default = False)
parser.add_argument('-m','--merge', action='store_true', default = False)
parser.add_argument('-p','--plots', action='store_false', default = True)
parser.add_argument('-rc','--runInCondor', action='store_true', default = False)
parser.add_argument('-dmc','--dataMC', action='store_true', default = False)
parser.add_argument('-d','--directory', dest='userCopyPath', default = '')
my_namespace = parser.parse_args()

if my_namespace.ntuples == True or my_namespace.runInCondor == True:
  print ("Starting ntuplizer for every sample in input")
  time.sleep(2)
#    r.gInterpreter.ProcessLine(".x  ./scripts/loadExampleAnalysis.C")
#    dir_path = os.path.dirname(os.path.realpath(__file__))
#    gSystem.Load(dir_path + "analysisCode_C.so")
#    from ROOT import analysisCode
else : 
  print("Not making ntuples. If you want to make them, restart with '-n' (local) or '-rc' (HTCondor) as argument ")
  time.sleep(2)

#path = '/eos/home-j/jleonhol/HHbbtautau/2017/'
path = '/eos/home-c/camendol/SKIMS_Thesis2017/'
#path = '/eos/home-c/camendol/SKIMS_Legacy2018/SKIMS_30Jan2020/'
eosPath = '/eos/home-j/jleonhol/HHbbtautau/'
plotPath = './plots/'

year = '2017'
selectionCfg = './config/selectionCfg_TauTau_VBF.cfg'


categories = ["baseline_tauhtauh", "baseline_etauh", "baseline_mutauh","noSelection"]
#categories = ["baseline","noSelection"]
#categories = ["baseline","noSelection","s1b1jresolvedMcut", "s2b0jresolvedMcut", "VBFtight_DNN", "VBFloose_DNN", "sboostedLLMcut", "VBFloose", "VBFtight"]

if my_namespace.userCopyPath == '' : 
  copyPath = '/eos/home-j/jleonhol/www/HHbbtautau/' + year 
else : 
  copyPath = '/eos/home-j/jleonhol/www/HHbbtautau/' + my_namespace.userCopyPath + '/'

if (my_namespace.copy == True) :
  rc = call('mkdir ' + copyPath, shell=True)
  rc = call('cp -r /eos/home-j/jleonhol/backup/index_HHbbtautau_php ' + copyPath +  '/index.php' , shell=True)
  for cat in categories : 
    rc = call('mkdir ' + copyPath +  '/' + cat + '/' , shell=True)
    rc = call('cp -r /eos/home-j/jleonhol/backup/index_HHbbtautau_php ' + copyPath + '/' + cat + '/index.php' , shell=True)



rc = call('mkdir ' + plotPath, shell=True) 
rc = call('mkdir ' + eosPath + year +'/', shell=True)

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
  files.append("GGHSM_xs")
  files.append("VBF_CV_1_C2V_1_C3_1")
  files += ["ttHJetToBB", "ttHJetTononBB"]
  files.append("PrivateGluGlu12JetsHHTo2B2Taus2017_SKIM")
  files += ["TT_fullyHad", "TT_semiLep", "TT_fullyLep"]

  files += ["DYJets_0j0b_0b", "DYJets_1j0b_0b", "DYJets_1j1b_0b", "DYJets_2j0b_0b", "DYJets_2j1b_0b", "DYJets_2j2b_0b", "DYJets_3j0b_0b", "DYJets_3j1b_0b", "DYJets_3j2b_0b", "DYJets_3j3b_0b", "DYJets_4j0b_0b", "DYJets_4j1b_0b", "DYJets_4j2b_0b", "DYJets_4j3b_0b", "DYJets_4j4b_0b"]
  files += ["DYJets_0j0b_1b", "DYJets_1j0b_1b", "DYJets_1j1b_1b", "DYJets_2j0b_1b", "DYJets_2j1b_1b", "DYJets_2j2b_1b", "DYJets_3j0b_1b", "DYJets_3j1b_1b", "DYJets_3j2b_1b", "DYJets_3j3b_1b", "DYJets_4j0b_1b", "DYJets_4j1b_1b", "DYJets_4j2b_1b", "DYJets_4j3b_1b", "DYJets_4j4b_1b"]
  files += ["DYJets_0j0b_2b", "DYJets_1j0b_2b", "DYJets_1j1b_2b", "DYJets_2j0b_2b", "DYJets_2j1b_2b", "DYJets_2j2b_2b", "DYJets_3j0b_2b", "DYJets_3j1b_2b", "DYJets_3j2b_2b", "DYJets_3j3b_2b", "DYJets_4j0b_2b", "DYJets_4j1b_2b", "DYJets_4j2b_2b", "DYJets_4j3b_2b", "DYJets_4j4b_2b"]
  files += ["WJets_HT_0_100","WJets_HT_1200_2500","WJets_HT_100_200", "WJets_HT_2500_Inf", "WJets_HT_200_400", "WJets_HT_400_600", "WJets_HT_600_800", "WJets_HT_800_1200"]
  files += ["ST_tW_antitop", "ST_tchannel_antitop", "ST_tW_top", "ST_tchannel_top", "EWKWMinus2Jets_WToLNu", "EWKWPlus2Jets_WToLNu", "EWKZ2Jets_ZToLL", "EWKZ2Jets_ZToNuNu","WWTo2L2Nu", "WWTo4Q", "WWToLNuQQ", "WZTo2L2Q", "WZTo1L1Nu2Q", "WZTo3LNu", "ZZTo2L2Q", "ZZTo4L", "ZH_HBB_ZLL", "ZH_HTauTau", "ggHTauTau", "VBFHTauTau", "WplusHTauTau", "WminusHTauTau", "WWW", "WWZ", "WZZ", "TTWJetsToLNu", "TTWJetsToQQ", "TTWW"]

  dataFiles = []
  #dataFiles = ['Tau2017C','Tau2017D','Tau2017E','Tau2017F']
  dataFiles = ['Tau2017B','Tau2017C','Tau2017D','Tau2017E','Tau2017F']



  mergingCategories = OrderedDict()
 # mergingCategories["ggHSM"] = ["GGHSM_xs"]
 # mergingCategories["VBFSM"] = ["VBF_CV_1_C2V_1_C3_1"]
  #mergingCategories["ttHJetToBB"] = ["ttHJetToBB"]
 # mergingCategories["ggF+2jets"] = ["PrivateGluGlu12JetsHHTo2B2Taus2017_SKIM"]
  mergingCategories["TT"] = ["TT_fullyHad", "TT_semiLep", "TT_fullyLep"]
  mergingCategories["DY"] = ["DYJets_0j0b_0b", "DYJets_1j0b_0b", "DYJets_1j1b_0b", "DYJets_2j0b_0b", "DYJets_2j1b_0b", "DYJets_2j2b_0b", "DYJets_3j0b_0b", "DYJets_3j1b_0b", "DYJets_3j2b_0b", "DYJets_3j3b_0b", "DYJets_4j0b_0b", "DYJets_4j1b_0b", "DYJets_4j2b_0b", "DYJets_4j3b_0b", "DYJets_4j4b_0b"]
  #mergingCategories["DY+0b"] = ["DYJets_0j0b_0b", "DYJets_1j0b_0b", "DYJets_1j1b_0b", "DYJets_2j0b_0b", "DYJets_2j1b_0b", "DYJets_2j2b_0b", "DYJets_3j0b_0b", "DYJets_3j1b_0b", "DYJets_3j2b_0b", "DYJets_3j3b_0b", "DYJets_4j0b_0b", "DYJets_4j1b_0b", "DYJets_4j2b_0b", "DYJets_4j3b_0b", "DYJets_4j4b_0b"]
  mergingCategories["DY"] += ["DYJets_0j0b_1b", "DYJets_1j0b_1b", "DYJets_1j1b_1b", "DYJets_2j0b_1b", "DYJets_2j1b_1b", "DYJets_2j2b_1b", "DYJets_3j0b_1b", "DYJets_3j1b_1b", "DYJets_3j2b_1b", "DYJets_3j3b_1b", "DYJets_4j0b_1b", "DYJets_4j1b_1b", "DYJets_4j2b_1b", "DYJets_4j3b_1b", "DYJets_4j4b_1b"]
  #mergingCategories["DY+1b"] = ["DYJets_0j0b_1b", "DYJets_1j0b_1b", "DYJets_1j1b_1b", "DYJets_2j0b_1b", "DYJets_2j1b_1b", "DYJets_2j2b_1b", "DYJets_3j0b_1b", "DYJets_3j1b_1b", "DYJets_3j2b_1b", "DYJets_3j3b_1b", "DYJets_4j0b_1b", "DYJets_4j1b_1b", "DYJets_4j2b_1b", "DYJets_4j3b_1b", "DYJets_4j4b_1b"]
  mergingCategories["DY"] += ["DYJets_0j0b_2b", "DYJets_1j0b_2b", "DYJets_1j1b_2b", "DYJets_2j0b_2b", "DYJets_2j1b_2b", "DYJets_2j2b_2b", "DYJets_3j0b_2b", "DYJets_3j1b_2b", "DYJets_3j2b_2b", "DYJets_3j3b_2b", "DYJets_4j0b_2b", "DYJets_4j1b_2b", "DYJets_4j2b_2b", "DYJets_4j3b_2b", "DYJets_4j4b_2b"]
  #mergingCategories["DY+2b"] = ["DYJets_0j0b_2b", "DYJets_1j0b_2b", "DYJets_1j1b_2b", "DYJets_2j0b_2b", "DYJets_2j1b_2b", "DYJets_2j2b_2b", "DYJets_3j0b_2b", "DYJets_3j1b_2b", "DYJets_3j2b_2b", "DYJets_3j3b_2b", "DYJets_4j0b_2b", "DYJets_4j1b_2b", "DYJets_4j2b_2b", "DYJets_4j3b_2b", "DYJets_4j4b_2b"]
  mergingCategories["W+jets"] = ["WJets_HT_0_100","WJets_HT_1200_2500","WJets_HT_100_200", "WJets_HT_2500_Inf", "WJets_HT_200_400", "WJets_HT_400_600", "WJets_HT_600_800", "WJets_HT_800_1200"]
  mergingCategories["others"] = ["ST_tW_antitop", "ST_tchannel_antitop", "ST_tW_top", "ST_tchannel_top", "EWKWMinus2Jets_WToLNu", "EWKWPlus2Jets_WToLNu", "EWKZ2Jets_ZToLL", "EWKZ2Jets_ZToNuNu","WWTo2L2Nu", "WWTo4Q", "WWToLNuQQ", "WZTo2L2Q", "WZTo1L1Nu2Q", "WZTo3LNu", "ZZTo2L2Q", "ZZTo4L", "ZH_HBB_ZLL", "ZH_HTauTau", "ggHTauTau", "VBFHTauTau", "WplusHTauTau", "WminusHTauTau", "WWW", "WWZ", "WZZ", "TTWJetsToLNu", "TTWJetsToQQ", "TTWW"] + ["ttHJetToBB", "ttHJetTononBB"]


  data = ['Tau2017B','Tau2017C','Tau2017D','Tau2017E','Tau2017F']


if my_namespace.runInCondor :

  outDir = datetime.datetime.now().strftime('%Y.%m.%d_%H.%M.%S')
  outDir = "jobs_"+outDir
 
  here = os.getcwd()

  program = 'runCode.exe'

  proto = 'filler_' ## job .sh fie name
  logproto = 'log_' ## job .sh fie name

  os.system('mkdir ' + outDir)
  myJob = 0 

  for nj, (fil) in enumerate(files+dataFiles):
    scriptName = proto + str(nj) + '.sh'
    logName    = logproto + str(nj) + '.txt'
    scriptFile = open (outDir + '/' + scriptName, 'w')
    scriptFile.write ('#!/bin/bash\n')
    scriptFile.write ('cd %s\n' % here)
    scriptFile.write ('export SCRAM_ARCH=slc6_amd64_gcc491\n')
    scriptFile.write ('eval `scram r -sh`\n')
    scriptFile.write ('source scripts/setup.sh\n')
    command = program + ' '
    command += samples[year][fil] 
    

    command += ' ' + eosPath + year + '/' + fil + '.root ' + selectionCfg + ' ' + fil
    if fil in files : command += ' 1'
    else : command += ' 0'

    scriptFile.write(command)
    scriptFile.close()
    
    os.system ('chmod u+rwx ' + outDir + '/' + scriptName)

    condorName = "submit_condor_" + str(nj) + ".sub"
    f = open (outDir + '/' + condorName, 'w')
    f.write( "executable         = %s/%s\n"%(outDir,scriptName))
    f.write( "output             = %s/$(ClusterId).$(ProcId).out\n"%outDir)
    f.write( "error              = %s/$(ClusterId).$(ProcId).error\n"%outDir)
    f.write( "log                = %s/$(ClusterId).log\n"%outDir)
    f.write( '+JobFlavour        = "longlunch"\n')
    f.write( "queue\n")
    f.close()

    os.system ( 'condor_submit %s/submit_condor_%s.sub'%(outDir,str(nj)))
  sys.exit(0)


for fil in files+dataFiles :
  if my_namespace.ntuples == True :
    continue #FIXME
    print ('Obtaining plot ntuples for ' + fil)
    time.sleep(2) 
    program = 'runCode_True.exe'
    command = program + ' '
    if (fil != 'PrivateGluGlu12JetsHHTo2B2Taus2017_SKIM') : command += path + 'SKIM_' + fil  
    else : command += '/eos/home-j/jleonhol/HHbbtautau/2017/' + fil 
    
    command += ' ' + eosPath + '2017/' + fil + '.root '
    if fil in files : command += ' 1'
    else : command += ' 0'

    os.system(command)


if not my_namespace.plots : sys.exit(0)



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

if my_namespace.merge == True or my_namespace.dataMC == True:
  myFiles = {}
  for merge in mergingCategories: 
    myFiles[merge] = []
    for fil in mergingCategories[merge] : 
      myFiles[merge].append(r.TFile.Open(eosPath + year + '/' +fil+'.root'))
if my_namespace.dataMC == True : 
  dataFiles = []
  for fil in data : 
    dataFiles.append(r.TFile.Open(eosPath + year + '/'+fil+'.root'))

for plot in whatToPlot :
  for cat in categories : 
    listOfPlots = []
    listOfDataPlots = []
    
    if my_namespace.merge == True or my_namespace.dataMC == True:
      lumi = 41557 
      if my_namespace.dataMC == True : normalize = lumi
      else : normalize = 1

      legends = mergingCategories.keys() 
      for merge in mergingCategories :
        plotTools.makePlot(listOfPlots, eosPath + year + '/', myFiles[merge] , plot+'_'+cat, True, normalize)
        #plotTools.makePlot(listOfPlots, eosPath + '2017/', mergingCategories[merge] , plot+'_'+cat, True, normalize)
      if my_namespace.dataMC == True : 
        plotTools.makePlot(listOfDataPlots, eosPath + year + '/', dataFiles , plot+'_'+cat, True, -1)
        #plotTools.makePlot(listOfDataPlots, eosPath + '2017/', data , plot+'_'+cat, True, normalize)

    else :
      legends = files
      for fil in files :
        plotTools.makePlot(listOfPlots, eosPath + year + '/', fil + '.root', plot+'_'+cat, merge=False, normalize=1)
    
    if not my_namespace.dataMC : 
      plotTools.combinePlots (listOfPlots, legends, plottingStuff, plotPath, plot+'_'+cat, logy=False) 
      plotTools.combinePlots (listOfPlots, legends, plottingStuff, plotPath, plot+'_'+cat, logy=True) 

      if my_namespace.copy == True: 
        for ext in ['.png','.pdf'] : 
        #for ext in ['.png','.pdf','.root'] : 
          rc = call('cp ' + plotPath + plot + '_' + cat + ext + ' ' + copyPath + '/' + cat + '/', shell=True)
          rc = call('cp ' + plotPath + plot + '_' + cat + '_logy' + ext + ' ' + copyPath + '/' + cat + '/', shell=True)
        print 'Copying ' +  plotPath + plot + '_' + cat + '.* to ' + copyPath + '/' + cat 
    else : 
      plotTools.dataMCPlots (listOfDataPlots, listOfPlots, legends, plottingStuff, plotPath, plot+'_'+cat, logy=False) 
      if my_namespace.copy == True: 
        for ext in ['.png','.pdf'] : 
        #for ext in ['.png','.pdf','.root'] : 
          rc = call('cp ' + plotPath + plot + '_' + cat + ext + ' ' + copyPath + '/' + cat + '/', shell=True)
        print 'Copying ' +  plotPath + plot + '_' + cat + '.* to ' + copyPath + '/' + cat 

  


