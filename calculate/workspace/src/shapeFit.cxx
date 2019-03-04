
"""
##Generate Asimov data and fit 

"""

__author__ = "Tan Yuhang <tanyuhang@ihep.ac.cn>"
__copyright__ = "Copyright (c) Tanyuhang"
__created__ = "[2019-03-04 ]"


#include "numberCounting.h" 
#include "shapeFit.h"
#include "makespace.cxx" 
#include "TDatime.h"

RooCategory* channellist = new RooCategory("channellist","channellist");
RooSimultaneous CombinedPdf("CombinedPdf","",*channellist) ;
RooArgSet* Observables = new RooArgSet(); // x value
RooArgSet* ks = new RooArgSet();
map<string,RooDataSet*> datasetMap_SBasimov;
RooArgSet *args = new RooArgSet();

int main(int argc, char **argv)
{
    clock_t start, finish;
    start = clock(); 
    gROOT -> Reset();
    gROOT -> Time();
 
    RooWorkspace* w[Nch];
    vector<string> catName;
    vector<TString> CN;
    RooRealVar wt("wt","wt",1);

    args->add(wt);

    //defined parameter


    for( int i = 0 ; i < Nch; i ++ )
    {
		//read some information from shapefit.h
        CN.push_back(m_CN[i]);
        catName.push_back((string)CN[i]);
        channel c=channelbyname(CN[i]);
        n_bkg = c.nbkg;   
        w[i] = makespace(CN[i] , i);

        PlotPdf(w[i],n_bkg,CN[i]); //fit   sig+bkg of normal data
        PlotAsimov(w[i],n_bkg,CN[i]);// fit sig+bkg of Asimov data
        PlotSB(c,CN[i]);  //plot signal and background respectively

		
		//define some parameter
        channellist -> defineType(CN[i]) ;
        CombinedPdf.addPdf(*w[i]->pdf("modelSB_"+CN[i]),CN[i]) ;
        Observables->add(*w[i]->set("Observables"));
        ks->add( *w[i]->set("Pois"));
        datasetMap_SBasimov[catName[i]] = (RooDataSet*)w[i]->data("AsimovSB");  //??
    
    }

//	FillPara(w[i],CN[i],catName[i]); 
    RooWorkspace* combination = new RooWorkspace("combination");
    combination -> importClassCode();
    combination -> import(CombinedPdf);
    combination -> defineSet("Observables",*Observables, true);               //mean value of x axis
    combination -> defineSet("poi", *ks, true);      //Statistical error
    args->add(*Observables);
//    cerr<<"Observables:"<<*Observables<<endl;
    RooDataSet* AsimovSB = new RooDataSet("AsimovSB","Asimov SB data ",*args, Index(*channellist), Import(datasetMap_SBasimov) ,WeightVar(wt));//??
    combination->import(*AsimovSB);
 //   cerr<<"channellist:"<<channellist<<endl;
    //  ks->Print("v");
	cout<<".................combination................"<<endl;
    combination->Print("v");
//    ModelConfig *mconfig = new ModelConfig("ModelConfig",combination);
//    mconfig -> SetPdf(*combination->pdf("CombinedPdf"));
//    mconfig -> SetObservables( *combination->set("Observables"));  //specify the observables
//    mconfig -> SetParametersOfInterest( (*combination->set("poi")) ); //specify the parameters of interest 
//    combination -> import(*mconfig);
    combination->writeToFile("out/workspace/cepc_5.root");
    TDatime time;
    int time_i=time.GetTime();
    string time_str=to_string(time_i);
    TString Ntime = time_str;
    combination->writeToFile("out/workspace/_"+Ntime+".root");
    
    cout<<"workspace/cepc_5 finished, primez"<<endl;

    finish = clock();
    cout<<endl<<"main:: All Done! Used time: "<<(finish - start)/CLOCKS_PER_SEC<<"seconds"<<endl;
    cerr<<endl<<"main1:: All Done! Used time: "<<(finish - start)/CLOCKS_PER_SEC<<"seconds"<<endl; 
    return 0;

}

void PlotPdf (RooWorkspace *wspace, int n_bkg , TString cname)
{

   TCanvas *canvas = new TCanvas("c1", "c1", 800, 800);
   canvas->SetMargin(0.16, 0.04, 0.11, 0.02);

   //raw data 
   RooPlot *frame;   
   frame = (*wspace->var("invMass_"+cname)).frame(25);
   wspace->data("d_tot")->plotOn(frame,DataError(RooAbsData::Poisson),XErrorSize(0),MarkerSize(2)); 
   wspace->pdf("modelSB_"+cname)->plotOn(frame, Name("Fit"), LineColor(4));
   wspace->pdf("modelSB_" +cname)->plotOn(frame, Name("s"),  Components((*wspace->pdf("pdf_s_" +cname))), LineColor(kRed),LineStyle(2));//s
   wspace->pdf("modelSB_" +cname)->plotOn(frame, Name("bkg"), Components((*wspace->pdf("pdf_b_" +cname))), LineColor(kGreen), LineStyle(2));
   frame->SetTitle(""); 
   if ( SetPlotMaximum(cname) )  frame->SetMaximum(PlotMaximum); //set y height
   frame->Draw();

    Float_t lxmin,lxmax,lymin,lymax,tx,ty;
    tx=0.6;      ty=0.78;
    lxmin=0.2;   lymin=0.76; 
    int n_ent=4;

    lymax=lymin+0.05*n_ent;
    lxmax=lxmin+0.2;
    TLegend *legend = new TLegend(lxmin, lymin, lxmax, lymax);

//    FormatLegend(legend);
//    FormatLegend(legend);
    legend->AddEntry("MCdata","CEPC Simulation","P");
    legend->AddEntry("Fit","S+B Fit","L");

    legend->AddEntry("s" , "Signal", "L"); 

    if ( n_bkg != 0)   legend->AddEntry("bkg", "Background",  "L"); //always be last
    
    legend->Draw("same");

    TLatex *tex = new TLatex();
	tex->SetNDC(kTRUE);
	tex->SetTextFont(43);
	tex->SetTextSize(28);

    tex->DrawLatexNDC(tx, ty+0.14, "#bf{CEPC CDR}");

    tex->DrawLatexNDC(tx, ty+0.09, "5.6 ab^{-1}, 240 GeV");
    TString e_cname=namesetting(cname);
    tex->DrawLatexNDC(tx, ty+0.04, e_cname);

    canvas->SaveAs("../../fig/"+cname+"/"+cname+"rawfit.pdf");

    delete canvas;
    delete frame;
    delete legend;
}

void PlotAsimov (RooWorkspace *wspace, int n_bkg , TString cname)
{
	  //AsimovSB data 
	TCanvas *xcanvas = new TCanvas("c2", "c2", 800, 800);
	xcanvas->SetMargin(0.16, 0.04, 0.11, 0.02);
	RooPlot *xframe;   
	xframe = (*wspace->var("invMass_"+cname)).frame(25);
	wspace->data("AsimovSB")->plotOn(xframe,DataError(RooAbsData::Poisson),XErrorSize(0),MarkerSize(2)); 
	wspace->pdf("modelSB_"+cname)->plotOn(xframe, Name("Fit"), LineColor(4));
	wspace->pdf("modelSB_" +cname)->plotOn(xframe, Name("s"),  Components((*wspace->pdf("pdf_s_" +cname))), LineColor(kRed),LineStyle(2));//s
	wspace->pdf("modelSB_" +cname)->plotOn(xframe, Name("bkg"), Components((*wspace->pdf("pdf_b_" +cname))), LineColor(kGreen), LineStyle(2));
    xframe->SetTitle(""); 	
	if ( SetPlotMaximum(cname) )  xframe->SetMaximum(PlotMaximum); 
	xframe->Draw();
	
	Float_t lxmin,lxmax,lymin,lymax,tx,ty;
	tx=0.6;      ty=0.78;
	lxmin=0.2;   lymin=0.76; 
	int n_ent=4;

	lymax=lymin+0.05*n_ent;
	lxmax=lxmin+0.2;
	TLegend *legend = new TLegend(lxmin, lymin, lxmax, lymax);

	legend->AddEntry("MCdata","CEPC Simulation","P");
	legend->AddEntry("Fit","S+B Fit","L");

	legend->AddEntry("s" , "Signal", "L"); 

	if ( n_bkg != 0)   legend->AddEntry("bkg", "Background",  "L"); //always be last
	
	legend->Draw("same");

	TLatex *tex = new TLatex();
	tex->SetNDC(kTRUE);
	tex->SetTextFont(43);
	tex->SetTextSize(28);
//    FormatLatex(tex);
	tex->DrawLatexNDC(tx, ty+0.14, "#bf{CEPC CDR}");
	tex->DrawLatexNDC(tx, ty+0.09, "5.6 ab^{-1}, 240 GeV");
	TString e_cname=namesetting(cname);
	tex->DrawLatexNDC(tx, ty+0.04, e_cname);

	xcanvas->SaveAs("../../fig/"+cname+"/"+cname+"Asimovfit.pdf");

	delete xcanvas;
	delete xframe;  
	delete legend ;

}

void PlotSB (channel c, TString cname)
{

	TString wsname="out/workspace/part/ws_"+cname+"_5.root";
	TFile fs;
	RooWorkspace *ws;
    ws=      (RooWorkspace*)      fs.Open(wsname,"READ")->Get("wspace");
	Plotsig(ws,c,"s");
	Plotsig(ws,c,"b");

}

void Plotsig(RooWorkspace *wspace, channel c, TString proc)

{
    TString cname=c.name;   
    TString e_cname=namesetting(cname);
    TString e_m=xnamesetting(cname);	
    TString e_proc;
    if (proc=="s" ) e_proc="Signal";
    if (proc=="b") e_proc="Background";
    TCanvas *ycanvas = new TCanvas("c3", "c3", 800, 800);
    ycanvas->SetMargin(0.16, 0.04, 0.11, 0.02);	
    RooRealVar *hmass =(RooRealVar *)(wspace->var ("invMass"));
    RooDataSet *d_mass=(RooDataSet *)(wspace->data("d_mass_"+proc));
    RooPlot    *yframe = hmass->frame(100);
    d_mass->plotOn(yframe, Name(proc+"_hist"), DataError(RooAbsData::SumW2),MarkerColor(kBlack), XErrorSize(0));
    if (proc=="b") (*wspace->pdf("pdf_b")    ).plotOn(yframe, Name(proc), LineColor(kGreen));
    else           (*wspace->pdf("pdf_"+proc)).plotOn(yframe, Name(proc), LineColor(kBlue));
    yframe->SetTitle("");  
	yframe->Draw();	



    TLegend *legend = new TLegend(0.8, 0.86, 0.95, 0.95);
    legend->AddEntry("s_hist" , "Data", "P");
	if (proc=="s")     legend->AddEntry("s" , "Signal", "L");
	else  legend->AddEntry("b" , "Background", "L");
	legend->Draw("same");

    Float_t Entries=d_mass->sumEntries();
    char ent_str[9];
    sprintf(ent_str, "%6.2f", Entries);
    TString ent=e_proc+": ";
    ent+=ent_str;

	TLatex *tex = new TLatex();

	tex->SetNDC(kTRUE);
	tex->SetTextFont(43);
	tex->SetTextSize(15);
    tex->DrawLatexNDC(0.78, 0.82,ent);	

	ycanvas->SaveAs("../../fig/"+cname+"/"+cname+"_"+proc+"_fit.pdf");
	
	delete ycanvas;
	delete yframe;
	delete legend;
}