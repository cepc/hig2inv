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
		cd scripts
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_qq.root e2e2h_qq 0
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_qq.root e2e2h_qq 1
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_qq.root e2e2h_qq 2
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_qq.root e2e2h_qq 3
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_qq.root e2e2h_qq 4
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_qq.root e2e2h_qq 5
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_qq.root e2e2h_qq 6
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_qq.root e2e2h_qq 7
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_qq.root e2e2h_qq 8
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sw_l.root e2e2h_sw_l 0
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sw_l.root e2e2h_sw_l 1
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sw_l.root e2e2h_sw_l 2
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sw_l.root e2e2h_sw_l 3
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sw_l.root e2e2h_sw_l 4
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sw_l.root e2e2h_sw_l 5
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sw_l.root e2e2h_sw_l 6
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sw_l.root e2e2h_sw_l 7
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sw_l.root e2e2h_sw_l 8
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sw_sl.root e2e2h_sw_l 0
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sw_sl.root e2e2h_sw_l 1
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sw_sl.root e2e2h_sw_l 2
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sw_sl.root e2e2h_sw_l 3
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sw_sl.root e2e2h_sw_l 4
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sw_sl.root e2e2h_sw_l 5
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sw_sl.root e2e2h_sw_l 6
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sw_sl.root e2e2h_sw_l 7
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sw_sl.root e2e2h_sw_l 8
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_szeorsw_l.root e2e2h_szeorsw_l 0
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_szeorsw_l.root e2e2h_szeorsw_l 1
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_szeorsw_l.root e2e2h_szeorsw_l 2
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_szeorsw_l.root e2e2h_szeorsw_l 3
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_szeorsw_l.root e2e2h_szeorsw_l 4
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_szeorsw_l.root e2e2h_szeorsw_l 5
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_szeorsw_l.root e2e2h_szeorsw_l 6
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_szeorsw_l.root e2e2h_szeorsw_l 7
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_szeorsw_l.root e2e2h_szeorsw_l 8
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sze_sl.root e2e2h_sze_sl 0
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sze_sl.root e2e2h_sze_sl 1
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sze_sl.root e2e2h_sze_sl 2
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sze_sl.root e2e2h_sze_sl 3
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sze_sl.root e2e2h_sze_sl 4
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sze_sl.root e2e2h_sze_sl 5
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sze_sl.root e2e2h_sze_sl 6
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sze_sl.root e2e2h_sze_sl 7
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sze_sl.root e2e2h_sze_sl 8
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sznu_l.root e2e2h_sznu_l 0
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sznu_l.root e2e2h_sznu_l 1
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sznu_l.root e2e2h_sznu_l 2
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sznu_l.root e2e2h_sznu_l 3
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sznu_l.root e2e2h_sznu_l 4
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sznu_l.root e2e2h_sznu_l 5
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sznu_l.root e2e2h_sznu_l 6
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sznu_l.root e2e2h_sznu_l 7
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sznu_l.root e2e2h_sznu_l 8
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sznu_sl.root e2e2h_sznu_sl 0
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sznu_sl.root e2e2h_sznu_sl 1
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sznu_sl.root e2e2h_sznu_sl 2
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sznu_sl.root e2e2h_sznu_sl 3
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sznu_sl.root e2e2h_sznu_sl 4
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sznu_sl.root e2e2h_sznu_sl 5
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sznu_sl.root e2e2h_sznu_sl 6
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sznu_sl.root e2e2h_sznu_sl 7
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sznu_sl.root e2e2h_sznu_sl 8
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_h.root e2e2h_ww_h 0
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_h.root e2e2h_ww_h 1
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_h.root e2e2h_ww_h 2
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_h.root e2e2h_ww_h 3
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_h.root e2e2h_ww_h 4
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_h.root e2e2h_ww_h 5
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_h.root e2e2h_ww_h 6
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_h.root e2e2h_ww_h 7
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_h.root e2e2h_ww_h 8
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sze_l.root e2e2h_sze_l 0 
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sze_l.root e2e2h_sze_l 1 
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sze_l.root e2e2h_sze_l 2 
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sze_l.root e2e2h_sze_l 3 
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sze_l.root e2e2h_sze_l 4 
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sze_l.root e2e2h_sze_l 5 
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sze_l.root e2e2h_sze_l 6 
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sze_l.root e2e2h_sze_l 7 
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_sze_l.root e2e2h_sze_l 8 
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_l.root e2e2h_ww_l 0
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_l.root e2e2h_ww_l 1
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_l.root e2e2h_ww_l 2
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_l.root e2e2h_ww_l 3
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_l.root e2e2h_ww_l 4
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_l.root e2e2h_ww_l 5
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_l.root e2e2h_ww_l 6
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_l.root e2e2h_ww_l 7
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_l.root e2e2h_ww_l 8
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_sl.root e2e2h_ww_sl 0
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_sl.root e2e2h_ww_sl 1
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_sl.root e2e2h_ww_sl 2
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_sl.root e2e2h_ww_sl 3
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_sl.root e2e2h_ww_sl 4
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_sl.root e2e2h_ww_sl 5
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_sl.root e2e2h_ww_sl 6
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_sl.root e2e2h_ww_sl 7
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_ww_sl.root e2e2h_ww_sl 8
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_h.root e2e2h_zz_h 0
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_h.root e2e2h_zz_h 1
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_h.root e2e2h_zz_h 2
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_h.root e2e2h_zz_h 3
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_h.root e2e2h_zz_h 4
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_h.root e2e2h_zz_h 5
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_h.root e2e2h_zz_h 6
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_h.root e2e2h_zz_h 7
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_h.root e2e2h_zz_h 8
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_l.root e2e2h_zz_l 0
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_l.root e2e2h_zz_l 1
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_l.root e2e2h_zz_l 2
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_l.root e2e2h_zz_l 3
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_l.root e2e2h_zz_l 4
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_l.root e2e2h_zz_l 5
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_l.root e2e2h_zz_l 6
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_l.root e2e2h_zz_l 7
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_l.root e2e2h_zz_l 8
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zzorww_h.root e2e2h_zzorww_h 0
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zzorww_h.root e2e2h_zzorww_h 1
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zzorww_h.root e2e2h_zzorww_h 2
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zzorww_h.root e2e2h_zzorww_h 3
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zzorww_h.root e2e2h_zzorww_h 4
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zzorww_h.root e2e2h_zzorww_h 5
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zzorww_h.root e2e2h_zzorww_h 6
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zzorww_h.root e2e2h_zzorww_h 7
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zzorww_h.root e2e2h_zzorww_h 8
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zzorww_l.root e2e2h_zzorww_l 0
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zzorww_l.root e2e2h_zzorww_l 1
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zzorww_l.root e2e2h_zzorww_l 2
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zzorww_l.root e2e2h_zzorww_l 3
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zzorww_l.root e2e2h_zzorww_l 4
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zzorww_l.root e2e2h_zzorww_l 5
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zzorww_l.root e2e2h_zzorww_l 6
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zzorww_l.root e2e2h_zzorww_l 7
		python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zzorww_l.root e2e2h_zzorww_l 8
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0mu_down.root e2e2h_zz_sl0mu_down 0
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0mu_down.root e2e2h_zz_sl0mu_down 1
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0mu_down.root e2e2h_zz_sl0mu_down 2
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0mu_down.root e2e2h_zz_sl0mu_down 3
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0mu_down.root e2e2h_zz_sl0mu_down 4
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0mu_down.root e2e2h_zz_sl0mu_down 5
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0mu_down.root e2e2h_zz_sl0mu_down 6
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0mu_down.root e2e2h_zz_sl0mu_down 7
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0mu_down.root e2e2h_zz_sl0mu_down 8
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0mu_up.root e2e2h_zz_sl0mu_up 0
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0mu_up.root e2e2h_zz_sl0mu_up 1
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0mu_up.root e2e2h_zz_sl0mu_up 2
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0mu_up.root e2e2h_zz_sl0mu_up 3
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0mu_up.root e2e2h_zz_sl0mu_up 4
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0mu_up.root e2e2h_zz_sl0mu_up 5
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0mu_up.root e2e2h_zz_sl0mu_up 6
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0mu_up.root e2e2h_zz_sl0mu_up 7
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0mu_up.root e2e2h_zz_sl0mu_up 8
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0nu_down.root e2e2h_zz_sl0nu_down 0
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0nu_down.root e2e2h_zz_sl0nu_down 1
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0nu_down.root e2e2h_zz_sl0nu_down 2
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0nu_down.root e2e2h_zz_sl0nu_down 3
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0nu_down.root e2e2h_zz_sl0nu_down 4
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0nu_down.root e2e2h_zz_sl0nu_down 5
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0nu_down.root e2e2h_zz_sl0nu_down 6
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0nu_down.root e2e2h_zz_sl0nu_down 7
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0nu_down.root e2e2h_zz_sl0nu_down 8
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0nu_up.root e2e2h_zz_sl0nu_up 0
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0nu_up.root e2e2h_zz_sl0nu_up 1
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0nu_up.root e2e2h_zz_sl0nu_up 2
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0nu_up.root e2e2h_zz_sl0nu_up 3
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0nu_up.root e2e2h_zz_sl0nu_up 4
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0nu_up.root e2e2h_zz_sl0nu_up 5
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0nu_up.root e2e2h_zz_sl0nu_up 6
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0nu_up.root e2e2h_zz_sl0nu_up 7
		# python compare.py ../presel/signal_e2e2h.root ../presel/bkg_e2e2h_zz_sl0nu_up.root e2e2h_zz_sl0nu_up 8
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

