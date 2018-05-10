#!/usr/bin/env python
"""
Event Selection
"""

__author__='JING Maoqiang <jingmq@ihep.ac.cn>'
__copyright__='Copyright (c) JING Maoqiang'
__created__='[2018-04-22]'

import os
import math
import ROOT
from array import array

def sel(infile,outfile):
	fin=ROOT.TFile(infile)
	t=fin.Get('MCPart')
	Mass_Recoil=array('d',[0])
	fout=ROOT.TFile(outfile,'RECREATE')
	t_out=ROOT.TTree('MCPart','MCPart')
	t_out.Branch('Mass_Recoil',Mass_Recoil,'Mass_Recoil/D')
	Count=0
	N=[0.,0.,0.,0.,0.,0.,0.,0.]
	for ientry in xrange(t.GetEntries()):
		t.GetEntry(ientry)
		if ((t.m_n_leptonp+t.m_n_leptonm)<2|(t.m_n_leptonp+t.m_n_leptonm))>3:
			continue
		N[0]+=1
		if (t.m_n_charged>3):
			continue
		N[1]+=1
		if (t.m_n_gamma>1):
			continue
		N[2]+=1
		if (t.m_pt_dilepton<=10 or t.m_pt_dilepton>=70):
			continue
		N[3]+=1
		if (abs(t.m_p_dilepton[2])>=60):
			continue
		N[4]+=1
		# if (abs(math.cos(t.m_angle_dilepton))>=0.8):
		if (abs(t.m_cos_Z)>=0.8):
			continue
		N[5]+=1
		if (t.m_m_visble<=70 or t.m_m_visble>=100):
			continue
		N[6]+=1
		if (t.m_energy_visble<=90 or t.m_energy_visble>=120):
			continue
		N[7]+=1
		Mass_Recoil[0]=t.m_m_recoil
		t_out.Fill()
	print '######Cut flow######'
	print 'InputFile: %s'%(infile)
	print 'Total Events: %d'%(t.GetEntries())
	for j in xrange(8):
		print 'Cut No.: %d'%(j+1)
		print 'Events: %d'%(N[j])
		print 'Efficiency: %f'%(N[j]/t.GetEntries())
	
	fout.Write()
	fout.Close()

if __name__ == '__main__':
	sel('../rawdata/signal_e1e1h_1.root','../presel/signal_e1e1h_1.root')
	sel('../data/bhabha.root','../presel/bhabha.root')
	sel('../data/e3e3.root','../presel/e3e3.root')
	sel('../data/sze_l0mu.root','../presel/sze_l0mu.root')
	sel('../data/sze_l0nunu.root','../presel/sze_l0nunu.root')
	sel('../data/sze_l0tau.root','../presel/sze_l0tau.root')
	sel('../data/szeorsw_l0l.root','../presel/szeorsw_l0l.root')
	sel('../data/zz_l0taumu.root','../presel/zz_l0taumu.root')
