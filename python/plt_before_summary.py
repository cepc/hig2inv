#!/usr/bin/env python
"""  
Plot summary histograms 
"""
 
__author__ = "Tanyh <shixin@ihep.ac.cn>"
__copyright__ = "Copyright (c) Tanyh"
__created__ = "[2016-07-25 Mon 09:22]"

import os
import sys
import copy
import ROOT
from tools import check_outfile_path, set_root_style


def main():  
    set_root_style(stat=0, grid=0)
    ROOT.gStyle.SetPadLeftMargin(0.15)
    processname = sys.argv[1]
    sample = sys.argv[2:]

    fs = get_files_from_sample(sample,processname)
    c = ROOT.TCanvas('c', 'c', 200, 10, 700, 500)
    if processname == "qqH":
        draw_before_cut_dijet_Pt(sample, c, fs, processname)
        draw_before_cut_TauTauM(sample, c, fs, processname)
        draw_before_cut_dijet_ang(sample, c, fs, processname)
        draw_before_cut_dijet_phi(sample, c, fs, processname)
        draw_before_cut_dijet_e(sample, c, fs, processname)
        draw_before_cut_dijet_m(sample, c, fs, processname)
        draw_before_cut_dijet_rec_m(sample, c, fs, processname)
        draw_before_cut_dijet_p(sample, c, fs, processname)	
        draw_before_cut_vis(sample, c, fs, processname)
        draw_before_cut_cos_miss(sample, c, fs, processname)						
#    draw_before_cut_n_moun(sample, c, fs, processname)
#	draw_before_cut_n_photon(sample, c, fs, processname)
    else:
        draw_before_cut_Pt(sample, c, fs, processname)
        draw_before_cut_vdt(sample, c, fs, processname)
        draw_before_cut_theta(sample, c, fs, processname)
        draw_before_cut_vis(sample, c, fs, processname)
        draw_before_cut_Mmumu(sample, c, fs, processname)
        draw_before_cut_Mrecoil(sample, c, fs, processname)
        draw_before_cut_ep(sample, c, fs, processname)



def get_files_from_sample(sample,processname):
    fs = []       
    if 'signal' in sample:
        if processname == "mumuH":
            fs.append(ROOT.TFile('run/'+processname+'/'+'total/hist/mumuH_inv.root'))
        if processname == "eeH":
            fs.append(ROOT.TFile('run/'+processname+'/'+'total/hist/eeH_inv.root'))	
        if processname == "qqH":
            fs.append(ROOT.TFile('run/'+processname+'/'+'total/hist/qqH_inv.root'))	

    if 'ZZ' in sample:
        fs.append(ROOT.TFile('run/'+processname+'/'+'total/hist/ZZ.root'))

    if 'WW' in sample:
        fs.append(ROOT.TFile('run/'+processname+'/'+'total/hist/WW.root'))

    if 'single_z' in sample:
        fs.append(ROOT.TFile('run/'+processname+'/'+'total/hist/single_z.root'))

    if 'single_w' in sample:
        fs.append(ROOT.TFile('run/'+processname+'/'+'total/hist/single_w.root'))

    if 'zzorww' in sample:
        fs.append(ROOT.TFile('run/'+processname+'/'+'total/hist/zzorww.root'))	

    if 'szorsw' in sample:
        fs.append(ROOT.TFile('run/'+processname+'/'+'total/hist/sz_sw.root'))	
        
    if '2f' in sample:
        fs.append(ROOT.TFile('run/'+processname+'/'+'total/hist/2f.root'))

    if 'ZH_visible' in sample:
        fs.append(ROOT.TFile('run/'+processname+'/'+'total/hist/ZH_visible.root'))


    return fs

def get_common_objects_to_draw(fs, hname, leg, processname):
    hs = []

    leg.SetTextSize(0.)
    leg.SetFillColor(0)
    leg.SetFillStyle(0)
    leg.SetLineWidth(0)
    leg.SetShadowColor(0)

    for f in fs:
        h = f.Get(hname)
        if fs.index(f) == 0:
            if processname == "eeH":				
                h.Scale(1.0/19712.0)
            if processname == "mumuH":
                h.Scale(1.0/18956.0)
            if processname == "qqH":
                h.Scale(1.0/342025.0)                 
            h.SetLineColor(2)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 1:
            h.Scale(1.0/6389430.0)
            h.SetLineColor(22)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 2:
            h.Scale(1.0/50826214.0)
            h.SetLineColor(5)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 3:
            h.Scale(1.0/7932735.0)
            h.SetLineColor(42)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 4:
            h.Scale(1.0/19517400.0)
            h.SetLineColor(6)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 5:
            h.Scale(1.0/1397088.0)
            h.SetLineColor(7)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)
 
        elif fs.index(f) == 6:
            h.Scale(1.0/20440840.0)       
            h.SetLineColor(14)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 7:
            h.Scale(1.0/498194816.0)
            h.SetLineColor(3)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 8:
            h.Scale(1.0/1140495.0)       
            h.SetLineColor(12)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        else:
            print "Sample name misses, please check that!"
            sys.exit() 		

        leg = leg_add_entry_hist(leg, f, h)
        hs.append(h)

    return  hs, leg


def leg_add_entry_hist(leg, f, h):
    sample = f.GetName()
    sample = sample.split('/')[-1]
    sample = sample.split('.root')[0]


    if sample in ['mumuH_inv','eeH_inv','qqH_inv']:
        leg.AddEntry(h, "signal")

    elif sample in ['ZZ']:
        leg.AddEntry(h, "ZZ")

    elif sample in ['WW']:
        leg.AddEntry(h, "WW")

    elif sample in ['sz_sw']:
        leg.AddEntry(h, "szorsw")

    elif sample in ['single_z']:
        leg.AddEntry(h, "single_z")

    elif sample in ['single_w']:
        leg.AddEntry(h, "single_w")

    elif sample in ['zzorww']:
        leg.AddEntry(h, "zzorww")

    elif sample in ['2f']:
        leg.AddEntry(h, "2fbkg")
    elif sample in ['ZH_visible']:
        leg.AddEntry(h, "ZH_visible") 
    else:
        raise NameError(sample)

    return leg


def draw_before_cut_n_moun(sample, c, fs, processname):
    hname = 'before_cut_number_moun'
    figfile = 'fig/'+processname+'/'+'before/hig2inv_before_cut_n_moun.pdf'

    leg = ROOT.TLegend(0.7, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg, processname)
    for h in hs:
        if hs.index(h) == 6:
            if processname == "mumuH":
                h.SetXTitle('M(#pi^{+}#pi^{-}) (GeV)')
            if processname == "eeH":
                h.SetXTitle('M(#pi^{+}#pi^{-}) (GeV)')
                h.SetMaximum(6000000)
                h.SetMinimum(10)
            h.SetYTitle('Normalized to 1')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 6:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_before_cut_n_photon(sample, c, fs, processname):
    hname = 'before_cut_n_photon'
    figfile = 'fig/'+processname+'/'+'before/hig2inv_before_cut_n_photon.pdf'
    leg = ROOT.TLegend(0.7, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg, processname)

    for h in hs:
        if hs.index(h) == 6:
            h.SetXTitle('N_{#gamma}')
            h.SetYTitle('Normalized to 1')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
            h.SetMaximum(0.02)
            h.SetMinimum(0.0001)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 6:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def  draw_before_cut_Pt(sample, c, fs, processname):
    hname = 'before_cut_Pt'
    figfile = 'fig/'+processname+'/'+'before/hig2inv_before_cut_Pt.pdf'
    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg, processname)

    for h in hs:
        if hs.index(h) == 6:
            if processname == "mumuH":
                h.SetXTitle('P_{t}^{#mu^{+}#mu^{-}} (GeV)')
                h.SetMaximum(0.03)
                h.SetMinimum(0.00000000000001)	
            if processname == "eeH":
                h.SetXTitle('P_{t}^{e^{+}e^{-}} (GeV)')	
                h.SetMaximum(0.03)
                h.SetMinimum(0.00000000000001)		
            h.SetYTitle('Normalized to 1')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)

            h.Draw()
    for h in hs: 
        if not hs.index(h) == 6:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_before_cut_vdt(sample, c, fs, processname):
    hname = 'before_cut_vdt'
    figfile = 'fig/'+processname+'/'+'before/hig2inv_before_cut_vdt.pdf'
    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg, processname)

    for h in hs:
        if hs.index(h) == 6:
            if processname == "mumuH":
                h.SetXTitle('the recoil mass of visible minus tau (GeV)')
                h.SetMaximum(0.01)
                h.SetMinimum(0.0000001)
            if processname == "eeH":
                h.SetXTitle('the recoil mass of visible minus tau (GeV)')
                h.SetMaximum(0.01)
                h.SetMinimum(0.0000001)
            h.SetYTitle('Normalized to 1')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 6:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_before_cut_theta(sample, c, fs, processname):
    hname = 'before_cut_theta'
    figfile = 'fig/'+processname+'/'+'before/hig2inv_before_cut_theta.pdf'

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg, processname)

    for h in hs:
        if hs.index(h) == 6:
            if processname == "mumuH":
                h.SetXTitle('#Delta#phi_{#mu^{+}#mu^{-}}')
                h.SetMaximum(0.01)
                h.SetMinimum(0.000001)
            if processname == "eeH":
                h.SetXTitle('#Delta#phi_{e^{+}e^{-}}')
                h.SetMaximum(0.05)
                h.SetMinimum(0)
            h.SetYTitle('Normalized to 1')
            h.SetMarkerStyle(1)
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.Draw()
    for h in hs:
        if not hs.index(h) == 6:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_before_cut_vis(sample, c, fs, processname):
    hname = 'before_cut_vis'
    figfile = 'fig/'+processname+'/'+'before/hig2inv_before_cut_vis.pdf'

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg, processname)

    for h in hs:
        if hs.index(h) == 6:
            h.SetXTitle('Visible Energy (GeV)(raw data)')
            h.SetYTitle('Normalized to 1')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
            h.SetMaximum(0.06)
            h.SetMinimum(0.000001)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 6:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_before_cut_Mmumu(sample, c, fs, processname):
    hname = 'before_cut_Mmumu'
    figfile = 'fig/'+processname+'/'+'before/hig2inv_before_cut_Mmumu.pdf'
    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg, processname)

    for h in hs:
        if hs.index(h) == 6:
            if processname == "mumuH":
                h.SetXTitle('M_{#mu^{+}#mu^{-}}(GeV)')
                h.SetMaximum(0.02)
                h.SetMinimum(0.0001)
            if processname == "eeH":
                h.SetXTitle('M_{e^{+}e^{-}}(GeV)')
                h.SetMaximum(0.04)
                h.SetMinimum(0.0001)
            h.SetYTitle('Normalized to 1')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 6:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def  draw_before_cut_Mrecoil(sample, c, fs, processname):
    hname = 'before_cut_Mrecoil'
    figfile = 'fig/'+processname+'/'+'before/hig2inv_before_cut_Mrecoil.pdf'
    check_outfile_path(figfile)

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg, processname)

    for h in hs:
        if hs.index(h) == 6:
            if processname == "mumuH":
                h.SetXTitle('M_{recoil}^{#mu^{+}#mu^{-}}(GeV)')
                h.SetMaximum(0.06)
                h.SetMinimum(0.0000000000000001)
            if processname == "eeH":
                h.SetXTitle('M_{recoil}^{e^{+}e^{-}}(GeV)')
                h.SetMaximum(0.05)
                h.SetMinimum(0.00000000000001)
            h.SetYTitle('Normalized to 1')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            #            h.GetYaxis().SetRange(0,400)
            # Plot title?
            h.SetMarkerStyle(1)
#            gPad.SetLogy();
            #            h.SetMinimum(0.1)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 6:
            #            h.GetYaxis().SetLimits(0,1000)
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)
def  draw_before_cut_ep(sample, c, fs, processname):
    hname = 'before_cut_ep'
    figfile = 'fig/'+processname+'/'+'before/hig2inv_before_cut_ep.pdf'
    check_outfile_path(figfile)

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg, processname)

    for h in hs:
        if hs.index(h) == 6:

            h.SetXTitle('E/P')
            h.SetYTitle('Events/(1Gev)')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMaximum(0.03)
            h.SetMinimum(0.00000000000001)
            #            h.GetYaxis().SetRange(0,400)
            # Plot title?
            h.SetMarkerStyle(1)
            #            h.SetMinimum(0.1)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 6:
            #            h.GetYaxis().SetLimits(0,1000)
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)

def draw_before_cut_dijet_Pt(sample, c, fs, processname):

    hname = 'before_cut_dijet_pt'
    figfile = 'fig/'+processname+'/'+'before/hig2inv_before_cut_dijet_pt.pdf'
    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg, processname)

    for h in hs:
        if hs.index(h) == 6:

            h.SetXTitle('P_{t}^{dijet}(GeV)(raw data)')	
            h.SetMaximum(0.1)
            h.SetMinimum(0.00000000000001)		
            h.SetYTitle('Normalized to 1')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)

            h.Draw()
    for h in hs:
        if not hs.index(h) == 6:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)

def draw_before_cut_TauTauM(sample, c, fs, processname):

    hname = 'before_cut_TauTauM'
    figfile = 'fig/'+processname+'/'+'before/hig2inv_before_cut_TauTauM.pdf'
    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg, processname)

    for h in hs:
        if hs.index(h) == 6:
            h.SetXTitle('the mass of Candidate tau (GeV)(raw data)')
            h.SetMaximum(0.03)
            h.SetMinimum(0.0000001)
            h.SetYTitle('Normalized to 1')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 6:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)

def draw_before_cut_dijet_ang(sample, c, fs, processname):
    hname = 'before_cut_dijet_dang'
    figfile = 'fig/'+processname+'/'+'before/hig2inv_before_cut_dijet_dang.pdf'

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg, processname)

    for h in hs:
        if hs.index(h) == 6:
            h.SetXTitle('|#angle_{dijet}|(raw data)')
            h.SetMaximum(0.1)
            h.SetMinimum(0.000001)

            h.SetYTitle('Normalized to 1')
            h.SetMarkerStyle(1)
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.Draw()
    for h in hs:
        if not hs.index(h) == 6:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)	
def draw_before_cut_dijet_phi(sample, c, fs, processname):
    hname = 'before_cut_dijet_dphi'
    figfile = 'fig/'+processname+'/'+'before/hig2inv_before_cut_dijet_dphi.pdf'

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg, processname)

    for h in hs:
        if hs.index(h) == 6:
            h.SetXTitle('|#Delta#phi_{dijet}|(raw data)')
            h.SetMaximum(0.05)
            h.SetMinimum(0)
            h.SetYTitle('Normalized to 1')
            h.SetMarkerStyle(1)
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.Draw()
    for h in hs:
        if not hs.index(h) == 6:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)
def draw_before_cut_dijet_e(sample, c, fs, processname):

    hname = 'before_cut_dijet_e'
    figfile = 'fig/'+processname+'/'+'before/hig2inv_before_cut_dijet_e.pdf'

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg, processname)

    for h in hs:
        if hs.index(h) == 6:
            h.SetXTitle('Visible Energy (GeV)(raw data)')
            h.SetYTitle('Normalized to 1')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
            h.SetMaximum(0.06)
            h.SetMinimum(0.000001)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 6:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)	

def draw_before_cut_dijet_m(sample, c, fs, processname):

    hname = 'before_cut_dijet_m'
    figfile = 'fig/'+processname+'/'+'before/hig2inv_before_cut_dijet_m.pdf'
    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg, processname)

    for h in hs:
        if hs.index(h) == 6:
            h.SetXTitle('M_{dejet}(GeV)(raw data)')
            h.SetMaximum(0.04)
            h.SetMinimum(0.0001)
            h.SetYTitle('Normalized to 1')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 6:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)

def draw_before_cut_dijet_rec_m(sample, c, fs, processname):	
    hname = 'before_cut_m_dijet_rec_m'
    figfile = 'fig/'+processname+'/'+'before/hig2inv_before_cut_m_dijet_rec_m.pdf'
    check_outfile_path(figfile)

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg, processname)

    for h in hs:
        if hs.index(h) == 6:

            h.SetXTitle('M_{recoil}^{dijet}(GeV)(raw data)')
            h.SetMaximum(0.05)
            h.SetMinimum(0.00000000000001)
            h.SetYTitle('Normalized to 1')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            #            h.GetYaxis().SetRange(0,400)
            # Plot title?
            h.SetMarkerStyle(1)
#            gPad.SetLogy();
            #            h.SetMinimum(0.1)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 6:
            #            h.GetYaxis().SetLimits(0,1000)
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)
def draw_before_cut_dijet_p(sample, c, fs, processname):	
    hname = 'before_cut_dijet_p'
    figfile = 'fig/'+processname+'/'+'before/hig2inv_before_cut_m_dijet_p.pdf'
    check_outfile_path(figfile)

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg, processname)

    for h in hs:
        if hs.index(h) == 6:

            h.SetXTitle('P_{dijet}(GeV)(raw data)')
            h.SetMaximum(0.05)
            h.SetMinimum(0.00000000000001)
            h.SetYTitle('Normalized to 1')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            #            h.GetYaxis().SetRange(0,400)
            # Plot title?
            h.SetMarkerStyle(1)
#            gPad.SetLogy();
            #            h.SetMinimum(0.1)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 6:
            #            h.GetYaxis().SetLimits(0,1000)
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)

def draw_before_cut_cos_miss(sample, c, fs, processname):	
    hname = 'before_cut_cos_miss'
    figfile = 'fig/'+processname+'/'+'before/hig2inv_before_cut_cos_miss.pdf'
    check_outfile_path(figfile)

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg, processname)

    for h in hs:
        if hs.index(h) == 0:

            h.SetXTitle('cos#theta_{miss}(raw data)')
            h.SetMaximum(0.06)
#            h.SetMinimum(0.00000000000001)
            h.SetYTitle('Events/(0.5GeV)')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            #            h.GetYaxis().SetRange(0,400)
            # Plot title?
            h.SetMarkerStyle(1)
#            gPad.SetLogy();
            #            h.SetMinimum(0.1)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 0:
            #            h.GetYaxis().SetLimits(0,1000)
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


if __name__ == '__main__':
    main()
