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
#include <iomanip>
#include <TFile.h> 
#include <TTree.h>
#include <TH1.h>
#include <TVector3.h>
#include <TRandom.h>
#include <sstream>              
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
        std::string Processname;

        LCCollection* col_MC;
        LCCollection* col_Reco;
        MCParticle *a1_MC;

        TFile *m_file;
        TTree *m_tree;
        TH1F* h_mc_init_plist;
        TH1F* h_mc_higgs_dlist;

        int LeptonID, RecoPID, tmpPID, PhotonPID, ElectronPID, MuonPID, NeutrinoEPID, NeutrinoMuonPID, TauPID, NeutrinoTauPID, ZPID, HiggsPID;
        int Dquark, Uquark, Squark, Cquark, Bquark,WPID;
        int nMC, nReco, NCandiP, NCandiM, NParent, NDaughter, nDaughter, DIndex;
        int OverWrite,DecayFlag;
        float RecoEMax, RecoEMin, ZMass;
        int m_n_gamma, m_n_charged, m_n_leptonp, m_n_leptonm, m_n_chargedp, m_n_chargedm, m_n_Higgsdaughter, m_n_neutral,m_n_neutrino,m_Neutral_PID;
        int Nmup;
        int Nmum;
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

        // MC info 
        std::vector<int> m_mc_pdgid;
        std::vector<int> m_mc_init_pdgid;
        std::vector<TLorentzVector> P4_MCTruth_LeptonPlus;  
        std::vector<TLorentzVector> P4_MCTruth_LeptonMinus;
        std::vector<TLorentzVector> P4_MCTruth_photon;
        std::vector<TLorentzVector> P4_MCTruth_Higgs;   

        int m_mc_lepton_minus_id;
        int m_mc_lepton_plus_id;

        int m_mc_init_n_lepton_plus;
        int m_mc_init_n_lepton_minus;

        double m_mc_init_leptonp_e;
        double m_mc_init_leptonp_p;
        double m_mc_init_leptonp_pt;
        double m_mc_init_leptonp_pz;

        double m_mc_init_leptonp_phi;
        double m_mc_init_leptonp_theta;

        double m_mc_init_leptonm_e;
        double m_mc_init_leptonm_p;
        double m_mc_init_leptonm_pt;
        double m_mc_init_leptonm_pz;

        double m_mc_init_leptonm_phi;
        double m_mc_init_leptonm_theta;

        double m_mc_init_dilepton_m;
        double m_mc_init_dilepton_e;
        double m_mc_init_dilepton_p;
        double m_mc_init_dilepton_pt;
        double m_mc_init_dilepton_pz;

        double m_mc_init_dilepton_rec_m;
        double m_mc_init_dilepton_dphi;
        double m_mc_init_dilepton_dang;

        int m_mc_init_n_photon;
        std::vector<double> m_mc_init_photon_e;
        std::vector<double> m_mc_init_photon_p;
        std::vector<double> m_mc_init_photon_pt;
        std::vector<double> m_mc_init_photon_pz;
        std::vector<double> m_mc_init_photon_phi;  
        std::vector<double> m_mc_init_photon_theta;

        double m_mc_higgs_m;
        double m_mc_higgs_e;
        double m_mc_higgs_rec_m;

        int m_mc_n_Zboson;
        int m_mc_higgs_decay_type;
        std::vector<int> m_mc_higgs_daughter_pdgid;
        std::vector<int> m_mc_z1_daughter_pid;
        std::vector<int> m_mc_z2_daughter_pid;
        std::vector<TLorentzVector> P4_MCTruth_Z1;  
        std::vector<TLorentzVector> P4_MCTruth_Z2;  
        std::vector<int> m_mc_w1_daughter_pid;
        std::vector<int> m_mc_w2_daughter_pid;
        std::vector<TLorentzVector> P4_MCTruth_W1;  
        std::vector<TLorentzVector> P4_MCTruth_W2;  

        double m_mc_zw1_m;
        double m_mc_zw1_p;
        double m_mc_zw1_pt;
        double m_mc_zw1_e;
        double m_mc_zw1_rec_m;

        double m_mc_zw2_m;
        double m_mc_zw2_p;
        double m_mc_zw2_pt;
        double m_mc_zw2_e;
        double m_mc_zw2_rec_m;
        
        double m_mc_zw1zw2_m;
        double m_mc_zw1zw2_e;
        double m_mc_zw1zw2_rec_m;

        int m_mc_zz_flag;
        int m_mc_ww_flag;
        int m_mc_h2gaugeboson_flag;



        void book_histogram();
        void book_tree();
        bool buildZToff();
        
        void saveNeutral( int nReco, LCCollection* colReco );
        void savePhoton( int nReco, LCCollection* colReco );
        void selectCharged( int nReco, LCCollection* colReco );
        void selectLepton( int nReco, LCCollection* col_Reco);
        void saveVisible(TLorentzVector P4_Neutral_Sum,TLorentzVector P4_Charged_Sum);
        void saveminandmaxLepton(std::vector<TLorentzVector> FourMom_LeptonP, std::vector<TLorentzVector> FourMom_LeptonM);		
        void saveRecInfo(std::vector<TLorentzVector> FourMom_LeptonP, std::vector<TLorentzVector> FourMom_LeptonM);
        //MC information
        void checkGenMCInfo( LCCollection* col_MC ); 
        void saveMCInfo( int nMC, LCCollection* col_MC );
        void saveZdaughter( int NParent, int NDaughter, int tmpPID, float MCEn, MCParticle *a1_MC );
        void saveHiggsdaughter( int NParent, int NDaughter, MCParticle *itr, int tmpPID, float MCEn, MCParticle *a1_MC );
        void saveNeutrino( int NParent, int NDaughter, MCParticle *a1_MC, int tmpPID, float MCEn );
        void printDecayChain( int MCParticleID, MCParticle *mcp );
        void printMCinfo( int MCParticleID, int flag, MCParticle *mcp, std::vector<MCParticle*> pvec, std::vector<MCParticle*> dvec );
        void saveMCTruthInfo( LCCollection* col_MC );
        void fillMCInfo();
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

    Processname="ee";  //muon is muonmuon channel,qq is qq channel.
        registerProcessorParameter( "Processname" ,
            "The name of the Processname" ,
            Processname ,
            Processname);

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
    Dquark=1;
        registerProcessorParameter( "Dquark" ,
            "Dquark ID that will be used in this analysis." ,
            Dquark ,
            Dquark);
    Uquark=2;
        registerProcessorParameter( "Uquark" ,
            "Uquark ID that will be used in this analysis." ,
            Uquark ,
            Uquark);
    Squark=3;
        registerProcessorParameter( "Squark" ,
            "Squark ID that will be used in this analysis." ,
            Squark ,
            Squark);
    Cquark=4;
        registerProcessorParameter( "Cquark" ,
            "Cquark ID that will be used in this analysis." ,
            Cquark ,
            Cquark);
    Bquark=5;
        registerProcessorParameter( "Bquark" ,
            "Bquark ID that will be used in this analysis." ,
            Bquark ,
            Bquark);
    WPID=24;
        registerProcessorParameter( "WPID" ,
            "W Boson ID that will be used in this analysis." ,
            WPID ,
            WPID);
    DecayFlag=0;  //1 is H->Z ; 2 is H->W ; 3 is H->q ; 4 is H ->Lepton ; 5 is H->Gluon ; 6 is H-> Photon in MC.  
        registerProcessorParameter( "DecayFlag" ,
            "DecayFlag is Higgs decay once produced particles" ,
            DecayFlag ,
            DecayFlag);            
}

void hig2inv::init() {
    book_histogram();
    book_tree();

}

void hig2inv::processEvent( LCEvent * evt ) {	

    if(evt){
        try{
            variable_init();

            col_MC = evt->getCollection( "MCParticle" );
            if(buildZToff()){

            col_Reco = evt->getCollection( "ArborPFOs" );
            nMC = col_MC->getNumberOfElements();
            nReco = col_Reco->getNumberOfElements();
            m_event=evt->getEventNumber();

            saveNeutral( nReco, col_Reco );
            savePhoton( nReco, col_Reco );
            selectCharged( nReco, col_Reco );
            selectLepton(nReco,col_Reco);
            saveVisible(P4_Neutral_Sum, P4_Charged_Sum);
            saveRecInfo(FourMom_LeptonP,FourMom_LeptonM);
             saveMCTruthInfo( col_MC );            

//            saveMCInfo( nMC, col_MC );

            m_tree->Fill();
        }
        }
        catch (lcio::DataNotAvailableException err) { }
    }

}	

void hig2inv::end() {

    if (m_tree) {
        TFile *tree_file = m_tree->GetCurrentFile(); //just in case we switched to a new file
        tree_file->Write();
        h_mc_init_plist->Write();
        h_mc_higgs_dlist->Write();
        delete tree_file;
    }

}

void hig2inv::book_histogram() {
 h_mc_init_plist = new TH1F("h_mc_init_plist", "mc_init_plist", 80, -40, 40 );
 h_mc_higgs_dlist = new TH1F("h_mc_higgs_dlist", "mc_higgs_dlist", 80, -40, 40 );
}

void hig2inv::book_tree() { 

    m_file=new TFile(FileName.c_str(),(OverWrite ? "RECREATE" : "UPDATE"));
    if (!m_file->IsOpen()) {
        delete m_file;
        m_file=new TFile(FileName.c_str(),"NEW");
    }
    m_tree = new TTree(TreeName.c_str(),TreeName.c_str());
    m_tree->Branch("m_event",&m_event,"m_event/I");
    m_tree->Branch("m_n_neutral",  &m_n_neutral,  "m_n_neutral/I");
    m_tree->Branch("m_Neutral_PID",  &m_Neutral_PID,  "m_Neutral_PID/I");
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


//MC info
  m_tree->Branch("mc_pdgid", &m_mc_pdgid);
  m_tree->Branch("mc_init_pdgid", &m_mc_init_pdgid);
  
  m_tree->Branch("mc_lepton_minus_id", &m_mc_lepton_minus_id, "mc_lepton_minus_id/I");
  m_tree->Branch("mc_lepton_plus_id", &m_mc_lepton_plus_id, "mc_lepton_plus_id/I");
  
  m_tree->Branch("mc_init_n_lepton_plus", &m_mc_init_n_lepton_plus,  "mc_init_n_lepton_plus/I");
  m_tree->Branch("mc_init_n_lepton_minus", &m_mc_init_n_lepton_minus,  "mc_init_n_lepton_minus/I");
  
  m_tree->Branch("mc_init_leptonp_e",  &m_mc_init_leptonp_e,   "mc_init_leptonp_e/D");
  m_tree->Branch("mc_init_leptonp_p",  &m_mc_init_leptonp_p,   "mc_init_leptonp_p/D");
  m_tree->Branch("mc_init_leptonp_pt", &m_mc_init_leptonp_pt,  "mc_init_leptonp_pt/D");
  m_tree->Branch("mc_init_leptonp_pz", &m_mc_init_leptonp_pz,  "mc_init_leptonp_pz/D");

  m_tree->Branch("mc_init_leptonp_phi", &m_mc_init_leptonp_phi,  "mc_init_leptonp_phi/D");
  m_tree->Branch("mc_init_leptonp_theta", &m_mc_init_leptonp_theta,  "mc_init_leptonp_theta/D");
  
  m_tree->Branch("mc_init_leptonm_e",  &m_mc_init_leptonm_e,   "mc_init_leptonm_e/D");
  m_tree->Branch("mc_init_leptonm_p",  &m_mc_init_leptonm_p,   "mc_init_leptonm_p/D");
  m_tree->Branch("mc_init_leptonm_pt", &m_mc_init_leptonm_pt,  "mc_init_leptonm_pt/D");
  m_tree->Branch("mc_init_leptonm_pz", &m_mc_init_leptonm_pz,  "mc_init_leptonm_pz/D");

  m_tree->Branch("mc_init_leptonm_phi", &m_mc_init_leptonm_phi,  "mc_init_leptonm_phi/D");
  m_tree->Branch("mc_init_leptonm_theta", &m_mc_init_leptonm_theta,  "mc_init_leptonm_theta/D");
  
  m_tree->Branch("mc_init_dilepton_m",  &m_mc_init_dilepton_m,   "mc_init_dilepton_m/D");
  m_tree->Branch("mc_init_dilepton_e",  &m_mc_init_dilepton_e,   "mc_init_dilepton_e/D");
  m_tree->Branch("mc_init_dilepton_p",  &m_mc_init_dilepton_p,   "mc_init_dilepton_p/D");
  m_tree->Branch("mc_init_dilepton_pt", &m_mc_init_dilepton_pt,  "mc_init_dilepton_pt/D");
  m_tree->Branch("mc_init_dilepton_pz", &m_mc_init_dilepton_pz,  "mc_init_dilepton_pz/D");
  m_tree->Branch("mc_init_dilepton_rec_m", &m_mc_init_dilepton_rec_m,  "mc_init_dilepton_rec_m/D");
  m_tree->Branch("mc_init_dilepton_dphi", &m_mc_init_dilepton_dphi,  "mc_init_dilepton_dphi/D");
  m_tree->Branch("mc_init_dilepton_dang", &m_mc_init_dilepton_dang,  "mc_init_dilepton_dang/D");
  
  m_tree->Branch("mc_init_n_photon", &m_mc_init_n_photon,  "mc_init_n_photon/I");
  m_tree->Branch("mc_init_photon_e",  &m_mc_init_photon_e);
  m_tree->Branch("mc_init_photon_p",  &m_mc_init_photon_p);
  m_tree->Branch("mc_init_photon_pt",  &m_mc_init_photon_pt);
  m_tree->Branch("mc_init_photon_pz",  &m_mc_init_photon_pz);
  m_tree->Branch("mc_init_photon_phi",  &m_mc_init_photon_phi);
  m_tree->Branch("mc_init_photon_theta",  &m_mc_init_photon_theta);

  m_tree->Branch("mc_higgs_m", &m_mc_higgs_m, "mc_higgs_m/D");
  m_tree->Branch("mc_higgs_e", &m_mc_higgs_e, "mc_higgs_e/D");
  m_tree->Branch("mc_higgs_rec_m", &m_mc_higgs_rec_m, "mc_higgs_rec_m/D");
  m_tree->Branch("mc_higgs_decay_type", &m_mc_higgs_decay_type, "mc_higgs_decay_type/I");
  m_tree->Branch("mc_higgs_daughter_pdgid", &m_mc_higgs_daughter_pdgid);
 
  m_tree->Branch("mc_n_Zboson", &m_mc_n_Zboson, "mc_n_Zboson/I");
  
  m_tree->Branch("mc_z1_daughter_pid", &m_mc_z1_daughter_pid);
  m_tree->Branch("mc_z2_daughter_pid", &m_mc_z2_daughter_pid);

  m_tree->Branch("mc_w1_daughter_pid", &m_mc_w1_daughter_pid);
  m_tree->Branch("mc_w2_daughter_pid", &m_mc_w2_daughter_pid);
  
  m_tree->Branch("mc_zw1_m", &m_mc_zw1_m, "mc_zw1_m/D");
  m_tree->Branch("mc_zw1_p", &m_mc_zw1_p, "mc_zw1_p/D");
  m_tree->Branch("mc_zw1_pt", &m_mc_zw1_pt, "mc_zw1_pt/D");
  m_tree->Branch("mc_zw1_e", &m_mc_zw1_e, "mc_zw1_e/D");
  m_tree->Branch("mc_zw1_rec_m", &m_mc_zw1_rec_m, "mc_zw1_rec_m/D");
  
  m_tree->Branch("mc_zw2_m", &m_mc_zw2_m, "mc_zw2_m/D");
  m_tree->Branch("mc_zw2_p", &m_mc_zw2_p, "mc_zw2_p/D");
  m_tree->Branch("mc_zw2_pt", &m_mc_zw2_pt, "mc_zw2_pt/D");
  m_tree->Branch("mc_zw2_e", &m_mc_zw2_e, "mc_zw2_e/D");
  m_tree->Branch("mc_zw2_rec_m", &m_mc_zw2_rec_m, "mc_zw2_rec_m/D");
  
  m_tree->Branch("mc_zw1zw2_m", &m_mc_zw1zw2_m, "mc_zw1zw2_m/D");
  m_tree->Branch("mc_zw1zw2_e", &m_mc_zw1zw2_e, "mc_zw1zw2_e/D");
  m_tree->Branch("mc_zw1zw2_rec_m", &m_mc_zw1zw2_rec_m, "mc_zw1zw2_rec_m/D");
  m_tree->Branch("mc_zz_flag", &m_mc_zz_flag, "mc_zz_flag/I");
  m_tree->Branch("mc_ww_flag", &m_mc_ww_flag, "mc_ww_flag/I");
  m_tree->Branch("mc_h2gaugeboson_flag", &m_mc_h2gaugeboson_flag, "mc_h2gaugeboson_flag/I");


}

void hig2inv::variable_init() {

    m_n_charged = 0;
    m_n_neutral = 0;
    Nmum = 0;
    Nmup = 0;
    m_Neutral_PID = 0;
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

  // MC info. 
  m_mc_pdgid.clear();
  m_mc_init_pdgid.clear();
  m_mc_higgs_daughter_pdgid.clear();
  P4_MCTruth_LeptonPlus.clear();
  P4_MCTruth_LeptonMinus.clear();
  P4_MCTruth_photon.clear();
  P4_MCTruth_Higgs.clear();

  m_mc_init_photon_e.clear();
  m_mc_init_photon_p.clear();
  m_mc_init_photon_pt.clear();
  m_mc_init_photon_pz.clear();
  m_mc_init_photon_phi.clear();
  m_mc_init_photon_theta.clear();

  m_mc_z1_daughter_pid.clear();
  m_mc_z2_daughter_pid.clear();
  P4_MCTruth_Z1.clear();
  P4_MCTruth_Z2.clear();

  m_mc_w1_daughter_pid.clear();
  m_mc_w2_daughter_pid.clear();
  P4_MCTruth_W1.clear();
  P4_MCTruth_W2.clear();
}

void hig2inv::saveNeutral( int nReco, LCCollection* col_Reco ) {
//changed:we need Neutral sum monmentum and energy,this is visible energy.
    int counter = 0; 
    for(int i = 0; i < nReco; i++) {
        ReconstructedParticle *a_Reco = dynamic_cast<EVENT::ReconstructedParticle *>(col_Reco->getElementAt(i));
        if(a_Reco->getCharge()!=0) continue;
        P4_Neutral_Sum[0] += a_Reco->getMomentum()[0];
        P4_Neutral_Sum[1] += a_Reco->getMomentum()[1];
        P4_Neutral_Sum[2] += a_Reco->getMomentum()[2];
        P4_Neutral_Sum[3] += a_Reco->getEnergy();
        m_Neutral_PID = a_Reco->getType();
        counter++;
    }
    m_n_neutral = counter;	

    m_sum_p_neutral[0] = P4_Neutral_Sum[0];
    m_sum_p_neutral[1] = P4_Neutral_Sum[1];
    m_sum_p_neutral[2] = P4_Neutral_Sum[2]; 
    m_sum_p_neutral[3] = P4_Neutral_Sum[3];
}

void hig2inv::savePhoton( int nReco, LCCollection* col_Reco ) {

//	float photone=50;maoqiang
    double tmp_emax=-1.0;  //PID identification is OK. first change 
    for(int i = 0; i < nReco; i++) {
        ReconstructedParticle *a_Reco = dynamic_cast<EVENT::ReconstructedParticle *>(col_Reco->getElementAt(i));
        if(a_Reco->getCharge()!=0) continue;

        if(a_Reco->getType()!=PhotonPID) continue;
        if(fabs(a_Reco->getMomentum()[2]/a_Reco->getEnergy())>0.995) continue; // acceptance of the detector
        if(a_Reco->getEnergy()>tmp_emax) {
            tmp_emax = a_Reco->getEnergy();
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

}

void hig2inv::selectCharged( int nReco, LCCollection* col_Reco ) {
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

      m_sum_p_charged[0] = P4_Charged_Sum[0];
      m_sum_p_charged[1] = P4_Charged_Sum[1];
      m_sum_p_charged[2] = P4_Charged_Sum[2];
      m_sum_p_charged[3] = P4_Charged_Sum[3];

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
        if (lepton_charge > 0.0)FourMom_ChargedP.push_back(curr);
        if (lepton_charge < 0.0)FourMom_ChargedM.push_back(curr);
        if(RecoPID == LeptonID ) {
           if( lepton_charge >  0.0 )FourMom_LeptonP.push_back( curr );
           if( lepton_charge < 0.0 )FourMom_LeptonM.push_back( curr );
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


void hig2inv::saveVisible(TLorentzVector P4_Neutral_Sum,TLorentzVector P4_Charged_Sum) {
    for(int i=0;i<4;i++){
    m_p_visible[i] = P4_Charged_Sum[i] +  P4_Neutral_Sum[i];
    }
   m_m_visible = ( P4_Charged_Sum+ P4_Neutral_Sum).M();
   m_energy_visible = ( P4_Charged_Sum+ P4_Neutral_Sum).E();
   m_vis_rec_m = (P_T - P4_Charged_Sum - P4_Neutral_Sum).M();
   m_vis_rec_e = (P_T - P4_Charged_Sum - P4_Neutral_Sum).E();
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
void hig2inv::printDecayChain( int MCParticleID, MCParticle *mcp ) {
    std::vector<MCParticle*> pvec, dvec;
    pvec = mcp->getParents();
    dvec = mcp->getDaughters();
    
    // Display PID info. 
    printMCinfo( MCParticleID, 1, mcp, pvec, dvec );
    
    // Follow daughter's information as well
    if( 0 ){
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
    
    if( flag == 1 )std::cout << " MCParticleID = " <<std::setw(4)<<  MCParticleID ;
    if( flag == 2 )std::cout << "           " << "    " ;                    // daughther info.
    std::cout << ", status=" << status << " : nParents = " << nparents << " : " ;
    for( std::vector<int>::iterator itr = p_pid.begin(); itr != p_pid.end(); ++itr ) std::cout <<std::setw(5)<< *itr << " " ;
    if( p_pid.size() == 0 ) {
        std::cout << "     " << " " ;
        std::cout << "     " << " " ;
    }
    if( p_pid.size() == 1 ) {
        std::cout << "     " << " " ;
    }
    std::cout << " : pdgid = " <<std::setw(5) << pdgid << " : nDaughters = " << ndaughters << " : " ;
    for( std::vector<int>::iterator itr = d_pid.begin(); itr != d_pid.end(); ++itr ) std::cout <<std::setw(5)<< *itr << ", " ;
    std::cout << std::endl;

}

void hig2inv::checkGenMCInfo( LCCollection* col_MC ) {

  int ncol = col_MC->getNumberOfElements();
  for( int i = 0; i < ncol; i++) {

    MCParticle *mcp = dynamic_cast<EVENT::MCParticle *>(col_MC->getElementAt(i));

    std::vector<MCParticle*> pvec;
    pvec = mcp->getParents();

    int pdgid       =  mcp->getPDG();
    int nparents    =  pvec.size();

    int mother_pid=-9999;
    if( nparents > 0 )mother_pid=pvec[0]->getPDG();

    // Save Initial Partons PID
    if( nparents == 0 )h_mc_init_plist->Fill( pdgid );  

    // Save Higgs Daughter PID
    if( nparents == 1 && mother_pid == HiggsPID )h_mc_higgs_dlist->Fill( pdgid );
    if (Processname == "ee"){  
    if (nparents == 0){
    LeptonID=11;
        if ( pdgid == ElectronPID ) {
            Nmup++;
        }
        if(pdgid == -ElectronPID ) {
            Nmum++;		
        }	
    }
    }
    if (Processname == "muon"){ 
    LeptonID=13;
    if (nparents == 0){
        if ( pdgid == MuonPID ) {
            Nmup++;
        }
        if(pdgid == -MuonPID ) {
            Nmum++;		
        }	
    }	
    }
    if (Processname == "qq"){ 
    if (nparents == 0){
        if ( pdgid == Dquark ||pdgid == Uquark ||pdgid == Squark ||pdgid == Cquark ||pdgid == Bquark ) {
            Nmup++;
        }
        if( pdgid == -Dquark ||pdgid == -Uquark ||pdgid == -Squark ||pdgid == -Cquark ||pdgid == -Bquark ) {
            Nmum++;	
        }	
    }	
    }
    if (Processname == "BKGM"){ 
    LeptonID=13;
       Nmup=1;
       Nmum=1;
    }	
    if (Processname == "BKGE"){ 
    LeptonID=11;
       Nmup=1;
       Nmum=1;
    }	
  }

}
bool hig2inv::buildZToff() {
    checkGenMCInfo(col_MC);
  if (Nmup == 1 && Nmum == 1){
      return true; 
  }
  else{
      return false;
  }
}
void hig2inv::saveMCTruthInfo( LCCollection* col_MC ) {

  int ncol = col_MC->getNumberOfElements();
  
  int Zcount=0;
  int Wcount=0;
  for( int i = 0; i < ncol; i++) {

    MCParticle *mcp = dynamic_cast<EVENT::MCParticle *>(col_MC->getElementAt(i));

    std::vector<MCParticle*> pvec, dvec;
    pvec = mcp->getParents();
    dvec = mcp->getDaughters();

    int status      =  mcp->getGeneratorStatus(); 
    int pdgid       =  mcp->getPDG();
    //int mass        =  mcp->getMass();
    int nparents    =  pvec.size();
    //int ndaughters  =  dvec.size();

    // Print decay chain info, if need them.
    if( 0 ) printDecayChain( i , mcp );


    int mother_pid=-9999;
    if( nparents > 0 )mother_pid=pvec[0]->getPDG();

    if( nparents == 0 ) { 
    
      double px = mcp->getMomentum()[0];
      double py = mcp->getMomentum()[1];
      double pz = mcp->getMomentum()[2];
      double e = mcp->getEnergy();
      
      TLorentzVector p4vec(px, py, pz, e);
      
      if( pdgid == MuonPID || pdgid == ElectronPID || pdgid == TauPID) {
        m_mc_lepton_minus_id = pdgid;
        P4_MCTruth_LeptonMinus.push_back( p4vec );
      }
      if( pdgid == -MuonPID|| pdgid == -ElectronPID|| pdgid == -TauPID){
        m_mc_lepton_plus_id = pdgid;
        P4_MCTruth_LeptonPlus.push_back( p4vec );
      }
      
      if( pdgid == PhotonPID )P4_MCTruth_photon.push_back( p4vec );
      if( pdgid == HiggsPID )P4_MCTruth_Higgs.push_back( p4vec );
    
      m_mc_init_pdgid.push_back( pdgid );
    }

    // Search Higgs daughters
    if( nparents == 1 && mother_pid == HiggsPID ) { // mother is Higgs

      m_mc_higgs_daughter_pdgid.push_back( pdgid );

      if( pdgid == ZPID ) {  // Z boson
    
    //for( int j = 0; j < ndaughters; j++ ) 
    for( int j = 0; j < 2; j++ )  { // fill daughter's info
      
      int d_pid  = dvec[j]->getPDG();
      
      double px = dvec[j]->getMomentum()[0];
      double py = dvec[j]->getMomentum()[1];
      double pz = dvec[j]->getMomentum()[2];
      double e = dvec[j]->getEnergy();
      
      TLorentzVector p4vec(px, py, pz, e);

      if( Zcount == 0 ) {
        m_mc_z1_daughter_pid.push_back( d_pid );
        P4_MCTruth_Z1.push_back( p4vec );	    
      }
      else if( Zcount == 1 ) {
        m_mc_z2_daughter_pid.push_back( d_pid );
        P4_MCTruth_Z2.push_back( p4vec );
      }
    }
    
    DecayFlag = 1;
    Zcount++;
      }

      if( abs(pdgid) == WPID ) {  // W boson
    
    for( int j = 0; j < 2; j++ )  { // fill daughter's info
      
      int d_pid  = dvec[j]->getPDG();
      
      double px = dvec[j]->getMomentum()[0];
      double py = dvec[j]->getMomentum()[1];
      double pz = dvec[j]->getMomentum()[2];
      double e = dvec[j]->getEnergy();
      
      TLorentzVector p4vec(px, py, pz, e);

      if( Wcount == 0 ) {
        m_mc_w1_daughter_pid.push_back( d_pid );
        P4_MCTruth_W1.push_back( p4vec );	    
      }
      else if( Wcount == 1 ) {
        m_mc_w2_daughter_pid.push_back( d_pid );
        P4_MCTruth_W2.push_back( p4vec );
      }
    }
    
    DecayFlag = 2;
    Wcount++;
      }    
      
      if( abs(pdgid) >= 1  && abs(pdgid) <= 6  ) DecayFlag = 3;  //qq
      if( abs(pdgid) >= 11 && abs(pdgid) <= 16 ) DecayFlag = 4;  //Lepton
      if( pdgid == 21 ) DecayFlag = 5;  //Gluon
      if( pdgid == 22 ) DecayFlag = 6; //Photon
    
    }

    if(status==1)m_mc_pdgid.push_back(pdgid);
  }

  m_mc_n_Zboson = Zcount;
  m_mc_higgs_decay_type = DecayFlag;

  fillMCInfo();

}

void hig2inv::fillMCInfo() {

  int n_init_lepton_p = P4_MCTruth_LeptonPlus.size();
  int n_init_lepton_m = P4_MCTruth_LeptonMinus.size();
  
  // Initial two leptons
  m_mc_init_n_lepton_plus  = n_init_lepton_p;
  m_mc_init_n_lepton_minus = n_init_lepton_m;

  if( n_init_lepton_p > 0 && n_init_lepton_m > 0 ) {

    m_mc_init_leptonp_e  = P4_MCTruth_LeptonPlus[0].E();
    m_mc_init_leptonp_p  = P4_MCTruth_LeptonPlus[0].P();
    m_mc_init_leptonp_pt = P4_MCTruth_LeptonPlus[0].Pt();
    m_mc_init_leptonp_pz = P4_MCTruth_LeptonPlus[0].Pz();

    m_mc_init_leptonp_phi = P4_MCTruth_LeptonPlus[0].Phi()      *180.0/M_PI;
    m_mc_init_leptonp_theta = P4_MCTruth_LeptonPlus[0].Theta()  *180.0/M_PI;
  
    m_mc_init_leptonm_e  = P4_MCTruth_LeptonMinus[0].E();
    m_mc_init_leptonm_p  = P4_MCTruth_LeptonMinus[0].P();
    m_mc_init_leptonm_pt = P4_MCTruth_LeptonMinus[0].Pt();
    m_mc_init_leptonm_pz = P4_MCTruth_LeptonMinus[0].Pz();

    m_mc_init_leptonm_phi = P4_MCTruth_LeptonMinus[0].Phi()     *180.0/M_PI;
    m_mc_init_leptonm_theta = P4_MCTruth_LeptonMinus[0].Theta() *180.0/M_PI;
  
    double mll     = ( P4_MCTruth_LeptonPlus[0] + P4_MCTruth_LeptonMinus[0] ).M();
    double ell     = ( P4_MCTruth_LeptonPlus[0] + P4_MCTruth_LeptonMinus[0] ).E();
    double pll     = ( P4_MCTruth_LeptonPlus[0] + P4_MCTruth_LeptonMinus[0] ).P();
    double ptll    = ( P4_MCTruth_LeptonPlus[0] + P4_MCTruth_LeptonMinus[0] ).Pt();
    double pzll    = ( P4_MCTruth_LeptonPlus[0] + P4_MCTruth_LeptonMinus[0] ).Pz();
    double rec_mll = (P_T - P4_MCTruth_LeptonPlus[0] - P4_MCTruth_LeptonMinus[0] ).M();
    double dphi    = fabs(P4_MCTruth_LeptonPlus[0].DeltaPhi(P4_MCTruth_LeptonMinus[0])) *180.0/M_PI;
    double dang    = P4_MCTruth_LeptonPlus[0].Angle(P4_MCTruth_LeptonMinus[0].Vect())   *180.0/M_PI;
  
    m_mc_init_dilepton_m = mll;
    m_mc_init_dilepton_e = ell;
    m_mc_init_dilepton_p = pll;
    m_mc_init_dilepton_pt = ptll;
    m_mc_init_dilepton_pz = pzll;
    m_mc_init_dilepton_rec_m = rec_mll;
    m_mc_init_dilepton_dphi = dphi;
    m_mc_init_dilepton_dang = dang;
  }
  else {
    
    m_mc_init_leptonp_e  = -9999.0;
    m_mc_init_leptonp_p  = -9999.0;
    m_mc_init_leptonp_pt = -9999.0;
    m_mc_init_leptonp_pz = -9999.0;

    m_mc_init_leptonp_phi = -9999.0;
    m_mc_init_leptonp_theta = -9999.0;
  
    m_mc_init_leptonm_e  = -9999.0;
    m_mc_init_leptonm_p  = -9999.0;
    m_mc_init_leptonm_pt = -9999.0;
    m_mc_init_leptonm_pz = -9999.0;

    m_mc_init_leptonm_phi = -9999.0;
    m_mc_init_leptonm_theta = -9999.0;
  
    m_mc_init_dilepton_m = -9999.0;
    m_mc_init_dilepton_e = -9999.0;
    m_mc_init_dilepton_p = -9999.0;
    m_mc_init_dilepton_pt = -9999.0;
    m_mc_init_dilepton_pz = -9999.0;
    m_mc_init_dilepton_rec_m = -9999.0;
    m_mc_init_dilepton_dphi = -9999.0;
    m_mc_init_dilepton_dang = -9999.0;
  }
    
  // Initial photons
  int n_init_photon = P4_MCTruth_photon.size();
  
  m_mc_init_n_photon  = n_init_photon;

  for( int i=0; i<n_init_photon; i++) {

    m_mc_init_photon_e.push_back( P4_MCTruth_photon[i].E() );
    m_mc_init_photon_p.push_back( P4_MCTruth_photon[i].P() );
    m_mc_init_photon_pt.push_back( P4_MCTruth_photon[i].Pt() );
    m_mc_init_photon_pz.push_back( P4_MCTruth_photon[i].Pz() );

    m_mc_init_photon_phi.push_back( P4_MCTruth_photon[i].Phi()*180.0/M_PI );
    m_mc_init_photon_theta.push_back( P4_MCTruth_photon[i].Theta()*180.0/M_PI );
  }

  if( n_init_photon == 0 ) {

    m_mc_init_photon_e.push_back( -99.0 );
    m_mc_init_photon_p.push_back( -99.0 );
    m_mc_init_photon_pt.push_back( -99.0 );
    m_mc_init_photon_pz.push_back( -999.0 );

    m_mc_init_photon_phi.push_back( -99.0 );
    m_mc_init_photon_theta.push_back( -99.0 );
  }


  // Initial Higgs
  int n_higgs = P4_MCTruth_Higgs.size();
  if( n_higgs == 1 ) {

    m_mc_higgs_m = P4_MCTruth_Higgs[0].M();
    m_mc_higgs_e = P4_MCTruth_Higgs[0].E();
    m_mc_higgs_rec_m = ( P_T - P4_MCTruth_Higgs[0] ).M();
  }
  else {

    m_mc_higgs_m = -9999.0;
    m_mc_higgs_e = -9999.0;
    m_mc_higgs_rec_m = -9999.0;
  }


  // H->ZZ* or H->WW* channels   
  int n_z1_daughters = P4_MCTruth_Z1.size();
  int n_z2_daughters = P4_MCTruth_Z2.size();
  int n_w1_daughters = P4_MCTruth_W1.size();
  int n_w2_daughters = P4_MCTruth_W2.size();

  int h2zz_flag=0;
  int h2ww_flag=0;
  m_mc_zz_flag = -1;
  m_mc_ww_flag = -1;

  TLorentzVector p4_zw1_daughter_1, p4_zw1_daughter_2;
  TLorentzVector p4_zw2_daughter_1, p4_zw2_daughter_2;

  // Higgs -> ZZ
  if( n_higgs == 1 && n_z1_daughters == 2 && n_z2_daughters == 2 ) {

    h2zz_flag = 1;

    int flag1=0;
    int flag2=0;
    //*******  Z1 decay combination   *******//
    // Z1->qq
    if( abs(m_mc_z1_daughter_pid[0]) >= 1 && abs(m_mc_z1_daughter_pid[0]) <= 6 ) { flag1 = 1; }

    // Z1->nunu
    if( abs(m_mc_z1_daughter_pid[0]) == NeutrinoEPID ||
    abs(m_mc_z1_daughter_pid[0]) == NeutrinoMuonPID     ||
    abs(m_mc_z1_daughter_pid[0]) == NeutrinoTauPID         ) { flag1 = 2; }

    // Z1->ll
    if( abs(m_mc_z1_daughter_pid[0]) == ElectronPID ||
    abs(m_mc_z1_daughter_pid[0]) == MuonPID     ||
    abs(m_mc_z1_daughter_pid[0]) == TauPID         ) { flag1 = 3; }

    // Strange !
    if( (m_mc_z1_daughter_pid[0] + m_mc_z1_daughter_pid[1]) != 0 ) { flag1 = 4; }
  
    //*******  Z2 decay combination   *******//
    // Z2->qq
    if( abs(m_mc_z2_daughter_pid[0]) >= 1 && abs(m_mc_z2_daughter_pid[0]) <= 6 ) { flag2 = 1; }

    // Z2->nunu
    if( abs(m_mc_z2_daughter_pid[0]) == NeutrinoEPID ||
    abs(m_mc_z2_daughter_pid[0]) == NeutrinoMuonPID     ||
    abs(m_mc_z2_daughter_pid[0]) == NeutrinoTauPID         ) { flag2 = 2; }

    // Z2->ll
    if( abs(m_mc_z2_daughter_pid[0]) == ElectronPID ||
    abs(m_mc_z2_daughter_pid[0]) == MuonPID     ||
    abs(m_mc_z2_daughter_pid[0]) == TauPID         ) { flag2 = 3; }

    // Strange Combination
    if( (m_mc_z2_daughter_pid[0] + m_mc_z2_daughter_pid[1]) != 0 ) { flag2 = 4; }

    m_mc_zz_flag = flag2*10 + flag1;
  
    // Replace Neutrino component to "invisible"
    TLorentzVector p4_null(0,0,0,0);

    p4_zw1_daughter_1 = P4_MCTruth_Z1[0];
    p4_zw1_daughter_2 = P4_MCTruth_Z1[1];
    p4_zw2_daughter_1 = P4_MCTruth_Z2[0];
    p4_zw2_daughter_2 = P4_MCTruth_Z2[1];

    if( flag1 == 2 ) { // neutrino
    
      p4_zw1_daughter_1 = p4_null;
      p4_zw1_daughter_2 = p4_null;
    }
    if( flag2 == 2 ) { // neutrino
    
      p4_zw2_daughter_1 = p4_null;
      p4_zw2_daughter_2 = p4_null;
    }
  }

  // Higgs -> WW
  if( n_higgs == 1 && n_w1_daughters == 2 && n_w2_daughters == 2  ) {     

    h2ww_flag = 1;

    int flag1=0;
    int flag2=0;
    //*******  W1 decay combination   *******//
    // W1->qq
    if( abs(m_mc_w1_daughter_pid[0]) >= 1 && abs(m_mc_w1_daughter_pid[0]) <= 6 ) { flag1 = 1; }

    // W1->nu+l
    if( abs(m_mc_w1_daughter_pid[0]) == NeutrinoEPID  || 
        abs(m_mc_w1_daughter_pid[0]) == NeutrinoMuonPID      ||
    abs(m_mc_w1_daughter_pid[0]) == NeutrinoTauPID            ) { flag1 = 2; }

    // W1->l+nu
    if( abs(m_mc_w1_daughter_pid[1]) == NeutrinoEPID  || 
        abs(m_mc_w1_daughter_pid[1]) == NeutrinoMuonPID      ||
    abs(m_mc_w1_daughter_pid[1]) == NeutrinoTauPID            ) { flag1 = 3; }

  
    //*******  W2 decay combination   *******//
    // W2->qq
    if( abs(m_mc_w2_daughter_pid[0]) >= 1 && abs(m_mc_w2_daughter_pid[0]) <= 6 ) { flag2 = 1; }

    // W2->nu+l
    if( abs(m_mc_w2_daughter_pid[0]) == NeutrinoEPID  || 
        abs(m_mc_w2_daughter_pid[0]) == NeutrinoMuonPID      ||
    abs(m_mc_w2_daughter_pid[0]) == NeutrinoTauPID            ) { flag2 = 2; }

    // W2->l+nu
    if( abs(m_mc_w2_daughter_pid[1]) == NeutrinoEPID  || 
        abs(m_mc_w2_daughter_pid[1]) == NeutrinoMuonPID      ||
    abs(m_mc_w2_daughter_pid[1]) == NeutrinoTauPID            ) { flag2 = 3; }


    m_mc_ww_flag = flag2*10 + flag1;

    // Replace Neutrino component to "invisible"
    TLorentzVector p4_null(0,0,0,0);
    p4_zw1_daughter_1 = P4_MCTruth_W1[0];
    p4_zw1_daughter_2 = P4_MCTruth_W1[1];
    p4_zw2_daughter_1 = P4_MCTruth_W2[0];
    p4_zw2_daughter_2 = P4_MCTruth_W2[1];

    if( flag1 == 2 ) p4_zw1_daughter_1 = p4_null; // neutrino
    if( flag1 == 3 ) p4_zw1_daughter_2 = p4_null; // neutrino

    if( flag2 == 2 ) p4_zw2_daughter_1 = p4_null; // neutrino
    if( flag2 == 3 ) p4_zw2_daughter_2 = p4_null; // neutrino
  }


  // Save Variables ( H->ZZ*/WW* )
  if( h2zz_flag == 0 && h2ww_flag == 0 ) m_mc_h2gaugeboson_flag = 0;
  if( h2zz_flag == 1 && h2ww_flag == 0 ) m_mc_h2gaugeboson_flag = 1;
  if( h2zz_flag == 0 && h2ww_flag == 1 ) m_mc_h2gaugeboson_flag = 2;
  if( h2zz_flag == 1 && h2ww_flag == 1 ) m_mc_h2gaugeboson_flag = 3;


  if( h2zz_flag == 1 || h2ww_flag == 1 ) {

    double zw1_m  = ( p4_zw1_daughter_1 + p4_zw1_daughter_2 ).M();
    double zw1_p  = ( p4_zw1_daughter_1 + p4_zw1_daughter_2 ).P();
    double zw1_pt = ( p4_zw1_daughter_1 + p4_zw1_daughter_2 ).Pt();
    double zw1_e  = ( p4_zw1_daughter_1 + p4_zw1_daughter_2 ).E();
    double zw1_rec_m  = ( P_T - p4_zw1_daughter_1 - p4_zw1_daughter_2 ).M();

    double zw2_m  = ( p4_zw2_daughter_1 + p4_zw2_daughter_2 ).M();
    double zw2_p  = ( p4_zw2_daughter_1 + p4_zw2_daughter_2 ).P();
    double zw2_pt = ( p4_zw2_daughter_1 + p4_zw2_daughter_2 ).Pt();
    double zw2_e  = ( p4_zw2_daughter_1 + p4_zw2_daughter_2 ).E();
    double zw2_rec_m  = ( P_T - p4_zw2_daughter_1 - p4_zw2_daughter_2 ).M();

    double zw1zw2_m = ( p4_zw1_daughter_1 + p4_zw1_daughter_2 + p4_zw2_daughter_1 + p4_zw2_daughter_2 ).M();
    double zw1zw2_e = ( p4_zw1_daughter_1 + p4_zw1_daughter_2 + p4_zw2_daughter_1 + p4_zw2_daughter_2 ).E();
    double zw1zw2_rec_m = ( P_T - p4_zw1_daughter_1 - p4_zw1_daughter_2 - p4_zw2_daughter_1 - p4_zw2_daughter_2 ).M();

    m_mc_zw1_m  = zw1_m;
    m_mc_zw1_p  = zw1_p;
    m_mc_zw1_pt = zw1_pt;
    m_mc_zw1_e  = zw1_e;
    m_mc_zw1_rec_m = zw1_rec_m;

    m_mc_zw2_m  = zw2_m;
    m_mc_zw2_p  = zw2_p;
    m_mc_zw2_pt = zw2_pt;
    m_mc_zw2_e  = zw2_e;
    m_mc_zw2_rec_m = zw2_rec_m;

    m_mc_zw1zw2_m = zw1zw2_m;
    m_mc_zw1zw2_e = zw1zw2_e;
    m_mc_zw1zw2_rec_m = zw1zw2_rec_m;
  }
  else {

    m_mc_zw1_m  = -9999.0;
    m_mc_zw1_p  = -9999.0;
    m_mc_zw1_pt = -9999.0;
    m_mc_zw1_e  = -9999.0;
    m_mc_zw1_rec_m = -9999.0;

    m_mc_zw2_m  = -9999.0;
    m_mc_zw2_p  = -9999.0;
    m_mc_zw2_pt = -9999.0;
    m_mc_zw2_e  = -9999.0;
    m_mc_zw2_rec_m = -9999.0;

    m_mc_zw1zw2_m = -9999.0;
    m_mc_zw1zw2_e = -9999.0;
    m_mc_zw1zw2_rec_m = -9999.0;
  }

}

