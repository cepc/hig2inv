#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

//#if not defined(__CINT__) || defined(__MAKECINT__)
//#include "TMVA/Tools.h"
//#include "TMVA/Reader.h"
//#include "TMVA/MethodCuts.h"
//#endif

void mm_ntuple(TString a,TString b);
void qz4v()
{

  // mm_ntuple("bkgzqq.root",  "bkg.root");
  // mm_ntuple("sm.root",   "bkg.root");
  mm_ntuple("qqH_inv.root",   "qz4v_sig.root");
  mm_ntuple("total_bkg.root", "qz4v_bkg.root");
  // mm_ntuple("sig30c1.root",   "3c1.root");
}

void mm_ntuple(TString a,TString b)
{

  TFile *f       = new TFile(a);
  TFile *target  = new TFile(b,"RECREATE");
  TTree *data = (TTree *)f->Get("tree");

//   Float_t      RecoMass,TauTauM;
//   Double_t     recmass,
//   Double_t VisMass,  MisMass;
   Float_t  VisMassf, MisMassf;
   Float_t      weight;

//  Int_t   MCtau=0; 
//  Int_t   Tau,nTauP,nTauM;
  weight=1;

//  Float_t g1CosPolar,g2CosPolar, g1E, g2E, g1rcCos, g2rcCos, ggE, ggM, rcM, g1PTrans, g2PTrans, ggPTrans, rcCosPolar, g1g2cos;
//  Float_t LD0, LZ0, NLD0, NLZ0;

//    data->SetBranchAddress("ggM",          &ggM); // For recoil M, recoilM is MCtruth.
//   data->SetBranchAddress("m_m_recoil",      &MisMassf);
//   data->SetBranchAddress("m_m_dimu",        &VisMassf);
   data->SetBranchAddress("dijet_rec_m",      &MisMassf);
   data->SetBranchAddress("dijet_m",        &VisMassf);

  Int_t nentries = data->GetEntries();



  TTree *output=new TTree("HiggsTree","HiggsTree");
  output->Branch("Mass_invar"    ,&MisMassf,         "Mass_invar/F");
  output->Branch("Mass_Z"        ,&VisMassf,         "Mass_vis/F");
  output->Branch("weight"        ,&weight,           "weight/F");
//   output->Branch("g1PTrans"      ,&g1PTrans,    "g1PTrans/F");
//   output->Branch("g2PTrans"      ,&g2PTrans,    "g2PTrans/F");
//   output->Branch("ggPTrans"      ,&ggPTrans,    "ggPTrans/F");
//   output->Branch("rcCosPolar"    ,&rcCosPolar,  "rcCosPolar/F");
//   output->Branch("g1g2Cos"       ,&g1g2cos,     "g1g2Cos/F");
double sum=0;
 
  for (Long64_t ievt=0; ievt<nentries;ievt++)
 {
     data->GetEntry(ievt);
//   if (
//       abs(g1CosPolar) < 0.99 && abs(g2CosPolar) < 0.99 && g1E>25 && g2E>25 
//    && ((g1CosPolar+1)*(g2CosPolar-1) < -0.07 && (g1CosPolar-1)*(g2CosPolar+1) < -0.07)&&(-0.9 < (g1CosPolar+g2CosPolar) && (g1CosPolar+g2CosPolar) < 0.9)
//    && g1rcCos > -0.95
//    && g2rcCos < 0.70
//    && ggE < 0.48*ggM+83
//    && 0.74*ggM+41<ggE
//    && ggM>113 && ggM<150  
//    )
//   if (MisMassf>120 && MisMassf<130 && VisMassf>89 && VisMassf<94)
//   {
//     //   VisMassf=(Float_t)VisMass;
//     //   MisMassf=(Float_t)MisMass;
//     //  cout<<"Reco:"<<RecoMass<<endl;
     if (b.Contains("s")) weight=0.00212;
    // if (b.Contains("s")) weight=1; 
     if (b.Contains("b")) weight=1;
     sum+=weight;
//     //  if (b.Contains("zh")) weight=6587/2279.;
//     //  decay=HDecay[0];
//     //  cout<<"decay:"<<decay<<endl;
//     if (b.Contains("3"))  weight=0.02875;
//     if (b.Contains("5"))  weight=0.0023;
    // if (b.Contains("fast"))  weight*=0.925;

     output->Fill();
  }

 cout<<a<<"->begin:"<<nentries<<endl;
 cout<<"after:"<<output->GetEntries()<<endl;
  cout<<"sum weight:"<<sum<<endl;
 output->Write("",TObject::kOverwrite);
 target->Close();
 f->Close();


}
