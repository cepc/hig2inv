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
h_evtflw.GetXaxis().SetBinLabel(2,'N_{#mu}<=3&&N_{charged}<=3')
h_evtflw.GetXaxis().SetBinLabel(3,'N_{#gamma}<=1')
h_evtflw.GetXaxis().SetBinLabel(4,'10GeV<P_{t}^{#mu^{+}#mu^{-}}<70GeV')
h_evtflw.GetXaxis().SetBinLabel(5,'|P_{z}^{#mu^{+}#mu^{-}}|<65GeV')
h_evtflw.GetXaxis().SetBinLabel(6,'|cos#theta_{#mu^{+}#mu^{-}}|<0.7')
h_evtflw.GetXaxis().SetBinLabel(7,'90GeV<|Visible Energy|<120GeV')
h_evtflw.GetXaxis().SetBinLabel(8,'80GeV<|M_{#mu^{+}#mu^{-}}|<100GeV')
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
	Mass_Visble=array('d',[0])
	Energy_Visble=array('d',[0])
	P_Dilepton=array('d',4*[-99])
	Weight=array('d',[0])
	fout=ROOT.TFile(outfile,"RECREATE")
	t_out=ROOT.TTree('MCPart','MCPart')
	t_link=ROOT.TTree('Link','Link')
	t_out.Branch('Mass_Recoil',Mass_Recoil,'Mass_Recoil/D')
	t_out.Branch('Mass_Visble',Mass_Visble,'Mass_Visble/D')
	t_out.Branch('Energy_Visble',Energy_Visble,'Energy_Visble/D')
	t_out.Branch('P_Dilepton',P_Dilepton,'P_Dilepton[4]/D')
	t_link.Branch('Weight',Weight,'Weight/D')

	sel(t_in,t_out,t_link,entries,Mass_Recoil,Mass_Visble,Energy_Visble,P_Dilepton,Weight,infile)

	print '\n######Cut flow######\n'
	print 'InputFile: %s'%(infile)
	print 'Total Events: %d'%(t_in.GetEntries())
	for i in xrange(len(N)):
		print 'Cut No.: %d'%(i)
		print 'Events: %d'%(N[i])
		print 'Efficiency: %f'%(N[i]/t_in.GetEntries())
	print '\n####################\n'

	t_out.Write()
	t_link.Write()
	h_evtflw.Write()
	fout.Close()

	dur = time()-time_start
	sys.stdout.write(' \nDone in %s. \n' % dur)

def sel(t_in,t_out,t_link,entries,Mass_Recoil,Mass_Visble,Energy_Visble,P_Dilepton,Weight,infile):
	for i in xrange(entries):
		t_in.GetEntry(i)

		N[0]+=1
		h_evtflw.Fill(0)

		if not ((t_in.m_n_leptonp+t_in.m_n_leptonm)<=3 and t_in.m_n_charged<=3):
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
        	                                                   
		if not (abs(t_in.m_p_dilepton[2])<65):                
			continue
		N[4]+=1
		h_evtflw.Fill(4)                                   

		TotalP=math.sqrt(t_in.m_p_charged[3]*t_in.m_p_charged[3]-t_in.m_p_charged[0]*t_in.m_p_charged[0]-t_in.m_p_charged[1]*t_in.m_p_charged[1]-t_in.m_p_charged[2]*t_in.m_p_charged[2])
		TotalPz=t_in.m_p_charged[2]
		if TotalP!=0:
			costheta=TotalPz/TotalP
		if not (abs(costheta)<0.7):
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
		Mass_Visble[0]=t_in.m_m_visble
		Energy_Visble[0]=t_in.m_energy_visble
		for i in xrange(4):
			P_Dilepton[i]=t_in.m_p_dilepton[i]
		t_out.Fill()

	A=0
	if(N[7]!=0):
		if(infile=='../presel/signal_e2e2h.root'):
			A=7.1*5000*N[7]/100000*0.03*0.0106
		if(infile=='../presel/bkg_e2e2h_bhabha.root'):
			A=24992.21*5000*N[7]/100000
		if(infile=='../presel/bkg_e2e2h_e2e2.root'):
			A=4991.91*5000*N[7]/430200
		if(infile=='../presel/bkg_e2e2h_e3e3.root'):
			A=4432.18*5000*N[7]/1493200
		if(infile=='../presel/bkg_e2e2h_sze_l0mu.root'):
			A=0.0*5000*N[7]/1304600
		if(infile=='../presel/bkg_e2e2h_sze_l0nunu.root'):
			A=29.57*5000*N[7]/131400
		if(infile=='../presel/bkg_e2e2h_sze_l0tau.root'):
			A=150.32*5000*N[7]/1821400
		if(infile=='../presel/bkg_e2e2h_szeorsw_l0l.root'):
			A=249.84*5000*N[7]/541600
		if(infile=='../presel/bkg_e2e2h_sze_sl0_dd.root'):
			A=128.73*5000*N[7]/571000
		if(infile=='../presel/bkg_e2e2h_sze_sl0_uu.root'):
			A=195.91*5000*N[7]/850600
		if(infile=='../presel/bkg_e2e2h_ww_h_ccbs.root'):
			A=5.73*5000*N[7]/100000
		if(infile=='../presel/bkg_e2e2h_ww_h_ccds.root'):
			A=165.78*5000*N[7]/60600
		if(infile=='../presel/bkg_e2e2h_ww_h_cuxx.root'):
			A=3395.55*5000*N[7]/343200
		if(infile=='../presel/bkg_e2e2h_ww_h_uubd.root'):
			A=0.05*5000*N[7]/100000
		if(infile=='../presel/bkg_e2e2h_ww_h_uusd.root'):
			A=166.55*5000*N[7]/205800
		if(infile=='../presel/bkg_e2e2h_ww_sl0muq.root'):
			A=2366.41*5000*N[7]/11911394
		if(infile=='../presel/bkg_e2e2h_ww_sl0tauq.root'):
			A=2362.27*5000*N[7]/11911394
		if(infile=='../presel/bkg_e2e2h_zz_h.root'):
			A=499.39*5000*N[7]/2518600
		if(infile=='../presel/bkg_e2e2h_zz_l0mumu.root'):
			A=18.17*5000*N[7]/100000
		if(infile=='../presel/bkg_e2e2h_zz_l0mu.root'):
			A=14.50*5000*N[7]/100000
		if(infile=='../presel/bkg_e2e2h_zz_l0taumu.root'):
			A=17.55*5000*N[7]/100000
		if(infile=='../presel/bkg_e2e2h_zz_l0tau.root'):
			A=4.38*5000*N[7]/99800
		if(infile=='../presel/bkg_e2e2h_zz_l0tautau.root'):
			A=9.19*5000*N[7]/100000
	else:
		A=0

	if(A!=0):
		weight=A/N[7]
	else:
		weight=0

	print '###############'
	print 'InputFile: %s'%(infile)
	print 'Weight: %f'%(weight)
	print '###############'
	Weight[0]=weight
	t_link.Fill()

if __name__ == '__main__':
	main()
