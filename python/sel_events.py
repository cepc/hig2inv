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
        self.h_evtflw.GetXaxis().SetBinLabel(2,'N_{#mu}<3&&N_{charged}<3')
        self.h_evtflw.GetXaxis().SetBinLabel(3,'N_{#gamma}<=1')
        self.h_evtflw.GetXaxis().SetBinLabel(4,'10GeV/c<P_{t}^{#mu^{+}#mu^{-}}<70GeV/c')
        self.h_evtflw.GetXaxis().SetBinLabel(5,'|P_{z}^{#mu^{+}#mu^{-}}|<50GeV/c')
        self.h_evtflw.GetXaxis().SetBinLabel(6,'|cos#theta_{#mu^{+}#mu^{-}}|<0.5')
        self.h_evtflw.GetXaxis().SetBinLabel(7,'90GeV<Visible Energy<110GeV')
        self.h_evtflw.GetXaxis().SetBinLabel(8,'83GeV/c^{2}<M_{#mu^{+}#mu^{-}}<97GeV/c^{2}')
        self.h_evtflw.GetXaxis().SetBinLabel(9,'120GeV/c^{2}<M_{Recoil}<150GeV/c^{2}')
        self.N=[0.,0.,0.,0.,0.,0.,0.,0.,0.]
        #Before cuts histrogram define
        self.h_before_cut_n_moun = ROOT.TH2F('before_cut_number_moun','before_cut_N_{#mu}<3&&N_{charged}<3',20,0,10,20,0,10)
        self.h_before_cut_n_photon = ROOT.TH1F('before_cut_n_photon','before_cut_N_{#gamma}<=1',10,0,10)
        self.h_before_cut_Pt = ROOT.TH1F('before_cut_Pt','before_cut_10GeV/c<P_{t}^{#mu^{+}#mu^{-}}<70GeV/c',90,0,90)
        self.h_before_cut_Pz = ROOT.TH1F('before_cut_Pz','before_cut_|P_{z}^{#mu^{+}#mu^{-}}|<50GeV/c',70,0,70)
        self.h_before_cut_theta = ROOT.TH1F('before_cut_theta','before_cut_|cos#theta_{#mu^{+}#mu^{-}}|<0.5',10,0,1)
        self.h_before_cut_vis = ROOT.TH1F('before_cut_vis','before_cut_90GeV<Visible Energy<110GeV',40,70,180)
        self.h_before_cut_Mmumu= ROOT.TH1F('before_cut_Mmumu','before_cut_83GeV/c^{2}<M_{#mu^{+}#mu^{-}}<97GeV/c^{2}',60,60,120)
        self.h_before_cut_Mrecoil = ROOT.TH1F('before_cut_Mrecoil','before_cut_120GeV/c^{2}<M_{Recoil}<150GeV/c^{2}',70,100,170)
        #After cut histrogram define
        self.h_after_cut_n_moun = ROOT.TH2F('after_cut_number_moun','after_cut_N_{#mu}<3&&N_{charged}<3',20,0,10,20,0,10)
        self.h_after_cut_n_photon = ROOT.TH1F('after_cut_n_photon','after_cut_N_{#gamma}<=1',10,0,10)
        self.h_after_cut_Pt = ROOT.TH1F('after_cut_Pt','after_cut_10GeV/c<P_{t}^{#mu^{+}#mu^{-}}<70GeV/c',90,0,90)
        self.h_after_cut_Pz = ROOT.TH1F('after_cut_Pz','after_cut_|P_{z}^{#mu^{+}#mu^{-}}|<50GeV/c',70,0,70)
        self.h_after_cut_theta = ROOT.TH1F('after_cut_theta','after_cut_|cos#theta_{#mu^{+}#mu^{-}}|<0.5',10,0,1)
        self.h_after_cut_vis = ROOT.TH1F('after_cut_vis','after_cut_90GeV<Visible Energy<110GeV',40,70,180)
        self.h_after_cut_Mmumu= ROOT.TH1F('after_cut_Mmumu','after_cut_83GeV/c^{2}<M_{#mu^{+}#mu^{-}}<97GeV/c^{2}',60,60,120)
        self.h_after_cut_Mrecoil = ROOT.TH1F('after_cut_Mrecoil','after_cut_120GeV/c^{2}<M_{Recoil}<150GeV/c^{2}',70,100,170)


        self.m_event=array('i',[0])
        self.m_event_type=array('i',[0])
        self.m_p_neutral=array('f',4*[-99])
        self.m_p_photon=array('f',4*[-99])
        self.m_p_leptonp=array('f',4*[-99])
        self.m_p_leptonm=array('f',4*[-99])
        self.m_p_dilepton=array('f',4*[-99])
        self.m_p_charged=array('f',4*[-99])
        self.m_p_Higgsdaughters=array('f',4*[-99])
        self.m_p_Higgsdaughter1=array('f',4*[-99])
        self.m_p_Higgsdaughter2=array('f',4*[-99])
        self.m_p_Zdaughters=array('f',4*[-99])
        self.m_p_Zdaughterp=array('f',4*[-99])
        self.m_p_Zdaughterm=array('f',4*[-99])
        self.m_pt_photon=array('f',[0])
        self.m_pt_dilepton=array('f',[0])
        self.m_pt_leptonm=array('f',[0])
        self.m_pt_leptonp=array('f',[0])
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
        self.m_m_visible=array('f',[0])
        self.m_m_recoil=array('f',[0])
        self.m_phi_dilepton_1=array('f',[0])
        self.m_phi_dilepton_2=array('f',[0])
        self.m_cos_miss=array('f',[0])
        self.m_cos_Z=array('f',[0])
        self.m_cos_theta_dilepton=array('f',[0])
        self.m_cos_theta_leptonm=array('f',[0])
        self.m_cos_theta_leptonp=array('f',[0])
        self.m_angle_dilepton=array('f',[0])
        self.m_delta_pt=array('f',[0])
        self.m_energy_neutrino=array('f',[0])
        self.m_energy_visible=array('f',[0])
        self.m_energy_leptonm=array('f',[0])
        self.m_energy_leptonp=array('f',[0])

    def plot_before_cut(self,t_in):

        self.h_before_cut_n_moun.Fill(t_in.m_n_leptonm+t_in.m_n_leptonm, t_in.m_n_charged)
        self.h_before_cut_n_photon.Fill(t_in.m_n_gamma)
        self.h_before_cut_Pt.Fill(t_in.m_pt_dilepton)
        self.h_before_cut_Pz.Fill(t_in.m_p_dilepton[2])
        TotalP=math.sqrt(t_in.m_p_dilepton[0]*t_in.m_p_dilepton[0]+t_in.m_p_dilepton[1]*t_in.m_p_dilepton[1]+t_in.m_p_dilepton[2]*t_in.m_p_dilepton[2])
        TotalPz=t_in.m_p_dilepton[2]
        if TotalP!=0:
            costheta_dilepton=TotalPz/TotalP
        else:
            costheta_dilepton=-999
        self.h_before_cut_theta.Fill(abs(costheta_dilepton))
        self.h_before_cut_vis.Fill(t_in.m_energy_visible)
        self.h_before_cut_Mmumu.Fill(t_in.m_m_visible)
        self.h_before_cut_Mrecoil.Fill(t_in.m_m_recoil)
    
    def plot_after_cut(self,t_in):

        self.h_after_cut_n_moun.Fill(t_in.m_n_leptonm+t_in.m_n_leptonm, t_in.m_n_charged)
        self.h_after_cut_n_photon.Fill(t_in.m_n_gamma)
        self.h_after_cut_Pt.Fill(t_in.m_pt_dilepton)
        self.h_after_cut_Pz.Fill(t_in.m_p_dilepton[2])
        TotalP=math.sqrt(t_in.m_p_dilepton[0]*t_in.m_p_dilepton[0]+t_in.m_p_dilepton[1]*t_in.m_p_dilepton[1]+t_in.m_p_dilepton[2]*t_in.m_p_dilepton[2])
        TotalPz=t_in.m_p_dilepton[2]
        if TotalP!=0:
            costheta_dilepton=TotalPz/TotalP
        else:
            costheta_dilepton=-999
        self.h_after_cut_theta.Fill(abs(costheta_dilepton))
        self.h_after_cut_vis.Fill(t_in.m_energy_visible)
        self.h_after_cut_Mmumu.Fill(t_in.m_m_visible)
        self.h_after_cut_Mrecoil.Fill(t_in.m_m_recoil)
       
    def cut(self,t_in,t_out):      
        self.N[0]+=1
        self.h_evtflw.Fill(0)

        if not ((t_in.m_n_leptonp+t_in.m_n_leptonm)<3 and t_in.m_n_charged<3):
            return False
        self.N[1]+=1
        self.h_evtflw.Fill(1)

        if not (t_in.m_n_gamma<=1):
            return False
        self.N[2]+=1
        self.h_evtflw.Fill(2) 

        if not (t_in.m_pt_dilepton>10 and t_in.m_pt_dilepton<70):
            return False
        self.N[3]+=1
        self.h_evtflw.Fill(3)                                   
                                                    
        if not (abs(t_in.m_p_dilepton[2])<50): 
            return False
        self.N[4]+=1
        self.h_evtflw.Fill(4)

        TotalP=math.sqrt(t_in.m_p_dilepton[0]*t_in.m_p_dilepton[0]+t_in.m_p_dilepton[1]*t_in.m_p_dilepton[1]+t_in.m_p_dilepton[2]*t_in.m_p_dilepton[2])
        TotalPz=t_in.m_p_dilepton[2]
        if TotalP!=0:
            costheta_dilepton=TotalPz/TotalP
        else:
            costheta_dilepton=-999
        if not (abs(costheta_dilepton)<0.5):
            return False
        self.N[5]+=1
        self.h_evtflw.Fill(5)

        if not (t_in.m_energy_visible>90 and t_in.m_energy_visible<110):
            return False
        self.N[6]+=1
        self.h_evtflw.Fill(6)

        if not (t_in.m_m_visible>83 and t_in.m_m_visible<97):
            return False
        self.N[7]+=1
        self.h_evtflw.Fill(7)

        if not (t_in.m_m_recoil>120 and t_in.m_m_recoil<150):
            return False
        self.N[8]+=1   
        self.h_evtflw.Fill(8)
        #Plot cuts histrogram after cut
        self.plot_after_cut(t_in)
        #Fill root branches after cutting
        self.fill_root(t_in,t_out)
#            
    def fill_root(self,t_in,t_out):
        TotalP=math.sqrt(t_in.m_p_dilepton[3]*t_in.m_p_dilepton[3]-t_in.m_p_dilepton[0]*t_in.m_p_dilepton[0]-t_in.m_p_dilepton[1]*t_in.m_p_dilepton[1]-t_in.m_p_dilepton[2]*t_in.m_p_dilepton[2])
        TotalPz=t_in.m_p_dilepton[2]
        if TotalP!=0:
            costheta_dilepton=TotalPz/TotalP
        else:
            costheta_dilepton=-999
        LeptonmP=math.sqrt(t_in.m_p_leptonm[3]*t_in.m_p_leptonm[3]-t_in.m_p_leptonm[0]*t_in.m_p_leptonm[0]-t_in.m_p_leptonm[1]*t_in.m_p_leptonm[1]-t_in.m_p_leptonm[2]*t_in.m_p_leptonm[2])
        LeptonmPz=t_in.m_p_leptonm[2]
        if LeptonmP!=0:
            costheta_leptonm=LeptonmPz/LeptonmP
        else:
            costheta_leptonm=-999

        LeptonpP=math.sqrt(t_in.m_p_leptonp[3]*t_in.m_p_leptonp[3]-t_in.m_p_leptonp[0]*t_in.m_p_leptonp[0]-t_in.m_p_leptonp[1]*t_in.m_p_leptonp[1]-t_in.m_p_leptonp[2]*t_in.m_p_leptonp[2])
        LeptonpPz=t_in.m_p_leptonp[2]
        if LeptonpPz!=0:
            costheta_leptonp=LeptonpPz/LeptonpP
        else:
            costheta_leptonp=-999
        self.m_event[0]=t_in.m_event
        self.m_event_type[0]=t_in.m_event_type
        self.m_pt_photon[0]=t_in.m_pt_photon
        self.m_pt_dilepton[0]=t_in.m_pt_dilepton
        self.m_pt_leptonm[0]=math.sqrt(t_in.m_p_leptonm[0]*t_in.m_p_leptonm[0]+t_in.m_p_leptonm[1]*t_in.m_p_leptonm[1])
        self.m_pt_leptonp[0]=math.sqrt(t_in.m_p_leptonp[0]*t_in.m_p_leptonp[0]+t_in.m_p_leptonp[1]*t_in.m_p_leptonp[1])
        self.m_pz_dilepton[0]=t_in.m_p_dilepton[2]
        self.m_pz_leptonm[0]=t_in.m_p_leptonm[2]
        self.m_pz_leptonp[0]=t_in.m_p_leptonp[2]
        self.m_n_charged[0]=t_in.m_n_charged
        self.m_n_gamma[0]=t_in.m_n_gamma
        self.m_n_leptonp[0]=t_in.m_n_leptonp
        self.m_n_leptonm[0]=t_in.m_n_leptonm
        self.m_n_chargedp[0]=t_in.m_n_chargedp
        self.m_n_chargedm[0]=t_in.m_n_chargedm
        self.m_n_Higgsdaughter[0]=t_in.m_n_Higgsdaughter
        self.m_n_neutrino[0]=t_in.m_n_neutrino
        self.m_m_visible[0]=t_in.m_m_visible
        self.m_m_recoil[0]=t_in.m_m_recoil
        self.m_phi_dilepton_1[0]=t_in.m_phi_dilepton_1
        self.m_phi_dilepton_2[0]=t_in.m_phi_dilepton_2
        self.m_cos_miss[0]=t_in.m_cos_miss
        self.m_cos_Z[0]=t_in.m_cos_Z
        self.m_cos_theta_dilepton[0]=costheta_dilepton
        self.m_cos_theta_leptonm[0]=costheta_leptonm
        self.m_cos_theta_leptonp[0]=costheta_leptonp
        self.m_angle_dilepton[0]=t_in.m_angle_dilepton
        self.m_delta_pt[0]=t_in.m_delta_pt
        self.m_energy_neutrino[0]=t_in.m_energy_neutrino
        self.m_energy_visible[0]=t_in.m_energy_visible
        self.m_energy_leptonm[0]=t_in.m_p_leptonm[3]
        self.m_energy_leptonp[0]=t_in.m_p_leptonp[3]
        for i in xrange(4):
            self.m_p_neutral[i]=t_in.m_p_neutral[i]               
            self.m_p_photon[i]=t_in.m_p_photon[i]
            self.m_p_leptonp[i]=t_in.m_p_leptonp[i]
            self.m_p_leptonm[i]=t_in.m_p_leptonm[i]
            self.m_p_dilepton[i]=t_in.m_p_dilepton[i]
            self.m_p_charged[i]=t_in.m_p_charged[i]
            self.m_p_Higgsdaughters[i]=t_in.m_p_Higgsdaughters[i]
            self.m_p_Higgsdaughter1[i]=t_in.m_p_Higgsdaughter1[i]
            self.m_p_Higgsdaughter2[i]=t_in.m_p_Higgsdaughter2[i]
            self.m_p_Zdaughters[i]=t_in.m_p_Zdaughters[i]
            self.m_p_Zdaughterp[i]=t_in.m_p_Zdaughterp[i] 
            self.m_p_Zdaughterm[i]=t_in.m_p_Zdaughterm[i]

        t_out.Fill()

    def out_eff(self,t_in,N,infile): 

        infile2 = infile.split('ana_')[0]
        number = infile.split('ana_')[1].split('root')[0]
#        number1 = number.split('root')[0] 
        in_cut_dir = infile2 + 'test'
        if in_cut_dir != '' and not os.access(in_cut_dir, os.F_OK) :
            os.makedirs(in_cut_dir)
        out_cut_name =  in_cut_dir + '/' + number + 'out_cut.txt'

        out_cut_file = open(out_cut_name,'w')
        out_cut_file.write('\n.....Cut flow.....\n')
        out_cut_file.write('\nInputFile: %s\n'%(infile))
        out_cut_file.write('\nTotal Events: %d\n'%(t_in.GetEntries()))

        for i in xrange(len(N)):
            out_cut_file.write('\nCut No.: %d\n'%(i))
            out_cut_file.write('\nEvents: %d\n'%(N[i]))
            out_cut_file.write('\nEfficiency: %f\n'%(N[i]/t_in.GetEntries()))
            out_cut_file.write('\n........\n')
        out_cut_file.close()

    def cut_his_write(self):
        self.h_evtflw.Write()
        #before cut
        self.h_before_cut_n_moun.Write()
        self.h_before_cut_n_photon.Write()
        self.h_before_cut_Pt.Write()
        self.h_before_cut_Pz.Write()
        self.h_before_cut_theta.Write()
        self.h_before_cut_vis.Write()
        self.h_before_cut_Mmumu.Write()
        self.h_before_cut_Mrecoil.Write()
        #after cut
        self.h_after_cut_n_moun.Write()
        self.h_after_cut_n_photon.Write()
        self.h_after_cut_Pt.Write()
        self.h_after_cut_Pz.Write()
        self.h_after_cut_theta.Write()
        self.h_after_cut_vis.Write()
        self.h_after_cut_Mmumu.Write()
        self.h_after_cut_Mrecoil.Write()

    def run(self):
        args=sys.argv[1:]
        if len(args)<2:
            print('Input is wrong')
            sys.exit()

        infile=args[0]
        outfile=args[1]

        tmp_file = ROOT.TFile(infile)
        t_in = tmp_file.Get('tree')
        tmp_entries = t_in.GetEntriesFast()

        fout=ROOT.TFile(outfile,"RECREATE")
        t_out=ROOT.TTree('tree','tree')
        
        t_out.Branch('m_event',self.m_event,'m_event/I')
        t_out.Branch('m_event_type',self.m_event_type,'m_event_type/I')
        t_out.Branch('m_p_neutral',self.m_p_neutral,'m_p_neutral[4]/F')
        t_out.Branch('m_p_photon',self.m_p_photon,'m_p_photon[4]/F')
        t_out.Branch('m_p_leptonp',self.m_p_leptonp,'m_p_leptonp[4]/F')
        t_out.Branch('m_p_leptonm',self.m_p_leptonm,'m_p_leptonm[4]/F')
        t_out.Branch('m_p_dilepton',self.m_p_dilepton,'m_p_dilepton[4]/F')
        t_out.Branch('m_p_charged',self.m_p_charged,'m_p_charged[4]/F')
        t_out.Branch('m_p_Higgsdaughters',self.m_p_Higgsdaughters,'m_p_Higgsdaughters[4]/F')
        t_out.Branch('m_p_Higgsdaughter1',self.m_p_Higgsdaughter1,'m_p_Higgsdaughter1[4]/F')
        t_out.Branch('m_p_Higgsdaughter2',self.m_p_Higgsdaughter2,'m_p_Higgsdaughter2[4]/F')
        t_out.Branch('m_p_Zdaughters',self.m_p_Zdaughters,'m_p_Zdaughters[4]/F')
        t_out.Branch('m_p_Zdaughterp',self.m_p_Zdaughterp,'m_p_Zdaughterp[4]/F')
        t_out.Branch('m_p_Zdaughterm',self.m_p_Zdaughterm,'m_p_Zdaughterm[4]/F')
        t_out.Branch('m_pt_photon',self.m_pt_photon,'m_pt_photon/F')
        t_out.Branch('m_pt_dilepton',self.m_pt_dilepton,'m_pt_dilepton/F')
        t_out.Branch('m_pt_leptonm',self.m_pt_leptonm,'m_pt_leptonm/F')
        t_out.Branch('m_pt_leptonp',self.m_pt_leptonp,'m_pt_leptonp/F')
        t_out.Branch('m_pz_dilepton',self.m_pz_dilepton,'m_pz_dilepton/F')
        t_out.Branch('m_pz_leptonm',self.m_pz_leptonm,'m_pz_leptonm/F')
        t_out.Branch('m_pz_leptonp',self.m_pz_leptonp,'m_pz_leptonp/F')
        t_out.Branch('m_n_charged',self.m_n_charged,'m_n_charged/I')
        t_out.Branch('m_n_gamma',self.m_n_gamma,'m_n_gamma/I')
        t_out.Branch('m_n_leptonp',self.m_n_leptonp,'m_n_leptonp/I')
        t_out.Branch('m_n_leptonm',self.m_n_leptonm,'m_n_leptonm/I')
        t_out.Branch('m_n_chargedp',self.m_n_chargedp,'m_n_chargedp/I')
        t_out.Branch('m_n_chargedm',self.m_n_chargedm,'m_n_chargedm/I')
        t_out.Branch('m_n_Higgsdaughter',self.m_n_Higgsdaughter,'m_n_Higgsdaughter/I')
        t_out.Branch('m_n_neutrino',self.m_n_neutrino,'m_n_neutrino/I')
        t_out.Branch('m_m_visible',self.m_m_visible,'m_m_visible/F')
        t_out.Branch('m_m_recoil',self.m_m_recoil,'m_m_recoil/F')
        t_out.Branch('m_phi_dilepton_1',self.m_phi_dilepton_1,'m_phi_dilepton_1/F')
        t_out.Branch('m_phi_dilepton_2',self.m_phi_dilepton_2,'m_phi_dilepton_2/F')
        t_out.Branch('m_cos_miss',self.m_cos_miss,'m_cos_miss/F')
        t_out.Branch('m_cos_Z',self.m_cos_Z,'m_cos_Z/F')
        t_out.Branch('m_cos_theta_dilepton',self.m_cos_theta_dilepton,'m_cos_theta_dilepton/F')
        t_out.Branch('m_cos_theta_leptonm',self.m_cos_theta_leptonm,'m_cos_theta_leptonm/F')
        t_out.Branch('m_cos_theta_leptonp',self.m_cos_theta_leptonp,'m_cos_theta_leptonp/F')
        t_out.Branch('m_angle_dilepton',self.m_angle_dilepton,'m_angle_dilepton/F')
        t_out.Branch('m_delta_pt',self.m_delta_pt,'m_delta_pt/F')
        t_out.Branch('m_energy_neutrino',self.m_energy_neutrino,'m_energy_neutrino/F')
        t_out.Branch('m_energy_visible',self.m_energy_visible,'m_energy_visible/F')
        t_out.Branch('m_energy_leptonm',self.m_energy_leptonm,'m_energy_leptonm/F')
        t_out.Branch('m_energy_leptonp',self.m_energy_leptonp,'m_energy_leptonp/F')  

        for i in xrange(tmp_entries): 
            t_in.GetEntry(i)
            #Plot cuts histrogram before cut
            self.plot_before_cut(t_in)
            #Cut eventflow and fill histrogram
            self.cut(t_in,t_out)
            #record the select efficiency         
            self.out_eff(t_in,self.N,infile)
        #Write cut flow histrogram
        self.cut_his_write()
        t_out.Write()
        fout.Close()

if __name__ == '__main__':    
    start_time = time.clock()
    CUTFLOW = Cutflow()
    CUTFLOW.run()
    end_time = time.clock()
print('Running time: %s Seconds'%(end_time-start_time))