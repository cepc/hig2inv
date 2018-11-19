#!/usr/bin/env python  
"""
Choose Events
"""

__author__='Tanyh <tanyuhang@ihep.ac.cn>'
__copyright__='Copyright (c) Tanyh'
__created__='[2018-10-19]'
 
import sys
import os
import copy
import ROOT
from array import array
#cut flow histrogram
h_evtflw = ROOT.TH1F('hevtflw1','eventflow',10,0,10)      
h_evtflw.GetXaxis().SetBinLabel(1,'raw')      
h_evtflw.GetXaxis().SetBinLabel(2,'N_{#mu^{+}}>=1&&N_{#mu^{-}}>=1&&N_{charged}<=3')
h_evtflw.GetXaxis().SetBinLabel(3,'N_{#gamma}<=1')
h_evtflw.GetXaxis().SetBinLabel(4,'10GeV/c<P_{t}^{#mu^{+}#mu^{-}}<70GeV/c')
h_evtflw.GetXaxis().SetBinLabel(5,'|P_{z}^{#mu^{+}#mu^{-}}|<50GeV/c')
h_evtflw.GetXaxis().SetBinLabel(6,'|cos#theta_{#mu^{+}#mu^{-}}|<0.5')
h_evtflw.GetXaxis().SetBinLabel(7,'90GeV<Visible Energy<110GeV')
h_evtflw.GetXaxis().SetBinLabel(8,'83GeV/c^{2}<M_{#mu^{+}#mu^{-}}<97GeV/c^{2}')
h_evtflw.GetXaxis().SetBinLabel(9,'120GeV/c^{2}<M_{Recoil}<150GeV/c^{2}')

#root information
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
m_energy_neutrino=array('f',[0])
m_energy_visible=array('f',[0])
m_energy_leptonm=array('f',[0])
m_energy_leptonp=array('f',[0])

def main():
    args=sys.argv[1:]
    infile=args[0]
    outfile=args[1]
    processname=args[2]
    sample = ROOT.TFile(infile)
    b = sample.Get('hevtflw')
    event = []
    for i in range(1,10):
        event.append(b.GetBinContent(i))
    weight = get_weight(event,processname) 
    root_information(infile,outfile,weight,event)
    

def get_weight(event,processname):
    event_gen=event[0]            
    IntLum=5000
    if processname=="e2E2h_invi":
        ffH_cross=6.77
        br_Hinv=0.5
        weight=IntLum*ffH_cross*br_Hinv/event_gen
    elif processname=="e1e1":
        e1e1_cross=24770.90
        weight=IntLum*e1e1_cross/event_gen
    elif processname=="e2e2":
        e2e2_cross=5332.71
        weight=IntLum*e2e2_cross/event_gen
    elif processname=="e3e3":
        e3e3_cross=4752.89
        weight=IntLum*e3e3_cross/event_gen
    elif processname=="qq":
        qq_cross=54106.86
        weight=IntLum*qq_cross/event_gen
    elif processname=="sw_l":
        sw_l0mu=436.70
        sw_l0tau=435.93
        sw_l_cross=sw_l0mu+sw_l0tau
        weight=IntLum*sw_l_cross/event_gen
    elif processname=="sw_sl":
        sw_sl_cross=2612.62
        weight=IntLum*sw_sl_cross/event_gen
    elif processname=="sze_l":
        sze_l0e=78.49
        sze_l0mu=845.81
        sze_l0nunu=28.94
        sze_l0tau=147.28
        sze_l_cross=sze_l0e+sze_l0mu+sze_l0nunu+sze_l0tau
        weight=IntLum*sze_l_cross/event_gen
    elif processname=="sze_sl":
        sze_sl0dd=125.83
        sze_sl0uu=190.21
        sze_sl_cross=sze_sl0dd+sze_sl0uu
        weight=IntLum*sze_sl_cross/event_gen
    elif processname=="szeorsw_l":		
        szeorsw_l_cross=249.48
        weight=IntLum*szeorsw_l_cross/event_gen
    elif processname=="sznu_l":
        sznu_l0mumu=43.42
        sznu_l0tautau=14.57		
        sznu_l_cross=sznu_l0tautau+sznu_l0mumu
        weight=IntLum*sznu_l_cross/event_gen
    elif processname=="sznu_sl":
        sznu_sl0nu_down=90.03		
        sznu_sl0nu_up=55.59
        sznu_sl_cross=sznu_sl0nu_down+sznu_sl0nu_up
        weight=IntLum*sznu_sl_cross/event_gen	
    elif processname=="ww_h":
        ww_h0ccbs=5.89
        ww_h0ccds=170.18
        ww_h0cuxx=3478.89
        ww_h0uubd=0.05
        ww_h0uusd=170.45		
        ww_h_cross=ww_h0ccbs+ww_h0ccds+ww_h0cuxx+ww_h0uubd+ww_h0uusd
        weight=IntLum*ww_h_cross/event_gen
    elif processname=="ww_l0ll":		
        ww_l0ll_cross=403.66
        weight=IntLum*ww_l0ll_cross/event_gen
    elif processname=="ww_sl":		
        ww_sl0muq=2423.43
        ww_sl0tauq=2423.56
        ww_sl_cross=ww_sl0muq+ww_sl0tauq
        weight=IntLum*ww_sl_cross/event_gen
    elif processname=="zz_h":
        zz_h0cc_nots=98.97
        zz_h0dtdt=233.46
        zz_h0utut=85.68
        zz_h0uu_notd=98.56		
        zz_h_cross=zz_h0cc_nots+zz_h0dtdt+zz_h0utut+zz_h0uu_notd
        weight=IntLum*zz_h_cross/event_gen
    elif processname=="zz_l":
        zz_l04mu=15.56
        zz_l04tau=4.61
        zz_l0mumu=19.38
        zz_l0taumu=18.65
        zz_l0tautau=9.61		
        zz_l_cross=zz_l04mu+zz_l04tau+zz_l0mumu+zz_l0taumu+zz_l0tautau
        weight=IntLum*zz_l_cross/event_gen
    elif processname=="zz_sl":
        zz_sl0mu_down=136.14
        zz_sl0mu_up=87.39
        zz_sl0nu_down=139.71
        zz_sl0nu_up=84.38
        zz_sl0tau_down=67.31
        zz_sl0tau_up=41.56		
        zz_sl_cross=zz_sl0mu_down+zz_sl0mu_up+zz_sl0nu_down+zz_sl0nu_up+zz_sl0tau_down+zz_sl0tau_up
        weight=IntLum*zz_sl_cross/event_gen
    elif processname=="zzorww_h":
        zzorww_h0cscs=1607.55
        zzorww_h0udud=1610.32		
        zzorww_h_cross=zzorww_h0cscs+zzorww_h0udud
        weight=IntLum*zzorww_h_cross/event_gen
    elif processname=="zzorww_l":	
        zzorww_l0mumu=221.10
        zzorww_l0tautau=211.18
        zzorww_l_cross=zzorww_l0mumu+zzorww_l0tautau
        weight=IntLum*zzorww_l_cross/event_gen
    else:
        print "Sample name misses, please check that!"
        sys.exit()
    return weight
def root_information(infile,outfile,weight,event):
    for i in range(0,9):
        for j in range (0,int(event[i]*weight)):
            h_evtflw.Fill(i)
    h =[0]*19
    f = ROOT.TFile(infile)
    h[1] = f.Get('before_cut_number_mounp')
    h[2] = f.Get('before_cut_number_mounm')
    h[3] = f.Get('before_cut_n_photon')
    h[4] = f.Get('before_cut_Pt')
    h[5] = f.Get('before_cut_Pz')
    h[6] = f.Get('before_cut_theta')
    h[7] = f.Get('before_cut_vis')
    h[8] = f.Get('before_cut_Mmumu')
    h[9] = f.Get('before_cut_Mrecoil')

    h[10] = f.Get('after_cut_number_mounp')
    h[11] = f.Get('after_cut_number_mounm')
    h[12] = f.Get('after_cut_n_photon')
    h[13] = f.Get('after_cut_Pt')
    h[14] = f.Get('after_cut_Pz')
    h[15] = f.Get('after_cut_theta')
    h[16] = f.Get('after_cut_vis')
    h[17] = f.Get('after_cut_Mmumu')
    h[18] = f.Get('after_cut_Mrecoil')
    for i in range(1,19):
        h[i].Scale(weight)

    fin=ROOT.TFile(infile)
    t_in=fin.Get('tree')
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
    fout=ROOT.TFile(outfile,"RECREATE")
    t_out=ROOT.TTree('tree','tree')
   
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
    for i in xrange(entries):
        if (weight<1):
            rnd=ROOT.gRandom.Uniform()
        if (rnd<weight):
            t_in.GetEntry(i)
            t_out.Fill()
    else :
        rnd1=ROOT.gRandom.Uniform()
        valuem=int(weight)
        dweight=abs(valuem-weight)
        if (rnd1<dweight):
            for j in xrange(int(weight)+1):
                t_in.GetEntry(i)
                t_out.Fill()
        else:
            for j in xrange(int(weight)):
                t_in.GetEntry(i)
                t_out.Fill()
    for i in xrange(1,18):
        h[i].Write()
    h_evtflw.Write()
    t_out.Write()
if __name__ == '__main__':
    main()
