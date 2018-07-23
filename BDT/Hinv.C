#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#endif

void Hinv( TString myMethodList = "" )
{
	// This loads the library
	TMVA::Tools::Instance();
	
	// to get access to the GUI and all tmva macros
	TString tmva_dir(TString(gRootDir) + "/tmva");
	if(gSystem->Getenv("TMVASYS")) tmva_dir = TString(gSystem->Getenv("TMVASYS"));
	gROOT->SetMacroPath(tmva_dir + "/test/:" + gROOT->GetMacroPath() );
	gROOT->ProcessLine(".L TMVAGui.C");
	
	// Default MVA methods to be trained + tested
	std::map<std::string,int> Use;
	
	//Boosted Decision Trees
	Use["BDTG"]            = 1; // uses Gradient Boost
	
	std::cout << std::endl;
	std::cout << "==> Start TMVAClassification" << std::endl;

	// Select methods (don't look at this code - not of interest)
	if (myMethodList != "") {
		for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;
		std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
		for (UInt_t i=0; i<mlist.size(); i++) {
			std::string regMethod(mlist[i]);
			
			if (Use.find(regMethod) == Use.end()) {
				std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
				for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
				std::cout << std::endl;
				return;
			}
			Use[regMethod] = 1;
		}
	}

	TString signame="signal_e2e2h";
	TString bkgname[1]="bkg_e2e2h";

	for (Int_t i=0;i<1;i++) {

		//Create a ROOT output file where TMVA will store ntuples, histograms, etc.
		TString outfileName( "../BDT_output/"+bkgname[i]+".root" );
		TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
		
		TMVA::Factory *factory = new TMVA::Factory( bkgname[i], outputFile,"!V:!Silent:Color:AnalysisType=Classification" );
		factory->AddVariable( "m_pt_photon", "m_pt_photon", "", 'F' );
		factory->AddVariable( "m_pt_dilepton", "m_pt_dilepton", "", 'F' );
		factory->AddVariable( "m_m_visible", "m_m_visible", "", 'F' );
		factory->AddVariable( "m_m_recoil", "m_m_recoil", "", 'F' );
		factory->AddVariable( "m_phi_dilepton_1", "m_phi_dilepton_1", "", 'F' );
		factory->AddVariable( "m_phi_dilepton_2", "m_phi_dilepton_2", "", 'F' );
		factory->AddVariable( "m_cos_miss", "m_cos_miss", "", 'F' );
		factory->AddVariable( "m_cos_Z", "m_cos_Z", "", 'F' );
		factory->AddVariable( "m_angle_dilepton", "m_angle_dilepton", "", 'F' );
		factory->AddVariable( "m_delta_pt", "m_delta_pt", "", 'F' );
		factory->AddVariable( "m_energy_neutrino", "m_energy_neutrino", "", 'F' );
		factory->AddVariable( "m_energy_visible", "m_energy_visible", "", 'F' );

		TString sigfile="../sel/"+signame+".root";
		TString bkgfile="../sel/"+bkgname[i]+".root";
		TFile *inputS = TFile::Open(sigfile);
		TFile *inputB = TFile::Open(bkgfile);
		
		//Register the training and test trees
		TTree *signal = (TTree*)inputS->Get("MCPart");
		TTree *background = (TTree*)inputB->Get("MCPart"); 
		
		// global event weights per tree (see below for setting event-wise weights)
		Double_t signaltestWeight     = 1.0;
		Double_t backgroundtestWeight = 1.0;
		Double_t signaltrainWeight     = 1.0;
		Double_t backgroundtrainWeight = 1.0;
		
		factory->AddSignalTree( signal, signaltrainWeight );
		factory->AddBackgroundTree( background, backgroundtestWeight );
		
		// Apply additional cuts on the signal and background samples (can be different)
		TCut mycuts = "m_n_gamma<=1"; 
		TCut mycutb = "m_n_gamma<=1"; 
		
		// Tell the factory how to use the training and testing events
		factory->PrepareTrainingAndTestTree( mycuts, mycutb, "" );
		
		//-----Book MVA methods
		
		// Boosted Decision Trees with adaptive boosting
		if (Use["BDTG"]) factory->BookMethod( TMVA::Types::kBDT, "BDTG","!H:!V:NTrees=800:BoostType=Grad:Shrinkage=0.30:UseBaggedGrad:GradBaggingFraction=0.6:SeparationType=GiniIndex:nCuts=20:PruneMethod=CostComplexity:PruneStrength=50:NNodesMax=3" );
		
		//Train MVAs using the set of training events
		factory->TrainAllMethods();
		
		//Evaluate all MVAs using the set of test events
		factory->TestAllMethods();
		
		//Evaluate and compare performance of all configured MVAs
		factory->EvaluateAllMethods();
		
		//Save the output
		outputFile->Close();
		
		std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
		std::cout << "==> TMVAClassification is done!" << std::endl;
		
		delete factory;
		
		if (!gROOT->IsBatch()) TMVAGui( outfileName );
	}
}
