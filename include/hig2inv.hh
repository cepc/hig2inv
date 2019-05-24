#ifndef _hig2inv_hh_
#define _hig2inv_hh_

#include <EVENT/LCCollection.h>
#include <IMPL/LCCollectionVec.h>
#include <EVENT/LCFloatVec.h> 
#include <EVENT/MCParticle.h> 
#include <marlin/Processor.h>
#include <EVENT/ReconstructedParticle.h>
#include <IMPL/MCParticleImpl.h>
#include <UTIL/PIDHandler.h>
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
#include <EVENT/LCFloatVec.h>
#include <EVENT/LCRelation.h>
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
        LCCollection* col_FastJet;
        MCParticle *a1_MC;
        LCCollection* Col_WoLeps;
        LCCollection* Col_FJPList2;
        LCCollection* Col_Jets;
        LCCollection* Col_Leps; 
        TFile *m_file;
        TTree *m_tree;
        TH1F *h_evtflw;
        TH1F* h_mc_init_plist;
        TH1F* h_mc_higgs_dlist;

        int LeptonID, RecoPID, tmpPID, PhotonPID, ElectronPID, MuonPID, NeutrinoEPID, NeutrinoMuonPID, TauPID, NeutrinoTauPID, ZPID, HiggsPID,ClusterID;
        int Dquark, Uquark, Squark, Cquark, Bquark,WPID;
        int nMC,nReco,nLepton, NCandiP, NCandiM, NParent, NDaughter, nDaughter, DIndex;
        int OverWrite,DecayFlag;
        float RecoEMax, RecoEMin, ZMass;
        int m_n_gamma, m_n_charged, m_n_lepton,m_n_leptonp, m_n_leptonm, m_n_chargedp, m_n_chargedm, m_n_Higgsdaughter, m_n_neutral,m_n_neutrino,m_Neutral_PID;
        int Nmup;
        int Nmum;
        unsigned int m_event;
        float m_sum_p_neutral[4], m_sum_p_photon[4],m_p_visible[4],m_sum_p_charged[4], m_p_leptonp[4], m_p_leptonm[4], m_p_dilepton[4], m_p_Zdaughters[4], m_p_Zdaughterp[4], m_p_Zdaughterm[4], m_p_Higgsdaughters[4], m_p_Higgsdaughter1[4],m_p_Higgsdaughter2[4];
        float m_m_dimu, m_m_recoil,m_e_recoil,m_e_dimu,m_p_dimu,m_p_recoil,m_miss_p;
        float m_sum_pt_photon, m_pt_dilepton;
        float RecoE,lepton_charge;
        float RecoP[3];
        float m_energy_visible, m_energy_neutrino,m_miss_m,m_miss_e,m_m_visible;
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
        float m_miss_phi2;
        float m_miss_Et;
        float m_miss_phi;
        //qq channel lepton information 
        int m_n_Muon;
        int m_n_Electron;
        float m_maxpx_muon;
        float m_maxpy_muon;
        float m_maxpz_muon;
        float m_maxpe_muon;

        float m_minpx_muon;
        float m_minpy_muon;
        float m_minpz_muon;
        float m_minpe_muon;

        float m_maxpx_electron;
        float m_maxpy_electron;
        float m_maxpz_electron;
        float m_maxpe_electron;

        float m_minpx_electron;
        float m_minpy_electron;
        float m_minpz_electron;
        float m_minpe_electron;
        float m_minangle_mujet;
        float m_minphi_mujet;
        float m_maxangle_mujet;
        float m_maxphi_mujet;
        float m_minangle_ejet;
        float m_minphi_ejet;
        float m_maxangle_ejet;
        float m_maxphi_ejet;

        int   n_muon_track;
        float m_muz_theta;
        //new information about isolation lepton
        float m_visible_p;
        float m_visible_pt;
        std::vector<TLorentzVector> FourMom_IsoMuonP;
        std::vector<TLorentzVector> FourMom_IsoMuonM;
        std::vector<TLorentzVector> FourMom_IsoEletronP;
        std::vector<TLorentzVector> FourMom_IsoEletronM;
        std::vector<TLorentzVector> P4_IsElectron;  
        std::vector<TLorentzVector> P4_IsMuon; 
        int   m_n_IsoMuonP;
        int   m_n_IsoMuonM;
        int   m_n_IsoMuon;
        int   m_n_IsoEletronP;
        int   m_n_IsoEletronM;
        int   m_n_IsoEletron;

        float m_m_Isdimu;
        float m_e_Isdimu;
        float m_p_Isdimu;
        float m_e_Isdimurec;
        float m_p_Isdimurec;
        float m_m_Isdimurec;

        float m_m_Isdie;
        float m_e_Isdie;
        float m_p_Isdie;
        float m_e_Isdierec;
        float m_p_Isdierec;
        float m_m_Isdierec;


        std::vector<float>  m_px_muon;
        std::vector<float>  m_py_muon;
        std::vector<float>  m_pz_muon;
        std::vector<float>  m_pe_muon;
        std::vector<float>  m_px_electron;
        std::vector<float>  m_py_electron;
        std::vector<float>  m_pz_electron;
        std::vector<float>  m_pe_electron;

        // TLorentzVector P_P, P_M, P_T[11];
        std::vector<TLorentzVector> P4_Muon;  

        std::vector<TLorentzVector> P4_Electron;  


        TLorentzVector P4_Neutral_Sum,P4_Charged_Sum,P_P, P_M, P_T, miss, FourMin_Lepton, FourMax_Lepton,P4_sum_p_photon;
        std::vector<TLorentzVector> FourMom_LeptonP, FourMom_LeptonM, FourMom_ChargedP, FourMom_ChargedM, FourMom_Charged, FourMom_Gamma,CandiP, CandiM;


        // jet info

        int m_n_jet;
        std::vector<TLorentzVector> P4_Jet;  

        std::vector<float> m_jet_m;
        std::vector<float> m_jet_p;
        std::vector<float> m_jet_pt;
        std::vector<float> m_jet_pz;
        std::vector<float> m_jet_e;

        std::vector<float> m_jet_phi;
        std::vector<float> m_jet_theta;

        std::vector<float> m_dijet_m;
        std::vector<float> m_dijet_p;
        std::vector<float> m_dijet_pt;
        std::vector<float> m_dijet_pz;
        std::vector<float> m_dijet_e;
        std::vector<float> m_dijet_rec_m;
        std::vector<float> m_dijet_dphi;
        std::vector<float> m_dijet_dang;
//Tau information

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

        float m_mc_init_leptonp_e;
        float m_mc_init_leptonp_p;
        float m_mc_init_leptonp_pt;
        float m_mc_init_leptonp_pz;

        float m_mc_init_leptonp_phi;
        float m_mc_init_leptonp_theta;

        float m_mc_init_leptonm_e;
        float m_mc_init_leptonm_p;
        float m_mc_init_leptonm_pt;
        float m_mc_init_leptonm_pz;

        float m_mc_init_leptonm_phi;
        float m_mc_init_leptonm_theta;

        float m_mc_init_dilepton_m;
        float m_mc_init_dilepton_e;
        float m_mc_init_dilepton_p;
        float m_mc_init_dilepton_pt;
        float m_mc_init_dilepton_pz;
        
        float m_mc_p_dilepton[4];
        float m_mc_p_redilepton[4];


        float m_mc_init_dilepton_rec_m;
        float m_mc_init_dilepton_dphi;
        float m_mc_init_dilepton_dang;
        int mc_n_charge;
        int m_mc_init_n_photon;
        std::vector<float> m_mc_init_photon_e;
        std::vector<float> m_mc_init_photon_p;
        std::vector<float> m_mc_init_photon_pt;
        std::vector<float> m_mc_init_photon_pz;
        std::vector<float> m_mc_init_photon_phi;  
        std::vector<float> m_mc_init_photon_theta;

        float m_mc_higgs_m;
        float m_mc_higgs_e;
        float m_mc_higgs_rec_m;

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

        float m_mc_zw1_m;
        float m_mc_zw1_p;
        float m_mc_zw1_pt;
        float m_mc_zw1_e;
        float m_mc_zw1_rec_m;

        float m_mc_zw2_m;
        float m_mc_zw2_p;
        float m_mc_zw2_pt;
        float m_mc_zw2_e;
        float m_mc_zw2_rec_m;
        
        float m_mc_zw1zw2_m;
        float m_mc_zw1zw2_e;
        float m_mc_zw1zw2_rec_m;

        int m_mc_zz_flag;
        int m_mc_ww_flag;
        int m_mc_h2gaugeboson_flag;

        //tau information 

        float sqrts ;	
        ReconstructedParticleImpl * taujet;
        TLorentzVector P4_tauP;
        TLorentzVector P4_tauM;
        int _nMCP;
        int _tracedTau,_TauT,npion,nmuon,nelec;
        float _trackcone, _tracken, _E_par,_E_p,_E_m,_trackcone1,_Ltracken;
        float _taumass;
        int _Tau;  //from here
        float _EnergicEn, _EnergicAng, _PhEn, _PhAng, _VisE, _InvM, _outConeE, _E_imp, _MCVisE, _MCE,_MCVisEN, _tracedEn;
        int _Num, _evtN,  _nTau,_nTauP,_nTauM, _fakeTau,_candiTau, _tracedTrk,_totalJet; 	
        float _jetC;
        float _tauM_impact,_tauP_impact,_TauTauImpact,_leadE,_D0err,_Z0err;
        float _TauTauD0,_TauTauZ0;
        float _TauP[3];
        float _leadP[3];
        float _VisP[3];
        float _P[3];
        float _visEnergy[999];
        float  _Jet; 
        float _TotalEvtP[3];
        float _qqP[3];
        float _TotalEvtEn;
        float _qqEn;
        float _RecoilM;
        float _qqRecoilM;
        float _TauTauM,_qqM,_MCqqM;
        float _D0, _Z0;
        int _nRecoTau, _nRecoP;
        float _visEp,_visEm,_invMp,_invMm,_MCvisEp,_MCvisEm;
        float _visPp[3];	
        float _visPm[3];	
        float mvaVal_mu;
        float mvaVal_e;
        float mvaVal_pi;
        float n_muon_Ptrack;
        float n_muon_Mtrack;
        int  Npause;
        void book_histogram();
        void book_tree();
        bool buildZToff();
        bool preselection();

        void saveNeutral( int nReco, LCCollection* col_Reco );
        void savePhoton( int nReco, LCCollection* col_Reco );
        void selectCharged( int nReco, LCCollection* col_Reco );
        void selectLepton( int nReco, LCCollection* col_Reco);
        void selectIsoLepton(int nLepton,LCCollection* Col_Leps,std::vector<TLorentzVector> P4_jet);
        void saveDiElectron(std::vector<TLorentzVector> FourMom_IsoEletronP,std::vector<TLorentzVector> FourMom_IsoEletronM);
        void saveDiMuon(std::vector<TLorentzVector> FourMom_IsoMuonP,std::vector<TLorentzVector> FourMom_IsoMuonM);
        void saveVisible(TLorentzVector P4_Neutral_Sum,TLorentzVector P4_Charged_Sum);
        void saveMinAndMaxLepton(std::vector<TLorentzVector> FourMom_LeptonP, std::vector<TLorentzVector> FourMom_LeptonM);	
        int getPID(ReconstructedParticle* a_Reco);	
        void saveRecInfo(std::vector<TLorentzVector> FourMom_LeptonP, std::vector<TLorentzVector> FourMom_LeptonM);
        void saveMuonIf(std::vector<TLorentzVector> P4_Muon,std::vector<TLorentzVector> P4_jet);		
        void saveElectronIf(std::vector<TLorentzVector> P4_Electron,std::vector<TLorentzVector> P4_jet);		
        //Save qqH channel
        void saveFastJet(LCCollection* col_FastJet);
        void saveJetInfo( std::vector<TLorentzVector> P4_jet );
        //MC information
        void checkGenMCInfo(LCCollection* col_MC);
        void saveNeutrino( int NParent, int NDaughter, MCParticle *a1_MC, int tmpPID, float MCEn );
        void printDecayChain( int MCParticleID, MCParticle *mcp );
        void printMCinfo( int MCParticleID, int flag, MCParticle *mcp, std::vector<MCParticle*> pvec, std::vector<MCParticle*> dvec );
        void saveMCTruthInfo(LCCollection* col_MC);
        //tau information 
        void RecoAna( LCEvent * evtP );
        void fillMCInfo();
        void variable_init();

};
#endif