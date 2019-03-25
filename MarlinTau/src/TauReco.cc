#include <TauReco.hh>
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

using namespace std;

const float sqrts = 240.0;
TauReco a_TauReco_instance;

TauReco::TauReco()
	: Processor("TauReco"),
	_output(0)
{
	_description = "Print MC Truth" ;

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

void TauReco::init() {

	printParameters();

}
void TauReco::processEvent( LCEvent * evtP ) 
{		

	if (evtP) 								
	{		
		
		try 	
		{   
			LCCollection *col_taujet = new LCCollectionVec(LCIO::RECONSTRUCTEDPARTICLE);
			LCCollection *col_tauseed = new LCCollectionVec(LCIO::RECONSTRUCTEDPARTICLE);
			
			LCCollection* col_Reco = evtP->getCollection( "ArborPFOs" ) ;			

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
			TVector3 totRLdir;
			TLorentzVector P4_tauP;
			TLorentzVector P4_tauM;
			ReconstructedParticle *totRLPar;
			for(int i = 0; i < _nReco; i++)
                        {
                                ReconstructedParticle * a_RecoP = dynamic_cast<ReconstructedParticle*>(col_Reco->getElementAt(i));
				TVector3 curP=a_RecoP->getMomentum();
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

			std::vector<TVector3 > tauP;
			std::vector<float > tauEn;
			tauP.clear();
			tauEn.clear();
			
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
			
				
				
			for(int j=0;j<n_Rloop;j++){
				ReconstructedParticleImpl * taujet = new ReconstructedParticleImpl();
				ReconstructedParticleImpl * tauseed = new ReconstructedParticleImpl();
				int ncharged=0;
				int nrecoCh_O=0;
				int nphoton=0;
				float _outConeE=0;
				float _E_imp=0;
				TVector3 visP;
				visP[0]=0;
				visP[1]=0;
				visP[2]=0;
				float visEn=0;
				float _chargedEn=0;
				
				for(int i=0;i<_nReco;i++){
					ReconstructedParticle * a_RecoP = dynamic_cast<ReconstructedParticle*>(col_Reco->getElementAt(i));
						int pid = a_RecoP->getType();
						TVector3 curdir=a_RecoP->getMomentum();
						float energy=a_RecoP->getEnergy();
						int charge=a_RecoP->getCharge();
						if(energy>_tracken){

							if(curdir.Angle(leadRdir[j])<_trackcone){
								_outConeE+=energy;

								if(charge!=0){								
									
									if(curdir.Angle(leadRdir[j])<_trackcone1){
										taujet->addParticle(a_RecoP);
										tauseed->addParticle(a_RecoP);
										
										visEn += energy;
										visP[0]+=a_RecoP->getMomentum()[0];
										visP[1]+=a_RecoP->getMomentum()[1];
										visP[2]+=a_RecoP->getMomentum()[2];
										ncharged++;
																			}

								}
								else if(pid==22){
									 if(curdir.Angle(leadRdir[j])<_trackcone1){

										taujet->addParticle(a_RecoP);
										tauseed->addParticle(a_RecoP);
										nphoton++;
										visEn += energy;
										visP[0]+=a_RecoP->getMomentum()[0];
										visP[1]+=a_RecoP->getMomentum()[1];
										visP[2]+=a_RecoP->getMomentum()[2];
										
										
									 }
									
								}
								else{
									if(curdir.Angle(leadRdir[j])<_trackcone1){
										taujet->addParticle(a_RecoP);
										tauseed->addParticle(a_RecoP);
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
					
					float VisP[3];
					VisP[0]=visP[0];
					VisP[1]=visP[1];
					VisP[2]=visP[2];
					tauseed->setEnergy(visEn);
					tauseed->setMomentum(VisP);
					col_tauseed->addElement(tauseed);

						
						if((InvMass2<_taumass&&InvMass2>0.01&&ncharged<6&&nphoton<5&&ncharged+nphoton<8)&&((ncharged==1&&nphoton==0)||(ncharged+nphoton>1))){
							if(visEn/_outConeE>_E_par){
							
								taujet->setEnergy(visEn);
								taujet->setMomentum(VisP);
								col_taujet->addElement(taujet);
						}
						
						
					}

				}		
					
			}
				





		
			evtP->addCollection(col_taujet,"TauJet");
			evtP->addCollection(col_tauseed,"TauSeed");
		}		
		catch (lcio::DataNotAvailableException err) { }

	}  	  

}	

void TauReco::end()
{



}



