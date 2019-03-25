#include <TauAna.hh>
#include <EVENT/LCCollection.h>
#include <IMPL/LCCollectionVec.h>
#include <EVENT/LCFloatVec.h>
#include <EVENT/MCParticle.h>
#include <EVENT/LCRelation.h>
#include <EVENT/ReconstructedParticle.h>
#include <IMPL/ReconstructedParticleImpl.h>
#include <IMPL/MCParticleImpl.h>
#include <values.h>
#include <string>
#include <iostream>
#include <EVENT/LCFloatVec.h>
#include <EVENT/LCParameters.h>
#include <stdexcept>
#include <TFile.h> 
#include <TTree.h>
#include <TVector3.h>
#include <TRandom.h>
#include <Rtypes.h> 
#include <sstream>		
#include <cmath>
#include <vector>
#include <TMath.h>
#include "TLorentzVector.h"
#include "HelixClass.h"
#include <stdexcept>

using namespace std;

const float sqrts = 240.0;

ReconstructedParticleImpl * genjet;
ReconstructedParticleImpl * mcjet;
ReconstructedParticleImpl * taujet;
TauAna a_TauAna_instance;

TauAna::TauAna()
	: Processor("TauAna"),
	_output(0)
{
	_description = "Print MC Truth" ;

	_treeFileName="MCTruth.root";
	registerProcessorParameter( "TreeOutputFile" , 
			"The name of the file to which the ROOT tree will be written" ,
			_treeFileName ,
			_treeFileName);

	_treeName="Tau";
	registerProcessorParameter( "TreeName" , 
			"The name of the ROOT tree" ,
			_treeName ,
			_treeName);

	_overwrite=0;
	registerProcessorParameter( "OverwriteFile" , 
			"If zero an already existing file will not be overwritten." ,
			_overwrite ,
			_overwrite);
	_JetFlag=0;
	registerProcessorParameter( "JetFlag" , 
			"If zero tau in jet will not be recorded" ,
			_JetFlag ,
			_JetFlag);
	_PairFlag=0;
	registerProcessorParameter( "PairFlag" , 
			"If zero taujet will be paired with mcjet, else genjet" ,
			_PairFlag ,
			_PairFlag);
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

void TauAna::init() {

	printParameters();

	tree_file=new TFile(_treeFileName.c_str(),(_overwrite ? "RECREATE" : "UPDATE"));

	if (!tree_file->IsOpen()) {
		delete tree_file;
		tree_file=new TFile(_treeFileName.c_str(),"NEW");
	}

	_outputEvt = new TTree("Evt","Evt");
	_outputEvt->SetAutoSave(32*1024*1024);
	_outputJet = new TTree("TauJet","TauJet");
	_outputJet->SetAutoSave(32*1024*1024);
	_outputTau = new TTree("Tau","Tau");
	_outputTau->Branch("Num",&_Num, "Num/I");
	_outputTau->Branch("TauF",&_tauF, "TauF/I");
	_outputTau->Branch("Ang_Trk",&_Ang_Trk, "Ang_Trk/F");
	_outputTau->Branch("AngTauTrk",&_AngTauTrk, "AngTauTrk/F");
	_outputTau->Branch("AngTauPh",&_AngTauPh, "AngTauPh/F");
	_outputTau->Branch("NTauTrk",&_NTauTrk, "NTauTrk/I");
	_outputTau->Branch("NCh_O",&_NCh_O, "NCh_O/I");
	_outputTau->Branch("NTauPh",&_NTauPh, "NTauPh/I");
	_outputTau->Branch("LTrkEn",&_LTrkEn, "LTrkEn/F");
	_outputTau->Branch("sEn",&_sEn, "sEn/F");
	_outputTau->Branch("lEn",&_lEn, "lEn/F");
	_outputTau->Branch("minTrkEn",&_minTrkEn, "minTrkEn/F");
	_outputTau->Branch("misTrkEn",&_misTrkEn, "misTrkEn/F");

	_outputJet->Branch("Num",&_Num, "Num/I");
	_outputJet->Branch("Tau",&_Tau, "Tau/I");
	_outputJet->Branch("Decayflag",&_Decayflag, "Decayflag/I");
	_outputJet->Branch("TauT",&_TauT, "TauT/I");
	_outputJet->Branch("tracedTrk",&_tracedTrk, "tracedTrk/I");
	_outputJet->Branch("tracedEn",&_tracedEn, "tracedEn/F");
	_outputJet->Branch("EnergicAng",&_EnergicAng, "EnergicAng/F");
	_outputJet->Branch("EnergicEn",&_EnergicEn, "EnergicEn/F");
	_outputJet->Branch("PhAng",&_PhAng, "PhAng/F");
	_outputJet->Branch("PhEn",&_PhEn, "PhEn/F");
	_outputJet->Branch("InvM",&_InvM, "InvM/F");
	_outputJet->Branch("VisE",&_VisE, "VisE/F");
	_outputJet->Branch("VisP[3]",_VisP, "VisP[3]/F");
	_outputJet->Branch("MCVisE",&_MCVisE, "MCVisE/F");
	_outputJet->Branch("MCVisEN",&_MCVisEN, "MCVisEN/F");
	_outputJet->Branch("MCE",&_MCE, "MCE/F");
	_outputJet->Branch("jetC",&_jetC, "jetC/F");
	_outputJet->Branch("leadE",&_leadE, "leadE/F");
	_outputJet->Branch("leadP[3]",_leadP, "leadP[3]/F");
	_outputJet->Branch("E_imp",&_E_imp, "E_imp/F");
	_outputJet->Branch("NRecoCh_O", &_NRecoCh_O, "NRecoCh_O/I");
	_outputJet->Branch("NCharge", &_NCharge, "NCharge/I");
	_outputJet->Branch("NPion", &npion, "NPion/I");
	_outputJet->Branch("NMuon", &nmuon, "NMuon/I");
	_outputJet->Branch("NElec", &nelec, "NElec/I");
	_outputJet->Branch("NPhoton", &_NPhoton, "NPhoton/I");
	_outputJet->Branch("NNN", &_NNN, "NNN/I");
	_outputJet->Branch("D0", &_D0, "D0/F");
	_outputJet->Branch("D0err", &_D0err, "D0err/F");
	_outputJet->Branch("Z0", &_Z0, "Z0/F");
	_outputJet->Branch("Z0err", &_Z0err, "Z0err/F");

	_outputEvt->Branch("EventNr", &_eventNr, "EventNr/I");
	_outputEvt->Branch("nTau", 		&_nTau, 	"nTau/I");
	_outputEvt->Branch("nTauP", 		&_nTauP, 	"nTauP/I");
	_outputEvt->Branch("nTauM", 		&_nTauM, 	"nTauM/I");
	_outputEvt->Branch("fakeTau", 		&_fakeTau, 	"fakeTau/I");
	_outputEvt->Branch("tracedTau", 		&_tracedTau, 	"tracedTau/I");
	_outputEvt->Branch("candiTau", 		&_candiTau, 	"candiTau/I");
	_outputEvt->Branch("totalJet", 		&_totalJet, 	"totalJet/I");
	_outputEvt->Branch("visEnergy[999]", 	_visEnergy, 	"visEnergy[999]/F");
	_outputEvt->Branch("E_p",     &_E_p,	"E_p/F");
	_outputEvt->Branch("E_m",     &_E_m,	"E_m/F");

	_outputEvt->Branch("MCvisEp",	&_MCvisEp,		"MCvisEp/F");
	_outputEvt->Branch("MCvisEm",       &_MCvisEm,          "MCvisEm/F");
	_outputEvt->Branch("MCvisPp[3]",	_MCvisPp,		"MCvisPp[3]/F");
	_outputEvt->Branch("MCvisPm[3]",  _MCvisPm,          "MCvisPm[3]/F");
	_outputEvt->Branch("MCqqM",    &_MCqqM,       "MCqqM/F");
	_outputEvt->Branch("visEp",	&_visEp,		"visEp/F");
	_outputEvt->Branch("visEm",       &_visEm,          "visEm/F");
	_outputEvt->Branch("visPp[3]",	_visPp,		"visPp[3]/F");
	_outputEvt->Branch("visPm[3]",  _visPm,          "visPm[3]/F");
	_outputEvt->Branch("invMp",	&_invMp,		"invMp/F");
	_outputEvt->Branch("invMm",       &_invMm,          "invMm/F");
	
	_outputEvt->Branch("nch_p",	&_nch_p,	"nch_p/I");
	_outputEvt->Branch("npi_p",	&_npi_p,	"npi_p/I");
	_outputEvt->Branch("nph_p",	&_nph_p,	"nph_p/I");
	_outputEvt->Branch("nch_m",     &_nch_m,        "nch_m/I");
	_outputEvt->Branch("nph_m",     &_nph_m,        "nph_m/I");
	_outputEvt->Branch("npi_m",     &_npi_m,        "npi_m/I");
	_outputEvt->Branch("evtN",    &_evtN,       "evtN/I");
	_outputEvt->Branch("TauTauImpact", &_TauTauImpact, "TauTauImpact/F");
	_outputEvt->Branch("TauTauD0", &_TauTauD0, "TauTauD0/F");
	_outputEvt->Branch("TauTauZ0", &_TauTauZ0, "TauTauZ0/F");
	_outputEvt->Branch("tauP_impact", &_tauP_impact, "tauP_impact/F");
	_outputEvt->Branch("tauM_impact", &_tauM_impact, "tauM_impact/F");
	_outputEvt->Branch("RecoilM",    &_RecoilM,       "RecoilM/F");
	_outputEvt->Branch("qqRecoilM",    &_qqRecoilM,       "qqRecoilM/F");
	_outputEvt->Branch("TauTauM",    &_TauTauM,       "TauTauM/F");
	_outputEvt->Branch("qqM",    &_qqM,       "qqM/F");
	_outputEvt->Branch("TotalEvtEn",    &_TotalEvtEn,       "TotalEvtEn/F");
	_outputEvt->Branch("TotalEvtP[3]",    _TotalEvtP,       "TotalEvtP[3]/F");
	_outputEvt->Branch("MCTauNumber", &_MCTauNumber, "MCTauNumber/I");

	_outputPair = new TTree("Pair", "Pair");
	_outputPair->SetAutoSave(32*1024*1024);
	_outputPair->Branch("Num", &_Num, "Num/I");
	_outputPair->Branch("PairType", &_PairType, "PairType/I");
	_outputPair->Branch("PairIndex", &_PairIndex, "PairIndex/I");
	_outputPair->Branch("DR",&_DR,"DR/F");
	_outputPair->Branch("DE",&_DE,"DE/F");
	_outputPair->Branch("MCPEn",&_MCPEn,"MCPEn/F");
	_outputPair->Branch("MCPInvM",&_MCPInvM,"MCPInvM/F");
	_outputPair->Branch("MCNTrk", &_MCNTrk, "MCNTrk/I");
	_outputPair->Branch("MCNPh", &_MCNPh, "MCNPh/I");
	_outputPair->Branch("MCNPi", &_MCNPi, "MCNPi/I");
	_outputPair->Branch("MCNEl", &_MCNEl, "MCNEl/I");
	_outputPair->Branch("MCNMu", &_MCNMu, "MCNMu/I");
	_outputPair->Branch("MCPP", _MCPP, "MCPP[3]/F");
	_outputPair->Branch("RecoPEn",&_RecoPEn,"RecoPEn/F");
	_outputPair->Branch("RecoPInvM",&_RecoPInvM,"RecoPInvM/F");
	_outputPair->Branch("RecoNTrk", &_RecoNTrk, "RecoNTrk/I");
	_outputPair->Branch("RecoNPh", &_RecoNPh, "RecoNPh/I");
	_outputPair->Branch("RecoNPi", &_RecoNPi, "RecoNPi/I");
	_outputPair->Branch("RecoNEl", &_RecoNEl, "RecoNEl/I");
	_outputPair->Branch("RecoNMu", &_RecoNMu, "RecoNMu/I");
	_outputPair->Branch("RecoPP", _RecoPP, "RecoPP[3]/F");
		
	_Num = 0;
}
void TauAna::MCAna( LCEvent * evtP ) 
{		

	if (evtP) 								
	{		
		
		try 	
		{    

			_MCTauP=0;
			_MCTauM=0;
			_ATauM=100;
			_BTauM=100;
			_TauNumber=0;
			_dimu=0;
			_TauTauD0=0;
			_TauTauZ0=0;

			GenJets.clear();
			MCJets.clear();
			
			LCCollection* col_MCP = evtP->getCollection( "MCParticle" ) ;			

			_nMCP = col_MCP->getNumberOfElements();
			_eventNr=evtP->getEventNumber();
			cout<<_nMCP<<"MCP "<<_evtN<<"th event"<<endl;
			
			TVector3 MCP_P, MCVisP, RecoP_P, TotalReco_P;

			TVector3 VTX, EndP, _p_tr, _p_ph;
			_MCTauNumber=0;
			_E_p=0;
			_E_m=0;
			_nch_p=0;
			_npi_p=0;
			_nmu_p=0;
			_nel_p=0;
			_nph_p=0;
			_nch_m=0;
			_npi_m=0;
			_nmu_m=0;
			_nel_m=0;
			_nph_m=0;
			for(int i = 0; i < _nMCP; i++)
                        {
                                MCParticle * a_MCP = dynamic_cast<MCParticle*>(col_MCP->getElementAt(i));
				MCParticle *a_parent = a_MCP;
				if(a_MCP->getParents().size()>0)
				{
					a_parent=a_MCP->getParents()[0];
					//if(a_parent->getPDG()!=15){

						if(abs( a_MCP -> getPDG() )== 15 &&a_parent->getPDG()==25)
						{
							_MCTauNumber++;
						}
					//}
				}
			}
			
			TVector3 dir_p, dir_m;
			_minE_p=99;
			_minE_m=99;

			_MCvisEp=0;
			_MCvisPp[0]=0;
			_MCvisPp[1]=0;
			_MCvisPp[2]=0;
			_MCvisEm=0;
			_MCvisPm[0]=0;
			_MCvisPm[1]=0;
			_MCvisPm[2]=0;
			_MCqqM=0;
			MCtotalE=0;

			MCtotalP[0]=0;
			MCtotalP[1]=0;
			MCtotalP[2]=0;
			for(int i=0;i<_nMCP;i++)
			{
				MCParticle * a_MCP = dynamic_cast<MCParticle*>(col_MCP->getElementAt(i));
				TVector3 curP=a_MCP->getMomentum();
				VTX = a_MCP->getVertex();
                                EndP = a_MCP->getEndpoint();
				
				if(a_MCP->getParents().size()==0||abs(a_MCP->getPDG())==15)continue;
                                if( (fabs(VTX.Z()) < 200 && fabs(VTX.Perp()) < 200 ) ){
					if(abs(a_MCP->getPDG())!=12&&abs(a_MCP->getPDG())!=14&&abs(a_MCP->getPDG())!=16&&a_MCP->getGeneratorStatus()==1){
						MCtotalE+=a_MCP->getEnergy();
						MCtotalP+=a_MCP->getMomentum();
					}
					MCParticle * a_par=a_MCP;
					do{
						a_par=a_par->getParents()[0];
					}while(a_par->getParents().size()>0&&abs(a_par->getPDG())!=15);
					MCParticle * a_ppar=a_par;
					if(a_ppar->getParents().size()==0)continue;
					do{ 
						a_ppar=a_ppar->getParents()[0];
					}while(a_ppar->getParents().size()>0&&abs(a_ppar->getPDG())!=25);
					//if(_JetFlag==0&&a_ppar->getPDG()!=25)continue;
					if(a_ppar->getPDG()!=25)continue;

					if(a_par->getPDG()==15){
						if(a_MCP->getEnergy()>_E_p&&a_MCP->getCharge()!=0&& a_MCP->getGeneratorStatus()==1){
							_E_p=a_MCP->getEnergy();
							dir_p=a_MCP->getMomentum();
							
						}
						if(a_MCP->getEnergy()<_minE_p&&a_MCP->getCharge()!=0&& a_MCP->getGeneratorStatus()==1){

							_minE_p=a_MCP->getEnergy();
						}
						if(a_MCP->getCharge()!=0&& a_MCP->getGeneratorStatus()==1){
							_nch_p++;
							if(abs(a_MCP->getPDG())==211)_npi_p++;
							else if(abs(a_MCP->getPDG())==11)_nel_p++;
							else if(abs(a_MCP->getPDG())==13)_nmu_p++;
						}
						if(a_MCP->getPDG()==22&&a_MCP->getGeneratorStatus()==1){
							_nph_p++;
						}
						if(a_MCP->getEnergy()>_tracken&&a_MCP->getGeneratorStatus()==1&&abs(a_MCP->getPDG())!=12&&abs(a_MCP->getPDG())!=14&&abs(a_MCP->getPDG())!=16){

							_MCvisEp+=a_MCP->getEnergy();
							_MCvisPp[0]=a_MCP->getMomentum()[0];
							_MCvisPp[1]=a_MCP->getMomentum()[1];
							_MCvisPp[2]=a_MCP->getMomentum()[2];
						}
													
					}
									else if(a_par->getPDG()==-15){
						if(a_MCP->getEnergy()>_E_m&&a_MCP->getCharge()!=0&& a_MCP->getGeneratorStatus()==1){
							_E_m=a_MCP->getEnergy();
							dir_m=a_MCP->getMomentum();
						}
						if(a_MCP->getEnergy()<_minE_m&&a_MCP->getCharge()!=0&& a_MCP->getGeneratorStatus()==1){
							_minE_m=a_MCP->getEnergy();
						}
						if(a_MCP->getCharge()!=0&& a_MCP->getGeneratorStatus()==1){
							_nch_m++;
							if(abs(a_MCP->getPDG())==211)_npi_m++;
							else if(abs(a_MCP->getPDG())==11)_nel_m++;
							else if(abs(a_MCP->getPDG())==11)_nel_m++;
						}
						if(a_MCP->getPDG()==22&&a_MCP->getGeneratorStatus()==1){
							_nph_m++;
						}

						if(a_MCP->getEnergy()>1.5&&a_MCP->getGeneratorStatus()==1&&abs(a_MCP->getPDG())!=12&&abs(a_MCP->getPDG())!=14&&abs(a_MCP->getPDG())!=16){

							_MCvisEm+=a_MCP->getEnergy();
							_MCvisPm[0]=a_MCP->getMomentum()[0];
							_MCvisPm[1]=a_MCP->getMomentum()[1];
							_MCvisPm[2]=a_MCP->getMomentum()[2];
						}
						
					}
				}
					
			}
			
			float sconep=999;
			float dphconep=0;
			float sconem=999;
			float dphconem=0;
			float dconep=0;
			float dconem=0;
			float strkenp=0;
			float strkenm=0;
			float sEnp=0;
			float sEnm=0;
			float lEnp=0;
			float lEnm=0;
			int NCh_PO=0;
			int NCh_MO=0;
			TVector3 visPP(0,0,0);
			TVector3 visPM(0,0,0);
			float MCVisEnp, MCVisEnm;
			float MCVisPp[3];
			float MCVisPm[3];
			for(int i=0;i<3;i++){
				 MCVisPp[i]=0;
				 MCVisPm[i]=0;
			}

			for(int i=0;i<_nMCP;i++)
			{
				MCParticle * a_MCP = dynamic_cast<MCParticle*>(col_MCP->getElementAt(i));
				TVector3 curP=a_MCP->getMomentum();
				VTX = a_MCP->getVertex();
                                EndP = a_MCP->getEndpoint();

				if(a_MCP->getEnergy()<0.5)continue;
				
                                if( (fabs(VTX.Z()) < 200 && fabs(VTX.Perp()) < 200 ) && ( fabs(EndP.Z()) > 2350 || fabs(EndP.Perp()) > 1800  ) ){

					MCParticle * a_par=a_MCP;
					do{
						a_par=a_par->getParents()[0];
					}while(a_par->getParents().size()>0&&abs(a_par->getPDG())!=15);
					if(curP.Angle(dir_p)<_trackcone){
						sEnp+=a_MCP->getEnergy();
						if(a_MCP->getCharge()!=0)NCh_PO++;
					}


					if(a_par->getPDG()==15&&abs(a_MCP->getPDG())!=12&&abs(a_MCP->getPDG())!=14&&abs(a_MCP->getPDG())!=16){
						MCVisEnp+=a_MCP->getEnergy();
						MCVisPp[0]+=a_MCP->getMomentum()[0];
						MCVisPp[1]+=a_MCP->getMomentum()[1];
						MCVisPp[2]+=a_MCP->getMomentum()[2];
					}
					if(a_par->getPDG()==-15&&abs(a_MCP->getPDG())!=12&&abs(a_MCP->getPDG())!=14&&abs(a_MCP->getPDG())!=16){
						MCVisEnm+=a_MCP->getEnergy();
						MCVisPm[0]+=a_MCP->getMomentum()[0];
						MCVisPm[1]+=a_MCP->getMomentum()[1];
						MCVisPm[2]+=a_MCP->getMomentum()[2];
					}
					if(a_par->getPDG()==15&&curP.Angle(dir_p)>dphconep&&a_MCP->getPDG()==22){
						dphconep=curP.Angle(dir_p);
					}
					if(a_par->getPDG()==-15&&curP.Angle(dir_m)>dphconem&&a_MCP->getPDG()==22){
						dphconem=curP.Angle(dir_m);
					}

					if(curP.Angle(dir_p)<_trackcone1){
						lEnp+=a_MCP->getEnergy();
						visPP+=a_MCP->getMomentum();
					}
					if(curP.Angle(dir_m)<_trackcone){
						sEnm+=a_MCP->getEnergy();
						if(a_MCP->getCharge()!=0)NCh_MO++;
					}

					if(curP.Angle(dir_m)<_trackcone1){
						lEnm+=a_MCP->getEnergy();
						visPM+=a_MCP->getMomentum();
					}
					if(a_MCP->getCharge()==0)continue;
					if(abs(a_par->getPDG())!=15&&curP.Angle(dir_p)<sconep){
						sconep=curP.Angle(dir_p);
						strkenp=a_MCP->getEnergy();

					}

					if(abs(a_par->getPDG())!=15&&curP.Angle(dir_m)<sconem){
						sconem=curP.Angle(dir_m);
						strkenm=a_MCP->getEnergy();
					}
					if(a_par->getPDG()==15&&curP.Angle(dir_p)>dconep){
						dconep=curP.Angle(dir_p);
					}
					if(a_par->getPDG()==-15&&curP.Angle(dir_m)>dconem){
						dconem=curP.Angle(dir_m);
					}
				}
			}
			_LTrkEn=-999;
			_NTauTrk=0;
			_NTauPh=0;
			_Ang_Trk=0;
			_misTrkEn=0;
			_AngTauTrk=0;
			_AngTauPh=0;
			_sEn=0;
			_lEn=0;
			if(_MCTauNumber==2){
			for(int k=0;k<2;k++){
				if(k==0){

					genjet = new ReconstructedParticleImpl();
					mcjet = new ReconstructedParticleImpl();
					_LTrkEn=_E_p;
					_minTrkEn=_minE_p;
					_NTauTrk=_nch_p;
					_NTauPh=_nph_p;
					_Ang_Trk=sconep;
					_AngTauTrk=dconep;
					_AngTauPh=dphconep;
					_misTrkEn=strkenp;
					_sEn=sEnp;
					_lEn=lEnp;
					_NCh_O=NCh_PO;
					_outputTau->Fill();
					mcjet->setEnergy(MCVisEnp);
					mcjet->setMomentum(MCVisPp);
					mcjet->setType(_nph_p);
					mcjet->setCharge(_nch_p);
					float rp[3];
					rp[0]=_npi_p;
					rp[1]=_nmu_p;
					rp[2]=_nel_p;
					mcjet->setReferencePoint(rp);
					genjet->setEnergy(_MCvisEp);
					genjet->setMomentum(_MCvisPp);
					genjet->setType(_nph_p);
					genjet->setCharge(_nch_p);
					genjet->setReferencePoint(rp);
					GenJets.push_back(genjet);
					MCJets.push_back(mcjet);


				}
			
				if(k==1){
					genjet = new ReconstructedParticleImpl();
					mcjet = new ReconstructedParticleImpl();
					_LTrkEn=_E_m;
					_minTrkEn=_minE_m;
					_NTauTrk=_nch_m;
					_NTauPh=_nph_m;
					_Ang_Trk=sconem;
					_misTrkEn=strkenm;
					_AngTauTrk=dconem;
					_AngTauPh=dphconem;
					_NCh_O=NCh_MO;
					_sEn=sEnm;
					_lEn=lEnm;

					float rp[3];
					rp[0]=_npi_m;
					rp[1]=_nmu_m;
					rp[2]=_nel_m;
					genjet->setEnergy(_MCvisEm);
					genjet->setMomentum(_MCvisPm);
					genjet->setType(_nph_m);
					genjet->setCharge(_nch_m);
					genjet->setReferencePoint(rp);

					mcjet->setEnergy(MCVisEnm);
					mcjet->setMomentum(MCVisPm);
					mcjet->setType(_nph_m);
					mcjet->setCharge(_nch_m);
					mcjet->setReferencePoint(rp);
					GenJets.push_back(genjet);
					MCJets.push_back(mcjet);
					_outputTau->Fill();
				}
				
			}
			}


		
		}		
		catch (lcio::DataNotAvailableException err) { }

	}  	  

}	
void TauAna::RecoAna( LCEvent * evtP ) 
{		

	if (evtP) 								
	{		
		
		try 	
		{    

			_nTau=0;
			_nTauP=0;
			_nTauM=0;
			

			LCCollection* col_Reco = evtP->getCollection( "ArborPFOs" ) ;			
			TauJets.clear();

			int _nReco = col_Reco->getNumberOfElements();
			cout<<_nReco<<"PFOs"<<endl;
			
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
			cout<<"n_Rloop"<<n_Rloop<<endl;
			
			for(int k=0;k<n_Rloop;k++){
				_nRecoCharged[k]=-999;
				_nRecoPhoton[k]=0;
				_recoEnergy[k]=0;
			}	
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
				int nnn=0;
				TVector3 visP;
				visP[0]=0;
				visP[1]=0;
				visP[2]=0;
				_NCharge=0;
				_NPhoton=0;
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
				_E_imp=0;
				_D0=0;
				_Z0=0;
				_Decayflag=0;
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


										try{ 
										LCCollection *MCTruthLink = evtP->getCollection("RecoMCTruthLink");

										LCCollection* col_MCP = evtP->getCollection( "MCParticle" ) ;			
										 int NLink=MCTruthLink->getNumberOfElements();
										for(int im=0;im<_nMCP;im++){
											MCParticle *a_MCP=dynamic_cast<MCParticle*>(col_MCP->getElementAt(im));
											MCParticle *a_par=dynamic_cast<MCParticle*>(col_MCP->getElementAt(im));
											for(int pp = 0; pp < NLink; pp++)
											{
												LCRelation *a_link = dynamic_cast<LCRelation*>(MCTruthLink->getElementAt(pp));
												if(a_link->getTo() == a_MCP&&a_link->getFrom()==a_RecoP)
												{
													do{
														a_par=a_par->getParents()[0];
													}while(a_par->getParents().size()>0&&abs(a_par->getPDG())!=15);
													if(abs(a_par->getPDG())==15){_tracedTrk++;
														_tracedEn+=energy;
													}

												}
											}
										}
										}catch (lcio::DataNotAvailableException err) { }

									}

								}
								else if(pid==22){
									 if(curdir.Angle(leadRdir[j])<_trackcone1){

										taujet->addParticle(a_RecoP);
										nphoton++;
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
										nnn++;
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
					
					_NCharge=ncharged;
					_NRecoCh_O=nrecoCh_O;
					_NPhoton=nphoton;
					_NNN=nnn;
					try{
					 LCCollection *MCTruthLink = evtP->getCollection("RecoMCTruthLink");

					LCCollection* col_MCP = evtP->getCollection( "MCParticle" ) ;			
					 int NLink=MCTruthLink->getNumberOfElements();
					for(int im=0;im<_nMCP;im++){
						MCParticle *a_MCP=dynamic_cast<MCParticle*>(col_MCP->getElementAt(im));
						TVector3 curdir=a_MCP->getMomentum();
							MCParticle *a_par=dynamic_cast<MCParticle*>(col_MCP->getElementAt(im));
							for(int pp = 0; pp < NLink; pp++)
							{
								LCRelation *a_link = dynamic_cast<LCRelation*>(MCTruthLink->getElementAt(pp));
								if(a_link->getTo() == a_MCP&&a_link->getFrom()==leadRPar[j])
								{
									do{
										a_par=a_par->getParents()[0];
									}while(a_par->getParents().size()>0&&abs(a_par->getPDG())!=15);
									if(abs(a_par->getPDG())!=15){
										continue;

									}
									do{
										a_par=a_par->getParents()[0];
									}while(a_par->getParents().size()>0&&abs(a_par->getPDG())!=25);
									//if(_JetFlag==0&&a_par->getPDG()!=25)continue;
									if(a_par->getPDG()!=25)continue;
										_Tau=1;
										_MCE=a_par->getEnergy();
										_MCVisE=a_par->getEnergy();
										for(int nd=0;nd<a_par->getDaughters().size();nd++){
											if(a_par->getDaughters()[nd]->getPDG()==12||a_par->getDaughters()[nd]->getPDG()==14||a_par->getDaughters()[nd]->getPDG()==16)_MCVisE=_MCVisE-a_par->getDaughters()[nd]->getEnergy();
										}
									

								}
							}
							TVector3 EndP = a_MCP->getEndpoint();

							TVector3 VTX = a_MCP->getVertex();

							if(a_MCP->getEnergy()<0.5)continue;
				
							if( (fabs(VTX.Z()) < 200 && fabs(VTX.Perp()) < 200 ) && ( fabs(EndP.Z()) > 2350 || fabs(EndP.Perp()) > 1800  ) ){

							if(curdir.Angle(leadRdir[j])<_trackcone1&&_Tau==0&&!(a_MCP->getPDG()==12||a_MCP->getPDG()==14||a_MCP->getPDG()==16)){
								_MCVisEN+=a_MCP->getEnergy();
							}
							}
						}
							
					}catch (lcio::DataNotAvailableException err) { }
						_Num=_evtN;

						_E_imp=visEn/_outConeE;
						
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
							_nCharged[j]=ncharged;
							
							_nPhoton[j]=nphoton;
						}
						if(_TauT){

							taujet->setEnergy(visEn);
							taujet->setMomentum(_VisP);
							TauJets.push_back(taujet);
						}
						_outputJet->Fill();
						_totalJet++;
						if(_tracedTrk==0)_fakeTau++;
						else{
							_candiTau++;
						}
						
					}

			
			}		
											

		}		
		catch (lcio::DataNotAvailableException err) { }

	}  	  


}

std::vector<int> TauAna::SortMeasure( std::vector<float> Measure, int ControlOrderFlag )
{

	std::vector<int> objindex;
	int Nobj = Measure.size();

	for(int k = 0; k < Nobj; k++)
	{
		objindex.push_back(k);
	}

	int FlagSwapOrder = 1;
	float SwapMeasure = 0;
	int SwapIndex = 0;

	for(int i = 0; i < Nobj && FlagSwapOrder; i++)
	{
		FlagSwapOrder = 0;
		for(int j = 0; j < Nobj - 1; j++)
		{
			if((Measure[j] < Measure[j+1] && ControlOrderFlag) || (Measure[j] > Measure[j+1] && !ControlOrderFlag) )
			{
				FlagSwapOrder = 1;
				SwapMeasure = Measure[j];
				Measure[j] = Measure[j+1];
				Measure[j+1] = SwapMeasure;

				SwapIndex = objindex[j];
				objindex[j] = objindex[j+1];
				objindex[j+1] = SwapIndex;
			}
		}
	}

	return objindex;
}
void TauAna::Pairing(std::vector<ReconstructedParticle*> RecoPs, std::vector<ReconstructedParticle*> MCPs)
{

	int NReco = RecoPs.size();
	int NMCP = MCPs.size();
	std::vector<std::pair<int, int> > Pairs; 
	Pairs.clear();
	std::map<ReconstructedParticle*, int> MCPTouchFlag; 
	std::map<ReconstructedParticle*, int> RecoPTouchFlag; 
	MCPTouchFlag.clear();
	RecoPTouchFlag.clear();

	std::vector<float> RecoPEn;
	std::vector<float> MCPEn; 
	for(int i = 0; i < NReco; i++)
	{
		ReconstructedParticle* a_RecoP = RecoPs[i];
		RecoPEn.push_back(a_RecoP->getEnergy());
	}
	for(int j = 0; j < NMCP; j++)
	{
		ReconstructedParticle *a_MCP = MCPs[j];
		MCPEn.push_back(a_MCP->getEnergy());
	}
	std::vector<int> RecoPOrder = SortMeasure(RecoPEn, 1);
	std::vector<int> MCPOrder = SortMeasure(MCPEn, 1);
	_MCPEn = 0; _MCPInvM=-99; _MCNTrk=-99; _MCNPh=-99;_RecoPEn=-99; _RecoPInvM=-99; _RecoNTrk=0; _RecoNPh=0; _DR=-99; _DE=-99;

	_PairType = -99; 
	for(int t = 0; t < 3; t++)
	{
		_MCPP[t] = 0;
		_RecoPP[t] = 0;
	}

	TVector3 PRecoP, PMCP, RecoPSeed; 
	float MinDR = 1E10; 
	float tmpDR = 1E10; 
	float MinER = 1E10;
	float EnReco = 0; 
	float EnMCP = 0; 
	int mappedIndex = 0;

	int NPair = 0; 
	cout<<NReco<<" :Num of Map: "<<NMCP<<endl; 

	for(int i1 = 0; i1 < NReco; i1++)
	{
		ReconstructedParticle* a_RecoP = RecoPs[RecoPOrder[i1]];
		PRecoP = a_RecoP->getMomentum();
		EnReco = a_RecoP->getEnergy();
		tmpDR = 1E10; 
		MinDR = 1E10;
		MinER = 1E10; 
		for(int j1 = 0; j1 < NMCP; j1++)
		{
			ReconstructedParticle *a_MCP = MCPs[MCPOrder[j1]];
			//if( MCPTouchFlag.find(a_MCP) == MCPTouchFlag.end() )
			{
				PMCP = a_MCP->getMomentum();
				EnMCP = a_MCP->getEnergy();
				tmpDR = PRecoP.Angle(PMCP);	
				if( tmpDR < MinDR  )
				{
					MinDR = tmpDR;
					MinER = abs(EnMCP - EnReco)/(EnMCP + EnReco);
					mappedIndex = MCPOrder[j1];
				}
			}
		}

		if(MinDR < 0.5 && MinER < 0.8)	// Then create A Pair
		{	
			ReconstructedParticle * mm_MCP = MCPs[mappedIndex];
			MCPTouchFlag[mm_MCP] = 1; 
			RecoPTouchFlag[a_RecoP] = 1;
			_MCPEn = mm_MCP->getEnergy();
			_MCNTrk = mm_MCP->getCharge();
			_MCNPh = mm_MCP->getType();
			_MCNPi = mm_MCP->getReferencePoint()[0];
			_MCNMu = mm_MCP->getReferencePoint()[1];
			_MCNEl = mm_MCP->getReferencePoint()[2];
			_RecoPEn = a_RecoP->getEnergy();
			_DR = MinDR; 
			_DE = MinER; 
			for(int t = 0; t < 3; t++)
			{
				_MCPP[t] = mm_MCP->getMomentum()[t];
				_RecoPP[t] = a_RecoP->getMomentum()[t];
			}
			
			for(int ix=0;ix<a_RecoP->getParticles().size();ix++){
				if(abs(a_RecoP->getParticles()[ix]->getCharge())>0)_RecoNTrk++;
				if(a_RecoP->getParticles()[ix]->getType()==22)_RecoNPh++;
				if(abs(a_RecoP->getParticles()[ix]->getType())==211)_RecoNPi++;
				if(abs(a_RecoP->getParticles()[ix]->getType())==11)_RecoNEl++;
				if(abs(a_RecoP->getParticles()[ix]->getType())==13)_RecoNMu++;
			}
			NPair++;
			
			_PairType = 0;	//Correctly mapped;
			cout<<_MCNPi<<" "<<_MCNMu<<" "<<_MCNEl<<endl;
			cout<<"filled"<<endl;
			_outputPair->Fill();
		}
	}	

	for(int i2 = 0; i2 < NReco; i2++)
	{

		ReconstructedParticle* a_RecoP = RecoPs[RecoPOrder[i2]];
		if( RecoPTouchFlag.find(a_RecoP) == RecoPTouchFlag.end() )
		{		
			_MCPEn = -99;
			_RecoPEn = a_RecoP->getEnergy();

			_DR = 1E10;
			_DE = 1E10;
			for(int t = 0; t < 3; t++)
			{
				_MCPP[t] = -99;
				_RecoPP[t] = a_RecoP->getMomentum()[t];
			}
			
			for(int i=0;i<a_RecoP->getParticles().size();i++){
				if(abs(a_RecoP->getParticles()[i]->getCharge())>0)_RecoNTrk++;
				if(a_RecoP->getParticles()[i]->getType()==22)_RecoNPh++;
				if(abs(a_RecoP->getParticles()[i]->getType())==211)_RecoNPi++;
				if(abs(a_RecoP->getParticles()[i]->getType())==11)_RecoNEl++;
				if(abs(a_RecoP->getParticles()[i]->getType())==13)_RecoNMu++;
			}
			_PairType = 10;		//Reconstructed DidFound MCP 
			cout<<_RecoNPi<<" "<<_RecoNEl<<endl;
			_outputPair->Fill();
		}
	}

	for(int i3 = 0; i3 < NMCP; i3++)
        {
                ReconstructedParticle* a_MCP = MCPs[MCPOrder[i3]];
                if( MCPTouchFlag.find(a_MCP) == MCPTouchFlag.end() )
                {
			_MCPEn = a_MCP->getEnergy();
                        _RecoPEn = -99;
                        _DR = 1E10;
                        _DE = 1E10;
                        
			_MCNTrk = a_MCP->getCharge();
			_MCNPh = a_MCP->getType();
			_MCNPi = a_MCP->getReferencePoint()[0];
			_MCNMu = a_MCP->getReferencePoint()[1];
			_MCNEl = a_MCP->getReferencePoint()[2];
			_RecoNTrk=-99;
			_RecoNPh=-99;
                        _PairType = 20;         //Reconstructed DidFound MCP 
                        _outputPair->Fill();
                }
        }


	cout<<NReco<<" :Num of Map: "<<NMCP<<" : "<<NPair<<endl;
}

							
void TauAna::processEvent(LCEvent * evtP){
	if(evtP){
		cout<<"new event"<<endl;
		try{
		MCAna(evtP);
		RecoAna(evtP);

		if(_PairFlag==0)Pairing(TauJets,MCJets);//Genjets can be replaced by GenJets
		if(_PairFlag==1)Pairing(TauJets,GenJets);//Genjets can be replaced by GenJets
			TLorentzVector MCqqP(MCtotalP[0]-_MCvisPm[0]-_MCvisPp[0], MCtotalP[1]-_MCvisPm[1]-_MCvisPp[1],MCtotalP[2]-_MCvisPm[2]-_MCvisPp[2],MCtotalE-_MCvisEp);
			_MCqqM=MCqqP.M();

		
			cout<<"MCTau: "<<_MCTauNumber<<endl;



			_qqEn=_TotalEvtEn-_visEp-_visEm;
			_qqP[0]=_TotalEvtP[0]-_visPm[0]-_visPp[0];
			_qqP[1]=_TotalEvtP[1]-_visPm[1]-_visPp[1];
			_qqP[2]=_TotalEvtP[2]-_visPm[2]-_visPp[2];
	
			TLorentzVector P_T(0,0,0,sqrts);
			TLorentzVector currP(_TotalEvtP[0],_TotalEvtP[1],_TotalEvtP[2],_TotalEvtEn);
			_RecoilM=(P_T-currP).M();
			TLorentzVector currqqP(_qqP[0], _qqP[1],_qqP[2],_qqEn);
			_qqRecoilM=(P_T-currqqP).M();
			_qqM=currqqP.M();
			_invMm=P4_tauM.M();
			_invMp=P4_tauP.M();
			_TauTauM=(P4_tauP+P4_tauM).M();
			_TauTauImpact=_tauP_impact+_tauM_impact;





		
			_outputEvt->Fill();
			_evtN++;


		}
		catch (lcio::DataNotAvailableException err) { }
	}
}
void TauAna::end()
{


		//TFile *tree_file = _outputTree->GetCurrentFile(); //just in case we switched to a new file
		tree_file->cd();
		tree_file->Write();
		tree_file->Close();

}



