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
h_evtflw.GetXaxis().SetBinLabel(2,'N_{#mu}<3&&N_{charged}<3')
h_evtflw.GetXaxis().SetBinLabel(3,'N_{#gamma}<=1')
h_evtflw.GetXaxis().SetBinLabel(4,'30GeV/c<P_{t}^{#mu^{+}#mu^{-}}<60GeV/c')
h_evtflw.GetXaxis().SetBinLabel(5,'|P_{z}^{#mu^{+}#mu^{-}}|<55GeV/c')
h_evtflw.GetXaxis().SetBinLabel(6,'|cos#theta_{#mu^{+}#mu^{-}}|<0.6')
h_evtflw.GetXaxis().SetBinLabel(7,'90GeV<Visible Energy<107GeV')
h_evtflw.GetXaxis().SetBinLabel(8,'83GeV/c^{2}<M_{#mu^{+}#mu^{-}}<97GeV/c^{2}')
h_evtflw.GetXaxis().SetBinLabel(9,'120GeV/c^{2}<M_{Recoil}<150GeV/c^{2}')
N=[0.,0.,0.,0.,0.,0.,0.,0.,0.]

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

	m_event=array('i',[0])
	m_event_type=array('i',[0])
	m_p_neutral=array('f',4*[-99])
	m_p_photon=array('f',4*[-99])
	m_p_leptonp=array('f',4*[-99])
	m_p_leptonm=array('f',4*[-99])
	m_p_dilepton=array('f',4*[-99])
	m_p_charged=array('f',4*[-99])
	m_p_Higgsdaughters=array('f',4*[-99])
	m_p_Higgsdaughter1=array('f',4*[-99])
	m_p_Higgsdaughter2=array('f',4*[-99])
	m_p_Zdaughters=array('f',4*[-99])
	m_p_Zdaughterp=array('f',4*[-99])
	m_p_Zdaughterm=array('f',4*[-99])
	m_pt_photon=array('f',[0])
	m_pt_dilepton=array('f',[0])
	m_n_charged=array('i',[0])
	m_n_gamma=array('i',[0])
	m_n_leptonp=array('i',[0])
	m_n_leptonm=array('i',[0])
	m_n_chargedp=array('i',[0])
	m_n_chargedm=array('i',[0])
	m_n_Higgsdaughter=array('i',[0])
	m_n_neutrino=array('i',[0])
	m_m_visible=array('f',[0])
	m_m_recoil=array('f',[0])
	m_phi_dilepton_1=array('f',[0])
	m_phi_dilepton_2=array('f',[0])
	m_cos_miss=array('f',[0])
	m_cos_Z=array('f',[0])
	m_angle_dilepton=array('f',[0])
	m_delta_pt=array('f',[0])
	m_energy_neutrino=array('f',[0])
	m_energy_visible=array('f',[0])

	fout=ROOT.TFile(outfile,"RECREATE")
	t_out=ROOT.TTree('MCPart','MCPart')

	t_out.Branch('m_event',m_event,'m_event/I')
	t_out.Branch('m_event_type',m_event_type,'m_event_type/I')
	t_out.Branch('m_p_neutral',m_p_neutral,'m_p_neutral[4]/F')
	t_out.Branch('m_p_photon',m_p_photon,'m_p_photon[4]/F')
	t_out.Branch('m_p_leptonp',m_p_leptonp,'m_p_leptonp[4]/F')
	t_out.Branch('m_p_leptonm',m_p_leptonm,'m_p_leptonm[4]/F')
	t_out.Branch('m_p_dilepton',m_p_dilepton,'m_p_dilepton[4]/F')
	t_out.Branch('m_p_charged',m_p_charged,'m_p_charged[4]/F')
	t_out.Branch('m_p_Higgsdaughters',m_p_Higgsdaughters,'m_p_Higgsdaughters[4]/F')
	t_out.Branch('m_p_Higgsdaughter1',m_p_Higgsdaughter1,'m_p_Higgsdaughter1[4]/F')
	t_out.Branch('m_p_Higgsdaughter2',m_p_Higgsdaughter2,'m_p_Higgsdaughter2[4]/F')
	t_out.Branch('m_p_Zdaughters',m_p_Zdaughters,'m_p_Zdaughters[4]/F')
	t_out.Branch('m_p_Zdaughterp',m_p_Zdaughterp,'m_p_Zdaughterp[4]/F')
	t_out.Branch('m_p_Zdaughterm',m_p_Zdaughterm,'m_p_Zdaughterm[4]/F')
	t_out.Branch('m_pt_photon',m_pt_photon,'m_pt_photon/F')
	t_out.Branch('m_pt_dilepton',m_pt_dilepton,'m_pt_dilepton/F')
	t_out.Branch('m_n_charged',m_n_charged,'m_n_charged/I')
	t_out.Branch('m_n_gamma',m_n_gamma,'m_n_gamma/I')
	t_out.Branch('m_n_leptonp',m_n_leptonp,'m_n_leptonp/I')
	t_out.Branch('m_n_leptonm',m_n_leptonm,'m_n_leptonm/I')
	t_out.Branch('m_n_chargedp',m_n_chargedp,'m_n_chargedp/I')
	t_out.Branch('m_n_chargedm',m_n_chargedm,'m_n_chargedm/I')
	t_out.Branch('m_n_Higgsdaughter',m_n_Higgsdaughter,'m_n_Higgsdaughter/I')
	t_out.Branch('m_n_neutrino',m_n_neutrino,'m_n_neutrino/I')
	t_out.Branch('m_m_visible',m_m_visible,'m_m_visible/F')
	t_out.Branch('m_m_recoil',m_m_recoil,'m_m_recoil/F')
	t_out.Branch('m_phi_dilepton_1',m_phi_dilepton_1,'m_phi_dilepton_1/F')
	t_out.Branch('m_phi_dilepton_2',m_phi_dilepton_2,'m_phi_dilepton_2/F')
	t_out.Branch('m_cos_miss',m_cos_miss,'m_cos_miss/F')
	t_out.Branch('m_cos_Z',m_cos_Z,'m_cos_Z/F')
	t_out.Branch('m_angle_dilepton',m_angle_dilepton,'m_angle_dilepton/F')
	t_out.Branch('m_delta_pt',m_delta_pt,'m_delta_pt/F')
	t_out.Branch('m_energy_neutrino',m_energy_neutrino,'m_energy_neutrino/F')
	t_out.Branch('m_energy_visible',m_energy_visible,'m_energy_visible/F')

	sel(t_in,t_out,entries,m_event,m_event_type,m_p_neutral,m_p_photon,m_p_leptonp,m_p_leptonm,m_p_dilepton,m_p_charged,m_p_Higgsdaughters,m_p_Higgsdaughter1,m_p_Higgsdaughter2,m_p_Zdaughters,m_p_Zdaughterp,m_p_Zdaughterm,m_pt_photon,m_pt_dilepton,m_n_charged,m_n_gamma,m_n_leptonp,m_n_leptonm,m_n_chargedp,m_n_chargedm,m_n_Higgsdaughter,m_n_neutrino,m_m_visible,m_m_recoil,m_phi_dilepton_1,m_phi_dilepton_2,m_cos_miss,m_cos_Z,m_angle_dilepton,m_delta_pt,m_energy_neutrino,m_energy_visible,infile)

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

def sel(t_in,t_out,entries,m_event,m_event_type,m_p_neutral,m_p_photon,m_p_leptonp,m_p_leptonm,m_p_dilepton,m_p_charged,m_p_Higgsdaughters,m_p_Higgsdaughter1,m_p_Higgsdaughter2,m_p_Zdaughters,m_p_Zdaughterp,m_p_Zdaughterm,m_pt_photon,m_pt_dilepton,m_n_charged,m_n_gamma,m_n_leptonp,m_n_leptonm,m_n_chargedp,m_n_chargedm,m_n_Higgsdaughter,m_n_neutrino,m_m_visible,m_m_recoil,m_phi_dilepton_1,m_phi_dilepton_2,m_cos_miss,m_cos_Z,m_angle_dilepton,m_delta_pt,m_energy_neutrino,m_energy_visible,infile):
	for i in xrange(entries):
		t_in.GetEntry(i)

		N[0]+=1
		h_evtflw.Fill(0)

		if not ((t_in.m_n_leptonp+t_in.m_n_leptonm)<3 and t_in.m_n_charged<3):
			continue
		N[1]+=1
		h_evtflw.Fill(1)

		if not (t_in.m_n_gamma<=1):
			continue
		N[2]+=1
		h_evtflw.Fill(2)

		if not (t_in.m_pt_dilepton>30 and t_in.m_pt_dilepton<60):
			continue
		N[3]+=1
		h_evtflw.Fill(3)                                   
        	                                                   
		if not (abs(t_in.m_p_dilepton[2])<55): 
			continue
		N[4]+=1
		h_evtflw.Fill(4)

		TotalP=math.sqrt(t_in.m_p_dilepton[3]*t_in.m_p_dilepton[3]-t_in.m_p_dilepton[0]*t_in.m_p_dilepton[0]-t_in.m_p_dilepton[1]*t_in.m_p_dilepton[1]-t_in.m_p_dilepton[2]*t_in.m_p_dilepton[2])
		TotalPz=t_in.m_p_dilepton[2]
		if TotalP!=0:
			costheta=TotalPz/TotalP
		if not (abs(costheta)<0.6):
			continue
		N[5]+=1
		h_evtflw.Fill(5)

		if not (t_in.m_energy_visible>90 and t_in.m_energy_visible<107):
			continue
		N[6]+=1
		h_evtflw.Fill(6)

		if not (t_in.m_m_visible>83 and t_in.m_m_visible<97):
			continue
		N[7]+=1
		h_evtflw.Fill(7)

		if not (t_in.m_m_recoil>120 and t_in.m_m_recoil<150):
			continue
		N[8]+=1
		h_evtflw.Fill(8)

		m_event[0]=t_in.m_event                                 
		m_event_type[0]=t_in.m_event_type
		m_pt_photon[0]=t_in.m_pt_photon
		m_pt_dilepton[0]=t_in.m_pt_dilepton
		m_n_charged[0]=t_in.m_n_charged
		m_n_gamma[0]=t_in.m_n_gamma
		m_n_leptonp[0]=t_in.m_n_leptonp
		m_n_leptonm[0]=t_in.m_n_leptonm
		m_n_chargedp[0]=t_in.m_n_chargedp
		m_n_chargedm[0]=t_in.m_n_chargedm
		m_n_Higgsdaughter[0]=t_in.m_n_Higgsdaughter
		m_n_neutrino[0]=t_in.m_n_neutrino
		m_m_visible[0]=t_in.m_m_visible
		m_m_recoil[0]=t_in.m_m_recoil
		m_phi_dilepton_1[0]=t_in.m_phi_dilepton_1
		m_phi_dilepton_2[0]=t_in.m_phi_dilepton_2
		m_cos_miss[0]=t_in.m_cos_miss
		m_cos_Z[0]=t_in.m_cos_Z
		m_angle_dilepton[0]=t_in.m_angle_dilepton
		m_delta_pt[0]=t_in.m_delta_pt
		m_energy_neutrino[0]=t_in.m_energy_neutrino
		m_energy_visible[0]=t_in.m_energy_visible

		for i in xrange(4):
			m_p_neutral[i]=t_in.m_p_neutral[i]               
			m_p_photon[i]=t_in.m_p_photon[i]
			m_p_leptonp[i]=t_in.m_p_leptonp[i]
			m_p_leptonm[i]=t_in.m_p_leptonm[i]
			m_p_dilepton[i]=t_in.m_p_dilepton[i]
			m_p_charged[i]=t_in.m_p_charged[i]
			m_p_Higgsdaughters[i]=t_in.m_p_Higgsdaughters[i]
			m_p_Higgsdaughter1[i]=t_in.m_p_Higgsdaughter1[i]
			m_p_Higgsdaughter2[i]=t_in.m_p_Higgsdaughter2[i]
			m_p_Zdaughters[i]=t_in.m_p_Zdaughters[i]
			m_p_Zdaughterp[i]=t_in.m_p_Zdaughterp[i]
			m_p_Zdaughterm[i]=t_in.m_p_Zdaughterm[i]

		t_out.Fill()

if __name__ == '__main__':
	main()
