// -*- C++ -*- //  
//
// Description: Genarate Asimov data and fit data    
//
// Original Author:  tanyh <tanyuhang@ihep.ac.cn>
//         Created:  [2019-03-04 ] 
//         Inspired by Kaili's code  



#define DEBUG 1 // to 1: more details 
#include "head.h" 
using namespace std;
using namespace RooFit; 
using namespace RooStats;

RooWorkspace *makespace(TString cname, int index)
{
    RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);


    channel c=channelbyname(cname); 
    checkcname(cname);

    n_sig =  c.nsig;
    n_bkg =  c.nbkg;
    m_low =  c.mlow;
    m_high=  c.mhigh;
    invMass.setRange(m_low, m_high);
    TString ECM="240";

    cout << "Makeing workspace for channel " << cname << endl; 
	
    if (DEBUG && (index==0) )  cerr << "Begin "<<ECM<<" workspace building"<<endl;
   
    cerr << "Makeing workspace for channel " << cname << endl; //direnctly to screen

    RooWorkspace wspace("wspace");
    wspace.importClassCode();  //Inport code of all classes in the workspace that have a class name that matches pattern 'pat' and which are not found to be part of the standard ROOT distribution.
    RooArgSet poi,nuispara,globobs,observable,un,constraints;

    RooProduct u_c("u_c", "u_c", un); //uncer_common

    poi.add(RooArgSet(mu_in));
    observable.add(invMass);
    observable.add(weight);
    wspace.import(observable);
    wspace.import(u_c);
    wspace.import(poi);

    wspace.defineSet("Observables", observable, kTRUE);

    //Declare data path, number of signals, pois per channel
    // get yields and shape of signal and background

    Float_t ns, nbkg;
    TString ns_str, nbkg_str;
    TString a1, b1, a2, kcom, ksub, ksig, kzh, kz, a3, b3, a4, b4;

    TString modelname  = "SUM::modelSB(";
    kcom = "u_c";
    kzh  = "u_c";
    TString cname_collect;

    d_tot=new RooDataSet("d_tot","d_tot", RooArgSet(invMass, weight), WeightVar(weight));//weigtVar: interpret the given variable as event weight rather than as observabl

    for (int i = 0; i < n_sig; i++) 
    {
        TString func="DSCB";
        ns = pdfShape(wspace, c, "s", func);
  
        ns_str=(TString)to_string(ns);
//		cerr<<"nsig_str:"<<ns_str<<endl;
        a1 = "n_s";  //a1:n_s 
        modelname += "n_s*pdf_s,";
  
        b1 = "prod::" + a1 + "(" + ns_str + "," + kcom;
        
        TString cnamex;
        if (n_sig==1) cnamex=cname;
            else      cnamex=cname+"_s";

        cname_collect+=cnamex;    //mz4v,

        wspace.factory(cnamex+"[1,-1,5]");

        poi.add(*wspace.var(cnamex));
        b1 += ","+cnamex+ ",mu_in)";
        wspace.factory(b1);

//		cerr<<"poi:"<<poi<<endl;
//		cerr<<"b1:"<<b1<<endl;
    }
    if (n_bkg != 0)
    {
        TString func="exp2";
        nbkg = pdfShape(wspace, c, "b" , func);
        nbkg_str=(TString)to_string(nbkg);
        wspace.factory("n_b[" + nbkg_str + "]");

        modelname += "n_b*pdf_b)";
//		cerr<<"nbkg_str:"<<nbkg_str<<endl;
    }

	wspace.factory(modelname);

//	cerr<<"modelname:"<<modelname<<endl;

	wspace.defineSet("Pois", poi, kTRUE);
	wspace.Print("v");

	TString correlated = "mu_in,";
	correlated+=cname_collect;
//    cerr<<"correlated"<<correlated<<endl;
	// cout<<"correlated var:"<<correlated<<endl;


	RooWorkspace *wchannel = new RooWorkspace("wchannel_" + cname);
	wchannel->importClassCode();
	wchannel->import(poi, RooFit::RecycleConflictNodes());
	wchannel->import(*wspace.pdf("modelSB"), RooFit::RenameAllNodes(cname),
						RooFit::RenameAllVariablesExcept(cname, correlated),
						RooFit::RecycleConflictNodes());


	RooArgSet *observable_wchannel = new RooArgSet();
	TIterator *iter_observable = wspace.set("Observables")->createIterator();
	RooRealVar *parg_observable;
	while ((parg_observable = (RooRealVar *)iter_observable->Next())) 
	{
		TString name_observable = parg_observable->GetName() + (TString)"_" + cname;

		if ((bool)wchannel->obj(name_observable) == true) observable_wchannel->add(*(RooRealVar *)wchannel->obj(name_observable));
	}

	RooArgSet *poi_set = new RooArgSet();
	TIterator *iter_poi = wspace.set("Pois")->createIterator();
	RooRealVar *parg_poi;
	while ((parg_poi = (RooRealVar *)iter_poi->Next())) 
	{
		
		if ((bool)wchannel->obj(parg_poi->GetName()) == true) poi_set->add(*(RooRealVar *)wchannel->obj(parg_poi->GetName()));
	}
//	cerr<<"poi:"<<*poi_set<<endl;
//	cerr<<"Observables:"<<*observable_wchannel<<endl;
//	cerr<<"nuisanceParameters:"<<*nuisance_wchannel<<endl;
//	cerr<<"globalObservables:"<<*global_wchannel<<endl;
	wchannel->defineSet("Pois",                 *poi_set,               kTRUE);
	wchannel->defineSet("Observables",          *observable_wchannel,   kTRUE);


	RooArgSet *obs_plus_wt = new RooArgSet();
	//wt.printValue();   RooRealVar 怎么输出？
	obs_plus_wt->add(wt);
	//cerr<<"obs_plus_wt:"<<*obs_plus_wt<<endl;
	obs_plus_wt->add(*wchannel->set("Observables"));
	RooDataSet *AsimovSB =  new RooDataSet("AsimovSB", "AsimovSB", *obs_plus_wt, WeightVar(wt));

	Float_t npoints = 1000;
	Float_t total_SBevents = 0;

	if ( isinvi ) npoints*= 10;

	for (int i = 0; i < n_sig; i++) total_SBevents += (*wchannel->function("n_s_" + cname)).getVal();
	// if ( n_bkg != 0)   total_SBevents += (*wchannel->var("n_b_" + cname)).getVal();
	if ( n_bkg != 0)   total_SBevents += (*wchannel->var("n_b_" + cname)).getVal();
	cerr<<"Begin making Asimov data"<<endl;

	RooAbsReal *integral;
	Float_t integral_weight; 
	
	RooRealVar *mas = wchannel->var("invMass_" + cname);
	// if (cname.Contains("imp")) mas=wchannel->var("impact_" + cname);
	Float_t massrange = c.mhigh - c.mlow;
	Float_t width = massrange / npoints;
	Float_t mass_val  = c.mlow;

	for (int i = 0; i < npoints; i++) {
		mas->setRange("range", mass_val, mass_val + width);
		integral =(RooAbsReal *)
			(wchannel->pdf("modelSB_" + cname)->createIntegral(RooArgSet(*mas), NormSet(*mas),Range("range")));

		mas->setVal(mass_val+ 0.5 * width);
		integral_weight = integral->getVal() * total_SBevents ;
//	cerr<<"integral_weight:"<<integral_weight<<endl;
		wt.setVal(integral_weight);
		AsimovSB->add(RooArgSet(*mas, wt), integral_weight); //为什么有两次wt
		mass_val += width;
	}


	wchannel->import(*AsimovSB);
	// wspace.import(*AsimovSB);
	//     if (lu==2)
	// {

	wchannel->import(*d_tot, RooFit::RenameAllNodes(cname),
		RooFit::RenameAllVariablesExcept(cname, correlated),
		RooFit::RecycleConflictNodes(),
		RooFit::RenameVariable("invMass","invMass_"+cname));

	
	// }

	wspace.writeToFile("out/workspace/part/ws_"+cname+"_5.root");
	wchannel->writeToFile("out/workspace/part/wchannel_"+cname+"_5.root"); //data and parameter


	return wchannel;
}

Float_t pdfShape(RooWorkspace &ws, channel c, TString proc, TString func) 
{
    TString cname=c.name;
    TString ntuple;
    if (proc=="b") ntuple=c.f_bkg; 
    else ntuple =c.f_sig.at(proc);

    TFile *f = new TFile(ntuple);
    TTree *data = (TTree *)f->Get("HiggsTree");

    Float_t var;  
    Float_t scale;
    Int_t nentries = data->GetEntries();
    Float_t ns = 0;
//    cerr<<"nentries:"<<nentries<<endl;
    RooDataSet d_mass("d_mass_"+proc, "d_mass_"+proc, RooArgSet(invMass, weight), WeightVar(weight));
 
    data->SetBranchAddress(varnamesetting(cname), &var);
    data->SetBranchAddress("weight",     &scale);
    for (Int_t i = 0; i < nentries; i++) 
    {
        data->GetEvent(i);
        if (( var < c.mlow || var > c.mhigh))  continue;

        scale*=weightscale  (cname, proc);
        ns += scale;
 
        invMass.setVal(var);
        d_mass.add(invMass, scale);
        d_tot->add(invMass, scale);
    }
    ws.import(d_mass);

    RooAbsPdf *pdf;
    // if (true) 

    TString fun=funcsetting(cname, proc);
    if ((fun!="") && (!cname.Contains("_"))) func=fun;
    if (nentries<28) func="keys";
    cerr << "primez_label=" << proc << "," << cname <<", 1st func="<<func<< endl;

    if (cname.Contains("rec")) test_mass = 91.19;
    pdf = pdffit(cname, invMass, d_mass, func);

    if ( func.Contains("cheb")  )
    { 
        ws.factory("RooChebychev::pdf_" + proc + "( invMass,{p0_"+ proc + "[" + p0+ "],p1_"+ proc + "[" + p1+ "],p2_"+ proc + "[" + p2+ "],p3_"+ proc + "[" + p3+ "],p4_"+ proc + "[" + p4+ "]});");
    }
    else if ( func.Contains("keys")  || func.Contains("binned") )
    {
        pdf->SetNameTitle("pdf_"+proc, "pdf_"+proc);
        ws.import(*pdf);
    }
    else if ( func.Contains("exp2"))
    {
        ws.factory("EXPR::pdf_" + proc + "('" + exps + "',invMass, p0_1" + proc + "[" + p0 + "], p1_1" + proc + "[" + p1 + "])");
    }
    else if ( func.Contains("Voigtian")  )
    {
        ws.factory("Voigtian::pdf_" + proc + "(invMass, mH_" + proc + "[" + p0 + "], width_" + proc + "[" + p1 + "], sigma_"+ proc +"["+ p2 +"])");
    }
    else if ( func.Contains("BifurGuassian") )
    {
        ws.factory("BifurGauss::pdf_" + proc + "(invMass, mH_" + proc + "[" + p0 + "], sigL_" + proc + "[" + p1 + "], sigR_"+ proc +"["+ p2 +"])");
    }
    else if ( func.Contains("GaussExp") )
    {
        // gROOT->ProcessLine(".L /afs/ihep.ac.cn/users/z/zhangkl/wfs/workspace/lib/libRooGaussExp.so"); 
        // pdf->Print();
        ws.importClassCode("RooGaussExp");
        ws.factory("mH_"    + proc + "[" + tmH + "]");
        ws.factory("sigma_" + proc + "[" + tsigma + "]");
        ws.factory("Tn_" + proc + "[" + tTn + "]");
        ws.factory("RooGaussExp::pdf_" + proc + "(invMass, mH_" + proc + ", sigma_" + proc + ", Tn_"+ proc +")");
        //Factory 并不行。 在非编译环境下可以factory/ import, 但依然不能将workspace存入文件.
        cout<<__LINE__<<endl;
        cout<<"20180826"<<endl;
        ws.Print("v");
    }
    else if ( func.Contains("CB") )
    {
        ws.factory("RooCBShape::peakPdf_"    + proc + "(invMass,mH_"   + proc + "[" +tmH + "],sigma_" + proc + "[" + tsigma + "],Talpha_"+ proc + "[" + tTalpha+ "],Tn_"    + proc + "[" + tTn    + "]);");
        ws.factory("RooBifurGauss::tailPdf_" + proc + "(invMass,mtail_"+ proc + "[" +tmH + "],sigL_"  + proc + "[" + tsigL  + "],sigR_"  + proc + "[" + tsigR  + "]);");
        ws.factory("SUM::pdf_" + proc + "(r_"+ proc + "[" + tratio +"]*peakPdf_" + proc + ",tailPdf_" + proc + ")");
        //  ws.factory("RooGaussExp::pdf_" + proc + "(invMass, mH_" + proc + "[" + p0 + "], sigma_" + proc + "[" + p1 + "], sigR_"+ proc +"["+ p2 +"])");
    }
// result_mu->Print("v");

    exps = "exp(@1*(@0-100)/100.0+@2*(@0-100)*(@0-100)/10000.0)";
    test_mass = 125.;       //reset configuration
    delete f;
    return ns;
}

RooAbsPdf* pdffit(TString cname, RooRealVar &var, RooDataSet &data, TString func)
{
    RooAbsPdf *pdf;
    RooFitResult *result_mu;
    // cerr<<"Now fitting: "<<func<<endl;
        
        Float_t Res_min=0.1;    //resolution
        Float_t Res_max=10;
        Float_t GaussWidthMax=8;

        RooRealVar p0v("p0", "p0v", -0.1, -10, 10);
        RooRealVar p1v("p1", "p1v", -0.2, -10, 10);
        RooRealVar p2v("p2", "p2v", -0.1, -10, 10);
        RooRealVar p3v("p3", "p3v", -0.2, -10, 10);
        RooRealVar p4v("p4", "p4v", -0.1, -10, 10);
        RooRealVar mH    ("signal_mean",  "mean of Higgs", test_mass, test_mass - 5, test_mass + 5);
        RooRealVar width ("signal_width", "width of Higgs", 1, 0, 10); //voigitian
        RooRealVar sigma ("mRes",  "Resolution", 1, Res_min, Res_max);
        RooRealVar sigL  ("sigL", "sigTail_L", 3, 0.1, GaussWidthMax);
        RooRealVar sigR  ("sigR", "sigTail_R", 3, 0.1, GaussWidthMax);
        RooRealVar Talpha("tailAlpha", "tail alpha of Higgs", -1.50, -10, 10);
        RooRealVar Tn    ("tailN", "tail N of Higgs", 5., 0.1, 20);
        RooRealVar ratio ("ratio", "ratio", 0.9, 0.2, 1);

if ( func.Contains("cheb")  )
    {
        pdf = new RooChebychev("pdf", "pdf", var, RooArgSet( p0v, p1v, p2v, p3v, p4v));
        result_mu = Minimize(pdf,  data);
        p0=(TString)to_string(p0v.getVal());
        p1=(TString)to_string(p1v.getVal());
        p2=(TString)to_string(p2v.getVal());
        p3=(TString)to_string(p3v.getVal());
        p4=(TString)to_string(p4v.getVal());
    }
if ( func.Contains("exp2"))
    {
        pdf = new RooGenericPdf("pdf", "pdf", exps, RooArgSet(var, p0v, p1v));
        result_mu = Minimize(pdf,  data);
        if (result_mu->status()!=0) 
        {
            cout<<"turn to exp with 125"<<endl;
            exps="exp(@1*(@0-125)/125.0+@2*(@0-125)*(@0-125)/15625.0)";
            pdf = new RooGenericPdf("pdf", "pdf", exps, RooArgSet(invMass, p0v, p1v));
            
            result_mu = Minimize(pdf,  data);
        }
        if (result_mu->status()!=0) 
        {
            cout<<"turn to exp with 70"<<endl;
            exps="exp(@1*(@0-70)/125.0+@2*(@0-70)*(@0-70)/6400.0)";
            pdf = new RooGenericPdf("pdf", "pdf", exps, RooArgSet(invMass, p0v, p1v));
            result_mu = Minimize(pdf,  data);
        }
        if (result_mu->status()!=0) cerr<<"exp2 failed"<<endl;
            // cout << "Building a second order ploy exponential pdf " << endl;
        p0=(TString)to_string(p0v.getVal());
        p1=(TString)to_string(p1v.getVal());
        // ws.factory("EXPR::pdf_" + proc + "('" + exps + "',invMass, p0_1" + proc + "[" + p0 + "], p1_1" + proc + "[" + p1 + "])");
    }
if ( func.Contains("Voigtian")  )
    {
        pdf =new RooVoigtian("pdf", "pdf", var, mH, width, sigma);
        result_mu = Minimize(pdf,  data);
        p0=(TString)to_string(mH.getVal());
        p1=(TString)to_string(width.getVal());
        p2=(TString)to_string(sigma.getVal());
        // ws.factory("Voigtian::pdf_" + proc + "(invMass, mH_" + proc + "[" + p0 + "], width_" + proc + "[" + p1 + "], sigma_"+ proc +"["+ p2 +"])");
    }
if ( func.Contains("BifurGuassian") )
    {
        pdf =new RooBifurGauss("bifurPdf", "bifur", var, mH, sigL, sigR);
        result_mu = Minimize(pdf,  data);
        if (DEBUG) result_mu->Print("v");
        p0=(TString)to_string(mH.getVal());
        p1=(TString)to_string(sigL.getVal());
        p2=(TString)to_string(sigR.getVal());
        // ws.factory("BifurGauss::pdf_" + proc + "(invMass, mH_" + proc + "[" + p0 + "], sigL_" + proc + "[" + p1 + "], sigR_"+ proc +"["+ p2 +"])");
    }
if ( func.Contains("CB") )
    {
        
//gROOT->ProcessLine(".L /afs/ihep.ac.cn/users/z/zhangkl/wfs/workspace/src/RooGaussExp_cxx.so"); 
        RooCBShape    peakPdf("peakPdf", "peak", var, mH, sigma, Talpha, Tn);
        RooBifurGauss tailPdf("tailPdf", "tail", var, mH, sigL, sigR);
        pdf =new RooAddPdf("pdf", "pdf", RooArgList(peakPdf, tailPdf), ratio);
        // pdf =new RooGaussExp("pdf", "pdf", var, mH, sigma, Tn);
        result_mu = Minimize(pdf,  data);
 //       result_mu = Minimize(pdf,  data);
        
        if (DEBUG) result_mu->Print("v");

        // if (cname.Contains("eemm")||cname.Contains("qqmm")||cname.Contains("qqmm")||cname.Contains("vvmm")||cname.Contains("mcom")) 

        tmH    =(TString)to_string( mH    .getVal());
        tsigma =(TString)to_string( sigma .getVal());
        tTalpha=(TString)to_string( Talpha.getVal());
        tTn    =(TString)to_string( Tn    .getVal());
        tsigL  =(TString)to_string( sigL  .getVal());
        tsigR  =(TString)to_string( sigR  .getVal());
        tratio =(TString)to_string( ratio .getVal());
    }
if ( func.Contains("GaussExp") )
    {
        // pdf =new RooGaussExp("pdf", "pdf", var, mH, sigma, Tn);
        result_mu = Minimize(pdf,  data);
 //       result_mu = Minimize(pdf,  data);
        
        if (DEBUG) result_mu->Print("v");

        // if (cname.Contains("eemm")||cname.Contains("qqmm")||cname.Contains("qqmm")||cname.Contains("vvmm")||cname.Contains("mcom")) 

        tmH    =(TString)to_string( mH    .getVal());
        tsigma =(TString)to_string( sigma .getVal());
        tTn    =(TString)to_string( Tn    .getVal());

    }
if ( func.Contains("keys")  || func.Contains("binned") )
    {
        Float_t rho=2;
        pdf = new RooKeysPdf("pdf", "pdf", var, data, RooKeysPdf::MirrorAsymBoth, rho); // special for the Z peak
        // ws.import(*pdf);
    }
    return pdf;
}
RooFitResult* Minimize(RooAbsPdf *&pdf, RooDataSet &data)
{
  RooAbsReal *nll = pdf->createNLL(data, NumCPU(4), Offset(kTRUE) );
//   RooAbsReal *nll = pdf->createNLL(data);
  RooMinimizer minim(*nll);
  minim.setStrategy( 2 );
  minim.setPrintLevel( -1 );    // now -1 is the best choice;
//   minim.setProfile(); /* print out time */
  minim.setEps( 1e-01 ); //large……
  minim.setOffsetting( true );
  minim.optimizeConst( 2 );

  int status = 0;
  status += minim.minimize( "Minuit2" );
  cout<<"minimize Finished"<<endl;
  cout<<"status:"<<status<<endl;
  RooFitResult* result = minim.save();
  return result;
}




