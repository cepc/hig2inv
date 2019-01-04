#!/usr/bin/env python
""" 
Plot summary histograms  
"""

__author__ = "Tanyh <tanyuhang@ihep.ac.cn>"
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
    sample = sys.argv[1:]
    fs = get_files_from_sample(sample,processname)
    c = ROOT.TCanvas('c', 'c', 200, 10, 700, 500)
    if "processname == qqH":
        draw_after_cut_dijet_Pt(sample, c, fs, processname)
        draw_after_cut_dijet_Pz(sample, c, fs, processname)
        draw_after_cut_dijet_ang(sample, c, fs, processname)
        draw_after_cut_dijet_phi(sample, c, fs, processname)
        draw_after_cut_dijet_e(sample, c, fs, processname)
        draw_after_cut_dijet_m(sample, c, fs, processname)
        draw_after_cut_dijet_rec_m(sample, c, fs, processname)
        draw_after_cut_dijet_p(sample, c, fs, processname)	
    else:
        draw_after_cut_Pt(sample, c, fs, processname)
        draw_after_cut_Pz(sample, c, fs, processname)
        draw_after_cut_theta(sample, c, fs, processname)
        draw_after_cut_vis(sample, c, fs, processname)
        draw_after_cut_Mmumu(sample, c, fs, processname)
        draw_after_cut_Mrecoil(sample, c, fs, processname)
        draw_after_cut_ep(sample, c, fs, processname)



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

    if 'zorw' in sample:
        fs.append(ROOT.TFile('run/'+processname+'/'+'total/hist/zorw.root'))
        
    if '2f' in sample:
        fs.append(ROOT.TFile('run/'+processname+'/'+'total/hist/2f.root'))




    return fs

def get_common_objects_to_draw(fs, hname, leg):
    hs = []

    leg.SetTextSize(0.)
    leg.SetFillColor(0)
    leg.SetFillStyle(0)
    leg.SetLineWidth(0)
    leg.SetShadowColor(0)

    for f in fs:
        h = f.Get(hname)
        if fs.index(f) == 0:        
            h.SetLineColor(2)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 1:

            h.SetLineColor(22)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 2:

            h.SetLineColor(5)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 3:

            h.SetLineColor(6)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 4:

            h.SetLineColor(7)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)
 
        elif fs.index(f) == 5:

            h.SetLineColor(42)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 6:

            h.SetLineColor(9)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 7:

            h.SetLineColor(3)
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

#    if sample in ['bkg_add_sig']:
#        leg.AddEntry(h, "bkg_add_sig")

    if sample in ['mumuH_inv','eeH_inv','qqH_inv']:
        leg.AddEntry(h, "signal")

    elif sample in ['ZZ']:
        leg.AddEntry(h, "ZZ")

    elif sample in ['WW']:
        leg.AddEntry(h, "WW")

    elif sample in ['single_z']:
        leg.AddEntry(h, "single_z")

    elif sample in ['single_w']:
        leg.AddEntry(h, "single_w")

    elif sample in ['zzorww']:
        leg.AddEntry(h, "zzorww")

    elif sample in ['zorw']:
        leg.AddEntry(h, "zorw")

    elif sample in ['2f']:
        leg.AddEntry(h, "2fbkg")
        
#    else:
#        raise NameError(sample)

    return leg


def draw_after_cut_n_moun(sample, c, fs, processname):
    hname = 'after_cut_number_moun'
    figfile = 'fig/'+processname+'/'+'after/hig2inv_after_cut_n_moun.pdf'

    leg = ROOT.TLegend(0.7, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)
    for h in hs:
        if hs.index(h) == 1:
            h.SetXTitle('M(#pi^{+}#pi^{-}) (GeV/c^{2})')
            h.SetYTitle('Events/(1Gev/C^{2})')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle() 
            h.SetMarkerStyle(1)
            h.SetMaximum(1000);
            h.Draw()
    for h in hs:
        if not hs.index(h) == 1:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_after_cut_n_photon(sample, c, fs, processname):
    hname = 'after_cut_n_photon'
    figfile = 'fig/'+processname+'/'+'after/hig2inv_after_cut_n_photon.pdf'
    leg = ROOT.TLegend(0.7, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 1:
            h.SetXTitle('N_{#gamma}')
            h.SetYTitle('Events/(1Gev/C^{2})')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
            h.SetMaximum(15000);
            h.Draw()
    for h in hs:
        if not hs.index(h) == 1:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def  draw_after_cut_Pt(sample, c, fs, processname):
    hname = 'after_cut_Pt'
    figfile = 'fig/'+processname+'/'+'after/hig2inv_after_cut_Pt.pdf'
    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 1:
            if processname == "mumuH":
                h.SetXTitle('P_{t}^{#mu^{+}#mu^{-}} (GeV/c)')
                h.SetMaximum(1000)
            if processname == "eeH":
                h.SetXTitle('P_{t}^{e^{+}e^{-}} (GeV/c)')
                h.SetMaximum(600)
            h.SetYTitle('Events/(1Gev/C^{2})')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)

            h.Draw()
    for h in hs:
        if not hs.index(h) == 1:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_after_cut_Pz(sample, c, fs, processname):
    hname = 'after_cut_Pz'
    figfile = 'fig/'+processname+'/'+'after/hig2inv_after_cut_Pz.pdf'
    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 1:
            if processname == "mumuH":
                h.SetXTitle('|P_{z}^{#mu^{+}#mu^{-}}| (GeV/c)')
            if processname == "eeH":
                h.SetXTitle('|P_{z}^{e^{+}e^{-}}| (GeV/c)')
                h.SetMaximum(300)
            h.SetYTitle('Events/(1Gev/C^{2})')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)

            h.Draw()
    for h in hs:
        if not hs.index(h) == 1:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_after_cut_theta(sample, c, fs, processname):
    hname = 'after_cut_theta'
    figfile = 'fig/'+processname+'/'+'after/hig2inv_after_cut_theta.pdf'

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 1:
            if processname == "mumuH":
                h.SetXTitle('#Delta#phi_{#mu^{+}#mu^{-}}')
            if processname == "eeH":
                h.SetXTitle('#Delta#phi_{e^{+}e^{-}}')
                h.SetMaximum(300)
            h.SetYTitle('Events/(1Gev/C^{2})')
            h.SetMarkerStyle(1)
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()

            h.Draw()
    for h in hs:
        if not hs.index(h) == 1:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_after_cut_vis(sample, c, fs, processname):
    hname = 'after_cut_vis'
    figfile = 'fig/'+processname+'/'+'after/hig2inv_after_cut_vis.pdf'

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 1:
            if processname == "mumuH":
                h.SetMaximum(3000)
            if processname == "eeH": 
                h.SetMaximum(600)          
            h.SetXTitle('Visible Energy (GeV/c^{2})')
            h.SetYTitle('Events/(1Gev/C^{2})')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 1:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_after_cut_Mmumu(sample, c, fs, processname):
    hname = 'after_cut_Mmumu'
    figfile = 'fig/'+processname+'/'+'after/hig2inv_after_cut_Mmumu.pdf'
    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 1:
            if processname == "mumuH":
                h.SetXTitle('M_{#mu^{+}#mu^{-}}(GeV/c^{2})')
                h.SetMaximum(2000)
            if processname == "eeH":
                h.SetXTitle('M_{e^{+}e^{-}}(GeV/c^{2})')
                h.SetMaximum(1000)
            h.SetYTitle('Events/(1Gev/C^{2})')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)

            h.Draw()
    for h in hs:
        if not hs.index(h) == 1:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def  draw_after_cut_Mrecoil(sample, c, fs, processname):
    hname = 'after_cut_Mrecoil'
    figfile = 'fig/'+processname+'/'+'after/hig2inv_after_cut_Mrecoil.pdf'
    check_outfile_path(figfile)

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 1:
            if processname == "mumuH":
                  h.SetXTitle('M_{recoil}^{#mu^{+}#mu^{-}}(GeV/c^{2})')
            if processname == "eeH":
                h.SetXTitle('M_{recoil}^{e^{+}e^{-}}(GeV/c^{2})')
                h.SetMaximum(800)
            h.SetYTitle('Events/(1Gev/C^{2})')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            #            h.GetYaxis().SetRange(0,400)
            # Plot title?
            h.SetMarkerStyle(1)
            #            h.SetMinimum(0.1)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 1:
            #            h.GetYaxis().SetLimits(0,1000)
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)

def  draw_after_cut_ep(sample, c, fs, processname):
    hname = 'after_cut_ep'
    figfile = 'fig/'+processname+'/'+'after/hig2inv_after_cut_ep.pdf'
    check_outfile_path(figfile)

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 1:

            h.SetXTitle('E/P')
            h.SetYTitle('Events/(1Gev/C^{2})')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            #            h.GetYaxis().SetRange(0,400)
            # Plot title?
            h.SetMarkerStyle(1)
            #            h.SetMinimum(0.1)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 1:
            #            h.GetYaxis().SetLimits(0,1000)
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_after_cut_dijet_Pt(sample, c, fs, processname):
    
    hname = 'after_cut_dijet_pt'
    figfile = 'fig/'+processname+'/'+'after/hig2inv_after_cut_dijet_pt.pdf'
    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 1:

            h.SetXTitle('P_{t}^{dijet}(GeV/c)')	
            h.SetMaximum(14000)
#            h.SetMinimum(0.00000000000001)		
            h.SetYTitle('Events/(0.5GeV)')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)

            h.Draw()
    for h in hs:
        if not hs.index(h) == 1:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)

def draw_after_cut_dijet_Pz(sample, c, fs, processname):

    hname = 'after_cut_dijet_pz'
    figfile = 'fig/'+processname+'/'+'after/hig2inv_after_cut_dijet_pz.pdf'
    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 1:
            h.SetXTitle('|P_{z}^{dijet}| (GeV/c)')
            h.SetMaximum(2000)
#            h.SetMinimum(0.0000001)
            h.SetYTitle('Events/(0.5GeV)')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 1:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)

def draw_after_cut_dijet_ang(sample, c, fs, processname):
    hname = 'after_cut_dijet_dang'
    figfile = 'fig/'+processname+'/'+'after/hig2inv_after_cut_dijet_dang.pdf'

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 1:
            h.SetXTitle('|#angle_{dijet}|')
            h.SetMaximum(20000)
#            h.SetMinimum(0.000001)

            h.SetYTitle('Events/(0.5GeV)')
            h.SetMarkerStyle(1)
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.Draw()
    for h in hs:
        if not hs.index(h) == 1:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)	
def draw_after_cut_dijet_phi(sample, c, fs, processname):
    hname = 'after_cut_dijet_dphi'
    figfile = 'fig/'+processname+'/'+'after/hig2inv_after_cut_dijet_dphi.pdf'

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 1:
            h.SetXTitle('#Delta#phi_{dijet}')
            h.SetMaximum(5000)
#            h.SetMinimum(0)
            h.SetYTitle('Events/(0.5GeV)')
            h.SetMarkerStyle(1)
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.Draw()
    for h in hs:
        if not hs.index(h) == 1:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)
def draw_after_cut_dijet_e(sample, c, fs, processname):

    hname = 'after_cut_dijet_e'
    figfile = 'fig/'+processname+'/'+'after/hig2inv_after_cut_dijet_e.pdf'

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 1:
            h.SetXTitle('Energy of dijet (GeV)')
            h.SetYTitle('Events/(0.5GeV)')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
            h.SetMaximum(12000)
#            h.SetMinimum(0.000001)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 1:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)	

def draw_after_cut_dijet_m(sample, c, fs, processname):

    hname = 'after_cut_dijet_m'
    figfile = 'fig/'+processname+'/'+'after/hig2inv_after_cut_dijet_m.pdf'
    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 1:
            h.SetXTitle('M_{dijet}(GeV)')
            h.SetMaximum(15000)
#            h.SetMinimum(0.0001)
            h.SetYTitle('Events/(0.5GeV)')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 1:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)

def draw_after_cut_dijet_rec_m(sample, c, fs, processname):	
    hname = 'after_cut_m_dijet_rec_m'
    figfile = 'fig/'+processname+'/'+'after/hig2inv_after_cut_m_dijet_rec_m.pdf'
    check_outfile_path(figfile)

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 1:

            h.SetXTitle('M_{recoil}^{dijet}(GeV)')
            h.SetMaximum(10000)
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
        if not hs.index(h) == 1:
            #            h.GetYaxis().SetLimits(0,1000)
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)

def draw_after_cut_dijet_p(sample, c, fs, processname):	
    hname = 'after_cut_dijet_p'
    figfile = 'fig/'+processname+'/'+'after/hig2inv_after_cut_m_dijet_p.pdf'
    check_outfile_path(figfile)

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 1:

            h.SetXTitle('P_{dijet}(GeV)')
            h.SetMaximum(10000)
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
        if not hs.index(h) == 1:
            #            h.GetYaxis().SetLimits(0,1000)
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)

if __name__ == '__main__':
    main()
