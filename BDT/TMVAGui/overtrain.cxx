void NormalizeHists( TH1* sig, TH1* bkg );
void overtrain(int NTrees=1000, int MaxDepth=3)
{
//          gROOT->LoadMacro("/workfs/atlas/zhangyu/atlasstyle/trunk/AtlasStyle.C");
//          SetAtlasStyle();
   gStyle->SetOptStat(0);
   ofstream out;
   out.open("overtrain.log",ios::out|ios::app);
   //gR:OT->LoadMacro("/workfs/atlas/zhangyu/atlasstyle/trunk/AtlasStyle.C");
   //SetAtlasStyle();
   TFile* file;
//   for(int NTrees=100;NTrees<2100;NTrees=Ntrees+100)
//     for(int MaxDepth=2;MaxDepth<5;MaxDepth++)
       {
   file = TFile::Open(Form("out/ntuple/TMVA_VBF_vs_ggH_pTCut30_presel1_Nvar6_NTrees%d_MaxDepth%d_pTHjj0_20161111Dphi.root",NTrees, MaxDepth));  

   // search for the right histograms in full list of keys
   TIter next(file->GetListOfKeys());
   TKey *key(0);   
   while ((key = (TKey*)next())) {

      if (!TString(key->GetName()).BeginsWith("Method_")) continue;
      if (!gROOT->GetClass(key->GetClassName())->InheritsFrom("TDirectory")) continue;

      TDirectory* mDir = (TDirectory*)key->ReadObj();

      TIter keyIt(mDir->GetListOfKeys());
      TKey *titkey;
      while ((titkey = (TKey*)keyIt())) {

         if (!gROOT->GetClass(titkey->GetClassName())->InheritsFrom("TDirectory")) continue;

         TDirectory *titDir = (TDirectory *)titkey->ReadObj();

         TString hname = "MVA_BDTG_VBF_vs_yy";
         TH1* sig = dynamic_cast<TH1*>(titDir->Get( hname + "_S" ));
         TH1* bgd = dynamic_cast<TH1*>(titDir->Get( hname + "_B" ));

         // normalise both signal and background
         NormalizeHists( sig, bgd );

         // if overtraining check, load additional histograms
         TH1* sigOv = 0;
         TH1* bgdOv = 0;

         TString ovname = hname += "_Train";
         sigOv = dynamic_cast<TH1*>(titDir->Get( ovname + "_S" ));
         bgdOv = dynamic_cast<TH1*>(titDir->Get( ovname + "_B" ));
   
         // normalise both signal and background
         NormalizeHists( sigOv, bgdOv );

         // perform K-S test
         cout << "--- Perform Kolmogorov-Smirnov tests" << endl;
         Double_t kolS = sig->KolmogorovTest( sigOv );
         Double_t kolB = bgd->KolmogorovTest( bgdOv );
         TCanvas* c1=new TCanvas("c1","c1",0,0,800,600);
         sigOv->SetLineColor(kRed);
         sigOv->SetMarkerColor(kRed);
         sigOv->GetYaxis()->SetRangeUser(0,1.5*bgdOv->GetMaximum());
         sigOv->Draw("EP");
         bgdOv->SetLineColor(kBlue);
         bgdOv->SetMarkerColor(kBlue);
         bgdOv->Draw("EP same");
         sig->SetLineColor(kRed);
         sig->SetFillColor(kRed);
         sig->SetFillStyle(3004);
         sig->Draw("HIST same");
         bgd->SetLineColor(kBlue);
         bgd->SetFillColor(kBlue);
         bgd->SetFillStyle(3004);
         bgd->Draw("HIST same");
         c1->SaveAs(Form("overtrain_%d_%d.png",NTrees, MaxDepth));
         out<<"NTrees : "<<NTrees<<", MaxDepth : "<<MaxDepth<<endl;
         out << "--- Goodness of signal (background) consistency: " << kolS << " (" << kolB << ")" << endl;
      }
      cout << "";
      file->Close();
      
      
   }
   }
}

void NormalizeHists( TH1* sig, TH1* bkg )
{
   if (sig->GetSumw2N() == 0) sig->Sumw2();
   if (bkg && bkg->GetSumw2N() == 0) bkg->Sumw2();

   if(sig->GetSumOfWeights()!=0) {
      Float_t dx = (sig->GetXaxis()->GetXmax() - sig->GetXaxis()->GetXmin())/sig->GetNbinsX();
      sig->Scale( 1.0/sig->GetSumOfWeights()/dx );
   }
   if (bkg != 0 && bkg->GetSumOfWeights()!=0) {
      Float_t dx = (bkg->GetXaxis()->GetXmax() - bkg->GetXaxis()->GetXmin())/bkg->GetNbinsX();
      bkg->Scale( 1.0/bkg->GetSumOfWeights()/dx );
   }
//   bkg->Scale(1/bkg->Integral());
//   sig->Scale(1/sig->Integral());
   cout<<"aaaaaaaaaaaaaaaaaaaaaaaa"<<endl;
}

