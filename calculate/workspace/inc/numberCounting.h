#include "TROOT.h"  // for gROOT

#include "TFile.h"
#include "TTree.h"
#include "TF1.h"
#include "TString.h"
#include "TCanvas.h"
#include "TSystem.h"

#include "RooWorkspace.h"
#include "RooAbsData.h"
#include "RooRealVar.h"
#include "RooArgSet.h"
#include "RooDataSet.h"
#include "RooAbsReal.h"
#include "RooProdPdf.h"
#include "RooMinuit.h"
#include "RooCategory.h"
#include "RooSimultaneous.h"
#include "RooAbsPdf.h"
#include "RooPlot.h"

#include <RooFormula.h>
#include <RooArgList.h>
#include <RooFormulaVar.h>
#include <RooPolyVar.h>
#include <RooExponential.h>
#include <RooFitResult.h>
#include <RooAddPdf.h>


#include "RooStats/ModelConfig.h"
#include "RooStats/BayesianCalculator.h"
#include "RooStats/ModelConfig.h"
#include "RooStats/BayesianCalculator.h"
#include "RooStats/SequentialProposal.h"
#include "RooStats/MCMCCalculator.h"
#include "RooStats/MCMCInterval.h"
#include "RooStats/MCMCIntervalPlot.h"
#include "RooStats/HistFactory/FlexibleInterpVar.h"

#include <stdio.h>
#include <stdlib.h> // to use system()
#include <fstream>  // to use ifstream
#include <sstream>      // std::ostringstream

using namespace RooFit;
using namespace RooStats;
using namespace std;

