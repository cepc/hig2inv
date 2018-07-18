#!/usr/bin/env python
"""
SIgnal And Background Comparison
"""

__author__='JING Maoqiang <jingmq@ihep.ac.cn>'
__copyright__='Copyright (c) JING Maoqiang'
__created__='[2018-07-09]'

import sys
import os
import math
import ROOT

ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetPadColor(0)
ROOT.gStyle.SetCanvasColor(0)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetLegendFont(42)

def main():

	args=sys.argv[1:]
	if len(args)<4:
		print "ERROR: Please Enter FOUR Parameters!!!!!"
		sys.exit()

	sigfile=args[0]
	bkgfile=args[1]
	bkgname=str(args[2])
	cut_num=int(args[3])

	f_sig=ROOT.TFile(sigfile)
	t_sig=f_sig.Get('MCPart')
	sig_entries=t_sig.GetEntriesFast()

	f_bkg=ROOT.TFile(bkgfile)
	t_bkg=f_bkg.Get('MCPart')
	bkg_entries=t_bkg.GetEntriesFast()

	canvas = ROOT.TCanvas('','',800,600)
	canvas.Divide(1,1)
	set_canvas_style(canvas)

	N_sig=0.
	N_bkg=0.
	plot(t_sig,t_bkg,sig_entries,bkg_entries,canvas,cut_num,bkgname,sigfile,bkgfile,N_sig,N_bkg)

def set_canvas_style(canvas):
	canvas.SetFillColor(0)
	canvas.SetFrameFillColor(0)
	canvas.SetLeftMargin(0.15)
	canvas.SetRightMargin(0.15)
	canvas.SetTopMargin(0.1)
	canvas.SetBottomMargin(0.15)
	# canvas.SetLogy()

def plot(t_sig,t_bkg,sig_entries,bkg_entries,canvas,cut_num,bkgname,sigfile,bkgfile,N_sig,N_bkg):
	if cut_num==0:
		h_sig=ROOT.TH1F("Signal Distribution","",5,0,5)
		h_bkg=ROOT.TH1F("Background Distribution","",5,0,5)
		for i in xrange(sig_entries):
			t_sig.GetEntry(i)
			h_sig.Fill((t_sig.m_n_leptonm+t_sig.m_n_leptonp))
			N_sig=N_sig+1
		for i in xrange(bkg_entries):
			t_bkg.GetEntry(i)
			h_bkg.Fill((t_bkg.m_n_leptonm+t_bkg.m_n_leptonp))
			N_bkg=N_bkg+1
	if cut_num==1:
		h_sig=ROOT.TH1F("Signal Distribution","",5,0,5)
		h_bkg=ROOT.TH1F("Background Distribution","",5,0,5)
		for i in xrange(sig_entries):
			t_sig.GetEntry(i)
			cut1_sig=judge_cut(t_sig,i,1)
			if (cut1_sig):
				h_sig.Fill(t_sig.m_n_gamma)
				N_sig=N_sig+1
		for i in xrange(bkg_entries):
			t_bkg.GetEntry(i)
			cut1_bkg=judge_cut(t_bkg,i,1)
			if (cut1_bkg):
				h_bkg.Fill(t_bkg.m_n_gamma)
				N_bkg=N_bkg+1
	if cut_num==2:
		h_sig=ROOT.TH1F("Signal Distribution","",100,0,100)
		h_bkg=ROOT.TH1F("Background Distribution","",100,0,100)
		for i in xrange(sig_entries):
			t_sig.GetEntry(i)
			cut1_sig=judge_cut(t_sig,i,1)
			cut2_sig=judge_cut(t_sig,i,2)
			if (cut1_sig and cut2_sig):
				h_sig.Fill(t_sig.m_pt_dilepton)
				N_sig=N_sig+1
		for i in xrange(bkg_entries):
			t_bkg.GetEntry(i)
			cut1_bkg=judge_cut(t_bkg,i,1)
			cut2_bkg=judge_cut(t_bkg,i,2)
			if (cut1_bkg and cut2_bkg):
				h_bkg.Fill(t_bkg.m_pt_dilepton)
				N_bkg=N_bkg+1
	if cut_num==3:
		h_sig=ROOT.TH1F("Signal Distribution","",100,0,100)
		h_bkg=ROOT.TH1F("Background Distribution","",100,0,100)
		for i in xrange(sig_entries):
			t_sig.GetEntry(i)
			cut1_sig=judge_cut(t_sig,i,1)
			cut2_sig=judge_cut(t_sig,i,2)
			cut3_sig=judge_cut(t_sig,i,3)
			if (cut1_sig and cut2_sig and cut3_sig):
				h_sig.Fill(abs(t_sig.m_p_dilepton[2]))
				N_sig=N_sig+1
		for i in xrange(bkg_entries):
			t_bkg.GetEntry(i)
			cut1_bkg=judge_cut(t_bkg,i,1)
			cut2_bkg=judge_cut(t_bkg,i,2)
			cut3_bkg=judge_cut(t_bkg,i,3)
			if (cut1_bkg and cut2_bkg and cut3_bkg):
				h_bkg.Fill(abs(t_bkg.m_p_dilepton[2]))
				N_bkg=N_bkg+1
	if cut_num==4:
		h_sig=ROOT.TH1F("Signal Distribution","",100,0,1)
		h_bkg=ROOT.TH1F("Background Distribution","",100,0,1)
		for i in xrange(sig_entries):
			t_sig.GetEntry(i)
			cut1_sig=judge_cut(t_sig,i,1)
			cut2_sig=judge_cut(t_sig,i,2)
			cut3_sig=judge_cut(t_sig,i,3)
			cut4_sig=judge_cut(t_sig,i,4)
			if (cut1_sig and cut2_sig and cut3_sig and cut4_sig):
				costheta_sig=calculate_costheta(t_sig,i)
				h_sig.Fill(abs(costheta_sig))
				N_sig=N_sig+1
		for i in xrange(bkg_entries):
			t_bkg.GetEntry(i)
			cut1_bkg=judge_cut(t_bkg,i,1)
			cut2_bkg=judge_cut(t_bkg,i,2)
			cut3_bkg=judge_cut(t_bkg,i,3)
			cut4_bkg=judge_cut(t_bkg,i,4)
			if (cut1_bkg and cut2_bkg and cut3_bkg and cut4_bkg):
				costheta_bkg=calculate_costheta(t_bkg,i)
				h_bkg.Fill(abs(costheta_bkg))
				N_bkg=N_bkg+1
	if cut_num==5:
		h_sig=ROOT.TH1F("Signal Distribution","",100,80,130)
		h_bkg=ROOT.TH1F("Background Distribution","",100,80,130)
		for i in xrange(sig_entries):
			t_sig.GetEntry(i)
			cut1_sig=judge_cut(t_sig,i,1)
			cut2_sig=judge_cut(t_sig,i,2)
			cut3_sig=judge_cut(t_sig,i,3)
			cut4_sig=judge_cut(t_sig,i,4)
			cut5_sig=judge_cut(t_sig,i,5)
			if (cut1_sig and cut2_sig and cut3_sig and cut4_sig and cut5_sig):
				h_sig.Fill(t_sig.m_energy_visible)
				N_sig=N_sig+1
		for i in xrange(bkg_entries):
			t_bkg.GetEntry(i)
			cut1_bkg=judge_cut(t_bkg,i,1)
			cut2_bkg=judge_cut(t_bkg,i,2)
			cut3_bkg=judge_cut(t_bkg,i,3)
			cut4_bkg=judge_cut(t_bkg,i,4)
			cut5_bkg=judge_cut(t_bkg,i,5)
			if (cut1_bkg and cut2_bkg and cut3_bkg and cut4_bkg and cut5_bkg):
				h_bkg.Fill(t_bkg.m_energy_visible)
				N_bkg=N_bkg+1
	if cut_num==6:
		h_sig=ROOT.TH1F("Signal Distribution","",100,70,110)
		h_bkg=ROOT.TH1F("Background Distribution","",100,70,110)
		for i in xrange(sig_entries):
			t_sig.GetEntry(i)
			cut1_sig=judge_cut(t_sig,i,1)
			cut2_sig=judge_cut(t_sig,i,2)
			cut3_sig=judge_cut(t_sig,i,3)
			cut4_sig=judge_cut(t_sig,i,4)
			cut5_sig=judge_cut(t_sig,i,5)
			cut6_sig=judge_cut(t_sig,i,6)
			if (cut1_sig and cut2_sig and cut3_sig and cut4_sig and cut5_sig and cut6_sig):
				h_sig.Fill(t_sig.m_m_visible)
				N_sig=N_sig+1
		for i in xrange(bkg_entries):
			t_bkg.GetEntry(i)
			cut1_bkg=judge_cut(t_bkg,i,1)
			cut2_bkg=judge_cut(t_bkg,i,2)
			cut3_bkg=judge_cut(t_bkg,i,3)
			cut4_bkg=judge_cut(t_bkg,i,4)
			cut5_bkg=judge_cut(t_bkg,i,5)
			cut6_bkg=judge_cut(t_bkg,i,6)
			if (cut1_bkg and cut2_bkg and cut3_bkg and cut4_bkg and cut5_bkg and cut6_bkg):
				h_bkg.Fill(t_bkg.m_m_visible)
				N_bkg=N_bkg+1
	if cut_num==7:
		h_sig=ROOT.TH1F("Signal Distribution","",100,100,170)
		h_bkg=ROOT.TH1F("Background Distribution","",100,100,170)
		for i in xrange(sig_entries):
			t_sig.GetEntry(i)
			cut1_sig=judge_cut(t_sig,i,1)
			cut2_sig=judge_cut(t_sig,i,2)
			cut3_sig=judge_cut(t_sig,i,3)
			cut4_sig=judge_cut(t_sig,i,4)
			cut5_sig=judge_cut(t_sig,i,5)
			cut6_sig=judge_cut(t_sig,i,6)
			cut7_sig=judge_cut(t_sig,i,7)
			if (cut1_sig and cut2_sig and cut3_sig and cut4_sig and cut5_sig and cut6_sig and cut7_sig):
				h_sig.Fill(t_sig.m_m_recoil)
				N_sig=N_sig+1
		for i in xrange(bkg_entries):
			t_bkg.GetEntry(i)
			cut1_bkg=judge_cut(t_bkg,i,1)
			cut2_bkg=judge_cut(t_bkg,i,2)
			cut3_bkg=judge_cut(t_bkg,i,3)
			cut4_bkg=judge_cut(t_bkg,i,4)
			cut5_bkg=judge_cut(t_bkg,i,5)
			cut6_bkg=judge_cut(t_bkg,i,6)
			cut7_bkg=judge_cut(t_bkg,i,7)
			if (cut1_bkg and cut2_bkg and cut3_bkg and cut4_bkg and cut5_bkg and cut6_bkg and cut7_bkg):
				h_bkg.Fill(t_bkg.m_m_recoil)
				N_bkg=N_bkg+1
	if cut_num==8:
		h_sig=ROOT.TH1F("Signal Distribution","",100,120,150)
		h_bkg=ROOT.TH1F("Background Distribution","",100,120,150)
		for i in xrange(sig_entries):
			t_sig.GetEntry(i)
			cut1_sig=judge_cut(t_sig,i,1)
			cut2_sig=judge_cut(t_sig,i,2)
			cut3_sig=judge_cut(t_sig,i,3)
			cut4_sig=judge_cut(t_sig,i,4)
			cut5_sig=judge_cut(t_sig,i,5)
			cut6_sig=judge_cut(t_sig,i,6)
			cut7_sig=judge_cut(t_sig,i,7)
			cut8_sig=judge_cut(t_sig,i,8)
			if (cut1_sig and cut2_sig and cut3_sig and cut4_sig and cut5_sig and cut6_sig and cut7_sig and cut8_sig):
				h_sig.Fill(t_sig.m_m_recoil)
				N_sig=N_sig+1
		for i in xrange(bkg_entries):
			t_bkg.GetEntry(i)
			cut1_bkg=judge_cut(t_bkg,i,1)
			cut2_bkg=judge_cut(t_bkg,i,2)
			cut3_bkg=judge_cut(t_bkg,i,3)
			cut4_bkg=judge_cut(t_bkg,i,4)
			cut5_bkg=judge_cut(t_bkg,i,5)
			cut6_bkg=judge_cut(t_bkg,i,6)
			cut7_bkg=judge_cut(t_bkg,i,7)
			cut8_bkg=judge_cut(t_bkg,i,8)
			if (cut1_bkg and cut2_bkg and cut3_bkg and cut4_bkg and cut5_bkg and cut6_bkg and cut7_bkg and cut8_bkg):
				h_bkg.Fill(t_bkg.m_m_recoil)
				N_bkg=N_bkg+1
	
	h_sig.Scale(bkg_entries/sig_entries)
	cut_name,x_name_file=set_histo_style(h_sig,h_bkg,cut_num)
	h_sig.Draw('')
	h_bkg.Draw('same')
	legend=ROOT.TLegend(0.63, 0.68, 0.84, 0.87)
	legend.AddEntry(h_sig,'Signal: e^{+}e^{-}->ZH,Z->#mu^{+}#mu^{-},H->Invisible')
	legend.AddEntry(h_bkg,'Background: '+bkgname)
	legend.SetBorderSize(0)
	legend.SetFillColor(0)
	legend.Draw()
	canvas.Print('../figs/cut_'+bkgname+'_'+x_name_file+'.eps')
	
	print '################################'
	print 'Signal File: %s'%(sigfile)
	print 'Background File: %s'%(bkgfile)
	print 'Cut Name: %s'%cut_name
	print 'Background Number: %s'%str(N_bkg)
	print 'Singal Number: %s'%str(N_sig)
	print 'Background over Signal: %s'%str(N_bkg/N_sig)
	print '################################'

def set_histo_style(h_sig,h_bkg,cut_num):
	if cut_num==0:
		x_name='N_{#mu}'
		x_name_file='N_mu'
		cut_name='none'
	if cut_num==1:
		x_name='N_{#gamma}'
		x_name_file='N_gamma'
		cut_name='N_{#mu}'
	if cut_num==2:
		x_name='P_{t}^{#mu^{+}#mu^{-}}'
		x_name_file='P_t_mumu'
		cut_name='N_{charged}'
	if cut_num==3:
		x_name='|P_{z}^{#mu^{+}#mu^{-}}|'
		x_name_file='abs_P_z_mu_mu'
		cut_name='P_{t}^{#mu^{+}#mu^{-}}'
	if cut_num==4:
		x_name='|cos#theta|'
		x_name_file='abs_costheta'
		cut_name='|P_{z}^{#mu^{+}#mu^{-}}|'
	if cut_num==5:
		x_name='Visible Energy'
		x_name_file='Visible Energy'
		cut_name='|cos#theta|'
	if cut_num==6:
		x_name='M_{#mu^{+}#mu^{-}}'
		x_name_file='M_mumu'
		cut_name='Visible Energy'
	if cut_num==7:
		x_name='M_{Recoil}'
		x_name_file='M_Recoil'
		cut_name='M_{#mu^{+}#mu^{-}}'
	if cut_num==8:
		x_name='M_{Recoil}'
		x_name_file='With_M_Recoil_Window'
		cut_name='M_{Recoil}'
	h_sig.GetXaxis().SetTitle(x_name)
	h_sig.GetXaxis().CenterTitle()
	h_sig.GetXaxis().SetTitleOffset(1.5)
	h_sig.GetYaxis().SetTitle('Events')
	h_sig.GetYaxis().CenterTitle()
	h_sig.GetYaxis().SetTitleOffset(1.5)
	h_sig.SetLineWidth(1)
	h_sig.SetLineColor(1)
	h_bkg.SetLineWidth(1)
	h_bkg.SetLineColor(2)

	return cut_name,x_name_file

def judge_cut(t,i,cut_num):
	t.GetEntry(i)
	cut_flag=0
	if cut_num==1:
		if ((t.m_n_leptonm+t.m_n_leptonp)<3):
			cut_flag=1
	if cut_num==2:
		if (t.m_n_gamma<=1):
			cut_flag=1
	if cut_num==3:
		if (t.m_pt_dilepton>30 and t.m_pt_dilepton<60):
			cut_flag=1
	if cut_num==4:
		if (abs(t.m_p_dilepton[2])<55):
			cut_flag=1
	costheta=calculate_costheta(t,i)
	if cut_num==5:
		if (abs(costheta)<0.6):
			cut_flag=1
	if cut_num==6:
		if (t.m_energy_visible<107 and t.m_energy_visible>90):
			cut_flag=1
	if cut_num==7:
		if (t.m_m_visible<97 and t.m_m_visible>83):
			cut_flag=1
	if cut_num==8:
		if (t.m_m_recoil>120 and t.m_m_recoil<150):
			cut_flag=1
	return cut_flag

def calculate_costheta(t,i):
	t.GetEntry(i)
	TotalP=math.sqrt(abs(t.m_p_dilepton[3]*t.m_p_dilepton[3]-t.m_p_dilepton[0]*t.m_p_dilepton[0]-t.m_p_dilepton[1]*t.m_p_dilepton[1]-t.m_p_dilepton[2]*t.m_p_dilepton[2]))
	TotalPz=t.m_p_dilepton[2]
	if TotalP!=0:
		costheta=TotalPz/TotalP
	else:
		costheta=0
	return costheta

if __name__ == '__main__':
	main()
