from collections import OrderedDict

files = {"2017": [], "2017_FC": []}

files["2017"].append("GGHSM_xs")
files["2017"].append("VBF_CV_1_C2V_1_C3_1")
files["2017"] += ["ttHJetToBB", "ttHJetTononBB"]
files["2017"].append("PrivateGluGlu12JetsHHTo2B2Taus2017_SKIM")
files["2017"] += ["TTfullyHad", "TTsemiLep", "TTfullyLep"]

files["2017"] += ["DYJets_0j0b_0b", "DYJets_1j0b_0b", "DYJets_1j1b_0b", "DYJets_2j0b_0b", "DYJets_2j1b_0b", "DYJets_2j2b_0b", "DYJets_3j0b_0b", "DYJets_3j1b_0b", "DYJets_3j2b_0b", "DYJets_3j3b_0b", "DYJets_4j0b_0b", "DYJets_4j1b_0b", "DYJets_4j2b_0b", "DYJets_4j3b_0b", "DYJets_4j4b_0b"]
files["2017"] += ["DYJets_0j0b_1b", "DYJets_1j0b_1b", "DYJets_1j1b_1b", "DYJets_2j0b_1b", "DYJets_2j1b_1b", "DYJets_2j2b_1b", "DYJets_3j0b_1b", "DYJets_3j1b_1b", "DYJets_3j2b_1b", "DYJets_3j3b_1b", "DYJets_4j0b_1b", "DYJets_4j1b_1b", "DYJets_4j2b_1b", "DYJets_4j3b_1b", "DYJets_4j4b_1b"]
files["2017"] += ["DYJets_0j0b_2b", "DYJets_1j0b_2b", "DYJets_1j1b_2b", "DYJets_2j0b_2b", "DYJets_2j1b_2b", "DYJets_2j2b_2b", "DYJets_3j0b_2b", "DYJets_3j1b_2b", "DYJets_3j2b_2b", "DYJets_3j3b_2b", "DYJets_4j0b_2b", "DYJets_4j1b_2b", "DYJets_4j2b_2b", "DYJets_4j3b_2b", "DYJets_4j4b_2b"]
files["2017"] += ["WJets_HT_0_100","WJets_HT_1200_2500","WJets_HT_100_200", "WJets_HT_2500_Inf", "WJets_HT_200_400", "WJets_HT_400_600", "WJets_HT_600_800", "WJets_HT_800_1200"]
files["2017"] += ["ST_tW_antitop", "ST_tchannel_antitop", "ST_tW_top", "ST_tchannel_top", "EWKWMinus2Jets_WToLNu", "EWKWPlus2Jets_WToLNu", "EWKZ2Jets_ZToLL", "EWKZ2Jets_ZToNuNu","WWTo2L2Nu", "WWTo4Q", "WWToLNuQQ", "WZTo2L2Q", "WZTo1L1Nu2Q", "WZTo3LNu", "ZZTo2L2Q", "ZZTo4L", "ZH_HBB_ZLL", "ZH_HTauTau", "ggHTauTau", "VBFHTauTau", "WplusHTauTau", "WminusHTauTau", "WWW", "WWZ", "WZZ", "TTWJetsToLNu", "TTWJetsToQQ", "TTWW"]

files["2017_FC"] += ["DYJets_0j0b", "DYJets_1j0b", "DYJets_1j1b", "DYJets_2j0b", "DYJets_2j1b", "DYJets_2j2b", "DYJets_3j0b", "DYJets_3j1b", "DYJets_3j2b", "DYJets_3j3b", "DYJets_4j0b", "DYJets_4j1b", "DYJets_4j2b", "DYJets_4j3b", "DYJets_4j4b", "GGHHSM", "TTfullyHad", "TTfullyLep", "TTsemiLep", "VBFHHSM", "WJets_HT_0_100", "WJets_HT_100_200", "WJets_HT_1200_2500", "WJets_HT_200_400", "WJets_HT_2500_Inf", "WJets_HT_400_600", "WJets_HT_600_800", "WJets_HT_800_1200"]
  
  
mergingCategories = {"2017": OrderedDict(), "2017_FC": OrderedDict()}
mergingCategories["2017"]["Others"] = ["ST_tW_antitop", "ST_tchannel_antitop", "ST_tW_top", "ST_tchannel_top", "EWKWMinus2Jets_WToLNu", "EWKWPlus2Jets_WToLNu", "EWKZ2Jets_ZToLL", "EWKZ2Jets_ZToNuNu","WWTo2L2Nu", "WWTo4Q", "WWToLNuQQ", "WZTo2L2Q", "WZTo1L1Nu2Q", "WZTo3LNu", "ZZTo2L2Q", "ZZTo4L", "ZH_HBB_ZLL", "ZH_HTauTau", "ggHTauTau", "VBFHTauTau", "WplusHTauTau", "WminusHTauTau", "WWW", "WWZ", "WZZ", "TTWJetsToLNu", "TTWJetsToQQ", "TTWW"] + ["ttHJetToBB", "ttHJetTononBB"]
mergingCategories["2017"]["W+Jets"] = ["WJets_HT_0_100","WJets_HT_1200_2500","WJets_HT_100_200", "WJets_HT_2500_Inf", "WJets_HT_200_400", "WJets_HT_400_600", "WJets_HT_600_800", "WJets_HT_800_1200"]
mergingCategories["2017"]["TT"] = ["TTfullyHad", "TTsemiLep", "TTfullyLep"]
mergingCategories["2017"]["DY+Jets"] = ["DYJets_0j0b_0b", "DYJets_1j0b_0b", "DYJets_1j1b_0b", "DYJets_2j0b_0b", "DYJets_2j1b_0b", "DYJets_2j2b_0b", "DYJets_3j0b_0b", "DYJets_3j1b_0b", "DYJets_3j2b_0b", "DYJets_3j3b_0b", "DYJets_4j0b_0b", "DYJets_4j1b_0b", "DYJets_4j2b_0b", "DYJets_4j3b_0b", "DYJets_4j4b_0b"]
mergingCategories["2017"]["DY+Jets"] += ["DYJets_0j0b_1b", "DYJets_1j0b_1b", "DYJets_1j1b_1b", "DYJets_2j0b_1b", "DYJets_2j1b_1b", "DYJets_2j2b_1b", "DYJets_3j0b_1b", "DYJets_3j1b_1b", "DYJets_3j2b_1b", "DYJets_3j3b_1b", "DYJets_4j0b_1b", "DYJets_4j1b_1b", "DYJets_4j2b_1b", "DYJets_4j3b_1b", "DYJets_4j4b_1b"]
mergingCategories["2017"]["DY+Jets"] += ["DYJets_0j0b_2b", "DYJets_1j0b_2b", "DYJets_1j1b_2b", "DYJets_2j0b_2b", "DYJets_2j1b_2b", "DYJets_2j2b_2b", "DYJets_3j0b_2b", "DYJets_3j1b_2b", "DYJets_3j2b_2b", "DYJets_3j3b_2b", "DYJets_4j0b_2b", "DYJets_4j1b_2b", "DYJets_4j2b_2b", "DYJets_4j3b_2b", "DYJets_4j4b_2b"]
## NEW FROM CHIARA AND FRANCESCO
mergingCategories["2017_FC"]["W+Jets"] = ["WJets_HT_0_100","WJets_HT_1200_2500","WJets_HT_100_200", "WJets_HT_2500_Inf", "WJets_HT_200_400", "WJets_HT_400_600", "WJets_HT_600_800", "WJets_HT_800_1200"]
mergingCategories["2017_FC"]["TT"] = ["TTfullyHad", "TTsemiLep", "TTfullyLep"]
mergingCategories["2017_FC"]["DY+Jets"]= ["DYJets_0j0b", "DYJets_1j0b", "DYJets_1j1b", "DYJets_2j0b", "DYJets_2j1b", "DYJets_2j2b", "DYJets_3j0b", "DYJets_3j1b", "DYJets_3j2b", "DYJets_3j3b", "DYJets_4j0b", "DYJets_4j1b", "DYJets_4j2b", "DYJets_4j3b", "DYJets_4j4b"]



signal = {"2017":OrderedDict(), "2017_FC":OrderedDict()}
signal["2017"]['ggHSM'] = ['GGHSM_xs']
signal["2017"]['VBFSM'] = ['VBF_CV_1_C2V_1_C3_1']
  
## NEW FROM CHIARA AND FRANCESCO
signal["2017_FC"]['ggHHSM'] = ['GGHHSM']
signal["2017_FC"]['VBFHHSM'] = ['VBFHHSM']


