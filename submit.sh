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
	printf "\n\t%-5s  %-40s\n"  "0.1.3"    "Draw distributions of cut variables and calculate ratios of bachground over signal" 
	printf "\n\t%-5s  %-40s\n"  "0.1.4"    "Calculate cut flows of siganl and background samples" 
	printf "\n\t%-5s  %-40s\n"  "0.1.5"    "Draw plots of signal and background" 
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
		./bkg_e2e2h_sw_l.sh
		./bkg_e2e2h_sw_sl.sh
		./bkg_e2e2h_qq.sh
		./bkg_e2e2h_szeorsw_l.sh
		./bkg_e2e2h_sze_sl.sh
		./bkg_e2e2h_sznu_l.sh
		./bkg_e2e2h_sznu_sl.sh
		./bkg_e2e2h_ww_h.sh
		./bkg_e2e2h_sze_l.sh
		./bkg_e2e2h_ww_l.sh
		./bkg_e2e2h_ww_sl.sh
		./bkg_e2e2h_zz_h.sh
		./bkg_e2e2h_zz_l.sh
		./bkg_e2e2h_zzorww_h.sh
		./bkg_e2e2h_zzorww_l.sh
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
		hadd bkg_e2e2h.root bkg_e2e2h_*root
	;;

	0.1.3) echo "Drawing distributions of cut variables and calculate ratios of bachground over signal..."
		if [ ! -d "figs" ]; then
			mkdir figs
		fi
		if [ ! -d "logfiles" ]; then
			mkdir logfiles
		fi
		cd job
		hep_sub -g physics cut_variable_job -e job.err -o job.out
	;;

	0.1.4) echo "Calculating cut flows of siganl and background samples..."
		if [ ! -d "sel" ]; then
			mkdir sel
		fi
		cd scripts
		python sel_events_e2e2h.py ../presel/signal_e2e2h.root ../sel/signal_e2e2h.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_qq.root ../sel/bkg_e2e2h_qq.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_sw_l.root ../sel/bkg_e2e2h_sw_l.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_sw_sl.root ../sel/bkg_e2e2h_sw_sl.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_szeorsw_l.root ../sel/bkg_e2e2h_szeorsw_l.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_sze_sl.root ../sel/bkg_e2e2h_sze_sl.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_sznu_l.root ../sel/bkg_e2e2h_sznu_l.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_sznu_sl.root ../sel/bkg_e2e2h_sznu_sl.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_ww_h.root ../sel/bkg_e2e2h_ww_h.root
		python sel_events_e2e2h.py ../pesel/bkg_e2e2h_zzorww_h.root ../sel/bkg_e2e2h_zzorww_h.root
		python sel_events_e2e2h.py ../pesel/bkg_e2e2h_zzorww_l.root ../sel/bkg_e2e2h_zzorww_l.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_sze_l.root ../sel/bkg_e2e2h_sze_l.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_ww_l.root ../sel/bkg_e2e2h_ww_l.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_ww_sl.root ../sel/bkg_e2e2h_ww_sl.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_zz_h.root ../sel/bkg_e2e2h_zz_h.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_zz_l.root ../sel/bkg_e2e2h_zz_l.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_zz_sl0mu_down.root ../sel/bkg_e2e2h_zz_sl0mu_down.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_zz_sl0mu_up.root ../sel/bkg_e2e2h_zz_sl0mu_up.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_zz_sl0nu_down.root ../sel/bkg_e2e2h_zz_sl0nu_down.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h_zz_sl0nu_up.root ../sel/bkg_e2e2h_zz_sl0nu_up.root
		python sel_events_e2e2h.py ../presel/bkg_e2e2h.root ../sel/bkg_e2e2h.root
	;;

	0.1.5) echo "Drawing plots of signal and background..."
		if [ ! -d "figs" ]; then
			mkdir figs
		fi
		cd scripts
		# python plot_recoil_mass.py
	;;

esac

