#!/usr/bin/env python
"""
Event Selection
"""

__author__='JING Maoqiang <jingmq@ihep.ac.cn>'
__copyright__='Copyright (c) JING Maoqiang'
__created__='[2018-04-22]'

import sys
import os
import math
import ROOT

ROOT.gStyle.SetOptStat(0)
# ROOT.gStyle.SetStatX(0.9)
# ROOT.gStyle.SetStatY(0.9)
# ROOT.gStyle.SetStatW(0.08)
# ROOT.gStyle.SetStatH(0.12)

def set_style(hist,size):
	color=38
	for i in xrange(size):
		if i==0:
			hist[i].GetXaxis().SetTitle('M_{Recoil}(GeV/#it{c}^{2})')
			hist[i].GetXaxis().CenterTitle()
			hist[i].GetXaxis().SetRangeUser(120,150)
			hist[i].GetYaxis().SetTitle('Events')
			hist[i].GetYaxis().CenterTitle()
			hist[i].SetLineWidth(1)
			hist[i].SetLineColor(46)
		else:
			hist[i].SetLineColor(color)
			color=color+1

def fill_events(fname,hist,size):
	for i in xrange(size):
		f=ROOT.TFile(fname[i])
		t=f.Get('MCPart')
		for j in xrange(t.GetEntries()):
			t.GetEntry(j)
			hist[i].Fill(t.Mass_Recoil)

def plot():
	fname=['../sel/signal.root','../sel/bhabha.root','../sel/e3e3.root','../sel/sw_l0tau.root']
	XS=[7.6,39.5,39.9,429.84,82.45,0.00,29.57,150.32,249.84,1066.36,17.55,205.41]
	eff=[0.28732,0.13215,0.0662,0.044]
	myc=ROOT.TCanvas('myc','myc',200,10,500,300)
	myc.Divide(1,1)
	myc.cd(1)
	
	hist=[]
	size=len(fname)
	for i in xrange(size):
		hist.append(ROOT.TH1D('','',80,80,160))
	
	fill_events(fname,hist,size)
	set_style(hist,size)

	for i in xrange(size):
		if i==0:
			hist[i].Scale(XS[i]*5000*eff[i]*0.00106)
			hist[i].Draw('E1')
		else:
			hist[i].Scale(XS[i]*5000*eff[i])
			hist[i].Draw('same')

	symbol=['Higgs->Invisible,Z->e^{+}e^{-}','e^{+}e^{-}->e^{+}e^{-}','e^{+}e^{-}->#tau^{+}#tau^{-}','sw_l0tau','sze_l0e','sze_l0mu','sze_l0nunu','sze_l0tau','szeorsw_l0l','zzbosons','zz_l0taumu','zzorww_l0tautau']
	legend=ROOT.TLegend(0.65,.75,0.86,0.86)
	for i in xrange(size):
		if i==0:
			legend.AddEntry(hist[i],symbol[i])
		else:
			legend.AddEntry(hist[i],symbol[i])
	legend.SetLineColor(1)
	legend.SetFillColor(0)
	legend.SetLineWidth(1)
	legend.SetBorderSize(1)
	legend.Draw('same')

	if not os.path.exists('../figs/'):
		os.makedirs('../figs/')
	myc.SaveAs('../figs/Mass_Recoil.pdf')

if __name__=='__main__':
	plot()
