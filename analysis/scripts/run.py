import sys, os
import time
import ROOT as r
from ROOT import gSystem
r.gROOT.SetBatch(True)
from subprocess import call
from samples import samples
from config import files as allFiles, mergingCategories as allMergingCategories, signal as allSignals, dataCategories as dataCategories
from collections import OrderedDict
import plotTools
import datetime
import OutputManager as omng
import itertools

import argparse
parser = argparse.ArgumentParser(description='Plotter options')
parser.add_argument('-n','--ntuples', action='store_true', default = False)
parser.add_argument('-c','--copy', action='store_true', default = False)
parser.add_argument('-m','--merge', action='store_true', default = False)
parser.add_argument('-p','--plots', action='store_false', default = True)
parser.add_argument('-rc','--runInCondor', action='store_true', default = False)
parser.add_argument('-l','--launch', action='store_false', default = True)
parser.add_argument('-dmc','--dataMC', action='store_true', default = False)
parser.add_argument('-d','--directory', dest='userCopyPath', default = '')
parser.add_argument('-rew','--reweightVBF', action='store_true', default = False)
parser.add_argument('-vbf','--VBFtask', action='store_true', default = False)
parser.add_argument('-rat','--Ratios', action='store_true', default = False)
options = parser.parse_args()

if options.ntuples == True or options.runInCondor == True:
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
#path = '/eos/home-c/camendol/SKIMS_Thesis2017/'
path = '/eos/home-c/camendol/SKIMMED_Legacy2017_27mar2020_DNN' ## USELESS RIGHT NOW, PATH ADDED IN FILES
#path = '/eos/home-c/camendol/SKIMS_Legacy2018/SKIMS_30Jan2020/'
eosPath = '/eos/home-j/jleonhol/HHbbtautau/'
plotPath = './plots/'

selections = ["tauhtauh"]
#selections = ["tauhtauh", "etauh","mutauh",]
regions = ["SR", "SStight", "OSrlx", "SSrlx", "OSinviso", "SSinviso"]
myCategories = [x[0] + '_' + x[1] for x in list(itertools.product(selections, regions))]

#########################################################################################
#########################################################################################
year = '2018_vbf'
#########################################################################################
#########################################################################################


allSelectionCfg = {}
allSelectionCfg["2017"] = './config/selectionCfg_2017.cfg'
allSelectionCfg["2017_FC"] = './config/selectionCfg_2017_new.cfg'
allSelectionCfg["2017_may"] = './config/selectionCfg_2017_may.cfg'
allSelectionCfg["2017_vbf"] = './config/selectionCfg_2017_may.cfg'
allSelectionCfg["2018_vbf"] = './config/selectionCfg_2017_may.cfg'

if "2017" in year: lumi = '41557' 
elif "2018" in year: lumi = '59970'
else: 
    print "LUMI ERROR. Exiting"
    sys.exit()

selectionCfg = allSelectionCfg[year]

#categories = ["baseline_tauhtauh_SR", "baseline_etauh_SR", "baseline_mutauh_SR"]
#categories = ["baseline","noSelection"]
#categories = ["baseline","noSelection","s1b1jresolvedMcut", "s2b0jresolvedMcut", "VBFtight_DNN", "VBFloose_DNN", "sboostedLLMcut", "VBFloose", "VBFtight"]



rc = call('mkdir ' + plotPath, shell=True) 
rc = call('mkdir ' + eosPath + year +'/', shell=True)
copyPath = '/eos/home-j/jleonhol/www/HHbbtautau/' + year + "/"
rc = call('mkdir ' + copyPath, shell=True)
rc = call('cp -r /eos/home-j/jleonhol/backup/index_HHbbtautau_php ' + copyPath +  '/index.php' , shell=True)

files = allFiles[year] 
#files = []
#files = ["GGHHSM","VBFHHSM","VBFHH_CV_1_C2V_1_C3_2","VBFHH_CV_1_C2V_1_C3_0"]

dataFiles = []
#dataFiles = ['Tau2017B','Tau2017C','Tau2017D','Tau2017E','Tau2017F', 
            # 'SingleMuon2017B','SingleMuon2017C','SingleMuon2017D','SingleMuon2017E','SingleMuon2017F',
            # 'SingleElectron2017B','SingleElectron2017C','SingleElectron2017D','SingleElectron2017E','SingleElectron2017F',
#            ]

########################## MERGING CATEGORIES ########################
signal = allSignals[year]
mergingCategories = allMergingCategories[year]
data = dataCategories[year]
######################################################################

selections = data.keys() if data.keys() else selections 

categories = ["baseline_{}_".format(sel) for sel in selections]

if options.VBFtask: 
    categories = ["VBF_baseline", "VBF_loose_baseline"]
    selections = ["tauhtauh"]

if options.copy and options.userCopyPath == '' :
  print "If you want to copy sth, add a path!"
  sys.exit()
elif options.copy:

  copyPath = '/eos/home-j/jleonhol/www/HHbbtautau/' + year + "/" + options.userCopyPath + '/'

if (options.copy == True) :
  rc = call('mkdir ' + copyPath, shell=True)
  rc = call('cp -r /eos/home-j/jleonhol/backup/index_HHbbtautau_php ' + copyPath +  '/index.php' , shell=True)
  print categories
  for cat in categories : 
    if options.dataMC or options.merge or options.reweightVBF:  
      rc = call('mkdir ' + copyPath +  '/' + cat + 'SR/' , shell=True)
      rc = call('cp -r /eos/home-j/jleonhol/backup/index_HHbbtautau_php ' + copyPath + '/' + cat + 'SR/index.php' , shell=True)
    else: 
      rc = call('mkdir ' + copyPath +  '/' + cat + '/' , shell=True)
      rc = call('cp -r /eos/home-j/jleonhol/backup/index_HHbbtautau_php ' + copyPath + '/' + cat + '/index.php' , shell=True)


if options.runInCondor :

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

    sample = fil
    njets = -1
    if "GGHHNLO" in fil: 
        if "Jet" in fil: 
            sample = "GGHHSM_Jets"
            if "1" in fil: njets = "1"
            if "2" in fil: njets = "2"
    command += samples[year][sample] 
     

    command += ' ' + eosPath + year + '/' + fil + '.root ' + selectionCfg + ' ' + sample
    if fil in files : command += ' 1 '
    else : command += ' 0 '
    command += "{} {}".format(lumi, njets)

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

    if options.launch : os.system ( 'condor_submit %s/submit_condor_%s.sub'%(outDir,str(nj)))
  sys.exit(0)


for fil in files+dataFiles : #FIXME or better run -rc -l
  if options.ntuples == True :
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


if not options.plots : sys.exit(0)



whatToPlot = []


if 'Chiara' in copyPath : #plots from Chiara's thesis 
  stuff = ['tau1', 'tau2', 'bjet1', 'bjet2', 'additionalJet1','additionalJet2','VBFjet1', 'VBFjet2','additionalVBFjet1']
  variables = ['pt','eta','z', 'e']
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


if 'DNN' in copyPath : #plots from the different DNNs
  whatToPlot+=["DNN_VBFvsGGF_TauTauTight", "DNN_VBFvsGGF_TauTauLoose", "DNN_VBFvsGGF_MuTau", "DNN_VBFvsGGF_ETau", "DNNoutSM_kl_1", "BDToutSM_kl_1"]
  
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

# VBF vs ggH task 
if options.VBFtask or options.reweightVBF:
    whatToPlot = ["additionalJet1_pt", "additionalJet1_eta", "additionalJet2_pt", "additionalJet2_eta", 
                  "bjets_eta1eta2", "bjets_deltaEta", "VBFjj_eta1eta2", "additionalJets_deltaEta", "additionalJets_eta1eta2", "additionalJets_mass",
                  "HH_pt", "HH_mass", "tauH_pt", "tauH_eta", "bH_pt", "bH_eta", "HH_costhetaCS", "HH_costhetaCS_rev", "HH_costhetaCS_svfit",
                  "costheta_b1_b2", "costheta_tau1_tau2", "VBFjj_mass", "VBFjj_mass_5000", "VBFjj_deltaEta", 
                  "VBFjet1_pt", "VBFjet2_pt", "VBFjet1_eta", "VBFjet2_eta", "centrality_bb", 
                  "centrality_tautau", "VBFjTau_deltaR", "VBFjb_deltaR", "btau_dr_min", "btau_dr_max", "HHKin_mass_raw", "HHkinsvfit_mass", 
                  "VBFjj_deltaPhi", "VBFjj_deltaR", "deta_hbb_svfit", "NGenJets", "prodgenjet1_pt", "dib_deltaPhi", "ditau_deltaPhi"
                 ]

    #pt / mass
    whatToPlot += ["tau1_pt_m", "tau2_pt_m", "bjet1_pt_m", "bjet2_pt_m", "VBFjet1_pt_m", "VBFjet2_pt_m",
                   "bH_pt_m", "tauH_pt_m"]

    # centralities
    whatToPlot += ["tau1_z", "tau2_z", "bjet1_z", "bjet2_z", "tauH_z", "bH_z", "HH_z", "HH_z_nt"]


    mySignalFiles = {} 
    for signalS in signal:
        if signalS == "VBF": continue
        mySignalFiles[signalS] = []
        for sample in signal[signalS] : 
            mySignalFiles[signalS].append(r.TFile.Open(eosPath + year + '/' +sample+'.root'))














plottingStuff = { 'lowlimityaxis' : 0,
            'highlimityaxis' : 1,
            'markersize': 1,
	          'yaxistitleoffset': 1.5,
	          'legxlow' : 0.3575 + 1 * 0.1975,
	          #'legxlow' : 0.3075 + 2 * 0.1975,
	          'legylow': 0.70,
	          'legxhigh': 0.85,
	          'legyhigh': 0.85,
	          'markertypedir':{},
	          'markercolordir':{},
   	        }   

t0 = 0


if options.merge == True or options.dataMC == True or options.reweightVBF == True:
  #BACKGROUND FILES
  myFiles = {}
  for merge in mergingCategories: 
    myFiles[merge] = []
    for fil in mergingCategories[merge] : 
      myFiles[merge].append(r.TFile.Open(eosPath + year + '/' +fil+'.root'))
  mySignalFiles = {}

  #SIGNAL FILES
  for signalS in signal: 
    mySignalFiles[signalS] = []
    for sample in signal[signalS] : 
      mySignalFiles[signalS].append(r.TFile.Open(eosPath + year + '/' +sample+'.root'))
  
  #DATAFILES
  dataFiles = {}
  for chan in data :
    dataFiles[chan] = []
    for fil in data[chan] :
      dataFiles[chan].append(r.TFile.Open(eosPath + year + '/'+fil+'.root'))

  
  omngr = omng.OutputManager()
  omngr.sel_def     = selections
  omngr.sel_regions = regions    
  omngr.selections  = ["baseline_" + x[0] + '_' + x[1] for x in list(itertools.product(selections, regions))]   
  omngr.variables   = whatToPlot  
  omngr.variables2D = [] 
  # omngr.samples     = sigList + bkgList + dataList
  omngr.data        = data
  omngr.dataFiles   = dataFiles
  omngr.bkgs        = mergingCategories
  omngr.bkgFiles    = myFiles
  omngr.path        = eosPath + year + '/'
  omngr.year        = year
  if "VBF" in signal: 
    omngr.sigs        = signal["VBF"]
    omngr.sigFiles    = mySignalFiles["VBF"]

  omngr.merge()
  
  if options.merge == True or options.dataMC == True:
  
    SBtoSRforQCD = 1
    computeSBtoSRdyn = False
    if SBtoSRforQCD == 1: 
      computeSBtoSRdyn = True
    omngr.makeQCD(
        SR           = "SR",
        yieldSB      = "OSinviso",
        shapeSB      = "OSinviso",
        SBtoSRfactor = 1,
        regionC      = "SStight",   
        regionD      = "SSinviso",   
        doFitIf      = "False",
        fitFunc      = "[0] + [1]x",
        computeSBtoSR = computeSBtoSRdyn
        )

if options.reweightVBF:
    myVBFSamples = []
    target_kl  = [1]
    #target_kl = [-2,-1,0,1,2]
    target_cv  = [1]
    #target_c2v = [1]
    target_c2v = [1, 1.2, 1.4, 1.6, 1.8, 2]
    #target_c2v = [-2,-1,0,1,2]
    target_xs = 1
    
    for t_kl in target_kl: 
      for t_cv in target_cv: 
        for t_c2v in target_c2v: 
          myVBFSamples.append('VBF_CV_'+str(t_cv)+'_C2V_'+str(t_c2v)+'_C3_'+str(t_kl))

    omngr.makeVBFrew(signal["VBF"], target_kl, target_cv, target_c2v, target_xs) 


if options.dataMC == True : 
  for plot in whatToPlot :
    for cat in selections : 
      if "TauTau" in plot and "tauhtauh" not in cat : continue
      if "ETau" in plot and "etauh" not in cat : continue
      if "MuTau" in plot and "mutauh" not in cat : continue
    #for cat in myCategories : 
      listOfPlots = []
      listOfDataPlots = []
      signalList = []
      fullCat="baseline_"+cat+"_SR"
      
      for merge in mergingCategories.keys()+["QCD"] : 
        listOfPlots.append(omngr.histos[merge + "_" +fullCat + "_" + plot ])
      for merge in signal : 
        if merge == "VBF" : continue
        plotTools.makePlot(signalList, eosPath + year + '/', mySignalFiles[merge] , plot+'_'+fullCat, True, -1)
      plotTools.makePlot(listOfDataPlots, eosPath + year + '/', dataFiles[cat], plot+'_'+fullCat, True, -1)

      plottingStuff["channel"] = cat
      plottingStuff["region"] = "SR"
      plottingStuff["selection"] = "Baseline"
      
      legends = mergingCategories.keys()+["QCD"]+signal.keys()
      plotTools.dataMCPlots (listOfDataPlots, listOfPlots, signalList, legends, plottingStuff, plotPath, plot+'_'+fullCat, logy=False) 
      if options.copy == True: 
        for ext in ['.png','.pdf'] : 
        #for ext in ['.png','.pdf','.root'] : 
          rc = call('cp ' + plotPath + plot + '_' + fullCat + ext + ' ' + copyPath + '/' + fullCat + '/', shell=True)
        print 'Copying ' +  plotPath + plot + '_' + fullCat + '.* to ' + copyPath + '/' + fullCat 
      
  sys.exit()

if options.merge == True : 
  for plot in whatToPlot :
    for cat in selections : 
      if "TauTau" in plot and "tauhtauh" not in cat : continue
      if "ETau" in plot and "etauh" not in cat : continue
      if "MuTau" in plot and "mutauh" not in cat : continue
      fullCat="baseline_"+cat+"_SR"
      listOfPlots = []
      for merge in signal :
        if merge == "VBF" : continue
        plotTools.makePlot(listOfPlots, eosPath + year + '/', mySignalFiles[merge] , plot+'_'+fullCat, True, -1)
      for merge in mergingCategories.keys()+["QCD"] : 
        listOfPlots.append(omngr.histos[merge + "_" +fullCat + "_" + plot ])
      legends = signal.keys() + mergingCategories.keys()+["QCD"]


      plotTools.combinePlots (listOfPlots, legends, plottingStuff, plotPath, plot+'_'+fullCat, logy=False, normalize=True) 
      if options.copy == True: 
        for ext in ['.png','.pdf'] : 
        #for ext in ['.png','.pdf','.root'] : 
          rc = call('cp ' + plotPath + plot + '_' + fullCat + ext + ' ' + copyPath + '/' + fullCat + '/', shell=True)
        print 'Copying ' +  plotPath + plot + '_' + fullCat + '.* to ' + copyPath + '/' + fullCat 
  sys.exit()

if options.reweightVBF == True : 
  for plot in whatToPlot :
    for cat in selections : 
      if "TauTau" in plot and "tauhtauh" not in cat : continue
      if "ETau" in plot and "etauh" not in cat : continue
      if "MuTau" in plot and "mutauh" not in cat : continue
      fullCat="baseline_"+cat+"_SR"
      listOfPlots = []
      for sig in myVBFSamples:
        listOfPlots.append(omngr.histos[sig + "_" +fullCat + "_" + plot ])
      plotTools.makePlot(listOfPlots, eosPath + year + '/', mySignalFiles["GGHHSM_LO"] , plot+'_'+fullCat, True, -1)
      legends = myVBFSamples+["GGHHSM_LO"]
      plottingStuff['legxlow'] = 0.2575 + 1 * 0.1975
      plottingStuff['legylow'] = 0.75
      plottingStuff['legxhigh'] = 0.85
      plottingStuff['legyhigh'] = 0.85
      if cat == "tauhtauh":
        plottingStuff["channel"] = r"#tau#tau"
      elif cat == "etauh":
        plottingStuff["channel"] = r"e#tau"
      elif cat == "mutauh":
        plottingStuff["channel"] = r"#mu#tau"

      plottingStuff["region"] = "SR"
      plottingStuff["selection"] = "Baseline"
      
      plotTools.combinePlots (listOfPlots, legends, plottingStuff, plotPath, plot+'_'+fullCat, logy=False, normalize=True, lumi=int(lumi)) 
      plotTools.combinePlots (listOfPlots, legends, plottingStuff, plotPath, plot+'_'+fullCat, logy=True, normalize=True, lumi=int(lumi)) 
      if options.copy == True: 
        for ext in ['.png','.pdf'] : 
        #for ext in ['.png','.pdf','.root'] : 
          rc = call('cp ' + plotPath + plot + '_' + fullCat + ext + ' ' + copyPath + '/' + fullCat + '/', shell=True)
          rc = call('cp ' + plotPath + plot + '_' + fullCat + "_logy" + ext + ' ' + copyPath + '/' + fullCat + '/', shell=True)
        print 'Copying ' +  plotPath + plot + '_' + fullCat + '.* to ' + copyPath + '/' + fullCat 
  sys.exit()

myRatios = []
myRatios.append({"num": 'GGHHSM_LO', 
                 "den": 'GGHHSM_NLO',
                 "legend": 'GGHH LO/NLO', 
                 "color": r.kBlack
                })
myRatios.append({ "num": 'GGHHSM_LO #leq 2 Jets' if "2018" in year else "GGHHSM_NLO + 1,2 Jets", 
                  "den": 'GGHHSM_NLO',
                  "legend": 'GGHH LO #leq 2 Jets/NLO' if "2018" in year else "GGHH NLO + 1,2 Jets/NLO",
                  "color": r.kRed
                })

if options.VBFtask == True : 
  for plot in whatToPlot :
    for cat in categories : 
      listOfPlots = []
      legends = []
      for merge in signal : 
        if merge == "VBF" : continue
        if plot == "NGenJets" and "Jets" not in merge: continue
        legends.append(merge)
        plotTools.makePlot(listOfPlots, eosPath + year + '/', mySignalFiles[merge] , plot+'_'+cat+"_SR", True, -1)
      plottingStuff['legxlow'] = 0.2575 + 1 * 0.1975
      plottingStuff['legylow'] = 0.70
      plottingStuff['legxhigh'] = 0.89
      plottingStuff['legyhigh'] = 0.85
      if cat == "VBF_loose_baseline": plottingStuff["selection"] = "VBF enriched baseline"
      elif cat == "VBF_baseline": plottingStuff["selection"] = "VBF baseline"
         
      if options.Ratios:
          ratioPlots = []
          for ratio in myRatios:
              ratioPlots.append({
                  "num": plotTools.makePlotReturn(eosPath + year + '/', mySignalFiles[ratio['num']] , plot+'_'+cat+'_SR', True, 1),
                  "den": plotTools.makePlotReturn(eosPath + year + '/', mySignalFiles[ratio['den']] , plot+'_'+cat+'_SR', True, 1),
                  "legend": ratio['legend'], 
                  "color": ratio['color']
                  })
          plotTools.combinePlotsWithRatios (listOfPlots, ratioPlots, legends, plottingStuff, plotPath, plot+'_'+cat, logy=False, normalize=True, lumi = int(lumi)) 
          plotTools.combinePlotsWithRatios (listOfPlots, ratioPlots, legends, plottingStuff, plotPath, plot+'_'+cat, logy=True, normalize=True, lumi = int(lumi)) 

      else:      
          plotTools.combinePlots (listOfPlots, legends, plottingStuff, plotPath, plot+'_'+cat, logy=False, normalize=True) 
          plotTools.combinePlots (listOfPlots, legends, plottingStuff, plotPath, plot+'_'+cat, logy=True, normalize=True) 
      if options.copy == True: 
        for ext in ['.png','.pdf'] : 
        #for ext in ['.png','.pdf','.root'] : 
          rc = call('cp ' + plotPath + plot + '_' + cat + ext + ' ' + copyPath + '/' + cat + '/', shell=True)
          rc = call('cp ' + plotPath + plot + '_' + cat + "_logy"+ ext + ' ' + copyPath + '/' + cat + '/', shell=True)
        print 'Copying ' +  plotPath + plot + '_' + cat + '.* to ' + copyPath + '/' + cat 
  sys.exit()




#FIXME: Remove merge and dmc from here
for plot in whatToPlot :
  for cat in ["baseline_tauhtauh_"] : 
  #for cat in myCategories : 
    listOfPlots = []
    listOfDataPlots = []

    if options.merge == True :
      normalize = 1

      legends = mergingCategories.keys() 
      for merge in mergingCategories :
        plotTools.makePlot(listOfPlots, eosPath + year + '/', myFiles[merge] , plot+'_'+cat, True, normalize)
        #plotTools.makePlot(listOfPlots, eosPath + '2017/', mergingCategories[merge] , plot+'_'+cat, True, normalize)
      if options.dataMC == True : 
        plotTools.makePlot(listOfDataPlots, eosPath + year + '/', dataFiles , plot+'_'+cat, True, -1)
        #plotTools.makePlot(listOfDataPlots, eosPath + '2017/', data , plot+'_'+cat, True, normalize)

    else :
      legends = files
      for fil in files :
        plotTools.makePlot(listOfPlots, eosPath + year + '/', fil + '.root', plot+'_'+cat, merge=False, normalize=1)
    
    plotTools.combinePlots (listOfPlots, legends, plottingStuff, plotPath, plot+'_'+cat, logy=False) 

    if options.copy == True: 
      for ext in ['.png','.pdf'] : 
      #for ext in ['.png','.pdf','.root'] : 
        rc = call('cp ' + plotPath + plot + '_' + cat + ext + ' ' + copyPath + '/' + cat + '/', shell=True)
       # rc = call('cp ' + plotPath + plot + '_' + cat + '_logy' + ext + ' ' + copyPath + '/' + cat + '/', shell=True)
      print 'Copying ' +  plotPath + plot + '_' + cat + '.* to ' + copyPath + '/' + cat 
  


