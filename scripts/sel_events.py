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
from array import array

args=sys.argv[1:]

if (len(args)<2):
	print 'input error'
	exit(0)

infile=args[0]
outfile=args[1]

fin=ROOT.TFile(infile)
t=fin.Get('MCPart')

Mass_Recoil=array('d',[0])

fout=ROOT.TFile(outfile,'RECREATE')
t_out=ROOT.TTree('MCPart','MCPart')
t_out.Branch('Mass_Recoil',Mass_Recoil,'Mass_Recoil/D')

for ientry in xrange(t.GetEntries()):
	t.GetEntry(ientry)
	if ((t.m_n_leptonp+t.m_n_leptonm)<2|(t.m_n_leptonp+t.m_n_leptonm))>3:
		continue
	if (t.m_n_charged>3):
		continue
	if (t.m_n_gamma>1):
		continue
	if (t.m_pt_dilepton<=10 or t.m_pt_dilepton>=70):
		continue
	if (abs(t.m_p_dilepton[2])>=60):
		continue
	if (abs(math.cos(t.m_angle_dilepton))>=0.8):
		continue
	if (t.m_m_visble<=70 or t.m_m_visble>=100):
		continue
	if (t.m_energy_visble<=90 or t.m_energy_visble>=120):
		continue
	Mass_Recoil[0]=t.m_m_recoil
	t_out.Fill()

fout.Write()
fout.Close()
