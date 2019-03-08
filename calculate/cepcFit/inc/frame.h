#ifndef FRAME_H
#define FRAME_H
#include "CommonHead.h"
#include "CommonFunc.h"

#include "RooWorkspace.h"
#include "RooAbsData.h"
#include "RooRandom.h"
#include "RooSimultaneous.h"

#include "RooStats/ModelConfig.h"
#include "RooStats/FeldmanCousins.h"
#include "RooStats/NeymanConstruction.h"
#include "RooStats/ToyMCSampler.h"
#include "RooStats/PointSetInterval.h"
#include "RooStats/ConfidenceBelt.h"
#include "RooStats/LikelihoodInterval.h"
#include "RooStats/ProfileLikelihoodCalculator.h"
#include "RooStats/ProfileLikelihoodTestStat.h"
#include "RooStats/SamplingDistribution.h"
#include "RooStats/HypoTestResult.h"

#define LARGENUM 1e30

using namespace std;
using namespace RooStats;
using namespace CommonFunc;

const double LB2S = (1.0 - 0.954499736) / 2.;
const double LB1S = (1.0 - 0.682689492) / 2.;
const double B0S  = (1.0) / 2.;
const double UB1S = (1.0 + 0.682689492) / 2.;
const double UB2S = (1.0 + 0.954499736) / 2.;

const double SIG1 =(1-0.682689492)/2;
const double SIG2 =(1-0.954499736104)/2.;
const double SIG3 =(1-0.997300203937)/2.;
const double SIG4 =(1-0.999936657516)/2.;
const double SIG5 =2.867865e-7;
const double SIG6 =SignificanceToPValue(6);

double FindFraction(std::vector<double> dist, double threshold, bool isSorted=true){
  if(!isSorted) sort(dist.begin(),dist.end());
  int total = (int)dist.size();
  int Frac = 0;
  for(int i=0;i< total ;i++){
    if(dist[i]>=threshold) {
      Frac++;
    }
  }
  return (double)Frac/(double)total;
}

double writeSampling(std::string sbFileName, std::string bOnlyFileName, bool isCLsb, bool &flag){

  TFile *fsb=new TFile(sbFileName.c_str(),"read");
  TFile *fbo=new TFile(bOnlyFileName.c_str(),"read");
  TTree *tsb=(TTree *)fsb->Get("sampling");
  TTree *tbo=(TTree *)fbo->Get("sampling");
  
  std::vector<double >* distribution;
  std::vector<double >* weights;
  TBranch* b_distribution;
  TBranch* b_weights;

  vector<double> sum_dist_sb; sum_dist_sb.clear();
  vector<double> sum_wts_sb; sum_wts_sb.clear();
  vector<double> sum_dist_bo; sum_dist_bo.clear();
  vector<double> sum_wts_bo; sum_wts_bo.clear();

  tsb->SetBranchAddress("distribution", &distribution, &b_distribution);
  tsb->SetBranchAddress("weights", &weights, &b_weights);
  
  distribution = 0;
  weights = 0;
  
  int Nsb=tsb->GetEntries();
  // fill the s+b vectors
  for(int ii=0; ii<Nsb; ii++){
    tsb->GetEntry(ii);
    for(UInt_t i=0; i<distribution->size(); i++){
      sum_dist_sb.push_back(distribution->at(i));
      sum_wts_sb.push_back(weights->at(i));
    }
  }

  int tot=sum_dist_sb.size();

  sort(sum_dist_sb.begin(),sum_dist_sb.end()); // sort so that the distribution values are ordered
  
  SamplingDistribution* sam = new SamplingDistribution(
  "Profile Likelihood Ratio", "Profile Likelihood Ratio",
  sum_dist_sb, sum_wts_sb);
  double threshold = sam->InverseCDF(0.95);
  if(isCLsb){
    SafeDelete(tsb);
    SafeDelete(tbo);
    fsb->Close();
    fbo->Close();
    SafeDelete(fsb);
    SafeDelete(fbo);
    return threshold;
  }
  // find the position of the threshold
  int index=0;
  for(UInt_t i=0;i<sum_dist_sb.size();i++)
    if(threshold==sum_dist_sb[i]){index=i;break;}
  
  // Now deal with the background only part
  tbo->SetBranchAddress("distribution", &distribution, &b_distribution);
  tbo->SetBranchAddress("weights", &weights, &b_weights);
  
  distribution = 0;
  weights = 0;
  
  int Nbo = tbo->GetEntries();
  for(int ii=0; ii<Nbo; ii++){
    tbo->GetEntry(ii);
    for(UInt_t i=0; i<distribution->size(); i++){
      sum_dist_bo.push_back(distribution->at(i));
      sum_wts_bo.push_back(weights->at(i));
    }
  }  
  sort(sum_dist_bo.begin(),sum_dist_bo.end());

  double minVal=LARGENUM;
  double minCLs=LARGENUM;
  double minThd=LARGENUM;
  for(int idx=index;idx<tot;idx++){
    threshold=sum_dist_sb[idx];
    double CLsb=FindFraction(sum_dist_sb,threshold,true);
    double CLb =FindFraction(sum_dist_bo,threshold,true);
    double CLs =CLsb/CLb;
/*     printf("index = %d, clsb = %f, clb = %f, cls = %f\n",index, CLsb,CLb,CLs); */
    if(fabs(CLs-0.05)<minVal){
      minVal=fabs(CLs-0.05);
      minCLs=CLs;
      minThd=threshold;
      /* This is a protection. Though by doing this we will lose some precision, it would protect us from the case where the CLs curve has a U-Shape */
      if(minVal<0.001) break;
    }
  }
  cout<<"The best CLs value found is "<<minCLs<<endl;
  if(fabs(minCLs-0.05)>0.02) flag=false;
  else flag=true;
  SafeDelete(tsb);
  SafeDelete(tbo);
  fsb->Close();
  fbo->Close();
  SafeDelete(fsb);
  SafeDelete(fbo);

  return minThd;
}

void smoothen(double m[], double y[], int np, int N) {
  // computes the smoothened values in a new array
  double s[200];

  // First and last N entries are kept unchanged; 
  // rest obtained averaging 2N+1 neighbors
  for (int i=N+1; i<np-N-1; ++i) {
    //if (160<m[i] && m[i]<180) { s[i]=y[i]; continue; }
/*     if (150<m[i] && m[i]<190) { N=1; } else N=2; */
    s[i] = 0;
    for (int j=-N; j<=N; ++j) s[i]+=y[i+j];
    s[i] /= (2*N+1);
  }
  
  // Copy new values back into the external array
  for (int i=N+1; i<np-N-1; ++i) y[i] = s[i];
  
}

pair<double,double> CalculatePValue(RooAbsData* data, RooAbsPdf* pdf, RooArgSet* nullParams, RooArgSet& poi){
  ProfileLikelihoodCalculator plc(*data, *pdf, poi);
  plc.SetNullParameters( *nullParams);
  HypoTestResult* htr = plc.GetHypoTest();
  double sig = htr->Significance();
  pair<double,double> pvalue;
  pvalue.first=sig;
//   sig =  1-0.5*(1 - TMath::Erf(sig/sqrt(2.0)));
  sig =  0.5*(1 - TMath::Erf(sig/sqrt(2.0)));
  pvalue.second=sig;
  return pvalue;
}

double UncapP0(double qmu, double muhat){
//  cout<<endl<<"Test::qmu is "<<qmu<<", minpoi is "<<muhat<<endl;
  if(muhat<0) qmu=-qmu;
  int sign=int(qmu==0 ? 0 : fabs(qmu)/qmu);
  double Z=sign*sqrt(fabs(qmu));
  return 1-ROOT::Math::gaussian_cdf(Z);
}

#endif
