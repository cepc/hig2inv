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
from time import time

h_evtflw = ROOT.TH1F('hevtflw','eventflow',10,0,10)
h_evtflw.GetXaxis().SetBinLabel(1,'raw')
h_evtflw.GetXaxis().SetBinLabel(2,'2=<N_{e}<=3&&N_{ch}<=3')
h_evtflw.GetXaxis().SetBinLabel(3,'N_{#gamma}<=1')
h_evtflw.GetXaxis().SetBinLabel(4,'10GeV<P_{t}^{e^{+}e^{-}}<70GeV')
h_evtflw.GetXaxis().SetBinLabel(5,'|P_{z}^{e^{+}e^{-}}|<60GeV')
h_evtflw.GetXaxis().SetBinLabel(6,'|cos#theta_{e^{+}e^{-}}|<0.8')
h_evtflw.GetXaxis().SetBinLabel(7,'90GeV<|Visible Energy|<120GeV')
h_evtflw.GetXaxis().SetBinLabel(8,'70GeV<|M_{e^{+}e^{-}}|<100GeV')
N=[0.,0.,0.,0.,0.,0.,0.,0.]

def main():

	args=sys.argv[1:]
	if len(args)<2:
		return usage()

	infile=args[0]
	outfile=args[1]

	fin=ROOT.TFile(infile)
	t_in=fin.Get('MCPart')
	entries=t_in.GetEntriesFast()

	time_start = time()

	Mass_Recoil=array('d',[0])
	fout=ROOT.TFile(outfile,"RECREATE")
	t_out=ROOT.TTree('MCPart','MCPart')
	t_out.Branch('Mass_Recoil',Mass_Recoil,'Mass_Recoil/D')

	sel(t_in,t_out,entries,Mass_Recoil)

	print '\n######Cut flow######\n'
	print 'InputFile: %s'%(infile)
	print 'Total Events: %d'%(t_in.GetEntries())
	for i in xrange(len(N)):
		print 'Cut No.: %d'%(i)
		print 'Events: %d'%(N[i])
		print 'Efficiency: %f'%(N[i]/t_in.GetEntries())
	print '\n####################\n'

	t_out.Write()
	h_evtflw.Write()
	fout.Close()

	dur = time()-time_start
	sys.stdout.write(' \nDone in %s. \n' % dur)

def sel(t_in,t_out,entries,Mass_Recoil):
	for i in xrange(entries):
		t_in.GetEntry(i)

		N[0]+=1
		h_evtflw.Fill(0)

		if not ((t_in.m_n_leptonp+t_in.m_n_leptonm)>=2 and (t_in.m_n_leptonp+t_in.m_n_leptonm)<=3 and t_in.m_n_charged<=3):
			continue
		N[1]+=1
		h_evtflw.Fill(1)

		if not (t_in.m_n_gamma<=1):
			continue
		N[2]+=1
		h_evtflw.Fill(2)

		if not (t_in.m_pt_dilepton>10 and t_in.m_pt_dilepton<70):
			continue
		N[3]+=1
		h_evtflw.Fill(3)                                   
        	                                                   
		if not (abs(t_in.m_p_dilepton[2])<60):                
			continue
		N[4]+=1
		h_evtflw.Fill(4)                                   

		if not (abs(t_in.m_cos_Z)<0.8):
			continue
		N[5]+=1
		h_evtflw.Fill(5)

		if not (t_in.m_energy_visble>90 and t_in.m_energy_visble<120):
			continue
		N[6]+=1
		h_evtflw.Fill(6)

		if not (t_in.m_m_visble>70 and t_in.m_m_visble<100):
			continue
		N[7]+=1
		h_evtflw.Fill(7)

		Mass_Recoil[0]=t_in.m_m_recoil
		t_out.Fill()

if __name__ == '__main__':
	main()
