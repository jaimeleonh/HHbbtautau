import ROOT as r

markerColors = [
    r.kBlue, 
    r.kRed, 
    r.kGreen+3, 
    r.kMagenta,
    r.kBlack,
    r.kOrange, 
    r.kViolet+2
]

markerColorsMerge = {
    "GGHHSM":r.kRed,
    "GGHHSM_LO":r.kBlack,
    "GGHHSM_NLO":r.kBlue,
    "GGHHSM_LO + 2 Jets":r.kRed,
    "GGHHSM_LO + 1 Jet":r.kRed,
    "GGHHSM_LO #leq 2 Jets":r.kRed,
    "GGHHSM_LO + 1,2 Jets":r.kRed,
    #"VBFHHSM":r.kBlue,
    "VBFHHSM":r.kGreen+2, #  NADYA
    "TT":r.kYellow+2, 
    "QCD":r.kOrange-3, 
    "DY+Jets":r.kGreen+2,
    "W+Jets":r.kBlue,
    "Others": r.kRed,

}



markerTypes = [
    20, 
    21, 
    22
]


