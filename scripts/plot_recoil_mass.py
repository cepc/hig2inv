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

fsig=ROOT.TFile('../presel/signal.root')
tsig=fsig.Get('MCPart')

fbkg=ROOT.TFile('../presel/bkg.root')
tbkg=fbkg.Get('MCPart')

myc=ROOT.TCanvas('myc','myc',200,10,500,300)
myc.Divide(1,1)
myc.cd(1)

hsig=ROOT.TH1D('','',80,80,160)
hbkg=ROOT.TH1D('','',80,80,160)

for i in xrange(tsig.GetEntries()):
	tsig.GetEntry(i)
	hsig.Fill(tsig.Mass_Recoil)

for i in xrange(tbkg.GetEntries()):
	tbkg.GetEntry(i)
	hbkg.Fill(tbkg.Mass_Recoil)

hsig.GetXaxis().SetTitle('M_{Recoil}(GeV/#it{c}^{2})')
hsig.GetXaxis().CenterTitle()
hsig.GetXaxis().SetRangeUser(120,150)
hsig.GetYaxis().SetTitle('Events')
hsig.GetYaxis().CenterTitle()
hsig.SetLineWidth(1)
hsig.SetLineColor(46)
hbkg.SetLineColor(38)
hsig.Draw('E1')
hbkg.Draw('same')

legend=ROOT.TLegend(0.65,.75,0.86,0.86)
legend.AddEntry(hsig,'Signal Sample')
legend.AddEntry(hbkg,'Background Sample')
legend.SetLineColor(1)
legend.SetLineWidth(1)
legend.SetBorderSize(1)
legend.Draw('same')

myc.SaveAs('../figs/Mass_Recoil.pdf')
