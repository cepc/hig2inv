#!/usr/bin/env bash

# Unset MARLIN_DLL
unset MARLIN_DLL

# Set Variables for MARLIN Execution
shopt -s expand_aliases
#source /besfs/groups/higgs/Software/v01-17-05_slc6/init_ilcsoft.sh
source $PWD/init_ilcsoft.sh

# FastJet
export MARLIN_DLL=$PWD/MarlinFastJet-00-02/lib/libMarlinFastJet.so:$MARLIN_DLL

# Add MARLIN Library Path 
export LD_LIBRARY_PATH=$PWD/lib:$LD_LIBRARY_PATH
export MARLIN_DLL=$PWD/lib/libhig2inv.so:$MARLIN_DLL

# For Condor Job Submit
export PATH=/afs/ihep.ac.cn/soft/common/sysgroup/hep_job/bin:$PATH


# PyROOT 
export PYTHONPATH=$ROOTSYS/lib:$PYTHONPATH
