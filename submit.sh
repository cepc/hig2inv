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

		./signal_e2e2h.sh
		./bkg_e2e2h_qq.sh
		./bkg_e2e2h_sze_l.sh
		./bkg_e2e2h_ww_l.sh
		./bkg_e2e2h_ww_sl.sh
		./bkg_e2e2h_zz_h.sh
		./bkg_e2e2h_zz_l.sh
		./bkg_e2e2h_zz_sl0mu_down.sh
		./bkg_e2e2h_zz_sl0mu_up.sh
		./bkg_e2e2h_zz_sl0nu_down.sh
		./bkg_e2e2h_zz_sl0nu_up.sh
	;;

	0.1.2) echo "Synthetizing seperated ROOT files..."
		if [ ! -d "presel" ]; then
			mkdir presel
		fi
		cd presel
		hadd signal_e2e2h.root ../splitted/signal_e2e2h*
		hadd bkg_e2e2h_qq.root ../splitted/bkg_e2e2h_qq*
		hadd bkg_e2e2h_sze_l.root ../splitted/bkg_e2e2h_sze_l*
		hadd bkg_e2e2h_ww_l.root ../splitted/bkg_e2e2h_ww_l*
		hadd bkg_e2e2h_ww_sl.root ../splitted/bkg_e2e2h_ww_sl* 
		hadd bkg_e2e2h_zz_h.root ../splitted/bkg_e2e2h_zz_h*
		hadd bkg_e2e2h_zz_l.root ../splitted/bkg_e2e2h_zz_l*
		hadd bkg_e2e2h_zz_sl0mu_down.root ../splitted/bkg_e2e2h_zz_sl0mu_down*
		hadd bkg_e2e2h_zz_sl0mu_up.root ../splitted/bkg_e2e2h_zz_sl0mu_up*
		hadd bkg_e2e2h_zz_sl0nu_down.root ../splitted/bkg_e2e2h_zz_sl0nu_down*
		hadd bkg_e2e2h_zz_sl0nu_up.root ../splitted/bkg_e2e2h_zz_sl0nu_up*
	;;

	0.1.3) echo "Selecting events from signal and background samples..."
		if [ ! -d "sel" ]; then
			mkdir sel
		fi
		cd scripts
		python sel_events_e2e2h.py ../presel/signal_e2e2h.root ../sel/signal_e2e2h.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_qq.root ../sel/bkg_e2e2h_qq.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_sze_l.root ../sel/bkg_e2e2h_sze_l.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_ww_l.root ../sel/bkg_e2e2h_ww_l.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_ww_sl.root ../sel/bkg_e2e2h_ww_sl.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_zz_h.root ../sel/bkg_e2e2h_zz_h.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_zz_l.root ../sel/bkg_e2e2h_zz_l.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_zz_sl0mu_down.root ../sel/bkg_e2e2h_zz_sl0mu_down.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_zz_sl0mu_up.root ../sel/bkg_e2e2h_zz_sl0mu_up.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_zz_sl0nu_down.root ../sel/bkg_e2e2h_zz_sl0nu_down.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_zz_sl0nu_up.root ../sel/bkg_e2e2h_zz_sl0nu_up.root
	;;

	0.1.4) echo "Drawing plots of signal and background..."
		if [ ! -d "figs" ]; then
			mkdir figs
		fi
		cd scripts
		python plot_recoil_mass.py
	;;

esac

