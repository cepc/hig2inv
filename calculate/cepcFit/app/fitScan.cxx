// -*- C++ -*- //  
//
// Description: get constant quality of Higgs    
//
// Original Author:  tanyh <tanyuhang@ihep.ac.cn>
//         Created:  [2019-03-05 ] 
//         Inspired by Kaili's code  

#include "inc/CommonHead.h"
#include "inc/RooFitHead.h" 
#include "inc/RooStatsHead.h"  

#include <boost/program_options.hpp>

#include "inc/fitTool.h" 
#include "inc/auxUtils.h"  
#include "TDatime.h"
#define DEBUG 1 

std::string _outputFile = "";
std::string _inputFile = "";
std::string _minAlgo  = "Minuit2";
std::string _dataName = "AsimovSB";
std::string _wsName = "combination";
//std::string _wsName = "combination";
std::string _mcName = "ModelConfig";

std::string _poiStr = "";
std::string _fixNPStr = "";
std::string _postFitFile = "";

bool _saveWS = true;
bool _useHESSE = false;
bool _useMINOS = false;
bool _useSIMPLEX = false;
bool _nllOffset = true;
float _minTolerance = 1E-04;
int _minStrategy = 2;
int _optConst = 2;
int _printLevel = -1;
int _nCPU = 4;

std::string _scanStr = "";



int main( int argc, char** argv )
{
	namespace po = boost::program_options;
	po::options_description desc( "quickFit options" );
	desc.add_options()
		// IO Options
		( "inputFile,f",   po::value<std::string>(&_inputFile),  "Specify the input TFile (REQUIRED)" )
		( "outputFile,o",  po::value<std::string>(&_outputFile), "Save fit results to output TFile" )
		( "dataName,d",    po::value<std::string>(&_dataName)->default_value(_dataName),
							"Name of the dataset" )
		( "wsName,w",      po::value<std::string>(&_wsName)->default_value(_wsName),
							"Name of the workspace" )
		( "mcName,m",      po::value<std::string>(&_mcName)->default_value(_mcName),
							"Name of the model config" )
		// Model Options
		( "poi,p",         po::value<std::string>(&_poiStr),     "Specify POIs to be used in fit" )
		( "fixNP,n",       po::value<std::string>(&_fixNPStr),   "Specify NPs to be used in fit" )
		( "postFit",         po::value<std::string>(&_postFitFile),   "perform statistic only fit" )
		// Fit Options
		( "simplex",       po::value<bool>(&_useSIMPLEX)->default_value(_useSIMPLEX),
							"Estimate central values with SIMPLEX" )
		( "hesse",         po::value<bool>(&_useHESSE)->default_value(_useHESSE),
							"Estimate errors with HESSE after fit" )
		( "minos",         po::value<bool>(&_useMINOS)->default_value(_useMINOS),
							"Get asymmetric errors with MINOS fit" )
		( "scanNLL",      po::value<std::string>(&_scanStr),     "Specify POI to be scanned" )
		( "nllOffset",     po::value<bool>(&_nllOffset)->default_value(_nllOffset),
							"Set NLL offset" )
		( "numCPU",        po::value<int>(&_nCPU)->default_value(_nCPU),
							"Set number of CPUs for fit" )
		( "minStrat",      po::value<int>(&_minStrategy)->default_value(_minStrategy),
							"Set minimizer strategy" )
		( "optConst",      po::value<int>(&_optConst)->default_value(_optConst),
							"Set optimize constant" )
		( "printLevel",    po::value<int>(&_printLevel)->default_value(_printLevel),
							"Set minimizer print level" )
		( "minTolerance",  po::value<float>(&_minTolerance)->default_value(_minTolerance),
							"Set minimizer tolerance" )
		( "saveWS",        po::value<bool>(&_saveWS)->default_value(_saveWS),
							"Save postfit workspace to the output file" )
		// Other
		( "help,h",  "Print help message")
		;

	po::variables_map vm;
	try
	{
		po::store( po::command_line_parser( argc, argv ).options( desc ).run(), vm );
		po::notify( vm );
	}
	catch ( std::exception& ex )
	{
		std::cerr << "Invalid options: " << ex.what() << std::endl;
		std::cout << "Invalid options: " << ex.what() << std::endl;
		std::cout << "Use manager --help to get a list of all the allowed options"  << std::endl;
		return 999;
	}
	catch ( ... )
	{
		std::cerr << "Unidentified error parsing options." << std::endl;
		return 1000;
	}

	// if help, print help
	if ( !(vm.count("inputFile")||vm.count("postFit")) || vm.count( "help" ) )
	{
		std::cout << "Usage: manager [options]\n";
		std::cout << desc;
		return 0;
	}

	RooMsgService::instance().getStream(1).removeTopic(RooFit::NumIntegration) ;//suppress messages for num integration of Roofit
	RooMsgService::instance().getStream(1).removeTopic(RooFit::Fitting) ;
	RooMsgService::instance().getStream(1).removeTopic(RooFit::Minimization) ;
	RooMsgService::instance().getStream(1).removeTopic(RooFit::InputArguments) ;
	RooMsgService::instance().getStream(1).removeTopic(RooFit::Eval) ;
	RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
	RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
	RooMsgService::instance().setStreamStatus(1,false);
	
	// Set fit options
	fitTool *fitter = new fitTool();
	fitter->setMinAlgo( (TString) _minAlgo );
	fitter->useHESSE( _useHESSE );
	fitter->useMINOS( _useMINOS );
	fitter->useSIMPLEX( _useSIMPLEX );
	fitter->setNLLOffset( _nllOffset );
	fitter->setTolerance( _minTolerance );
	fitter->setStrategy( _minStrategy );
	fitter->setOptConst( _optConst );
	fitter->setPrintLevel( _printLevel );
	fitter->setNCPU( _nCPU );
	fitter->setOutputFile( (TString) _outputFile );
	fitter->saveWorkspace( _saveWS );

	// Get workspace, model, and data from file
	TFile *tf;
	RooWorkspace *ws;

	tf = new TFile( (TString) _inputFile );
	cout << endl << "Read workspace "<<_wsName<<" in : " << _inputFile << endl;
	ws = (RooWorkspace*)tf->Get( (TString) _wsName );
	
	RooStats::ModelConfig *mc = (RooStats::ModelConfig*)ws->obj( (TString) _mcName );
	RooAbsData *data = ws->data( (TString) _dataName );
	
	utils::setAllConstant( mc->GetParametersOfInterest(), true );  

	RooArgSet fitPOIs;

	cout << endl << "Preparing parameters of interest :" << endl;
	std::vector<std::string> poiStrs = auxUtils::Tokenize( _poiStr, "," );   //ez4v=1_-5_5,mz4v=1_-5_5,qz4v=1_-5_5

	for( unsigned int ipoi(0); ipoi < poiStrs.size(); ipoi++ ) 
	{
		std::vector<std::string> poiTerms = auxUtils::Tokenize( poiStrs[ipoi], "=" ); //split string with =
		TString poiName = (TString) poiTerms[0]; //  cname :mz4v and qz4v ..

	// check if variable is in workspace
		if (not ws->var(poiName))  
		{
			cout << "FAIL" << "Variable " << poiName << " not in workspace. Skipping." << "ENDC" << endl;
			continue;
		}

	// set variable for fit
		fitPOIs.add( *(ws->var(poiName)) ); //contains all thing 
	//	  cerr<<"fitPOIS:"<<fitPOIS<<endl;
		if (poiTerms.size() > 1) 
		{
			std::vector<std::string> poiVals = auxUtils::Tokenize( poiTerms[1], "_" );//RooRealVar::ez4v = 1  L(-5 - 5)

			if (poiVals.size() == 3) 
			{
				ws->var(poiName)->setConstant( kFALSE );
				ws->var(poiName)->setVal( std::stof(poiVals[0]) );   //1,-5,5 //stof change to number
				ws->var(poiName)->setRange( std::stof(poiVals[1]), std::stof(poiVals[2]) );
			} 
			else 
			{
				ws->var(poiName)->setVal( std::stof(poiVals[0]) );
			}

			ws->var(poiName)->Print();
		} 
		else 
		{
			ws->var(poiName)->setConstant( kFALSE );
			ws->var(poiName)->Print();
		}
	}


	mc->SetParametersOfInterest( fitPOIs );
	cerr<<"................mc........."<<endl;
    mc->Print();
//	cerr<<"workspace11:"<<endl;
//	ws->Print();
//	cerr<<"....end......"<<endl;
	// Fitting
	TStopwatch timer;
	cout << endl << "Starting fit..." << endl;
	int status = fitter->profileToData( mc, data ); // Perform fit
	timer.Stop();
	double t_cpu_ = timer.CpuTime()/60.;
	double t_real_ = timer.RealTime()/60.;
	printf("\nAll fits done in %.2f min (cpu), %.2f min (real)\n", t_cpu_, t_real_);

	string STATMSG = (status) ? "Fail" : "Ok" ;

	// Print summary
	cout << endl << "  Fit Summary of POIs (" << STATMSG << ")" << endl;
	cout << "------------------------------------------------" << endl;
	for (RooLinkedListIter it = fitPOIs.iterator(); RooRealVar* POI = dynamic_cast<RooRealVar*>(it.Next());) 
	{
		if (POI->isConstant()) continue;
		POI->Print();
		// cout<<"E:"<<POI->getError()<<endl;
		// cout<<"H:"<<POI->getErrorHi()<<endl;
		// cout<<"L:"<<POI->getErrorLo()<<endl;
		// cout<<"aH:"<<POI->getAsymErrorHi()<<endl;
		// cout<<"aL:"<<POI->getAsymErrorLo()<<endl;
	}
	cout << endl << "  Fit Summary of POIs (" << STATMSG << ")" << endl;
	cout << "------------------------------------------------" << endl;
	for (RooLinkedListIter it = fitPOIs.iterator(); RooRealVar* POI = dynamic_cast<RooRealVar*>(it.Next());) 
	{
		if (POI->isConstant()) continue;
		Float_t err= (fabs(POI->getAsymErrorHi()) + fabs(POI->getAsymErrorLo()))/2;  //how to get err?
		cout<<POI->GetName()<<" : "<<err*100<<endl;
	}

	TDatime time;
	int time_i=time.GetTime();
	char time_str[9];
	sprintf(time_str, "%6i", time_i);
	string res="outs/log/Fitresult";
	res+=time_str;
	ofstream outs(res);
	outs << endl << "  Fit Summary of POIs (" << STATMSG << ")" << endl;
	outs << "------------------------------------------------" << endl;
	RooPrintable::defaultPrintStream(&outs);
	for (RooLinkedListIter it = fitPOIs.iterator(); RooRealVar* POI = dynamic_cast<RooRealVar*>(it.Next());) 
	{
		if (POI->isConstant()) continue;
		POI->Print();
		outs<<"E:"<<POI->getError()<<endl;
		// outs<<"H:"<<POI->getErrorHi()<<endl;
		// outs<<"L:"<<POI->getErrorLo()<<endl;
		// outs<<"aH:"<<POI->getAsymErrorHi()<<endl;
		// outs<<"aL:"<<POI->getAsymErrorLo()<<endl;
	}

	if (status) 
	{
		cout << "FAIL" << endl;
		cout << "   *****************************************" << endl;
		cout << "          WARNING: Fit status failed.       " << endl;
		cout << "   *****************************************" << "ENDC" << endl;
	}

	cout << endl;
	return 1;
	}
