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

    sample = sys.argv[1:]
    fs = get_files_from_sample(sample)
    c = ROOT.TCanvas('c', 'c', 200, 10, 700, 500)

#    draw_after_cut_n_moun(sample, c, fs)
    draw_after_cut_n_photon(sample, c, fs)
    draw_after_cut_Pt(sample, c, fs)
    draw_after_cut_Pz(sample, c, fs)
    draw_after_cut_theta(sample, c, fs)
    draw_after_cut_vis(sample, c, fs)
    draw_after_cut_Mmumu(sample, c, fs)
    draw_after_cut_Mrecoil(sample, c, fs)




def get_files_from_sample(sample):
    fs = []
    if 'sig+bkg' in sample:
        fs.append(ROOT.TFile('run/total/bkg_add_sig.root'))
        
    if 'signal' in sample:
        fs.append(ROOT.TFile('run/e2E2h_invi/hist/e2E2h_invi/ana_File_merged_scale_1.root'))

    if 'ZZ' in sample:
        fs.append(ROOT.TFile('run/total/hist/ZZ.root'))

    if 'WW' in sample:
        fs.append(ROOT.TFile('run/total/hist/WW.root'))

    if 'single_z' in sample:
        fs.append(ROOT.TFile('run/total/hist/single_z.root'))

    if 'single_w' in sample:
        fs.append(ROOT.TFile('run/total/hist/single_w.root'))

    if 'zzorww' in sample:
        fs.append(ROOT.TFile('run/total/hist/zzorww.root'))	

    if 'zorw' in sample:
        fs.append(ROOT.TFile('run/total/hist/zorw.root'))
        
    if '2f' in sample:
        fs.append(ROOT.TFile('run/total/hist/2f.root'))




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
            h.SetLineColor(4)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 1:
#            h.Scale(0.03)
            h.SetLineColor(2)
            h.SetLineWidth(2)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 2:
            h.SetLineColor(22)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 3:
            h.SetLineColor(5)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 4:
            h.SetLineColor(6)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 5:
            h.SetLineColor(7)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)
 
        elif fs.index(f) == 6:
            h.SetLineColor(42)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 7:
            h.SetLineColor(9)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 8:
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

    if sample in ['ana_File_merged_scale_1']:
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


def draw_after_cut_n_moun(sample, c, fs):
    hname = 'after_cut_number_moun'
    figfile = 'fig/after/hig2inv_after_cut_n_moun.pdf'

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
            h.Draw()
    for h in hs:
        if not hs.index(h) == 0:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_after_cut_n_photon(sample, c, fs):
    hname = 'after_cut_n_photon'
    figfile = 'fig/after/hig2inv_after_cut_n_photon.pdf'
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
            h.SetMaximum(5000);
            h.Draw()
    for h in hs:
        if not hs.index(h) == 0:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def  draw_after_cut_Pt(sample, c, fs):
    hname = 'after_cut_Pt'
    figfile = 'fig/after/hig2inv_after_cut_Pt.pdf'
    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 1:
            h.SetXTitle('P_{t}^{#mu^{+}#mu^{-}} (GeV/c)')
            h.SetYTitle('Events/(1Gev/C^{2})')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
            h.SetMaximum(200)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 0:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_after_cut_Pz(sample, c, fs):
    hname = 'after_cut_Pz'
    figfile = 'fig/after/hig2inv_after_cut_Pz.pdf'
    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 1:
            h.SetXTitle('|P_{z}^{#mu^{+}#mu^{-}}| (GeV/c)')
            h.SetYTitle('Events/(1Gev/C^{2})')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
            h.SetMaximum(80)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 0:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_after_cut_theta(sample, c, fs):
    hname = 'after_cut_theta'
    figfile = 'fig/after/hig2inv_after_cut_theta.pdf'

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 1:
            h.SetXTitle('|cos#theta_{#mu^{+}#mu^{-}}|')
            h.SetYTitle('Events/(1Gev/C^{2})')
            h.SetMarkerStyle(1)
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMaximum(210);
            h.Draw()
    for h in hs:
        if not hs.index(h) == 0:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_after_cut_vis(sample, c, fs):
    hname = 'after_cut_vis'
    figfile = 'fig/after/higinv_after_cut_vis.pdf'

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 1:
            h.SetXTitle('Visible Energy (GeV/c^{2})')
            h.SetYTitle('Events/(1Gev/C^{2})')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
            h.SetMaximum(700);
            h.Draw()
    for h in hs:
        if not hs.index(h) == 0:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_after_cut_Mmumu(sample, c, fs):
    hname = 'after_cut_Mmumu'
    figfile = 'fig/after/hig2inv_after_cut_Mmumu.pdf'
    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 1:
            h.SetXTitle('M_{#mu^{+}#mu^{-}}(GeV/c^{2})')
            h.SetYTitle('Events/(1Gev/C^{2})')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
            h.SetMaximum(600);
            h.Draw()
    for h in hs:
        if not hs.index(h) == 0:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def  draw_after_cut_Mrecoil(sample, c, fs):
    hname = 'after_cut_Mrecoil'
    figfile = 'fig/after/hig2inv_after_cut_Mrecoil.pdf'
    check_outfile_path(figfile)

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 1:

            h.SetXTitle('M_{recoil}^{#mu^{+}#mu^{-}}(GeV/c^{2})')
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
        if not hs.index(h) == 0:
            #            h.GetYaxis().SetLimits(0,1000)
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)



if __name__ == '__main__':
    main()
