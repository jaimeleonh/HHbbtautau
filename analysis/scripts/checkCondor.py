import os, sys

import argparse
parser = argparse.ArgumentParser(description='Options')
parser.add_argument('-d','--directory', dest='userCopyPath', default = '')
options = parser.parse_args()


class bcolors:
    black     = '\033[1;30m\033[90m'
    red       = '\033[1;31m\033[91m'
    green     = '\033[1;32m\033[92m'
    yellow    = '\033[1;33m\033[93m'
    blue      = '\033[1;34m\033[94m'
    purple    = '\033[1;35m\033[95m'
    cyan      = '\033[1;36m\033[96m'
    white     = '\033[1;37m\033[97m'
                    
    bold      = '\033[1m' 
    underline = '\033[4m' 

    reset     = '\033[0m' 




if options.userCopyPath == '': 
  print "ERROR: Introduce directory to check completeness"
  sys.exit()

else : 
  if not os.path.isdir(options.userCopyPath) :
    print "ERROR: Introduced directory is not valid"
    sys.exit()

  else : 
    filelist = os.listdir(options.userCopyPath)
    for fil in filelist :
      if not fil[-4:] == '.log' : continue 
      else : 
        inFile = options.userCopyPath + "/" + fil[0:-4]+'.0.out'
        if not os.path.isfile( inFile ) : print bcolors.red + "Job in cluster " +  fil[0:-4] + " not processed yet" + bcolors.reset
        else : 
          found = False
          with open( inFile  ) as a : 
            for line in a : 
              if "Finished" in line : 
                found = True 
                break
          if not found : print bcolors.red + "Job in cluster " + fil[0:-4] + " not processed yet" + bcolors.reset
          else : print bcolors.green + "Job in cluster " + fil[0:-4] + " completed" + bcolors.reset


