#ifndef _TauReco_hh_
#define _TauReco_hh_

#include <string>
#include <iostream>
#include <fstream>
#include <marlin/Processor.h>
#include <TNtuple.h>
#include <TObject.h>
#include <TTree.h>
#include <TFile.h>
#include <TH1F.h>

class TTree;

class TauReco  : public marlin::Processor
{
	public:

		Processor*  newProcessor() { return new TauReco ; }

		TauReco();

		~TauReco() {};

		void init();

		void processEvent( LCEvent * evtP );

		void end();
		std::vector<int> SortMeasure(std::vector<float> Measure, int ControlOrderFlag);

	protected:

		float _trackcone, _tracken, _trackcone1,_Ltracken,_E_par;
		float _taumass;

		std::ostream *_output;
		
};

#endif


