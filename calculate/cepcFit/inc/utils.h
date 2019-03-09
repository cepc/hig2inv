#ifndef _UTILS_
#define _UTILS_ 

#include <chrono>

#include "TROOT.h"
#include "TTime.h"
#include "TSystem.h"
#include "TMath.h"
#include "TAxis.h"
#include "TGraphAsymmErrors.h"

#include "RooProdPdf.h"
#include "RooArgSet.h"

#include "log.h"

#include "inc/RooStatsHead.h"
#include "inc/RooFitHead.h"
#include "inc/CommonHead.h"

using namespace std;
using namespace RooFit;
using namespace RooStats;

namespace utils {

  static void collectEverything( ModelConfig *mc, RooArgSet *set ) {
    set->add(*mc->GetNuisanceParameters());
    set->add(*mc->GetGlobalObservables());
    set->add(*mc->GetParametersOfInterest());
  }

  static void setAllConstant( RooArgSet *set, bool flag ) {
    TIterator *iter = set->createIterator();
    RooRealVar *parg = NULL;
    while ( (parg=(RooRealVar*)iter->Next()) ) parg->setConstant(flag);
    SafeDelete(iter);
  }
  
  static void setAllConstant( const RooArgSet *set, bool flag ){
    TIterator *iter = set->createIterator();
    RooRealVar *parg = NULL;
    while ( (parg=(RooRealVar*)iter->Next()) ) parg->setConstant(flag);
    SafeDelete(iter);
  }

}

// _____________________________________________________________________________
// Timer for benchmarks, see
// http://www.answerandquestion.net/questions/12290/c-timer-function-to-provide-time-in-nano-seconds
// for the original code
class MyTimer
{
public:
  MyTimer() : beg_(clock_::now()) {}
  void reset() { beg_ = clock_::now(); }
  double elapsed() const {
    return chrono::duration_cast<second_>
      (clock_::now() - beg_).count(); }

private:
  typedef chrono::high_resolution_clock clock_;
  typedef chrono::duration<double, ratio<1> > second_;
  chrono::time_point<clock_> beg_;
};

// _____________________________________________________________________________
// Compare two floating point numbers, see
// http://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
// for original code
union MyFloat_t {
  MyFloat_t(float num = 0.0f) : f(num) {}
  // Portable extraction of components.
  bool Negative() const { return (i >> 31) != 0; }
  Int_t RawMantissa() const { return i & ((1 << 23) - 1); }
  Int_t RawExponent() const { return (i >> 23) & 0xFF; }

  Int_t i;
  float f;
};

inline bool AlmostEqualUlpsAndAbs(float A, float B, float maxDiff, int maxUlpsDiff) {
  // Check if the numbers are really close -- needed  when comparing numbers
  // near zero.
  float absDiff = fabs(A - B);
  if (absDiff <= maxDiff) return true;

  MyFloat_t uA(A);
  MyFloat_t uB(B);

  // Different signs means they do not match.
  if (uA.Negative() != uB.Negative()) return false;

  // Find the difference in ULPs.
  int ulpsDiff = abs(uA.i - uB.i);
  if (ulpsDiff <= maxUlpsDiff) return true;

  return false;
}

// _____________________________________________________________________________
// Print used resources
// Courtesy of Tim Adye <T.J.Adye@rl.ac.uk>.
inline void PrintResourcesUsed(const TTime& progStart)
{
  ProcInfo_t info;
  if (gSystem->GetProcInfo(&info)<0) return;
  Long_t cput= TMath::CeilNint(info.fCpuUser);
  Long_t wall= Long64_t(gSystem->Now()-progStart+TTime(500))/Long64_t(1000);
  LOG(logINFO) << Form("resources used: cput=%02ld:%02ld:%02ld, mem=%ldkb, vmem=%ldkb, walltime=%02ld:%02ld:%02ld",
                       cput/3600, (cput/60)%60, cput%60,
                       info.fMemResident, info.fMemVirtual,
                       wall/3600, (wall/60)%60, wall%60);
}

// _____________________________________________________________________________
// Split strings according to separator
inline vector<string> parseString(string str, string sep)
{
  vector<string> parsed;
  int pos = 0;
  bool first = true;
  if (str.size() == 0) return parsed;
  if (str.find(sep) == string::npos) {
    parsed.push_back(str);
    return parsed;
  }

  while (true) {
    int newPos = str.find(sep, pos);
    if (str.find(sep, pos) == string::npos) {
      if (!first) parsed.push_back(str.substr(pos, newPos-pos));
      break;
    }

    string sub = str.substr(pos, newPos-pos);
    parsed.push_back(sub);
    pos = newPos+1;
    first = false;
  }

  return parsed;
}

// _____________________________________________________________________________
// Convert vector to array
inline double* getAry(vector<double> numbers) {
  int nrPoints = numbers.size();
  double* ary = new double[nrPoints];
  for (int i=0; i<nrPoints; i++) {
    ary[i] = numbers[i];
  }
  return ary;
}

// _____________________________________________________________________________
// Convert deque to array
inline double* getAry(deque<double> numbers) {
  int nrPoints = numbers.size();
  double* ary = new double[nrPoints];
  for (int i=0; i<nrPoints; i++) {
    ary[i] = numbers[i];
  }
  return ary;
}

// _____________________________________________________________________________
// Split a RooProdPdf into its components
inline void FindUniqueProdComponents( RooProdPdf* Pdf, RooArgSet& Components )
{
  static int counter = 0;
  counter++;

  if (counter > 50) {
    LOG(logERROR) << "FindUniqueProdComponents detected infinite loop. Please check.";
    exit(1);
  }

  RooArgList pdfList = Pdf->pdfList();
  if (pdfList.getSize() == 1) {
    LOG(logINFO) << "FindUniqueProdComponents " << pdfList.at(0)->GetName() << " is fundamental.";
    Components.add(pdfList);
  } else {
    TIterator* pdfItr = pdfList.createIterator();
    RooAbsArg* nextArg;
    while ((nextArg = (RooAbsArg*)pdfItr->Next())) {
      RooProdPdf* Pdf = (RooProdPdf*)nextArg;
      if (string(Pdf->ClassName()) != "RooProdPdf") {
        LOG(logINFO) << "FindUniqueProdComponents " << Pdf->GetName() << " is no RooProdPdf. Adding it.";
        Components.add(*Pdf);
        continue;
      }
      FindUniqueProdComponents(Pdf, Components);
    }
    delete pdfItr;
  }
  counter = 0;
}

// _____________________________________________________________________________
// Return a TGraph with the points of intersection (taken from https://root.cern.ch/phpBB3/viewtopic.php?t=12048)
inline TGraph* findIntersection(TGraph &a, TGraph &b)
{
  TGraph *interPoint = new TGraph();
  int i = 0;

  // Loop over all points in this TGraph
  for(int a_i = 0; a_i < a.GetN()-1; ++a_i) {
    // Loop over all points in the other TGraph
    for(int b_i = 0; b_i < b.GetN()-1; ++b_i) {

      // Get the current point, and the next point for each of the objects
      double x1, y1, x2, y2 = 0;
      double ax1, ay1, ax2, ay2 = 0;
      a.GetPoint(a_i, x1, y1);
      a.GetPoint(a_i+1, x2, y2);
      b.GetPoint(b_i, ax1, ay1);
      b.GetPoint(b_i+1, ax2, ay2);

      // Calculate the intersection between two straight lines, x axis
      double x = (ax1 *(ay2 *(x1-x2)+x2 * y1 - x1 * y2 )+ ax2 * (ay1 * (-x1+x2)- x2 * y1+x1 * y2)) / (-(ay1-ay2) * (x1-x2)+(ax1-ax2)* (y1-y2));

      // Calculate the intersection between two straight lines, y axis
      double y = (ax1 * ay2 * (y1-y2)+ax2 * ay1 * (-y1+y2)+(ay1-ay2) * (x2 * y1-x1 * y2))/(-(ay1-ay2) * (x1-x2)+(ax1-ax2) * (y1-y2));

      // Find the tightest interval along the x-axis defined by the four points
      double xrange_min = max(min(x1, x2), min(ax1, ax2));
      double xrange_max = min(max(x1, x2), max(ax1, ax2));

      if ((x1 == ax1 and y1 == ay1)or (x2 == ax2 and y2 == ay2)) {
        // If points from the two lines overlap, they are trivially intersecting
        interPoint->SetPoint(i, (x1 == ax1 and y1 == ay1) ? x1 : x2, (x1 == ax1 and y1 == ay1) ? y1 : y2);
        i++;
      } else if(x > xrange_min && x < xrange_max) {
        // If the intersection between the two lines is within the tight range, add it to the list of intersections.
        interPoint->SetPoint(i,x, y);
        i++;
      }
    }
  }

  return interPoint;
}

// _____________________________________________________________________________
inline TGraph* makeGraph(string title, int n, double* x_ary, double* y_ary) {
  TGraph* graph = new TGraph(n, x_ary, y_ary);
  graph->SetTitle("");
  graph->GetXaxis()->SetTitle("X");
  graph->GetYaxis()->SetTitle(title.c_str());
  return graph;
}

// _____________________________________________________________________________
inline TGraphAsymmErrors* makeGraphErr(string title, int n, double* x_ary, double* central, double* errlo, double* errhi) {
  TGraphAsymmErrors* graph = new TGraphAsymmErrors(n, x_ary, central, NULL, NULL, errlo, errhi);
  graph->SetTitle("");
  graph->GetXaxis()->SetTitle("X");
  graph->GetYaxis()->SetTitle(title.c_str());
  return graph;
}

// _____________________________________________________________________________
inline TGraphAsymmErrors* makeGraphErr(string title, int n, double* x_ary, double* central, double* cenlo, double* cenhi, double* errlo, double* errhi) {
  TGraphAsymmErrors* graph = new TGraphAsymmErrors(n, x_ary, central, cenlo, cenhi, errlo, errhi);
  graph->SetTitle("");
  graph->GetXaxis()->SetTitle("X");
  graph->GetYaxis()->SetTitle(title.c_str());
  return graph;
}

#endif /* _UTILS_ */
