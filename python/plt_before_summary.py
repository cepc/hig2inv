#!/usr/bin/env python   
"""
Plot summary histograms 
"""

__author__ = "SHI Xin <shixin@ihep.ac.cn>" 
__copyright__ = "Copyright (c) SHI Xin"
__created__ = "[2016-07-25 Mon 09:22]" 

import os
import sys 
import copy
import ROOT 
from tools import check_outfile_path, set_root_style


def main():
    set_root_style(stat=0, grid=0) 
    ROOT.gStyle.SetPadLeftMargin(0.15)

    sample = sys.argv[1:]
    fs = get_files_from_sample(sample)
    c = ROOT.TCanvas('c', 'c', 200, 10, 700, 500)


#    draw_before_cut_n_moun(sample, c, fs) 
    draw_before_cut_n_photon(sample, c, fs)
    draw_before_cut_Pt(sample, c, fs) 
    draw_before_cut_Pz(sample, c, fs) 
    draw_before_cut_theta(sample, c, fs) 
    draw_before_cut_vis(sample, c, fs)
    draw_before_cut_Mmumu(sample, c, fs)
    draw_before_cut_Mrecoil(sample, c, fs)

    
    

def get_files_from_sample(sample):
    fs = []
    
    if 'signal' in sample:
        fs.append(ROOT.TFile('run/e2E2h_invi/hist/ana_File_merged_1.root')) 

     
    if 'background' in sample:
        fs.append(ROOT.TFile('run/bg/plot/all_bkg_merge.root'))	

    if 'bkg+sig' in sample:
        fs.append(ROOT.TFile('run/total/bkg_add_sig.root'))

   

     
    return fs 

def get_common_objects_to_draw(fs, hname, leg):
    hs = []

    leg.SetTextSize(0.03)
    leg.SetFillColor(0)
    leg.SetFillStyle(0)
    leg.SetLineColor(0)
    leg.SetShadowColor(0)
    
    for f in fs:
        h = f.Get(hname)
        if fs.index(f) == 0:
            #h.Sumw2()
            h.Scale(50)
            h.SetLineColor(ROOT.kRed)
            h.SetFillColor(ROOT.kRed)
            a1=copy.copy(h)
            
        elif fs.index(f) == 1:
#            h.Scale(1.68) 
            h.SetLineColor(3)
            h.SetLineWidth(1)
#            h.SetLineStyleString(9)
            h.SetMarkerStyle(ROOT.kFullDotLarge)
            a2=copy.copy(h)	
            h.Draw()
        elif fs.index(f) == 2:
            h.Add(a1,a2,1,1)
            h.SetLineColor(ROOT.kOrange)
            h.SetFillColor(ROOT.kOrange)
#            h.GetYaxis().SetRange(0,1000)
#            h.Draw()
        leg = leg_add_entry_hist(leg, f, h)    
        hs.append(h) 
            
    return  hs, leg 


def leg_add_entry_hist(leg, f, h):
    sample = f.GetName()
    sample = sample.split('/')[1] 

    if sample in ['e2E2h_invi']:
        leg.AddEntry(h, "signal")

    elif sample in ['bg']:
        leg.AddEntry(h, "background")

    elif sample in ['total']:
        leg.AddEntry(h, "bkg+signal")

    else:
        raise NameError(sample)

    return leg

    
def draw_before_cut_n_moun(sample, c, fs):
    hname = 'before_cut_number_moun'
    figfile = 'fig/before/hig2inv_before_cut_n_moun.pdf'
        
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)  
    for h in hs:
        if hs.index(h) == 2:
            h.SetXTitle('M(#pi^{+}#pi^{-}) (GeV/c^{2})') 
            h.SetYTitle('Events')
            h.GetXaxis().SetLabelSize(0.03)
            h.GetYaxis().SetLabelSize(0.03)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(ROOT.kFullDotLarge)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 2:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_before_cut_n_photon(sample, c, fs):
    hname = 'before_cut_n_photon'
    figfile = 'fig/before/hig2inv_before_cut_n_photon.pdf' 
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 

    for h in hs:
        if hs.index(h) == 2:
            h.SetXTitle('N_{#gamma}')
            h.SetYTitle('N_{charged}')
            h.SetZTitle('Events')
            h.GetXaxis().SetLabelSize(0.03)
            h.GetYaxis().SetLabelSize(0.03)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle() 
            h.SetMarkerStyle(ROOT.kFullDotLarge)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 2:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def  draw_before_cut_Pt(sample, c, fs):
    hname = 'before_cut_Pt'
    figfile = 'fig/before/hig2inv_before_cut_Pt.pdf'   
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 
    
    for h in hs:
        if hs.index(h) == 2:
            h.SetXTitle('P_{t}^{#mu^{+}#mu^{-}} (GeV/c)')
            h.SetYTitle('Events') 
            h.GetXaxis().SetLabelSize(0.03)
            h.GetYaxis().SetLabelSize(0.03)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()			
            h.SetMarkerStyle(ROOT.kFullDotLarge)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 2:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_before_cut_Pz(sample, c, fs):
    hname = 'before_cut_Pz'
    figfile = 'fig/before/hig2inv_before_cut_Pz.pdf'  
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 

    for h in hs:
        if hs.index(h) == 2:
            h.SetXTitle('|P_{z}^{#mu^{+}#mu^{-}}| (GeV/c)')
            h.SetYTitle('Events')
            h.GetXaxis().SetLabelSize(0.03)
            h.GetYaxis().SetLabelSize(0.03)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()			
            h.SetMarkerStyle(ROOT.kFullDotLarge)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 2:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_before_cut_theta(sample, c, fs):
    hname = 'before_cut_theta'
    figfile = 'fig/before/hig2inv_before_cut_theta.pdf'   
    
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 
    
    for h in hs:
        if hs.index(h) == 2:
            h.SetXTitle('|cos#theta_{#mu^{+}#mu^{-}}|')
            h.SetYTitle('Events')
            h.GetXaxis().SetLabelSize(0.03)
            h.GetYaxis().SetLabelSize(0.03)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()			
            h.SetMarkerStyle(ROOT.kFullDotLarge)
            h.SetMinimum(0.1)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 2:
            h.Draw('same') 

    leg.Draw()
    c.SaveAs(figfile)


def draw_before_cut_vis(sample, c, fs):
    hname = 'before_cut_vis'
    figfile = 'fig/before/higinv_before_cut_vis.pdf' 
    
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 
    
    for h in hs:
        if hs.index(h) == 2:
            h.SetXTitle('Visible Energy (GeV/c^{2})')
            h.SetYTitle('Events')
            h.GetXaxis().SetLabelSize(0.03)
            h.GetYaxis().SetLabelSize(0.03)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(ROOT.kFullDotLarge)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 2:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_before_cut_Mmumu(sample, c, fs):
    hname = 'before_cut_Mmumu'
    figfile = 'fig/before/hig2inv_before_cut_Mmumu.pdf'     
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 

    for h in hs:
        if hs.index(h) == 2:
            h.SetXTitle('M_{#mu^{+}#mu^{-}}(GeV/c^{2})')
            h.SetYTitle('Events')
            h.GetXaxis().SetLabelSize(0.03)
            h.GetYaxis().SetLabelSize(0.03)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(ROOT.kFullDotLarge)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 2:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def  draw_before_cut_Mrecoil(sample, c, fs):
    hname = 'before_cut_Mrecoil'
    figfile = 'fig/before/hig2inv_before_cut_Mrecoil.pdf'
    check_outfile_path(figfile)
        
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 

    for h in hs:
        if hs.index(h) == 2:
            h.SetXTitle('M(recoil(#mu^{+}#mu^{-}) (GeV/c^{2})') 
            h.SetYTitle('Events')
            h.GetXaxis().SetLabelSize(0.03)
            h.GetYaxis().SetLabelSize(0.03)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
#            h.GetYaxis().SetRange(0,400)
            # Plot title?
            h.SetMarkerStyle(ROOT.kFullDotLarge)
#            h.SetMinimum(0.1)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 2:
#            h.GetYaxis().SetLimits(0,1000)
            h.Draw('same')
        
    leg.Draw()
    c.SaveAs(figfile)


    
if __name__ == '__main__':
    main()
