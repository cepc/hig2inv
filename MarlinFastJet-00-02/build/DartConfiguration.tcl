# This file is configured by CMake automatically as DartConfiguration.tcl
# If you choose not to use CMake, this file may be hand configured, by
# filling in the required variables.


# Configuration directories and files
SourceDirectory: /cefs/higgs/tanyuhang/hig2inv/MarlinFastJet-00-02
BuildDirectory: /cefs/higgs/tanyuhang/hig2inv/MarlinFastJet-00-02/build

# Where to place the cost data store
CostDataFile: 

# Site is something like machine.domain, i.e. pragmatic.crd
Site: lxslc603.ihep.ac.cn

# Build name is osname-revision-compiler, i.e. Linux-2.4.2-2smp-c++
BuildName: Linux-c++

# Submission information
IsCDash: 
CDashVersion: 
QueryCDashVersion: 
DropSite: 
DropLocation: 
DropSiteUser: 
DropSitePassword: 
DropSiteMode: 
DropMethod: http
TriggerSite: 
ScpCommand: /afs/ihep.ac.cn/soft/common/gcc/v01-17-05/mysql/usr/bin/scp

# Dashboard start time
NightlyStartTime: 00:00:00 EDT

# Commands for the build/test/submit cycle
ConfigureCommand: "/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/CMake/2.8.5/bin/cmake" "/cefs/higgs/tanyuhang/hig2inv/MarlinFastJet-00-02"
MakeCommand: /afs/ihep.ac.cn/soft/common/gcc/v01-17-05/mysql/usr/bin/gmake -i
DefaultCTestConfigurationType: Release

# CVS options
# Default is "-d -P -A"
CVSCommand: /afs/ihep.ac.cn/soft/common/gcc/v01-17-05/mysql/usr/bin/cvs
CVSUpdateOptions: -d -A -P

# Subversion options
SVNCommand: /afs/ihep.ac.cn/soft/common/gcc/v01-17-05/mysql/usr/bin/svn
SVNUpdateOptions: 

# Git options
GITCommand: /afs/ihep.ac.cn/soft/common/gcc/v01-17-05/mysql/usr/bin/git
GITUpdateOptions: 
GITUpdateCustom: 

# Generic update command
UpdateCommand: 
UpdateOptions: 
UpdateType: 

# Compiler info
Compiler: /afs/ihep.ac.cn/soft/common/gcc/v01-17-05/mysql/usr/bin/c++

# Dynamic analysis and coverage
PurifyCommand: 
ValgrindCommand: 
ValgrindCommandOptions: 
MemoryCheckCommand: /afs/ihep.ac.cn/soft/common/gcc/v01-17-05/mysql/usr/bin/valgrind
MemoryCheckCommandOptions: 
MemoryCheckSuppressionFile: 
CoverageCommand: /afs/ihep.ac.cn/soft/common/gcc/v01-17-05/mysql/usr/bin/gcov

# Cluster commands
SlurmBatchCommand: /afs/ihep.ac.cn/soft/common/gcc/v01-17-05/mysql/usr/bin/sbatch
SlurmRunCommand: /afs/ihep.ac.cn/soft/common/gcc/v01-17-05/mysql/usr/bin/srun

# Testing options
# TimeOut is the amount of time in seconds to wait for processes
# to complete during testing.  After TimeOut seconds, the
# process will be summarily terminated.
# Currently set to 25 minutes
TimeOut: 1500

UseLaunchers: 
CurlOptions: 
# warning, if you add new options here that have to do with submit,
# you have to update cmCTestSubmitCommand.cxx

# For CTest submissions that timeout, these options
# specify behavior for retrying the submission
CTestSubmitRetryDelay: 5
CTestSubmitRetryCount: 3
