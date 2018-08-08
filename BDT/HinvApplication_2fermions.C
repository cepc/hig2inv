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
#include "TMVAGui/TMVAGui.C"
#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#endif

using namespace TMVA;

void HinvApplication_2fermions( TString myMethodList = "" )
{
#ifdef __CINT__
	gROOT->ProcessLine( ".O0" ); // turn off optimization in CINT
#endif
    
	//---------------------------------------------------------------
	
	// This loads the library
	TMVA::Tools::Instance();
	
	// Default MVA methods to be trained + tested
	std::map<std::string,int> Use;
	
	// --- Boosted Decision Trees
	Use["BDTG"]             = 1; // uses Adaptive Boost
	//
	
	std::cout << std::endl;
	std::cout << "==> Start TMVAClassificationApplication" << std::endl;
	
	// Select methods (don't look at this code - not of interest)
	if (myMethodList != "") {
		for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;
		
		std::vector<TString> mlist = gTools().SplitString( myMethodList, ',' );
		for (UInt_t i=0; i<mlist.size(); i++) {
			std::string regMethod(mlist[i]);
			
			if (Use.find(regMethod) == Use.end()) {
				std::cout << "Method \"" << regMethod<< "\" not known in TMVA under this name. Choose among the following:" << std::endl;
				for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
					std::cout << it->first << " ";
				}
				std::cout << std::endl;
				return;
			}
			Use[regMethod] = 1;
		}
	}
	
	// --------------------------------------------------------------------------------------------------
	
	Float_t cut_BDT=0.6;

	TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );
	
	// Create a set of variables and declare them to the reader
	Float_t f_m_pt_photon,f_m_pt_dilepton,f_m_m_visible,f_m_m_recoil,f_m_phi_dilepton_1,f_m_phi_dilepton_2,f_m_cos_miss,f_m_cos_Z,f_m_angle_dilepton,f_m_delta_pt,f_m_energy_neutrino,f_m_energy_visible;
	Float_t f_m_pt_leptonm,f_m_pt_leptonp,f_m_pz_dilepton,f_m_pz_leptonm,f_m_pz_leptonp,f_m_cos_theta_dilepton;
	
	//reader->AddVariable("m_pt_photon",&f_m_pt_photon);
	reader->AddVariable("m_pt_dilepton",&f_m_pt_dilepton);
	reader->AddVariable("m_pt_leptonm",&f_m_pt_leptonm);
	reader->AddVariable("m_pt_leptonp",&f_m_pt_leptonp);
	reader->AddVariable("m_pz_leptonp",&f_m_pz_leptonp);
	//reader->AddVariable("m_m_visible",&f_m_m_visible);
	reader->AddVariable("m_m_recoil",&f_m_m_recoil);
	//reader->AddVariable("m_phi_dilepton_1",&f_m_phi_dilepton_1);
	//reader->AddVariable("m_phi_dilepton_2",&f_m_phi_dilepton_2);
	//reader->AddVariable("m_cos_miss",&f_m_cos_miss);
	//reader->AddVariable("m_cos_Z",&f_m_cos_Z);
	reader->AddVariable("m_cos_theta_dilepton",&f_m_cos_theta_dilepton);
	//reader->AddVariable("m_angle_dilepton",&f_m_angle_dilepton);
	//reader->AddVariable("m_delta_pt",&f_m_delta_pt);
	//reader->AddVariable("m_energy_neutrino",&f_m_energy_neutrino);
	//reader->AddVariable("m_energy_visible",&f_m_energy_visible);
	                                                 
	// --- Book the MVA methods
	reader->BookMVA("BDTG","weights/bkg_e2e2h_2fermions_BDTG.weights.xml");

	TFile *f_sig =TFile::Open("../sel/signal_e2e2h.root");
	TTree* TreeS_bbaa = f_sig->Get("MCPart");

	TFile *f_bkg= TFile::Open("../sel/bkg_e2e2h_2fermions.root");
	TTree* TreeB_bbaa = f_bkg->Get("MCPart");

	Float_t	d_m_event,d_m_event_type,d_m_p_neutral[4],d_m_p_photon[4],d_m_p_leptonp[4],d_m_p_leptonm[4],d_m_p_dilepton[4],d_m_p_charged[4],d_m_p_Higgsdaughters[4];
	Float_t d_m_p_Higgsdaughter1[4],d_m_p_Higgsdaughter2[4],d_m_p_Zdaughters[4],d_m_p_Zdaughterp[4],d_m_p_Zdaughterm[4],d_m_m_visible;
	Float_t d_m_pt_photon,d_m_pt_dilepton,d_m_n_charged,d_m_n_gamma,d_m_n_leptonp,d_m_n_leptonm,d_m_n_chargedp,d_m_n_chargedm,d_m_n_Higgsdaughter,d_m_n_neutrino;
	Float_t d_m_m_recoil,d_m_phi_dilepton_1,d_m_phi_dilepton_2,d_m_cos_miss,d_m_cos_Z,d_m_angle_dilepton,d_m_delta_pt,d_m_energy_neutrino,d_m_energy_visible,d_BDTG;
	Float_t d_m_pt_leptonm,d_m_pt_leptonp,d_m_pz_dilepton,d_m_pz_leptonm,d_m_pz_leptonp,d_m_cos_theta_dilepton;
	Float_t d_m_cos_theta_leptonm,d_m_cos_theta_leptonp,d_m_energy_leptonm,d_m_energy_leptonp;
	
	TreeS_bbaa->SetBranchAddress("m_p_neutral",d_m_p_neutral);
	TreeS_bbaa->SetBranchAddress("m_p_photon",d_m_p_photon);
	TreeS_bbaa->SetBranchAddress("m_p_leptonp",d_m_p_leptonp);
	TreeS_bbaa->SetBranchAddress("m_p_leptonm",d_m_p_leptonm);
	TreeS_bbaa->SetBranchAddress("m_p_dilepton",d_m_p_dilepton);
	TreeS_bbaa->SetBranchAddress("m_p_charged",d_m_p_charged);
	TreeS_bbaa->SetBranchAddress("m_p_Higgsdaughters",d_m_p_Higgsdaughters);
	TreeS_bbaa->SetBranchAddress("m_p_Higgsdaughter1",d_m_p_Higgsdaughter1);
	TreeS_bbaa->SetBranchAddress("m_p_Higgsdaughter2",d_m_p_Higgsdaughter2);
	TreeS_bbaa->SetBranchAddress("m_p_Zdaughters",d_m_p_Zdaughters);
	TreeS_bbaa->SetBranchAddress("m_p_Zdaughterp",d_m_p_Zdaughterp);
	TreeS_bbaa->SetBranchAddress("m_p_Zdaughterm",d_m_p_Zdaughterm);
	TreeS_bbaa->SetBranchAddress("m_pt_photon",&d_m_pt_photon);
	TreeS_bbaa->SetBranchAddress("m_pt_dilepton",&d_m_pt_dilepton);
	TreeS_bbaa->SetBranchAddress("m_pt_leptonm",&d_m_pt_leptonm);
	TreeS_bbaa->SetBranchAddress("m_pt_leptonp",&d_m_pt_leptonp);
	TreeS_bbaa->SetBranchAddress("m_pz_dilepton",&d_m_pz_dilepton);
	TreeS_bbaa->SetBranchAddress("m_pz_leptonm",&d_m_pz_leptonm);
	TreeS_bbaa->SetBranchAddress("m_pz_leptonp",&d_m_pz_leptonp);
	TreeS_bbaa->SetBranchAddress("m_m_visible",&d_m_m_visible);
	TreeS_bbaa->SetBranchAddress("m_m_recoil",&d_m_m_recoil);
	TreeS_bbaa->SetBranchAddress("m_phi_dilepton_1",&d_m_phi_dilepton_1);
	TreeS_bbaa->SetBranchAddress("m_phi_dilepton_2",&d_m_phi_dilepton_2);
	TreeS_bbaa->SetBranchAddress("m_cos_miss",&d_m_cos_miss);
	TreeS_bbaa->SetBranchAddress("m_cos_Z",&d_m_cos_Z);
	TreeS_bbaa->SetBranchAddress("m_cos_theta_dilepton",&d_m_cos_theta_dilepton);
	TreeS_bbaa->SetBranchAddress("m_cos_theta_leptonm",&d_m_cos_theta_leptonm);
	TreeS_bbaa->SetBranchAddress("m_cos_theta_leptonp",&d_m_cos_theta_leptonp);
	TreeS_bbaa->SetBranchAddress("m_angle_dilepton",&d_m_angle_dilepton);
	TreeS_bbaa->SetBranchAddress("m_delta_pt",&d_m_delta_pt);
	TreeS_bbaa->SetBranchAddress("m_energy_neutrino",&d_m_energy_neutrino);
	TreeS_bbaa->SetBranchAddress("m_energy_visible",&d_m_energy_visible);
	TreeS_bbaa->SetBranchAddress("m_energy_leptonm",&d_m_energy_leptonm);
	TreeS_bbaa->SetBranchAddress("m_energy_leptonp",&d_m_energy_leptonp);

	TreeB_bbaa->SetBranchAddress("m_p_neutral",d_m_p_neutral);
	TreeB_bbaa->SetBranchAddress("m_p_photon",d_m_p_photon);
	TreeB_bbaa->SetBranchAddress("m_p_leptonp",d_m_p_leptonp);
	TreeB_bbaa->SetBranchAddress("m_p_leptonm",d_m_p_leptonm);
	TreeB_bbaa->SetBranchAddress("m_p_dilepton",d_m_p_dilepton);
	TreeB_bbaa->SetBranchAddress("m_p_charged",d_m_p_charged);
	TreeB_bbaa->SetBranchAddress("m_p_Higgsdaughters",d_m_p_Higgsdaughters);
	TreeB_bbaa->SetBranchAddress("m_p_Higgsdaughter1",d_m_p_Higgsdaughter1);
	TreeB_bbaa->SetBranchAddress("m_p_Higgsdaughter2",d_m_p_Higgsdaughter2);
	TreeB_bbaa->SetBranchAddress("m_p_Zdaughters",d_m_p_Zdaughters);
	TreeB_bbaa->SetBranchAddress("m_p_Zdaughterp",d_m_p_Zdaughterp);
	TreeB_bbaa->SetBranchAddress("m_p_Zdaughterm",d_m_p_Zdaughterm);
	TreeB_bbaa->SetBranchAddress("m_pt_photon",&d_m_pt_photon);
	TreeB_bbaa->SetBranchAddress("m_pt_dilepton",&d_m_pt_dilepton);
	TreeB_bbaa->SetBranchAddress("m_pt_leptonm",&d_m_pt_leptonm);
	TreeB_bbaa->SetBranchAddress("m_pt_leptonp",&d_m_pt_leptonp);
	TreeB_bbaa->SetBranchAddress("m_pz_dilepton",&d_m_pt_dilepton);
	TreeB_bbaa->SetBranchAddress("m_pz_leptonm",&d_m_pz_leptonm);
	TreeB_bbaa->SetBranchAddress("m_pz_leptonp",&d_m_pz_leptonp);
	TreeB_bbaa->SetBranchAddress("m_m_visible",&d_m_m_visible);
	TreeB_bbaa->SetBranchAddress("m_m_recoil",&d_m_m_recoil);
	TreeB_bbaa->SetBranchAddress("m_phi_dilepton_1",&d_m_phi_dilepton_1);
	TreeB_bbaa->SetBranchAddress("m_phi_dilepton_2",&d_m_phi_dilepton_2);
	TreeB_bbaa->SetBranchAddress("m_cos_miss",&d_m_cos_miss);
	TreeB_bbaa->SetBranchAddress("m_cos_Z",&d_m_cos_Z);
	TreeB_bbaa->SetBranchAddress("m_cos_theta_dilepton",&d_m_cos_theta_dilepton);
	TreeB_bbaa->SetBranchAddress("m_cos_theta_leptonm",&d_m_cos_theta_leptonm);
	TreeB_bbaa->SetBranchAddress("m_cos_theta_leptonp",&d_m_cos_theta_leptonp);
	TreeB_bbaa->SetBranchAddress("m_angle_dilepton",&d_m_angle_dilepton);
	TreeB_bbaa->SetBranchAddress("m_delta_pt",&d_m_delta_pt);
	TreeB_bbaa->SetBranchAddress("m_energy_neutrino",&d_m_energy_neutrino);
	TreeB_bbaa->SetBranchAddress("m_energy_visible",&d_m_energy_visible);
	TreeB_bbaa->SetBranchAddress("m_energy_leptonm",&d_m_energy_leptonm);
	TreeB_bbaa->SetBranchAddress("m_energy_leptonp",&d_m_energy_leptonp);
	
	TFile f_S("../BDT_output/Hinv_sig_e2e2h_2fermions_BDT.root","recreate");
	
	TTree TreeS_bbaa_output("MCPart","MCPart");

	TreeS_bbaa_output.Branch("m_p_neutral",d_m_p_neutral,"m_p_neutral[4]/F");
	TreeS_bbaa_output.Branch("m_p_photon",d_m_p_photon,"m_p_photon[4]/F");
	TreeS_bbaa_output.Branch("m_p_leptonp",d_m_p_leptonp,"m_p_leptonp[4]/F");
	TreeS_bbaa_output.Branch("m_p_leptonm",d_m_p_leptonm,"m_p_leptonm[4]/F");
	TreeS_bbaa_output.Branch("m_p_dilepton",d_m_p_dilepton,"m_p_dilepton[4]/F");
	TreeS_bbaa_output.Branch("m_p_charged",d_m_p_charged,"m_p_charged[4]/F");
	TreeS_bbaa_output.Branch("m_p_Higgsdaughters",d_m_p_Higgsdaughters,"m_p_Higgsdaughters[4]/F");
	TreeS_bbaa_output.Branch("m_p_Higgsdaughter1",d_m_p_Higgsdaughter1,"m_p_Higgsdaughter1[4]/F");
	TreeS_bbaa_output.Branch("m_p_Higgsdaughter2",d_m_p_Higgsdaughter2,"m_p_Higgsdaughter2[4]/F");
	TreeS_bbaa_output.Branch("m_p_Zdaughters",d_m_p_Zdaughters,"m_p_Zdaughters[4]/F");
	TreeS_bbaa_output.Branch("m_p_Zdaughterp",d_m_p_Zdaughterp,"m_p_Zdaughterp[4]/F");
	TreeS_bbaa_output.Branch("m_p_Zdaughterm",d_m_p_Zdaughterm,"m_p_Zdaughterm[4]/F");
	TreeS_bbaa_output.Branch("m_pt_photon",&d_m_pt_photon,"m_pt_photon/F");
	TreeS_bbaa_output.Branch("m_pt_dilepton",&d_m_pt_dilepton,"m_pt_dilepton/F");
	TreeS_bbaa_output.Branch("m_pt_leptonm",&d_m_pt_leptonm,"m_pt_leptonm/F");
	TreeS_bbaa_output.Branch("m_pt_leptonp",&d_m_pt_leptonp,"m_pt_leptonp/F");
	TreeS_bbaa_output.Branch("m_pz_dilepton",&d_m_pz_dilepton,"m_pz_dilepton/F");
	TreeS_bbaa_output.Branch("m_pz_leptonm",&d_m_pz_leptonm,"m_pz_leptonm/F");
	TreeS_bbaa_output.Branch("m_pz_leptonp",&d_m_pz_leptonp,"m_pz_leptonp/F");
	TreeS_bbaa_output.Branch("m_m_visible",&d_m_m_visible,"m_m_visible/F");
	TreeS_bbaa_output.Branch("m_m_recoil",&d_m_m_recoil,"m_m_recoil/F");
	TreeS_bbaa_output.Branch("m_phi_dilepton_1",&d_m_phi_dilepton_1,"m_phi_dilepton_1/F");
	TreeS_bbaa_output.Branch("m_phi_dilepton_2",&d_m_phi_dilepton_2,"m_phi_dilepton_2/F");
	TreeS_bbaa_output.Branch("m_cos_miss",&d_m_cos_miss,"m_cos_miss/F");
	TreeS_bbaa_output.Branch("m_cos_Z",&d_m_cos_Z,"m_cos_Z/F");
	TreeS_bbaa_output.Branch("m_cos_theta_dilepton",&d_m_cos_theta_dilepton,"m_cos_theta_dilepton/F");
	TreeS_bbaa_output.Branch("m_cos_theta_leptonm",&d_m_cos_theta_leptonm,"m_cos_theta_leptonm/F");
	TreeS_bbaa_output.Branch("m_cos_theta_leptonp",&d_m_cos_theta_leptonp,"m_cos_theta_leptonp/F");
	TreeS_bbaa_output.Branch("m_angle_dilepton",&d_m_angle_dilepton,"m_angle_dilepton/F");
	TreeS_bbaa_output.Branch("m_delta_pt",&d_m_delta_pt,"m_delta_pt/F");
	TreeS_bbaa_output.Branch("m_energy_neutrino",&d_m_energy_neutrino,"m_energy_neutrino/F");
	TreeS_bbaa_output.Branch("m_energy_visible",&d_m_energy_visible,"m_energy_visible/F");
	TreeS_bbaa_output.Branch("m_energy_leptonm",&d_m_energy_leptonm,"m_energy_leptonm/F");
	TreeS_bbaa_output.Branch("m_energy_leptonp",&d_m_energy_leptonp,"m_energy_leptonp/F");
	TreeS_bbaa_output.Branch( "BDTG", &d_BDTG,"BDTG/F");
	
	std::cout << "--- Processing: " << TreeS_bbaa->GetEntries() << " signal events" << std::endl;
	for (Long64_t ievt=0; ievt<TreeS_bbaa->GetEntries();ievt++) {
		TreeS_bbaa->GetEntry(ievt);
		//f_m_pt_photon=d_m_pt_photon;
		f_m_pt_dilepton=d_m_pt_dilepton;
		f_m_pt_leptonm=d_m_pt_leptonm;
		f_m_pt_leptonp=d_m_pt_leptonp;
		f_m_pz_leptonp=d_m_pz_leptonp;
		//f_m_m_visible=d_m_m_visible;
		f_m_m_recoil=d_m_m_recoil;
		//f_m_phi_dilepton_1=d_m_phi_dilepton_1;
		//f_m_phi_dilepton_2=d_m_phi_dilepton_2;
		//f_m_cos_miss=d_m_cos_miss;
		//f_m_cos_Z=d_m_cos_Z;
		f_m_cos_theta_dilepton=d_m_cos_theta_dilepton;
		//f_m_angle_dilepton=d_m_angle_dilepton;
		//f_m_delta_pt=d_m_delta_pt;
		//f_m_energy_neutrino=d_m_energy_neutrino;
		//f_m_energy_visible=d_m_energy_visible;
		// --- Return the MVA outputs
		if (Use["BDTG"]) d_BDTG = reader->EvaluateMVA( "BDTG") ;
		if (d_BDTG>cut_BDT) TreeS_bbaa_output.Fill();
	}
	std::cout << "--- End of signal event loop: "<< std::endl;
	TreeS_bbaa_output.Write();
	//f_S.Close();
	
	TFile f_B("../BDT_output/Hinv_bkg_e2e2h_2fermions_BDT.root","recreate");
	TTree TreeB_bbaa_output("MCPart","MCPart");

	TreeB_bbaa_output.Branch("m_p_neutral",d_m_p_neutral,"m_p_neutral[4]/F");
	TreeB_bbaa_output.Branch("m_p_photon",d_m_p_photon,"m_p_photon[4]/F");
	TreeB_bbaa_output.Branch("m_p_leptonp",d_m_p_leptonp,"m_p_leptonp[4]/F");
	TreeB_bbaa_output.Branch("m_p_leptonm",d_m_p_leptonm,"m_p_leptonm[4]/F");
	TreeB_bbaa_output.Branch("m_p_dilepton",d_m_p_dilepton,"m_p_dilepton[4]/F");
	TreeB_bbaa_output.Branch("m_p_charged",d_m_p_charged,"m_p_charged[4]/F");
	TreeB_bbaa_output.Branch("m_p_Higgsdaughters",d_m_p_Higgsdaughters,"m_p_Higgsdaughters[4]/F");
	TreeB_bbaa_output.Branch("m_p_Higgsdaughter1",d_m_p_Higgsdaughter1,"m_p_Higgsdaughter1[4]/F");
	TreeB_bbaa_output.Branch("m_p_Higgsdaughter2",d_m_p_Higgsdaughter2,"m_p_Higgsdaughter2[4]/F");
	TreeB_bbaa_output.Branch("m_p_Zdaughters",d_m_p_Zdaughters,"m_p_Zdaughters[4]/F");
	TreeB_bbaa_output.Branch("m_p_Zdaughterp",d_m_p_Zdaughterp,"m_p_Zdaughterp[4]/F");
	TreeB_bbaa_output.Branch("m_p_Zdaughterm",d_m_p_Zdaughterm,"m_p_Zdaughterm[4]/F");
	TreeB_bbaa_output.Branch("m_pt_photon",&d_m_pt_photon,"m_pt_photon/F");
	TreeB_bbaa_output.Branch("m_pt_dilepton",&d_m_pt_dilepton,"m_pt_dilepton/F");
	TreeB_bbaa_output.Branch("m_pt_leptonm",&d_m_pt_leptonm,"m_pt_leptonm/F");
	TreeB_bbaa_output.Branch("m_pt_leptonp",&d_m_pt_leptonp,"m_pt_leptonp/F");
	TreeB_bbaa_output.Branch("m_pz_dilepton",&d_m_pz_dilepton,"m_pz_dilepton/F");
	TreeB_bbaa_output.Branch("m_pz_leptonm",&d_m_pz_leptonm,"m_pz_leptonm/F");
	TreeB_bbaa_output.Branch("m_pz_leptonp",&d_m_pz_leptonp,"m_pz_leptonp/F");
	TreeB_bbaa_output.Branch("m_m_visible",&d_m_m_visible,"m_m_visible/F");
	TreeB_bbaa_output.Branch("m_m_recoil",&d_m_m_recoil,"m_m_recoil/F");
	TreeB_bbaa_output.Branch("m_phi_dilepton_1",&d_m_phi_dilepton_1,"m_phi_dilepton_1/F");
	TreeB_bbaa_output.Branch("m_phi_dilepton_2",&d_m_phi_dilepton_2,"m_phi_dilepton_2/F");
	TreeB_bbaa_output.Branch("m_cos_miss",&d_m_cos_miss,"m_cos_miss/F");
	TreeB_bbaa_output.Branch("m_cos_Z",&d_m_cos_Z,"m_cos_Z/F");
	TreeB_bbaa_output.Branch("m_cos_theta_dilepton",&d_m_cos_theta_dilepton,"m_cos_theta_dilepton/F");
	TreeB_bbaa_output.Branch("m_cos_theta_leptonm",&d_m_cos_theta_leptonm,"m_cos_theta_leptonm/F");
	TreeB_bbaa_output.Branch("m_cos_theta_leptonp",&d_m_cos_theta_leptonp,"m_cos_theta_leptonp/F");
	TreeB_bbaa_output.Branch("m_angle_dilepton",&d_m_angle_dilepton,"m_angle_dilepton/F");
	TreeB_bbaa_output.Branch("m_delta_pt",&d_m_delta_pt,"m_delta_pt/F");
	TreeB_bbaa_output.Branch("m_energy_neutrino",&d_m_energy_neutrino,"m_energy_neutrino/F");
	TreeB_bbaa_output.Branch("m_energy_visible",&d_m_energy_visible,"m_energy_visible/F");
	TreeB_bbaa_output.Branch("m_energy_leptonm",&d_m_energy_leptonm,"m_energy_leptonm/F");
	TreeB_bbaa_output.Branch("m_energy_leptonp",&d_m_energy_leptonp,"m_energy_leptonp/F");
	TreeB_bbaa_output.Branch( "BDTG", &d_BDTG,"BDTG/F");

	std::cout << "--- Processing: " << TreeB_bbaa->GetEntries() << " background events" << std::endl;
	for (Long64_t ievt=0; ievt<TreeB_bbaa->GetEntries();ievt++) {
		TreeB_bbaa->GetEntry(ievt);
		//f_m_pt_photon=d_m_pt_photon;
		f_m_pt_dilepton=d_m_pt_dilepton;
		f_m_pt_leptonm=d_m_pt_leptonm;
		f_m_pt_leptonp=d_m_pt_leptonp;
		f_m_pz_leptonp=d_m_pz_leptonp;
		//f_m_m_visible=d_m_m_visible;
		f_m_m_recoil=d_m_m_recoil;
		//f_m_phi_dilepton_1=d_m_phi_dilepton_1;
		//f_m_phi_dilepton_2=d_m_phi_dilepton_2;
		//f_m_cos_miss=d_m_cos_miss;
		//f_m_cos_Z=d_m_cos_Z;
		f_m_cos_theta_dilepton=d_m_cos_theta_dilepton;
		//f_m_angle_dilepton=d_m_angle_dilepton;
		//f_m_delta_pt=d_m_delta_pt;
		//f_m_energy_neutrino=d_m_energy_neutrino;
		//f_m_energy_visible=d_m_energy_visible;
		// --- Return the MVA outputs
		if (Use["BDTG"]) d_BDTG = reader->EvaluateMVA( "BDTG") ;
		if (d_BDTG>cut_BDT) TreeB_bbaa_output.Fill();
	}
	std::cout << "--- End of background event loop: "<< std::endl;
	TreeB_bbaa_output.Write();
	//f_B.Close();	

	std::cout << "==> TMVAClassificationApplication is done!" << endl << std::endl;
}
