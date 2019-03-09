#include "frame.h"

using namespace std;
using namespace CommonFunc;
using namespace RooStats;

int main(int argc, char **argv){
  //============================ Global booking and setting ==========================
  //   gErrorIgnoreLevel = kError+1;
  map<string,bool> Opt;
  Opt["LIMIT"]=false;
  Opt["PVALUE"]=false;

  TString myOptList="";
  if(argc>1) myOptList=argv[1];
  myOptList.ToUpper();
  if (myOptList != "") {
    for (std::map<std::string,bool>::iterator it = Opt.begin(); it != Opt.end(); it++) it->second = false;

    std::vector<TString> olist = TMVA::gTools().SplitString( myOptList, ',' );
    for (UInt_t i=0; i<olist.size(); i++) {
      std::string Option(olist[i]);
      
      if (Opt.find(Option) == Opt.end()) {
	std::cout << "Option \"" << Option << "\" not known in DrawFrame under this name. Choose among the following:" << std::endl;
	for (std::map<std::string,bool>::iterator it = Opt.begin(); it != Opt.end(); it++) std::cout << it->first << " ";
	std::cout << std::endl;
	return 1;
      }
      Opt[Option] = true;
    }
  }
  SetAtlasStyle();
  //================================= Draw Limit Band ====================================
  if(Opt["LIMIT"]){
    if(argc<4){
      cout<<"Usage: ./Frame limit <jobname> <imode> <option>"<<endl;
      exit(0);
    }
    TString jobname=argc>2 ? argv[2] : "nominal";
    int imode=argc>3 ? atoi(argv[3]) : 1;
    TString option=argv[4];
    TString type;
    string fileName[5];
    int nsample=1;
    fileName[0]=jobname.Data();

    double mass[5][200];
    double N2S[5][200],N1S[5][200],P1S[5][200],P2S[5][200],Median[5][200],Zero[5][200],Observed[5][200];
    vector<int> temp;
    TCanvas *cv = CreateCanvas("canvas", "",1024,768);
    int nmass[5];

    // gg limit
    if(imode==0){	       
      type="gg";
      nsample=1;
      for(int Mass=1100;Mass<=1400;Mass+=5) temp.push_back(Mass);
      for(int Mass=1400;Mass<=1500;Mass+=10) temp.push_back(Mass);
      nmass[0]=temp.size();
      for(int i=0;i<nmass[0];i++) mass[0][i]=temp[i];
    }
    else return -1;

    system(Form("mkdir -vp fig/limit_plot/%s",jobname.Data()));
    ofstream fout(Form("fig/limit_plot/%s/info_%s.txt",jobname.Data(),type.Data()),ios::out);
    fout<<Form("Mass \t -2S \t -1S \t Med \t +1S \t +2S \t Obs")<<endl;
    double max=0;
    for(int jj=0;jj<nsample;jj++){
      Info("Frame: LIMIT","%d mass points will be processed.",nmass[jj]);
      for(int idx=0;idx<nmass[jj];idx++){

	string infile=Form("out/%s/%3.3d.txt", fileName[jj].c_str(),(int)mass[jj][idx]);
	ifstream fin(infile.c_str(),ios::in);
	if(!fin){
	  cerr<<"File "<<infile.c_str()<<" does not exist."<<endl;
	  continue;
	}
	double n2s,n1s,median,p1s,p2s,observed,dummy;
	fin>>dummy>>observed>>median>>p2s>>p1s>>n1s>>n2s;
	fin.close();
	if(imode==0) mass[jj][idx]/=10;
	cout << "Mass "<<mass[jj][idx]<<" GeV"<<endl;
	cout << "-2 sigma  band " << n2s << endl; N2S[jj][idx]=median-n2s;
	cout << "-1 sigma  band " << n1s << endl; N1S[jj][idx]=median-n1s;
	cout << "Median of band " << median << endl; Median[jj][idx]=median;
	cout << "+1 sigma  band " << p1s << endl; P1S[jj][idx]=p1s-median;
	cout << "+2 sigma  band " << p2s << endl; P2S[jj][idx]=p2s-median;
	cout << "Observed "<<observed<<endl;Observed[jj][idx]=observed;
	Zero[jj][idx]=0;
	if(p2s>max)max=p2s;
	if(observed>max)max=observed;
	
	fout<<Form("%.1f \t %.2f \t %.2f \t %.2f \t %.2f \t %.2f \t %.2f",mass[jj][idx],n2s,n1s,median,p1s,p2s,observed)<<endl;
      }
    }
    cout<<"All info has been retrieved."<<endl;
    TGraph *likelihd_limit_d[5];
    TGraph *likelihd_limit_c[5];
    TGraphAsymmErrors *likelihd_limit_1sigma[5];
    TGraphAsymmErrors *likelihd_limit_2sigma[5];
    TMultiGraph *likelihd_limit = new TMultiGraph("exclusionlimit_p","CL_{S} Exclusion Limits ;m_{H} [GeV]; 95% CL limit on #sigma/#sigma_{SM}");

    TList *leglist=new TList();
    vector<TString> legtext;
    vector<TString> legopt;
    for(int jj=0;jj<nsample;jj++){	// WSN...
      likelihd_limit_d[jj] = new TGraph(nmass[jj],mass[jj],Observed[jj]);
      if(jj!=0){

      }
      likelihd_limit_d[jj]->SetLineWidth(3);
      likelihd_limit_d[jj]->SetLineStyle(1); 
      likelihd_limit_d[jj]->SetMarkerSize(0.9);

      likelihd_limit_c[jj] = new TGraph(nmass[jj],mass[jj],Median[jj]);
      likelihd_limit_c[jj]->SetLineWidth(2);
      likelihd_limit_c[jj]->SetLineStyle(2);

      if(imode==0){
	likelihd_limit_c[jj]->SetLineStyle(1);
	likelihd_limit_c[jj]->SetLineWidth(3);
	likelihd_limit_c[jj]->SetLineColor(kRed);
      }

      likelihd_limit_1sigma[jj] = new TGraphAsymmErrors(nmass[jj],mass[jj],Median[jj],Zero[jj],Zero[jj],N1S[jj],P1S[jj]);
      likelihd_limit_1sigma[jj]->SetFillColor(kGreen);

      likelihd_limit_2sigma[jj] = new TGraphAsymmErrors(nmass[jj],mass[jj],Median[jj],Zero[jj],Zero[jj],N2S[jj],P2S[jj]);

      likelihd_limit_2sigma[jj]->SetFillColor(kYellow);

      likelihd_limit->Add(likelihd_limit_2sigma[jj],"E3");  
      likelihd_limit->Add(likelihd_limit_1sigma[jj],"E3");

      likelihd_limit->Add(likelihd_limit_d[jj], "L");
      likelihd_limit->Add(likelihd_limit_c[jj], "L");

    }


    double x1,y1,x2,y2;
    GetX1Y1X2Y2(cv,x1,y1,x2,y2);

    leglist->Add(likelihd_limit_d[0]);legtext.push_back("Observed");legopt.push_back("L");
    leglist->Add(likelihd_limit_c[0]);legtext.push_back("Expected");legopt.push_back("L");
    leglist->Add(likelihd_limit_1sigma[0]);legtext.push_back("#pm 1#sigma");legopt.push_back("F");
    leglist->Add(likelihd_limit_2sigma[0]);legtext.push_back("#pm 2#sigma");legopt.push_back("F");
    TLegend* legend=CreateLegend(x2-0.35,y2-0.3,x2-0.02,y2-0.01,leglist,legtext,legopt,0.05);

    vector<TString> pavetext;
//     pavetext.push_back("#bf{#it{ATLAS}} Preliminary");
    // It is ATLAS now. 2011-08-12 4:48 p.m.
//     pavetext.push_back("#bf{#it{ATLAS}}");
    if(imode==0) pavetext.push_back("H#rightarrow#gamma#gamma, 2012 Data");
    else if(imode==1) pavetext.push_back("H#rightarrowZZ#rightarrowll#nu#nu");
    else if(imode==2) pavetext.push_back("H#rightarrowZZ#rightarrowllqq");
    else if(imode==4) pavetext.push_back("H#rightarrowZZ");
//     pavetext.push_back("#intLdt=2.05fb^{-1}, #sqrt{s}=7TeV");
    if(imode==1||imode==2) pavetext.push_back("#scale[0.6]{#int}Ldt=4.7fb^{-1}, #sqrt{s}=7TeV");
    else if(imode==4) pavetext.push_back("#intLdt=2.05-4.8fb^{-1}, #sqrt{s}=7TeV");
//     pavetext.push_back("June 4th, 2012");
    pavetext.push_back("#scale[0.6]{#int}Ldt=3.23fb^{-1}, #sqrt{s}=8TeV");
    if(option=="conv") pavetext.push_back("Converted Categories");
    else if(option=="unconv") pavetext.push_back("Unconverted Categories");
    else if(option=="vbf") pavetext.push_back("VBF Category");
    else if(option=="highpt") pavetext.push_back("High P_{Tt} Categories");
    else if(option=="lowpt") pavetext.push_back("Low P_{Tt} + Bad Categories");
    else if(option=="good") pavetext.push_back("Good #eta Categories");
    else if(option=="rest") pavetext.push_back("Rest #eta Categories");
    
    TPaveText* text=CreatePaveText(x1,y2-0.3,x1+0.4,y2-0.01,pavetext,0.05);

    cv->cd();

    likelihd_limit->Draw("A");
    likelihd_limit->GetXaxis()->SetTitleSize(0.05);
    likelihd_limit->GetXaxis()->SetTitleOffset(1.3);
    likelihd_limit->GetYaxis()->SetLabelSize(0.045);
    likelihd_limit->GetYaxis()->SetTitleSize(0.05);
    if(imode==0){
      likelihd_limit->GetXaxis()->SetRangeUser(109,151);
      likelihd_limit->SetMaximum(10);
    }
    if(imode==4){likelihd_limit->SetMinimum(1e-1);cv->SetLogy();}

    legend->Draw();

    text->Draw("same");
    DrawConstantLine(cv,1,mass[0],nmass[0],kBlue);
    TLine *line2 = new TLine(280,0.2,280,3.);
    line2->SetLineStyle(2);
    line2->SetLineColor(kBlue);
    line2->SetLineWidth(2);
    line2->Draw();
    PrintCanvas(cv,Form("fig/limit_plot/%s/limitplot",jobname.Data()));
    fout.close();
  }// 
  //======================================================================================
  //======================================================================================
  if(Opt["PVALUE"]){
    if(argc<4){
      cout<<"Usage: ./Pvalue pvalue <jobname> <imode> <option>"<<endl;
      return 0;
    }

    TString jobname=argc>2 ? argv[2] : "nominal";
    int imode=argc>3 ? atoi(argv[3]) : 1;
    TString option=argv[4];
    option.ToLower();
//     bool m_uncap=option.Contains("uncap");
    bool m_uncap=true;
    bool m_logy=true;
    string fileName[5];
    fileName[0]=jobname.Data();
    int nsample=1;
    TString type=(imode==1)?"llvv":"llqq";
    double mass[5][200];
    double pvalue_obs[5][200];
    double pvalue_exp[5][200];

    TCanvas *cv = CreateCanvas("canvas", "",1024,768);
    int nmass[5];
    vector<TString> tag;
    tag.push_back("(2012)");
    tag.push_back("(combined)");
    vector<int> temp;
    if(imode==0){
      type="";
      nsample=1;
      for(int Mass=1100;Mass<=1400;Mass+=5) temp.push_back(Mass);
      for(int Mass=1400;Mass<=1500;Mass+=10) temp.push_back(Mass);
    }
    else return -1;

    nmass[0]=temp.size();
    for(int i=0;i<nmass[0];i++) mass[0][i]=temp[i];
    system(Form("mkdir -vp fig/limit_plot/%s",jobname.Data()));

    for(int jj=0;jj<nsample;jj++){
      ofstream fout(Form("fig/limit_plot/%s/pvalue.txt",jobname.Data()),ios::out);
      double maxsig=0;
      double maxmass=0;
      for(int idx=0;idx<nmass[jj];idx++){
	TString fileName_obs="pvalue/"+type+"/"+jobname+"/"+Form("%d_obs.txt",(int)mass[jj][idx]);
	cout<<"Opening file "<<fileName_obs.Data()<<endl;
	ifstream fin_obs(fileName_obs.Data(),ios::in);
	if(!fin_obs) continue;
	ifstream fin_exp("pvalue/"+type+"/"+jobname+"/"+Form("%d_exp.txt",(int)mass[jj][idx]),ios::in);
	if(!fin_exp) continue;
	double temp,qmu,muhat;

	fin_obs>>temp>>pvalue_obs[jj][idx]>>qmu>>muhat; 
	if(m_uncap)  pvalue_obs[jj][idx]=UncapP0(qmu,muhat);
	if(fabs(temp-mass[jj][idx])>epsilon) return -1;

	fin_exp>>temp>>pvalue_exp[jj][idx]>>qmu>>muhat;
	if(m_uncap) pvalue_exp[jj][idx]=UncapP0(qmu,muhat);
	if(fabs(temp-mass[jj][idx])>epsilon) return -1;

	fin_obs.close();
	fin_exp.close();
	mass[jj][idx]/=10;
	double sig=PValueToSignificance(pvalue_obs[jj][idx]);
	if(sig>maxsig) {maxsig=sig;maxmass=mass[jj][idx];}
	fout<<mass[jj][idx]<<" "<<pvalue_obs[jj][idx]<<" "<<pvalue_exp[jj][idx]<<" "<<sig<<endl;
      }
      fout<<"Max sig: "<<maxmass<<" GeV, "<<maxsig<<" sigma"<<endl;
      fout.close();
    }

    TGraph *plot_pvalue_obs[5],*plot_pvalue_exp[5];
    TMultiGraph *plot_pvalue = new TMultiGraph("exclusionlimit_p","p_{0};m_{H} [GeV];Local p_{0}");
    TList *leglist=new TList();
    vector<TString> legtext;
    vector<TString> legopt;

    for(int jj=0;jj<nsample;jj++){	// WSN...
      plot_pvalue_obs[jj]=new TGraph(nmass[jj],mass[jj],pvalue_obs[jj]);
      plot_pvalue_obs[jj]->SetLineWidth(3);
      plot_pvalue->Add(plot_pvalue_obs[jj],"L");
      leglist->Add(plot_pvalue_obs[jj]);legtext.push_back("Observed p_{0} "+tag[jj]);legopt.push_back("L");

      plot_pvalue_exp[jj]=new TGraph(nmass[jj],mass[jj],pvalue_exp[jj]);
      plot_pvalue_exp[jj]->SetLineWidth(3);
      plot_pvalue_exp[jj]->SetLineStyle(2);
      plot_pvalue->Add(plot_pvalue_exp[jj],"L");
      leglist->Add(plot_pvalue_exp[jj]);legtext.push_back("Expected SM p_{0} "+tag[jj]);legopt.push_back("L");
    }
    double x1,y1,x2,y2;
    GetX1Y1X2Y2(cv,x1,y1,x2,y2);
    TLegend* legend=CreateLegend(x2-0.5,y2-0.2,x2,y2-0.01,leglist,legtext,legopt,0.045);

    vector<TString> pavetext;
    pavetext.push_back("#bf{#it{ATLAS}} Internal");
    // It is ATLAS now. 2011-08-12 4:48 p.m.
//     pavetext.push_back("#bf{#it{ATLAS}}");
    if(imode==0){
      pavetext.push_back("H#rightarrow#gamma#gamma");
    }
    else if(imode==1) pavetext.push_back("H#rightarrowZZ#rightarrowll#nu#nu");
    else if(imode==2) pavetext.push_back("H#rightarrowZZ#rightarrowllqq");
    else if(imode==4) pavetext.push_back("H#rightarrowZZ");

    if(imode==1||imode==2) pavetext.push_back("#intLdt=4.7fb^{-1}, #sqrt{s}=7TeV");
    else if(imode==4) pavetext.push_back("#intLdt=2.05-4.8fb^{-1}, #sqrt{s}=7TeV");
//     pavetext.push_back("June 4th, 2012");
//     TPaveText* text=CreatePaveText(x2-0.3,y1+0.05,x2,y1+0.2,pavetext,0.045);
    TPaveText* text=CreatePaveText(x1+0.01,y2-0.2,x1+0.4,y2-0.02,pavetext,0.045);
//     pavetext.push_back("#intLdt=2.05fb^{-1}, #sqrt{s}=7TeV");
    cv->cd();
    TPaveText* combination=new TPaveText();

    if(option=="conv") combination->AddText("Converted Categories");
    else if(option=="unconv") combination->AddText("Unconverted Categories");
    else if(option=="vbf") combination->AddText("VBF Category");
    else if(option=="highpt") combination->AddText("High P_{Tt} Categories");
    else if(option=="lowpt") combination->AddText("Low P_{Tt} + Bad Categories");
    else if(option=="good") combination->AddText("Good #eta Categories");
    else if(option=="rest") combination->AddText("Rest #eta Categories");
    combination->AddText("#scale[0.6]{#int}Ldt=3.23fb^{-1}, #sqrt{s}=8TeV");
    combination->AddText("2012 Data");
    combination->SetX1NDC(x2-0.4);
    combination->SetX2NDC(x2-0.02);
    combination->SetY1NDC(y1+0.3);
    combination->SetY2NDC(y1+0.01);
    combination->SetTextSize(0.05);
    combination->SetFillColor(0);
    combination->SetFillStyle(0);
    combination->SetLineColor(0);
    combination->SetLineWidth(0);
    combination->SetBorderSize(0);

    plot_pvalue->Draw("A");
    plot_pvalue->GetXaxis()->SetTitleSize(0.05);
    plot_pvalue->GetXaxis()->SetTitleOffset(1.3);
    plot_pvalue->GetYaxis()->SetLabelSize(0.045);
    plot_pvalue->GetYaxis()->SetTitleSize(0.05);
    plot_pvalue->SetMaximum(50);
    if(m_uncap&&!m_logy) plot_pvalue->SetMaximum(1.5);
    plot_pvalue->SetMinimum(1e-5);
    plot_pvalue->GetXaxis()->SetRangeUser(109,151);

    legend->Draw();
    if(m_uncap){
      if(!m_logy){
	TLatex l1sigma;
	l1sigma.SetTextFont(42);
	l1sigma.DrawLatex(109.5,SIG1+0.015,"+1#sigma");
	TLatex l2sigma;
	l2sigma.SetTextFont(42);
	l2sigma.DrawLatex(109.5,SIG2+0.015,"+2#sigma");

	TLatex l3sigma;
	l3sigma.SetTextFont(42);
	l3sigma.DrawLatex(109.5,1-SIG1+0.015,"-1#sigma");
	TLatex l4sigma;
	l4sigma.SetTextFont(42);
	l4sigma.DrawLatex(109.5,1-SIG2+0.015,"-2#sigma");
      }
      else{
	TLatex l1sigma;
	l1sigma.SetTextFont(42);
	l1sigma.DrawLatex(109.5,0.17,"+1#sigma");
	TLatex l2sigma;
	l2sigma.SetTextFont(42);
	l2sigma.DrawLatex(109.5,0.025,"+2#sigma");

	TLatex l3sigma;
	l3sigma.SetTextFont(42);
	l3sigma.DrawLatex(109.5,0.00148,"+3#sigma");
	TLatex l4sigma;
	l4sigma.SetTextFont(42);
	l4sigma.DrawLatex(109.5,0.000045,"+4#sigma");
	TLatex l5sigma;
	l5sigma.SetTextFont(42);
	l5sigma.DrawLatex(109.5,1-SIG1+0.015,"-1#sigma");
      }
    }
    else{
      TLatex l1sigma;
      l1sigma.SetTextFont(42);
      l1sigma.DrawLatex(109.5,0.17,"1#sigma");
      TLatex l2sigma;
      l2sigma.SetTextFont(42);
      l2sigma.DrawLatex(109.5,0.025,"2#sigma");

      TLatex l3sigma;
      l3sigma.SetTextFont(42);
      l3sigma.DrawLatex(109.5,0.00148,"3#sigma");
      TLatex l4sigma;
      l4sigma.SetTextFont(42);
      l4sigma.DrawLatex(109.5,0.000045,"4#sigma");
    }

    text->Draw("same");
    combination->Draw("same");

    if(m_uncap){
      DrawConstantLine(cv,SIG1,mass[0],nmass[0],2); 
      DrawConstantLine(cv,SIG2,mass[0],nmass[0],2);
      DrawConstantLine(cv,1-SIG1,mass[0],nmass[0],2);
      if(!m_logy) DrawConstantLine(cv,1-SIG2,mass[0],nmass[0],2);
      else{
	DrawConstantLine(cv,SIG3,mass[0],nmass[0],2);
	DrawConstantLine(cv,SIG4,mass[0],nmass[0],2);
      }	
      DrawConstantLine(cv,0.5,mass[0],nmass[0],kOrange);
    }
    else{
      DrawConstantLine(cv,SIG1,mass[0],nmass[0]); 
      DrawConstantLine(cv,SIG2,mass[0],nmass[0]);
      DrawConstantLine(cv,SIG3,mass[0],nmass[0]);
      DrawConstantLine(cv,SIG4,mass[0],nmass[0]);
    }

    TString outputName=Form("fig/limit_plot/%s/pvalue",jobname.Data());
    if(m_uncap) outputName+="_uncap";
    if(m_logy) outputName+="_logy";
    if(m_logy) cv->SetLogy();
    PrintCanvas(cv,outputName);

  }
  //======================================================================================
}
