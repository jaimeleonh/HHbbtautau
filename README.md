# Plotting tools for HH to bbtautau

## Installation
```
cmsrel CMSSW_10_6_5_patch1
cd CMSSW_10_6_5_patch1/src/
cmsenv
git clone https://github.com/jaimeleonh/HHbbtautau.git
cd analysis
make
make exe
source scripts/setup.exe
```

## Running the ntuple production

``` python scripts/run.py -n -p``` to run locally. 
``` python scripts/run.py -rc -p``` to run in HTCondor in lxplus. 

In both cases, you need to modify by hand the samples you want to process and the folder you would like to use.

## Running the plot production 

``` python scripts/run.py ``` builds and combines the plots for the variables you introduce by hand. 
``` python scripts/run.py -m ``` merges the different samples in their categories. 
In both of the previous cases, the plots' integral is normalized to 1. 

``` python scripts/run.py -dmc ``` plots the merged data sampleas and builds a THStack with the merged background samples normalized to the data. 

In the three cases, add the flag ```-c``` to copy the plots produced to the default eoswww or an additional ```-d folder``` to specify the folder. 



