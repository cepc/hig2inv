// Author      : Stefan Gadatsch
// Email       : stefan.gadatsch@cern.ch
// Date        : 2016-03-17
// Description : Load models from ROOT file and prepare them for fits

#include "RooRealSumPdf.h"
#include "RooAddPdf.h"
// #include "RooStarMomentMorph.h"
// #include "RooMultiPdf.h"
#include "RooGaussian.h"
#include "RooRealVar.h"

#include "RooStats/HistFactory/FlexibleInterpVar.h"
#include "RooStats/HistFactory/PiecewiseInterpolation.h"

#include "ExtendedModel.h"
#include "utils.h"

using namespace std;
using namespace RooFit;
using namespace RooStats;
using namespace HistFactory;

// _____________________________________________________________________________
// Constructor
ExtendedModel::ExtendedModel( string ModelName, string FileName, string WsName, string ModelConfigName, string DataName, string SnapshotName, bool binnedLikelihood, string TagAsMeasurement, bool FixCache, bool FixMulti, int InterpolationCode )
  :
  TNamed( ModelName.c_str(), ModelName.c_str() ),
  fFileName( FileName ),
  fWsName( WsName ),
  fModelConfigName( ModelConfigName ),
  fDataName( DataName ),
  fSnapshotName( SnapshotName ),
  fBinnedLikelihood( binnedLikelihood ),
  fTagAsMeasurement( TagAsMeasurement ),
  fFixCache( FixCache ),
  fFixMulti( FixMulti ),
  fInterpolationCode( InterpolationCode )
{
  initialise();

  coutP(InputArguments) << "ExtendedModel::ExtendedModel(" << fName <<") created" << endl;
}

// _____________________________________________________________________________
// Destructor
ExtendedModel::~ExtendedModel()
{
  // TODO
}

// _____________________________________________________________________________
// Load all model information from specified file
void ExtendedModel::initialise()
{
  coutP(InputArguments) << "Opening file " << fFileName << endl;
  fFile = new TFile(fFileName.c_str());

  coutP(InputArguments) << "Loading workspace " << fWsName << endl;
  fWorkspace = (RooWorkspace*)(fFile->Get(fWsName.c_str()));
  if (!fWorkspace) {
    coutE(InputArguments) << "Something went wrong when loading the workspace " << fWsName << endl;
    exit(-1);
  }

  // Modify interpolation codes
  if (fInterpolationCode != -1) {
    RooFIter iter = fWorkspace->components().fwdIterator();
    RooAbsArg* arg;
    while((arg = iter.next())) {
      if (arg->IsA() == FlexibleInterpVar::Class()) {
        (static_cast<FlexibleInterpVar*>(arg))->setAllInterpCodes(fInterpolationCode);
        coutP(InputArguments) << arg->GetName() << " FlexibleInterpVar interpolation code set to " << fInterpolationCode << endl;
      } else if (arg->IsA() == PiecewiseInterpolation::Class()) {
        (static_cast<PiecewiseInterpolation*>(arg))->setAllInterpCodes(fInterpolationCode);
        coutP(InputArguments) << arg->GetName() << " PiecewiseInterpolation interpolation code set to " << fInterpolationCode << endl;
      }
    }
  }

  // Fixes for known features
  if (fBinnedLikelihood) {
    coutP(InputArguments) << "Activating binned likelihood evaluation" << endl;
    RooFIter iter = fWorkspace->components().fwdIterator();
    RooAbsArg* arg;
    while ((arg = iter.next())) {
      if (arg->IsA() == RooRealSumPdf::Class()) {
        arg->setAttribute("BinnedLikelihood");
        coutI(InputArguments) << "Activating binned likelihood attribute for " << arg->GetName() << endl;
      }
    }
  }

  if (fTagAsMeasurement != "") {
    coutP(InputArguments) << "Tagging CMS main measurements to reduce memory consumption" << endl;
    RooFIter iter = fWorkspace->components().fwdIterator() ;
    RooAbsArg* arg ;
    while ((arg = iter.next())) {
      if (arg->IsA()==RooAddPdf::Class() && TString(arg->GetName()).BeginsWith(fTagAsMeasurement.c_str())) {
      arg->setAttribute("MAIN_MEASUREMENT") ;
      coutI(InputArguments) << "Component " << arg->GetName() << " is a CMS main measurement";
      }
    }
  }

  // if (fFixCache) {
  //   coutP(InputArguments) << "Fixing cache of early RooStarMomentMorph pdf" << endl;
  //   RooFIter iter = fWorkspace->components().fwdIterator();
  //   RooAbsArg* arg;
  //   while ((arg = iter.next())) {
  //     if (arg->IsA() == RooStarMomentMorph::Class()) {
  //       ((RooStarMomentMorph*)arg)->fixCache();
  //       coutI(InputArguments) << "Fixing cache of " << arg->GetName() << endl;
  //     }
  //   }
  // }
  //
  // if (fFixMulti) {
  //   coutP(InputArguments) << "De-activating level 2 constant term optimization for RooMultiPdf" << endl;
  //   RooFIter iter = fWorkspace->components().fwdIterator();
  //   RooAbsArg* arg;
  //   while ((arg = iter.next())) {
  //     if (arg->IsA() == RooMultiPdf::Class()) {
  //       arg->setAttribute("NOCacheAndTrack");
  //       coutI(InputArguments) << "De-activation of level 2 constant term optimization for " << arg->GetName() << endl;
  //     }
  //   }
  // }

  if (kTRUE) {
    coutP(InputArguments) << "De-activating level 2 constant term optimization for specified pdfs" << endl;
    RooFIter iter = fWorkspace->components().fwdIterator();
    RooAbsArg* arg;
    while ((arg = iter.next())) {
      TString aname(arg->GetName());
      if (arg->InheritsFrom(RooAbsPdf::Class()) && (aname.EndsWith("_mm") || aname.Contains("mumu_atlas"))) {
        arg->setAttribute("NOCacheAndTrack");
        coutI(InputArguments) << "De-activation of level 2 constant term optimization for " << arg->GetName();
      }
    }
  }

  // Continue loading the model
  coutP(InputArguments) << "Loading ModelConfig " << fModelConfigName << endl;
  fModelConfig = (ModelConfig*)(fWorkspace->obj(fModelConfigName.c_str()));
  if (!fModelConfig) {
    coutE(InputArguments) << "Something went wrong when loading the ModelConfig " << fModelConfigName << endl;
    exit(-1);
  }

  coutP(InputArguments) << "Grabbing the pdf from the ModelConfig" << endl;
  fPdf = (RooAbsPdf*)fModelConfig->GetPdf();
  if (!fPdf) {
    coutE(InputArguments) << "Something went wrong when loading the pdf" << endl;
    exit(-1);
  }

  coutP(InputArguments) << "Loading ModelConfig " << fModelConfigName << endl;
  fData = (RooAbsData*)(fWorkspace->data(fDataName.c_str()));
  if (!fData) {
    coutE(InputArguments) << "Something went wrong when loading the data set " << fDataName << endl;
    exit(-1);
  }

  coutP(InputArguments) << "Loading the nuisance parameters" << endl;
  fNuis = (RooArgSet*)fModelConfig->GetNuisanceParameters();
  if (!fNuis) {
    coutE(InputArguments) << "Something went wrong when loading the nuisance parameters" << endl;
    exit(-1);
  }

  coutP(InputArguments) << "Loading the global observables" << endl;
  fGlobs = (RooArgSet*)fModelConfig->GetGlobalObservables();
  if (!fGlobs) {
    coutE(InputArguments) << "Something went wrong when loading the global observables" << endl;
    exit(-1);
  }

  coutP(InputArguments) << "Loading the parameters of interest" << endl;
  fPOIs = (RooArgSet*)fModelConfig->GetParametersOfInterest();
  if (!fPOIs) {
    coutE(InputArguments) << "Something went wrong when loading the parameters of interest" << endl;
    exit(-1);
  }

  coutP(InputArguments) << "Loading the observables" << endl;
  fObs = (RooArgSet*)fModelConfig->GetObservables();
  if (!fObs) {
    coutE(InputArguments) << "Something went wrong when loading the observables" << endl;
    exit(-1);
  }

  if (fSnapshotName != "") {
    coutP(InputArguments) << "Loading snapshots" << endl;
    vector<string> parsedSnapshots = parseString(fSnapshotName, ",");
    for (size_t i_snapshot = 0; i_snapshot < parsedSnapshots.size(); ++i_snapshot) {
      string thisSnapshot = parsedSnapshots[i_snapshot];
      coutI(InputArguments) << "Loading snapshot " << thisSnapshot << endl;
      fWorkspace->loadSnapshot(thisSnapshot.c_str());
    }
  }
}

// _____________________________________________________________________________
// Fix all nuisance parameters
void ExtendedModel::fixNuisanceParameters()
{
  for (RooLinkedListIter it = fNuis->iterator(); RooRealVar* v = dynamic_cast<RooRealVar*>(it.Next());) {
    Double_t value = v->getVal();
    string name = v->GetName();
    coutI(ObjectHandling) << "Fixing nuisance parameter " << name << " at value " << value << endl;
    v->setConstant(1);
  }
}

// _____________________________________________________________________________
// Fix all parameters of interest
void ExtendedModel::fixParametersOfInterest()
{
  for (RooLinkedListIter it = fPOIs->iterator(); RooRealVar* v = dynamic_cast<RooRealVar*>(it.Next());) {
    Double_t value = v->getVal();
    string name = v->GetName();
    coutI(ObjectHandling) << "Fixing parameter of interest " << name << " at value " << value << endl;
    v->setConstant(1);
  }
}

// _____________________________________________________________________________
// Fix a subset of the nuisance parameters at the specified values
void ExtendedModel::fixNuisanceParameters( string fixName )
{
  vector<string> parsed = parseString(fixName, ",");

  for (size_t i = 0; i < parsed.size(); i++) {
     TString thisName = parsed[i].c_str();
     TString thisVal;
     if (thisName.Contains("[")) {
       assert(thisName.Contains("]"));
       TObjArray* thisNameArray = thisName.Tokenize("[");
       thisName = ((TObjString*)thisNameArray->At(0))->GetString();
       thisVal = ((TObjString*)thisNameArray->At(1))->GetString();
       thisVal.ReplaceAll("]","");
     }

     RooRealVar* par = (RooRealVar*)fWorkspace->var(thisName.Data());
     if (!par) {
       coutE(ObjectHandling) << "Nuisance parameter " << thisName.Data() << " does not exist." << endl;
       exit(-1);
     }

     double value = par->getVal();
     if (thisVal.IsFloat()) {
       value = thisVal.Atof();
       par->setVal(value);
     }

     coutI(ObjectHandling) << "Fixing nuisance parameter " << thisName.Data() << " at value " << value << endl;
     par->setConstant(1);
   }

}

// _____________________________________________________________________________
// Fix a subset of the nuisance parameters at the specified values
void ExtendedModel::profileParameters( string profileName )
{
  vector<string> parsed = parseString(profileName, ",");

  for (size_t i = 0; i < parsed.size(); i++) {
    TString thisName = parsed[i];
    TString range;
    TString boundary;
    int sign = 0;

    bool useRange    = kFALSE;
    bool useBoundary = kFALSE;

    // Get ranges
    if (thisName.Contains("[")) {
      assert(thisName.Contains("]"));
      TObjArray* thisNameArray = thisName.Tokenize("[");
      thisName = ((TObjString*)thisNameArray->At(0))->GetString();
      range = ((TObjString*)thisNameArray->At(1))->GetString();
      range.ReplaceAll("]","");
      assert(range.Contains(":"));
      useRange = kTRUE;
    }

    // Get sign
    if (thisName.Contains("+")) {
      thisName.ReplaceAll("+",">0");
    } else if (thisName.Contains("-")) {
      thisName.ReplaceAll("-","<0");
    }

    // Get boundaries
    if (thisName.Contains(">")) {
      TObjArray* thisNameArray = thisName.Tokenize(">");
      thisName = ((TObjString*)thisNameArray->At(0))->GetString();
      boundary = ((TObjString*)thisNameArray->At(1))->GetString();
      sign = +1;
      useBoundary = kTRUE;
    } else if (thisName.Contains("<")) {
      TObjArray* thisNameArray = thisName.Tokenize("<");
      thisName = ((TObjString*)thisNameArray->At(0))->GetString();
      boundary = ((TObjString*)thisNameArray->At(1))->GetString();
      sign = -1;
      useBoundary = kTRUE;
    }

    coutI(ObjectHandling) << "Profiling parameter " << thisName.Data() << endl;
    RooRealVar* thisPoi = (RooRealVar*)fWorkspace->var(thisName);
    if (!thisPoi) {
      coutE(ObjectHandling) << "Parameter " << thisPoi->GetName() << " doesn't exist!" << endl;
      exit(-1);
    }

    if (useRange) {
      double origVal = thisPoi->getVal();
      TObjArray* rangeArray = range.Tokenize(":");
      TString s_lo = ((TObjString*)rangeArray->At(0))->GetString();
      TString s_hi = ((TObjString*)rangeArray->At(1))->GetString();
      double lo = atof(s_lo.Data());
      double hi = atof(s_hi.Data());
      thisPoi->setRange(lo, hi);
      if ((origVal < lo) || (origVal > hi)) {
        double newVal = (hi - lo) / 2;
        thisPoi->setVal(newVal);
        coutI(ObjectHandling) << "Setting value to " << newVal << endl;
      }
    }

    if (useBoundary) {
      double tmpBoundary = atof(boundary.Data());
      double origVal = thisPoi->getVal();
      double forigVal = fabs(thisPoi->getVal());
      bool boundaryIsZero = AlmostEqualUlpsAndAbs(tmpBoundary, 0.0, 0.0001, 4);

      if (sign > 0) {
        thisPoi->setMin(tmpBoundary);
        if (origVal < tmpBoundary) {
          thisPoi->setVal(tmpBoundary);
        }
        if (boundaryIsZero && origVal < 0) {
          thisPoi->setVal(forigVal);
        }
      } else if (sign < 0) {
        thisPoi->setMax(tmpBoundary);
        if (origVal > tmpBoundary) {
          thisPoi->setVal(tmpBoundary);
        }
        if (boundaryIsZero && origVal > 0) {
          thisPoi->setVal(-forigVal);
        }
      }
    }

    thisPoi->setConstant(0);
    coutI(ObjectHandling) << thisName.Data() << " = " << thisPoi->getVal() << " in [" << thisPoi->getMin() << "," << thisPoi->getMax() << "]" << endl;
  }
}

// _____________________________________________________________________________
// Set initial errors of model parameters depending on constraint terms
void ExtendedModel::setInitialErrors()
{
  RooArgSet* AllConstraints = new RooArgSet();

  if (fWorkspace->set(Form("CACHE_CONSTR_OF_PDF_%s_FOR_OBS_%s", fPdf->GetName(), RooNameSet(*fData->get()).content()))) {
    // Retrieve constraints from cache
    const RooArgSet* constr = fWorkspace->set(Form("CACHE_CONSTR_OF_PDF_%s_FOR_OBS_%s", fPdf->GetName(), RooNameSet(*fData->get()).content()));
    AllConstraints->add(*constr);
    delete constr;
  } else {
    // Load information needed to determine attributes from ModelConfig
    RooAbsPdf* tmpPdf = (RooAbsPdf*)fModelConfig->GetPdf();
    RooArgSet* tmpAllNuisanceParameters = (RooArgSet*)fModelConfig->GetNuisanceParameters();
    RooArgSet* tmpAllObservables = (RooArgSet*)fModelConfig->GetObservables();

    // Copies, to keep original sets in place after getAllconstraints call
    RooArgSet tmpAllNuisanceParameters2 = *tmpAllNuisanceParameters;
    RooArgSet tmpAllObservables2 = *tmpAllObservables;
    AllConstraints = tmpPdf->getAllConstraints(tmpAllObservables2, tmpAllNuisanceParameters2, kFALSE);
  }

  // Take care of the case where we have a product of constraint terms
  TIterator* ConstraintItrAll = AllConstraints->createIterator();
  RooAbsArg* nextConstraint;
  RooArgSet* tmpAllConstraints = new RooArgSet(AllConstraints->GetName());
  while ((nextConstraint = (RooAbsArg*)ConstraintItrAll->Next())) {
    if (nextConstraint->IsA() == RooProdPdf::Class()) {
      RooArgSet thisComponents;
      FindUniqueProdComponents((RooProdPdf*)nextConstraint, thisComponents);
      tmpAllConstraints->add(thisComponents);
    } else {
      coutI(ObjectHandling) << "Adding constraint " << nextConstraint->GetName() << endl;
      tmpAllConstraints->add(*nextConstraint);
    }
  }

  for (RooLinkedListIter it = fNuis->iterator(); RooRealVar* nuip = dynamic_cast<RooRealVar*>(it.Next());) {
    coutI(ObjectHandling) << "On nuisance parameter " << nuip->GetName();
    double prefitvariation = 1.0;

    TIterator* ConstraintItr = tmpAllConstraints->createIterator();
    bool foundConstraint = kFALSE;
    bool foundGaussianConstraint = kFALSE;
    while ((nextConstraint = (RooAbsArg*)ConstraintItr->Next()) && !foundConstraint) {
      if (nextConstraint->dependsOn(*nuip)) {
        foundConstraint = kTRUE;

        // Loop over global observables to match nuisance parameter and
        // global observable in case of a constrained nuisance parameter
        TIterator* GlobsItr = fGlobs->createIterator();
        RooRealVar* nextGlobalObservable;
        bool foundGlobalObservable = kFALSE;
        while ((nextGlobalObservable = (RooRealVar*)GlobsItr->Next()) && !foundGlobalObservable) {
          if (nextConstraint->dependsOn(*nextGlobalObservable)) {
            foundGlobalObservable = kTRUE;

            // find constraint width in case of a Gaussian
            if (nextConstraint->IsA() == RooGaussian::Class()) {
              foundGaussianConstraint = kTRUE;
              double oldSigmaVal = 1.0;
              TIterator* ServerItr = nextConstraint->serverIterator();
              RooRealVar* nextServer;
              bool foundSigma = kFALSE;
              while ((nextServer = (RooRealVar*)ServerItr->Next()) && !foundSigma) {
                if (nextServer != nextGlobalObservable && nextServer != nuip) {
                  oldSigmaVal = nextServer->getVal();
                  foundSigma = kTRUE;
                }
              }

              if (AlmostEqualUlpsAndAbs(oldSigmaVal, 1.0, 0.001, 4)) {
                oldSigmaVal = 1.0;
              }

              if (!foundSigma) {
                coutI(ObjectHandling) << "Sigma for pdf " << nextConstraint->GetName() << " not found. Using 1.0." << endl;
              } else {
                coutI(ObjectHandling)  << "Using " << oldSigmaVal << " for sigma of pdf " << nextConstraint->GetName() << endl;
              }

              prefitvariation = oldSigmaVal;
            }
          }
        }
        delete GlobsItr;
      }
    }
    delete ConstraintItr;

    if (foundGaussianConstraint) {
      coutP(ObjectHandling) << "Changing error of " << nuip->GetName() << " from " << nuip->getError() << " to " << prefitvariation << endl;
      nuip->setError(prefitvariation);
      nuip->removeRange();
    }
  }
}
