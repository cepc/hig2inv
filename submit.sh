#!/usr/bin/env bash

# Main driver to submit jobs 
# Author SHI Xin <shixin@ihep.ac.cn>
# Created [2016-08-16 Tue 08:29] 

usage() {
	printf "NAME\n\tsubmit.sh - Main driver to submit jobs\n"
	printf "\nSYNOPSIS\n"
	printf "\n\t%-5s\n" "./submit.sh [OPTION]" 
	printf "\nOPTIONS\n" 
	printf "\n\t%-5s  %-40s\n"  "0.1.1"    "Run on signal and background samples" 
	printf "\n\t%-5s  %-40s\n"  "0.1.2"    "Synthetize seperated ROOT files" 
	printf "\n\t%-5s  %-40s\n"  "0.1.3"    "Select candidates from signal and background samples" 
	printf "\n\t%-5s  %-40s\n"  "0.1.4"    "Draw plots of signal and background" 
	printf "\nDATE\n"
	printf "\n\t%-5s\n" "AUGUST 2016"     
}


if [[ $# -eq 0 ]]; then
	usage
fi


option=$1

case $option in 
	0.1.1) echo "Running on signal and background samples..."
		if [ ! -d "steer" ]; then
			mkdir steer
		fi
		if [ ! -d "splitted" ]; then
			mkdir splitted
		fi
		rm job/job.out -rf
		mkdir  job/job.out
		rm job/job.err -rf
		mkdir job/job.err
		cd job
		./signal_e1e1h.sh
		./signal_e2e2h.sh
		./bkg_e2e2h_bhabha.sh
		./bkg_e2e2h_e2e2.sh
		./bkg_e2e2h_e3e3.sh
		./bkg_e2e2h_sze_l0mu.sh
		./bkg_e2e2h_sze_l0nunu.sh
		./bkg_e2e2h_sze_l0tau.sh
		./bkg_e2e2h_szeorsw_l0l.sh
		./bkg_e2e2h_sze_sl0_dd.sh
		./bkg_e2e2h_sze_sl0_uu.sh
		./bkg_e2e2h_ww_h_ccbs.sh
		./bkg_e2e2h_ww_h_ccds.sh
		./bkg_e2e2h_ww_h_cuxx.sh
		./bkg_e2e2h_ww_h_uubd.sh
		./bkg_e2e2h_ww_h_uusd.sh
		./bkg_e2e2h_ww_sl0muq.sh
		./bkg_e2e2h_ww_sl0tauq.sh
		./bkg_e2e2h_zz_h.sh
		./bkg_e2e2h_zz_l0mumu.sh
		./bkg_e2e2h_zz_l0mu.sh
		./bkg_e2e2h_zz_l0taumu.sh
		./bkg_e2e2h_zz_l0tau.sh
		./bkg_e2e2h_zz_l0tautau.sh
	;;

	0.1.2) echo "Synthetizing seperated ROOT files..."
		if [ ! -d "presel" ]; then
			mkdir presel
		fi
		cd presel
		hadd signal_e1e1h.root ../splitted/signal_e1e1h*
		hadd signal_e2e2h.root ../splitted/signal_e2e2h*
		hadd bkg_e2e2h_bhabha.root ../splitted/bkg_e2e2h_bhabha*
		hadd bkg_e2e2h_e2e2.root ../splitted/bkg_e2e2h_e2e2*
		hadd bkg_e2e2h_e3e3.root ../splitted/bkg_e2e2h_e3e3*
		hadd bkg_e2e2h_sze_l0mu.root ../splitted/bkg_e2e2h_sze_l0mu*
		hadd bkg_e2e2h_sze_l0nunu.root ../splitted/bkg_e2e2h_sze_l0nunu*
		hadd bkg_e2e2h_sze_l0tau.root ../splitted/bkg_e2e2h_sze_l0tau*
		hadd bkg_e2e2h_szeorsw_l0l.root ../splitted/bkg_e2e2h_szeorsw_l0l*
		hadd bkg_e2e2h_sze_sl0_dd.root ../splitted/bkg_e2e2h_sze_sl0_dd*
		hadd bkg_e2e2h_sze_sl0_uu.root ../splitted/bkg_e2e2h_sze_sl0_uu*
		hadd bkg_e2e2h_ww_h_ccbs.root ../splitted/bkg_e2e2h_ww_h_ccbs* 
		hadd bkg_e2e2h_ww_h_ccds.root ../splitted/bkg_e2e2h_ww_h_ccds*
		hadd bkg_e2e2h_ww_h_cuxx.root ../splitted/bkg_e2e2h_ww_h_cuxx*
		hadd bkg_e2e2h_ww_h_uubd.root ../splitted/bkg_e2e2h_ww_h_uubd*
		hadd bkg_e2e2h_ww_h_uusd.root ../splitted/bkg_e2e2h_ww_h_uusd*
		hadd bkg_e2e2h_ww_sl0muq.root ../splitted/bkg_e2e2h_ww_sl0muq*
		hadd bkg_e2e2h_ww_sl0tauq.root ../splitted/bkg_e2e2h_ww_sl0tauq*
		hadd bkg_e2e2h_zz_h.root ../splitted/bkg_e2e2h_zz_h*
		hadd bkg_e2e2h_zz_l0mumu.root ../splitted/bkg_e2e2h_zz_l0mumu*
		hadd bkg_e2e2h_zz_l0mu.root ../splitted/bkg_e2e2h_zz_l0mu*
		hadd bkg_e2e2h_zz_l0taumu.root ../splitted/bkg_e2e2h_zz_l0taumu*
		hadd bkg_e2e2h_zz_l0tau.root ../splitted/bkg_e2e2h_zz_l0tau*
		hadd bkg_e2e2h_zz_l0tautau.root ../splitted/bkg_e2e2h_zz_l0tautau*
	;;

	0.1.3) echo "Selecting events from signal and background samples..."
		if [ ! -d "sel" ]; then
			mkdir sel
		fi
		cd scripts
		python sel_events_e1e1h.py ../presel/signal_e1e1h.root ../sel/signal_e1e1h.root
		python sel_events_e2e2h.py ../presel/signal_e2e2h.root ../sel/signal_e2e2h.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_bhabha.root ../sel/bkg_e2e2h_bhabha.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_e2e2.root ../sel/bkg_e2e2h_e2e2.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_e3e3.root ../sel/bkg_e2e2h_e3e3.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_sze_l0mu.root ../sel/bkg_e2e2h_sze_l0mu.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_sze_l0nunu.root ../sel/bkg_e2e2h_sze_l0nunu.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_sze_l0tau.root ../sel/bkg_e2e2h_sze_l0tau.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_szeorsw_l0l.root ../sel/bkg_e2e2h_szeorsw_l0l.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_sze_sl0_dd.root ../sel/bkg_e2e2h_sze_sl0_dd.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_sze_sl0_uu.root ../sel/bkg_e2e2h_sze_sl0_uu.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_ww_h_ccbs.root ../sel/bkg_e2e2h_ww_h_ccbs.root 
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_ww_h_ccds.root ../sel/bkg_e2e2h_ww_h_ccds.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_ww_h_cuxx.root ../sel/bkg_e2e2h_ww_h_cuxx.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_ww_h_uubd.root ../sel/bkg_e2e2h_ww_h_uubd.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_ww_h_uusd.root ../sel/bkg_e2e2h_ww_h_uusd.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_ww_sl0muq.root ../sel/bkg_e2e2h_ww_sl0muq.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_ww_sl0tauq.root ../sel/bkg_e2e2h_ww_sl0tauq.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_zz_h.root ../sel/bkg_e2e2h_zz_h.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_zz_l0mumu.root ../sel/bkg_e2e2h_zz_l0mumu.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_zz_l0mu.root ../sel/bkg_e2e2h_zz_l0mu.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_zz_l0taumu.root ../sel/bkg_e2e2h_zz_l0taumu.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_zz_l0tau.root ../sel/bkg_e2e2h_zz_l0tau.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_zz_l0tautau.root ../sel/bkg_e2e2h_zz_l0tautau.root
	;;

	0.1.4) echo "Drawing plots of signal and background..."
		if [ ! -d "figs" ]; then
			mkdir figs
		fi
		cd scripts
		python plot_recoil_mass.py
	;;

esac

