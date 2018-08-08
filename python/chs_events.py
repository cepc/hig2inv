#!/usr/bin/env python
"""
Choose Events
"""

__author__='JING Maoqiang <jingmq@ihep.ac.cn>'
__copyright__='Copyright (c) JING Maoqiang'
__created__='[2018-07-18]'

import sys
import os
import ROOT
from array import array

args=sys.argv[1:]
infile=args[0]
outfile=args[1]
processname=args[2]
IntLum=5000
if processname=="signal_e2e2h":
	ffH_cross=203.66
	br_Hinv=0.106*0.01
	event_gen=199863.
	weight=IntLum*ffH_cross*br_Hinv/event_gen
elif processname=="bkg_e2e2":
	e2e2_cross=4991.91
	event_gen=328311.
	weight=IntLum*e2e2_cross/event_gen
elif processname=="bkg_e3e3":
	e3e3_cross=4432.18
	event_gen=1484572.
	weight=IntLum*e3e3_cross/event_gen
elif processname=="bkg_bb":
	bb_cross=9957.7
	event_gen=885200.
	weight=IntLum*bb_cross/event_gen
elif processname=="bkg_cc":
	cc_cross=10102.75
	event_gen=1181208.
	weight=IntLum*cc_cross/event_gen
elif processname=="bkg_dd":
	dd_cross=10010.07
	event_gen=1152000.
	weight=IntLum*dd_cross/event_gen
else:
	print "Sample name misses, please check that!"
	sys.exit()

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
m_pt_leptonm=array('f',[0])
m_pt_leptonp=array('f',[0])
m_pz_dilepton=array('f',[0])
m_pz_leptonm=array('f',[0])
m_pz_leptonp=array('f',[0])
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
m_cos_theta_dilepton=array('f',[0])
m_cos_theta_leptonm=array('f',[0])
m_cos_theta_leptonp=array('f',[0])
m_angle_dilepton=array('f',[0])
m_delta_pt=array('f',[0])
m_PID_Zdaughter=array('i',[0])
m_PID_HiggsDaughter=array('i',[0])
m_PID_Higgsdaughter=array('i',[0])
m_energy_neutrino=array('f',[0])
m_energy_visible=array('f',[0])
m_energy_leptonm=array('f',[0])
m_energy_leptonp=array('f',[0])
BDTG=array('f',[0])

fin=ROOT.TFile(infile)
t_in=fin.Get('MCPart')
entries=t_in.GetEntriesFast()

t_in.SetBranchAddress('m_p_neutral',m_p_neutral)
t_in.SetBranchAddress('m_p_photon',m_p_photon)
t_in.SetBranchAddress('m_p_leptonp',m_p_leptonp)
t_in.SetBranchAddress('m_p_leptonm',m_p_leptonm)
t_in.SetBranchAddress('m_p_dilepton',m_p_dilepton)
t_in.SetBranchAddress('m_p_charged',m_p_charged)
t_in.SetBranchAddress('m_p_Higgsdaughters',m_p_Higgsdaughters)
t_in.SetBranchAddress('m_p_Higgsdaughter1',m_p_Higgsdaughter1)
t_in.SetBranchAddress('m_p_Higgsdaughter2',m_p_Higgsdaughter2)
t_in.SetBranchAddress('m_p_Zdaughters',m_p_Zdaughters)
t_in.SetBranchAddress('m_p_Zdaughterp',m_p_Zdaughterp)
t_in.SetBranchAddress('m_p_Zdaughterm',m_p_Zdaughterm)
t_in.SetBranchAddress('m_pt_photon',m_pt_photon)
t_in.SetBranchAddress('m_pt_dilepton',m_pt_dilepton)
t_in.SetBranchAddress('m_m_visible',m_m_visible)
t_in.SetBranchAddress('m_m_recoil',m_m_recoil)
t_in.SetBranchAddress('m_phi_dilepton_1',m_phi_dilepton_1)
t_in.SetBranchAddress('m_phi_dilepton_2',m_phi_dilepton_2)
t_in.SetBranchAddress('m_cos_miss',m_cos_miss)
t_in.SetBranchAddress('m_cos_Z',m_cos_Z)
t_in.SetBranchAddress('m_angle_dilepton',m_angle_dilepton)
t_in.SetBranchAddress('m_delta_pt',m_delta_pt)
t_in.SetBranchAddress('m_energy_neutrino',m_energy_neutrino)
t_in.SetBranchAddress('m_energy_visible',m_energy_visible)
if processname=="signal_e2e2h":
	t_in.SetBranchAddress('m_pt_leptonm',m_pt_leptonm)
	t_in.SetBranchAddress('m_pt_leptonp',m_pt_leptonp)
	t_in.SetBranchAddress('m_pz_dilepton',m_pz_dilepton)
	t_in.SetBranchAddress('m_pz_leptonm',m_pz_leptonm)
	t_in.SetBranchAddress('m_pz_leptonp',m_pz_leptonp)
	t_in.SetBranchAddress('m_cos_theta_dilepton',m_cos_theta_dilepton)
	t_in.SetBranchAddress('m_cos_theta_leptonm',m_cos_theta_leptonm)
	t_in.SetBranchAddress('m_cos_theta_leptonp',m_cos_theta_leptonp)
	t_in.SetBranchAddress('m_energy_leptonm',m_energy_leptonm)
	t_in.SetBranchAddress('m_energy_leptonp',m_energy_leptonp)
	t_in.SetBranchAddress('BDTG',BDTG)
if processname!="signal_e2e2h":
	t_in.SetBranchAddress('m_event',m_event)
	t_in.SetBranchAddress('m_event_type',m_event_type)
	t_in.SetBranchAddress('m_n_charged',m_n_charged)
	t_in.SetBranchAddress('m_n_gamma',m_n_gamma)
	t_in.SetBranchAddress('m_n_leptonp',m_n_leptonp)
	t_in.SetBranchAddress('m_n_leptonm',m_n_leptonm)
	t_in.SetBranchAddress('m_n_chargedp',m_n_chargedp)
	t_in.SetBranchAddress('m_n_chargedm',m_n_chargedm)
	t_in.SetBranchAddress('m_n_Higgsdaughter',m_n_Higgsdaughter)
	t_in.SetBranchAddress('m_n_neutrino',m_n_neutrino)
	t_in.SetBranchAddress('m_PID_Zdaughter',m_PID_Zdaughter)
	t_in.SetBranchAddress('m_PID_HiggsDaughter',m_PID_HiggsDaughter)
	t_in.SetBranchAddress('m_PID_Higgsdaughter',m_PID_Higgsdaughter)

fout=ROOT.TFile(outfile,"RECREATE")
t_out=ROOT.TTree('MCPart','MCPart')

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
if processname=="signal_e2e2h":
	t_out.Branch('m_pt_leptonm',m_pt_leptonm,'m_pt_leptonm/F')
	t_out.Branch('m_pt_leptonp',m_pt_leptonp,'m_pt_leptonp/F')
	t_out.Branch('m_pz_dilepton',m_pz_dilepton,'m_pz_dilepton/F')
	t_out.Branch('m_pz_leptonm',m_pz_leptonm,'m_pz_leptonm/F')
	t_out.Branch('m_pz_leptonp',m_pz_leptonp,'m_pz_leptonp/F')
	t_out.Branch('m_cos_theta_dilepton',m_cos_theta_dilepton,'m_cos_theta_dilepton/F')
	t_out.Branch('m_cos_theta_leptonm',m_cos_theta_leptonm,'m_cos_theta_leptonm/F')
	t_out.Branch('m_cos_theta_leptonp',m_cos_theta_leptonp,'m_cos_theta_leptonp/F')
	t_out.Branch('m_energy_leptonm',m_energy_leptonm,'m_energy_leptonm/F')
	t_out.Branch('m_energy_leptonp',m_energy_leptonp,'m_energy_leptonp/F')
	t_out.Branch('BDTG',BDTG,'BDTG/F')
if processname!="signal_e2e2h":
	t_out.Branch('m_event',m_event,'m_event/I')
	t_out.Branch('m_event_type',m_event_type,'m_event_type/I')
	t_out.Branch('m_n_charged',m_n_charged,'m_n_charged/I')
	t_out.Branch('m_n_gamma',m_n_gamma,'m_n_gamma/I')
	t_out.Branch('m_n_leptonp',m_n_leptonp,'m_n_leptonp/I')
	t_out.Branch('m_n_leptonm',m_n_leptonm,'m_n_leptonm/I')
	t_out.Branch('m_n_chargedp',m_n_chargedp,'m_n_chargedp/I')
	t_out.Branch('m_n_chargedm',m_n_chargedm,'m_n_chargedm/I')
	t_out.Branch('m_n_Higgsdaughter',m_n_Higgsdaughter,'m_n_Higgsdaughter/I')
	t_out.Branch('m_n_neutrino',m_n_neutrino,'m_n_neutrino/I')
	t_out.Branch('m_PID_Zdaughter',m_PID_Zdaughter,'m_PID_Zdaughter/I')
	t_out.Branch('m_PID_HiggsDaughter',m_PID_HiggsDaughter,'m_PID_HiggsDaughter/I')
	t_out.Branch('m_PID_Higgsdaughter',m_PID_Higgsdaughter,'m_PID_Higgsdaughter/I')

for i in xrange(entries):
	if (weight<1):
		rnd=ROOT.gRandom.Uniform()
		if (rnd<weight):
			t_in.GetEntry(i)
			t_out.Fill()
	else :
		for j in xrange(int(weight)):
			t_in.GetEntry(i)
			t_out.Fill()

t_out.Write()
