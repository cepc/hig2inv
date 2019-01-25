#!/usr/bin/env python
"""    
Event Selection
 
## Inspired from an event selection script for J/psi->invisible   
"""

__author__ = "Tan Yuhang <tanyuhang@ihep.ac.cn>"
__copyright__ = "Copyright (c) Tanyuhang"
__created__ = "[2018-09-18 ]"

import sys
import os
import math
import ROOT
import numpy as np
from array import array
from progressbar import Bar, Percentage, ProgressBar
import time
from tools import duration, check_outfile_path

class Cutflow(): 
    def __init__(self):
        self.h_evtflw = ROOT.TH1F('hevtflw','eventflow',10,0,10)
        self.h_evtflw.GetXaxis().SetBinLabel(1,'raw')
        self.h_evtflw.GetXaxis().SetBinLabel(2,'N_{e^{+}}==1&&N_{e^{-}}==1')
        self.h_evtflw.GetXaxis().SetBinLabel(3,'120GeV/c^{2}<M_{Recoil}<170GeV/c^{2}')
        self.h_evtflw.GetXaxis().SetBinLabel(4,'71GeV/c^{2}<M_{e^{+}e^{-}}<99GeV/c^{2}')
        self.h_evtflw.GetXaxis().SetBinLabel(5,'10GeV/c<P_{t}^{e^{+}e^{-}}<55GeV')
        self.h_evtflw.GetXaxis().SetBinLabel(6,'#\Delta#phi_{e^{+}e^{-}}<176')
        self.h_evtflw.GetXaxis().SetBinLabel(7,'103GeV<Visible Energy<120GeV')
        self.h_evtflw.GetXaxis().SetBinLabel(8,'1.8<E/P<2.4')
        self.h_evtflw.GetXaxis().SetBinLabel(9,'|P_{z}|<55')

        self.N=[0.,0.,0.,0.,0.,0.,0.,0.,0.,0.] 
        #Before cuts histrogram define
        self.h_before_cut_Pt = ROOT.TH1F('before_cut_Pt','before_cut_P_{t}^{e^{+}e^{-}}',180,0,90)
        self.h_before_cut_Pz = ROOT.TH1F('before_cut_Pz','before_cut_|P_{z}^{e^{+}e^{-}}|',360,-90,90)
        self.h_before_cut_theta = ROOT.TH1F('before_cut_theta','#phi_{e^{+}e^{-}}',400,0,200)
        self.h_before_cut_vis = ROOT.TH1F('before_cut_vis','before_cut_Visible Energy',500,0,250)
        self.h_before_cut_Mmumu= ROOT.TH1F('before_cut_Mmumu','before_cut_M_{e^{+}e^{-}}',300,0,150)
        self.h_before_cut_Mrecoil = ROOT.TH1F('before_cut_Mrecoil','before_cut_M_{Recoil}',140,100,170)
        self.h_before_cut_ep = ROOT.TH1F('before_cut_ep','before_cut_ep',300,1,4)
#        self.h_before_cut_costhem= ROOT.TH1F('before_cut_costhem','before_cut_costhem',60,-1,1)
#        self.h_before_cut_costhep= ROOT.TH1F('before_cut_costhep','before_cut_costhep',60,-1,1)
        #After first cut
        self.h_after_first_cut_Pt = ROOT.TH1F('after_first_cut_Pt','after_first_cut_P_{t}^{e^{+}e^{-}}',180,0,90)
        self.h_after_first_cut_Pz = ROOT.TH1F('after_first_cut_Pz','after_first_cut_|P_{z}^{e^{+}e^{-}}|',360,-90,90)
        self.h_after_first_cut_theta = ROOT.TH1F('after_first_cut_theta','#phi_{e^{+}e^{-}}',400,0,200)
        self.h_after_first_cut_vis = ROOT.TH1F('after_first_cut_vis','after_first_cut_Visible Energy',500,0,250)
        self.h_after_first_cut_Mmumu= ROOT.TH1F('after_first_cut_Mmumu','after_first_cut_M_{e^{+}e^{-}}',300,0,150)
        self.h_after_first_cut_Mrecoil = ROOT.TH1F('after_first_cut_Mrecoil','after_first_cut_M_{Recoil}',140,100,170)
        self.h_after_first_cut_ep = ROOT.TH1F('after_first_cut_ep','after_first_cut_ep',300,1,4)

        #After second cut
        self.h_after_second_cut_Pt = ROOT.TH1F('after_second_cut_Pt','after_second_cut_P_{t}^{e^{+}e^{-}}',180,0,90)
        self.h_after_second_cut_Pz = ROOT.TH1F('after_second_cut_Pz','after_second_cut_|P_{z}^{e^{+}e^{-}}|',360,-90,90)
        self.h_after_second_cut_theta = ROOT.TH1F('after_second_cut_theta','#phi_{e^{+}e^{-}}',400,0,200)
        self.h_after_second_cut_vis = ROOT.TH1F('after_second_cut_vis','after_second_cut_Visible Energy',500,0,250)
        self.h_after_second_cut_Mmumu= ROOT.TH1F('after_second_cut_Mmumu','after_second_cut_M_{e^{+}e^{-}}',300,0,150)
        self.h_after_second_cut_Mrecoil = ROOT.TH1F('after_second_cut_Mrecoil','after_second_cut_M_{Recoil}',140,100,170)
        self.h_after_second_cut_ep = ROOT.TH1F('after_second_cut_ep','after_second_cut_ep',300,1,4)

        #After third cut
        self.h_after_third_cut_Pt = ROOT.TH1F('after_third_cut_Pt','after_third_cut_P_{t}^{e^{+}e^{-}}',180,0,90)
        self.h_after_third_cut_Pz = ROOT.TH1F('after_third_cut_Pz','after_third_cut_|P_{z}^{e^{+}e^{-}}|',360,-90,90)
        self.h_after_third_cut_theta = ROOT.TH1F('after_third_cut_theta','#phi_{e^{+}e^{-}}',400,0,200)
        self.h_after_third_cut_vis = ROOT.TH1F('after_third_cut_vis','after_third_cut_Visible Energy',500,0,250)
        self.h_after_third_cut_Mmumu= ROOT.TH1F('after_third_cut_Mmumu','after_third_cut_M_{e^{+}e^{-}}',300,0,150)
        self.h_after_third_cut_Mrecoil = ROOT.TH1F('after_third_cut_Mrecoil','after_third_cut_M_{Recoil}',140,100,170)
        self.h_after_third_cut_ep = ROOT.TH1F('after_third_cut_ep','after_third_cut_ep',300,1,4)

        #After fourth cut
        self.h_after_fourth_cut_Pt = ROOT.TH1F('after_fourth_cut_Pt','after_fourth_cut_P_{t}^{e^{+}e^{-}}',180,0,90)
        self.h_after_fourth_cut_Pz = ROOT.TH1F('after_fourth_cut_Pz','after_fourth_cut_|P_{z}^{e^{+}e^{-}}|',360,-90,90)
        self.h_after_fourth_cut_theta = ROOT.TH1F('after_fourth_cut_theta','#phi_{e^{+}e^{-}}',400,0,200)
        self.h_after_fourth_cut_vis = ROOT.TH1F('after_fourth_cut_vis','after_fourth_cut_Visible Energy',500,0,250)
        self.h_after_fourth_cut_Mmumu= ROOT.TH1F('after_fourth_cut_Mmumu','after_fourth_cut_M_{e^{+}e^{-}}',300,0,150)
        self.h_after_fourth_cut_Mrecoil = ROOT.TH1F('after_fourth_cut_Mrecoil','after_fourth_cut_M_{Recoil}',140,100,170)
        self.h_after_fourth_cut_ep = ROOT.TH1F('after_fourth_cut_ep','after_fourth_cut_ep',300,1,4)

        #After fifth cut
        self.h_after_fifth_cut_Pt = ROOT.TH1F('after_fifth_cut_Pt','after_fifth_cut_P_{t}^{e^{+}e^{-}}',180,0,90)
        self.h_after_fifth_cut_Pz = ROOT.TH1F('after_fifth_cut_Pz','after_fifth_cut_|P_{z}^{e^{+}e^{-}}|',360,-90,90)
        self.h_after_fifth_cut_theta = ROOT.TH1F('after_fifth_cut_theta','#phi_{e^{+}e^{-}}',400,0,200)
        self.h_after_fifth_cut_vis = ROOT.TH1F('after_fifth_cut_vis','after_fifth_cut_Visible Energy',500,0,250)
        self.h_after_fifth_cut_Mmumu= ROOT.TH1F('after_fifth_cut_Mmumu','after_fifth_cut_M_{e^{+}e^{-}}',300,0,150)
        self.h_after_fifth_cut_Mrecoil = ROOT.TH1F('after_fifth_cut_Mrecoil','after_fifth_cut_M_{Recoil}',140,100,170)
        self.h_after_fifth_cut_ep = ROOT.TH1F('after_fifth_cut_ep','after_fifth_cut_ep',300,1,4)

        #After sixth cut 
        self.h_after_sixth_cut_Pt = ROOT.TH1F('after_sixth_cut_Pt','after_sixth_cut_P_{t}^{e^{+}e^{-}}',180,0,90)
        self.h_after_sixth_cut_Pz = ROOT.TH1F('after_sixth_cut_Pz','after_sixth_cut_|P_{z}^{e^{+}e^{-}}|',360,-90,90)
        self.h_after_sixth_cut_theta = ROOT.TH1F('after_sixth_cut_theta','#phi_{e^{+}e^{-}}',400,0,200)
        self.h_after_sixth_cut_vis = ROOT.TH1F('after_sixth_cut_vis','after_sixth_cut_Visible Energy',500,0,250)
        self.h_after_sixth_cut_Mmumu= ROOT.TH1F('after_sixth_cut_Mmumu','after_sixth_cut_M_{e^{+}e^{-}}',300,0,150)
        self.h_after_sixth_cut_Mrecoil = ROOT.TH1F('after_sixth_cut_Mrecoil','after_sixth_cut_M_{Recoil}',140,100,170)
        self.h_after_sixth_cut_ep = ROOT.TH1F('after_sixth_cut_ep','after_sixth_cut_ep',300,1,4)

        #After seventh cut
        self.h_after_seventh_cut_Pt = ROOT.TH1F('after_seventh_cut_Pt','after_seventh_cut_P_{t}^{e^{+}e^{-}}',180,0,90)
        self.h_after_seventh_cut_Pz = ROOT.TH1F('after_seventh_cut_Pz','after_seventh_cut_|P_{z}^{e^{+}e^{-}}|',360,-90,90)
        self.h_after_seventh_cut_theta = ROOT.TH1F('after_seventh_cut_theta','#phi_{e^{+}e^{-}}',400,0,200)
        self.h_after_seventh_cut_vis = ROOT.TH1F('after_seventh_cut_vis','after_seventh_cut_Visible Energy',500,0,250)
        self.h_after_seventh_cut_Mmumu= ROOT.TH1F('after_seventh_cut_Mmumu','after_seventh_cut_M_{e^{+}e^{-}}',300,0,150)
        self.h_after_seventh_cut_Mrecoil = ROOT.TH1F('after_seventh_cut_Mrecoil','after_seventh_cut_M_{Recoil}',140,100,170)
        self.h_after_seventh_cut_ep = ROOT.TH1F('after_seventh_cut_ep','after_seventh_cut_ep',300,1,4)       
        #After cut histrogram define

        self.h_after_cut_Pt = ROOT.TH1F('after_cut_Pt','after_cut_P_{t}^{e^{+}e^{-}}',180,0,90)
        self.h_after_cut_Pz = ROOT.TH1F('after_cut_Pz','after_cut_|P_{z}^{e^{+}e^{-}}|',140,-70,70)
        self.h_after_cut_theta = ROOT.TH1F('after_cut_theta','#phi_{e^{+}e^{-}}',180,0,180)
        self.h_after_cut_vis = ROOT.TH1F('after_cut_vis','after_cut_Visible Energy',120,60,120)
        self.h_after_cut_Mmumu= ROOT.TH1F('after_cut_Mmumu','after_cut_M_{e^{+}e^{-}}',60,70,100)
        self.h_after_cut_Mrecoil = ROOT.TH1F('after_cut_Mrecoil','after_cut_M_{Recoil}',130,115,180)
        self.h_after_cut_ep = ROOT.TH1F('after_cut_ep','after_cut_ep',120,1.6,2.8)
#        self.h_after_cut_costhem= ROOT.TH1F('after_cut_costhem','after_cut_costhem',60,-1,1)
#        self.h_after_cut_costhep= ROOT.TH1F('after_cut_costhep','after_cut_costhep',60,-1,1)

        self.m_event=array('i',[0])
        self.m_n_neutral=array('i',[0])
        self.m_Neutral_PID=array('i',[0])		
        self.m_sum_p_neutral=array('f',4*[-99]) 
        self.m_sum_p_photon=array('f',4*[-99])
        self.m_e_photon=array('f',[0])
        self.m_p_leptonp=array('f',4*[-99])
        self.m_p_leptonm=array('f',4*[-99])
        self.m_p_dilepton=array('f',4*[-99])
        self.m_sum_p_charged=array('f',4*[-99])
        self.m_p_Higgsdaughters=array('f',4*[-99])
        self.m_p_Higgsdaughter1=array('f',4*[-99])
        self.m_p_Higgsdaughter2=array('f',4*[-99])
        self.m_p_Zdaughters=array('f',4*[-99])
        self.m_p_Zdaughterp=array('f',4*[-99])
        self.m_p_Zdaughterm=array('f',4*[-99])
        self.m_sum_pt_photon=array('f',[0])
        self.m_pt_dilepton=array('f',[0])
        self.m_pt_leptonm=array('f',[0])
        self.m_pt_leptonp=array('f',[0])
        self.m_e_leptonm=array('f',[0])
        self.m_e_leptonp=array('f',[0])
        self.m_pz_dilepton=array('f',[0])
        self.m_pz_leptonm=array('f',[0])
        self.m_pz_leptonp=array('f',[0])
        self.m_n_charged=array('i',[0])
        self.m_n_gamma=array('i',[0])
        self.m_n_leptonp=array('i',[0])
        self.m_n_leptonm=array('i',[0])
        self.m_n_chargedp=array('i',[0])
        self.m_n_chargedm=array('i',[0])
        self.m_n_Higgsdaughter=array('i',[0])
        self.m_n_neutrino=array('i',[0])
        self.m_m_dimu=array('f',[0])
        self.m_m_recoil=array('f',[0])
        self.m_phi_dilepton_1=array('f',[0])
        self.m_phi_dilepton_2=array('f',[0])
        self.m_cos_miss=array('f',[0])
        self.m_cos_Z=array('f',[0])
        self.m_theta_dilepton=array('f',[0])
        self.m_cos_theta_leptonm=array('f',[0])
        self.m_cos_theta_leptonp=array('f',[0])
        self.m_angle_dilepton=array('f',[0])
        self.m_delta_pt=array('f',[0])
        self.m_energy_neutrino=array('f',[0])
        self.m_p_visible=array('f',4*[-99])
        self.m_energy_visible=array('f',[0])
        self.m_p_visible3=array('f',[0])
        self.m_miss_m=array('f',[0])
        self.m_miss_e=array('f',[0])

        self.m_e_other=array('f',[0])
        self.m_m_visible=array('f',[0])
        self.m_e_dimu=array('f',[0])
        self.m_e_recoil=array('f',[0])
        self.m_mine_lepton=array('f',[0])
        self.m_maxe_lepton=array('f',[0])

        self.m_minp_lepton=array('f',4*[-99])
        self.m_maxp_lepton=array('f',4*[-99])
        self.m_e_ep=array('f',[0])
        self.m_l_ep=array('f',[0])

# MC information 		
        self.m_mc_lepton_minus_id=array('i',[0])
        self.m_mc_lepton_plus_id=array('i',[0])		
        self.m_mc_init_n_lepton_plus=array('i',[0])
        self.m_mc_init_n_lepton_minus=array('i',[0])		
        self.m_mc_init_leptonp_e=array('d',[0])
        self.m_mc_init_leptonp_p=array('d',[0])
        self.m_mc_init_leptonp_pt=array('d',[0])
        self.m_mc_init_leptonp_pz=array('d',[0])
        self.m_mc_init_leptonp_phi=array('d',[0])
        self.m_mc_init_leptonp_theta=array('d',[0])		
        self.m_mc_init_leptonm_e=array('d',[0])
        self.m_mc_init_leptonm_p=array('d',[0])
        self.m_mc_init_leptonm_pt=array('d',[0])
        self.m_mc_init_leptonm_pz=array('d',[0])
        self.m_mc_init_leptonm_phi=array('d',[0])
        self.m_mc_init_leptonm_theta=array('d',[0])		
        self.m_mc_init_dilepton_m=array('d',[0])
        self.m_mc_init_dilepton_e=array('d',[0])
        self.m_mc_init_dilepton_p=array('d',[0])
        self.m_mc_init_dilepton_pt=array('d',[0])
        self.m_mc_init_dilepton_pz=array('d',[0])
        self.m_mc_init_dilepton_rec_m=array('d',[0])
        self.m_mc_init_dilepton_dphi=array('d',[0])
        self.m_mc_init_dilepton_dang=array('d',[0])		
        self.m_mc_init_n_photon=array('i',[0])
        self.m_mc_higgs_m=array('d',[0])
        self.m_mc_higgs_e=array('d',[0])
        self.m_mc_higgs_rec_m=array('d',[0])
        self.m_mc_higgs_decay_type=array('i',[0])		
        self.m_mc_n_Zboson=array('i',[0])		
        self.m_mc_zw1_m=array('d',[0])
        self.m_mc_zw1_p=array('d',[0])
        self.m_mc_zw1_pt=array('d',[0])
        self.m_mc_zw1_e=array('d',[0])
        self.m_mc_zw1_rec_m=array('d',[0])
        self.m_mc_zw2_m=array('d',[0])
        self.m_mc_zw2_p=array('d',[0])
        self.m_mc_zw2_pt=array('d',[0])
        self.m_mc_zw2_e=array('d',[0])
        self.m_mc_zw2_rec_m=array('d',[0])
        self.m_mc_h2gaugeboson_flag=array('i',[0])  		
        self.m_mc_zw1zw2_m=array('d',[0])
        self.m_mc_zw1zw2_e=array('d',[0])
        self.m_mc_zw1zw2_rec_m=array('d',[0])
        self.m_mc_zz_flag=array('i',[0])
        self.m_mc_ww_flag=array('i',[0])

        self.m_mc_init_photon_e=ROOT.std.vector(float)()
        self.m_mc_init_photon_p=ROOT.std.vector(float)()
        self.m_mc_init_photon_pt=ROOT.std.vector(float)()
        self.m_mc_init_photon_pz=ROOT.std.vector(float)()
        self.m_mc_init_photon_phi=ROOT.std.vector(float)()
        self.m_mc_init_photon_theta=ROOT.std.vector(float)()

        self.m_mc_z1_daughter_pid=ROOT.std.vector(float)()
        self.m_mc_z2_daughter_pid=ROOT.std.vector(float)()
        self.m_mc_pdgid=ROOT.std.vector(float)()
        self.m_mc_init_pdgid=ROOT.std.vector(float)()
        self.m_mc_w1_daughter_pid=ROOT.std.vector(float)()
        self.m_mc_w2_daughter_pid=ROOT.std.vector(float)() 
        self.m_mc_higgs_daughter_pdgid=ROOT.std.vector(float)()

    def plot_before_cut(self,t_in):
        m_pp_lepton=math.sqrt(t_in.m_p_dilepton[0]*t_in.m_p_dilepton[0]+t_in.m_p_dilepton[1]*t_in.m_p_dilepton[1]+t_in.m_p_dilepton[2]*t_in.m_p_dilepton[2])
        m_ee_lepton=t_in.m_p_dilepton[3]
        if m_pp_lepton != 0 and abs(t_in.m_p_dilepton[3])<5000:
            m_l_ep=m_ee_lepton/m_pp_lepton
        else:
            m_l_ep=10
#
#        LeptonmP = math.sqrt(t_in.m_p_leptonm[0] * t_in.m_p_leptonm[0] +
#                             t_in.m_p_leptonm[1] * t_in.m_p_leptonm[1] +
#                             t_in.m_p_leptonm[2] * t_in.m_p_leptonm[2])
#        LeptonmPz=t_in.m_p_leptonm[2]
#        if LeptonmP!=0:
#            costheta_leptonm=LeptonmPz/LeptonmP
#        else:
#            costheta_leptonm=-999
# 
#        LeptonpP = math.sqrt(t_in.m_p_leptonp[0] * t_in.m_p_leptonp[0] +
#                             t_in.m_p_leptonp[1] * t_in.m_p_leptonp[1] +
#                             t_in.m_p_leptonp[2] * t_in.m_p_leptonp[2])
#        LeptonpPz=t_in.m_p_leptonp[2]
#        if LeptonpPz!=0:
#            costheta_leptonp=LeptonpPz/LeptonpP
#        else:
#            costheta_leptonp=-999

        self.h_before_cut_Pt.Fill(t_in.m_pt_dilepton) 
        self.h_before_cut_Pz.Fill(t_in.m_p_dilepton[2])
        self.h_before_cut_theta.Fill(t_in.m_phi_dilepton_2)
        self.h_before_cut_vis.Fill(t_in.m_energy_visible)
        self.h_before_cut_Mmumu.Fill(t_in.m_m_dimu)
        self.h_before_cut_Mrecoil.Fill(t_in.m_m_recoil)
        self.h_before_cut_ep.Fill(m_l_ep)
#        self.h_before_cut_costhem.Fill(costheta_leptonm)
#        self.h_before_cut_costhep.Fill(costheta_leptonp)
    #After first cut
    def plot_after_first_cut(self,t_in,m_l_ep):
    
        self.h_after_first_cut_Pt.Fill(t_in.m_pt_dilepton)
        self.h_after_first_cut_Pz.Fill(t_in.m_p_dilepton[2])
        self.h_after_first_cut_theta.Fill(t_in.m_phi_dilepton_2)
        self.h_after_first_cut_vis.Fill(t_in.m_energy_visible)
        self.h_after_first_cut_Mmumu.Fill(t_in.m_m_dimu)
        self.h_after_first_cut_Mrecoil.Fill(t_in.m_m_recoil)
        self.h_after_first_cut_ep.Fill(m_l_ep) 
    #After second cut
    def plot_after_second_cut(self,t_in,m_l_ep):
    
        self.h_after_second_cut_Pt.Fill(t_in.m_pt_dilepton)
        self.h_after_second_cut_Pz.Fill(t_in.m_p_dilepton[2])
        self.h_after_second_cut_theta.Fill(t_in.m_phi_dilepton_2)
        self.h_after_second_cut_vis.Fill(t_in.m_energy_visible)
        self.h_after_second_cut_Mmumu.Fill(t_in.m_m_dimu)
        self.h_after_second_cut_Mrecoil.Fill(t_in.m_m_recoil)
        self.h_after_second_cut_ep.Fill(m_l_ep)
    #After third cut        
    def plot_after_third_cut(self,t_in,m_l_ep):
    
        self.h_after_third_cut_Pt.Fill(t_in.m_pt_dilepton)
        self.h_after_third_cut_Pz.Fill(t_in.m_p_dilepton[2])
        self.h_after_third_cut_theta.Fill(t_in.m_phi_dilepton_2)
        self.h_after_third_cut_vis.Fill(t_in.m_energy_visible)
        self.h_after_third_cut_Mmumu.Fill(t_in.m_m_dimu)
        self.h_after_third_cut_Mrecoil.Fill(t_in.m_m_recoil)
        self.h_after_third_cut_ep.Fill(m_l_ep) 
    #After fourth cut
    def plot_after_fourth_cut(self,t_in,m_l_ep):
    
        self.h_after_fourth_cut_Pt.Fill(t_in.m_pt_dilepton)
        self.h_after_fourth_cut_Pz.Fill(t_in.m_p_dilepton[2])
        self.h_after_fourth_cut_theta.Fill(t_in.m_phi_dilepton_2)
        self.h_after_fourth_cut_vis.Fill(t_in.m_energy_visible)
        self.h_after_fourth_cut_Mmumu.Fill(t_in.m_m_dimu)
        self.h_after_fourth_cut_Mrecoil.Fill(t_in.m_m_recoil)
        self.h_after_fourth_cut_ep.Fill(m_l_ep)
    #After fifth cut
    def plot_after_fifth_cut(self,t_in,m_l_ep):
    
        self.h_after_fifth_cut_Pt.Fill(t_in.m_pt_dilepton)
        self.h_after_fifth_cut_Pz.Fill(t_in.m_p_dilepton[2])
        self.h_after_fifth_cut_theta.Fill(t_in.m_phi_dilepton_2)
        self.h_after_fifth_cut_vis.Fill(t_in.m_energy_visible)
        self.h_after_fifth_cut_Mmumu.Fill(t_in.m_m_dimu)
        self.h_after_fifth_cut_Mrecoil.Fill(t_in.m_m_recoil)
        self.h_after_fifth_cut_ep.Fill(m_l_ep) 
    #After sixth cut
    def plot_after_sixth_cut(self,t_in,m_l_ep):
    
        self.h_after_sixth_cut_Pt.Fill(t_in.m_pt_dilepton)
        self.h_after_sixth_cut_Pz.Fill(t_in.m_p_dilepton[2])
        self.h_after_sixth_cut_theta.Fill(t_in.m_phi_dilepton_2)
        self.h_after_sixth_cut_vis.Fill(t_in.m_energy_visible)
        self.h_after_sixth_cut_Mmumu.Fill(t_in.m_m_dimu)
        self.h_after_sixth_cut_Mrecoil.Fill(t_in.m_m_recoil)
        self.h_after_sixth_cut_ep.Fill(m_l_ep)  
    #After seventh cut
    def plot_after_seventh_cut(self,t_in,m_l_ep):
    
        self.h_after_seventh_cut_Pt.Fill(t_in.m_pt_dilepton)
        self.h_after_seventh_cut_Pz.Fill(t_in.m_p_dilepton[2])
        self.h_after_seventh_cut_theta.Fill(t_in.m_phi_dilepton_2)
        self.h_after_seventh_cut_vis.Fill(t_in.m_energy_visible)
        self.h_after_seventh_cut_Mmumu.Fill(t_in.m_m_dimu)
        self.h_after_seventh_cut_Mrecoil.Fill(t_in.m_m_recoil)
        self.h_after_seventh_cut_ep.Fill(m_l_ep)

    def plot_after_cut(self,t_in,m_l_ep):
#        LeptonmP = math.sqrt(t_in.m_p_leptonm[0] * t_in.m_p_leptonm[0] +
#                             t_in.m_p_leptonm[1] * t_in.m_p_leptonm[1] +
#                             t_in.m_p_leptonm[2] * t_in.m_p_leptonm[2])
#        LeptonmPz=t_in.m_p_leptonm[2]
#        if LeptonmP!=0:
#            costheta_leptonm=LeptonmPz/LeptonmP
#        else:
#            costheta_leptonm=-999
# 
#        LeptonpP = math.sqrt(t_in.m_p_leptonp[0] * t_in.m_p_leptonp[0] +
#                             t_in.m_p_leptonp[1] * t_in.m_p_leptonp[1] +
#                             t_in.m_p_leptonp[2] * t_in.m_p_leptonp[2])
#        LeptonpPz=t_in.m_p_leptonp[2]
#        if LeptonpPz!=0:
#            costheta_leptonp=LeptonpPz/LeptonpP
#        else:
#            costheta_leptonp=-999

        self.h_after_cut_Pt.Fill(t_in.m_pt_dilepton)
        self.h_after_cut_Pz.Fill(t_in.m_p_dilepton[2])
        self.h_after_cut_theta.Fill(t_in.m_phi_dilepton_2)
        self.h_after_cut_vis.Fill(t_in.m_energy_visible)
        self.h_after_cut_Mmumu.Fill(t_in.m_m_dimu)
        self.h_after_cut_Mrecoil.Fill(t_in.m_m_recoil)
        self.h_after_cut_ep.Fill(m_l_ep)
#        self.h_after_cut_costhem.Fill(costheta_leptonm)
#        self.h_after_cut_costhep.Fill(costheta_leptonp)

    def cut(self,t_in,t_out):
        self.N[0]+=1
        self.h_evtflw.Fill(0)
        m_pp_lepton=math.sqrt(t_in.m_p_dilepton[0]*t_in.m_p_dilepton[0]+t_in.m_p_dilepton[1]*t_in.m_p_dilepton[1]+t_in.m_p_dilepton[2]*t_in.m_p_dilepton[2])
        m_ee_lepton=t_in.m_p_dilepton[3]
        if m_pp_lepton != 0 and abs(t_in.m_p_dilepton[3])<5000:
            m_l_ep=m_ee_lepton/m_pp_lepton
        else:
            m_l_ep=10

        if not (t_in.m_n_leptonp==1 and t_in.m_n_leptonm==1):
            return False
        self.N[1]+=1		
        self.h_evtflw.Fill(1)
        self.plot_after_first_cut(t_in,m_l_ep)

        if not (t_in.m_m_recoil>120 and t_in.m_m_recoil<170):
            return False
        self.N[2]+=1
        self.h_evtflw.Fill(2)
        self.plot_after_second_cut(t_in,m_l_ep)

        if not (t_in.m_m_dimu>71 and t_in.m_m_dimu<99):
            return False
        self.N[3]+=1
        self.h_evtflw.Fill(3)
        self.plot_after_third_cut(t_in,m_l_ep)        
#
        if not (t_in.m_pt_dilepton>10 and t_in.m_pt_dilepton<55 ):
            return False
        self.N[4]+=1
        self.h_evtflw.Fill(4)
        self.plot_after_fourth_cut(t_in,m_l_ep)         
#
        if not (t_in.m_phi_dilepton_2<176):
            return False
        self.N[5]+=1
        self.h_evtflw.Fill(5)
        self.plot_after_fifth_cut(t_in,m_l_ep)
#
        if not (t_in.m_energy_visible>103 and t_in.m_energy_visible<120):
            return False
        self.N[6]+=1
        self.h_evtflw.Fill(6)
        self.plot_after_sixth_cut(t_in,m_l_ep)

        if not (m_l_ep<2.4 and m_l_ep>1.8):
            return False  
        self.N[7]+=1
        self.h_evtflw.Fill(7) 
        self.plot_after_seventh_cut(t_in,m_l_ep)

#        if not (abs(t_in.m_p_dilepton[2])<55):
#            return False

#        if not (costheta_leptonm<0.7 and costheta_leptonp>-0.7 ):
#            return False 
        if not (abs(t_in.m_p_dilepton[2])<55 ):
            return False 
        self.N[8]+=1
        self.h_evtflw.Fill(8) 
#        #Plot cuts histrogram after cut
        self.plot_after_cut(t_in,m_l_ep)
#        #Fill root branches after cutting
        self.fill_root(t_in,t_out,m_l_ep)

    def fill_root(self,t_in,t_out,m_l_ep):
        m_pp_photon=math.sqrt(t_in.m_sum_p_photon[0]*t_in.m_sum_p_photon[0]+t_in.m_sum_p_photon[1]*t_in.m_sum_p_photon[1]+t_in.m_sum_p_photon[2]*t_in.m_sum_p_photon[2])
        m_ee_photon=t_in.m_sum_p_photon[3]
        if m_pp_photon != 0 and abs(t_in.m_sum_p_photon[3])<5000:
            m_e_ep=m_ee_photon/m_pp_photon
        else:
            m_e_ep=10
        m_pp_lepton=math.sqrt(t_in.m_p_dilepton[0]*t_in.m_p_dilepton[0]+t_in.m_p_dilepton[1]*t_in.m_p_dilepton[1]+t_in.m_p_dilepton[2]*t_in.m_p_dilepton[2])
        m_ee_lepton=t_in.m_p_dilepton[3]
        if m_pp_lepton != 0 and abs(t_in.m_p_dilepton[3])<5000:
            m_l_ep=m_ee_lepton/m_pp_lepton
        else:
            m_l_ep=10
        LeptonmP = math.sqrt(t_in.m_p_leptonm[0] * t_in.m_p_leptonm[0] +
                             t_in.m_p_leptonm[1] * t_in.m_p_leptonm[1] +
                             t_in.m_p_leptonm[2] * t_in.m_p_leptonm[2])
        LeptonmPz=t_in.m_p_leptonm[2]
        if LeptonmP!=0:
            costheta_leptonm=LeptonmPz/LeptonmP
        else:
            costheta_leptonm=-999
 
        LeptonpP = math.sqrt(t_in.m_p_leptonp[0] * t_in.m_p_leptonp[0] +
                             t_in.m_p_leptonp[1] * t_in.m_p_leptonp[1] +
                             t_in.m_p_leptonp[2] * t_in.m_p_leptonp[2])
        LeptonpPz=t_in.m_p_leptonp[2]
        if LeptonpPz!=0:
            costheta_leptonp=LeptonpPz/LeptonpP
        else:
            costheta_leptonp=-999
        self.m_event[0]=t_in.m_event
        self.m_n_neutral[0]=t_in.m_n_neutral
        self.m_Neutral_PID[0]=t_in.m_Neutral_PID
        self.m_e_other[0]=t_in.m_energy_visible-abs(t_in.m_p_leptonm[3])-abs(t_in.m_p_leptonp[3])
        self.m_e_photon[0]=t_in.m_sum_p_photon[3]
        self.m_sum_pt_photon[0]=t_in.m_sum_pt_photon
        self.m_pt_dilepton[0]=t_in.m_pt_dilepton
        self.m_pt_leptonm[0]=math.sqrt(t_in.m_p_leptonm[0]*t_in.m_p_leptonm[0]+t_in.m_p_leptonm[1]*t_in.m_p_leptonm[1])
        self.m_pt_leptonp[0]=math.sqrt(t_in.m_p_leptonp[0]*t_in.m_p_leptonp[0]+t_in.m_p_leptonp[1]*t_in.m_p_leptonp[1])
        self.m_pz_dilepton[0]=t_in.m_p_dilepton[2]
        self.m_pz_leptonm[0]=t_in.m_p_leptonm[2]
        self.m_pz_leptonp[0]=t_in.m_p_leptonp[2]
        self.m_e_leptonm[0]=t_in.m_p_leptonm[3]
        self.m_e_leptonp[0]=t_in.m_p_leptonp[3]
        self.m_n_charged[0]=t_in.m_n_charged
        self.m_n_gamma[0]=t_in.m_n_gamma
        self.m_n_leptonp[0]=t_in.m_n_leptonp
        self.m_n_leptonm[0]=t_in.m_n_leptonm
        self.m_n_chargedp[0]=t_in.m_n_chargedp
        self.m_n_chargedm[0]=t_in.m_n_chargedm
        self.m_n_Higgsdaughter[0]=t_in.m_n_Higgsdaughter
        self.m_n_neutrino[0]=t_in.m_n_neutrino
        self.m_m_dimu[0]=t_in.m_m_dimu
        self.m_m_recoil[0]=t_in.m_m_recoil
        self.m_phi_dilepton_1[0]=t_in.m_phi_dilepton_1
        self.m_phi_dilepton_2[0]=t_in.m_phi_dilepton_2
        self.m_cos_miss[0]=t_in.m_cos_miss
        self.m_cos_Z[0]=t_in.m_cos_Z
        self.m_theta_dilepton[0]=t_in.m_phi_dilepton_2
        self.m_cos_theta_leptonm[0]=costheta_leptonm
        self.m_cos_theta_leptonp[0]=costheta_leptonp
        self.m_angle_dilepton[0]=t_in.m_angle_dilepton
        self.m_delta_pt[0]=t_in.m_delta_pt
        self.m_energy_neutrino[0]=t_in.m_energy_neutrino
        self.m_miss_m[0]=t_in.m_miss_m
        self.m_miss_e[0]=t_in.m_miss_e
        self.m_energy_visible[0]=t_in.m_energy_visible
        self.m_p_visible3[0]=t_in.m_p_visible[3]
        self.m_m_visible[0]=t_in.m_m_visible
        self.m_e_dimu[0]=t_in.m_e_dimu
        self.m_e_recoil[0]=t_in.m_e_recoil
        self.m_mine_lepton[0]=t_in.m_mine_lepton
        self.m_maxe_lepton[0]=t_in.m_maxe_lepton
        self.m_e_ep[0]=m_e_ep
        self.m_l_ep[0]=m_l_ep
        #MC information
        self.m_mc_lepton_minus_id[0]=t_in.mc_lepton_minus_id
        self.m_mc_lepton_plus_id[0]=t_in.mc_lepton_plus_id	
        self.m_mc_init_n_lepton_plus[0]=t_in.mc_init_n_lepton_plus
        self.m_mc_init_n_lepton_minus[0]=t_in.mc_init_n_lepton_minus		
        self.m_mc_init_leptonp_e[0]=t_in.mc_init_leptonp_e
        self.m_mc_init_leptonp_p[0]=t_in.mc_init_leptonp_p
        self.m_mc_init_leptonp_pt[0]=t_in.mc_init_leptonp_pt
        self.m_mc_init_leptonp_pz[0]=t_in.mc_init_leptonp_pz
        self.m_mc_init_leptonp_phi[0]=t_in.mc_init_leptonp_phi
        self.m_mc_init_leptonp_theta[0]=t_in.mc_init_leptonp_theta	
        self.m_mc_init_leptonm_e[0]=t_in.mc_init_leptonm_e
        self.m_mc_init_leptonm_p[0]=t_in.mc_init_leptonm_p
        self.m_mc_init_leptonm_pt[0]=t_in.mc_init_leptonm_pt
        self.m_mc_init_leptonm_pz[0]=t_in.mc_init_leptonm_pz
        self.m_mc_init_leptonm_phi[0]=t_in.mc_init_leptonm_phi
        self.m_mc_init_leptonm_theta[0]=t_in.mc_init_leptonm_theta	
        self.m_mc_init_dilepton_m[0]=t_in.mc_init_dilepton_m
        self.m_mc_init_dilepton_e[0]=t_in.mc_init_dilepton_e
        self.m_mc_init_dilepton_p[0]=t_in.mc_init_dilepton_p
        self.m_mc_init_dilepton_pt[0]=t_in.mc_init_dilepton_pt
        self.m_mc_init_dilepton_pz[0]=t_in.mc_init_dilepton_pz
        self.m_mc_init_dilepton_rec_m[0]=t_in.mc_init_dilepton_rec_m
        self.m_mc_init_dilepton_dphi[0]=t_in.mc_init_dilepton_dphi
        self.m_mc_init_dilepton_dang[0]=t_in.mc_init_dilepton_dang		
        self.m_mc_init_n_photon[0]=t_in.mc_init_n_photon
        self.m_mc_higgs_m[0]=t_in.mc_higgs_m
        self.m_mc_higgs_e[0]=t_in.mc_higgs_e
        self.m_mc_higgs_rec_m[0]=t_in.mc_higgs_rec_m
        self.m_mc_higgs_decay_type[0]=t_in.mc_higgs_decay_type		
        self.m_mc_n_Zboson[0]=t_in.mc_n_Zboson		
        self.m_mc_zw1_m[0]=t_in.mc_zw1_m
        self.m_mc_zw1_p[0]=t_in.mc_zw1_p
        self.m_mc_zw1_pt[0]=t_in.mc_zw1_pt
        self.m_mc_zw1_e[0]=t_in.mc_zw1_e
        self.m_mc_zw1_rec_m[0]=t_in.mc_zw1_rec_m
        self.m_mc_zw2_m[0]=t_in.mc_zw2_m
        self.m_mc_zw2_p[0]=t_in.mc_zw2_p
        self.m_mc_zw2_pt[0]=t_in.mc_zw2_pt
        self.m_mc_zw2_e[0]=t_in.mc_zw2_e
        self.m_mc_zw2_rec_m[0]=t_in.mc_zw2_rec_m
        self.m_mc_h2gaugeboson_flag[0]=t_in.mc_h2gaugeboson_flag  		
        self.m_mc_zw1zw2_m[0]=t_in.mc_zw1zw2_m
        self.m_mc_zw1zw2_e[0]=t_in.mc_zw1zw2_e
        self.m_mc_zw1zw2_rec_m[0]=t_in.mc_zw1zw2_rec_m
        self.m_mc_zz_flag[0]=t_in.mc_zz_flag
        self.m_mc_ww_flag[0]=t_in.mc_ww_flag

        for i in xrange(4):
            self.m_p_visible[i]=t_in.m_p_visible[i]
            self.m_sum_p_photon[i]=t_in.m_sum_p_photon[i]
            self.m_sum_p_neutral[i]=t_in.m_sum_p_neutral[i]
            self.m_p_leptonp[i]=t_in.m_p_leptonp[i]
            self.m_p_leptonm[i]=t_in.m_p_leptonm[i]
            self.m_p_dilepton[i]=t_in.m_p_dilepton[i]
            self.m_sum_p_charged[i]=t_in.m_sum_p_charged[i]
            self.m_p_Higgsdaughters[i]=t_in.m_p_Higgsdaughters[i]
            self.m_p_Higgsdaughter1[i]=t_in.m_p_Higgsdaughter1[i]
            self.m_p_Higgsdaughter2[i]=t_in.m_p_Higgsdaughter2[i]
            self.m_p_Zdaughters[i]=t_in.m_p_Zdaughters[i]
            self.m_p_Zdaughterp[i]=t_in.m_p_Zdaughterp[i]
            self.m_p_Zdaughterm[i]=t_in.m_p_Zdaughterm[i]
            self.m_minp_lepton[i]=t_in.m_minp_lepton[i]
            self.m_maxp_lepton[i]=t_in.m_maxp_lepton[i]
 #           print t_in.mc_init_photon_e.at(0)
        for i in xrange(len(t_in.mc_init_photon_e)):

            self.m_mc_init_photon_e.push_back(t_in.mc_init_photon_e.at(i))
            self.m_mc_init_photon_p.push_back(t_in.mc_init_photon_p.at(i))
            self.m_mc_init_photon_pt.push_back(t_in.mc_init_photon_pt.at(i))
            self.m_mc_init_photon_pz.push_back(t_in.mc_init_photon_pz.at(i))
            self.m_mc_init_photon_phi.push_back(t_in.mc_init_photon_phi.at(i))
            self.m_mc_init_photon_theta.push_back(t_in.mc_init_photon_theta.at(i))  

        for i in xrange (len(t_in.mc_z1_daughter_pid)): 
            self.m_mc_z1_daughter_pid.push_back(t_in.mc_init_photon_theta.at(i))           
        for i in xrange (len(t_in.mc_z2_daughter_pid)):
            self.m_mc_z2_daughter_pid.push_back(t_in.mc_z2_daughter_pid.at(i))           
        for i in xrange (len(t_in.mc_pdgid)):
            self.m_mc_pdgid.push_back(t_in.mc_pdgid.at(i))         
        for i in xrange (len(t_in.mc_init_pdgid)):
            self.m_mc_init_pdgid.push_back(t_in.mc_init_pdgid.at(i))          
        for i in xrange (len(t_in.mc_w1_daughter_pid)):
            self.m_mc_w1_daughter_pid.push_back(t_in.mc_w1_daughter_pid.at(i))           
        for i in xrange (len(t_in.mc_w2_daughter_pid)):
            self.m_mc_w2_daughter_pid.push_back(t_in.mc_w2_daughter_pid.at(i))          
        for i in xrange (len(t_in.mc_higgs_daughter_pdgid)):
            self.m_mc_higgs_daughter_pdgid.push_back(t_in.mc_higgs_daughter_pdgid.at(i))                                               
        t_out.Fill()

        self.m_mc_init_photon_e.clear()
        self.m_mc_init_photon_p.clear()
        self.m_mc_init_photon_pt.clear()
        self.m_mc_init_photon_pz.clear()
        self.m_mc_init_photon_phi.clear()
        self.m_mc_init_photon_theta.clear()

        self.m_mc_z1_daughter_pid.clear()
        self.m_mc_z2_daughter_pid.clear()
        self.m_mc_pdgid.clear()
        self.m_mc_init_pdgid.clear()
        self.m_mc_w1_daughter_pid.clear()
        self.m_mc_w2_daughter_pid.clear()
        self.m_mc_higgs_daughter_pdgid.clear()
        
#    def out_eff(self,t_in,N,infile):
#
#        infile2 = infile.split('ana_')[0]
#        number = infile.split('ana_')[1].split('root')[0]
#        #        number1 = number.split('root')[0]
#        in_cut_dir = infile2 + 'test'
#        if in_cut_dir != '' and not os.access(in_cut_dir, os.F_OK) :
#            os.makedirs(in_cut_dir)
#        out_cut_name =  in_cut_dir + '/' + number + 'out_cut.txt'
#
#        out_cut_file = open(out_cut_name,'w')
#        out_cut_file.write('\n.....Cut flow.....\n')
#        out_cut_file.write('\nInputFile: %s\n'%(infile))
#        out_cut_file.write('\nTotal Events: %d\n'%(t_in.GetEntries()))
#
#        for i in xrange(len(N)):
#            out_cut_file.write('\nCut No.: %d\n'%(i))
#            out_cut_file.write('\nEvents: %d\n'%(N[i]))
#            out_cut_file.write('\nEfficiency: %f\n'%(N[i]/t_in.GetEntries()))
#            out_cut_file.write('\n........\n')
#        out_cut_file.close()

    def cut_his_write(self):
        self.h_evtflw.Write()
        #before cut
        self.h_before_cut_Pt.Write()
        self.h_before_cut_Pz.Write()
        self.h_before_cut_theta.Write()
        self.h_before_cut_vis.Write()
        self.h_before_cut_Mmumu.Write()
        self.h_before_cut_Mrecoil.Write()
        self.h_before_cut_ep.Write()
#        self.h_before_cut_costhem.Write()
#        self.h_before_cut_costhep.Write()

# After first cut
        self.h_after_first_cut_Pt.Write()
        self.h_after_first_cut_Pz.Write()
        self.h_after_first_cut_theta.Write()
        self.h_after_first_cut_vis.Write()
        self.h_after_first_cut_Mmumu.Write()
        self.h_after_first_cut_Mrecoil.Write()
        self.h_after_first_cut_ep.Write()
# After second cut
        self.h_after_second_cut_Pt.Write()
        self.h_after_second_cut_Pz.Write()
        self.h_after_second_cut_theta.Write()
        self.h_after_second_cut_vis.Write()
        self.h_after_second_cut_Mmumu.Write()
        self.h_after_second_cut_Mrecoil.Write()
        self.h_after_second_cut_ep.Write()
# After third cut
        self.h_after_third_cut_Pt.Write()
        self.h_after_third_cut_Pz.Write()
        self.h_after_third_cut_theta.Write()
        self.h_after_third_cut_vis.Write()
        self.h_after_third_cut_Mmumu.Write()
        self.h_after_third_cut_Mrecoil.Write()
        self.h_after_third_cut_ep.Write()
# After fourth cut
        self.h_after_fourth_cut_Pt.Write()
        self.h_after_fourth_cut_Pz.Write()
        self.h_after_fourth_cut_theta.Write()
        self.h_after_fourth_cut_vis.Write()
        self.h_after_fourth_cut_Mmumu.Write()
        self.h_after_fourth_cut_Mrecoil.Write()
        self.h_after_fourth_cut_ep.Write()
# After fifth cut

        self.h_after_fifth_cut_Pt.Write()
        self.h_after_fifth_cut_Pz.Write()
        self.h_after_fifth_cut_theta.Write()
        self.h_after_fifth_cut_vis.Write()
        self.h_after_fifth_cut_Mmumu.Write()
        self.h_after_fifth_cut_Mrecoil.Write()
        self.h_after_fifth_cut_ep.Write()
# After sixth cut
        self.h_after_sixth_cut_Pt.Write()
        self.h_after_sixth_cut_Pz.Write()
        self.h_after_sixth_cut_theta.Write()
        self.h_after_sixth_cut_vis.Write()
        self.h_after_sixth_cut_Mmumu.Write()
        self.h_after_sixth_cut_Mrecoil.Write()
        self.h_after_sixth_cut_ep.Write()
# After seventh cut
        self.h_after_seventh_cut_Pt.Write()
        self.h_after_seventh_cut_Pz.Write()
        self.h_after_seventh_cut_theta.Write()
        self.h_after_seventh_cut_vis.Write()
        self.h_after_seventh_cut_Mmumu.Write()
        self.h_after_seventh_cut_Mrecoil.Write()
        self.h_after_seventh_cut_ep.Write()
        #after all cut

        self.h_after_cut_Pt.Write()
        self.h_after_cut_Pz.Write()
        self.h_after_cut_theta.Write()
        self.h_after_cut_vis.Write()
        self.h_after_cut_Mmumu.Write()
        self.h_after_cut_Mrecoil.Write()
        self.h_after_cut_ep.Write()
#       self.h_after_cut_costhem.Write()
#       self.h_after_cut_costhep.Write()
    def run(self):
        args=sys.argv[1:]
        if len(args)<2:
            print('Input is wrong')
            sys.exit()

        infile=args[0]
        outfile=args[1]
#        h =[0]*21
#        f = ROOT.TFile(infile)
#        h[1] = f.Get('h_mc_init_plist')
#        h[2] = f.Get('h_mc_higgs_dlist')
        tmp_file = ROOT.TFile(infile)
        t_in = tmp_file.Get('tree')
        tmp_entries = t_in.GetEntriesFast()

        fout=ROOT.TFile(outfile,"RECREATE")
        t_out=ROOT.TTree('tree','tree')

        t_out.Branch('m_event',self.m_event,'m_event/I')
        t_out.Branch('m_n_neutral',self.m_n_neutral,'m_n_neutral/I')
        t_out.Branch('m_Neutral_PID',self.m_Neutral_PID,'m_Neutral_PID/I')
        t_out.Branch('m_sum_p_neutral',self.m_sum_p_neutral,'m_sum_p_neutral[4]/F')
        t_out.Branch('m_sum_p_photon',self.m_sum_p_photon,'m_sum_p_photon[4]/F')
        t_out.Branch('m_e_photon',self.m_e_photon,'m_e_photon/F')
        t_out.Branch('m_e_other',self.m_e_other,'m_e_other/F')		
        t_out.Branch('m_p_leptonp',self.m_p_leptonp,'m_p_leptonp[4]/F')
        t_out.Branch('m_p_leptonm',self.m_p_leptonm,'m_p_leptonm[4]/F')
        t_out.Branch('m_p_dilepton',self.m_p_dilepton,'m_p_dilepton[4]/F')
        t_out.Branch('m_sum_p_charged',self.m_sum_p_charged,'m_sum_p_charged[4]/F')
        t_out.Branch('m_p_Higgsdaughters',self.m_p_Higgsdaughters,'m_p_Higgsdaughters[4]/F')
        t_out.Branch('m_p_Higgsdaughter1',self.m_p_Higgsdaughter1,'m_p_Higgsdaughter1[4]/F')
        t_out.Branch('m_p_Higgsdaughter2',self.m_p_Higgsdaughter2,'m_p_Higgsdaughter2[4]/F')
        t_out.Branch('m_p_Zdaughters',self.m_p_Zdaughters,'m_p_Zdaughters[4]/F')
        t_out.Branch('m_p_Zdaughterp',self.m_p_Zdaughterp,'m_p_Zdaughterp[4]/F')
        t_out.Branch('m_p_Zdaughterm',self.m_p_Zdaughterm,'m_p_Zdaughterm[4]/F')
        t_out.Branch('m_sum_pt_photon',self.m_sum_pt_photon,'m_sum_pt_photon/F')
        t_out.Branch('m_pt_dilepton',self.m_pt_dilepton,'m_pt_dilepton/F')
        t_out.Branch('m_pt_leptonm',self.m_pt_leptonm,'m_pt_leptonm/F')
        t_out.Branch('m_pt_leptonp',self.m_pt_leptonp,'m_pt_leptonp/F')
        t_out.Branch('m_pz_dilepton',self.m_pz_dilepton,'m_pz_dilepton/F')
        t_out.Branch('m_pz_leptonm',self.m_pz_leptonm,'m_pz_leptonm/F')
        t_out.Branch('m_pz_leptonp',self.m_pz_leptonp,'m_pz_leptonp/F')
        t_out.Branch('m_e_leptonm',self.m_e_leptonm,'m_e_leptonm/F')
        t_out.Branch('m_e_leptonp',self.m_e_leptonp,'m_e_leptonp/F')
        t_out.Branch('m_n_charged',self.m_n_charged,'m_n_charged/I')
        t_out.Branch('m_n_gamma',self.m_n_gamma,'m_n_gamma/I')
        t_out.Branch('m_n_leptonp',self.m_n_leptonp,'m_n_leptonp/I')
        t_out.Branch('m_n_leptonm',self.m_n_leptonm,'m_n_leptonm/I')
        t_out.Branch('m_n_chargedp',self.m_n_chargedp,'m_n_chargedp/I')
        t_out.Branch('m_n_chargedm',self.m_n_chargedm,'m_n_chargedm/I')
        t_out.Branch('m_n_Higgsdaughter',self.m_n_Higgsdaughter,'m_n_Higgsdaughter/I')
        t_out.Branch('m_n_neutrino',self.m_n_neutrino,'m_n_neutrino/I')
        t_out.Branch('m_m_dimu',self.m_m_dimu,'m_m_dimu/F')
        t_out.Branch('m_m_recoil',self.m_m_recoil,'m_m_recoil/F')
        t_out.Branch('m_phi_dilepton_1',self.m_phi_dilepton_1,'m_phi_dilepton_1/F')
        t_out.Branch('m_phi_dilepton_2',self.m_phi_dilepton_2,'m_phi_dilepton_2/F')
        t_out.Branch('m_cos_miss',self.m_cos_miss,'m_cos_miss/F')
        t_out.Branch('m_cos_Z',self.m_cos_Z,'m_cos_Z/F')
        t_out.Branch('m_theta_dilepton',self.m_theta_dilepton,'m_theta_dilepton/F')
        t_out.Branch('m_cos_theta_leptonm',self.m_cos_theta_leptonm,'m_cos_theta_leptonm/F')
        t_out.Branch('m_cos_theta_leptonp',self.m_cos_theta_leptonp,'m_cos_theta_leptonp/F')
        t_out.Branch('m_angle_dilepton',self.m_angle_dilepton,'m_angle_dilepton/F')
        t_out.Branch('m_delta_pt',self.m_delta_pt,'m_delta_pt/F')
        t_out.Branch('m_energy_neutrino',self.m_energy_neutrino,'m_energy_neutrino/F')
        t_out.Branch('m_p_visible',self.m_p_visible,'m_p_visible[4]/F')
        t_out.Branch('m_p_visible3',self.m_p_visible3,'m_p_visible3/F')
        t_out.Branch('m_energy_visible',self.m_energy_visible,'m_energy_visible/F')
        t_out.Branch('m_miss_m',self.m_miss_m,'m_miss_m/F')
        t_out.Branch('m_miss_e',self.m_miss_e,'m_miss_e/F')
        t_out.Branch('m_m_visible',self.m_m_visible,'m_m_visible/F')  
        t_out.Branch('m_e_dimu',self.m_e_dimu,'m_e_dimu/F')
        t_out.Branch('m_e_recoil',self.m_e_recoil,'m_e_recoil/F') 

        t_out.Branch("m_mine_lepton",  self.m_mine_lepton,  "m_mine_lepton/F")
        t_out.Branch("m_maxe_lepton",  self.m_maxe_lepton,  "m_maxe_lepton/F")


        t_out.Branch("m_minp_lepton",  self.m_minp_lepton,  "m_minp_lepton[4]/F")
        t_out.Branch("m_maxp_lepton",  self.m_maxp_lepton,  "m_maxp_lepton[4]/F")

        t_out.Branch("m_e_ep",  self.m_e_ep,  "m_e_ep/F") 
        t_out.Branch("m_l_ep",  self.m_l_ep,  "m_l_ep/F") 
        #MC information
        t_out.Branch("mc_pdgid", self.m_mc_pdgid)
        t_out.Branch("mc_init_pdgid", self.m_mc_init_pdgid)
        
        t_out.Branch("mc_lepton_minus_id", self.m_mc_lepton_minus_id, "mc_lepton_minus_id/I")
        t_out.Branch("mc_lepton_plus_id", self.m_mc_lepton_plus_id, "mc_lepton_plus_id/I")
        
        t_out.Branch("mc_init_n_lepton_plus", self.m_mc_init_n_lepton_plus,  "mc_init_n_lepton_plus/I")
        t_out.Branch("mc_init_n_lepton_minus", self.m_mc_init_n_lepton_minus,  "mc_init_n_lepton_minus/I")
        
        t_out.Branch("mc_init_leptonp_e",  self.m_mc_init_leptonp_e,   "mc_init_leptonp_e/D")
        t_out.Branch("mc_init_leptonp_p",  self.m_mc_init_leptonp_p,   "mc_init_leptonp_p/D")
        t_out.Branch("mc_init_leptonp_pt", self.m_mc_init_leptonp_pt,  "mc_init_leptonp_pt/D")
        t_out.Branch("mc_init_leptonp_pz", self.m_mc_init_leptonp_pz,  "mc_init_leptonp_pz/D")

        t_out.Branch("mc_init_leptonp_phi", self.m_mc_init_leptonp_phi,  "mc_init_leptonp_phi/D")
        t_out.Branch("mc_init_leptonp_theta", self.m_mc_init_leptonp_theta,  "mc_init_leptonp_theta/D")
        
        t_out.Branch("mc_init_leptonm_e",  self.m_mc_init_leptonm_e,   "mc_init_leptonm_e/D")
        t_out.Branch("mc_init_leptonm_p",  self.m_mc_init_leptonm_p,   "mc_init_leptonm_p/D")
        t_out.Branch("mc_init_leptonm_pt", self.m_mc_init_leptonm_pt,  "mc_init_leptonm_pt/D")
        t_out.Branch("mc_init_leptonm_pz", self.m_mc_init_leptonm_pz,  "mc_init_leptonm_pz/D")

        t_out.Branch("mc_init_leptonm_phi", self.m_mc_init_leptonm_phi,  "mc_init_leptonm_phi/D")
        t_out.Branch("mc_init_leptonm_theta", self.m_mc_init_leptonm_theta,  "mc_init_leptonm_theta/D")
        
        t_out.Branch("mc_init_dilepton_m",  self.m_mc_init_dilepton_m,   "mc_init_dilepton_m/D")
        t_out.Branch("mc_init_dilepton_e",  self.m_mc_init_dilepton_e,   "mc_init_dilepton_e/D")
        t_out.Branch("mc_init_dilepton_p",  self.m_mc_init_dilepton_p,   "mc_init_dilepton_p/D")
        t_out.Branch("mc_init_dilepton_pt", self.m_mc_init_dilepton_pt,  "mc_init_dilepton_pt/D")
        t_out.Branch("mc_init_dilepton_pz", self.m_mc_init_dilepton_pz,  "mc_init_dilepton_pz/D")
        t_out.Branch("mc_init_dilepton_rec_m", self.m_mc_init_dilepton_rec_m,  "mc_init_dilepton_rec_m/D")
        t_out.Branch("mc_init_dilepton_dphi", self.m_mc_init_dilepton_dphi,  "mc_init_dilepton_dphi/D")
        t_out.Branch("mc_init_dilepton_dang", self.m_mc_init_dilepton_dang,  "mc_init_dilepton_dang/D")
        
        t_out.Branch("mc_init_n_photon", self.m_mc_init_n_photon,  "mc_init_n_photon/I")
        t_out.Branch("mc_init_photon_e",  self.m_mc_init_photon_e)
        t_out.Branch("mc_init_photon_p",  self.m_mc_init_photon_p)
        t_out.Branch("mc_init_photon_pt",  self.m_mc_init_photon_pt)
        t_out.Branch("mc_init_photon_pz",  self.m_mc_init_photon_pz)
        t_out.Branch("mc_init_photon_phi",  self.m_mc_init_photon_phi)
        t_out.Branch("mc_init_photon_theta",  self.m_mc_init_photon_theta)

        t_out.Branch("mc_higgs_m", self.m_mc_higgs_m, "mc_higgs_m/D")
        t_out.Branch("mc_higgs_e", self.m_mc_higgs_e, "mc_higgs_e/D")
        t_out.Branch("mc_higgs_rec_m", self.m_mc_higgs_rec_m, "mc_higgs_rec_m/D")
        t_out.Branch("mc_higgs_decay_type", self.m_mc_higgs_decay_type, "mc_higgs_decay_type/I")
        t_out.Branch("mc_higgs_daughter_pdgid", self.m_mc_higgs_daughter_pdgid)
        
        t_out.Branch("mc_n_Zboson", self.m_mc_n_Zboson, "mc_n_Zboson/I")
        
        t_out.Branch("mc_z1_daughter_pid", self.m_mc_z1_daughter_pid)
        t_out.Branch("mc_z2_daughter_pid", self.m_mc_z2_daughter_pid)

        t_out.Branch("mc_w1_daughter_pid", self.m_mc_w1_daughter_pid)
        t_out.Branch("mc_w2_daughter_pid", self.m_mc_w2_daughter_pid)
        
        t_out.Branch("mc_zw1_m", self.m_mc_zw1_m, "mc_zw1_m/D")
        t_out.Branch("mc_zw1_p", self.m_mc_zw1_p, "mc_zw1_p/D")
        t_out.Branch("mc_zw1_pt", self.m_mc_zw1_pt, "mc_zw1_pt/D")
        t_out.Branch("mc_zw1_e", self.m_mc_zw1_e, "mc_zw1_e/D")
        t_out.Branch("mc_zw1_rec_m", self.m_mc_zw1_rec_m, "mc_zw1_rec_m/D")
        
        t_out.Branch("mc_zw2_m", self.m_mc_zw2_m, "mc_zw2_m/D")
        t_out.Branch("mc_zw2_p", self.m_mc_zw2_p, "mc_zw2_p/D")
        t_out.Branch("mc_zw2_pt", self.m_mc_zw2_pt, "mc_zw2_pt/D")
        t_out.Branch("mc_zw2_e", self.m_mc_zw2_e, "mc_zw2_e/D")
        t_out.Branch("mc_zw2_rec_m", self.m_mc_zw2_rec_m, "mc_zw2_rec_m/D")
        
        t_out.Branch("mc_zw1zw2_m", self.m_mc_zw1zw2_m, "mc_zw1zw2_m/D")
        t_out.Branch("mc_zw1zw2_e", self.m_mc_zw1zw2_e, "mc_zw1zw2_e/D")
        t_out.Branch("mc_zw1zw2_rec_m", self.m_mc_zw1zw2_rec_m, "mc_zw1zw2_rec_m/D")
        t_out.Branch("mc_zz_flag", self.m_mc_zz_flag, "mc_zz_flag/I")
        t_out.Branch("mc_ww_flag", self.m_mc_ww_flag, "mc_ww_flag/I")
        t_out.Branch("mc_h2gaugeboson_flag", self.m_mc_h2gaugeboson_flag, "mc_h2gaugeboson_flag/I")


        for i in xrange(tmp_entries):
            t_in.GetEntry(i)
            #Plot cuts histrogram before cut
            self.plot_before_cut(t_in)
            #Cut eventflow and fill histrogram
            self.cut(t_in,t_out)
            #record the select efficiency
#            self.out_eff(t_in,self.N,infile)
        #Write cut flow histrogram
        self.cut_his_write()
#        h[1].Write()
#        h[2].Write()
        t_out.Write()
        fout.Close()

if __name__ == '__main__':
    start_time = time.clock()
    CUTFLOW = Cutflow()
    CUTFLOW.run()
    print "Cut_successful"
    end_time = time.clock()
print('Running time: %s Seconds'%(end_time-start_time))

