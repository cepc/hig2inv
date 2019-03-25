#ifndef _TauAna_hh_
#define _TauAna_hh_

#include <string>
#include <iostream>
#include <fstream>
#include <marlin/Processor.h>
#include <TNtuple.h>
#include <TObject.h>
#include <TTree.h>
#include <TFile.h>
#include <TH1F.h>
#include <TVector3.h>
#include <TLorentzVector.h>

#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>
#include <IMPL/ReconstructedParticleImpl.h>

class TTree;

class TauAna  : public marlin::Processor
{
	public:

		Processor*  newProcessor() { return new TauAna ; }

		TauAna();

		~TauAna() {};

		void init();

		void MCAna( LCEvent * evtP );
		void RecoAna( LCEvent * evtP );
		void Pairing(std::vector<ReconstructedParticle*> RecoPs, std::vector<ReconstructedParticle*> MCPs);
		void processEvent( LCEvent * evtP );
		std::vector<ReconstructedParticle*> MCJets;
		std::vector<ReconstructedParticle*> GenJets;
		std::vector<ReconstructedParticle*> TauJets;

		void end();
		std::vector<int> SortMeasure(std::vector<float> Measure, int ControlOrderFlag);

	protected:
		std::string _treeFileName;
		std::string _treeName;
		std::string _colName;
		std::string _colAdcVals;
		TFile *tree_file;
		

		int _overwrite;
		int _PairFlag;
		int _JetFlag;
		TTree *_outputEvt;
		TTree *_outputJet;
		TTree *_outputTau;
		TTree *_outputPair;
		TVector3 MCtotalP;

		TLorentzVector P4_tauP;
		TLorentzVector P4_tauM;
			
		LCCollection *col_taujet;
		LCCollection *col_mcjet;
		LCCollection *col_seedjet;

		int _nMCP;
		int _PairType, _PairIndex, _MCNTrk, _MCNPh, _RecoNTrk, _RecoNPh,_MCNPi,_MCNMu,_MCNEl,_RecoNPi,_RecoNMu,_RecoNEl;
		float _MCPEn, _MCPInvM, _RecoPEn, _RecoPInvM, _DR, _DE;
		float _MCPP[3], _RecoPP[3];
		
		float MCtotalE;
		float _Ang_Trk, _AngTauTrk, _LTrkEn,_minTrkEn,_minE_p,_minE_m,_misTrkEn,_sEn,_lEn,_AngTauPh;
		int _NTauTrk, _NTauPh,_tracedTau;
		unsigned int _eventNr;
		float _trackcone, _tracken, _E_par,_E_p,_E_m, _MCAng, _trackcone1,_Ltracken;
		float _taumass;
		int _nch_p, _nch_m, _TauT,npion,nmuon,nelec;
		int _NCharge, _NPhoton,_Tau,_NNN,_tauF,_NCh_O,_NRecoCh_O;
		float _EnergicEn, _EnergicAng, _PhEn, _PhAng, _VisE, _InvM, _outConeE, _E_imp, _MCVisE, _MCE,_MCVisEN, _tracedEn;
		int _Num, _evtN,  _nTau,_nTauP,_nTauM, _fakeTau,_candiTau, _tracedTrk,_totalJet; 
		float _Charge, _En, _VisEn, _VisEnCh, _Reco_Charge, _Reco_VisEn, _Reco_VisEnCh, _DeltaTheta, _DeltaPhi, _DeltaR, _DeltaPhiVis, _DeltaThetaVis, _cone, _En_tr_all, _TauEnergy, _TauCharge, _TauMass, _MCTauEnergy, _MCTauCharge, _MCTauMass;
		float _MCTauPMass,_TauPMass,_MCTauPEn,_TauPEn,_MCTauPP[3],_TauPP[3],_MCTauMMass,_TauMMass,_MCTauMEn,_TauMEn,_MCTauMP[3],_TauMP[3],_tauAngle;		
		int _NMuon, _NEle, _NPion, _NKaon, _NUndef, _Reco_NMuon, _Reco_NEle, _Reco_NPion, _Reco_NPhoton, _Reco_NUndef, _TauNumber, _MCTauM,_MCTauP, _MCTauNumber, _Tag_e,_Tag_mu, _Tag_pi,_Tag_photon, _Ancharged,_Bncharged,_Anphoton,_Bnphoton,_Ane,_Anmu,_Anpi,_Bne,_Bnmu,_Bnpi,_dimu; 
		float _jetC;
		float _tauM_impact,_tauP_impact,_TauTauImpact,_leadE,_D0err,_Z0err;
		float _TauTauD0,_TauTauZ0;
		float _TauP[3];
		float _leadP[3];
		float _MC_TauP[3];
		float _VisP[3];
		float _P[3];
		float _Reco_VisP[3];
		int _HDecay[999];
		int _HDDecay[999];
		int _nCharged[999];
		int _nPhoton[999];
		float _visEnergy[999];
		float _Mass, _Jet; 
		float _AvisEn,_BvisEn,_AMass,_BMass,_Acone1,_Acone2,_Acone3,_Bcone1,_Bcone2,_Bcone3,_recoilM,_Acharged,_Bcharged,_ATauM,_BTauM;
		float _AvisP[3];
		float _BvisP[3];
		TH1F *_photonmass, *_photonmass2, *_photonmass3; 
		float _Reco_recoilM,_ArecoEn,_BrecoEn,_ArecoM,_BrecoM;
		int _ArecoNch,_BrecoNch,_ArecoNph,_BrecoNph,_Arecoe,_Arecomu,_Arecopi,_Brecoe,_Brecomu,_Brecopi;
		float _ArecoP[3];
                float _BrecoP[3];
		float _TotalEvtP[3];
		float _qqP[3];
		float _TotalEvtEn;
		float _qqEn;
		float _RecoilM;
		float _qqRecoilM;
		float _TauTauM,_qqM,_MCqqM;
		float _D0, _Z0;
		int _nRecoCharged[999],_nRecoPhoton[999];
		int _nRecoTau, _nRecoP;
		int _Decayflag,_npi_p,_nph_p,_npi_m,_nph_m,_nmu_p,_nel_p,_nmu_m,_nel_m;
		float _recoEnergy[999];

		float _visEp,_visEm,_invMp,_invMm,_MCvisEp,_MCvisEm;
		float _visPp[3];
		float _MCvisPp[3];
		float _visPm[3];	
		float _MCvisPm[3];	
		std::string _fileName;
		std::ostream *_output;
		std::string _histFileName;
};

#endif


