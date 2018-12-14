// -*- C++ -*- //  
//
// Description: Higgs -> Invisible 
//
// Original Author:  JING Maoqiang <jingmq@ihep.ac.cn>
//         Created:  [2018-04-02 Mon 15:49] 
//         Inspired by CHEN Zhenxing's code 
//
//

//
// system include files
//

// for MCParticle, collection and reconstruction
#include <EVENT/LCCollection.h>
#include <IMPL/LCCollectionVec.h>
#include <EVENT/LCFloatVec.h>
#include <EVENT/MCParticle.h>
#include <marlin/Processor.h>
#include <EVENT/ReconstructedParticle.h>
#include <IMPL/MCParticleImpl.h>
#include <EVENT/LCFloatVec.h>
#include <EVENT/LCParameters.h>

// for general definition
// #include <values.h>
#include <string>
#include <iostream>
#include <TFile.h> 
#include <TTree.h>
#include <TVector3.h>
#include <TRandom.h>
//#include <sstream>              
#include <cmath>
#include <vector>
#include <TMath.h>
#include <TLorentzVector.h>
//#include <stdexcept>
//#include <Rtypes.h>

class hig2inv  : public marlin::Processor {

<<<<<<< HEAD
    public:
        Processor*  newProcessor() { return new hig2inv ; }
        hig2inv();
        ~hig2inv() {};

        void init();
        void processEvent( LCEvent * evt );
        void end();

    private:
        std::string FileName;
        std::string TreeName;

        LCCollection* col_MC;
        LCCollection* col_Reco;
        MCParticle *a1_MC;

        TFile *m_file;
        TTree *m_tree;

        int LeptonID, RecoPID, tmpPID, PhotonPID, ElectronPID, MuonPID, NeutrinoEPID, NeutrinoMuonPID, TauPID, NeutrinoTauPID, ZPID, HiggsPID;
        int nMC, nReco, NCandiP, NCandiM, NParent, NDaughter, nDaughter, DIndex;
        int OverWrite;
        float RecoEMax, RecoEMin, ZMass;
        int m_n_gamma, m_n_charged, m_n_leptonp, m_n_leptonm, m_n_chargedp, m_n_chargedm, m_n_Higgsdaughter, m_n_neutral,m_n_neutrino;
        unsigned int m_event;
        float m_sum_p_neutral[4], m_p_photon[4],m_p_visible[4],m_sum_p_charged[4], m_p_leptonp[4], m_p_leptonm[4], m_p_dilepton[4], m_p_Zdaughters[4], m_p_Zdaughterp[4], m_p_Zdaughterm[4], m_p_Higgsdaughters[4], m_p_Higgsdaughter1[4],m_p_Higgsdaughter2[4];
        float m_m_dimu, m_m_recoil,m_e_recoil,m_e_dimu;
        float m_pt_photon, m_pt_dilepton;
        float RecoE,lepton_charge;
        float RecoP[3];
        float m_energy_visible, m_energy_neutrino,m_vis_rec_m,m_vis_rec_e,m_m_visible;
        float m_mine_lepton,m_maxe_lepton;
        float m_minp_lepton[4],m_maxp_lepton[4];
        // float m_m_recoil[11];
        // float spreadfactor[11];
        float scale1, scale2;
        float currVisMass, currRecoilMass, currVisEnergy;
        float MinZThrDis;
        float m_phi_dilepton_1, m_phi_dilepton_2;
        float phi_p_tmp, phi_m_tmp;
        float m_cos_miss, m_cos_Z;
        float m_angle_dilepton;
        float m_delta_pt;
                float MCEn;
        int m_PID_Zdaughter, m_PID_HiggsDaughter, m_PID_Higgsdaughter[2];
        // TLorentzVector P_P, P_M, P_T[11];

        TLorentzVector P4_Neutral_Sum,P4_Charged_Sum,P_P, P_M, P_T, miss, FourMin_Lepton, FourMax_Lepton;
        std::vector<TLorentzVector> FourMom_LeptonP, FourMom_LeptonM, FourMom_ChargedP, FourMom_ChargedM, FourMom_Charged, FourMom_Gamma,CandiP, CandiM;

        void book_tree();
        void saveNeutral( int nReco, LCCollection* colReco );
        void savePhoton( int nReco, LCCollection* colReco );
        void selectCharged( int nReco, LCCollection* colReco );
        void selectLepton( int nReco, LCCollection* col_Reco);
        void saveVisible(TLorentzVector m_sum_p_charged,TLorentzVector m_sum_p_neutral);
        void saveminandmaxLepton(std::vector<TLorentzVector> FourMom_LeptonP, std::vector<TLorentzVector> FourMom_LeptonM);		
        void saveRecInfo(std::vector<TLorentzVector> FourMom_LeptonP, std::vector<TLorentzVector> FourMom_LeptonM);
        void saveMCInfo( int nMC, LCCollection* col_MC );
        void saveZdaughter( int NParent, int NDaughter, int tmpPID, float MCEn, MCParticle *a1_MC );
        void saveHiggsdaughter( int NParent, int NDaughter, MCParticle *itr, int tmpPID, float MCEn, MCParticle *a1_MC );
        void saveNeutrino( int NParent, int NDaughter, MCParticle *a1_MC, int tmpPID, float MCEn );
        void printDecayChain( int MCParticleID, MCParticle *mcp );
        void printMCinfo( int MCParticleID, int flag, MCParticle *mcp, std::vector<MCParticle*> pvec, std::vector<MCParticle*> dvec );
        void variable_init();
=======
	public:
		Processor*  newProcessor() { return new hig2inv ; }
		hig2inv();
		~hig2inv() {};

		void init();
		void processEvent( LCEvent * evt );
		void end();

	private:
		std::string FileName;
		std::string TreeName;

		LCCollection* col_MC;
		LCCollection* col_Reco;
		MCParticle *a1_MC;

		TFile *m_file;
		TTree *m_tree;

		int LeptonID, RecoPID, tmpPID, PhotonPID, ElectronPID, MuonPID, NeutrinoEPID, NeutrinoMuonPID, TauPID, NeutrinoTauPID, ZPID, HiggsPID;
		int nMC, nReco, NCandiP, NCandiM, NParent, NDaughter, nDaughter, DIndex;
		int OverWrite;
		float RecoEMax, RecoEMin, ZMass;
		int m_n_gamma, m_n_charged, m_n_leptonp, m_n_leptonm, m_n_chargedp, m_n_chargedm, m_n_Higgsdaughter, m_n_neutral,m_n_neutrino;
		unsigned int m_event;
		float m_sum_p_neutral[4], m_p_photon[4],m_p_visible[4],m_sum_p_charged[4], m_p_leptonp[4], m_p_leptonm[4], m_p_dilepton[4], m_p_Zdaughters[4], m_p_Zdaughterp[4], m_p_Zdaughterm[4], m_p_Higgsdaughters[4], m_p_Higgsdaughter1[4],m_p_Higgsdaughter2[4];
		float m_m_dimu, m_m_recoil;
		float m_pt_photon, m_pt_dilepton;
		float RecoE,lepton_charge;
		float RecoP[3];
		float m_energy_visible, m_energy_neutrino,m_vis_rec_m,m_vis_rec_e;
		// float m_m_recoil[11];
		// float spreadfactor[11];
		float scale1, scale2;
		float currVisMass, currRecoilMass, currVisEnergy;
		float MinZThrDis;
		float m_phi_dilepton_1, m_phi_dilepton_2;
		float phi_p_tmp, phi_m_tmp;
		float m_cos_miss, m_cos_Z;
		float m_angle_dilepton;
		float m_delta_pt;
                float MCEn;
		int m_PID_Zdaughter, m_PID_HiggsDaughter, m_PID_Higgsdaughter[2];
		// TLorentzVector P_P, P_M, P_T[11];

		TLorentzVector P4_Neutral_Sum,P4_Charged_Sum,P_P, P_M, P_T, miss;
		std::vector<TLorentzVector> FourMom_LeptonP, FourMom_LeptonM, FourMom_ChargedP, FourMom_ChargedM, FourMom_Charged, FourMom_Gamma,CandiP, CandiM;

		void book_tree();
		void saveNeutral( int nReco, LCCollection* colReco );
		void savePhoton( int nReco, LCCollection* colReco );
		void selectCharged( int nReco, LCCollection* colReco );
		void selectLepton( int nReco, LCCollection* col_Reco);
		void saveVisible(TLorentzVector m_sum_p_charged,TLorentzVector m_sum_p_neutral);		
		void saveRecInfo(std::vector<TLorentzVector> FourMom_LeptonP, std::vector<TLorentzVector> FourMom_LeptonM);
		void saveMCInfo( int nMC, LCCollection* col_MC );
		void saveZdaughter( int NParent, int NDaughter, int tmpPID, float MCEn, MCParticle *a1_MC );
		void saveHiggsdaughter( int NParent, int NDaughter, MCParticle *itr, int tmpPID, float MCEn, MCParticle *a1_MC );
		void saveNeutrino( int NParent, int NDaughter, MCParticle *a1_MC, int tmpPID, float MCEn );
		void printDecayChain( int MCParticleID, MCParticle *mcp );
		void printMCinfo( int MCParticleID, int flag, MCParticle *mcp, std::vector<MCParticle*> pvec, std::vector<MCParticle*> dvec );
		void variable_init();
>>>>>>> cepc/master

};

hig2inv a_hig2inv_instance;

hig2inv::hig2inv()
     : Processor("hig2inv") {

    FileName="MCTruth.root";
        registerProcessorParameter( "TreeOutputFile" ,
            "The name of the file to which the ROOT tree will be written" ,
            FileName ,
            FileName);

    TreeName="MCPart";
        registerProcessorParameter( "TreeName" ,
            "The name of the ROOT tree" ,
            TreeName ,
            TreeName);

    LeptonID=13; // 11 for electron, 13 for muon
        registerProcessorParameter( "LeptonIDTag" ,
            "Lepton ID that will be used in this analysis." ,
            LeptonID ,
            LeptonID);

    OverWrite=0;
            registerProcessorParameter( "OverwriteFile" ,
            "If zero an already existing file will not be overwritten." ,
            OverWrite ,
            OverWrite);

    PhotonPID=22; // 22 for photon
        registerProcessorParameter( "PhotonPID" ,
            "Photon ID that will be used in this analysis." ,
            PhotonPID ,
            PhotonPID);

    RecoEMax=100.0;
        registerProcessorParameter( "RecoEMax" ,
            "Maximum energy of reconstructed particles." ,
            RecoEMax ,
            RecoEMax);

    RecoEMin=10.0; 
        registerProcessorParameter( "RecoEMin" ,
            "Minimum energy of reconstructed particles." ,
            RecoEMin ,
            RecoEMin);

    ZMass=91.2; 
        registerProcessorParameter( "ZMass" ,
            "Mass of Z Boson." ,
            ZMass ,
            ZMass);

    ElectronPID=11;
        registerProcessorParameter( "ElectronPID" ,
            "Electron ID that will be used in this analysis." ,
            ElectronPID ,
            ElectronPID);

    NeutrinoEPID=12;
        registerProcessorParameter( "NeutrinoEPID" ,
            "Electron neutrino ID that will be used in this analysis." ,
            NeutrinoEPID ,
            NeutrinoEPID);

    MuonPID=13;
        registerProcessorParameter( "MuonPID" ,
            "Muon ID that will be used in this analysis." ,
            MuonPID ,
            MuonPID);

    NeutrinoMuonPID=14;
        registerProcessorParameter( "NeutrinoMuonPID" ,
            "Muon neutrino ID that will be used in this analysis." ,
            NeutrinoMuonPID ,
            NeutrinoMuonPID);

    TauPID=15;
        registerProcessorParameter( "TauPID" ,
            "Tau ID that will be used in this analysis." ,
            TauPID ,
            TauPID);

    NeutrinoTauPID=16;
        registerProcessorParameter( "NeutrinoTauPID" ,
            "Tau neutrino ID that will be used in this analysis." ,
            NeutrinoTauPID ,
            NeutrinoTauPID);

    ZPID=23;
        registerProcessorParameter( "ZPID" ,
            "Z Boson ID that will be used in this analysis." ,
            ZPID ,
            ZPID);
    HiggsPID=25;
        registerProcessorParameter( "HiggsPID" ,
            "Higgs Boson ID that will be used in this analysis." ,
            HiggsPID ,
            HiggsPID);

}

void hig2inv::init() {

    book_tree();

}

void hig2inv::processEvent( LCEvent * evt ) {	

<<<<<<< HEAD
    if(evt){
        try{
            variable_init();

            col_MC = evt->getCollection( "MCParticle" );
            col_Reco = evt->getCollection( "ArborPFOs" );
            nMC = col_MC->getNumberOfElements();
            nReco = col_Reco->getNumberOfElements();
            m_event=evt->getEventNumber();

            saveNeutral( nReco, col_Reco );
            savePhoton( nReco, col_Reco );
            selectCharged( nReco, col_Reco );
            selectLepton(nReco,col_Reco);
            saveVisible(m_sum_p_charged, m_sum_p_neutral);
            saveRecInfo(FourMom_LeptonP,FourMom_LeptonM);
            saveMCInfo( nMC, col_MC );

            m_tree->Fill();
        }
        catch (lcio::DataNotAvailableException err) { }
    }
=======
	if(evt){
		try{
			variable_init();

			col_MC = evt->getCollection( "MCParticle" );
			col_Reco = evt->getCollection( "ArborPFOs" );
			nMC = col_MC->getNumberOfElements();
			nReco = col_Reco->getNumberOfElements();
			m_event=evt->getEventNumber();

            saveNeutral( nReco, col_Reco );
			savePhoton( nReco, col_Reco );
			selectCharged( nReco, col_Reco );
			selectLepton(nReco,col_Reco);
			saveVisible(m_sum_p_charged, m_sum_p_neutral);
			saveRecInfo(FourMom_LeptonP,FourMom_LeptonM);
			saveMCInfo( nMC, col_MC );

			m_tree->Fill();
		}
		catch (lcio::DataNotAvailableException err) { }
	}
>>>>>>> cepc/master

}	

void hig2inv::end() {

    if (m_tree) {
        TFile *tree_file = m_tree->GetCurrentFile(); //just in case we switched to a new file
        tree_file->Write();
        delete tree_file;
    }

}

void hig2inv::book_tree() { 

<<<<<<< HEAD
    m_file=new TFile(FileName.c_str(),(OverWrite ? "RECREATE" : "UPDATE"));
    if (!m_file->IsOpen()) {
        delete m_file;
        m_file=new TFile(FileName.c_str(),"NEW");
    }
    m_tree = new TTree(TreeName.c_str(),TreeName.c_str());
    m_tree->Branch("m_event",&m_event,"m_event/I");
    m_tree->Branch("m_n_neutral",  &m_n_neutral,  "m_n_neutral/I");
    m_tree->Branch("m_sum_p_neutral", m_sum_p_neutral, "m_sum_p_neutral[4]/F");
    m_tree->Branch("m_p_photon", m_p_photon, "m_p_photon[4]/F");
    m_tree->Branch("m_p_leptonp",  m_p_leptonp,  "m_p_lepton[4]/F");
    m_tree->Branch("m_p_leptonm",  m_p_leptonm,  "m_p_lepton[4]/F");
    m_tree->Branch("m_p_dilepton",  m_p_dilepton,  "m_p_dilepton[4]/F");
    m_tree->Branch("m_sum_p_charged",  m_sum_p_charged,  "m_sum_p_charged[4]/F");
    m_tree->Branch("m_p_Higgsdaughters",  m_p_Higgsdaughters,  "m_p_Higgsdaughters[4]/F");
    m_tree->Branch("m_p_Higgsdaughter1",  m_p_Higgsdaughter1,  "m_p_Higgsdaughter1[4]/F");
    m_tree->Branch("m_p_Higgsdaughter2",  m_p_Higgsdaughter2,  "m_p_Higgsdaughter2[4]/F");
    m_tree->Branch("m_p_Zdaughters",  m_p_Zdaughters,  "m_p_Zdaughters[4]/F");
    m_tree->Branch("m_p_Zdaughterp",  m_p_Zdaughterp,  "m_p_Zdaughterp[4]/F");
    m_tree->Branch("m_p_Zdaughterm",  m_p_Zdaughterm,  "m_p_Zdaughterm[4]/F");

    m_tree->Branch("m_pt_photon", &m_pt_photon, "m_pt_photon/F");
    m_tree->Branch("m_pt_dilepton",  &m_pt_dilepton,  "m_pt_dilepton/F");

    m_tree->Branch("m_n_charged",  &m_n_charged,  "m_n_charged/I");
    m_tree->Branch("m_n_gamma",  &m_n_gamma,  "m_n_gamma/I");
    m_tree->Branch("m_n_leptonp",  &m_n_leptonp,  "m_n_leptonp/I");
    m_tree->Branch("m_n_leptonm",  &m_n_leptonm,  "m_n_leptonm/I");
    m_tree->Branch("m_n_chargedp",  &m_n_chargedp,  "m_n_chargedp/I");
    m_tree->Branch("m_n_chargedm",  &m_n_chargedm,  "m_n_chargedm/I");
    m_tree->Branch("m_n_Higgsdaughter",  &m_n_Higgsdaughter,  "m_n_Higgsdaughter/I");
    m_tree->Branch("m_n_neutrino",  &m_n_neutrino,  "m_n_neutrino/I");

    m_tree->Branch("m_m_dimu",  &m_m_dimu,  "m_m_dimu/F");
    m_tree->Branch("m_e_dimu",  &m_e_dimu,  "m_e_dimu/F");
    // m_tree->Branch("m_m_recoil",  m_m_recoil,  "m_m_recoil[11]/F");
    m_tree->Branch("m_m_recoil",  &m_m_recoil,  "m_m_recoil/F");
    m_tree->Branch("m_e_recoil",  &m_e_recoil,  "m_e_recoil/F");
    m_tree->Branch("m_phi_dilepton_1",  &m_phi_dilepton_1,  "m_phi_dilepton_1/F");
    m_tree->Branch("m_phi_dilepton_2",  &m_phi_dilepton_2,  "m_phi_dilepton_2/F");
    m_tree->Branch("m_cos_miss",  &m_cos_miss,  "m_cos_miss/F");
    m_tree->Branch("m_cos_Z",  &m_cos_Z,  "m_cos_Z/F");
    m_tree->Branch("m_angle_dilepton",  &m_angle_dilepton,  "m_angle_dilepton/F");
    m_tree->Branch("m_delta_pt",  &m_delta_pt,  "m_delta_pt/F");

    m_tree->Branch("m_PID_Zdaughter",  &m_PID_Zdaughter,  "m_PID_Zdaughter/I");
    m_tree->Branch("m_PID_HiggsDaughter",  &m_PID_HiggsDaughter,  "m_PID_HiggsDaughter/I");
    m_tree->Branch("m_PID_Higgsdaughter",  m_PID_Higgsdaughter,  "m_PID_Higgsdaughter[2]/I");

    m_tree->Branch("m_energy_neutrino",  &m_energy_neutrino,  "m_energy_neutrino/F");
    m_tree->Branch("m_energy_visible",  &m_energy_visible,  "m_energy_visible/F");
    m_tree->Branch("m_m_visible",  &m_m_visible,  "m_m_visible/F");
    m_tree->Branch("m_p_visible",  &m_p_visible,  "m_p_visible[4]/F");
    m_tree->Branch("m_vis_rec_m",  &m_vis_rec_m,  "m_vis_rec_m/F");
    m_tree->Branch("m_vis_rec_e",  &m_vis_rec_e,  "m_vis_rec_e/F");

    m_tree->Branch("m_mine_lepton",  &m_mine_lepton,  "m_mine_lepton/F");
    m_tree->Branch("m_maxe_lepton",  &m_maxe_lepton,  "m_maxe_lepton/F");


    m_tree->Branch("m_minp_lepton",  &m_minp_lepton,  "m_minp_lepton[4]/F");
    m_tree->Branch("m_maxp_lepton",  &m_maxp_lepton,  "m_maxp_lepton[4]/F");



=======
	m_file=new TFile(FileName.c_str(),(OverWrite ? "RECREATE" : "UPDATE"));
	if (!m_file->IsOpen()) {
		delete m_file;
		m_file=new TFile(FileName.c_str(),"NEW");
	}
	m_tree = new TTree(TreeName.c_str(),TreeName.c_str());
	m_tree->Branch("m_event",&m_event,"m_event/I");
    m_tree->Branch("m_n_neutral",  &m_n_neutral,  "m_n_neutral/I");
	m_tree->Branch("m_sum_p_neutral", m_sum_p_neutral, "m_sum_p_neutral[4]/F");
	m_tree->Branch("m_p_photon", m_p_photon, "m_p_photon[4]/F");
	m_tree->Branch("m_p_leptonp",  m_p_leptonp,  "m_p_lepton[4]/F");
	m_tree->Branch("m_p_leptonm",  m_p_leptonm,  "m_p_lepton[4]/F");
	m_tree->Branch("m_p_dilepton",  m_p_dilepton,  "m_p_dilepton[4]/F");
	m_tree->Branch("m_sum_p_charged",  m_sum_p_charged,  "m_sum_p_charged[4]/F");
	m_tree->Branch("m_p_Higgsdaughters",  m_p_Higgsdaughters,  "m_p_Higgsdaughters[4]/F");
	m_tree->Branch("m_p_Higgsdaughter1",  m_p_Higgsdaughter1,  "m_p_Higgsdaughter1[4]/F");
	m_tree->Branch("m_p_Higgsdaughter2",  m_p_Higgsdaughter2,  "m_p_Higgsdaughter2[4]/F");
	m_tree->Branch("m_p_Zdaughters",  m_p_Zdaughters,  "m_p_Zdaughters[4]/F");
	m_tree->Branch("m_p_Zdaughterp",  m_p_Zdaughterp,  "m_p_Zdaughterp[4]/F");
	m_tree->Branch("m_p_Zdaughterm",  m_p_Zdaughterm,  "m_p_Zdaughterm[4]/F");

	m_tree->Branch("m_pt_photon", &m_pt_photon, "m_pt_photon/F");
	m_tree->Branch("m_pt_dilepton",  &m_pt_dilepton,  "m_pt_dilepton/F");

	m_tree->Branch("m_n_charged",  &m_n_charged,  "m_n_charged/I");
	m_tree->Branch("m_n_gamma",  &m_n_gamma,  "m_n_gamma/I");
	m_tree->Branch("m_n_leptonp",  &m_n_leptonp,  "m_n_leptonp/I");
	m_tree->Branch("m_n_leptonm",  &m_n_leptonm,  "m_n_leptonm/I");
	m_tree->Branch("m_n_chargedp",  &m_n_chargedp,  "m_n_chargedp/I");
	m_tree->Branch("m_n_chargedm",  &m_n_chargedm,  "m_n_chargedm/I");
	m_tree->Branch("m_n_Higgsdaughter",  &m_n_Higgsdaughter,  "m_n_Higgsdaughter/I");
	m_tree->Branch("m_n_neutrino",  &m_n_neutrino,  "m_n_neutrino/I");

	m_tree->Branch("m_m_dimu",  &m_m_dimu,  "m_m_dimu/F");
	// m_tree->Branch("m_m_recoil",  m_m_recoil,  "m_m_recoil[11]/F");
	m_tree->Branch("m_m_recoil",  &m_m_recoil,  "m_m_recoil/F");

	m_tree->Branch("m_phi_dilepton_1",  &m_phi_dilepton_1,  "m_phi_dilepton_1/F");
	m_tree->Branch("m_phi_dilepton_2",  &m_phi_dilepton_2,  "m_phi_dilepton_2/F");
	m_tree->Branch("m_cos_miss",  &m_cos_miss,  "m_cos_miss/F");
	m_tree->Branch("m_cos_Z",  &m_cos_Z,  "m_cos_Z/F");
	m_tree->Branch("m_angle_dilepton",  &m_angle_dilepton,  "m_angle_dilepton/F");
	m_tree->Branch("m_delta_pt",  &m_delta_pt,  "m_delta_pt/F");

	m_tree->Branch("m_PID_Zdaughter",  &m_PID_Zdaughter,  "m_PID_Zdaughter/I");
	m_tree->Branch("m_PID_HiggsDaughter",  &m_PID_HiggsDaughter,  "m_PID_HiggsDaughter/I");
	m_tree->Branch("m_PID_Higgsdaughter",  m_PID_Higgsdaughter,  "m_PID_Higgsdaughter[2]/I");

	m_tree->Branch("m_energy_neutrino",  &m_energy_neutrino,  "m_energy_neutrino/F");
	m_tree->Branch("m_energy_visible",  &m_energy_visible,  "m_energy_visible/F");
	m_tree->Branch("m_p_visible",  &m_p_visible,  "m_p_visible[4]/F");
	m_tree->Branch("m_vis_rec_m",  &m_vis_rec_m,  "m_vis_rec_m/F");
	m_tree->Branch("m_vis_rec_e",  &m_vis_rec_e,  "m_vis_rec_e/F");
>>>>>>> cepc/master
}

void hig2inv::variable_init() {

<<<<<<< HEAD
    m_n_charged = 0;
    m_n_neutral = 0;
    m_n_leptonp = 0;
    m_n_leptonm = 0;
    m_n_chargedp = 0;
    m_n_chargedm = 0;
    m_n_gamma = 0;
    m_n_neutrino = 0;
    m_n_Higgsdaughter = 0;
    m_energy_neutrino = 0.;
    m_m_dimu = 0.0;  //m_m_visible -> m_m_dimu;
    m_e_dimu = 0.0;
    m_m_recoil=-999.;
    m_e_recoil=-999.;
    m_energy_visible = 0.;
    m_m_visible = 0.;
    m_phi_dilepton_1 = 0;
    m_phi_dilepton_2 = 0;
    m_cos_miss = 0;
    m_cos_Z =0;
    m_angle_dilepton = 0;
    m_delta_pt = 0;
    m_PID_HiggsDaughter = 0;
    m_PID_Zdaughter = 0;
    m_PID_Higgsdaughter[0] = 0;
    m_PID_Higgsdaughter[1] = 0;
    MinZThrDis = 10;
    DIndex = 0;
    m_pt_photon = 0;
    m_pt_dilepton = 0;
    m_vis_rec_m = 0.0;
    m_vis_rec_e = 0.0;
    m_mine_lepton = 0.0;
    m_maxe_lepton = 0.0;
    TLorentzVector beamp(0,0,120.0,120.0);
    TLorentzVector beamm(0,0,-120.0,120.0);
    scale1 = (gRandom->Gaus(1, 0.0024));
    scale2 = (gRandom->Gaus(1, 0.0024));
    TLorentzVector ecms(0, 0, 0, 240);
    P_T = ecms;
    for(int i=0; i<4; i++) {
        m_sum_p_neutral[i] = 0.0;
        m_p_photon[i] = 0.0;
        m_sum_p_charged[i] = 0.0;
        m_p_leptonp[i] = 0.0;
        m_p_leptonm[i] = 0.0;
        m_p_dilepton[i] = 0.0;
        m_p_Zdaughters[i] = 0.0;
        m_p_Zdaughterp[i] = 0.0;
        m_p_Zdaughterm[i] =0.0;
        m_p_Higgsdaughters[i] = 0.0;
        m_p_Higgsdaughter1[i] = 0.0;
        m_p_Higgsdaughter2[i] = 0.0;
        FourMin_Lepton[i]=0.0;
        FourMax_Lepton[i]=0.0;
        m_minp_lepton[i] = 0.0;
        m_maxp_lepton[i] = 0.0;
 

        P4_Charged_Sum[i]= 0.0;//change to get visble energy and mass
        P4_Neutral_Sum[i]= 0.0;//change to get visble energy and mass
        m_p_visible[i] = 0.0;
    }                   
    FourMom_LeptonM.clear();
    FourMom_LeptonP.clear();
    FourMom_Gamma.clear(); 
    FourMom_Charged.clear();
    FourMom_ChargedP.clear();
    FourMom_ChargedM.clear();
    CandiP.clear();
    CandiM.clear();
=======
	m_n_charged = 0;
	m_n_neutral = 0;
	m_n_leptonp = 0;
	m_n_leptonm = 0;
	m_n_chargedp = 0;
	m_n_chargedm = 0;
	m_n_gamma = 0;
	m_n_neutrino = 0;
	m_n_Higgsdaughter = 0;
	m_energy_neutrino = 0.;
	m_m_dimu = 0.0;  //m_m_visible -> m_m_dimu;
	m_m_recoil=-999.;
	m_energy_visible = 0.;
	m_phi_dilepton_1 = 0;
	m_phi_dilepton_2 = 0;
	m_cos_miss = 0;
	m_cos_Z =0;
	m_angle_dilepton = 0;
	m_delta_pt = 0;
	m_PID_HiggsDaughter = 0;
	m_PID_Zdaughter = 0;
	m_PID_Higgsdaughter[0] = 0;
	m_PID_Higgsdaughter[1] = 0;
	MinZThrDis = 10;
	DIndex = 0;
	m_pt_photon = 0;
	m_pt_dilepton = 0;
	m_vis_rec_m = 0.0;
	m_vis_rec_e = 0.0;
	TLorentzVector beamp(0,0,120.0,120.0);
	TLorentzVector beamm(0,0,-120.0,120.0);
	scale1 = (gRandom->Gaus(1, 0.0024));
	scale2 = (gRandom->Gaus(1, 0.0024));
	P_T=scale1*beamp+scale2*beamm;
	for(int i=0; i<4; i++) {
		m_sum_p_neutral[i] = 0.0;
		m_p_photon[i] = 0.0;
		m_sum_p_charged[i] = 0.0;
		m_p_leptonp[i] = 0.0;
		m_p_leptonm[i] = 0.0;
		m_p_dilepton[i] = 0.0;
		m_p_Zdaughters[i] = 0.0;
		m_p_Zdaughterp[i] = 0.0;
		m_p_Zdaughterm[i] =0.0;
		m_p_Higgsdaughters[i] = 0.0;
		m_p_Higgsdaughter1[i] = 0.0;
		m_p_Higgsdaughter2[i] = 0.0;

		P4_Charged_Sum[i]= 0.0;//change to get visble energy and mass
		P4_Neutral_Sum[i]= 0.0;//change to get visble energy and mass
        m_p_visible[i] = 0.0;
	}                   
	FourMom_LeptonM.clear();
	FourMom_LeptonP.clear();
	FourMom_Gamma.clear(); 
	FourMom_Charged.clear();
	FourMom_ChargedP.clear();
	FourMom_ChargedM.clear();
	CandiP.clear();
	CandiM.clear();
>>>>>>> cepc/master

}

void hig2inv::saveNeutral( int nReco, LCCollection* col_Reco ) {
//changed:we need Neutral sum monmentum and energy,this is visible energy.
    int counter = 0; 
<<<<<<< HEAD
    for(int i = 0; i < nReco; i++) {
        ReconstructedParticle *a_Reco = dynamic_cast<EVENT::ReconstructedParticle *>(col_Reco->getElementAt(i));
        if(a_Reco->getCharge()!=0) continue;
        P4_Neutral_Sum[0] += a_Reco->getMomentum()[0];
        P4_Neutral_Sum[1] += a_Reco->getMomentum()[1];
        P4_Neutral_Sum[2] += a_Reco->getMomentum()[2];
        P4_Neutral_Sum[3] += a_Reco->getEnergy();

        counter++;
    }
    m_n_neutral = counter;	

    m_sum_p_neutral[0] = P4_Neutral_Sum[0];
    m_sum_p_neutral[1] = P4_Neutral_Sum[1];
    m_sum_p_neutral[2] = P4_Neutral_Sum[2]; 
    m_sum_p_neutral[3] = P4_Neutral_Sum[3];
=======
	for(int i = 0; i < nReco; i++) {
		ReconstructedParticle *a_Reco = dynamic_cast<EVENT::ReconstructedParticle *>(col_Reco->getElementAt(i));
		if(a_Reco->getCharge()!=0) continue;
		P4_Neutral_Sum[0] += a_Reco->getMomentum()[0];
		P4_Neutral_Sum[1] += a_Reco->getMomentum()[1];
		P4_Neutral_Sum[2] += a_Reco->getMomentum()[2];
		P4_Neutral_Sum[3] += a_Reco->getEnergy();

		counter++;
	}
	m_n_neutral = counter;	

	m_sum_p_neutral[0] = P4_Neutral_Sum[0];
	m_sum_p_neutral[1] = P4_Neutral_Sum[1];
	m_sum_p_neutral[2] = P4_Neutral_Sum[2]; 
	m_sum_p_neutral[3] = P4_Neutral_Sum[3];
>>>>>>> cepc/master
}

void hig2inv::savePhoton( int nReco, LCCollection* col_Reco ) {

//	float photone=50;maoqiang
    double tmp_emax=-1.0;  //PID identification is OK. first change 
<<<<<<< HEAD
    for(int i = 0; i < nReco; i++) {
        ReconstructedParticle *a_Reco = dynamic_cast<EVENT::ReconstructedParticle *>(col_Reco->getElementAt(i));
        if(a_Reco->getCharge()!=0) continue;
        if(a_Reco->getType()!=PhotonPID) continue;
        if(fabs(a_Reco->getMomentum()[2]/a_Reco->getEnergy())>0.995) continue; // acceptance of the detector
        if(a_Reco->getEnergy()>tmp_emax) {
            // photone = a_Reco->getEnergy();
            m_p_photon[3] = a_Reco->getEnergy();
            m_p_photon[0] = a_Reco->getMomentum()[0];
            m_p_photon[1] = a_Reco->getMomentum()[1];
            m_p_photon[2] = a_Reco->getMomentum()[2];
            m_pt_photon = sqrt(m_p_photon[0]*m_p_photon[0]+m_p_photon[1]*m_p_photon[1]);
            FourMom_Gamma.push_back(m_p_photon);
        }
    }
    m_n_gamma = FourMom_Gamma.size();
    if (m_n_gamma == 0){
    m_p_photon[1] = -9999.0;
    m_p_photon[2] = -9999.0; 
    m_p_photon[3] = -9999.0;
    m_p_photon[0] = -9999.0;
    m_pt_photon	= -9999.0;
    } //Second change. Exclude values when photo = 0
=======
	for(int i = 0; i < nReco; i++) {
		ReconstructedParticle *a_Reco = dynamic_cast<EVENT::ReconstructedParticle *>(col_Reco->getElementAt(i));
		if(a_Reco->getCharge()!=0) continue;
		if(a_Reco->getType()!=PhotonPID) continue;
		if(fabs(a_Reco->getMomentum()[2]/a_Reco->getEnergy())>0.995) continue; // acceptance of the detector
		if(a_Reco->getEnergy()>tmp_emax) {
			// photone = a_Reco->getEnergy();
			m_p_photon[3] = a_Reco->getEnergy();
			m_p_photon[0] = a_Reco->getMomentum()[0];
			m_p_photon[1] = a_Reco->getMomentum()[1];
			m_p_photon[2] = a_Reco->getMomentum()[2];
			m_pt_photon = sqrt(m_p_photon[0]*m_p_photon[0]+m_p_photon[1]*m_p_photon[1]);
			FourMom_Gamma.push_back(m_p_photon);
		}
	}
	m_n_gamma = FourMom_Gamma.size();
	if (m_n_gamma == 0){
	m_p_photon[1] = -9999.0;
	m_p_photon[2] = -9999.0; 
	m_p_photon[3] = -9999.0;
	m_p_photon[0] = -9999.0;
	m_pt_photon	= -9999.0;
	} //Second change. Exclude values when photo = 0
>>>>>>> cepc/master

}

void hig2inv::selectCharged( int nReco, LCCollection* col_Reco ) {
<<<<<<< HEAD
    int counter = 0;
    for(int i = 0; i < nReco; i++) {
        ReconstructedParticle *a_Reco = dynamic_cast<EVENT::ReconstructedParticle *>(col_Reco->getElementAt(i));
        if(a_Reco->getCharge()==0) continue;
        P4_Charged_Sum[0] += a_Reco->getMomentum()[0];
        P4_Charged_Sum[1] += a_Reco->getMomentum()[1];
        P4_Charged_Sum[2] += a_Reco->getMomentum()[2];
        P4_Charged_Sum[3] += a_Reco->getEnergy();
        counter++;
    }
      m_n_charged = counter;//3changed.only choose changed particles,rather mu.
=======
	int counter = 0;
	for(int i = 0; i < nReco; i++) {
		ReconstructedParticle *a_Reco = dynamic_cast<EVENT::ReconstructedParticle *>(col_Reco->getElementAt(i));
		if(a_Reco->getCharge()==0) continue;
		P4_Charged_Sum[0] += a_Reco->getMomentum()[0];
		P4_Charged_Sum[1] += a_Reco->getMomentum()[1];
		P4_Charged_Sum[2] += a_Reco->getMomentum()[2];
		P4_Charged_Sum[3] += a_Reco->getEnergy();
		counter++;
	}
	  m_n_charged = counter;//3changed.only choose changed particles,rather mu.
>>>>>>> cepc/master

      m_sum_p_charged[0] = P4_Charged_Sum[0];
      m_sum_p_charged[1] = P4_Charged_Sum[1];
      m_sum_p_charged[2] = P4_Charged_Sum[2];
      m_sum_p_charged[3] = P4_Charged_Sum[3];
<<<<<<< HEAD

}

void hig2inv::selectLepton( int nReco, LCCollection* col_Reco) {

    for(int i = 0; i < nReco; i++) {
        ReconstructedParticle *a_Reco = dynamic_cast<EVENT::ReconstructedParticle *>(col_Reco->getElementAt(i));
        if(a_Reco->getCharge()==0) continue;
        lepton_charge = a_Reco->getCharge();
        RecoPID = abs(a_Reco->getType());
        RecoE = a_Reco->getEnergy();
        RecoP[0] = a_Reco->getMomentum()[0];
        RecoP[1] = a_Reco->getMomentum()[1];
        RecoP[2] = a_Reco->getMomentum()[2];
        TLorentzVector curr(RecoP[0], RecoP[1], RecoP[2], RecoE);
    if ( RecoE > RecoEMin && RecoE < RecoEMax) {
        if (lepton_charge > 0.1)FourMom_ChargedP.push_back(curr);
        if (lepton_charge <-0.1)FourMom_ChargedM.push_back(curr);
        if(RecoPID == MuonPID ) {
           if( lepton_charge >  0.1 )FourMom_LeptonP.push_back( curr );
           if( lepton_charge < -0.1 )FourMom_LeptonM.push_back( curr );
        }
    }	
    }
    saveminandmaxLepton(FourMom_LeptonP,FourMom_LeptonM);
    m_n_leptonp = FourMom_LeptonP.size();
    m_n_leptonm = FourMom_LeptonM.size();
    m_n_chargedp = FourMom_ChargedP.size();
    m_n_chargedm = FourMom_ChargedM.size();

}
void hig2inv::saveminandmaxLepton( std::vector<TLorentzVector> FourMom_LeptonP, std::vector<TLorentzVector> FourMom_LeptonM ) {
    int n_leptonp=0;
    int n_leptonm=0;
    n_leptonp = FourMom_LeptonP.size();
    n_leptonm = FourMom_LeptonM.size();
    if (n_leptonp>0 && n_leptonm>0){
        double min_diff=100.0;
        double max_diff=0.0;
        for (int i=0; i< n_leptonp; i++){
        for (int j=0; j< n_leptonm; j++){
            double E_leptonp=FourMom_LeptonP[i].E();
            double E_leptonm=FourMom_LeptonM[j].E();
            if (E_leptonp <min_diff || E_leptonm<min_diff){
                if(E_leptonp<E_leptonm){
                min_diff=E_leptonp;
                FourMin_Lepton=FourMom_LeptonP[i];
                }
                if (E_leptonp >= E_leptonm){
                min_diff=E_leptonm;
                FourMin_Lepton=FourMom_LeptonM[j];
            }
            }
            if (E_leptonp >max_diff || E_leptonm>max_diff){
                if(E_leptonp>E_leptonm){
                max_diff=E_leptonp;
                FourMax_Lepton=FourMom_LeptonP[i];
                }
                if (E_leptonp <= E_leptonm){
                max_diff=E_leptonm;
                FourMax_Lepton=FourMom_LeptonM[j];
            }
            }            
            }
            }
    }
    m_mine_lepton=FourMin_Lepton[3];
    m_maxe_lepton=FourMax_Lepton[3];
    for(int k=0; k<4; k++) {
    m_minp_lepton[k]=FourMin_Lepton[k];
    m_maxp_lepton[k]=FourMax_Lepton[k];
    }
 
    }


void hig2inv::saveVisible(TLorentzVector m_sum_p_charged,TLorentzVector m_sum_p_neutral) {
    for(int i=0;i<4;i++){
    m_p_visible[i] = m_sum_p_charged[i] + m_sum_p_neutral[i];
    }
   m_m_visible = ( m_sum_p_charged + m_sum_p_neutral).M();
   m_energy_visible = ( m_sum_p_charged + m_sum_p_neutral).E();
   m_vis_rec_m = (P_T - m_sum_p_charged - m_sum_p_neutral).M();
   m_vis_rec_e = (P_T - m_sum_p_charged - m_sum_p_neutral).E();
}

void hig2inv::saveRecInfo( std::vector<TLorentzVector> FourMom_LeptonP, std::vector<TLorentzVector> FourMom_LeptonM ) {

    int nlep_p =  FourMom_LeptonP.size();
    int nlep_m =  FourMom_LeptonM.size();
    if (nlep_p > 0 && nlep_m >0){

    for(int i = 0; i < nlep_p; i++) {  
    for(int j = 0; j < nlep_m; j++) {
        P_P = FourMom_LeptonP[i];
        P_M = FourMom_LeptonM[j];	
        float currdimumass = (P_P + P_M).M();
//	if(fabs(currdimumass - ZMass) < MinZThrDis)) { //This file don't exclude background,only record information 
        MinZThrDis = fabs(currdimumass - ZMass);
        m_m_dimu = currdimumass;
        m_e_dimu = (P_P + P_M).E();
    // save recil mass
        m_e_recoil = (P_T - P_P - P_M).E();
        currRecoilMass = (P_T - P_P - P_M).M();
        m_m_recoil = currRecoilMass;
        // save lepton information
        for(int k=0; k<4; k++) {
            m_p_leptonp[k] = P_P[k];
            m_p_leptonm[k] = P_M[k];
            m_p_dilepton[k] = P_P[k] + P_M[k];
        }
        // save other information
        TLorentzVector ecms(0,0,0,240);
        m_phi_dilepton_1 = fabs(P_P.Phi()- P_M.Phi());
        miss = ecms - m_p_dilepton;
        m_cos_miss = miss.CosTheta();
        m_angle_dilepton = P_P.Angle(P_M.Vect())*180./3.1415926;
        m_pt_dilepton = sqrt(m_p_dilepton[0]*m_p_dilepton[0]+m_p_dilepton[1]*m_p_dilepton[1]);
        m_delta_pt = m_pt_dilepton - m_pt_photon;
        m_cos_Z = m_p_dilepton[2]/sqrt(m_p_dilepton[0]*m_p_dilepton[0]+m_p_dilepton[1]*m_p_dilepton[1]+m_p_dilepton[2]*m_p_dilepton[2]);
        phi_p_tmp = atan2(m_p_leptonp[1],m_p_leptonp[0])*180./3.14159265;
        phi_m_tmp = atan2(m_p_leptonm[1],m_p_leptonm[0])*180./3.14159265;
        if(m_p_leptonp[1] < 0) phi_p_tmp = phi_p_tmp + 360.;
        if(m_p_leptonm[1] < 0) phi_m_tmp = phi_m_tmp + 360.;
        m_phi_dilepton_2 = fabs(phi_p_tmp - phi_m_tmp);
        if (m_phi_dilepton_2 > 180) m_phi_dilepton_2 = 360. - m_phi_dilepton_2;
    }
    }
    }
    // fill dummy value in case of N(muon)=0
  if( nlep_p == 0 && nlep_m != 0 ) {
   for(int k=0; k<4; k++) {
       m_p_leptonp[k] = -9999.0;
       m_p_leptonm[k] = P_M[k];
    }
  }
  if( nlep_m == 0 && nlep_p != 0 ) {
    for(int k=0; k<4; k++) {
    m_p_leptonp[k] = P_P[k];
    m_p_leptonm[k] = -9999.0;
  }
  }
    if( nlep_m == 0 && nlep_p == 0 ) {
    for(int k=0; k<4; k++) {
    m_p_leptonp[k] = -9999.0;
    m_p_leptonm[k] = -9999.0;
  }
  }
  if( nlep_p == 0 || nlep_m == 0 ) {
   for(int k=0; k<4; k++) {
   m_p_dilepton[k] = -9999.0;  
   m_m_recoil = -9999.0;
   m_e_recoil = -9999.0;
   m_pt_dilepton = -9999.0;
   m_m_dimu = -9999.0;
   m_phi_dilepton_2 = 9999.0;
   m_angle_dilepton = -9999.0;
   m_delta_pt = -9999.0;
   m_cos_Z = -9999.0;
  }
  }
}
=======

}

void hig2inv::selectLepton( int nReco, LCCollection* col_Reco) {

	for(int i = 0; i < nReco; i++) {
		ReconstructedParticle *a_Reco = dynamic_cast<EVENT::ReconstructedParticle *>(col_Reco->getElementAt(i));
		if(a_Reco->getCharge()==0) continue;
		lepton_charge = a_Reco->getCharge();
		RecoPID = abs(a_Reco->getType());
		RecoE = a_Reco->getEnergy();
		RecoP[0] = a_Reco->getMomentum()[0];
		RecoP[1] = a_Reco->getMomentum()[1];
		RecoP[2] = a_Reco->getMomentum()[2];
		TLorentzVector curr(RecoP[0], RecoP[1], RecoP[2], RecoE);
	if ( RecoE > RecoEMin && RecoE < RecoEMax) {
        if (lepton_charge > 0.1)FourMom_ChargedP.push_back(curr);
		if (lepton_charge <-0.1)FourMom_ChargedM.push_back(curr);
		if(RecoPID == MuonPID ) {
		   if( lepton_charge >  0.1 )FourMom_LeptonP.push_back( curr );
	       if( lepton_charge < -0.1 )FourMom_LeptonM.push_back( curr );
		}
	}
	}
	m_n_leptonp = FourMom_LeptonP.size();
	m_n_leptonm = FourMom_LeptonM.size();
	m_n_chargedp = FourMom_ChargedP.size();
	m_n_chargedm = FourMom_ChargedM.size();

}

void hig2inv::saveVisible(TLorentzVector m_sum_p_charged,TLorentzVector m_sum_p_neutral) {
	for(int i=0;i<4;i++){
	m_p_visible[i] = m_sum_p_charged[i] + m_sum_p_neutral[i];
    }
   m_energy_visible = ( m_sum_p_charged + m_sum_p_neutral).E();
   m_vis_rec_m = (P_T - m_sum_p_charged - m_sum_p_neutral).M();
   m_vis_rec_e = (P_T - m_sum_p_charged - m_sum_p_neutral).E();
}

void hig2inv::saveRecInfo( std::vector<TLorentzVector> FourMom_LeptonP, std::vector<TLorentzVector> FourMom_LeptonM ) {

    int nlep_p =  FourMom_LeptonP.size();
	int nlep_m =  FourMom_LeptonM.size();
    if (nlep_p > 0 && nlep_m >0){

	for(int i = 0; i < nlep_p; i++) {  
    for(int j = 0; j < nlep_m; j++) {
		P_P = FourMom_LeptonP[i];
		P_M = FourMom_LeptonM[j];	
        float currdimumass = (P_P + P_M).M();
//	if(fabs(currdimumass - ZMass) < MinZThrDis)) { //This file don't exclude background,only record information 
	    MinZThrDis = fabs(currdimumass - ZMass);
	    m_m_dimu = currdimumass;
	// save recil mass
	    currRecoilMass = (P_T - P_P - P_M).M();
	    m_m_recoil = currRecoilMass;
		// save lepton information
	    for(int k=0; k<4; k++) {
			m_p_leptonp[k] = P_P[k];
			m_p_leptonm[k] = P_M[k];
			m_p_dilepton[k] = P_P[k] + P_M[k];
		}
		// save other information
		TLorentzVector ecms(0,0,0,240);
		m_phi_dilepton_1 = fabs(P_P.Phi()- P_M.Phi());
		miss = ecms - m_p_dilepton;
		m_cos_miss = miss.CosTheta();
		m_angle_dilepton = P_P.Angle(P_M.Vect())*180./3.1415926;
		m_pt_dilepton = sqrt(m_p_dilepton[0]*m_p_dilepton[0]+m_p_dilepton[1]*m_p_dilepton[1]);
		m_delta_pt = m_pt_dilepton - m_pt_photon;
		m_cos_Z = m_p_dilepton[2]/sqrt(m_p_dilepton[0]*m_p_dilepton[0]+m_p_dilepton[1]*m_p_dilepton[1]+m_p_dilepton[2]*m_p_dilepton[2]);
		phi_p_tmp = atan2(m_p_leptonp[1],m_p_leptonp[0])*180./3.14159265;
		phi_m_tmp = atan2(m_p_leptonm[1],m_p_leptonm[0])*180./3.14159265;
		if(m_p_leptonp[1] < 0) phi_p_tmp = phi_p_tmp + 360.;
		if(m_p_leptonm[1] < 0) phi_m_tmp = phi_m_tmp + 360.;
		m_phi_dilepton_2 = fabs(phi_p_tmp - phi_m_tmp);
		if (m_phi_dilepton_2 > 180) m_phi_dilepton_2 = 360. - m_phi_dilepton_2;
	}
	}
	}
    // fill dummy value in case of N(muon)=0
  if( nlep_p == 0 && nlep_m != 0 ) {
   for(int k=0; k<4; k++) {
	   m_p_leptonp[k] = -9999.0;
	   m_p_leptonm[k] = P_M[k];
	}
  }
  if( nlep_m == 0 && nlep_p != 0 ) {
	for(int k=0; k<4; k++) {
	m_p_leptonp[k] = P_P[k];
	m_p_leptonm[k] = -9999.0;
  }
  }
    if( nlep_m == 0 && nlep_p == 0 ) {
	for(int k=0; k<4; k++) {
	m_p_leptonp[k] = -9999.0;
	m_p_leptonm[k] = -9999.0;
  }
  }
  if( nlep_p == 0 || nlep_m == 0 ) {
   for(int k=0; k<4; k++) {
   m_p_dilepton[k] = -9999.0;  
   m_m_recoil = -9999.0;
   m_pt_dilepton = -9999.0;
   m_m_dimu = -9999.0;
  }
  }
}
>>>>>>> cepc/master
void hig2inv::saveMCInfo( int nMC, LCCollection* col_MC ) {

    for(int i = 0; i < nMC; i++) {
        a1_MC = dynamic_cast<EVENT::MCParticle *>(col_MC->getElementAt(i));
        tmpPID = a1_MC->getPDG();
        NParent = a1_MC->getParents().size();
        NDaughter = a1_MC->getDaughters().size();
        MCEn = a1_MC->getEnergy();
        saveZdaughter( NParent, NDaughter, tmpPID, MCEn, a1_MC );
        std::vector<MCParticle*> pvec;
        pvec = a1_MC->getParents();
        for( std::vector<MCParticle*>::iterator itr = pvec.begin(); itr != pvec.end(); ++itr ) {
            saveHiggsdaughter( NParent, NDaughter, *itr, tmpPID, MCEn, a1_MC );
            saveNeutrino( NParent, NDaughter, *itr, tmpPID, MCEn );
        }
        if( 0 ) printDecayChain( i , a1_MC );
    }

}

void hig2inv::saveZdaughter( int NParent, int NDaughter, int tmpPID, float MCEn, MCParticle *a1_MC ) {

    if(NParent == 0 && abs(tmpPID) == LeptonID ) { //Including all Z decay
        m_PID_Zdaughter = abs(tmpPID);
        m_p_Zdaughters[3] = MCEn;
        m_p_Zdaughters[0] = a1_MC->getMomentum()[0];
        m_p_Zdaughters[1] = a1_MC->getMomentum()[1];
        m_p_Zdaughters[2] = a1_MC->getMomentum()[2];
        if(tmpPID > 0) {
            m_p_Zdaughterp[0] = a1_MC->getMomentum()[0];
            m_p_Zdaughterp[1] = a1_MC->getMomentum()[1];
            m_p_Zdaughterp[2] = a1_MC->getMomentum()[2];
            m_p_Zdaughterp[3] = MCEn;
        }
        else if(tmpPID < 0) {
            m_p_Zdaughterm[0] = a1_MC->getMomentum()[0];
            m_p_Zdaughterm[1] = a1_MC->getMomentum()[1];
            m_p_Zdaughterm[2] = a1_MC->getMomentum()[2];
            m_p_Zdaughterm[3] = MCEn;
        }
    }

}

void hig2inv::saveHiggsdaughter( int NParent, int NDaughter, MCParticle *itr, int tmpPID, float MCEn, MCParticle *a1_MC ) {

    if(abs(tmpPID) == ZPID && NParent == 1 && itr->getPDG() == HiggsPID ) { //Higgs
        m_n_Higgsdaughter = NDaughter;
        m_p_Higgsdaughters[3] = MCEn;
        m_p_Higgsdaughters[0] = a1_MC->getMomentum()[0];
        m_p_Higgsdaughters[1] = a1_MC->getMomentum()[1];
        m_p_Higgsdaughters[2] = a1_MC->getMomentum()[2];
        for(int i = 0; i < NDaughter; i++) { //NDaughter
            MCParticle *b_MC = a1_MC->getDaughters()[i];
            m_PID_HiggsDaughter = b_MC->getPDG();
            m_PID_Higgsdaughter[DIndex] = m_PID_HiggsDaughter;
            if(m_PID_HiggsDaughter < 6 || m_PID_HiggsDaughter == MuonPID || m_PID_HiggsDaughter == ElectronPID || m_PID_HiggsDaughter == TauPID ) {
                if(m_PID_HiggsDaughter > 0) {
                    m_p_Higgsdaughter1[3] = b_MC->getEnergy();
                    m_p_Higgsdaughter1[0] = b_MC->getMomentum()[0];
                    m_p_Higgsdaughter1[1] = b_MC->getMomentum()[1];
                    m_p_Higgsdaughter1[2] = b_MC->getMomentum()[2];
                }
                else if(m_PID_HiggsDaughter < 0) {
                    m_p_Higgsdaughter2[3] = b_MC->getEnergy();
                    m_p_Higgsdaughter2[0] = b_MC->getMomentum()[0];
                    m_p_Higgsdaughter2[1] = b_MC->getMomentum()[1];
                    m_p_Higgsdaughter2[2] = b_MC->getMomentum()[2];
                }
            }
            else if(DIndex == 0) {
                m_p_Higgsdaughter1[3] = b_MC->getEnergy();
                m_p_Higgsdaughter1[0] = b_MC->getMomentum()[0];
                m_p_Higgsdaughter1[1] = b_MC->getMomentum()[1];
                m_p_Higgsdaughter1[2] = b_MC->getMomentum()[2];
                DIndex = 1;
            }
            else if(DIndex == 1) {
                m_p_Higgsdaughter2[3] = b_MC->getEnergy();
                m_p_Higgsdaughter2[0] = b_MC->getMomentum()[0];
                m_p_Higgsdaughter2[1] = b_MC->getMomentum()[1];
                m_p_Higgsdaughter2[2] = b_MC->getMomentum()[2];
            }
            m_PID_HiggsDaughter = abs(m_PID_HiggsDaughter);
        }
    }

}

void hig2inv::saveNeutrino( int NParent, int NDaughter, MCParticle *itr, int tmpPID, float MCEn ) {

    if(NParent ==1 && NDaughter == 0) {
        if( itr->getPDG() == MuonPID && ( abs(tmpPID) == NeutrinoEPID || abs(tmpPID) == NeutrinoMuonPID || abs(tmpPID) == NeutrinoTauPID ) ) {
            m_n_neutrino++;
            m_energy_neutrino = MCEn;
        }
    }

}

void hig2inv::printDecayChain( int MCParticleID, MCParticle *mcp ) {
    std::vector<MCParticle*> pvec, dvec;
    pvec = mcp->getParents();
    dvec = mcp->getDaughters();
    
    // Display PID info. 
    printMCinfo( MCParticleID, 1, mcp, pvec, dvec );
    
    // Follow daughter's information as well
    if( 1 ){
        for( std::vector<MCParticle*>::iterator itr = dvec.begin(); itr != dvec.end(); ++itr ) {
            std::vector<MCParticle*> p_dvec, d_dvec;
            p_dvec = (*itr)->getParents();
            d_dvec = (*itr)->getDaughters();
            int dummy_MCParticleID = -1;
            printMCinfo( dummy_MCParticleID, 2, *itr, p_dvec, d_dvec );
        }
    }
}

void hig2inv::printMCinfo( int MCParticleID, int flag, MCParticle *mcp, std::vector<MCParticle*> pvec, std::vector<MCParticle*> dvec ) {

    int status      =  mcp->getGeneratorStatus();
    int pdgid       =  mcp->getPDG();
    int nparents    =  pvec.size();
    int ndaughters  =  dvec.size();
    
    std::vector<int> p_pid;
    std::vector<int> d_pid;
    
    for( std::vector<MCParticle*>::iterator itr = pvec.begin(); itr != pvec.end(); ++itr ) p_pid.push_back( (*itr)->getPDG() );
    for( std::vector<MCParticle*>::iterator itr = dvec.begin(); itr != dvec.end(); ++itr ) d_pid.push_back( (*itr)->getPDG() );
    
    if( flag == 1 )std::cout << " MCParticleID = " <<  MCParticleID ;
    if( flag == 2 )std::cout << "           " << "    " ;                    // daughther info.
    std::cout << ", status=" << status << " : nParents = " << nparents << " : " ;
    for( std::vector<int>::iterator itr = p_pid.begin(); itr != p_pid.end(); ++itr ) std::cout << *itr << " " ;
    if( p_pid.size() == 0 ) {
        std::cout << "     " << " " ;
        std::cout << "     " << " " ;
    }
    if( p_pid.size() == 1 ) {
        std::cout << "     " << " " ;
    }
    std::cout << " : pdgid = " << pdgid << " : nDaughters = " << ndaughters << " : " ;
    for( std::vector<int>::iterator itr = d_pid.begin(); itr != d_pid.end(); ++itr ) std::cout << *itr << ", " ;
    std::cout << std::endl;

}
