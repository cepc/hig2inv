#!/bin/bash
cd ../presel
hadd signal_e2e2h.root ../splitted/signal_e2e2h*
hadd bkg_e2e2h_sw_l.root ../splitted/bkg_e2e2h_sw_l*
hadd bkg_e2e2h_sw_sl.root ../splitted/bkg_e2e2h_sw_sl*
hadd bkg_e2e2h_qq.root ../splitted/bkg_e2e2h_qq*
hadd bkg_e2e2h_szeorsw_l.root ../splitted/bkg_e2e2h_szeorsw_l*
hadd bkg_e2e2h_sze_sl.root ../splitted/bkg_e2e2h_sze_sl*
hadd bkg_e2e2h_sznu_l.root ../splitted/bkg_e2e2h_sznu_l*
hadd bkg_e2e2h_sznu_sl.root ../splitted/bkg_e2e2h_sznu_sl*
hadd bkg_e2e2h_ww_h.root ../splitted/bkg_e2e2h_ww_h*
hadd bkg_e2e2h_sze_l.root ../splitted/bkg_e2e2h_sze_l*
hadd bkg_e2e2h_ww_l.root ../splitted/bkg_e2e2h_ww_l*
hadd bkg_e2e2h_ww_sl.root ../splitted/bkg_e2e2h_ww_sl* 
hadd bkg_e2e2h_zz_h.root ../splitted/bkg_e2e2h_zz_h*
hadd bkg_e2e2h_zz_l.root ../splitted/bkg_e2e2h_zz_l*
hadd bkg_e2e2h_zzorww_h.root ../splitted/bkg_e2e2h_zzorww_h*
hadd bkg_e2e2h_zzorww_l.root ../splitted/bkg_e2e2h_zzorww_l*
hadd bkg_e2e2h_zz_sl0mu_down.root ../splitted/bkg_e2e2h_zz_sl0mu_down*
hadd bkg_e2e2h_zz_sl0mu_up.root ../splitted/bkg_e2e2h_zz_sl0mu_up*
hadd bkg_e2e2h_zz_sl0nu_down.root ../splitted/bkg_e2e2h_zz_sl0nu_down*
hadd bkg_e2e2h_zz_sl0nu_up.root ../splitted/bkg_e2e2h_zz_sl0nu_up*
hadd bkg_e2e2h_zz_sl0tau_down.root ../splitted/bkg_e2e2h_zz_sl0tau_down*
hadd bkg_e2e2h_zz_sl0tau_up.root ../splitted/bkg_e2e2h_zz_sl0tau_up*
hadd bkg_e2e2h_bhabha.root ../splitted/bkg_e2e2h_bhabha*
hadd bkg_e2e2h_e2e2.root ../splitted/bkg_e2e2h_e2e2*
hadd bkg_e2e2h_e3e3.root ../splitted/bkg_e2e2h_e3e3*
hadd bkg_e2e2h_n2n2.root ../splitted/bkg_e2e2h_n2n2*
hadd bkg_e2e2h_bb.root ../splitted/bkg_e2e2h_bb*
hadd bkg_e2e2h_cc.root ../splitted/bkg_e2e2h_cc*
hadd bkg_e2e2h_dd.root ../splitted/bkg_e2e2h_dd*
cd ../job
bash add_scale
cd ../presel
hadd bkg_e2e2h.root bkg_e2e2h_*root
hadd bkg_e2e2h_2fermions.root bkg_e2e2h_qq.root bkg_e2e2h_bhabha.root bkg_e2e2h_e2e2.root bkg_e2e2h_e3e3.root bkg_e2e2h_n2n2.root bkg_e2e2h_bb.root bkg_e2e2h_cc.root bkg_e2e2h_dd.root
hadd bkg_e2e2h_4fermions.root bkg_e2e2h_sw*root bkg_e2e2h_sze*root bkg_e2e2h_sznu*root bkg_e2e2h_ww*root bkg_e2e2h_zz*root 
