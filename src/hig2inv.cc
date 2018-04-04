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
#include <values.h>
#include <string>
#include <iostream>
#include <TFile.h> 
#include <TTree.h>
#include <TVector3.h>
#include <TRandom.h>
#include <sstream>              
#include <cmath>
#include <vector>
#include <TMath.h>
#include "TLorentzVector.h"
#include <stdexcept>
#include <Rtypes.h>

class hig2inv  : public marlin::Processor {
	public:

		Processor*  newProcessor() { return new hig2inv ; }

		hig2inv();

		~hig2inv() {};

		void init();

		void processEvent( LCEvent * evt );

		void end();

	private:
		void book_tree();
		std::string FileName;
		std::string TreeName;
		int LeptonID;
		int OverWrite;
		LCCollection* col_MC;
		LCCollection* col_Reco;
		MCParticle *a1_MC;
		int nMC, nReco, NCandiP, NCandiM;
		TFile *m_file;
		TTree *m_tree;
		int m_n_charged, m_n_electronp, m_n_electronm, m_n_chargedp, m_n_chargedm;
		unsigned int m_event;
		float m_p_neutral[4], m_p_photon[4], m_p_charged[4], m_p_electronp[4], m_p_electronm[4], m_p_dielectron[4];
		float m_p_recoil[4], m_p_Higgs[4];
		float m_m_Higgs;
		float m_pt_photon;
		int RecoPID;
		float RecoE;
		float RecoP[3];
		int m_event_type;
		float m_m_visble;
		float m_m_recoil[11];
		float spreadfactor[11];
		float scale1, scale2;
		float currVisMass, currRecoilMass;
		float MinZThrDis;
		float m_phi_dielectron_1;
		float phi_p_tmp, phi_m_tmp;
		float m_cos_miss;
		float m_angle_dielectron;
		float m_pt_Z;
		float m_delta_pt;
		float m_cos_Z;
		float m_phi_dielectron_2;
                int tmpPID;
                int NParent; 
                int NDaughter;
		int DIndex;
                float MCEn;
		int m_PID_Zdaughter;
		float m_pz_Zdaughters[4], m_pz_Zdaughterp[4], m_pz_Zdaughterm[4];
		int m_n_Higgsdaughter, m_PID_HiggsDaughter, m_PID_Higgsdaughter[2], m_n_Zneutrino;
		float m_p_Higgsdaughters[4], m_p_Higgsdaughter1[4],m_p_Higgsdaughter2[4];
		int m_n_neutrino;
		float m_energy_neutrino;
		float m_m_Z;
		//int m_n_event;

		TLorentzVector P_P, P_M, P_T[11];
		TLorentzVector miss;
		std::vector<TLorentzVector> FourMom_ElectronP;
		std::vector<TLorentzVector> FourMom_ElectronM;
		std::vector<TLorentzVector> FourMom_ChargedP;
		std::vector<TLorentzVector> FourMom_ChargedM;
		std::vector<TLorentzVector> CandiP;
		std::vector<TLorentzVector> CandiM;

		void saveNeutral( int nReco, LCCollection* colReco );
		void savePhoton( int nReco, LCCollection* colReco );
		void selectCharged( int nReco, LCCollection* colReco );
		void selectElectron( float RecoE, int RecoPID, TLorentzVector curr, ReconstructedParticle *a_Reco );
		void saveEventType( int m_n_electronp, int m_n_electronm, int m_n_chargedp, int m_n_chargedm );
		void saveEvent( int NCandiP, int NCandiM, std::vector<TLorentzVector> CandiP, std::vector<TLorentzVector> CandiM, float m_pt_photon );
		void saveRecInfo( TLorentzVector P_P, TLorentzVector P_M, float m_pt_photon );
		void saveHiggsMass( float *m_p_neutral, float *m_p_charged, float *m_p_dielectron );
		void saveMCInfo( int nMC, LCCollection* col_MC );
		void saveZdaughter( int NParent, int NDaughter, int tmpPID, float MCEn, MCParticle *a1_MC );
		void saveHiggsdaughter( int NParent, int NDaughter, int tmpPID, float MCEn, MCParticle *a1_MC );
		void saveNeutrino( int NDaughter, int tmpPID, float MCEn );
		void variable_init();

};

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

	LeptonID=13;
		registerProcessorParameter( "LeptonIDTag" ,
			"Lepton ID that will be used in this analysis." ,
			LeptonID ,
			LeptonID);
		
	OverWrite=0;
			registerProcessorParameter( "OverwriteFile" ,
			"If zero an already existing file will not be overwritten." ,
			OverWrite ,
			OverWrite);

}

void hig2inv::init() {

	book_tree();
	variable_init();

}

void hig2inv::processEvent( LCEvent * evt ) {	

	if(evt){

		try{

			col_MC = evt->getCollection( "MCParticle" );
			col_Reco = evt->getCollection( "ArborPFOs" );

			nMC = col_MC->getNumberOfElements();
			nReco = col_Reco->getNumberOfElements();

			m_event=evt->getEventNumber();

                        saveNeutral( nReco, col_Reco );
			savePhoton( nReco, col_Reco );
			selectCharged( nReco, col_Reco );

			m_n_electronp = FourMom_ElectronP.size();
			m_n_electronm = FourMom_ElectronM.size();
			m_n_chargedp = FourMom_ChargedP.size();
			m_n_chargedm = FourMom_ChargedM.size();

			saveEventType( m_n_electronp, m_n_electronm, m_n_chargedp, m_n_chargedm );

			NCandiP = CandiP.size();
			NCandiM = CandiM.size();

			saveEvent( NCandiP, NCandiM, CandiP, CandiM, m_pt_photon );
			saveHiggsMass( m_p_neutral, m_p_charged, m_p_dielectron );
			saveMCInfo( nMC, col_MC );

			m_tree->Fill();

			//m_n_event++;

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
	m_tree->Branch("event",&m_event,"event/I");
	m_tree->Branch("P_allNeutral", m_p_neutral, "m_p_neutral[4]/F");
	m_tree->Branch("P_Photon", m_p_photon, "m_p_photon[4]/F");
	m_tree->Branch("Pt_Photon", &m_pt_photon, "m_pt_photon/F");
	m_tree->Branch("N_Charged",  &m_n_charged,  "m_n_charged/I");
	m_tree->Branch("P_allCharged",  m_p_charged,  "m_p_charged[4]/F");
	m_tree->Branch("N_ElectronPlus",  &m_n_electronp,  "m_n_electronp/I");
	m_tree->Branch("N_ElectronMinus",  &m_n_electronm,  "m_n_electronm/I");
	m_tree->Branch("N_ChargedPlus",  &m_n_chargedp,  "m_n_chargedp/I");
	m_tree->Branch("N_ChargedMinus",  &m_n_chargedm,  "m_n_chargedm/I");
	m_tree->Branch("Event_Type",  &m_event_type,  "m_event_type/I");
	m_tree->Branch("Mass_Visble",  &m_m_visble,  "m_m_visble/F");
	m_tree->Branch("Mass_Recoil",  m_m_recoil,  "m_m_recoil[11]/F");
	m_tree->Branch("P_ElectronP",  m_p_electronp,  "m_p_electron[4]/F");
	m_tree->Branch("P_ElectronM",  m_p_electronm,  "m_p_electron[4]/F");
	m_tree->Branch("P_DiElectron",  m_p_dielectron,  "m_p_dielectron[4]/F");
	m_tree->Branch("Phi_DiElectron_1",  &m_phi_dielectron_1,  "m_phi_dielectron_1/F");
	m_tree->Branch("Phi_DiElectron_2",  &m_phi_dielectron_2,  "m_phi_dielectron_2/F");
	m_tree->Branch("Cos_Miss",  &m_cos_miss,  "m_cos_miss/F");
	m_tree->Branch("Angle_DiElectron",  &m_angle_dielectron,  "m_angle_dielectron/F");
	m_tree->Branch("Pt_Z",  &m_pt_Z,  "m_pt_Z/F");
	m_tree->Branch("Delta_Pt",  &m_delta_pt,  "m_delta_pt/F");
	m_tree->Branch("Cos_Z",  &m_cos_Z,  "m_cos_Z/F");
	m_tree->Branch("P_allRecoil",  m_p_recoil,  "m_p_recoil[4]/F");
	m_tree->Branch("P_Higgs",  m_p_Higgs,  "m_p_Higgs[4]/F");
	m_tree->Branch("Mass_Higgs",  &m_m_Higgs,  "m_m_Higgs/F");
	m_tree->Branch("PID_ZDaughter",  &m_PID_Zdaughter,  "m_PID_Zdaughter/I");
	m_tree->Branch("Pz_ZDaughters",  m_pz_Zdaughters,  "m_pz_Zdaughters[4]/F");
	m_tree->Branch("Pz_ZDaughterp",  m_pz_Zdaughterp,  "m_pz_Zdaughterp[4]/F");
	m_tree->Branch("Pz_ZDaughterm",  m_pz_Zdaughterm,  "m_pz_Zdaughterm[4]/F");
	m_tree->Branch("N_HiggsDaughter",  &m_n_Higgsdaughter,  "m_n_Higgsdaughter/I");
	m_tree->Branch("P_HiggsDaughters",  m_p_Higgsdaughters,  "m_p_Higgsdaughters[4]/F");
	m_tree->Branch("PID_HiggsDaughter",  &m_PID_HiggsDaughter,  "m_PID_HiggsDaughter/I");
	m_tree->Branch("PID_Higgsdaughter",  m_PID_Higgsdaughter,  "m_PID_Higgsdaughter[2]/I");
	m_tree->Branch("P_HiggsDaughter1",  m_p_Higgsdaughter1,  "m_p_Higgsdaughter1[4]/F");
	m_tree->Branch("P_HiggsDaughter2",  m_p_Higgsdaughter2,  "m_p_Higgsdaughter2[4]/F");
	m_tree->Branch("N_ZNeutrino",  &m_n_Zneutrino,  "m_n_Zneutrino/I");
	m_tree->Branch("N_Neutrino",  &m_n_neutrino,  "m_n_neutrino/I");
	m_tree->Branch("Energy_Neutrino",  &m_energy_neutrino,  "m_energy_neutrino/F");
	m_tree->Branch("Mass_Z",  &m_m_Z,  "m_m_Z/F");
	//m_tree->Branch("N_Event",  &m_n_event,  "m_n_event/I");

}

void hig2inv::variable_init() {

	m_n_charged = 0;
	m_n_electronp = 0;
	m_n_electronm = 0;
	m_n_chargedp = 0;
	m_n_chargedm = 0;
	m_n_Zneutrino = 0;
	m_n_neutrino = 0;
	m_event_type = -1;
	MinZThrDis = 1.0E10;

	TLorentzVector beamp(0,0,125.0,125.0);
	TLorentzVector beamm(0,0,-125.0,125.0);
	float spreadfactor[11]={0.0,0.0004,0.0008,0.0012,0.0016,0.0020,0.0024,0.0028,0.0032,0.0036,0.0040};

	for(int i=0; i<11; i++) {

		scale1 = (gRandom->Gaus(1, spreadfactor[i]));
		scale2 = (gRandom->Gaus(1, spreadfactor[i]));
		P_T[i]=scale1*beamp+scale2*beamm;

	}

	DIndex = 0;

}

void hig2inv::saveNeutral( int nReco, LCCollection* col_Reco ) {

	for(int i = 0; i < nReco; i++) {

		ReconstructedParticle *a_Reco = dynamic_cast<EVENT::ReconstructedParticle *>(col_Reco->getElementAt(i));
		if(a_Reco->getCharge()!=0) continue;
		m_p_neutral[3] += a_Reco->getEnergy();
		m_p_neutral[0] += a_Reco->getMomentum()[0];
		m_p_neutral[1] += a_Reco->getMomentum()[1];
		m_p_neutral[2] += a_Reco->getMomentum()[2];

	}

}

void hig2inv::savePhoton( int nReco, LCCollection* col_Reco ) {

	float photone=-1.;
	for(int i = 0; i < nReco; i++) {

		ReconstructedParticle *a_Reco = dynamic_cast<EVENT::ReconstructedParticle *>(col_Reco->getElementAt(i));
		if(a_Reco->getType()!=22) continue;
		//if(fabs(a_Reco->getMomentum()[2]/a_Reco->getEnergy())>0.995) continue; // acceptance of the detector
		if(a_Reco->getEnergy()>photone) {

			photone = a_Reco->getEnergy();
			m_p_photon[3] = a_Reco->getEnergy();
			m_p_photon[0] = a_Reco->getMomentum()[0];
			m_p_photon[1] = a_Reco->getMomentum()[1];
			m_p_photon[2] = a_Reco->getMomentum()[2];
			m_pt_photon = sqrt(m_p_photon[0]*m_p_photon[0]+m_p_photon[1]*m_p_photon[1]);

		}
	}

}

void hig2inv::selectCharged( int nReco, LCCollection* col_Reco ) {

	for(int i = 0; i < nReco; i++) {

		ReconstructedParticle *a_Reco = dynamic_cast<EVENT::ReconstructedParticle *>(col_Reco->getElementAt(i));
		if(a_Reco->getCharge()==0) continue;
		RecoPID = a_Reco->getType();
		RecoE = a_Reco->getEnergy();
		RecoP[0] = a_Reco->getMomentum()[0];
		RecoP[1] = a_Reco->getMomentum()[1];
		RecoP[2] = a_Reco->getMomentum()[2];

		TLorentzVector curr(RecoP[0], RecoP[1], RecoP[2], RecoE);

		if(RecoE<2.0) continue;
		m_n_charged++;

		for(int j = 0; j < 4; j++) {

			m_p_charged[j] += curr[j];

		}

		selectElectron( RecoE, RecoPID, curr, a_Reco );

	}

}

void hig2inv::selectElectron( float RecoE, int RecoPID, TLorentzVector curr, ReconstructedParticle *a_Reco ) {

	if( RecoE > 10 && RecoE < 100 ) {  //0.4*sqrt(s) 

		if(abs(RecoPID) == LeptonID ) { //Put by hand... guess enough

			if(RecoPID == LeptonID ) { //Got swapped...gosh!

				FourMom_ElectronM.push_back(curr);

			}

			else {

				FourMom_ElectronP.push_back(curr);

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

void hig2inv::saveEventType( int m_n_electronp, int m_n_electronm, int m_n_chargedp, int m_n_chargedm ) {

	if( m_n_electronp && m_n_electronm ) {

		m_event_type = 0;
		CandiP = FourMom_ElectronP;
		CandiM = FourMom_ElectronM;

	}

	else if( m_n_electronp == 0 && m_n_chargedp && m_n_electronm ) {

		m_event_type = 1;
		CandiP = FourMom_ChargedP;
		CandiM = FourMom_ElectronM;

	}

	else if( m_n_electronm == 0 && m_n_chargedm && m_n_electronp ) {

		m_event_type = 2;
		CandiM = FourMom_ChargedM;
		CandiP = FourMom_ElectronP;

	}

	else if( m_n_electronm == 0 && m_n_chargedm && m_n_chargedp && m_n_electronp == 0 ) {

		m_event_type = 3;
		CandiM = FourMom_ChargedM;
		CandiP = FourMom_ChargedP;

	}

}

void hig2inv::saveEvent( int NCandiP, int NCandiM, std::vector<TLorentzVector> CandiP, std::vector<TLorentzVector> CandiM, float m_pt_photon ) {

	if( NCandiP > 0 && NCandiM > 0 ) {

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
	if(fabs(currVisMass - 91.2) < MinZThrDis) {

		MinZThrDis = fabs(currVisMass - 91.2);
		m_m_visble = currVisMass;

		// save recil mass
		for(int i=0; i<11; i++) {

			currRecoilMass = (P_T[i] - P_P - P_M).M();
			m_m_recoil[i] = currRecoilMass;

		}

		// save electron information
		for(int i=0; i<4; i++) {

			m_p_electronp[i] = P_P[i];
			m_p_electronm[i] = P_M[i];
			m_p_dielectron[i] = m_p_electronp[i] + m_p_electronm[i];

		}

		// save other information
		TLorentzVector ecms(0,0,0,250);
		m_phi_dielectron_1 = fabs(P_P.Phi()-P_M.Phi());
		miss = ecms - m_p_dielectron;
		m_cos_miss = miss.CosTheta();
		m_angle_dielectron = P_P.Angle(P_M.Vect())*180./3.1415926;
		m_pt_Z = sqrt(m_p_dielectron[0]*m_p_dielectron[0]+m_p_dielectron[1]*m_p_dielectron[1]);
		m_delta_pt = m_pt_Z - m_pt_photon;
		m_cos_Z = m_p_dielectron[2]/sqrt(m_p_dielectron[0]*m_p_dielectron[0]+m_p_dielectron[1]*m_p_dielectron[1]+m_p_dielectron[2]*m_p_dielectron[2]);
		phi_p_tmp = atan2(m_p_electronp[1],m_p_electronp[0])*180./3.14159265;
		phi_m_tmp = atan2(m_p_electronm[1],m_p_electronm[0])*180./3.14159265;
		if(m_p_electronp[1] < 0) phi_p_tmp = phi_p_tmp + 360.;
		if(m_p_electronm[1] < 0) phi_m_tmp = phi_m_tmp + 360.;
		m_phi_dielectron_2 = fabs(phi_p_tmp - phi_m_tmp);
		if (m_phi_dielectron_2 > 180) m_phi_dielectron_2 = 360. - m_phi_dielectron_2;

	}

}

void hig2inv::saveHiggsMass( float *m_p_neutral, float *m_p_charged, float *m_p_dielectron ) {

	for(int i = 0; i < 4; i++) {

		m_p_recoil[i] = m_p_neutral[i] + m_p_charged[i];
		m_p_Higgs[i] = m_p_recoil[i] - m_p_dielectron[i];

	}

	m_m_Higgs = sqrt( m_p_Higgs[3] * m_p_Higgs[3] - m_p_Higgs[0] * m_p_Higgs[0] - m_p_Higgs[1] * m_p_Higgs[1] - m_p_Higgs[2] * m_p_Higgs[2] );

}

void hig2inv::saveMCInfo( int nMC, LCCollection* col_MC ) {

	for(int i = 0; i < nMC; i++) {

		a1_MC = dynamic_cast<EVENT::MCParticle *>(col_MC->getElementAt(i));
		tmpPID = a1_MC->getPDG();
		NParent = a1_MC->getParents().size();
		NDaughter = a1_MC->getDaughters().size();
		MCEn = a1_MC->getEnergy();

		saveZdaughter( NParent, NDaughter, tmpPID, MCEn, a1_MC );
		saveHiggsdaughter( NParent, NDaughter, tmpPID, MCEn, a1_MC );
		saveNeutrino( NDaughter, tmpPID, MCEn );

	}

	m_m_Z = sqrt(m_pz_Zdaughters[3]*m_pz_Zdaughters[3] - m_pz_Zdaughters[0]*m_pz_Zdaughters[0]- m_pz_Zdaughters[1]*m_pz_Zdaughters[1]- m_pz_Zdaughters[2]*m_pz_Zdaughters[2]);

}

void hig2inv::saveZdaughter( int NParent, int NDaughter, int tmpPID, float MCEn, MCParticle *a1_MC ) {

	if(NParent == 0 && NDaughter == 1 && abs(tmpPID) < 20 ) { //Including all Z decay

		m_PID_Zdaughter = abs(tmpPID);
		m_pz_Zdaughters[3] += MCEn;
		m_pz_Zdaughters[0] += a1_MC->getMomentum()[0];
		m_pz_Zdaughters[1] += a1_MC->getMomentum()[1];
		m_pz_Zdaughters[2] += a1_MC->getMomentum()[2];

		if( m_PID_Zdaughter < 6 || m_PID_Zdaughter == 13 || m_PID_Zdaughter == 11 || m_PID_Zdaughter == 15) {

			if(tmpPID > 0) {

				m_pz_Zdaughterp[0] = a1_MC->getMomentum()[0];
				m_pz_Zdaughterp[1] = a1_MC->getMomentum()[1];
				m_pz_Zdaughterp[2] = a1_MC->getMomentum()[2];
				m_pz_Zdaughterp[3] = MCEn;

			}

			else if(tmpPID < 0) {

				m_pz_Zdaughterm[0] = a1_MC->getMomentum()[0];
				m_pz_Zdaughterm[1] = a1_MC->getMomentum()[1];
				m_pz_Zdaughterm[2] = a1_MC->getMomentum()[2];
				m_pz_Zdaughterm[3] = MCEn;

			}

		}

	}

}

void hig2inv::saveHiggsdaughter( int NParent, int NDaughter, int tmpPID, float MCEn, MCParticle *a1_MC ) {

	if(tmpPID == 25 && NDaughter > 1 && NParent !=0 ) { //Higgs

		m_n_Higgsdaughter = NDaughter;
		m_p_Higgsdaughters[3] = MCEn;
		m_p_Higgsdaughters[0] = a1_MC->getMomentum()[0];
		m_p_Higgsdaughters[1] = a1_MC->getMomentum()[1];
		m_p_Higgsdaughters[2] = a1_MC->getMomentum()[2];

		for(int i = 0; i < NDaughter; i++) { //NDaughter

			MCParticle *b_MC = a1_MC->getDaughters()[i];
			m_PID_HiggsDaughter = b_MC->getPDG();
			m_PID_Higgsdaughter[DIndex] = m_PID_HiggsDaughter;

			if(m_PID_HiggsDaughter < 6 || m_PID_HiggsDaughter == 13 || m_PID_HiggsDaughter == 11 || m_PID_HiggsDaughter == 15 ) {

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

			}

			else if(DIndex == 1) {

				m_p_Higgsdaughter2[3] = b_MC->getEnergy();
				m_p_Higgsdaughter2[0] = b_MC->getMomentum()[0];
				m_p_Higgsdaughter2[1] = b_MC->getMomentum()[1];
				m_p_Higgsdaughter2[2] = b_MC->getMomentum()[2];

			}


			if(m_PID_HiggsDaughter==23) { // Neutrino from Z ??

				NDaughter = b_MC->getDaughters().size();

				for(int j=0; j<NDaughter; j++) {

					MCParticle *c_MC = b_MC->getDaughters()[j];

					if(abs(c_MC->getPDG())==12 || abs(c_MC->getPDG())==14 || abs(c_MC->getPDG())==16) {

						m_n_Zneutrino++;

					}

				}

			}

			m_PID_HiggsDaughter = abs(m_PID_HiggsDaughter);

		}

	}

}

void hig2inv::saveNeutrino( int NDaughter, int tmpPID, float MCEn ) {

	if(NDaughter == 0) {

		if(abs(tmpPID) == 12 || abs(tmpPID) == 14 || abs(tmpPID) == 16) {

			m_n_neutrino++;
			m_energy_neutrino += MCEn;

		}

	}

}
