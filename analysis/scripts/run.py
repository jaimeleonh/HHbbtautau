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

  dataFiles = []
  #dataFiles = ['Tau2017C','Tau2017D','Tau2017E','Tau2017F']
  #dataFiles = ['Tau2017B','Tau2017C','Tau2017D','Tau2017E','Tau2017F']



  mergingCategories = OrderedDict()
 # mergingCategories["ggHSM"] = ["GGHSM_xs"]
 # mergingCategories["VBFSM"] = ["VBF_CV_1_C2V_1_C3_1"]
  #mergingCategories["ttHJetToBB"] = ["ttHJetToBB"]
 # mergingCategories["ggF+2jets"] = ["PrivateGluGlu12JetsHHTo2B2Taus2017_SKIM"]
  mergingCategories["TT"] = ["TT_fullyHad", "TT_semiLep", "TT_fullyLep"]
  mergingCategories["DY+0b"] = ["DYJets_0j0b_allgenjets_0b", "DYJets_1j0b_allgenjets_0b", "DYJets_1j1b_allgenjets_0b", "DYJets_2j0b_allgenjets_0b", "DYJets_2j1b_allgenjets_0b", "DYJets_2j2b_allgenjets_0b", "DYJets_3j0b_allgenjets_0b", "DYJets_3j1b_allgenjets_0b", "DYJets_3j2b_allgenjets_0b", "DYJets_3j3b_allgenjets_0b", "DYJets_4j0b_allgenjets_0b", "DYJets_4j1b_allgenjets_0b", "DYJets_4j2b_allgenjets_0b", "DYJets_4j3b_allgenjets_0b", "DYJets_4j4b_allgenjets_0b"]
  mergingCategories["DY+1b"] = ["DYJets_0j0b_allgenjets_1b", "DYJets_1j0b_allgenjets_1b", "DYJets_1j1b_allgenjets_1b", "DYJets_2j0b_allgenjets_1b", "DYJets_2j1b_allgenjets_1b", "DYJets_2j2b_allgenjets_1b", "DYJets_3j0b_allgenjets_1b", "DYJets_3j1b_allgenjets_1b", "DYJets_3j2b_allgenjets_1b", "DYJets_3j3b_allgenjets_1b", "DYJets_4j0b_allgenjets_1b", "DYJets_4j1b_allgenjets_1b", "DYJets_4j2b_allgenjets_1b", "DYJets_4j3b_allgenjets_1b", "DYJets_4j4b_allgenjets_1b"]
  mergingCategories["DY+2b"] = ["DYJets_0j0b_allgenjets_2b", "DYJets_1j0b_allgenjets_2b", "DYJets_1j1b_allgenjets_2b", "DYJets_2j0b_allgenjets_2b", "DYJets_2j1b_allgenjets_2b", "DYJets_2j2b_allgenjets_2b", "DYJets_3j0b_allgenjets_2b", "DYJets_3j1b_allgenjets_2b", "DYJets_3j2b_allgenjets_2b", "DYJets_3j3b_allgenjets_2b", "DYJets_4j0b_allgenjets_2b", "DYJets_4j1b_allgenjets_2b", "DYJets_4j2b_allgenjets_2b", "DYJets_4j3b_allgenjets_2b", "DYJets_4j4b_allgenjets_2b"]


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
    if (fil != 'PrivateGluGlu12JetsHHTo2B2Taus2017_SKIM') : command += path + 'SKIM_' + fil  
    else : command += '/eos/home-j/jleonhol/HHbbtautau/2017/' + fil 
    
    command += ' ' + eosPath + '2017/' + fil + '.root '
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
    f.write("queue \n")
    f.close()

    os.system ( 'condor_submit %s/submit_condor_%s.sub'%(outDir,str(nj)))
  sys.exit(0)


for fil in files+dataFiles :
  if my_namespace.ntuples == True :
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
        plotTools.makePlot(listOfPlots, eosPath + '2017/', mergingCategories[merge] , plot+'_'+cat, True, normalize)
      if my_namespace.dataMC == True : 
        plotTools.makePlot(listOfDataPlots, eosPath + '2017/', data , plot+'_'+cat, True, normalize)

    else :
      legends = files
      for fil in files :
        plotTools.makePlot(listOfPlots, eosPath + '2017/', fil + '.root', plot+'_'+cat, merge=False, normalize=1)
    
    if not my_namespace.dataMC : 
      plotTools.combinePlots (listOfPlots, legends, plottingStuff, plotPath, plot+'_'+cat, logy=False) 
      plotTools.combinePlots (listOfPlots, legends, plottingStuff, plotPath, plot+'_'+cat, logy=True) 

    else : 
      plotTools.dataMCPlots (listOfDataPlots, listOfPlots, legends, plottingStuff, plotPath, plot+'_'+cat, logy=False) 
      plotTools.dataMCPlots (listOfDataPlots, listOfPlots, legends, plottingStuff, plotPath, plot+'_'+cat, logy=True) 

    if my_namespace.copy == True: 
      for ext in ['.png','.pdf'] : 
      #for ext in ['.png','.pdf','.root'] : 
        rc = call('cp ' + plotPath + plot + '_' + cat + ext + ' ' + copyPath + '/' + cat + '/', shell=True)
        rc = call('cp ' + plotPath + plot + '_' + cat + '_logy' + ext + ' ' + copyPath + '/' + cat + '/', shell=True)
      print 'Copying ' +  plotPath + plot + '_' + cat + '.* to ' + copyPath + '/' + cat 
  


