import sys, os
import time
import ROOT as r
from ROOT import gSystem
r.gROOT.SetBatch(True)
from subprocess import call
from samples import samples

import argparse
parser = argparse.ArgumentParser(description='Plotter options')
parser.add_argument('-n','--ntuples', action='store_true', default = False)
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

path = '/eos/home-c/camendol/SKIMS_Legacy2018/SKIMS_30Jan2020/'

files = []
#files.append("SKIM_ZZ")
files.append( samples[0] )

for fil in files : 
  if my_namespace.ntuples == True :
    print ('Obtaining plot ntuples for ' + fil)
    time.sleep(2) 
    analysis = analysisCode(path + fil, fil + '.root')
    analysis.Loop()


