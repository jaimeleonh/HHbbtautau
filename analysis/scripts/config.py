from collections import OrderedDict

files = {"2017": [], "2017_FC": [], "2017_may": [] }

files["2017"].append("GGHSM_xs")
files["2017"].append("VBF_CV_1_C2V_1_C3_1")
files["2017"] += ['VBF_CV_1_C2V_1_C3_1', 'VBF_CV_1_C2V_1_C3_0', 'VBF_CV_1_C2V_1_C3_2', 'VBF_CV_1_C2V_2_C3_1', 'VBF_CV_1_5_C2V_1_C3_1', 'VBF_CV_1_C2V_0_C3_2']
files["2017"] += ["ttHJetToBB", "ttHJetTononBB"]
files["2017"].append("PrivateGluGlu12JetsHHTo2B2Taus2017_SKIM")
files["2017"] += ["TTfullyHad", "TTsemiLep", "TTfullyLep"]

files["2017"] += ["DYJets_0j0b_0b", "DYJets_1j0b_0b", "DYJets_1j1b_0b", "DYJets_2j0b_0b", "DYJets_2j1b_0b", "DYJets_2j2b_0b", "DYJets_3j0b_0b", "DYJets_3j1b_0b", "DYJets_3j2b_0b", "DYJets_3j3b_0b", "DYJets_4j0b_0b", "DYJets_4j1b_0b", "DYJets_4j2b_0b", "DYJets_4j3b_0b", "DYJets_4j4b_0b"]
files["2017"] += ["DYJets_0j0b_1b", "DYJets_1j0b_1b", "DYJets_1j1b_1b", "DYJets_2j0b_1b", "DYJets_2j1b_1b", "DYJets_2j2b_1b", "DYJets_3j0b_1b", "DYJets_3j1b_1b", "DYJets_3j2b_1b", "DYJets_3j3b_1b", "DYJets_4j0b_1b", "DYJets_4j1b_1b", "DYJets_4j2b_1b", "DYJets_4j3b_1b", "DYJets_4j4b_1b"]
files["2017"] += ["DYJets_0j0b_2b", "DYJets_1j0b_2b", "DYJets_1j1b_2b", "DYJets_2j0b_2b", "DYJets_2j1b_2b", "DYJets_2j2b_2b", "DYJets_3j0b_2b", "DYJets_3j1b_2b", "DYJets_3j2b_2b", "DYJets_3j3b_2b", "DYJets_4j0b_2b", "DYJets_4j1b_2b", "DYJets_4j2b_2b", "DYJets_4j3b_2b", "DYJets_4j4b_2b"]
files["2017"] += ["WJets_HT_0_100","WJets_HT_1200_2500","WJets_HT_100_200", "WJets_HT_2500_Inf", "WJets_HT_200_400", "WJets_HT_400_600", "WJets_HT_600_800", "WJets_HT_800_1200"]
files["2017"] += ["ST_tW_antitop", "ST_tchannel_antitop", "ST_tW_top", "ST_tchannel_top", "EWKWMinus2Jets_WToLNu", "EWKWPlus2Jets_WToLNu", "EWKZ2Jets_ZToLL", "EWKZ2Jets_ZToNuNu","WWTo2L2Nu", "WWTo4Q", "WWToLNuQQ", "WZTo2L2Q", "WZTo1L1Nu2Q", "WZTo3LNu", "ZZTo2L2Q", "ZZTo4L", "ZH_HBB_ZLL", "ZH_HTauTau", "ggHTauTau", "VBFHTauTau", "WplusHTauTau", "WminusHTauTau", "WWW", "WWZ", "WZZ", "TTWJetsToLNu", "TTWJetsToQQ", "TTWW"]

files["2017_FC"] += ["DYJets_0j0b", "DYJets_1j0b", "DYJets_1j1b", "DYJets_2j0b", "DYJets_2j1b", "DYJets_2j2b", "DYJets_3j0b", "DYJets_3j1b", "DYJets_3j2b", "DYJets_3j3b", "DYJets_4j0b", "DYJets_4j1b", "DYJets_4j2b", "DYJets_4j3b", "DYJets_4j4b", "GGHHSM", "TTfullyHad", "TTfullyLep", "TTsemiLep", "VBFHHSM", "WJets_HT_0_100", "WJets_HT_100_200", "WJets_HT_1200_2500", "WJets_HT_200_400", "WJets_HT_2500_Inf", "WJets_HT_400_600", "WJets_HT_600_800", "WJets_HT_800_1200"]

files["2017_may"] += ["DYJets_0j0b", "DYJets_1j0b", "DYJets_1j1b", "DYJets_2j0b", "DYJets_2j1b", "DYJets_2j2b", "DYJets_3j0b", "DYJets_3j1b", "DYJets_3j2b", "DYJets_3j3b", "DYJets_4j0b", "DYJets_4j1b", "DYJets_4j2b", "DYJets_4j3b", "DYJets_4j4b", "GGHHSM", "TTfullyHad", "TTfullyLep", "TTsemiLep", "VBFHHSM", "WJets_HT_0_70", "WJets_HT_70_100", "WJets_HT_100_200", "WJets_HT_1200_2500", "WJets_HT_200_400", "WJets_HT_2500_Inf", "WJets_HT_400_600", "WJets_HT_600_800", "WJets_HT_800_1200", "VBF_CV_1_C2V_1_C3_2", "VBF_CV_1_C2V_1_C3_0", "VBF_CV_1_5_C2V_1_C3_1", "VBF_CV_1_C2V_0_C3_2", "VBF_CV_1_C2V_2_C3_1", "GGHHNLO"]

files["2017_vbf"] = ["GGHHSM", "GGHHNLO", 'VBFHHSM', 'VBF_CV_1_C2V_1_C3_0', 'VBF_CV_1_C2V_1_C3_2', 'VBF_CV_1_C2V_2_C3_1', 'VBF_CV_1_5_C2V_1_C3_1', 'VBF_CV_1_C2V_0_C3_2']

  
  
mergingCategories = {"2017": OrderedDict(), "2017_FC": OrderedDict(), "2017_may": OrderedDict(),}
mergingCategories["2017"]["Others"] = ["ST_tW_antitop", "ST_tchannel_antitop", "ST_tW_top", "ST_tchannel_top", "EWKWMinus2Jets_WToLNu", "EWKWPlus2Jets_WToLNu", "EWKZ2Jets_ZToLL", "EWKZ2Jets_ZToNuNu","WWTo2L2Nu", "WWTo4Q", "WWToLNuQQ", "WZTo2L2Q", "WZTo1L1Nu2Q", "WZTo3LNu", "ZZTo2L2Q", "ZZTo4L", "ZH_HBB_ZLL", "ZH_HTauTau", "ggHTauTau", "VBFHTauTau", "WplusHTauTau", "WminusHTauTau", "WWW", "WWZ", "WZZ", "TTWJetsToLNu", "TTWJetsToQQ", "TTWW"] + ["ttHJetToBB", "ttHJetTononBB"]
mergingCategories["2017"]["W+Jets"] = ["WJets_HT_0_100","WJets_HT_1200_2500","WJets_HT_100_200", "WJets_HT_2500_Inf", "WJets_HT_200_400", "WJets_HT_400_600", "WJets_HT_600_800", "WJets_HT_800_1200"]
mergingCategories["2017"]["TT"] = ["TTfullyHad", "TTsemiLep", "TTfullyLep"]
mergingCategories["2017"]["DY+Jets"] = ["DYJets_0j0b_0b", "DYJets_1j0b_0b", "DYJets_1j1b_0b", "DYJets_2j0b_0b", "DYJets_2j1b_0b", "DYJets_2j2b_0b", "DYJets_3j0b_0b", "DYJets_3j1b_0b", "DYJets_3j2b_0b", "DYJets_3j3b_0b", "DYJets_4j0b_0b", "DYJets_4j1b_0b", "DYJets_4j2b_0b", "DYJets_4j3b_0b", "DYJets_4j4b_0b"]
mergingCategories["2017"]["DY+Jets"] += ["DYJets_0j0b_1b", "DYJets_1j0b_1b", "DYJets_1j1b_1b", "DYJets_2j0b_1b", "DYJets_2j1b_1b", "DYJets_2j2b_1b", "DYJets_3j0b_1b", "DYJets_3j1b_1b", "DYJets_3j2b_1b", "DYJets_3j3b_1b", "DYJets_4j0b_1b", "DYJets_4j1b_1b", "DYJets_4j2b_1b", "DYJets_4j3b_1b", "DYJets_4j4b_1b"]
mergingCategories["2017"]["DY+Jets"] += ["DYJets_0j0b_2b", "DYJets_1j0b_2b", "DYJets_1j1b_2b", "DYJets_2j0b_2b", "DYJets_2j1b_2b", "DYJets_2j2b_2b", "DYJets_3j0b_2b", "DYJets_3j1b_2b", "DYJets_3j2b_2b", "DYJets_3j3b_2b", "DYJets_4j0b_2b", "DYJets_4j1b_2b", "DYJets_4j2b_2b", "DYJets_4j3b_2b", "DYJets_4j4b_2b"]

## NEW FROM CHIARA AND FRANCESCO
#mergingCategories["2017_FC"]["W+Jets"] = ["WJets_HT_0_100","WJets_HT_1200_2500","WJets_HT_100_200", "WJets_HT_2500_Inf", "WJets_HT_200_400", "WJets_HT_400_600", "WJets_HT_600_800", "WJets_HT_800_1200"]
mergingCategories["2017_FC"]["TT"] = ["TTfullyHad", "TTsemiLep", "TTfullyLep"]
mergingCategories["2017_FC"]["DY+Jets"]= ["DYJets_0j0b", "DYJets_1j0b", "DYJets_1j1b", "DYJets_2j0b", "DYJets_2j1b", "DYJets_2j2b", "DYJets_3j0b", "DYJets_3j1b", "DYJets_3j2b", "DYJets_3j3b", "DYJets_4j0b", "DYJets_4j1b", "DYJets_4j2b", "DYJets_4j3b", "DYJets_4j4b"]

## From May 2020
#mergingCategories["2017_FC"]["W+Jets"] = ["WJets_HT_0_70","WJets_HT_70_100","WJets_HT_1200_2500","WJets_HT_100_200", "WJets_HT_2500_Inf", "WJets_HT_200_400", "WJets_HT_400_600", "WJets_HT_600_800", "WJets_HT_800_1200"]
mergingCategories["2017_may"]["TT"] = ["TTfullyHad", "TTsemiLep", "TTfullyLep"]
mergingCategories["2017_may"]["DY+Jets"]= ["DYJets_0j0b", "DYJets_1j0b", "DYJets_1j1b", "DYJets_2j0b", "DYJets_2j1b", "DYJets_2j2b", "DYJets_3j0b", "DYJets_3j1b", "DYJets_3j2b", "DYJets_3j3b", "DYJets_4j0b", "DYJets_4j1b", "DYJets_4j2b", "DYJets_4j3b", "DYJets_4j4b"]

mergingCategories["2017_vbf"] = OrderedDict()





dataCategories = {"2017": {}, "2017_FC": {}, "2017_may":{}}
dataCategories["2017"] = {"tauhtauh":['Tau2017B','Tau2017C','Tau2017D','Tau2017E','Tau2017F',],
                          #"mutauh":['SingleMuon2017B','SingleMuon2017C','SingleMuon2017D','SingleMuon2017E','SingleMuon2017F',],
                          #"etauh":['SingleElectron2017B','SingleElectron2017C','SingleElectron2017D','SingleElectron2017E','SingleElectron2017F',],
                         }
dataCategories["2017_FC"] = {"tauhtauh":['Tau2017B','Tau2017C','Tau2017D','Tau2017E','Tau2017F']}
dataCategories["2017_may"] = {"tauhtauh":['Tau2017B','Tau2017C','Tau2017D','Tau2017E','Tau2017F',],
#                              "mutauh":['SingleMuon2017B','SingleMuon2017C','SingleMuon2017D','SingleMuon2017E','SingleMuon2017F',],
#                              "etauh":['SingleElectron2017B','SingleElectron2017C','SingleElectron2017D','SingleElectron2017E','SingleElectron2017F',],
                             }
dataCategories["2017_vbf"] = OrderedDict()

signal = {"2017":OrderedDict(), "2017_FC":OrderedDict(), "2017_may": OrderedDict(),}
signal["2017"]['GGHHSM'] = ['GGHSM_xs']
signal["2017"]['VBFHHSM'] = ['VBF_CV_1_C2V_1_C3_1']
signal["2017"]['VBF'] = ['VBF_CV_1_C2V_1_C3_1', 'VBF_CV_1_C2V_1_C3_0', 'VBF_CV_1_C2V_1_C3_2', 'VBF_CV_1_C2V_2_C3_1', 'VBF_CV_1_5_C2V_1_C3_1', 'VBF_CV_1_C2V_0_C3_2']
  
## NEW FROM CHIARA AND FRANCESCO
signal["2017_FC"]['GGHHSM'] = ['GGHHSM']
signal["2017_FC"]['VBFHHSM'] = ['VBFHHSM']

## From May 2020
signal["2017_may"]['GGHHSM_LO'] = ['GGHHSM']
signal["2017_may"]['GGHHSM_NLO'] = ['GGHHNLO']
signal["2017_may"]['VBFHHSM'] = ['VBFHHSM']
signal["2017_may"]['VBF'] = ['VBFHHSM', 'VBF_CV_1_C2V_1_C3_0', 'VBF_CV_1_C2V_1_C3_2', 'VBF_CV_1_C2V_2_C3_1', 'VBF_CV_1_5_C2V_1_C3_1', 'VBF_CV_1_C2V_0_C3_2']

## From May 2020 - VBF Slides
signal["2017_vbf"] = OrderedDict()
signal["2017_vbf"]['GGHHSM_LO'] = ['GGHHSM']
signal["2017_vbf"]['GGHHSM_NLO'] = ['GGHHNLO']
signal["2017_vbf"]['VBFHHSM'] = ['VBFHHSM']
signal["2017_vbf"]['VBF'] = ['VBFHHSM', 'VBF_CV_1_C2V_1_C3_0', 'VBF_CV_1_C2V_1_C3_2', 'VBF_CV_1_C2V_2_C3_1', 'VBF_CV_1_5_C2V_1_C3_1', 'VBF_CV_1_C2V_0_C3_2']
