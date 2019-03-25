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
h_evtflw = ROOT.TH1F('hevtflw','eventflow',10,0,10)
h_evtflw.GetXaxis().SetBinLabel(1,'raw')
h_evtflw.GetXaxis().SetBinLabel(2,'N_{jet}==2')
h_evtflw.GetXaxis().SetBinLabel(3,'dijet_pt<60GeV')
h_evtflw.GetXaxis().SetBinLabel(4,'20GeV<dijet_p<60GeV')
h_evtflw.GetXaxis().SetBinLabel(5,'dijet_pz<60GeV')
h_evtflw.GetXaxis().SetBinLabel(6,'60GeV<dijet_m<110GeV')
h_evtflw.GetXaxis().SetBinLabel(7,'90GeV<dijet_e<120GeV')
h_evtflw.GetXaxis().SetBinLabel(8,'100GeV<dijet_rec_m<180GeV')
h_evtflw.GetXaxis().SetBinLabel(9,'dijet_dphi<175')

#root information
m_n_lepton=array('i',[0])
m_n_neutral=array('i',[0])
m_Neutral_PID=array('i',[0])		
m_sum_p_neutral=array('f',4*[-99]) 
m_sum_p_photon=array('f',4*[-99])
m_e_photon=array('f',[0])
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
m_sum_pt_photon=array('f',[0])
m_pt_dilepton=array('f',[0])
m_pt_leptonm=array('f',[0])
m_pt_leptonp=array('f',[0])
m_e_leptonm=array('f',[0])
m_e_leptonp=array('f',[0])
m_pz_dilepton=array('f',[0])
m_pz_leptonm=array('f',[0])
m_pz_leptonp=array('f',[0])
m_n_charged=array('i',[0])
m_n_gamma=array('i',[0])
m_n_leptonp=array('i',[0])
m_n_lepton=array('i',[0])
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
m_miss_m=array('f',[0])
m_miss_e=array('f',[0])

m_miss_p=array('f',[0])
m_p_dimu=array('f',[0])
m_p_recoil=array('f',[0])

m_e_other=array('f',[0])
m_m_visible=array('f',[0])
m_e_dimu=array('f',[0])
m_e_recoil=array('f',[0])
m_mine_lepton=array('f',[0])
m_maxe_lepton=array('f',[0])

m_minp_lepton=array('f',4*[-99])
m_maxp_lepton=array('f',4*[-99])


m_event=array('i',[0])
m_n_jet=array('i',[0])
m_jet_m=ROOT.std.vector(float)()
m_jet_p=ROOT.std.vector(float)()
m_jet_pt=ROOT.std.vector(float)() 
m_jet_pz=ROOT.std.vector(float)()
m_jet_e=ROOT.std.vector(float)()

m_jet_phi=ROOT.std.vector(float)()
m_jet_theta=ROOT.std.vector(float)()
 
m_dijet_e=ROOT.std.vector(float)()
m_dijet_p=ROOT.std.vector(float)()
m_dijet_pt=ROOT.std.vector(float)()
m_dijet_pz=ROOT.std.vector(float)()
#m_dijet_m=ROOT.std.vector(float)()
#m_dijet_rec_m=ROOT.std.vector(float)()
m_dijet_dphi=ROOT.std.vector(float)()
m_dijet_dang=ROOT.std.vector(float)()
m_dijet_m=array('f',[0])
m_dijet_rec_m=array('f',[0])

#New Branch

m_miss_phi=array('f',[0])   
m_miss_Et=array('f',[0])	   
m_miss_phi2=array('f',[0])
m_n_Muon=array('i',[0])
m_n_Electron=array('i',[0])
    
m_maxpx_muon=array('f',[0]) 
m_maxpy_muon=array('f',[0]) 
m_maxpz_muon=array('f',[0]) 
m_maxpe_muon=array('f',[0]) 
m_minpx_muon=array('f',[0]) 
m_minpy_muon=array('f',[0]) 
m_minpz_muon=array('f',[0]) 
m_minpe_muon=array('f',[0]) 

m_maxpx_electron=array('f',[0]) 
m_maxpy_electron=array('f',[0]) 
m_maxpz_electron=array('f',[0]) 
m_maxpe_electron=array('f',[0]) 

m_minpx_electron=array('f',[0]) 
m_minpy_electron=array('f',[0]) 
m_minpz_electron=array('f',[0]) 
m_minpe_electron=array('f',[0]) 

m_minangle_mujet=array('f',[0])
m_minphi_mujet=array('f',[0])
m_maxangle_mujet=array('f',[0])
m_maxphi_mujet=array('f',[0])
m_minangle_ejet=array('f',[0])
m_minphi_ejet=array('f',[0])
m_maxangle_ejet=array('f',[0])
m_maxphi_ejet=array('f',[0])


m_px_muon=ROOT.std.vector(float)()
m_py_muon=ROOT.std.vector(float)()
m_pz_muon=ROOT.std.vector(float)()
m_pe_muon=ROOT.std.vector(float)()

m_px_electron=ROOT.std.vector(float)()
m_py_electron=ROOT.std.vector(float)()
m_pz_electron=ROOT.std.vector(float)()
m_pe_electron=ROOT.std.vector(float)()

#MC information
m_mc_lepton_minus_id=array('i',[0])
m_mc_lepton_plus_id=array('i',[0])		
m_mc_init_n_lepton_plus=array('i',[0])
m_mc_init_n_lepton_minus=array('i',[0])		
m_mc_init_leptonp_e=array('d',[0])
m_mc_init_leptonp_p=array('d',[0])
m_mc_init_leptonp_pt=array('d',[0])
m_mc_init_leptonp_pz=array('d',[0])
m_mc_init_leptonp_phi=array('d',[0])
m_mc_init_leptonp_theta=array('d',[0])		
m_mc_init_leptonm_e=array('d',[0])
m_mc_init_leptonm_p=array('d',[0])
m_mc_init_leptonm_pt=array('d',[0])
m_mc_init_leptonm_pz=array('d',[0])
m_mc_init_leptonm_phi=array('d',[0])
m_mc_init_leptonm_theta=array('d',[0])		
m_mc_init_dilepton_m=array('d',[0])
m_mc_init_dilepton_e=array('d',[0])
m_mc_init_dilepton_p=array('d',[0])
m_mc_init_dilepton_pt=array('d',[0])
m_mc_init_dilepton_pz=array('d',[0])
m_mc_init_dilepton_rec_m=array('d',[0])
m_mc_init_dilepton_dphi=array('d',[0])
m_mc_init_dilepton_dang=array('d',[0])		
m_mc_init_n_photon=array('i',[0])
m_mc_higgs_m=array('d',[0])
m_mc_higgs_e=array('d',[0])
m_mc_higgs_rec_m=array('d',[0])
m_mc_higgs_decay_type=array('i',[0])		
m_mc_n_Zboson=array('i',[0])		
m_mc_zw1_m=array('d',[0])
m_mc_zw1_p=array('d',[0])
m_mc_zw1_pt=array('d',[0])
m_mc_zw1_e=array('d',[0])
m_mc_zw1_rec_m=array('d',[0])
m_mc_zw2_m=array('d',[0])
m_mc_zw2_p=array('d',[0])
m_mc_zw2_pt=array('d',[0])
m_mc_zw2_e=array('d',[0])
m_mc_zw2_rec_m=array('d',[0])
m_mc_h2gaugeboson_flag=array('i',[0])  		
m_mc_zw1zw2_m=array('d',[0])
m_mc_zw1zw2_e=array('d',[0])
m_mc_zw1zw2_rec_m=array('d',[0])
m_mc_zz_flag=array('i',[0])
m_mc_ww_flag=array('i',[0])

m_mc_init_photon_e=ROOT.std.vector(float)()
m_mc_init_photon_p=ROOT.std.vector(float)()
m_mc_init_photon_pt=ROOT.std.vector(float)()
m_mc_init_photon_pz=ROOT.std.vector(float)()
m_mc_init_photon_phi=ROOT.std.vector(float)()
m_mc_init_photon_theta=ROOT.std.vector(float)()

m_mc_z1_daughter_pid=ROOT.std.vector(float)()
m_mc_z2_daughter_pid=ROOT.std.vector(float)()
m_mc_pdgid=ROOT.std.vector(float)()
m_mc_init_pdgid=ROOT.std.vector(float)()
m_mc_w1_daughter_pid=ROOT.std.vector(float)()
m_mc_w2_daughter_pid=ROOT.std.vector(float)() 
m_mc_higgs_daughter_pdgid=ROOT.std.vector(float)()
#tau information 
_nTau=array('i',[0])
_nTauP=array('i',[0])
_nTauM=array('i',[0])
_fakeTau=array('i',[0])
_totalJet=array('i',[0])

_visEp=array('f',[0])
_visEm=array('f',[0])

_invMp=array('f',[0])
_invMm=array('f',[0])

_evtN=array('i',[0])
_TauTauImpact=array('f',[0])
_TauTauD0=array('f',[0])
_TauTauZ0=array('f',[0])
_tauP_impact=array('f',[0])
_tauM_impact=array('f',[0])

_RecoilM=array('f',[0])
_qqRecoilM=array('f',[0])
_TauTauM=array('f',[0])
_qqM=array('f',[0])
_TotalEvtEn=array('f',[0])

def main():
    args=sys.argv[1:]
    infile=args[0]
    outfile=args[1]
    processname=args[2]
    print processname
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
    IntLum=5600
    table = open(table_list , 'r' )
    cross_section=0.
    for s_line in table :
        if not s_line.startswith('#'):
            l = [x.strip() for x in s_line.split(',')] 
            process=l[0]            
            if processname == process:
                cross_section=l[2]
    if processname=="e2E2h_inv":
        ffH_cross=6.77
        br_Hinv=0.5		
        weight=IntLum*ffH_cross*br_Hinv/event_gen
    elif processname=="eeh_inv":
        ffH_cross=7.04
        br_Hinv=0.5		
        weight=IntLum*ffH_cross*br_Hinv/event_gen
    elif processname=="qqh_inv":
        ffH_cross=136.81
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
    h =[0]*100
    f = ROOT.TFile(infile)
    h[1] = f.Get('before_cut_n_neutral')
    h[2] = f.Get('before_cut_dijet_pt')
    h[3] = f.Get('before_cut_TauTauM')
    h[4] = f.Get('before_cut_dijet_dang')
    h[5] = f.Get('before_cut_dijet_dphi')
    h[6] = f.Get('before_cut_dijet_e')
    h[7] = f.Get('before_cut_dijet_m')
    h[8] = f.Get('before_cut_m_dijet_rec_m')
    h[9] = f.Get('before_cut_dijet_p')
    h[10] = f.Get('before_cut_cos_miss')
    h[11] = f.Get('before_cut_vis')
    #after first cut
    h[12] = f.Get('after_first_cut_n_neutral')
    h[13] = f.Get('after_first_cut_dijet_pt')
    h[14] = f.Get('after_first_cut_TauTauM')
    h[15] = f.Get('after_first_cut_dijet_dang')
    h[16] = f.Get('after_first_cut_dijet_dphi')
    h[17] = f.Get('after_first_cut_dijet_e')
    h[18] = f.Get('after_first_cut_dijet_m')
    h[19] = f.Get('after_first_cut_m_dijet_rec_m')
    h[20] = f.Get('after_first_cut_dijet_p')
    h[21] = f.Get('after_first_cut_cos_miss')
    h[22] = f.Get('after_first_cut_vis')
    #after second cut 
    h[23] = f.Get('after_second_cut_n_neutral')
    h[24] = f.Get('after_second_cut_dijet_pt')
    h[25] = f.Get('after_second_cut_TauTauM')
    h[26] = f.Get('after_second_cut_dijet_dang')
    h[27] = f.Get('after_second_cut_dijet_dphi')
    h[28] = f.Get('after_second_cut_dijet_e')
    h[29] = f.Get('after_second_cut_dijet_m')
    h[30] = f.Get('after_second_cut_m_dijet_rec_m')
    h[31] = f.Get('after_second_cut_dijet_p')
    h[32] = f.Get('after_second_cut_cos_miss')
    h[33] = f.Get('after_second_cut_vis')
    #after third cut 
    h[34] = f.Get('after_third_cut_n_neutral')
    h[35] = f.Get('after_third_cut_dijet_pt')
    h[36] = f.Get('after_third_cut_TauTauM')
    h[37] = f.Get('after_third_cut_dijet_dang')
    h[38] = f.Get('after_third_cut_dijet_dphi')
    h[39] = f.Get('after_third_cut_dijet_e')
    h[40] = f.Get('after_third_cut_dijet_m')
    h[41] = f.Get('after_third_cut_m_dijet_rec_m')
    h[42] = f.Get('after_third_cut_dijet_p')
    h[43] = f.Get('after_third_cut_cos_miss')
    h[44] = f.Get('after_third_cut_vis')

    #after fourth cut
    h[45] = f.Get('after_fourth_cut_n_neutral')
    h[46] = f.Get('after_fourth_cut_dijet_pt')
    h[47] = f.Get('after_fourth_cut_TauTauM')
    h[48] = f.Get('after_fourth_cut_dijet_dang')
    h[49] = f.Get('after_fourth_cut_dijet_dphi')
    h[50] = f.Get('after_fourth_cut_dijet_e')
    h[51] = f.Get('after_fourth_cut_dijet_m')
    h[52] = f.Get('after_fourth_cut_m_dijet_rec_m')
    h[53] = f.Get('after_fourth_cut_dijet_p')
    h[54] = f.Get('after_fourth_cut_cos_miss')
    h[55] = f.Get('after_fourth_cut_vis')

    #after fifth cut
    h[56] = f.Get('after_fifth_cut_n_neutral')
    h[57] = f.Get('after_fifth_cut_dijet_pt')
    h[58] = f.Get('after_fifth_cut_TauTauM')
    h[59] = f.Get('after_fifth_cut_dijet_dang')
    h[60] = f.Get('after_fifth_cut_dijet_dphi')
    h[61] = f.Get('after_fifth_cut_dijet_e')
    h[62] = f.Get('after_fifth_cut_dijet_m')
    h[63] = f.Get('after_fifth_cut_m_dijet_rec_m')
    h[64] = f.Get('after_fifth_cut_dijet_p')
    h[65] = f.Get('after_fifth_cut_cos_miss')
    h[66] = f.Get('after_fifth_cut_vis')

    #after sixth cut 
    h[67] = f.Get('after_sixth_cut_n_neutral')
    h[68] = f.Get('after_sixth_cut_dijet_pt')
    h[69] = f.Get('after_sixth_cut_TauTauM')
    h[70] = f.Get('after_sixth_cut_dijet_dang')
    h[71] = f.Get('after_sixth_cut_dijet_dphi')
    h[72] = f.Get('after_sixth_cut_dijet_e')
    h[73] = f.Get('after_sixth_cut_dijet_m')
    h[74] = f.Get('after_sixth_cut_m_dijet_rec_m')
    h[75] = f.Get('after_sixth_cut_dijet_p')
    h[76] = f.Get('after_sixth_cut_cos_miss')
    h[77] = f.Get('after_sixth_cut_vis') 
    #after seventh cut 
    h[78] = f.Get('after_seventh_cut_n_neutral')
    h[79] = f.Get('after_seventh_cut_dijet_pt')
    h[80] = f.Get('after_seventh_cut_TauTauM')
    h[81] = f.Get('after_seventh_cut_dijet_dang')
    h[82] = f.Get('after_seventh_cut_dijet_dphi')
    h[83] = f.Get('after_seventh_cut_dijet_e')
    h[84] = f.Get('after_seventh_cut_dijet_m')
    h[85] = f.Get('after_seventh_cut_m_dijet_rec_m')
    h[86] = f.Get('after_seventh_cut_dijet_p')
    h[87] = f.Get('after_seventh_cut_cos_miss')
    h[88] = f.Get('after_seventh_cut_vis')
      
    #after all cut
    h[89] = f.Get('after_cut_n_neutral')
    h[90] = f.Get('after_cut_dijet_pt')
    h[91] = f.Get('after_cut_TauTauM')
    h[92] = f.Get('after_cut_dijet_dang')
    h[93] = f.Get('after_cut_dijet_dphi')
    h[94] = f.Get('after_cut_dijet_e')
    h[95] = f.Get('after_cut_dijet_m') 
    h[96] = f.Get('after_cut_m_dijet_rec_m')
    h[97] = f.Get('after_cut_dijet_p')
    h[98] = f.Get('after_cut_cos_miss')
    h[99] = f.Get('after_cut_vis')



    for i in range(1,100):
        h[i].Scale(weight)

    fin=ROOT.TFile(infile)
    t_in=fin.Get('tree')
    entries=t_in.GetEntriesFast()
    t_in.SetBranchAddress('m_event',m_event)
    t_in.SetBranchAddress('m_n_neutral',m_n_neutral)
    t_in.SetBranchAddress('m_Neutral_PID',m_Neutral_PID)
    t_in.SetBranchAddress('m_sum_p_neutral',m_sum_p_neutral)
    t_in.SetBranchAddress('m_sum_p_photon',m_sum_p_photon)
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
    t_in.SetBranchAddress('m_sum_pt_photon',m_sum_pt_photon)
    t_in.SetBranchAddress('m_pt_dilepton',m_pt_dilepton)
    t_in.SetBranchAddress('m_n_lepton',m_n_lepton)
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
    t_in.SetBranchAddress('m_miss_m',m_miss_m)
    t_in.SetBranchAddress('m_miss_e',m_miss_e)   

    t_in.SetBranchAddress('m_e_other',m_e_other)
    t_in.SetBranchAddress('m_m_visible',m_m_visible)
    t_in.SetBranchAddress('m_e_dimu',m_e_dimu)
    t_in.SetBranchAddress('m_e_recoil',m_e_recoil)
    t_in.SetBranchAddress('m_mine_lepton',m_mine_lepton)
    t_in.SetBranchAddress('m_maxe_lepton',m_maxe_lepton)
    t_in.SetBranchAddress('m_minp_lepton',m_minp_lepton)
    t_in.SetBranchAddress('m_maxp_lepton',m_maxp_lepton)
#New branch about qqH
    t_in.SetBranchAddress('m_miss_p',m_miss_p)
    t_in.SetBranchAddress('m_p_dimu',m_p_dimu)
    t_in.SetBranchAddress('m_p_recoil',m_p_recoil)

    t_in.SetBranchAddress("m_miss_phi",  m_miss_phi)
    t_in.SetBranchAddress("m_miss_Et",  m_miss_Et)
    t_in.SetBranchAddress("m_miss_phi2",  m_miss_phi2)
    t_in.SetBranchAddress("m_n_Muon",  m_n_Muon)
    t_in.SetBranchAddress("m_n_Electron",  m_n_Electron) 
    t_in.SetBranchAddress("m_px_muon", m_px_muon)
    t_in.SetBranchAddress("m_py_muon", m_py_muon)
    t_in.SetBranchAddress("m_pz_muon", m_pz_muon)
    t_in.SetBranchAddress("m_pe_muon", m_pe_muon)
    t_in.SetBranchAddress("m_px_electron", m_px_electron)
    t_in.SetBranchAddress("m_py_electron", m_py_electron)
    t_in.SetBranchAddress("m_pz_electron", m_pz_electron)
    t_in.SetBranchAddress("m_pe_electron", m_pe_electron)
    t_in.SetBranchAddress("m_maxpx_muon",  m_maxpx_muon)
    t_in.SetBranchAddress("m_maxpy_muon",  m_maxpy_muon)
    t_in.SetBranchAddress("m_maxpz_muon",  m_maxpz_muon)
    t_in.SetBranchAddress("m_maxpe_muon",  m_maxpe_muon)
    t_in.SetBranchAddress("m_minpx_muon",  m_minpx_muon)
    t_in.SetBranchAddress("m_minpy_muon",  m_minpy_muon)
    t_in.SetBranchAddress("m_minpz_muon",  m_minpz_muon)
    t_in.SetBranchAddress("m_minpe_muon",  m_minpe_muon)	
    t_in.SetBranchAddress("m_maxpx_electron",  m_maxpx_electron)	
    t_in.SetBranchAddress("m_maxpy_electron",  m_maxpy_electron)
    t_in.SetBranchAddress("m_maxpz_electron",  m_maxpz_electron)
    t_in.SetBranchAddress("m_maxpe_electron",  m_maxpe_electron)
    t_in.SetBranchAddress("m_minpx_electron",  m_minpx_electron)
    t_in.SetBranchAddress("m_minpy_electron",  m_minpy_electron)
    t_in.SetBranchAddress("m_minpz_electron",  m_minpz_electron)
    t_in.SetBranchAddress("m_minpe_electron",  m_minpe_electron)

#JET information
    t_in.SetBranchAddress("m_n_jet",  m_n_jet)

    t_in.SetBranchAddress("jet_m", m_jet_m)
    t_in.SetBranchAddress("jet_p", m_jet_p)
    t_in.SetBranchAddress("jet_pt", m_jet_pt)
    t_in.SetBranchAddress("jet_pz", m_jet_pz)
    t_in.SetBranchAddress("jet_e", m_jet_e)

    t_in.SetBranchAddress("jet_phi", m_jet_phi)
    t_in.SetBranchAddress("jet_theta", m_jet_theta)
    
    t_in.SetBranchAddress("dijet_e", m_dijet_e)
    t_in.SetBranchAddress("dijet_p", m_dijet_p)
    t_in.SetBranchAddress("dijet_pt", m_dijet_pt)
    t_in.SetBranchAddress("dijet_pz", m_dijet_pz)
    t_in.SetBranchAddress("dijet_m", m_dijet_m)
    t_in.SetBranchAddress("dijet_rec_m", m_dijet_rec_m)
    t_in.SetBranchAddress("dijet_dphi", m_dijet_dphi)
    t_in.SetBranchAddress("dijet_dang", m_dijet_dang)

    t_in.SetBranchAddress("m_maxangle_mujet",  m_maxangle_mujet);
    t_in.SetBranchAddress("m_maxphi_mujet",  m_maxphi_mujet);
    t_in.SetBranchAddress("m_maxangle_ejet",  m_maxangle_ejet);
    t_in.SetBranchAddress("m_maxphi_ejet",  m_maxphi_ejet);
    t_in.SetBranchAddress("m_minangle_mujet",  m_minangle_mujet);
    t_in.SetBranchAddress("m_minphi_mujet",  m_minphi_mujet);
    t_in.SetBranchAddress("m_minangle_ejet",  m_minangle_ejet);
    t_in.SetBranchAddress("m_minphi_ejet",  m_minphi_ejet);

    #MC information 
    t_in.SetBranchAddress("mc_pdgid", m_mc_pdgid)
    t_in.SetBranchAddress("mc_init_pdgid", m_mc_init_pdgid)
    
    t_in.SetBranchAddress("mc_lepton_minus_id", m_mc_lepton_minus_id)
    t_in.SetBranchAddress("mc_lepton_plus_id", m_mc_lepton_plus_id)
    
    t_in.SetBranchAddress("mc_init_n_lepton_plus", m_mc_init_n_lepton_plus)
    t_in.SetBranchAddress("mc_init_n_lepton_minus", m_mc_init_n_lepton_minus)
    
    t_in.SetBranchAddress("mc_init_leptonp_e",  m_mc_init_leptonp_e)
    t_in.SetBranchAddress("mc_init_leptonp_p",  m_mc_init_leptonp_p)
    t_in.SetBranchAddress("mc_init_leptonp_pt", m_mc_init_leptonp_pt)
    t_in.SetBranchAddress("mc_init_leptonp_pz", m_mc_init_leptonp_pz)

    t_in.SetBranchAddress("mc_init_leptonp_phi", m_mc_init_leptonp_phi)
    t_in.SetBranchAddress("mc_init_leptonp_theta", m_mc_init_leptonp_theta)
    
    t_in.SetBranchAddress("mc_init_leptonm_e",  m_mc_init_leptonm_e)
    t_in.SetBranchAddress("mc_init_leptonm_p",  m_mc_init_leptonm_p)
    t_in.SetBranchAddress("mc_init_leptonm_pt", m_mc_init_leptonm_pt)
    t_in.SetBranchAddress("mc_init_leptonm_pz", m_mc_init_leptonm_pz)

    t_in.SetBranchAddress("mc_init_leptonm_phi", m_mc_init_leptonm_phi)
    t_in.SetBranchAddress("mc_init_leptonm_theta", m_mc_init_leptonm_theta)
    
    t_in.SetBranchAddress("mc_init_dilepton_m",  m_mc_init_dilepton_m)
    t_in.SetBranchAddress("mc_init_dilepton_e",  m_mc_init_dilepton_e)
    t_in.SetBranchAddress("mc_init_dilepton_p",  m_mc_init_dilepton_p)
    t_in.SetBranchAddress("mc_init_dilepton_pt", m_mc_init_dilepton_pt)
    t_in.SetBranchAddress("mc_init_dilepton_pz", m_mc_init_dilepton_pz)
    t_in.SetBranchAddress("mc_init_dilepton_rec_m", m_mc_init_dilepton_rec_m)
    t_in.SetBranchAddress("mc_init_dilepton_dphi", m_mc_init_dilepton_dphi)
    t_in.SetBranchAddress("mc_init_dilepton_dang", m_mc_init_dilepton_dang)
    
    t_in.SetBranchAddress("mc_init_n_photon", m_mc_init_n_photon)
    t_in.SetBranchAddress("mc_init_photon_e",  m_mc_init_photon_e)
    t_in.SetBranchAddress("mc_init_photon_p",  m_mc_init_photon_p)
    t_in.SetBranchAddress("mc_init_photon_pt",  m_mc_init_photon_pt)
    t_in.SetBranchAddress("mc_init_photon_pz",  m_mc_init_photon_pz)
    t_in.SetBranchAddress("mc_init_photon_phi",  m_mc_init_photon_phi)
    t_in.SetBranchAddress("mc_init_photon_theta",  m_mc_init_photon_theta)

    t_in.SetBranchAddress("mc_higgs_m", m_mc_higgs_m)
    t_in.SetBranchAddress("mc_higgs_e", m_mc_higgs_e)
    t_in.SetBranchAddress("mc_higgs_rec_m", m_mc_higgs_rec_m)
    t_in.SetBranchAddress("mc_higgs_decay_type", m_mc_higgs_decay_type)
    t_in.SetBranchAddress("mc_higgs_daughter_pdgid", m_mc_higgs_daughter_pdgid)
    
    t_in.SetBranchAddress("mc_n_Zboson", m_mc_n_Zboson)
    
    t_in.SetBranchAddress("mc_z1_daughter_pid", m_mc_z1_daughter_pid)
    t_in.SetBranchAddress("mc_z2_daughter_pid", m_mc_z2_daughter_pid)

    t_in.SetBranchAddress("mc_w1_daughter_pid", m_mc_w1_daughter_pid)
    t_in.SetBranchAddress("mc_w2_daughter_pid", m_mc_w2_daughter_pid)
    
    t_in.SetBranchAddress("mc_zw1_m", m_mc_zw1_m)
    t_in.SetBranchAddress("mc_zw1_p", m_mc_zw1_p)
    t_in.SetBranchAddress("mc_zw1_pt", m_mc_zw1_pt)
    t_in.SetBranchAddress("mc_zw1_e", m_mc_zw1_e)
    t_in.SetBranchAddress("mc_zw1_rec_m", m_mc_zw1_rec_m)
    
    t_in.SetBranchAddress("mc_zw2_m", m_mc_zw2_m)
    t_in.SetBranchAddress("mc_zw2_p", m_mc_zw2_p)
    t_in.SetBranchAddress("mc_zw2_pt", m_mc_zw2_pt)
    t_in.SetBranchAddress("mc_zw2_e", m_mc_zw2_e)
    t_in.SetBranchAddress("mc_zw2_rec_m", m_mc_zw2_rec_m)
    
    t_in.SetBranchAddress("mc_zw1zw2_m", m_mc_zw1zw2_m)
    t_in.SetBranchAddress("mc_zw1zw2_e", m_mc_zw1zw2_e)
    t_in.SetBranchAddress("mc_zw1zw2_rec_m", m_mc_zw1zw2_rec_m)
    t_in.SetBranchAddress("mc_zz_flag", m_mc_zz_flag)
    t_in.SetBranchAddress("mc_ww_flag", m_mc_ww_flag)
    t_in.SetBranchAddress("mc_h2gaugeboson_flag", m_mc_h2gaugeboson_flag)
    #tau information
    t_in.SetBranchAddress("nTau", _nTau);
    t_in.SetBranchAddress("nTauP", _nTauP);
    t_in.SetBranchAddress("nTauM", _nTauM);
    t_in.SetBranchAddress("fakeTau", _fakeTau);
    t_in.SetBranchAddress("totalJet", _totalJet);
    t_in.SetBranchAddress("visEp",_visEp);
    t_in.SetBranchAddress("visEm",_visEm);
    t_in.SetBranchAddress("invMp",_invMp);
    t_in.SetBranchAddress("invMm",_invMm);
    t_in.SetBranchAddress("evtN",_evtN);
    t_in.SetBranchAddress("TauTauImpact",_TauTauImpact);
    t_in.SetBranchAddress("TauTauD0",_TauTauD0);
    t_in.SetBranchAddress("TauTauZ0", _TauTauZ0);
    t_in.SetBranchAddress("tauP_impact", _tauP_impact);
    t_in.SetBranchAddress("tauM_impact", _tauM_impact);
    t_in.SetBranchAddress("RecoilM", _RecoilM);
    t_in.SetBranchAddress("qqRecoilM", _qqRecoilM);
    t_in.SetBranchAddress("TauTauM",  _TauTauM);
    t_in.SetBranchAddress("qqM",_qqM);
    t_in.SetBranchAddress("TotalEvtEn",_TotalEvtEn);

    fout=ROOT.TFile(outfile,"RECREATE")
    t_out=ROOT.TTree('tree','tree')


    t_out.Branch('m_event',m_event,'m_event/I') 
    t_out.Branch('m_n_neutral',m_n_neutral,'m_n_neutral/I')
    t_out.Branch('m_Neutral_PID',m_Neutral_PID,'m_Neutral_PID/I')
    t_out.Branch('m_sum_p_neutral',m_sum_p_neutral,'m_sum_p_neutral[4]/F')
    t_out.Branch('m_sum_p_photon',m_sum_p_photon,'m_sum_p_photon[4]/F')
    t_out.Branch('m_e_photon',m_e_photon,'m_e_photon/F')
    t_out.Branch('m_e_other',m_e_other,'m_e_other/F')		
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
    t_out.Branch('m_sum_pt_photon',m_sum_pt_photon,'m_sum_pt_photon/F')
    t_out.Branch('m_pt_dilepton',m_pt_dilepton,'m_pt_dilepton/F')
    t_out.Branch('m_n_lepton',m_n_lepton,'m_n_lepton/F')
    t_out.Branch('m_pt_leptonm',m_pt_leptonm,'m_pt_leptonm/F')
    t_out.Branch('m_pt_leptonp',m_pt_leptonp,'m_pt_leptonp/F')
    t_out.Branch('m_pz_dilepton',m_pz_dilepton,'m_pz_dilepton/F')
    t_out.Branch('m_pz_leptonm',m_pz_leptonm,'m_pz_leptonm/F')
    t_out.Branch('m_pz_leptonp',m_pz_leptonp,'m_pz_leptonp/F')
    t_out.Branch('m_e_leptonm',m_e_leptonm,'m_e_leptonm/F')
    t_out.Branch('m_e_leptonp',m_e_leptonp,'m_e_leptonp/F')
    t_out.Branch('m_n_charged',m_n_charged,'m_n_charged/I')
    t_out.Branch('m_n_gamma',m_n_gamma,'m_n_gamma/I')
    t_out.Branch('m_n_leptonp',m_n_leptonp,'m_n_leptonp/I')
    t_out.Branch('m_n_leptonm',m_n_leptonm,'m_n_leptonm/I')
    t_out.Branch('m_n_lepton',m_n_lepton,'m_n_lepton/I')
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
    t_out.Branch('m_miss_m',m_miss_m,'m_miss_m/F')
    t_out.Branch('m_miss_e',m_miss_e,'m_miss_e/F')
    t_out.Branch('m_m_visible',m_m_visible,'m_m_visible/F')  
    t_out.Branch('m_e_dimu',m_e_dimu,'m_e_dimu/F')
    t_out.Branch('m_e_recoil',m_e_recoil,'m_e_recoil/F') 

    t_out.Branch("m_mine_lepton",  m_mine_lepton,  "m_mine_lepton/F")
    t_out.Branch("m_maxe_lepton",  m_maxe_lepton,  "m_maxe_lepton/F")


    t_out.Branch("m_minp_lepton",  m_minp_lepton,  "m_minp_lepton[4]/F")
    t_out.Branch("m_maxp_lepton",  m_maxp_lepton,  "m_maxp_lepton[4]/F")
    

    t_out.Branch("m_maxangle_mujet",  m_maxangle_mujet,  "m_maxangle_mujet/F");
    t_out.Branch("m_maxphi_mujet",  m_maxphi_mujet,  "m_maxphi_mujet/F");
    t_out.Branch("m_maxangle_ejet",  m_maxangle_ejet,  "m_maxangle_ejet/F");
    t_out.Branch("m_maxphi_ejet",  m_maxphi_ejet,  "m_maxphi_ejet/F");

    t_out.Branch("m_minangle_mujet",  m_minangle_mujet,  "m_minangle_mujet/F");
    t_out.Branch("m_minphi_mujet",  m_minphi_mujet,  "m_minphi_mujet/F");
    t_out.Branch("m_minangle_ejet",  m_minangle_ejet,  "m_minangle_ejet/F");
    t_out.Branch("m_minphi_ejet",  m_minphi_ejet,  "m_minphi_ejet/F");

    t_out.Branch("m_n_jet",  m_n_jet,  "m_n_jet/I")

    t_out.Branch("jet_m", m_jet_m)
    t_out.Branch("jet_p", m_jet_p)
    t_out.Branch("jet_pt", m_jet_pt)
    t_out.Branch("jet_pz", m_jet_pz)
    t_out.Branch("jet_e", m_jet_e)

    t_out.Branch("jet_phi", m_jet_phi)
    t_out.Branch("jet_theta", m_jet_theta)
    
    t_out.Branch("dijet_e", m_dijet_e)
    t_out.Branch("dijet_p", m_dijet_p)
    t_out.Branch("dijet_pt", m_dijet_pt)
    t_out.Branch("dijet_pz", m_dijet_pz)
    t_out.Branch("dijet_m", m_dijet_m,'dijet_m/F')
    t_out.Branch("dijet_rec_m", m_dijet_rec_m,'dijet_rec_m/F')
    t_out.Branch("dijet_dphi", m_dijet_dphi)
    t_out.Branch("dijet_dang", m_dijet_dang) 

#New branch about qqH

    t_out.Branch("m_miss_phi",  m_miss_phi,  "m_miss_phi/F")

    t_out.Branch("m_miss_Et",  m_miss_Et,  "m_miss_Et/F")
    t_out.Branch("m_miss_phi2",  m_miss_phi2,  "m_miss_phi2/F")

    t_out.Branch("m_n_Muon",  m_n_Muon,  "m_n_Muon/I")
    t_out.Branch("m_n_Electron",  m_n_Electron,  "m_n_Electron/I") 

    t_out.Branch("m_px_muon", m_px_muon)
    t_out.Branch("m_py_muon", m_py_muon)
    t_out.Branch("m_pz_muon", m_pz_muon)
    t_out.Branch("m_pe_muon", m_pe_muon)
    t_out.Branch("m_px_electron", m_px_electron)
    t_out.Branch("m_py_electron", m_py_electron)
    t_out.Branch("m_pz_electron", m_pz_electron)
    t_out.Branch("m_pe_electron", m_pe_electron)

    t_out.Branch("m_maxpx_muon",  m_maxpx_muon,  "m_maxpx_muon/F")
    t_out.Branch("m_maxpy_muon",  m_maxpy_muon,  "m_maxpy_muon/F")
    t_out.Branch("m_maxpz_muon",  m_maxpz_muon,  "m_maxpz_muon/F")
    t_out.Branch("m_maxpe_muon",  m_maxpe_muon,  "m_maxpe_muon/F")

    t_out.Branch("m_minpx_muon",  m_minpx_muon,  "m_minpx_muon/F")
    t_out.Branch("m_minpy_muon",  m_minpy_muon,  "m_minpy_muon/F")
    t_out.Branch("m_minpz_muon",  m_minpz_muon,  "m_minpz_muon/F")
    t_out.Branch("m_minpe_muon",  m_minpe_muon,  "m_minpe_muon/F")	

    t_out.Branch("m_maxpx_electron",  m_maxpx_electron,  "m_maxpx_electron/F")	
    t_out.Branch("m_maxpy_electron",  m_maxpy_electron,  "m_maxpy_electron/F")
    t_out.Branch("m_maxpz_electron",  m_maxpz_electron,  "m_maxpz_electron/F")
    t_out.Branch("m_maxpe_electron",  m_maxpe_electron,  "m_maxpe_electron/F")

    t_out.Branch("m_minpx_electron",  m_minpx_electron,  "m_minpx_electron/F")
    t_out.Branch("m_minpy_electron",  m_minpy_electron,  "m_minpy_electron/F")
    t_out.Branch("m_minpz_electron",  m_minpz_electron,  "m_minpz_electron/F")
    t_out.Branch("m_minpe_electron",  m_minpe_electron,  "m_minpe_electron/F") 


    t_out.Branch('m_miss_p',m_miss_p,'m_miss_p/F')
    t_out.Branch('m_p_dimu',m_p_dimu,'m_p_dimu/F')
    t_out.Branch('m_p_recoil',m_p_recoil,'m_p_recoil/F')  
#Mc information
    t_out.Branch("mc_pdgid", m_mc_pdgid)
    t_out.Branch("mc_init_pdgid", m_mc_init_pdgid)
    
    t_out.Branch("mc_lepton_minus_id", m_mc_lepton_minus_id, "mc_lepton_minus_id/I")
    t_out.Branch("mc_lepton_plus_id", m_mc_lepton_plus_id, "mc_lepton_plus_id/I")
    
    t_out.Branch("mc_init_n_lepton_plus", m_mc_init_n_lepton_plus,  "mc_init_n_lepton_plus/I")
    t_out.Branch("mc_init_n_lepton_minus", m_mc_init_n_lepton_minus,  "mc_init_n_lepton_minus/I")
    
    t_out.Branch("mc_init_leptonp_e",  m_mc_init_leptonp_e,   "mc_init_leptonp_e/D")
    t_out.Branch("mc_init_leptonp_p",  m_mc_init_leptonp_p,   "mc_init_leptonp_p/D")
    t_out.Branch("mc_init_leptonp_pt", m_mc_init_leptonp_pt,  "mc_init_leptonp_pt/D")
    t_out.Branch("mc_init_leptonp_pz", m_mc_init_leptonp_pz,  "mc_init_leptonp_pz/D")

    t_out.Branch("mc_init_leptonp_phi", m_mc_init_leptonp_phi,  "mc_init_leptonp_phi/D")
    t_out.Branch("mc_init_leptonp_theta", m_mc_init_leptonp_theta,  "mc_init_leptonp_theta/D")
    
    t_out.Branch("mc_init_leptonm_e",  m_mc_init_leptonm_e,   "mc_init_leptonm_e/D")
    t_out.Branch("mc_init_leptonm_p",  m_mc_init_leptonm_p,   "mc_init_leptonm_p/D")
    t_out.Branch("mc_init_leptonm_pt", m_mc_init_leptonm_pt,  "mc_init_leptonm_pt/D")
    t_out.Branch("mc_init_leptonm_pz", m_mc_init_leptonm_pz,  "mc_init_leptonm_pz/D")

    t_out.Branch("mc_init_leptonm_phi", m_mc_init_leptonm_phi,  "mc_init_leptonm_phi/D")
    t_out.Branch("mc_init_leptonm_theta", m_mc_init_leptonm_theta,  "mc_init_leptonm_theta/D")
    
    t_out.Branch("mc_init_dilepton_m",  m_mc_init_dilepton_m,   "mc_init_dilepton_m/D")
    t_out.Branch("mc_init_dilepton_e",  m_mc_init_dilepton_e,   "mc_init_dilepton_e/D")
    t_out.Branch("mc_init_dilepton_p",  m_mc_init_dilepton_p,   "mc_init_dilepton_p/D")
    t_out.Branch("mc_init_dilepton_pt", m_mc_init_dilepton_pt,  "mc_init_dilepton_pt/D")
    t_out.Branch("mc_init_dilepton_pz", m_mc_init_dilepton_pz,  "mc_init_dilepton_pz/D")
    t_out.Branch("mc_init_dilepton_rec_m", m_mc_init_dilepton_rec_m,  "mc_init_dilepton_rec_m/D")
    t_out.Branch("mc_init_dilepton_dphi", m_mc_init_dilepton_dphi,  "mc_init_dilepton_dphi/D")
    t_out.Branch("mc_init_dilepton_dang", m_mc_init_dilepton_dang,  "mc_init_dilepton_dang/D")
    
    t_out.Branch("mc_init_n_photon", m_mc_init_n_photon,  "mc_init_n_photon/I")
    t_out.Branch("mc_init_photon_e",  m_mc_init_photon_e)
    t_out.Branch("mc_init_photon_p",  m_mc_init_photon_p)
    t_out.Branch("mc_init_photon_pt",  m_mc_init_photon_pt)
    t_out.Branch("mc_init_photon_pz",  m_mc_init_photon_pz)
    t_out.Branch("mc_init_photon_phi",  m_mc_init_photon_phi)
    t_out.Branch("mc_init_photon_theta",  m_mc_init_photon_theta)

    t_out.Branch("mc_higgs_m", m_mc_higgs_m, "mc_higgs_m/D")
    t_out.Branch("mc_higgs_e", m_mc_higgs_e, "mc_higgs_e/D")
    t_out.Branch("mc_higgs_rec_m", m_mc_higgs_rec_m, "mc_higgs_rec_m/D")
    t_out.Branch("mc_higgs_decay_type", m_mc_higgs_decay_type, "mc_higgs_decay_type/I")
    t_out.Branch("mc_higgs_daughter_pdgid", m_mc_higgs_daughter_pdgid)
    
    t_out.Branch("mc_n_Zboson", m_mc_n_Zboson, "mc_n_Zboson/I")
    
    t_out.Branch("mc_z1_daughter_pid", m_mc_z1_daughter_pid)
    t_out.Branch("mc_z2_daughter_pid", m_mc_z2_daughter_pid)

    t_out.Branch("mc_w1_daughter_pid", m_mc_w1_daughter_pid)
    t_out.Branch("mc_w2_daughter_pid", m_mc_w2_daughter_pid)
    
    t_out.Branch("mc_zw1_m", m_mc_zw1_m, "mc_zw1_m/D")
    t_out.Branch("mc_zw1_p", m_mc_zw1_p, "mc_zw1_p/D")
    t_out.Branch("mc_zw1_pt", m_mc_zw1_pt, "mc_zw1_pt/D")
    t_out.Branch("mc_zw1_e", m_mc_zw1_e, "mc_zw1_e/D")
    t_out.Branch("mc_zw1_rec_m", m_mc_zw1_rec_m, "mc_zw1_rec_m/D")
    
    t_out.Branch("mc_zw2_m", m_mc_zw2_m, "mc_zw2_m/D")
    t_out.Branch("mc_zw2_p", m_mc_zw2_p, "mc_zw2_p/D")
    t_out.Branch("mc_zw2_pt", m_mc_zw2_pt, "mc_zw2_pt/D")
    t_out.Branch("mc_zw2_e", m_mc_zw2_e, "mc_zw2_e/D")
    t_out.Branch("mc_zw2_rec_m", m_mc_zw2_rec_m, "mc_zw2_rec_m/D")
    
    t_out.Branch("mc_zw1zw2_m", m_mc_zw1zw2_m, "mc_zw1zw2_m/D")
    t_out.Branch("mc_zw1zw2_e", m_mc_zw1zw2_e, "mc_zw1zw2_e/D")
    t_out.Branch("mc_zw1zw2_rec_m", m_mc_zw1zw2_rec_m, "mc_zw1zw2_rec_m/D")
    t_out.Branch("mc_zz_flag", m_mc_zz_flag, "mc_zz_flag/I")
    t_out.Branch("mc_ww_flag", m_mc_ww_flag, "mc_ww_flag/I")
    t_out.Branch("mc_h2gaugeboson_flag", m_mc_h2gaugeboson_flag, "mc_h2gaugeboson_flag/I")
    #tau information 
    t_out.Branch("nTau", _nTau, "nTau/I");
    t_out.Branch("nTauP", _nTauP, "nTauP/I");
    t_out.Branch("nTauM", _nTauM,"nTauM/I");
    t_out.Branch("fakeTau", _fakeTau, "fakeTau/I");
    t_out.Branch("totalJet", _totalJet, "totalJet/I");

    t_out.Branch("visEp",_visEp,"visEp/F");
    t_out.Branch("visEm",_visEm, "visEm/F");

    t_out.Branch("invMp",_invMp,"invMp/F");
    t_out.Branch("invMm",_invMm,"invMm/F");

    t_out.Branch("evtN",_evtN,"evtN/I");
    t_out.Branch("TauTauImpact",_TauTauImpact, "TauTauImpact/F");
    t_out.Branch("TauTauD0",_TauTauD0, "TauTauD0/F");
    t_out.Branch("TauTauZ0", _TauTauZ0, "TauTauZ0/F");
    t_out.Branch("tauP_impact", _tauP_impact, "tauP_impact/F");
    t_out.Branch("tauM_impact", _tauM_impact, "tauM_impact/F");
    t_out.Branch("RecoilM", _RecoilM, "RecoilM/F");
    t_out.Branch("qqRecoilM", _qqRecoilM,"qqRecoilM/F");
    t_out.Branch("TauTauM",  _TauTauM,"TauTauM/F");
    t_out.Branch("qqM",_qqM,"qqM/F");
    t_out.Branch("TotalEvtEn",_TotalEvtEn,"TotalEvtEn/F");
    
    for i in xrange(entries):
        if (weight<1):
            rnd=random.random()
            if (rnd<weight):
                t_in.GetEntry(i)
                t_out.Fill()
        else :
            rnd1=random.random()

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
    for i in xrange(1,100):
        h[i].Write()
    h_evtflw.Write()
    t_out.Write()
    #		Jet  clear()
    m_jet_m.clear()
    m_jet_p.clear()
    m_jet_pt.clear()
    m_jet_pz.clear()
    m_jet_e.clear()
    m_jet_phi.clear()
    m_jet_theta.clear()
    m_dijet_e.clear()
    m_dijet_p.clear()
    m_dijet_pt.clear()
    m_dijet_pz.clear()
#		m_dijet_m.clear()
#		m_dijet_rec_m.clear()
    m_dijet_dphi.clear()
    m_dijet_dang.clear()
    # MC information
    
    m_mc_init_photon_e.clear()
    m_mc_init_photon_p.clear()
    m_mc_init_photon_pt.clear()
    m_mc_init_photon_pz.clear()
    m_mc_init_photon_phi.clear()
    m_mc_init_photon_theta.clear()

    m_mc_z1_daughter_pid.clear()
    m_mc_z2_daughter_pid.clear()
    m_mc_pdgid.clear()
    m_mc_init_pdgid.clear()
    m_mc_w1_daughter_pid.clear()
    m_mc_w2_daughter_pid.clear()
    m_mc_higgs_daughter_pdgid.clear()
    # New Branch about qqH channel 

    m_px_muon.clear()
    m_py_muon.clear()
    m_pz_muon.clear()
    m_pe_muon.clear()

    m_px_electron.clear()
    m_py_electron.clear()
    m_pz_electron.clear()
    m_pe_electron.clear()
    
if __name__ == '__main__':
    main()
