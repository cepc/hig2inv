// -*- C++ -*- //  
//
// Description: Higgs -> Invisible    
//
// Original Author:  tanyh <tanyh@ihep.ac.cn>
//         Created:  [2019-03-13 ] 
//         Inspired by CHEN Zhenxing's code   
//
// system include files
//
// for MCParticle, collection and reconstruction
#include <hig2inv.hh>
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

    Processname="muon";  //muon is muonmuon channel,qq is qq channel.
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
    //tau information 
    registerProcessorParameter( "TrackCone",
            "Cone between tracks",
            _trackcone,
            _trackcone);	
    registerProcessorParameter( "smallTrackCone",
            "Cone between tracks",
            _trackcone1,
            _trackcone1);	
    
    registerProcessorParameter( "TauMass",
            "Mass of Tau",
            _taumass,
            _taumass);	
    
    registerProcessorParameter( "E_par",
            "energy importance",
            _E_par,
            _E_par);	

    registerProcessorParameter( "LeadTrackEn",
            "leading tracks energy",
            _Ltracken,
            _Ltracken);	
    

    registerProcessorParameter( "TrackEn",
            "tracks energy",
            _tracken,
            _tracken);	

}

void hig2inv::init() {
    book_histogram();
    book_tree();

}

void hig2inv::processEvent( LCEvent * evt ) {	

    if(evt){
        try{
            variable_init();
            col_Reco = evt->getCollection( "ArborPFOs" );

            col_MC = evt->getCollection( "MCParticle" );
            Col_WoLeps  = evt->getCollection( "WithoutIsoLeps" ); 
			Col_Leps    = evt->getCollection( "IsoLeps");                         
            if(buildZToff()){
            if  (Processname == "qq" || Processname == "BKGQ"){
            col_FastJet = evt->getCollection("FastJets");   

            saveFastJet(col_FastJet);
            saveJetInfo( P4_Jet );
            } 				
            _nMCP = col_MC->getNumberOfElements();
            nReco = col_Reco->getNumberOfElements();
            nLepton = Col_Leps->getNumberOfElements();
            m_event=evt->getEventNumber();
            saveNeutral( nReco, col_Reco );
            savePhoton( nReco, col_Reco );
            selectCharged( nReco, col_Reco );
            selectLepton(nLepton,Col_Leps,P4_Jet);
            saveVisible(P4_Neutral_Sum, P4_Charged_Sum);
            saveRecInfo(FourMom_LeptonP,FourMom_LeptonM);
            RecoAna( evt );
  

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
    m_tree->Branch("m_sum_p_photon", m_sum_p_photon, "m_sum_p_photon[4]/F");
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

    m_tree->Branch("m_sum_pt_photon", &m_sum_pt_photon, "m_sum_pt_photon/F");
    m_tree->Branch("m_pt_dilepton",  &m_pt_dilepton,  "m_pt_dilepton/F");

    m_tree->Branch("m_n_charged",  &m_n_charged,  "m_n_charged/I");
    m_tree->Branch("m_n_gamma",  &m_n_gamma,  "m_n_gamma/I");
    m_tree->Branch("m_n_leptonp",  &m_n_leptonp,  "m_n_leptonp/I");
    m_tree->Branch("m_n_lepton",  &m_n_lepton,  "m_n_lepton/I");
    m_tree->Branch("m_n_leptonm",  &m_n_leptonm,  "m_n_leptonm/I");
    m_tree->Branch("m_n_chargedp",  &m_n_chargedp,  "m_n_chargedp/I");
    m_tree->Branch("m_n_chargedm",  &m_n_chargedm,  "m_n_chargedm/I");
    m_tree->Branch("m_n_Higgsdaughter",  &m_n_Higgsdaughter,  "m_n_Higgsdaughter/I");
    m_tree->Branch("m_n_neutrino",  &m_n_neutrino,  "m_n_neutrino/I");

    m_tree->Branch("m_m_dimu",  &m_m_dimu,  "m_m_dimu/F");
    m_tree->Branch("m_e_dimu",  &m_e_dimu,  "m_e_dimu/F");
    m_tree->Branch("m_p_dimu",  &m_p_dimu,  "m_p_dimu/F");
    // m_tree->Branch("m_m_recoil",  m_m_recoil,  "m_m_recoil[11]/F");
    m_tree->Branch("m_m_recoil",  &m_m_recoil,  "m_m_recoil/F");
    m_tree->Branch("m_e_recoil",  &m_e_recoil,  "m_e_recoil/F");
    m_tree->Branch("m_p_recoil",  &m_p_recoil,  "m_p_recoil/F");
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
    m_tree->Branch("m_miss_m",  &m_miss_m,  "m_miss_m/F");
    m_tree->Branch("m_miss_e",  &m_miss_e,  "m_miss_e/F");
    m_tree->Branch("m_miss_p",  &m_miss_p,  "m_miss_p/F");

    m_tree->Branch("m_mine_lepton",  &m_mine_lepton,  "m_mine_lepton/F");
    m_tree->Branch("m_maxe_lepton",  &m_maxe_lepton,  "m_maxe_lepton/F");

    m_tree->Branch("m_minp_lepton",  &m_minp_lepton,  "m_minp_lepton[4]/F");
    m_tree->Branch("m_maxp_lepton",  &m_maxp_lepton,  "m_maxp_lepton[4]/F");

    m_tree->Branch("m_miss_phi",  &m_miss_phi,  "m_miss_phi/F");

    m_tree->Branch("m_miss_Et",  &m_miss_Et,  "m_miss_Et/F");
    m_tree->Branch("m_miss_phi2",  &m_miss_phi2,  "m_miss_phi2/F");	
    
//new qq channel branch

    m_tree->Branch("m_n_Muon",  &m_n_Muon,  "m_n_Muon/I");
    m_tree->Branch("m_n_Electron",  &m_n_Electron,  "m_n_Electron/I");  

    m_tree->Branch("m_px_muon", &m_px_muon);
    m_tree->Branch("m_py_muon", &m_py_muon);
    m_tree->Branch("m_pz_muon", &m_pz_muon);
    m_tree->Branch("m_pe_muon", &m_pe_muon);
    m_tree->Branch("m_px_electron", &m_px_electron);
    m_tree->Branch("m_py_electron", &m_py_electron);
    m_tree->Branch("m_pz_electron", &m_pz_electron);
    m_tree->Branch("m_pe_electron", &m_pe_electron);

    m_tree->Branch("m_maxpx_muon",  &m_maxpx_muon,  "m_maxpx_muon/F");
    m_tree->Branch("m_maxpy_muon",  &m_maxpy_muon,  "m_maxpy_muon/F");
    m_tree->Branch("m_maxpz_muon",  &m_maxpz_muon,  "m_maxpz_muon/F");
    m_tree->Branch("m_maxpe_muon",  &m_maxpe_muon,  "m_maxpe_muon/F");

    m_tree->Branch("m_maxangle_mujet",  &m_maxangle_mujet,  "m_maxangle_mujet/F");
    m_tree->Branch("m_maxphi_mujet",  &m_maxphi_mujet,  "m_maxphi_mujet/F");
    m_tree->Branch("m_maxangle_ejet",  &m_maxangle_ejet,  "m_maxangle_ejet/F");
    m_tree->Branch("m_maxphi_ejet",  &m_maxphi_ejet,  "m_maxphi_ejet/F");

    m_tree->Branch("m_minangle_mujet",  &m_minangle_mujet,  "m_minangle_mujet/F");
    m_tree->Branch("m_minphi_mujet",  &m_minphi_mujet,  "m_minphi_mujet/F");
    m_tree->Branch("m_minangle_ejet",  &m_minangle_ejet,  "m_minangle_ejet/F");
    m_tree->Branch("m_minphi_ejet",  &m_minphi_ejet,  "m_minphi_ejet/F");

    m_tree->Branch("m_minpx_muon",  &m_minpx_muon,  "m_minpx_muon/F");
    m_tree->Branch("m_minpy_muon",  &m_minpy_muon,  "m_minpy_muon/F");
    m_tree->Branch("m_minpz_muon",  &m_minpz_muon,  "m_minpz_muon/F");
    m_tree->Branch("m_minpe_muon",  &m_minpe_muon,  "m_minpe_muon/F");	

    m_tree->Branch("m_maxpx_electron",  &m_maxpx_electron,  "m_maxpx_electron/F");	
    m_tree->Branch("m_maxpy_electron",  &m_maxpy_electron,  "m_maxpy_electron/F");
    m_tree->Branch("m_maxpz_electron",  &m_maxpz_electron,  "m_maxpz_electron/F");
    m_tree->Branch("m_maxpe_electron",  &m_maxpe_electron,  "m_maxpe_electron/F");

    m_tree->Branch("m_minpx_electron",  &m_minpx_electron,  "m_minpx_electron/F");
    m_tree->Branch("m_minpy_electron",  &m_minpy_electron,  "m_minpy_electron/F");
    m_tree->Branch("m_minpz_electron",  &m_minpz_electron,  "m_minpz_electron/F");
    m_tree->Branch("m_minpe_electron",  &m_minpe_electron,  "m_minpe_electron/F");
    
    // Jets
    if (Processname == "qq" || Processname == "BKGQ"){
    m_tree->Branch("m_n_jet",  &m_n_jet,  "m_n_jet/I");

    m_tree->Branch("jet_m", &m_jet_m);
    m_tree->Branch("jet_p", &m_jet_p);
    m_tree->Branch("jet_pt", &m_jet_pt);
    m_tree->Branch("jet_pz", &m_jet_pz);
    m_tree->Branch("jet_e", &m_jet_e);

    m_tree->Branch("jet_phi", &m_jet_phi);
    m_tree->Branch("jet_theta", &m_jet_theta);
    
    m_tree->Branch("dijet_e", &m_dijet_e);
    m_tree->Branch("dijet_p", &m_dijet_p);
    m_tree->Branch("dijet_pt", &m_dijet_pt);
    m_tree->Branch("dijet_pz", &m_dijet_pz);
    m_tree->Branch("dijet_m", &m_dijet_m);
    m_tree->Branch("dijet_rec_m", &m_dijet_rec_m);
    m_tree->Branch("dijet_dphi", &m_dijet_dphi);
    m_tree->Branch("dijet_dang", &m_dijet_dang);
    } 
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

    //tau information 

    m_tree->Branch("nTau", 		&_nTau, 	"nTau/I");
    m_tree->Branch("nTauP", 		&_nTauP, 	"nTauP/I");
    m_tree->Branch("nTauM", 		&_nTauM, 	"nTauM/I");
    m_tree->Branch("fakeTau", 		&_fakeTau, 	"fakeTau/I");
    m_tree->Branch("totalJet", 		&_totalJet, 	"totalJet/I");
    m_tree->Branch("visEnergy[999]", 	_visEnergy, 	"visEnergy[999]/F");

    m_tree->Branch("visEp",	&_visEp,		"visEp/F");
    m_tree->Branch("visEm",       &_visEm,          "visEm/F");
    m_tree->Branch("visPp[3]",	_visPp,		"visPp[3]/F");
    m_tree->Branch("visPm[3]",  _visPm,          "visPm[3]/F");
    m_tree->Branch("invMp",	&_invMp,		"invMp/F");
    m_tree->Branch("invMm",       &_invMm,          "invMm/F");

    m_tree->Branch("evtN",    &_evtN,       "evtN/I");
    m_tree->Branch("TauTauImpact", &_TauTauImpact, "TauTauImpact/F");
    m_tree->Branch("TauTauD0", &_TauTauD0, "TauTauD0/F");
    m_tree->Branch("TauTauZ0", &_TauTauZ0, "TauTauZ0/F");
    m_tree->Branch("tauP_impact", &_tauP_impact, "tauP_impact/F");
    m_tree->Branch("tauM_impact", &_tauM_impact, "tauM_impact/F");
    m_tree->Branch("RecoilM",    &_RecoilM,       "RecoilM/F");
    m_tree->Branch("qqRecoilM",    &_qqRecoilM,       "qqRecoilM/F");
    m_tree->Branch("TauTauM",    &_TauTauM,       "TauTauM/F");
    m_tree->Branch("qqM",    &_qqM,       "qqM/F");
    m_tree->Branch("TotalEvtEn",    &_TotalEvtEn,       "TotalEvtEn/F");
    m_tree->Branch("TotalEvtP[3]",    _TotalEvtP,       "TotalEvtP[3]/F");

}

void hig2inv::variable_init() {

    m_n_charged = 0;
    m_n_neutral = 0;
    Nmum = 0;
    Nmup = 0;
    m_Neutral_PID = 0;
    m_n_leptonp = 0;
    m_n_lepton = 0;	
    m_n_leptonm = 0;
    m_n_chargedp = 0;
    m_n_chargedm = 0;
    m_n_gamma = 0;
    m_n_neutrino = 0;
    m_n_Higgsdaughter = 0;
    m_energy_neutrino = 0.;
    m_m_dimu = 0.0;  //m_m_visible -> m_m_dimu;
    m_e_dimu = 0.0;
    m_p_dimu = 0.0;
    m_p_recoil=0.0;
    m_m_recoil=0.0;
    m_e_recoil=-999.;
    m_energy_visible = 0.;
    m_m_visible = 0.;
    m_phi_dilepton_1 = 0;
    m_phi_dilepton_2 = 0;
    m_cos_miss = 0.0;
    m_cos_Z =0.0;
    m_angle_dilepton = 0;
    m_delta_pt = 0;
    m_PID_HiggsDaughter = 0;
    m_PID_Zdaughter = 0;
    m_PID_Higgsdaughter[0] = 0;
    m_PID_Higgsdaughter[1] = 0;
    MinZThrDis = 10;
    DIndex = 0;
    //New add 
    m_sum_pt_photon = 0;
    m_pt_dilepton = 0;
    m_miss_m = 0.0;
    m_miss_e = 0.0;
    m_miss_p = 0.0;
    m_mine_lepton = 0.0;
    m_maxe_lepton = 0.0;

    m_miss_phi = 0.0;
    m_miss_Et = 0.0;
    m_miss_phi2 = 0.0;
    m_n_Muon = 0;
    m_n_Electron = 0;
// Tau information

    TLorentzVector beamp(0,0,120.0,120.0);
    TLorentzVector beamm(0,0,-120.0,120.0);
    scale1 = (gRandom->Gaus(1, 0.0024));
    scale2 = (gRandom->Gaus(1, 0.0024));
    TLorentzVector ecms(0, 0, 0, 240);
    P_T = ecms;
    sqrts=240.0;
    // Jet information
    m_n_jet = 0;

    for(int i=0; i<4; i++) {
        m_sum_p_neutral[i] = 0.0;
        m_sum_p_photon[i] = 0.0;
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
        miss[i] = 0.0;
        FourMax_Lepton[i]=0.0;
        m_minp_lepton[i] = 0.0;
        m_maxp_lepton[i] = 0.0;
 

        P4_Charged_Sum[i]= 0.0;//change to get visble energy and mass
        P4_Neutral_Sum[i]= 0.0;//change to get visble energy and mass
        P4_sum_p_photon[i]= 0.0;
        m_p_visible[i] = 0.0;
  

    }  
    //qq channel lepton information

    m_maxpx_muon=0.0;
    m_maxpy_muon=0.0;
    m_maxpz_muon=0.0;
    m_maxpe_muon=0.0;
    m_minpx_muon=0.0;
    m_minpy_muon=0.0;
    m_minpz_muon=0.0;
    m_minpe_muon=0.0;

    m_maxpx_electron=0.0;
    m_maxpy_electron=0.0;
    m_maxpz_electron=0.0;
    m_maxpe_electron=0.0;

    m_minpx_electron=0.0;
    m_minpy_electron=0.0;
    m_minpz_electron=0.0;
    m_minpe_electron=0.0;
    
    m_px_muon.clear();
    m_py_muon.clear();
    m_pz_muon.clear();
    m_pe_muon.clear();

    m_px_electron.clear();
    m_py_electron.clear();
    m_pz_electron.clear();
    m_pe_electron.clear();

    P4_Electron.clear();
    P4_Muon.clear();
    //Jet information      
    P4_Jet.clear();     
    m_jet_m.clear();
    m_jet_p.clear();
    m_jet_pt.clear();
    m_jet_pz.clear();
    m_jet_e.clear();
    m_jet_phi.clear();
    m_jet_theta.clear();
  
    m_dijet_m.clear();
    m_dijet_p.clear();
    m_dijet_pt.clear();
    m_dijet_pz.clear();
    m_dijet_e.clear();
    m_dijet_rec_m.clear();
    m_dijet_dphi.clear();
    m_dijet_dang.clear(); 


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

    int counter =0;
    for(int i = 0; i < nReco; i++) {
        ReconstructedParticle *a_Reco = dynamic_cast<EVENT::ReconstructedParticle *>(col_Reco->getElementAt(i));
        if(a_Reco->getCharge()!=0) continue;
        if(a_Reco->getType()!=PhotonPID) continue;
        if(fabs(a_Reco->getMomentum()[2]/a_Reco->getEnergy())>0.995) continue; // acceptance of the detector
            P4_sum_p_photon[3] += a_Reco->getEnergy();
            P4_sum_p_photon[0] += a_Reco->getMomentum()[0];
            P4_sum_p_photon[1] += a_Reco->getMomentum()[1];
            P4_sum_p_photon[2] += a_Reco->getMomentum()[2];
            counter++; 
    }
    m_n_gamma = counter;
    m_sum_p_photon[0]=P4_sum_p_photon[0];
    m_sum_p_photon[1]=P4_sum_p_photon[1];
    m_sum_p_photon[2]=P4_sum_p_photon[2];
    m_sum_p_photon[3]=P4_sum_p_photon[3];
    m_sum_pt_photon = sqrt(m_sum_p_photon[0]*m_sum_p_photon[0]+m_sum_p_photon[1]*m_sum_p_photon[1]);
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

void hig2inv::selectLepton( int nLepton, LCCollection* Col_Leps,std::vector<TLorentzVector> P4_jet) {
    int count = 0;
    for(int i = 0; i < nLepton; i++) {
        ReconstructedParticle *a_Reco = dynamic_cast<EVENT::ReconstructedParticle *>(Col_Leps->getElementAt(i));
        if(a_Reco->getCharge()==0) continue;
        lepton_charge = a_Reco->getCharge();
        RecoPID = abs(a_Reco->getType());
        RecoE = a_Reco->getEnergy();
        RecoP[0] = a_Reco->getMomentum()[0];
        RecoP[1] = a_Reco->getMomentum()[1];
        RecoP[2] = a_Reco->getMomentum()[2];
        TLorentzVector curr(RecoP[0], RecoP[1], RecoP[2], RecoE);
    if ( RecoE > 0.0 && RecoE < RecoEMax) {
        if (lepton_charge > 0.1)FourMom_ChargedP.push_back(curr);
        if (lepton_charge < -0.1)FourMom_ChargedM.push_back(curr);
        if (Processname == "qq" || Processname == "BKGQ"){
           if(RecoPID == MuonPID) {
               if( lepton_charge >  0.1 ){
                   FourMom_LeptonP.push_back( curr );

                }
                if( lepton_charge < -0.1 ){
                   FourMom_LeptonM.push_back( curr );	
                }
                   P4_Muon.push_back( curr );
            }    
            if(RecoPID == ElectronPID) {
               if( lepton_charge >  0.1 ){
                   FourMom_LeptonP.push_back( curr );

                }
                if( lepton_charge < -0.1 ){
                    FourMom_LeptonM.push_back( curr );			   
                }
                P4_Electron.push_back( curr );
                count++;
            }
        
        }
        else{  //qqH record all lepton.
        if(RecoPID == LeptonID ) {
           if( lepton_charge >  0.1 )FourMom_LeptonP.push_back( curr );
           if( lepton_charge < -0.1 )FourMom_LeptonM.push_back( curr );
        }
        }	
    }
    }
    saveMinAndMaxLepton(FourMom_LeptonP,FourMom_LeptonM);
    m_n_leptonp = FourMom_LeptonP.size();
    m_n_leptonm = FourMom_LeptonM.size();
    m_n_lepton = m_n_leptonp + m_n_leptonm;
    m_n_chargedp = FourMom_ChargedP.size();
    m_n_chargedm = FourMom_ChargedM.size();
//qq channel information
   // if (Processname == "qq" || Processname == "BKGQ"){
    m_n_Muon=P4_Muon.size();
    //m_n_Muon=count;
    m_n_Electron=P4_Electron.size();

    saveMuonIf(P4_Muon,P4_jet);
    saveElectronIf(P4_Electron, P4_jet);
    //}

}
void hig2inv::saveMuonIf( std::vector<TLorentzVector> P4_Muon,std::vector<TLorentzVector> P4_jet ){
    int nMuon=P4_Muon.size();
    int nJet=P4_jet.size();
    float min_value=100.0;
    float max_value=0.0;
    for(int i=0; i<nMuon; i++){
    TLorentzVector P_Muon ;
    P_Muon = P4_Muon[i];
    m_px_muon.push_back(P_Muon[0]);
    m_py_muon.push_back(P_Muon[1]);
    m_pz_muon.push_back(P_Muon[2]);
    m_pe_muon.push_back(P_Muon[3]);
    if  (P_Muon[3] > max_value){
        max_value = P_Muon.E();
        m_maxpx_muon=P_Muon.Px();
        m_maxpy_muon=P_Muon.Py();
        m_maxpz_muon=P_Muon.Pz();
        m_maxpe_muon=P_Muon.E();
    }
    if  (P_Muon[3] < min_value){
        min_value = P_Muon.E();
        m_minpx_muon=P_Muon.Px();
        m_minpy_muon=P_Muon.Py();
        m_minpz_muon=P_Muon.Pz();
        m_minpe_muon=P_Muon.E();
    }
    if (nMuon!=0){
    TLorentzVector currP(m_maxpx_muon,m_maxpy_muon,m_maxpz_muon,m_maxpe_muon); 
    float angle=0.0;
    float phi=0.0;
    float m_angle1_mujet=0.0;
    float m_phi1_mujet=0.0;
    for(int i=0; i<nJet; i++){  

        m_angle1_mujet=(currP - P4_jet[i]).Theta();
        m_phi1_mujet=(currP - P4_jet[i]).Phi();
        if (m_angle1_mujet>angle){
            angle=m_angle1_mujet;
            m_maxangle_mujet=m_angle1_mujet*180.0/M_PI;
        }

        if (m_phi1_mujet>phi){
            phi=m_phi1_mujet;
            m_maxphi_mujet=m_phi1_mujet*180.0/M_PI;
        }	
    float maxangle=360.0;
    float maxphi=360.0;
    float m_angle2_mujet=0.0;
    float m_phi2_mujet=0.0;
    for(int i=0; i<nJet; i++){  

        m_angle2_mujet=(currP - P4_jet[i]).Theta();
        m_phi2_mujet=(currP - P4_jet[i]).Phi();
        if (m_angle2_mujet<maxangle){
            maxangle=m_angle2_mujet;
            m_minangle_mujet=m_angle2_mujet*180.0/M_PI;
        }

        if (m_phi2_mujet<maxphi){
            maxphi=m_phi2_mujet;
            m_minphi_mujet=m_phi2_mujet*180.0/M_PI;
        }		
    }
    }
    }
    }
    if (nMuon==0){
    m_maxpx_muon=0.0;
    m_maxpy_muon=0.0;
    m_maxpz_muon=0.0;
    m_maxpe_muon=0.0;
    m_minpx_muon=0.0;
    m_minpy_muon=0.0;
    m_minpz_muon=0.0;
    m_minpe_muon=0.0;
    m_maxphi_mujet=0.0;
    m_maxangle_mujet=0.0;
    m_minphi_mujet=0.0;
    m_minangle_mujet=0.0;
    }

}

void hig2inv::saveElectronIf( std::vector<TLorentzVector> P4_Electron,std::vector<TLorentzVector> P4_jet){
    int nElectron=P4_Electron.size();
    float min_value=100.0;
    float max_value=0.0;
    int nJet=P4_jet.size();
    for(int i=0; i<nElectron; i++){
    TLorentzVector P_Electron = P4_Electron[i];
    m_px_electron.push_back(P_Electron[0]);
    m_py_electron.push_back(P_Electron[1]);
    m_pz_electron.push_back(P_Electron[2]);
    m_pe_electron.push_back(P_Electron[3]);
    if  (P_Electron[3] > max_value){
        max_value = P_Electron.E();
        m_maxpx_electron=P_Electron.Px();
        m_maxpy_electron=P_Electron.Py();
        m_maxpz_electron=P_Electron.Pz();
        m_maxpe_electron=P_Electron.E();
    }
    if  (P_Electron[3] < min_value){
        min_value = P_Electron.E();
        m_minpx_electron=P_Electron.Px();
        m_minpy_electron=P_Electron.Py();
        m_minpz_electron=P_Electron.Pz();
        m_minpe_electron=P_Electron.E();
    }
}
    if (nElectron!=0){
    TLorentzVector currP(m_maxpx_electron,m_maxpy_electron,m_maxpz_electron,m_maxpe_electron); 
    float angle=0.0;
    float phi=0.0;
    float m_angle1_ejet=0.0;
    float m_phi1_ejet=0.0;
    for(int i=0; i<nJet; i++){  

        m_angle1_ejet=(currP - P4_jet[i]).Theta();
        m_phi1_ejet=(currP - P4_jet[i]).Phi();
        if (m_angle1_ejet>angle){
            angle=m_angle1_ejet;
            m_maxangle_ejet=m_angle1_ejet*180.0/M_PI;
        }

        if (m_phi1_ejet>phi){
            phi=m_phi1_ejet;
            m_maxphi_ejet=m_phi1_ejet*180.0/M_PI;
        }		
    }
    float maxangle=360.0;
    float maxphi=360.0;
    float m_angle2_ejet=0.0;
    float m_phi2_ejet=0.0;
    for(int i=0; i<nJet; i++){  

        m_angle2_ejet=(currP - P4_jet[i]).Theta();
        m_phi2_ejet=(currP - P4_jet[i]).Phi();
        if (m_angle2_ejet<maxangle){
            maxangle=m_angle2_ejet;
            m_minangle_ejet=m_angle2_ejet*180.0/M_PI;
        }

        if (m_phi2_ejet<maxphi){
            maxphi=m_phi2_ejet;
            m_minphi_ejet=m_phi2_ejet*180.0/M_PI;
        }		
    }
    }
    if (nElectron==0){
    m_maxpx_electron=0.0;
    m_maxpy_electron=0.0;
    m_maxpz_electron=0.0;
    m_maxpe_electron=0.0;
    m_minpx_electron=0.0;
    m_minpy_electron=0.0;
    m_minpz_electron=0.0;
    m_minpe_electron=0.0;
    m_maxphi_ejet=0.0;
    m_maxangle_ejet=0.0;
    m_minphi_ejet=0.0;
    m_minangle_ejet=0.0;
    }

}

void hig2inv::saveMinAndMaxLepton( std::vector<TLorentzVector> FourMom_LeptonP, std::vector<TLorentzVector> FourMom_LeptonM ) {
    int n_leptonp=0;
    int n_leptonm=0;
    n_leptonp = FourMom_LeptonP.size();
    n_leptonm = FourMom_LeptonM.size();
    if (n_leptonp>0 && n_leptonm>0){
        float min_value=100.0;
        float max_value=0.0;
        for (int i=0; i< n_leptonp; i++){
        for (int j=0; j< n_leptonm; j++){
            float E_leptonp=FourMom_LeptonP[i].E();
            float E_leptonm=FourMom_LeptonM[j].E();
            if (E_leptonp <min_value || E_leptonm<min_value){
                if(E_leptonp<E_leptonm){
                min_value=E_leptonp;
                FourMin_Lepton=FourMom_LeptonP[i];
                }
                if (E_leptonp >= E_leptonm){
                min_value=E_leptonm;
                FourMin_Lepton=FourMom_LeptonM[j];
            }
            }
            if (E_leptonp >max_value || E_leptonm>max_value){
                if(E_leptonp>E_leptonm){
                max_value=E_leptonp;
                FourMax_Lepton=FourMom_LeptonP[i];
                }
                if (E_leptonp <= E_leptonm){
                max_value=E_leptonm;
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
   miss = P_T - P4_Charged_Sum - P4_Neutral_Sum;
   m_miss_m = miss.M();
   m_miss_e = miss.E();
   m_miss_p = miss.P();  
   m_cos_miss = miss.CosTheta();
   m_miss_phi = miss.Phi();
   m_miss_Et = miss.Et();
   m_miss_phi2 = atan2(miss[1],miss[0])*180./3.14159265;
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
        m_p_dimu = (P_P + P_M).P();
    // save recil mass
        m_e_recoil = (P_T - P_P - P_M).E();
        m_p_recoil = (P_T - P_P - P_M).P();
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
        m_angle_dilepton = P_P.Angle(P_M.Vect())*180./3.1415926;
        m_pt_dilepton = (P_P+P_M).Pt();
        m_delta_pt = m_pt_dilepton - m_sum_pt_photon;
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
       m_p_leptonp[k] = 0.0;
       m_p_leptonm[k] = P_M[k];
    }
  }
  if( nlep_m == 0 && nlep_p != 0 ) {
    for(int k=0; k<4; k++) {
    m_p_leptonp[k] = P_P[k];
    m_p_leptonm[k] = 0.0;
  }
  }
    if( nlep_m == 0 && nlep_p == 0 ) {
    for(int k=0; k<4; k++) {
    m_p_leptonp[k] = 0.0;
    m_p_leptonm[k] = 0.0;
  }
  }
  if( nlep_p == 0 || nlep_m == 0 ) {
   for(int k=0; k<4; k++) {
   m_p_dilepton[k] = 0.0;  
   m_m_recoil = 0.0;
   m_e_recoil = 0.0;
   m_p_recoil = 0.0;
   m_pt_dilepton = 0.0;
   m_m_dimu = 0.0;
   m_p_dimu = 0.0;
   m_phi_dilepton_2 = 0.0;
   m_angle_dilepton = 0.0;
   m_delta_pt = 0.0;
   m_cos_Z = 0.0;
  }
  }
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
        if ( pdgid ==  MuonPID ) {
            Nmup++;
        }
        if(pdgid == - MuonPID ) {
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
    if (Processname == "BKGQ"){
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

void hig2inv::saveFastJet( LCCollection* col_FastJet){
  int ncol = col_FastJet->getNumberOfElements();
  for( int i = 0; i < ncol; i++) {
   ReconstructedParticle *reco_jet = dynamic_cast<EVENT::ReconstructedParticle *>(col_FastJet->getElementAt(i));  
    float jet_px     = reco_jet->getMomentum()[0];
    float jet_py     = reco_jet->getMomentum()[1];
    float jet_pz     = reco_jet->getMomentum()[2];
    float jet_e      = reco_jet->getEnergy();
    TLorentzVector p4vec(jet_px, jet_py, jet_pz, jet_e); 
    P4_Jet.push_back( p4vec );
  }
    m_n_jet = ncol; 
}

void hig2inv::saveJetInfo( std::vector<TLorentzVector> P4_jet ) {

 int njet = P4_jet.size();
 for( int i=0; i < njet; i++ ) {
    
    m_jet_m.push_back(P4_jet[i].M());
    m_jet_p.push_back(P4_jet[i].P());
    m_jet_pt.push_back(P4_jet[i].Pt());
    m_jet_pz.push_back(P4_jet[i].Pz());
    m_jet_e.push_back(P4_jet[i].E());

    m_jet_phi.push_back(P4_jet[i].Phi()     *180.0/M_PI );
    m_jet_theta.push_back(P4_jet[i].Theta() *180.0/M_PI );

    for( int j=i+1; j < njet; j++) {

      float mjj     = ( P4_jet[i] + P4_jet[j] ).M();
      float pjj     = ( P4_jet[i] + P4_jet[j] ).P();
      float ptjj    = ( P4_jet[i] + P4_jet[j] ).Pt();
      float pzjj    = ( P4_jet[i] + P4_jet[j] ).Pz();
      float ejj     = ( P4_jet[i] + P4_jet[j] ).E();
      float rec_mjj = ( P_T - P4_jet[i] - P4_jet[j] ).M();
      float dphi    = fabs(P4_jet[i].DeltaPhi(P4_jet[j])) *180.0/M_PI;
      float dang    = P4_jet[i].Angle(P4_jet[j].Vect())   *180.0/M_PI;

      m_dijet_m.push_back( mjj );
      m_dijet_p.push_back( pjj );
      m_dijet_pt.push_back( ptjj );
      m_dijet_pz.push_back( pzjj );
      m_dijet_e.push_back( ejj );
      m_dijet_rec_m.push_back( rec_mjj );
      m_dijet_dphi.push_back( dphi );
      m_dijet_dang.push_back( dang );
    }
  }
      
  if( njet <= 1 ) {  // Can not calculate dijet variables

    m_dijet_m.push_back( 0.0 );
    m_dijet_p.push_back( 0.0 );
    m_dijet_pt.push_back( 0.0 );
    m_dijet_pz.push_back( 0.0 );
    m_dijet_e.push_back( 0.0 );
    m_dijet_rec_m.push_back( 0.0 );
    m_dijet_dphi.push_back( 0.0 );
    m_dijet_dang.push_back( 0.0 );
    
    if( njet == 0 ) {

      m_jet_m.push_back( 0.0 );
      m_jet_p.push_back( 0.0 );
      m_jet_pt.push_back( 0.0 );
      m_jet_pz.push_back( 0.0 );
      m_jet_e.push_back( 0.0 );
      m_jet_phi.push_back( 0.0 );
      m_jet_theta.push_back( 0.0 );
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
    
      float px = mcp->getMomentum()[0];
      float py = mcp->getMomentum()[1];
      float pz = mcp->getMomentum()[2];
      float e = mcp->getEnergy();
      
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
      
      float px = dvec[j]->getMomentum()[0];
      float py = dvec[j]->getMomentum()[1];
      float pz = dvec[j]->getMomentum()[2];
      float e = dvec[j]->getEnergy();
      
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
      
      float px = dvec[j]->getMomentum()[0];
      float py = dvec[j]->getMomentum()[1];
      float pz = dvec[j]->getMomentum()[2];
      float e = dvec[j]->getEnergy();
      
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
  
    float mll     = ( P4_MCTruth_LeptonPlus[0] + P4_MCTruth_LeptonMinus[0] ).M();
    float ell     = ( P4_MCTruth_LeptonPlus[0] + P4_MCTruth_LeptonMinus[0] ).E();
    float pll     = ( P4_MCTruth_LeptonPlus[0] + P4_MCTruth_LeptonMinus[0] ).P();
    float ptll    = ( P4_MCTruth_LeptonPlus[0] + P4_MCTruth_LeptonMinus[0] ).Pt();
    float pzll    = ( P4_MCTruth_LeptonPlus[0] + P4_MCTruth_LeptonMinus[0] ).Pz();
    float rec_mll = (P_T - P4_MCTruth_LeptonPlus[0] - P4_MCTruth_LeptonMinus[0] ).M();
    float dphi    = fabs(P4_MCTruth_LeptonPlus[0].DeltaPhi(P4_MCTruth_LeptonMinus[0])) *180.0/M_PI;
    float dang    = P4_MCTruth_LeptonPlus[0].Angle(P4_MCTruth_LeptonMinus[0].Vect())   *180.0/M_PI;
  
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
    
    m_mc_init_leptonp_e  = 0.0;
    m_mc_init_leptonp_p  = 0.0;
    m_mc_init_leptonp_pt = 0.0;
    m_mc_init_leptonp_pz = 0.0;

    m_mc_init_leptonp_phi = 0.0;
    m_mc_init_leptonp_theta = 0.0;
  
    m_mc_init_leptonm_e  = 0.0;
    m_mc_init_leptonm_p  = 0.0;
    m_mc_init_leptonm_pt = 0.0;
    m_mc_init_leptonm_pz = 0.0;

    m_mc_init_leptonm_phi = 0.0;
    m_mc_init_leptonm_theta = 0.0;
  
    m_mc_init_dilepton_m = 0.0;
    m_mc_init_dilepton_e = 0.0;
    m_mc_init_dilepton_p = 0.0;
    m_mc_init_dilepton_pt = 0.0;
    m_mc_init_dilepton_pz = 0.0;
    m_mc_init_dilepton_rec_m = 0.0;
    m_mc_init_dilepton_dphi = 0.0;
    m_mc_init_dilepton_dang = 0.0;
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

    m_mc_higgs_m = 0.0;
    m_mc_higgs_e = 0.0;
    m_mc_higgs_rec_m = 0.0;
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

    float zw1_m  = ( p4_zw1_daughter_1 + p4_zw1_daughter_2 ).M();
    float zw1_p  = ( p4_zw1_daughter_1 + p4_zw1_daughter_2 ).P();
    float zw1_pt = ( p4_zw1_daughter_1 + p4_zw1_daughter_2 ).Pt();
    float zw1_e  = ( p4_zw1_daughter_1 + p4_zw1_daughter_2 ).E();
    float zw1_rec_m  = ( P_T - p4_zw1_daughter_1 - p4_zw1_daughter_2 ).M();

    float zw2_m  = ( p4_zw2_daughter_1 + p4_zw2_daughter_2 ).M();
    float zw2_p  = ( p4_zw2_daughter_1 + p4_zw2_daughter_2 ).P();
    float zw2_pt = ( p4_zw2_daughter_1 + p4_zw2_daughter_2 ).Pt();
    float zw2_e  = ( p4_zw2_daughter_1 + p4_zw2_daughter_2 ).E();
    float zw2_rec_m  = ( P_T - p4_zw2_daughter_1 - p4_zw2_daughter_2 ).M();

    float zw1zw2_m = ( p4_zw1_daughter_1 + p4_zw1_daughter_2 + p4_zw2_daughter_1 + p4_zw2_daughter_2 ).M();
    float zw1zw2_e = ( p4_zw1_daughter_1 + p4_zw1_daughter_2 + p4_zw2_daughter_1 + p4_zw2_daughter_2 ).E();
    float zw1zw2_rec_m = ( P_T - p4_zw1_daughter_1 - p4_zw1_daughter_2 - p4_zw2_daughter_1 - p4_zw2_daughter_2 ).M();

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

    m_mc_zw1_m  = 0.0;
    m_mc_zw1_p  = 0.0;
    m_mc_zw1_pt = 0.0;
    m_mc_zw1_e  = 0.0;
    m_mc_zw1_rec_m = 0.0;

    m_mc_zw2_m  = 0.0;
    m_mc_zw2_p  = 0.0;
    m_mc_zw2_pt = 0.0;
    m_mc_zw2_e  = 0.0;
    m_mc_zw2_rec_m = 0.0;

    m_mc_zw1zw2_m = 0.0;
    m_mc_zw1zw2_e = 0.0;
    m_mc_zw1zw2_rec_m = 0.0;
  }

}


//the code from yudan
void hig2inv::RecoAna( LCEvent * evtP ) 
{		

    if (evtP) 								
    {		
        
        try 	
        {    

            _nTau=0;
            _nTauP=0;
            _nTauM=0;
            
            LCCollection* col_Reco = evtP->getCollection( "ArborPFOs" ) ;			

            int _nReco = col_Reco->getNumberOfElements();
            
            std::vector<ReconstructedParticle* > leadRPar;
            std::vector<ReconstructedParticle* > totChPar;

            std::vector<TVector3 > leadRdir;
            std::vector<float > leadREn;
            std::vector<float > totChEn;
            leadRdir.clear();
            leadREn.clear();
            leadRPar.clear();

            float totRLEn=0;
            _TotalEvtEn=0;
            _TotalEvtP[0]=0;
            _TotalEvtP[1]=0;
            _TotalEvtP[2]=0;

            _qqEn=0;
            _qqP[0]=0;
            _qqP[1]=0;
            _qqP[2]=0;
            TVector3 totRLdir;
            _TauTauImpact=0;
            _tauM_impact=0;
            _tauP_impact=0;
            ReconstructedParticle *totRLPar;
            for(int i = 0; i < _nReco; i++)
                        {
                                ReconstructedParticle * a_RecoP = dynamic_cast<ReconstructedParticle*>(col_Reco->getElementAt(i));
                TVector3 curP=a_RecoP->getMomentum();
                _TotalEvtEn+=a_RecoP->getEnergy();
                _TotalEvtP[0]+=a_RecoP->getMomentum()[0];
                _TotalEvtP[1]+=a_RecoP->getMomentum()[1];
                _TotalEvtP[2]+=a_RecoP->getMomentum()[2];
                if(a_RecoP->getCharge()==0)continue;
                
                          if(a_RecoP->getEnergy()>totRLEn&&a_RecoP->getCharge()!=0){
                        totRLEn=a_RecoP->getEnergy();
                        totRLdir=a_RecoP->getMomentum();
                        totRLPar=a_RecoP;
                }
            }
            leadREn.push_back(totRLEn);
            leadRdir.push_back(totRLdir);
            leadRPar.push_back(totRLPar);

            
            if(totRLEn>_tracken){
            


            for(int i=0;i<_nReco;i++)
            {
                ReconstructedParticle * a_RecoP = dynamic_cast<ReconstructedParticle*>(col_Reco->getElementAt(i));
                TVector3 curP=a_RecoP->getMomentum();
                    
                int nl = leadRdir.size();

                if(a_RecoP->getEnergy()<_Ltracken)continue;
                if(abs(a_RecoP->getCharge())==0)continue;
                int joined=0;
                
                for(int j=0;j<nl;j++){
                    if(curP.Angle(leadRdir[j])<_trackcone1){
                        joined=1;
                    
                        if(a_RecoP->getEnergy()>leadREn[j]){
                            leadRdir[j]=a_RecoP->getMomentum();
                            leadREn[j]=a_RecoP->getEnergy();
                            leadRPar[j]=a_RecoP;
                        }
                        continue;
                    }
                }
                if(joined==0){
            
                        leadRdir.push_back(a_RecoP->getMomentum());
                        leadREn.push_back(a_RecoP->getEnergy());
                        leadRPar.push_back(a_RecoP);
                    
                }
            }	


            int n_Rloop= leadRdir.size();

            _nRecoTau=0;
            _fakeTau=0;
            _tracedTau=0;
            _candiTau=0;
            _totalJet=0;
            _visEp=0;
            _visEm=0;
            _visPp[0]=0;
            _visPp[1]=0;
            _visPp[2]=0;
            _visPm[0]=0;
            _visPm[1]=0;
            _visPm[2]=0;
                    
            for(int j=0;j<n_Rloop;j++){

                taujet = new ReconstructedParticleImpl();
                _leadE=0;
                int ncharged=0;
                int nrecoCh_O=0;
                nelec=0;
                nmuon=0;
                npion=0;
                int nphoton=0;
                TVector3 visP;
                visP[0]=0;
                visP[1]=0;
                visP[2]=0;
                _TauTauD0=0;
                _TauTauZ0=0;

                _EnergicAng=0;
                _EnergicEn=0;
                _PhEn=0;
                _PhAng=0;
                _Tau=0;
                _TauT=0;
                _VisE=0;
                _MCVisE=0;
                _MCVisEN=0;
                _MCE=0;
                _InvM=0;
                _outConeE=0;
                _D0=0;
                _Z0=0;

                _jetC=0;
                _tracedTrk=0;
                _tracedEn=0;
                float visEn=0;
                float _chargedEn=0;
                _D0err=0;
                _Z0err=0;
                Track *Ltrk=leadRPar[j]->getTracks()[0];
                _D0=Ltrk->getD0();
                _D0err=sqrt(Ltrk->getCovMatrix()[0]);
                _Z0=Ltrk->getZ0();
                _Z0err=sqrt(Ltrk->getCovMatrix()[9]);
                _leadE=leadREn[j];
                _leadP[0]=leadRdir[j][0];
                _leadP[1]=leadRdir[j][1];
                _leadP[2]=leadRdir[j][2];
                for(int i=0;i<_nReco;i++){
                    ReconstructedParticle * a_RecoP = dynamic_cast<ReconstructedParticle*>(col_Reco->getElementAt(i));
                        int pid = a_RecoP->getType();
                        TVector3 curdir=a_RecoP->getMomentum();
                        float energy=a_RecoP->getEnergy();
                        int charge=a_RecoP->getCharge();
                        if(energy>_tracken){

                            if(curdir.Angle(leadRdir[j])<_trackcone){

                                _outConeE+=energy;		
                                nrecoCh_O++;
                                if(charge!=0){								
                                    if(energy<leadREn[j]&&energy>_EnergicEn){
                                        _EnergicEn=energy;
                                        _EnergicAng=curdir.Angle(leadRdir[j]);
                                    }
                                    if(curdir.Angle(leadRdir[j])<_trackcone1){
                                        taujet->addParticle(a_RecoP);
                                            _jetC+=charge;
                                        visEn += energy;
                                        visP[0]+=a_RecoP->getMomentum()[0];
                                        visP[1]+=a_RecoP->getMomentum()[1];
                                        visP[2]+=a_RecoP->getMomentum()[2];
                                        ncharged++;
                                        _chargedEn+=energy;
                                        if(fabs(pid)==11)nelec++;
                                        if(fabs(pid)==13)nmuon++;
                                        if(fabs(pid)==211)npion++;

                                    }

                                }
                                else if(pid==22){
                                     if(curdir.Angle(leadRdir[j])<_trackcone1){
                                        nphoton++;
                                        taujet->addParticle(a_RecoP);

                                        visEn += energy;
                                        visP[0]+=a_RecoP->getMomentum()[0];
                                        visP[1]+=a_RecoP->getMomentum()[1];
                                        visP[2]+=a_RecoP->getMomentum()[2];
                                        
                                        if(energy>_PhEn){
                                            _PhEn=energy;
                                            _PhAng=curdir.Angle(leadRdir[j]);
                                        }
                                     }
                                    
                                }
                                else{
                                    if(curdir.Angle(leadRdir[j])<_trackcone1){
                                        taujet->addParticle(a_RecoP);

                                        visEn += energy;
                                        visP[0]+=a_RecoP->getMomentum()[0];
                                        visP[1]+=a_RecoP->getMomentum()[1];
                                        visP[2]+=a_RecoP->getMomentum()[2];
                                    }
                                }

                            }
                        }
                    }

                    float InvMass2=sqrt(visEn*visEn-visP[0]*visP[0]-visP[1]*visP[1]-visP[2]*visP[2]);
                    _InvM=InvMass2;
                    _VisE=visEn;
                    _VisP[0]=visP[0];
                    _VisP[1]=visP[1];
                    _VisP[2]=visP[2];
                                            
                    if((InvMass2<_taumass&&InvMass2>0.01&&ncharged<6&&nphoton<5&&ncharged+nphoton<8)&&((ncharged==1&&nphoton==0&&visEn>10)||(ncharged+nphoton>1))){
                        _visEnergy[j]=visEn;
                        if(visEn/_outConeE>_E_par){
                            _TauT=1;
                            if(_Tau==1)_tracedTau++;
                            _nTau++;
                                
                            if(_jetC>0.5){
                                _nTauP++;
                                if(visEn>_visEp){
                                    _visEp=visEn;
                                    _visPp[0]=visP[0];
                                    _visPp[1]=visP[1];
                                    _visPp[2]=visP[2];
                                    TLorentzVector cur_P(visP[0],visP[1],visP[2],visEn);
                                    P4_tauP=cur_P;
                                    _tauP_impact=_D0*_D0/_D0err*_D0err+_Z0*_Z0/_Z0err*_Z0err;
                                    _TauTauD0+=_D0*_D0/_D0err*_D0err;
                                    _TauTauZ0+=_Z0*_Z0/_Z0err*_Z0err;
                                    
                                }

                                }
                            if(_jetC<-0.5){
                                _nTauM++;
                                if(visEn>_visEm){
                                    _visEm=visEn;
                                    _visPm[0]=visP[0];
                                    _visPm[1]=visP[1];
                                    _visPm[2]=visP[2];
                                    TLorentzVector cur_P(visP[0],visP[1],visP[2],visEn);
                                    P4_tauM=cur_P;
                                    _tauM_impact=_D0*_D0/_D0err*_D0err+_Z0*_Z0/_Z0err*_Z0err;

                                    _TauTauD0+=_D0*_D0/_D0err*_D0err;
                                    _TauTauZ0+=_Z0*_Z0/_Z0err*_Z0err;
                                    
                                }
                            }
                        }

                        
                    }
                        
                    }
        
            }		

            _qqEn=_TotalEvtEn-_visEp-_visEm;
            _qqP[0]=_TotalEvtP[0]-_visPm[0]-_visPp[0];
            _qqP[1]=_TotalEvtP[1]-_visPm[1]-_visPp[1];
            _qqP[2]=_TotalEvtP[2]-_visPm[2]-_visPp[2];
    
            TLorentzVector P_T(0.0,0.0,0.0,sqrts);
            TLorentzVector currP(_TotalEvtP[0],_TotalEvtP[1],_TotalEvtP[2],_TotalEvtEn);
            _RecoilM=(P_T-currP).M();
            TLorentzVector currqqP(_qqP[0], _qqP[1],_qqP[2],_qqEn);
            _qqRecoilM=(P_T-currqqP).M();  //Candidate tau recoil mass  ?
            _qqM=currqqP.M();
            _invMm=P4_tauM.M();
            _invMp=P4_tauP.M();
            _TauTauM=(P4_tauP+P4_tauM).M();
            _TauTauImpact=_tauP_impact+_tauM_impact;									
        }		
        catch (lcio::DataNotAvailableException err) { }

    }  	  


}