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
		int m_n_gamma, m_n_charged, m_n_leptonp, m_n_leptonm, m_n_chargedp, m_n_chargedm, m_n_Higgsdaughter, m_n_neutrino;
		unsigned int m_event;
		float m_p_neutral[4], m_p_photon[4], m_p_charged[4], m_p_leptonp[4], m_p_leptonm[4], m_p_dilepton[4], m_p_Zdaughters[4], m_p_Zdaughterp[4], m_p_Zdaughterm[4], m_p_Higgsdaughters[4], m_p_Higgsdaughter1[4],m_p_Higgsdaughter2[4];
		float m_m_visible, m_m_recoil;
		float m_pt_photon, m_pt_dilepton;
		float RecoE;
		float RecoP[3];
		int m_event_type;
		float m_energy_visible, m_energy_neutrino;
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

		TLorentzVector P_P, P_M, P_T, miss;
		std::vector<TLorentzVector> FourMom_LeptonP, FourMom_LeptonM, FourMom_ChargedP, FourMom_ChargedM, FourMom_Charged, FourMom_Gamma, CandiP, CandiM;

		void book_tree();
		void saveNeutral( int nReco, LCCollection* colReco );
		void savePhoton( int nReco, LCCollection* colReco );
		void selectCharged( int nReco, LCCollection* colReco );
		void selectLepton( float RecoE, int RecoPID, TLorentzVector curr, ReconstructedParticle *a_Reco );
		void saveEventType( int m_n_leptonp, int m_n_leptonm, int m_n_chargedp, int m_n_chargedm );
		void saveEvent( int NCandiP, int NCandiM, std::vector<TLorentzVector> CandiP, std::vector<TLorentzVector> CandiM, float m_pt_photon );
		void saveRecInfo( TLorentzVector P_P, TLorentzVector P_M, float m_pt_photon );
		void saveMCInfo( int nMC, LCCollection* col_MC );
		void saveZdaughter( int NParent, int NDaughter, int tmpPID, float MCEn, MCParticle *a1_MC );
		void saveHiggsdaughter( int NParent, int NDaughter, MCParticle *itr, int tmpPID, float MCEn, MCParticle *a1_MC );
		void saveNeutrino( int NParent, int NDaughter, MCParticle *a1_MC, int tmpPID, float MCEn );
		void printDecayChain( int MCParticleID, MCParticle *mcp );
		void printMCinfo( int MCParticleID, int flag, MCParticle *mcp, std::vector<MCParticle*> pvec, std::vector<MCParticle*> dvec );
		void variable_init();

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

	RecoEMax=100;
		registerProcessorParameter( "RecoEMax" ,
			"Maximum energy of reconstructed particles." ,
			RecoEMax ,
			RecoEMax);

	RecoEMin=10; 
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
			saveEventType( m_n_leptonp, m_n_leptonm, m_n_chargedp, m_n_chargedm );

			NCandiP = CandiP.size();
			NCandiM = CandiM.size();

			saveEvent( NCandiP, NCandiM, CandiP, CandiM, m_pt_photon );
			saveMCInfo( nMC, col_MC );

			m_tree->Fill();
		}
		catch (lcio::DataNotAvailableException err) { }
	}

}	

void hig2inv::end() {

	if (m_tree) {
		TFile *tree_file = m_tree->GetCurrentFile(); //just in case we switched to a new file
		tree_file->Write();
		delete tree_file;
	}

}

void hig2inv::book_tree() {

	m_file=new TFile(FileName.c_str(),(OverWrite ? "RECREATE" : "UPDATE"));
	if (!m_file->IsOpen()) {
		delete m_file;
		m_file=new TFile(FileName.c_str(),"NEW");
	}
	m_tree = new TTree(TreeName.c_str(),TreeName.c_str());
	m_tree->Branch("m_event",&m_event,"m_event/I");
	m_tree->Branch("m_event_type",  &m_event_type,  "m_event_type/I");

	m_tree->Branch("m_p_neutral", m_p_neutral, "m_p_neutral[4]/F");
	m_tree->Branch("m_p_photon", m_p_photon, "m_p_photon[4]/F");
	m_tree->Branch("m_p_leptonp",  m_p_leptonp,  "m_p_lepton[4]/F");
	m_tree->Branch("m_p_leptonm",  m_p_leptonm,  "m_p_lepton[4]/F");
	m_tree->Branch("m_p_dilepton",  m_p_dilepton,  "m_p_dilepton[4]/F");
	m_tree->Branch("m_p_charged",  m_p_charged,  "m_p_charged[4]/F");
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

	m_tree->Branch("m_m_visible",  &m_m_visible,  "m_m_visible/F");
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

}

void hig2inv::variable_init() {

	m_n_charged = 0;
	m_n_leptonp = 0;
	m_n_leptonm = 0;
	m_n_chargedp = 0;
	m_n_chargedm = 0;
	m_n_gamma = 0;
	m_n_neutrino = 0;
	m_n_Higgsdaughter = 0;
	m_event_type = -1;
	m_energy_neutrino = 0.;
	// m_m_visible = 0.;
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
	TLorentzVector beamp(0,0,125.0,125.0);
	TLorentzVector beamm(0,0,-125.0,125.0);
	scale1 = (gRandom->Gaus(1, 0.0024));
	scale2 = (gRandom->Gaus(1, 0.0024));
	P_T=scale1*beamp+scale2*beamm;
	for(int i=0; i<4; i++) {
		m_p_neutral[i] = 0;
		m_p_photon[i] = 0;
		m_p_charged[i] = 0;
		m_p_leptonp[i] = 0;
		m_p_leptonm[i] = 0;
		m_p_dilepton[i] = 0;
		m_p_Zdaughters[i] = 0;
		m_p_Zdaughterp[i] = 0;
		m_p_Zdaughterm[i] =0;
		m_p_Higgsdaughters[i] = 0;
		m_p_Higgsdaughter1[i] = 0;
		m_p_Higgsdaughter2[i] = 0;
	}                   
	FourMom_LeptonM.clear();
	FourMom_LeptonP.clear();
	FourMom_Gamma.clear();
	FourMom_Charged.clear();
	FourMom_ChargedP.clear();
	FourMom_ChargedM.clear();
	CandiP.clear();
	CandiM.clear();

}

void hig2inv::saveNeutral( int nReco, LCCollection* col_Reco ) {

	for(int i = 0; i < nReco; i++) {
		ReconstructedParticle *a_Reco = dynamic_cast<EVENT::ReconstructedParticle *>(col_Reco->getElementAt(i));
		if(a_Reco->getCharge()!=0) continue;
		m_p_neutral[3] = a_Reco->getEnergy();
		m_p_neutral[0] = a_Reco->getMomentum()[0];
		m_p_neutral[1] = a_Reco->getMomentum()[1];
		m_p_neutral[2] = a_Reco->getMomentum()[2];
	}

}

void hig2inv::savePhoton( int nReco, LCCollection* col_Reco ) {

	float photone=50;
	for(int i = 0; i < nReco; i++) {
		ReconstructedParticle *a_Reco = dynamic_cast<EVENT::ReconstructedParticle *>(col_Reco->getElementAt(i));
		if(a_Reco->getCharge()!=0) continue;
		if(a_Reco->getType()!=PhotonPID) continue;
		if(fabs(a_Reco->getMomentum()[2]/a_Reco->getEnergy())>0.995) continue; // acceptance of the detector
		if(a_Reco->getEnergy()>photone) {
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

}

void hig2inv::selectCharged( int nReco, LCCollection* col_Reco ) {

	for(int i = 0; i < nReco; i++) {
		ReconstructedParticle *a_Reco = dynamic_cast<EVENT::ReconstructedParticle *>(col_Reco->getElementAt(i));
		if(a_Reco->getCharge()==0) continue;
		RecoPID = a_Reco->getType();
		RecoE = a_Reco->getEnergy();
		// if ( RecoE > RecoEMin && RecoE < RecoEMax && ( abs(RecoPID) == ElectronPID || abs(RecoPID) == MuonPID || abs(RecoPID) == TauPID ) ) { 
		if ( RecoE > RecoEMin && RecoE < RecoEMax && abs(RecoPID) == MuonPID ) {
		// if ( RecoE > RecoEMin && RecoE < RecoEMax ) {
			RecoP[0] = a_Reco->getMomentum()[0];
			RecoP[1] = a_Reco->getMomentum()[1];
			RecoP[2] = a_Reco->getMomentum()[2];
			TLorentzVector curr(RecoP[0], RecoP[1], RecoP[2], RecoE);
			FourMom_Charged.push_back(curr);
			for(int j = 0; j < 4; j++) {
				// m_p_charged[j] += curr[j];
				m_p_charged[j] = curr[j];
			}
			selectLepton( RecoE, RecoPID, curr, a_Reco );
		}
	}
	m_n_charged = FourMom_Charged.size();
	m_n_leptonp = FourMom_LeptonP.size();
	m_n_leptonm = FourMom_LeptonM.size();
	m_n_chargedp = FourMom_ChargedP.size();
	m_n_chargedm = FourMom_ChargedM.size();

}

void hig2inv::selectLepton( float RecoE, int RecoPID, TLorentzVector curr, ReconstructedParticle *a_Reco ) {

	if( RecoE > RecoEMin && RecoE < RecoEMax ) {  //0.4*sqrt(s) 
		if(abs(RecoPID) == LeptonID ) {
			if(RecoPID == LeptonID ) { 
				FourMom_LeptonM.push_back(curr);
			}
			else {
				FourMom_LeptonP.push_back(curr);
			}
		}
		else if( a_Reco->getCharge() > 0.5 ) {
			FourMom_ChargedP.push_back(curr);
		}
		else if( a_Reco->getCharge() < -0.5 ) {
			FourMom_ChargedM.push_back(curr);
		}
	}

}

void hig2inv::saveEventType( int m_n_leptonp, int m_n_leptonm, int m_n_chargedp, int m_n_chargedm ) {

	if( m_n_leptonp && m_n_leptonm ) {
		m_event_type = 0;
		CandiP = FourMom_LeptonP;
		CandiM = FourMom_LeptonM;
	}
	else if( m_n_leptonp == 0 && m_n_chargedp && m_n_leptonm ) {
		m_event_type = 1;
		CandiP = FourMom_ChargedP;
		CandiM = FourMom_LeptonM;
	}
	else if( m_n_leptonm == 0 && m_n_chargedm && m_n_leptonp ) {
		m_event_type = 2;
		CandiM = FourMom_ChargedM;
		CandiP = FourMom_LeptonP;
	}
	else if( m_n_leptonm == 0 && m_n_chargedm && m_n_chargedp && m_n_leptonp == 0 ) {
		m_event_type = 3;
		CandiM = FourMom_ChargedM;
		CandiP = FourMom_ChargedP;
	}

}

void hig2inv::saveEvent( int NCandiP, int NCandiM, std::vector<TLorentzVector> CandiP, std::vector<TLorentzVector> CandiM, float m_pt_photon ) {

	if( NCandiP > 0 && NCandiM > 0 && m_event_type == 0 ) {
		for(int i = 0; i < NCandiP; i++) {
			P_P = CandiP[i];
			for(int j = 0; j < NCandiM; j++) {
				P_M = CandiM[j];
				saveRecInfo( P_P, P_M, m_pt_photon );
			}
		}
	}

}

void hig2inv::saveRecInfo( TLorentzVector P_P, TLorentzVector P_M, float m_pt_photon ) {

	currVisMass = (P_P + P_M).M();
	currVisEnergy = P_P[3] + P_M[3];
	if((m_event_type == 0) && (fabs(currVisMass - ZMass) < MinZThrDis)) {
		MinZThrDis = fabs(currVisMass - ZMass);
		m_m_visible = currVisMass;
		m_energy_visible = currVisEnergy;
		// save recil mass
		currRecoilMass = (P_T - P_P - P_M).M();
		m_m_recoil = currRecoilMass;
		// save lepton information
		for(int i=0; i<4; i++) {
			m_p_leptonp[i] = P_P[i];
			m_p_leptonm[i] = P_M[i];
			m_p_dilepton[i] = m_p_leptonp[i] + m_p_leptonm[i];
		}
		// save other information
		TLorentzVector ecms(0,0,0,250);
		m_phi_dilepton_1 = fabs(P_P.Phi()-P_M.Phi());
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
