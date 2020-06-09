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
    missingJobs = 0
    failedJobs = 0
    totalJobs = 0
    crashedJobs = 0
    for fil in filelist :
      if not fil[-4:] == '.log' : continue 
      else :
        totalJobs+=1
        filler = "{}/filler_{}.sh".format(options.userCopyPath, totalJobs-1)
        sample = ""
        if os.path.isfile(filler):
            with open(os.path.expandvars(filler)) as fillerFile:
                lines = fillerFile.readlines()
                sample = lines[-1].split(" ")[-4]
        inFile = options.userCopyPath + "/" + fil[0:-4]+'.0.out'
        found = False
        if os.path.isfile( inFile ) : 
          with open( inFile  ) as a : 
            for line in a : 
              if "Finished" in line : 
                found = True 
                break
        if found : 
          print bcolors.green + "Job " + str(totalJobs-1) + " in cluster " + fil[0:-4] + " completed (" + sample + ")" + bcolors.reset
          continue

        failed = False
        errorFile = options.userCopyPath + "/" + fil[0:-4]+'.0.error'
        if os.path.isfile( errorFile ) : 
          with open( errorFile  ) as a : 
            for line in a : 
              if "Break" in line : 
                print bcolors.yellow + "Crashed job " + str(totalJobs-1) +" in cluster " +  fil[0:-4] + "(" + sample + ")" + bcolors.reset
                crashedJobs += 1
                failed = True 
                break
         
        if failed: continue       
        
        with open (  options.userCopyPath + '/' + fil  ) as b : 
          for lin in b :
            if "SYSTEM_PERIODIC_REMOVE" in lin : 
              print bcolors.purple + "Failed job " + str(totalJobs-1) +" in cluster " +  fil[0:-4] + ". Finished w/o processing (" + sample + ")" + bcolors.reset
              failedJobs += 1
              failed = True
              break 
        if not failed :         
          print bcolors.red + "Job " + str(totalJobs-1) + " in cluster " + fil[0:-4] + " not processed yet (" + sample + ")" + bcolors.reset
          missingJobs += 1


    print "\n", "*********************** SUMMARY **********************", "\n"
    print bcolors.red + str(missingJobs) + " missing job" + (missingJobs!=1)*"s" + bcolors.reset
    print bcolors.purple + str(failedJobs) + " failed job" + (failedJobs!=1)*"s" + bcolors.reset
    print bcolors.yellow + str(crashedJobs) + " crashed job" + (crashedJobs!=1)*"s" + bcolors.reset
    print bcolors.green + str(totalJobs-missingJobs-failedJobs) + " succeeded job" + (totalJobs-missingJobs-failedJobs!=1)*"s" + bcolors.reset,'\n'

    print "******************************************************", "\n"

