import os
import sys
import ROOT
import math


x0 = 0.0031
sigma = 0.0080

mu_t = [0] * 130000
Prob = [0] * 130000

nbin = 10000
x_min = -0.05
x_max = 0.05
h_gaus = ROOT.TH1F('hgaus', 'hgaus', nbin, x_min, x_max)
sum = 0.0
for i in range(0, nbin):
    mu_t[i] = x_min + i * (x_max - x_min) / nbin
    c1 = 1 / math.sqrt(2 * 3.141592653858 * sigma * sigma)
    Prob[i] = c1 * math.exp(-(x0 - mu_t[i]) *
                            (x0 - mu_t[i]) / 2 / sigma / sigma)
    h_gaus.SetBinContent(i + 1, Prob[i])

    if (mu_t[i] > 0.0):
        sum = sum + Prob[i]

ROOT.gStyle.SetCanvasColor(0)
c = ROOT.TCanvas("c", "", 800, 600)
c.cd()
h_gaus.Draw()

c.SetTicks(1, 1)

ratio = 0.95
tmp_sum = 0.0
hmax = 0.0

for j in range(0, nbin):
    if Prob[j] > hmax:
        hmax = Prob[j]

    if mu_t[j] >= 0.0:
        tmp_sum += Prob[j]

    if tmp_sum >= sum * ratio:
        j_CL = j
        CL_mu = mu_t[j]
        break

print '95% CL limit ='
print CL_mu

t1 = ROOT.TLine(CL_mu, 0, CL_mu, hmax * 1.05)
t1.Draw()

ROOT.gPad.SetLeftMargin(0.2)
ROOT.gPad.SetBottomMargin(0.17)
ROOT.gPad.GetFrame().SetBorderMode(0)

h_gaus_shaded = ROOT.TH1F('hgaus_shaded', 'hgaus_shaded', nbin, x_min, x_max)
for i in range(0, nbin):
    if mu_t[i] >= 0 and CL_mu > mu_t[i]:
        h_gaus_shaded.SetBinContent(i + 1, Prob[i])
    else:
        h_gaus_shaded.SetBinContent(i + 1, 0.0)
h_gaus_shaded.Draw('same')
h_gaus_shaded.SetFillColor(4)
h_gaus.Draw('same')
h_gaus.SetLineColor(1)
h_gaus.SetLineWidth(2)
h_gaus_shaded.SetLineColor(1)

ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptTitle(0)

h_gaus.SetName("")
h_gaus.SetTitle("")
h_gaus.GetXaxis().SetTitleFont(22)
h_gaus.GetYaxis().SetTitleFont(22)
h_gaus.GetXaxis().SetTitleOffset(1.2)
h_gaus.GetYaxis().SetTitleOffset(0.9)
h_gaus.GetXaxis().SetTitleSize(0.06)
h_gaus.GetYaxis().SetTitleSize(0.06)
h_gaus.GetXaxis().SetLabelSize(0.03)
h_gaus.GetYaxis().SetLabelSize(0.03)
h_gaus.GetXaxis().SetTitle("Br(#mu^{+}#mu^{-}Higgs#rightarrow invisible)")
h_gaus.GetYaxis().SetTitle("Likelihood(in arbitrary unit)")
h_gaus.GetXaxis().CenterTitle()
h_gaus.GetYaxis().CenterTitle()
h_gaus.GetYaxis().SetNdivisions(500)
h_gaus.GetYaxis().SetNdivisions(500)
c.Draw()
c.Print("fig/upper_limit.pdf")
