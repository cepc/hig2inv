void fitBDT()
{
   gStyle->SetOptTitle(0);
   gStyle->SetPadLeftMargin(0.17);
   gStyle->SetPadBottomMargin(0.17);

   gSystem->Load("libRooFit");
   using namespace RooFit;
   TString rootfile;
   rootfile = "./run/total/bkg_add_sig_BDT.root";
    
   TString  epsname;  
   epsname="./fig/fithiggs.pdf";
   
   TCanvas *myC = new TCanvas("myC", "", 10,10,800,600);
   
   myC->Divide(1,1);
   myC->cd(1); 
   
   TFile *f = new TFile(rootfile);
   TTree *t = (TTree *)f->Get("tree");
   
   Float_t m_m_recoil;
   t->SetBranchAddress("m_m_recoil", &m_m_recoil);
   
   TH1F* histData=new TH1F("Recoil mass of Z boson","Recoil mass of Z boson",19,120,130);
   histData->SetLineColor(2);
   histData->SetLineWidth(2);
   
   for(int i=0; i<t->GetEntries(); i++)
   { 
      t->GetEntry(i);
      histData->Fill(m_m_recoil);
   }
   
   
   RooRealVar x("m_m_recoil","m_m_recoil",120,130);

   //Signal: CBshape function
   RooRealVar mean("mean_CB","mean_CB",125.2,125.0,125.4);
   RooRealVar sigma("sgm_CB","sgm_CB",0.18,0.16,0.19);
   RooRealVar alpha("alpha_CB","alpha_CB",2,1,4);
   RooRealVar n("n","n",4,2,6);
   RooCBShape cb("sig","sig p.d.f.",x,mean,sigma,alpha,n);

   //Siganl: B-W function 
   //RooRealVar mean1("mean1","Mean of Gaussian",125,120,130);
   //RooRealVar sigma1("sigma1","Width of Gaussian",10,0,30) ;
   //RooBreitWigner  breithtwigner2("breithtwigner2","breithtwigner2",x,mean1,sigma1);
   
   //Signal: Gauss function
   RooRealVar mean0("mean0", "mean0", 125.2, 125.0, 125.4);
   RooRealVar sigma0("sigma0", "sigma0",0.09,0.08,0.10);
   RooGaussian gauss0("gauss0"," gauss fit ",x, mean0, sigma0);
 
   //Background: Chebychev and Polynomial function
   //RooRealVar co1("co1","coefficienct #1",0,-999., 999.);
   //RooRealVar co2("co2","coefficienct #2",0,-999., 999.);
   //RooRealVar co3("co3","coefficienct #3",0,-999., 999.);
   //RooRealVar co4("co4","coefficienct #4",0,-999., 999.);
   //RooRealVar co5("co5","coefficienct #5",0,-999., 999.);
   //RooChebychev bkg("bkg", "bkg p.d.f", x, RooArgList(co1));
   //RooChebychev bkg("bkg", "bkg p.d.f", x, RooArgList(co1,co2));
   //RooChebychev bkg("bkg", "bkg p.d.f", x, RooArgList(co1,co2,co3));
   //RooPolynomial bkg("bkg", "bkg p.d.f", x, RooArgList(co1));
   //RooPolynomial bkg("bkg", "bkg p.d.f", x, RooArgList(co1,co2));
   //RooPolynomial bkg("bkg", "bkg p.d.f", x, RooArgList(co1,co2,co3));
   //RooPolynomial bkg("bkg", "bkg p.d.f", x, RooArgList(co1,co2,co3,co4));

   RooRealVar mean1("mean1", "mean1", 125.0, 124.9, 125.2);
   RooRealVar sigma1("sigma1", "sigma1",0.90,0.89,0.92);
   RooGaussian gauss1("gauss1"," gauss fit ",x, mean1, sigma1);

   Double_t mentr = (Double_t)histData->GetEntries();
   Double_t msig = mentr;
   Double_t mbkg = mentr;

   RooRealVar nsig("nsig", "signal elow number",0, msig);
   RooRealVar nbkg("nbkg", "background number",0, mbkg);
  // RooRealVar nbkg("nbkg", "background number",0, mbkg);
   //RooAddPdf sum("sum", "sum", RooArgList(breithtwigner2,bkg), RooArgList(nsig,nbkg));
   //RooAddPdf sum("sum", "sum", RooArgList(gauss0,bkg), RooArgList(nsig,nbkg));
   RooAddPdf sum("sum", "sum", RooArgList(cb,gauss1), RooArgList(nsig,nbkg));
   //RooAddPdf sum("sum", "sum", RooArgList(cb,bkg), RooArgList(nsig,nbkg));
   
   RooDataHist data("data","dada",x,histData);
   
   sum.fitTo(data,Extended(kTRUE));
   RooPlot *xframe=x.frame();
   
   data.plotOn(xframe);
   sum.plotOn(xframe);
//   sum.plotOn(xframe,Components(cb),LineStyle(2), LineColor(2));
//   sum.plotOn(xframe,Components(gauss1),LineStyle(2), LineColor(3));
   //sum.plotOn(xframe,Components(cb),LineStyle(2), LineColor(2));
   //sum.plotOn(xframe,Components(bkg),LineStyle(2), LineColor(3));

   nsig.Print();
   nbkg.Print();

   TAxis *yaxis= xframe->GetYaxis();
   TAxis *xaxis= xframe->GetXaxis();

   xaxis->SetTitleFont(22);
   yaxis->SetTitleFont(22);
   xaxis->SetTitleOffset(1.2);
   yaxis->SetTitleOffset(1.2);
   xaxis->SetTitleSize(0.06);
   yaxis->SetTitleSize(0.06);
   xaxis->SetLabelSize(0.05);
   yaxis->SetLabelSize(0.05);
   xaxis->SetTitle("M_{Recoil}(GeV/c^{2})");
   yaxis->SetTitle("Events");
   xaxis->CenterTitle();
   yaxis->CenterTitle();
   xaxis->SetNdivisions(505);
   yaxis->SetNdivisions(505);
     
   xframe->Draw();
   myC->Print(epsname);  
 
}
