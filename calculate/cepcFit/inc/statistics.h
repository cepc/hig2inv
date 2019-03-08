#ifndef STATISTICS_H
#define STATISTICS_H
#include "CommonHead.h"
#include "CommonFunc.h"
#include "RooFitHead.h"
#include "RooStatsHead.h"

using namespace std;
using namespace RooStats;
using namespace RooFit;
using namespace CommonFunc;

const double LB2S = SignificanceToPValue(2);
const double LB1S = SignificanceToPValue(1);
const double B0S  = SignificanceToPValue(0);;
const double UB1S = SignificanceToPValue(-1);
const double UB2S = SignificanceToPValue(-2);

const double SIG1 =SignificanceToPValue(1);
const double SIG2 =SignificanceToPValue(2);
const double SIG3 =SignificanceToPValue(3);
const double SIG4 =SignificanceToPValue(4);
const double SIG5 =SignificanceToPValue(5);
const double SIG6 =SignificanceToPValue(6);
const double SIG7 =SignificanceToPValue(7);

class statistics : public TObject{
public:
  //other configuration
  string defaultMinimizer;
  int defaultPrintLevel;
  int defaultStrategy;
  bool killBelowFatal;
  bool doBlind;
  bool conditionalExpected;
  bool doTilde;
  bool doExp;
  bool doObs;
  double precision;
  bool verbose;
  bool usePredictiveFit;
  bool extrapolateSigma;
  int maxRetries;
  TRandom3 *fRandom;
public:
  statistics();
  ~statistics();
  static void setDefaultMinimizer(string minimizer){ROOT::Math::MinimizerOptions::SetDefaultMinimizer(minimizer.c_str());}
  static void setDefaultPrintLevel(int printlevel){ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(printlevel);}
  static void setDefaultStrategy(int strategy){ROOT::Math::MinimizerOptions::SetDefaultStrategy(strategy);}
  static RooNLLVar* createNLL(RooAbsData* _data, ModelConfig* _mc);
  static RooFitResult* minimize(RooAbsReal* fcn, TString option="", RooArgSet *minosVars=NULL, bool m_save=true);
  static RooFitResult* minimize(RooNLLVar* nll, TString option="", RooArgSet *minosVars=NULL);
  static void constSet(RooArgSet* set, bool flag=true, RooArgSet* snapshot=NULL);
  static void scaleSet(RooArgSet* set, double f, bool rerange=false);
  static void setvalSet(RooArgSet* set, double value);
  static void rerangeSet(RooArgSet* set, double min, double max);
  static void printSet(RooArgSet* set);
  static void recoverSet(RooArgSet* set, RooArgSet* snapshot);
  static void duplicateSet(RooWorkspace *w, RooArgSet* set, TString setname);
  static void retrieveSet(RooWorkspace* w, RooArgSet* set, RooArgSet* snapshot);
  void randomizeSet(RooArgSet* set, int seed, bool protection=false);
  static void randomizeSet(RooAbsPdf* pdf, RooArgSet* globs, int seed);
  static RooDataSet* histToDataSet(TH1*, RooRealVar*, RooRealVar*);
  static RooDataSet* unbinnedToBinned(RooDataSet*, RooRealVar*, RooRealVar*);
  static double pvalueError(double pvalue, int ntoy);
  static double pvalueFromToy(vector<double> teststat, double thresold);
  static map<string,double> expFromToy(vector<double> teststat);
  static TH1* calcChi2(TH1*, TH1*);
  static TH1* calcLikelihd(TH1*, TH1*);
  static double significance(double, double);
  static void plotData(RooSimultaneous* m_pdf, RooDataSet* m_data, TString outputDir);
  static TH1D* plotToy(vector<double> teststat, TString histname, int nbin, double xmin, double xmax, TString xTitle, Color_t color, double width);
  static void copyDataSet(RooDataSet* datadebit,RooRealVar* obsdebit, RooDataSet* datacredit, RooRealVar* obscredit, RooRealVar* wt, double scale=1, bool verbose=false);
  static double countDataSet(RooDataSet* datadebit, RooSimultaneous *pdf, double xmin, double xmax, bool verbose=false);
  static void copyPdfParams(RooAbsPdf *pdfdebit, RooDataSet* datadebit, RooAbsPdf *pdfcredit, RooDataSet* datacredit);
  static void setVal(RooRealVar *x, double value, bool fix=false);
  static void addDataSet(RooDataSet *data, RooDataSet *data_add, RooRealVar* x, RooRealVar* w);
  ClassDef(statistics,1);
};

#endif
