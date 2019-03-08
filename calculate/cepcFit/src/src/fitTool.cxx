#include "fitTool.h"
 
fitTool::fitTool() {
  // Default values for the minimizer
  _minAlgo = "Minuit2";
  _minTolerance = 1E-06;
  _minStrat = 2;
  _nllOffset = true;
  _nCPU = 1;
  _optConst = 2;
  _printLevel = 2;
  _useHESSE = true;
  _useMINOS = true;
  _useSIMPLEX = false;
  _saveWS= false;
}

using namespace std;
using namespace RooFit;
using namespace RooStats;


int fitTool::profileToData(ModelConfig *mc, RooAbsData *data){
	// ----------------------------------------------------------------------------------------------------- 
	RooAbsPdf *pdf=mc->GetPdf();
	RooWorkspace *w=mc->GetWS();
//	
	TStopwatch timer1;
	std::cout << "   Building NLL..." << std::endl;

	RooAbsReal *nll = pdf->createNLL(*data, NumCPU(_nCPU));

	nll->enableOffsetting(1);
	timer1.Stop();
	double t_cpu_ = timer1.CpuTime()/60.;
	double t_real_ = timer1.RealTime()/60.;
	printf("   NLL built in %.2f min (cpu), %.2f min (real)\n", t_cpu_, t_real_);

	
	RooMinimizer minim(*nll);
	minim.setStrategy( _minStrat );
	minim.setPrintLevel( _printLevel-1 );
	minim.setProfile(); /* print out time */
	minim.setEps( _minTolerance/0.001  );
	minim.setOffsetting( _nllOffset );
	if (_optConst > 0) minim.optimizeConst( _optConst );

	int status = 0;
	// Perform fit with MIGRAD
	status += minim.minimize( _minAlgo );

	if ( _useHESSE ) {
		cout << endl << "Starting fit with HESSE..." << endl;
		status += minim.hesse();
		minim.save("hesse","")->Print();
	}

	if ( _useMINOS ) {
		cout << endl << "Starting fit with MINOS..." << endl;
		status += minim.minos( *mc->GetParametersOfInterest() );
	}

	if ( _outputFile != "" ) { 
		cout << endl << "Saving results to " << _outputFile << endl;
		// Create output file and save fit results
		TFile *tout = new TFile( _outputFile, "RECREATE" );
		tout->cd();
		RooFitResult *result = minim.save("fitResult","Fit Results");
		result->Write();
		
		// Get important values to save
		double nllVal = nll->getVal();
		TString str_nll = Form("NLL value is %.12f", nllVal);
		cout << endl << str_nll << endl;
		std::map<std::string, double> muMap;
		for (RooLinkedListIter it = mc->GetParametersOfInterest()->iterator(); RooRealVar* POI = dynamic_cast<RooRealVar*>(it.Next());) {
		muMap[POI->GetName()] = POI->getVal();
		}
		
		// Save values to TTree
		TTree *nllTree = new TTree("nllscan", "nllscan");
		nllTree->Branch( "status", &status);
		nllTree->Branch( "nll", &nllVal);
		for (RooLinkedListIter it = mc->GetParametersOfInterest()->iterator(); RooRealVar* POI = dynamic_cast<RooRealVar*>(it.Next());) {
		nllTree->Branch( POI->GetName(), &(muMap[POI->GetName()]) );
		}
		nllTree->Fill();
		nllTree->Write();
	}

	return status;
	}


