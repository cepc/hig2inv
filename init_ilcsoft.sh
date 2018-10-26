export ILCSOFT=/afs/ihep.ac.cn/soft/common/gcc/v01-17-05


#--------------------------------------------------------------------------------
#     MySQL
#--------------------------------------------------------------------------------
export MYSQL_HOME="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/mysql/usr"
export MYSQL_LIBDIR="$MYSQL_HOME/lib64/mysql"
export MYSQL_PATH="$MYSQL_HOME"
export MYSQL="$MYSQL_HOME"
export PATH="$MYSQL_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$MYSQL_HOME/lib64/mysql:$MYSQL_HOME/lib64:$MYSQL_HOME/lib/mysql:$MYSQL_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CERNLIB
#--------------------------------------------------------------------------------
export CERN_ROOT="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/cernlib/pro"
export CERN="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/cernlib"
export CERN_LEVEL="pro"
export CVSCOSRC="$CERN_ROOT/src"
export PATH="$CERN_ROOT/bin:$PATH"


#--------------------------------------------------------------------------------
#     XercesC
#--------------------------------------------------------------------------------
export XercesC_HOME="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/xercesc/3.1.1"
export PATH="$XercesC_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$XercesC_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     Geant4
#--------------------------------------------------------------------------------
export G4INSTALL="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/geant4/9.6.p02"
export G4ENV_INIT="$G4INSTALL/bin/geant4.sh"
export G4SYSTEM="Linux-g++"


#--------------------------------------------------------------------------------
#     QT
#--------------------------------------------------------------------------------
export QTDIR="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/QT/4.7.4"
export QMAKESPEC="$QTDIR/mkspecs/linux-g++"
export PATH="$QTDIR/bin:$PATH"
export LD_LIBRARY_PATH="$QTDIR/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CLHEP
#--------------------------------------------------------------------------------
export CLHEP="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/CLHEP/2.1.3.1"
export CLHEP_BASE_DIR="$CLHEP"
export CLHEP_INCLUDE_DIR="$CLHEP/include"
export PATH="$CLHEP_BASE_DIR/bin:$PATH"
export LD_LIBRARY_PATH="$CLHEP_BASE_DIR/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     ILCUTIL
#--------------------------------------------------------------------------------
export ilcutil="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/ilcutil/v01-01"
export LD_LIBRARY_PATH="$ilcutil/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     LCIO
#--------------------------------------------------------------------------------
export LCIO="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/lcio/v02-04-03"
export PATH="$LCIO/tools:$LCIO/bin:$PATH"
export LD_LIBRARY_PATH="$LCIO/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     ROOT
#--------------------------------------------------------------------------------
export ROOTSYS="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/root/5.34.07"
export PATH="$ROOTSYS/bin:$PATH"
export LD_LIBRARY_PATH="$ROOTSYS/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     GEAR
#--------------------------------------------------------------------------------
export GEAR="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/gear/v01-04"
export PATH="$GEAR/tools:$GEAR/bin:$PATH"
export LD_LIBRARY_PATH="$GEAR/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     KalTest
#--------------------------------------------------------------------------------
export KALTEST="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/KalTest/v01-05-03"
export LD_LIBRARY_PATH="$KALTEST/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     Marlin
#--------------------------------------------------------------------------------
export MARLIN="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/Marlin/v01-05"
export PATH="$MARLIN/bin:$PATH"
export MARLIN_DLL="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/MarlinReco/v01-09/lib/libMarlinReco.so:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/PandoraAnalysis/v00-05/lib/libPandoraAnalysis.so:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/MarlinPandora/v00-11/lib/libMarlinPandora.so:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/LCFIVertex/v00-06-01/lib/libLCFIVertex.so:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/CEDViewer/v01-07-02/lib/libCEDViewer.so:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/Overlay/v00-13/lib/libOverlay.so:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/FastJetClustering/v00-02/lib/libFastJetClustering.so:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/LCTuple/v01-03/lib/libLCTuple.so:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/MarlinKinfit/v00-01-02/lib/libMarlinKinfit.so:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/MarlinTrkProcessors/v01-10/lib/libMarlinTrkProcessors.so:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/Clupatra/v00-10/lib/libClupatra.so:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/LCFIPlus/v00-05-02/lib/libLCFIPlus.so:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/ForwardTracking/v01-07/lib/libForwardTracking.so:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/MarlinTPC/v00-16/lib/libMarlinTPC.so:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/Garlic/v2.10.1/lib/libGarlic.so:/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/Arbor/151125_v3/lib/libRanger.so:$MARLIN_DLL"


#--------------------------------------------------------------------------------
#     LCCD
#--------------------------------------------------------------------------------
export LCCD="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/lccd/v01-03"


#--------------------------------------------------------------------------------
#     CondDBMySQL
#--------------------------------------------------------------------------------
export COND_DB_DEBUGLOG="/dev/stdout"
export CondDBMySQL="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/CondDBMySQL/CondDBMySQL_ILC-0-9-6"
export LD_LIBRARY_PATH="$CondDBMySQL/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     RAIDA
#--------------------------------------------------------------------------------
export RAIDA_HOME="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/RAIDA/v01-06-02"
export PATH="$RAIDA_HOME/bin:$PATH"


#--------------------------------------------------------------------------------
#     GSL
#--------------------------------------------------------------------------------
export GSL_HOME="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/gsl/1.14"
export PATH="$GSL_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$GSL_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CED
#--------------------------------------------------------------------------------
export PATH="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/CED/v01-09-01/bin:$PATH"


#--------------------------------------------------------------------------------
#     Mokka
#--------------------------------------------------------------------------------
export MOKKA="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/Mokka/mokka-08-03_150612"
export PATH="$MOKKA/bin:$PATH"


#--------------------------------------------------------------------------------
#     PandoraPFANew
#--------------------------------------------------------------------------------
export PANDORAPFANEW="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/PandoraPFANew/v00-12"
export LD_LIBRARY_PATH="$PANDORAPFANEW/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CEDViewer
#--------------------------------------------------------------------------------
export PATH="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/CEDViewer/v01-07-02/bin:$PATH"


#--------------------------------------------------------------------------------
#     FastJet
#--------------------------------------------------------------------------------
export FastJet_HOME="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/FastJet/2.4.2"
export PATH="$FastJet_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$FastJet_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     GBL
#--------------------------------------------------------------------------------
export GBL="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/GBL/V01-16-03"
export LD_LIBRARY_PATH="$GBL/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     MarlinTPC
#--------------------------------------------------------------------------------
export MARLINTPC="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/MarlinTPC/v00-16"
export PATH="$MARLINTPC/bin:$PATH"


#--------------------------------------------------------------------------------
#     Druid
#--------------------------------------------------------------------------------
export DRUID="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/Druid/2.4"
export PATH="$DRUID/bin:$PATH"


#--------------------------------------------------------------------------------
#     HepPDT
#--------------------------------------------------------------------------------
export HepPDT_HOME="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/heppdt/3.04.01"
export PATH="$HepPDT_HOME/bin:$PATH"
export LD_LIBRARY_PATH="$HepPDT_HOME/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     GDML
#--------------------------------------------------------------------------------
export GDML="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/gdml/v03-00-02"
export LD_LIBRARY_PATH="$GDML/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     LCDD
#--------------------------------------------------------------------------------
export LCDD="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/lcdd/v03-02-00"
export GDML_SCHEMA_DIR="$LCDD"
export LD_LIBRARY_PATH="$LCDD/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     SLIC
#--------------------------------------------------------------------------------
export SLIC="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/slic/v03-01-03"
export PATH="$SLIC/build/bin:$PATH"
export LD_LIBRARY_PATH="$SLIC/build/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     DD4hep
#--------------------------------------------------------------------------------
export DD4HEP="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/DD4hep/v00-06"
export PATH="$DD4HEP/bin:$PATH"
export LD_LIBRARY_PATH="$DD4HEP/lib:$LD_LIBRARY_PATH"


#--------------------------------------------------------------------------------
#     CMake
#--------------------------------------------------------------------------------
export PATH="/afs/ihep.ac.cn/soft/common/gcc/v01-17-05/CMake/2.8.5/bin:$PATH"

# --- source GEANT4 INIT script ---
test -r ${G4ENV_INIT} && { cd $(dirname ${G4ENV_INIT}) ; . ./$(basename ${G4ENV_INIT}) ; cd $OLDPWD ; }


alias HFcmake='cmake -C /afs/ihep.ac.cn/soft/common/gcc/v01-17-05/ILCSoft.cmake ..'

# ---  Workaraund for OpenGl bug on SL6  ---
export LIBGL_ALWAYS_INDIRECT=1
