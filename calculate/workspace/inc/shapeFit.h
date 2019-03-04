#ifndef SHAPE_H 
#define SHAPE_H
   
const int Nch = 3;  
const TString m_CN[Nch] = {  
                                "qz4v", 
                                "ez4v",
								"mz4v",      
								};
							
typedef struct channel
{
    TString name;
    int nsig=1;
    int nbkg=1;
    Float_t mlow=120;
    Float_t mhigh=150;
    TString f_bkg;
    //vector<TString> name_sig;       
    TString name_sig[10];
    map<TString, TString> f_sig;    
} channel;

const channel c[3]=
{
    {   "qz4v", 1, 1, 120, 150,
        "data/hinvi/qz4v_bkg.root",
        {"s"},
        {
            {"s",   "data/hinvi/qz4v_sig.root"}
        }
    },
    {   "ez4v", 1, 1, 120, 160,
        "data/hinvi/ez4v_bkg.root",
        {"s"},
        {
            {"s",   "data/hinvi/ez4v_sig.root"}
        }
    },
    {   "mz4v", 1, 1, 120, 130,
        // "data/hinvi/invi_mm_bkg.root",
        "data/hinvi/mz4v_bkg.root",
        {"s"},
        {
            // {"s",   "data/hinvi/invi_mm_sig.root"}
             {"s",   "data/hinvi/mz4v_sig.root"}
        }
    }
};

// TString 2dname;
RooDataSet* d_tot;

        TString p0, p1, p2, p3, p4;
        TString tmH    ;
        TString tsigma ;
        TString tTalpha;
        TString tTn    ;
        TString tsigL  ;
        TString tsigR  ;
        TString tratio ;
        TString exps = "exp(@1*(@0-100)/100.0+@2*(@0-100)*(@0-100)/10000.0)";

        Float_t test_mass = 125.;

const map<TString, TString> name=
{
    {"qz4v",    "Z#rightarrowq#bar{q}, H#rightarrowZZ*#rightarrow#nu#nu#nu#nu"},
    {"ez4v",    "Z#rightarrowe^{+}e^{-}, H#rightarrowZZ*#rightarrow#nu#nu#nu#nu"},
    {"mz4v",    "Z#rightarrow#mu^{+}#mu^{-}, H#rightarrowZZ*#rightarrow#nu#nu#nu#nu"}
};
const map<TString, TString> xrec=
{
  {"qz4v",        "Recoil"},   
  {"ez4v",        "Recoil"},   
  {"mz4v",        "Recoil"}           
};
const map<TString, TString> xname=
{
    {"qz4v",    "qq"},
    {"ez4v",    "ee"},
    {"mz4v",    "#mu#mu"},
};
const map<TString, TString> varname=
{
    {"vw4q_rec",        "Mass_missing"},  
};
const map<TString, Float_t> histomax=
{
    {"qz4v",15000},
    {"ez4v",3000 },
    {"mz4v",800 }

};
TString funcsetting(TString cname, TString proc)
{
    TString f="";
    if (proc=="b")
    {
        if  (  cname.Contains("mz4v")) f="Voigtian"; 
        if  (  cname.Contains("qz4v")) f="keys";
        if  (  cname.Contains("ez4v")) f="keys";
    }
    else
    {           //signal
        if (cname.Contains("qz4v") ) f="BifurGuassian";
        // if (cname.Contains("yy") )   f="Voigtian";      //currently yy is Symmetrical.
        if (cname.Contains("ez4v") )   f="DSCB";      //currently yy is Symmetrical.
        if (cname.Contains("mz4v") )   f="DSCB";      //currently yy is Symmetrical.
    }
 return f;
}

int indexbyname(TString cname)
{
    for (int i=0; i<100; i++)
        if (c[i].name==cname) return i;
    return 0;
}
channel channelbyname(TString cname)
{
    for (int i=0; i<100; i++)
        if (c[i].name==cname) return c[i];
    return c[0];
}
//如果pdf没选好 大概率在拟合信号强度时崩

// Float_t lum=1; 
Float_t lum=1; // 5 ab-1 to 5.6 ab-1   How to understand this?

Float_t weightscale  (TString cname, TString proc)
{
    Float_t w=1;
    return w*1.12;
}

bool isinvi=false;

void checkcname(TString cname)
{
    isinvi=false;
    if (cname.Contains("4v"))
        isinvi=true;
    else 
	cerr<<"Check channels with error!"<<endl;
    // isforplot=true;
}

TString varnamesetting(TString cname)  // What's mean of varname? 
{
    TString str="Mass_invar";
    if ( varname.count(cname)>0 )  str=varname.at(cname);
    return str;
}
TString namesetting(TString cname)
{
    TString str="";
    if ( name.count(cname)>0 )      str=name.at(cname);
    return str;
}
TString xnamesetting(TString cname)
{
    TString str="";
    if ( xname.count(cname)>0 )  str=xname.at(cname);
    return str;
}
TString xrecsetting(TString cname)
{
    TString str="";
    if ( xrec.count(cname)>0 )  str=xrec.at(cname);
    return str;
}

Float_t PlotMaximum=0;
bool SetPlotMaximum(TString cname )
{
    bool defined=false;
    if ( histomax.count(cname)>0 ) 
    {
        defined     = true;
        PlotMaximum = histomax.at(cname)*1.12;  // 5 to 5.6;
    }
    return defined;
}

Float_t number[4]={0.1,0.4,1,2};
TString lu_n="5";
TString n[4]={"0.5","2","5","10"}; 

Float_t uncer_cx    = 0.005; // this is uncer of cx.
TString sigma_cx    ="0.005";
Float_t uncer_lumi  = 0.001;
TString sigma_lumi  ="0.001";

int     n_sig, n_bkg;
Float_t m_low, m_high;
Float_t v2_high, v2_low;
TString proc[10];

RooRealVar mu_in("mu_in", "mu_in", 1, -1, 5);
RooRealVar weight   ("weight", "weight", 1, -1, 10000.);
RooRealVar invMass ("invMass", "invMass", 120, 150);
RooRealVar recMass ("recMass", "recMass", 70, 110);
RooRealVar wt("wt", "wt", 1);

RooWorkspace *makespace(TString cname, int index);
// Float_t tempsetShape(RooWorkspace &ws,   channel c, TString proc);
Float_t    pdfShape    (RooWorkspace &ws,   channel c, TString proc, TString func);

RooAbsPdf* pdffit      (TString cname, RooRealVar &var, RooDataSet &data, TString func);
// void pdffit(RooAbsPdf* pdf, TString func); 难以实现 因为需要factory写死参数
void plotFit    (RooWorkspace *wchannel,channel c, TString proc="s",TString lu_n="5");
void plotImport (RooWorkspace *wspace,  channel c, TString proc,    TString lu_n="5");
void PlotPdf    (RooWorkspace *wspace, int n_bkg , TString cname); 
void PlotAsimov    (RooWorkspace *wspace, int n_bkg , TString cname);
void Plotsig(RooWorkspace *wspace, channel c, TString proc);
void PlotSB (channel c, TString cname);
void FormatAxis(TAxis * axis, double offset);
void FormatLegend(TLegend *legend);
RooFitResult* Minimize(RooAbsPdf *&pdf, RooDataSet &data);

#endif
