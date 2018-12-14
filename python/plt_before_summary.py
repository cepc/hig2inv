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


<<<<<<< HEAD
def main(): 
=======
def main():
>>>>>>> cepc/master
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
    draw_before_cut_ep(sample, c, fs)


<<<<<<< HEAD
=======


>>>>>>> cepc/master

def get_files_from_sample(sample):
    fs = []       
    if 'signal' in sample:
<<<<<<< HEAD
        fs.append(ROOT.TFile('run/total/hist/ffH_inv.root'))

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




=======
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




>>>>>>> cepc/master
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
            h.Scale(1.0/509150.0)
            h.SetLineColor(2)
<<<<<<< HEAD
            h.SetLineWidth(1)
=======
            h.SetLineWidth(2)
>>>>>>> cepc/master
            h.SetMarkerStyle(1)

        elif fs.index(f) == 1:
            h.Scale(1.0/23955150.0)
            h.SetLineColor(22)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 2:
            h.Scale(1.0/44763316.0)
            h.SetLineColor(5)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 3:
            h.Scale(1.0/8955800.0)
            h.SetLineColor(6)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 4:
            h.Scale(1.0/17426250.0)
            h.SetLineColor(7)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)
 
        elif fs.index(f) == 5:
            h.Scale(1.0/18250750.0)
            h.SetLineColor(42)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 6:
            h.Scale(1.0/1247400.0)
            h.SetLineColor(9)
            h.SetLineWidth(1)
            h.SetMarkerStyle(1)

        elif fs.index(f) == 7:
<<<<<<< HEAD
            h.Scale(1.0/444816800.0)
=======
            h.Scale(1.0/67108864.0)
>>>>>>> cepc/master
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


<<<<<<< HEAD
    if sample in ['ffH_inv']:
=======
    if sample in ['ana_File_merged_scale_1']:
>>>>>>> cepc/master
        leg.AddEntry(h, "signal")

    elif sample in ['ZZ']:
        leg.AddEntry(h, "ZZ")

    elif sample in ['WW']:
        leg.AddEntry(h, "WW")

    elif sample in ['single_z']:
        leg.AddEntry(h, "single_z")
<<<<<<< HEAD

    elif sample in ['single_w']:
        leg.AddEntry(h, "single_w")

    elif sample in ['zzorww']:
        leg.AddEntry(h, "zzorww")

=======

    elif sample in ['single_w']:
        leg.AddEntry(h, "single_w")

    elif sample in ['zzorww']:
        leg.AddEntry(h, "zzorww")

>>>>>>> cepc/master
    elif sample in ['zorw']:
        leg.AddEntry(h, "zorw")

    elif sample in ['2f']:
        leg.AddEntry(h, "2fbkg")
        
    else:
        raise NameError(sample)

    return leg


def draw_before_cut_n_moun(sample, c, fs):
    hname = 'before_cut_number_moun'
    figfile = 'fig/before/hig2inv_before_cut_n_moun.pdf'

    leg = ROOT.TLegend(0.7, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)
    for h in hs:
        if hs.index(h) == 7:
            h.SetXTitle('M(#pi^{+}#pi^{-}) (GeV/c^{2})')
            h.SetYTitle('Normalized to 1')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
<<<<<<< HEAD
            h.SetMaximum(6000000)
            h.SetMinimum(10)
=======
            h.SetMaximum(6000000);
            h.SetMinimum(10);
>>>>>>> cepc/master
            h.Draw()
    for h in hs:
        if not hs.index(h) == 7:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_before_cut_n_photon(sample, c, fs):
    hname = 'before_cut_n_photon'
    figfile = 'fig/before/hig2inv_before_cut_n_photon.pdf'
    leg = ROOT.TLegend(0.7, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 7:
            h.SetXTitle('N_{#gamma}')
            h.SetYTitle('Normalized to 1')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
<<<<<<< HEAD
            h.SetMaximum(0.02)
            h.SetMinimum(0.0001)
=======
            h.SetMaximum(1);
            h.SetMinimum(0.0001);
>>>>>>> cepc/master
            h.Draw()
    for h in hs:
        if not hs.index(h) == 7:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def  draw_before_cut_Pt(sample, c, fs):
    hname = 'before_cut_Pt'
    figfile = 'fig/before/hig2inv_before_cut_Pt.pdf'
    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 7:
            h.SetXTitle('P_{t}^{#mu^{+}#mu^{-}} (GeV/c)')
            h.SetYTitle('Normalized to 1')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
<<<<<<< HEAD
            h.SetMaximum(0.003)
            h.SetMinimum(0.00000000000001)
=======
            h.SetMaximum(0.02);
            h.SetMinimum(0.00000000000001);
>>>>>>> cepc/master
            h.Draw()
    for h in hs:
        if not hs.index(h) == 7:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_before_cut_Pz(sample, c, fs):
    hname = 'before_cut_Pz'
    figfile = 'fig/before/hig2inv_before_cut_Pz.pdf'
    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 7:
            h.SetXTitle('|P_{z}^{#mu^{+}#mu^{-}}| (GeV/c)')
            h.SetYTitle('Normalized to 1')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
<<<<<<< HEAD
            h.SetMaximum(0.0006)
            h.SetMinimum(0.0000001)
=======
            h.SetMaximum(0.0006);
            h.SetMinimum(0.0000001);
>>>>>>> cepc/master
            h.Draw()
    for h in hs:
        if not hs.index(h) == 7:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_before_cut_theta(sample, c, fs):
    hname = 'before_cut_theta'
    figfile = 'fig/before/hig2inv_before_cut_theta.pdf'

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 7:
<<<<<<< HEAD
            h.SetXTitle('|#phi_{#mu^{+}#mu^{-}}|')
=======
            h.SetXTitle('|cos#theta_{#mu^{+}#mu^{-}}|')
>>>>>>> cepc/master
            h.SetYTitle('Normalized to 1')
            h.SetMarkerStyle(1)
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
<<<<<<< HEAD
            h.SetMaximum(0.001)
            h.SetMinimum(0)
=======
#            h.SetMaximum(4000000);
#            h.SetMinimum(10);
>>>>>>> cepc/master
            h.Draw()
    for h in hs:
        if not hs.index(h) == 7:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_before_cut_vis(sample, c, fs):
    hname = 'before_cut_vis'
<<<<<<< HEAD
    figfile = 'fig/before/hig2inv_before_cut_vis.pdf'
=======
    figfile = 'fig/before/higinv_before_cut_vis.pdf'
>>>>>>> cepc/master

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 7:
            h.SetXTitle('Visible Energy (GeV/c^{2})')
            h.SetYTitle('Normalized to 1')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
<<<<<<< HEAD
            h.SetMaximum(0.06)
            h.SetMinimum(0.000001)
=======
            h.SetMaximum(0.06);
            h.SetMinimum(0.000001);
>>>>>>> cepc/master
            h.Draw()
    for h in hs:
        if not hs.index(h) == 7:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_before_cut_Mmumu(sample, c, fs):
    hname = 'before_cut_Mmumu'
    figfile = 'fig/before/hig2inv_before_cut_Mmumu.pdf'
    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 7:
            h.SetXTitle('M_{#mu^{+}#mu^{-}}(GeV/c^{2})')
            h.SetYTitle('Normalized to 1')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMarkerStyle(1)
<<<<<<< HEAD
            h.SetMaximum(0.004)
            h.SetMinimum(0.0001)
=======
#            h.SetMaximum(1200000);
#            h.SetMinimum(0);
>>>>>>> cepc/master
            h.Draw()
    for h in hs:
        if not hs.index(h) == 7:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def  draw_before_cut_Mrecoil(sample, c, fs):
    hname = 'before_cut_Mrecoil'
    figfile = 'fig/before/hig2inv_before_cut_Mrecoil.pdf'
    check_outfile_path(figfile)

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 7:

            h.SetXTitle('M_{recoil}^{#mu^{+}#mu^{-}}(GeV/c^{2})')
            h.SetYTitle('Normalized to 1')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            #            h.GetYaxis().SetRange(0,400)
            # Plot title?
            h.SetMarkerStyle(1)
#            gPad.SetLogy();
<<<<<<< HEAD
            h.SetMaximum(0.005)
            h.SetMinimum(0.00000000000001)
=======
            h.SetMaximum(0.0025);
            h.SetMinimum(0);
>>>>>>> cepc/master
            #            h.SetMinimum(0.1)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 7:
            #            h.GetYaxis().SetLimits(0,1000)
            h.Draw('same')

<<<<<<< HEAD
    leg.Draw()
    c.SaveAs(figfile)
def  draw_before_cut_ep(sample, c, fs):
    hname = 'before_cut_ep'
    figfile = 'fig/before/hig2inv_before_cut_ep.pdf'
    check_outfile_path(figfile)

    leg = ROOT.TLegend(0.8, 0.71, 0.9, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg)

    for h in hs:
        if hs.index(h) == 7:

            h.SetXTitle('E/P')
            h.SetYTitle('Events/(1Gev/C^{2})')
            h.GetXaxis().SetLabelSize(0.02)
            h.GetYaxis().SetLabelSize(0.02)
            h.GetXaxis().CenterTitle()
            h.GetYaxis().CenterTitle()
            h.SetMaximum(0.003)
            h.SetMinimum(0.00000000000001)
            #            h.GetYaxis().SetRange(0,400)
            # Plot title?
            h.SetMarkerStyle(1)
            #            h.SetMinimum(0.1)
            h.Draw()
    for h in hs:
        if not hs.index(h) == 7:
            #            h.GetYaxis().SetLimits(0,1000)
            h.Draw('same')

=======
>>>>>>> cepc/master
    leg.Draw()
    c.SaveAs(figfile)


<<<<<<< HEAD
=======

>>>>>>> cepc/master
if __name__ == '__main__':
    main()
