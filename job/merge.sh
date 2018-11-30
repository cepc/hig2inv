#!/bin/bash
cd ./run/bg/hist 
hadd ../../total/hist/2f.root e1e1/* e2e2/* e3e3/* qq/*
hadd ../../total/hist/ZZ.root  zz*/* 
hadd ../../total/hist/WW.root  ww*/*
hadd ../../total/hist/single_z.root sz*/*
hadd ../../total/hist/single_w.root sw*/*
hadd ../../total/hist/zzorww.root zzorww*/*
hadd ../../total/hist/zorw.root szeorsw*/*
hadd ../../total/hist/total_bkg.root ../../total/hist/*
cd ../plot
hadd ../../total/plot/2f.root e1e1/* e2e2/* e3e3/* qq/*
hadd ../../total/plot/ZZ.root  zz*/* 
hadd ../../total/plot/WW.root  ww*/*
hadd ../../total/plot/single_z.root sz*/*
hadd ../../total/plot/single_w.root sw*/*
hadd ../../total/plot/zzorww.root zzorww*/*
hadd ../../total/plot/zorw.root szeorsw*/*
hadd ../../total/plot/total_bkg.root ../../total/plot/*
cd ../../total 
hadd bkg_add_sig.root ./hist/total_bkg.root ../e2E2h_invi/hist/e2E2h_invi/ana_File_merged_scale_1.root 