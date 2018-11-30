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
import random
from array import array
#cut flow histrogram
h_evtflw = ROOT.TH1F('hevtflw1','eventflow',10,0,10)      
h_evtflw.GetXaxis().SetBinLabel(1,'raw')      
h_evtflw.GetXaxis().SetBinLabel(2,'N_{#mu^{+}}>=1&&N_{#mu^{-}}>=1&&N_{charged}<=3')
h_evtflw.GetXaxis().SetBinLabel(3,'N_{#gamma}<1')
h_evtflw.GetXaxis().SetBinLabel(4,'25GeV/c<P_{t}^{#mu^{+}#mu^{-}}<70GeV/c')
h_evtflw.GetXaxis().SetBinLabel(5,'|P_{z}^{#mu^{+}#mu^{-}}|<50GeV/c')
h_evtflw.GetXaxis().SetBinLabel(6,'#theta_{#mu^{+}#mu^{-}}<145')
h_evtflw.GetXaxis().SetBinLabel(7,'100GeV<Visible Energy<110GeV')
h_evtflw.GetXaxis().SetBinLabel(8,'86GeV/c^{2}<M_{#mu^{+}#mu^{-}}<97GeV/c^{2}')
h_evtflw.GetXaxis().SetBinLabel(9,'120GeV/c^{2}<M_{Recoil}<140GeV/c^{2}')

#root information
m_event=array('i',[0])
m_n_neutral=array('i',[0])
m_sum_p_neutral=array('f',4*[-99]) 
m_p_photon=array('f',4*[-99])
m_p_leptonp=array('f',4*[-99])
m_p_leptonm=array('f',4*[-99])
m_p_dilepton=array('f',4*[-99])
m_sum_p_charged=array('f',4*[-99])
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
m_m_dimu=array('f',[0])
m_m_recoil=array('f',[0])
m_phi_dilepton_1=array('f',[0])
m_phi_dilepton_2=array('f',[0])
m_cos_miss=array('f',[0])
m_cos_Z=array('f',[0])
m_theta_dilepton=array('f',[0])
m_cos_theta_leptonm=array('f',[0])
m_cos_theta_leptonp=array('f',[0])
m_angle_dilepton=array('f',[0])
m_delta_pt=array('f',[0])
m_energy_neutrino=array('f',[0])
m_p_visible=array('f',4*[-99])
m_energy_visible=array('f',[0])
m_p_visible3=array('f',[0])
m_vis_rec_m=array('f',[0])
m_vis_rec_e=array('f',[0])
def main():
    args=sys.argv[1:]
    infile=args[0]
    outfile=args[1]
    processname=args[2]
    table_list=args[3]
    sample = ROOT.TFile(infile)
    b = sample.Get('hevtflw')
    event = []
    for i in range(1,10):
        event.append(b.GetBinContent(i))
    weight = get_weight(event,processname,table_list) 
    root_information(infile,outfile,weight,event)
    

def get_weight(event,processname,table_list):
    event_gen=event[0]            
    IntLum=5000
    table = open(table_list , 'r' )
    cross_section=0.
    for s_line in table :
        if not s_line.startswith('#'):
            l = [x.strip() for x in s_line.split(',')] 
            process=l[0]            
            if processname == process:
                cross_section=l[2]
                print cross_section
    if processname=="e2E2h_invi":
        ffH_cross=203.66
        br_Hinv=0.5		
        weight=IntLum*ffH_cross*br_Hinv/event_gen

    elif cross_section==0.:
        print "Sample name misses, please check that!"
        sys.exit() 
    else:
        cs = float(cross_section)
        weight=IntLum*cs/event_gen
    print processname,weight
    return weight
def root_information(infile,outfile,weight,event):
    for i in range(0,9):
        for j in xrange (0,int(event[i]*weight)):
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
    t_in.SetBranchAddress('m_event',m_event)
    t_in.SetBranchAddress('m_sum_p_neutral',m_sum_p_neutral)
    t_in.SetBranchAddress('m_p_photon',m_p_photon)
    t_in.SetBranchAddress('m_p_leptonp',m_p_leptonp)
    t_in.SetBranchAddress('m_p_leptonm',m_p_leptonm)
    t_in.SetBranchAddress('m_p_dilepton',m_p_dilepton)
    t_in.SetBranchAddress('m_sum_p_charged',m_sum_p_charged)
    t_in.SetBranchAddress('m_p_Higgsdaughters',m_p_Higgsdaughters)
    t_in.SetBranchAddress('m_p_Higgsdaughter1',m_p_Higgsdaughter1)
    t_in.SetBranchAddress('m_p_Higgsdaughter2',m_p_Higgsdaughter2)
    t_in.SetBranchAddress('m_p_Zdaughters',m_p_Zdaughters)
    t_in.SetBranchAddress('m_p_Zdaughterp',m_p_Zdaughterp)
    t_in.SetBranchAddress('m_p_Zdaughterm',m_p_Zdaughterm)
    t_in.SetBranchAddress('m_pt_photon',m_pt_photon)
    t_in.SetBranchAddress('m_pt_dilepton',m_pt_dilepton)
    t_in.SetBranchAddress('m_pt_leptonm',m_pt_leptonm)
    t_in.SetBranchAddress('m_pt_leptonp',m_pt_leptonp)
    t_in.SetBranchAddress('m_pz_dilepton',m_pz_dilepton)
    t_in.SetBranchAddress('m_pz_leptonm',m_pz_leptonm)
    t_in.SetBranchAddress('m_pz_leptonp',m_pz_leptonp)
    t_in.SetBranchAddress('m_n_charged',m_n_charged)
    t_in.SetBranchAddress('m_n_gamma',m_n_gamma)
    t_in.SetBranchAddress('m_n_leptonp',m_n_leptonp)
    t_in.SetBranchAddress('m_n_leptonm',m_n_leptonm)
    t_in.SetBranchAddress('m_n_chargedp',m_n_chargedp)
    t_in.SetBranchAddress('m_n_chargedm',m_n_chargedm)
    t_in.SetBranchAddress('m_n_Higgsdaughter',m_n_Higgsdaughter)
    t_in.SetBranchAddress('m_n_neutrino',m_n_neutrino)
    t_in.SetBranchAddress('m_m_dimu',m_m_dimu)
    t_in.SetBranchAddress('m_m_recoil',m_m_recoil)
    t_in.SetBranchAddress('m_phi_dilepton_1',m_phi_dilepton_1)
    t_in.SetBranchAddress('m_phi_dilepton_2',m_phi_dilepton_2)
    t_in.SetBranchAddress('m_cos_miss',m_cos_miss)
    t_in.SetBranchAddress('m_cos_Z',m_cos_Z)
    t_in.SetBranchAddress('m_theta_dilepton',m_theta_dilepton)
    t_in.SetBranchAddress('m_cos_theta_leptonm',m_cos_theta_leptonm)
    t_in.SetBranchAddress('m_cos_theta_leptonp',m_cos_theta_leptonp)
    t_in.SetBranchAddress('m_angle_dilepton',m_angle_dilepton)
    t_in.SetBranchAddress('m_delta_pt',m_delta_pt)
    t_in.SetBranchAddress('m_energy_neutrino',m_energy_neutrino)
    t_in.SetBranchAddress('m_p_visible',m_p_visible)
    t_in.SetBranchAddress('m_p_visible3',m_p_visible3)
    t_in.SetBranchAddress('m_energy_visible',m_energy_visible)
    t_in.SetBranchAddress('m_vis_rec_m',m_vis_rec_m)
    t_in.SetBranchAddress('m_vis_rec_e',m_vis_rec_e)   
    fout=ROOT.TFile(outfile,"RECREATE")
    t_out=ROOT.TTree('tree','tree')
   
    t_out.Branch('m_event',m_event,'m_event/I')
    t_out.Branch('m_sum_p_neutral',m_sum_p_neutral,'m_sum_p_neutral[4]/F')
    t_out.Branch('m_p_photon',m_p_photon,'m_p_photon[4]/F')
    t_out.Branch('m_p_leptonp',m_p_leptonp,'m_p_leptonp[4]/F')
    t_out.Branch('m_p_leptonm',m_p_leptonm,'m_p_leptonm[4]/F')
    t_out.Branch('m_p_dilepton',m_p_dilepton,'m_p_dilepton[4]/F')
    t_out.Branch('m_sum_p_charged',m_sum_p_charged,'m_sum_p_charged[4]/F')
    t_out.Branch('m_p_Higgsdaughters',m_p_Higgsdaughters,'m_p_Higgsdaughters[4]/F')
    t_out.Branch('m_p_Higgsdaughter1',m_p_Higgsdaughter1,'m_p_Higgsdaughter1[4]/F')
    t_out.Branch('m_p_Higgsdaughter2',m_p_Higgsdaughter2,'m_p_Higgsdaughter2[4]/F')
    t_out.Branch('m_p_Zdaughters',m_p_Zdaughters,'m_p_Zdaughters[4]/F')
    t_out.Branch('m_p_Zdaughterp',m_p_Zdaughterp,'m_p_Zdaughterp[4]/F')
    t_out.Branch('m_p_Zdaughterm',m_p_Zdaughterm,'m_p_Zdaughterm[4]/F')
    t_out.Branch('m_pt_photon',m_pt_photon,'m_pt_photon/F')
    t_out.Branch('m_pt_dilepton',m_pt_dilepton,'m_pt_dilepton/F')
    t_out.Branch('m_pt_leptonm',m_pt_leptonm,'m_pt_leptonm/F')
    t_out.Branch('m_pt_leptonp',m_pt_leptonp,'m_pt_leptonp/F')
    t_out.Branch('m_pz_dilepton',m_pz_dilepton,'m_pz_dilepton/F')
    t_out.Branch('m_pz_leptonm',m_pz_leptonm,'m_pz_leptonm/F')
    t_out.Branch('m_pz_leptonp',m_pz_leptonp,'m_pz_leptonp/F')
    t_out.Branch('m_n_charged',m_n_charged,'m_n_charged/I')
    t_out.Branch('m_n_gamma',m_n_gamma,'m_n_gamma/I')
    t_out.Branch('m_n_leptonp',m_n_leptonp,'m_n_leptonp/I')
    t_out.Branch('m_n_leptonm',m_n_leptonm,'m_n_leptonm/I')
    t_out.Branch('m_n_chargedp',m_n_chargedp,'m_n_chargedp/I')
    t_out.Branch('m_n_chargedm',m_n_chargedm,'m_n_chargedm/I')
    t_out.Branch('m_n_Higgsdaughter',m_n_Higgsdaughter,'m_n_Higgsdaughter/I')
    t_out.Branch('m_n_neutrino',m_n_neutrino,'m_n_neutrino/I')
    t_out.Branch('m_m_dimu',m_m_dimu,'m_m_dimu/F')
    t_out.Branch('m_m_recoil',m_m_recoil,'m_m_recoil/F')
    t_out.Branch('m_phi_dilepton_1',m_phi_dilepton_1,'m_phi_dilepton_1/F')
    t_out.Branch('m_phi_dilepton_2',m_phi_dilepton_2,'m_phi_dilepton_2/F')
    t_out.Branch('m_cos_miss',m_cos_miss,'m_cos_miss/F')
    t_out.Branch('m_cos_Z',m_cos_Z,'m_cos_Z/F')
    t_out.Branch('m_theta_dilepton',m_theta_dilepton,'m_theta_dilepton/F')
    t_out.Branch('m_cos_theta_leptonm',m_cos_theta_leptonm,'m_cos_theta_leptonm/F')
    t_out.Branch('m_cos_theta_leptonp',m_cos_theta_leptonp,'m_cos_theta_leptonp/F')
    t_out.Branch('m_angle_dilepton',m_angle_dilepton,'m_angle_dilepton/F')
    t_out.Branch('m_delta_pt',m_delta_pt,'m_delta_pt/F')
    t_out.Branch('m_energy_neutrino',m_energy_neutrino,'m_energy_neutrino/F')
    t_out.Branch('m_p_visible',m_p_visible,'m_p_visible[4]/F')
    t_out.Branch('m_p_visible3',m_p_visible3,'m_p_visible3/F')
    t_out.Branch('m_energy_visible',m_energy_visible,'m_energy_visible/F')
    t_out.Branch('m_vis_rec_m',m_vis_rec_m,'m_vis_rec_m/F')
    t_out.Branch('m_vis_rec_e',m_vis_rec_e,'m_vis_rec_e/F')
    for i in xrange(entries):
        if (weight<1):
            rnd=random.random()
            if (rnd<weight):
                t_in.GetEntry(i)
                t_out.Fill()
        else :
            rnd1=random.random()
            print rnd1
            valuem=int(weight)
            dweight=abs(valuem-weight)
            print dweight
            if (rnd1<dweight):
                for j in xrange(int(weight)+1):
                    t_in.GetEntry(i)
                    t_out.Fill()
            else:
                for j in xrange(int(weight)):
                    t_in.GetEntry(i)
                    t_out.Fill()
    for i in xrange(1,19):
        h[i].Write()
    h_evtflw.Write()
    t_out.Write()
if __name__ == '__main__':
    main()
