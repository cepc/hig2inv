#!/usr/bin/env bash 

shopt -s expand_aliases
source /besfs/groups/higgs/Software/v01-17-05_slc6/init_ilcsoft.sh
export PATH=/afs/ihep.ac.cn/soft/common/sysgroup/hep_job/bin:$PATH

# Setup PyROOT 
export PATH=/afs/ihep.ac.cn/bes3/offline/ExternalLib/SLC6/ExternalLib/external/Python/2.7.3/x86_64-slc6-gcc46-opt/bin:$PATH
export PYTHONPATH=/afs/ihep.ac.cn/bes3/offline/ExternalLib/SLC6/ExternalLib/external/Python/2.7.3/x86_64-slc6-gcc46-opt/lib
. /afs/ihep.ac.cn/bes3/offline/ExternalLib/SLC6/ExternalLib/external/ROOT/5.34.09/x86_64-slc6-gcc46-opt/root/bin/thisroot.sh 
export LD_LIBRARY_PATH=/afs/ihep.ac.cn/bes3/offline/ExternalLib/SLC6/contrib/gcc/4.6.3/x86_64-slc6/lib64:$PYTHONPATH:$LD_LIBRARY_PATH
