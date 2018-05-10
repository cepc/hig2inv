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
		if [ ! -d "rawdata" ]; then
			mkdir rawdata
		fi
		rm job/job.out -rf
		mkdir  job/job.out
		rm job/job.err -rf
		mkdir job/job.err
		cd job
		./signal_e1e1h.sh
		./bhabha.sh
		./e3e3.sh
		./sze_l0mu.sh
		./sze_l0nunu.sh
		./sze_l0tau.sh
		./szeorsw_l0l.sh
		./zz_l0taumu.sh
	;;

	0.1.2) echo "Synthetizing seperated ROOT files..."
		if [ ! -d "data" ]; then
			mkdir data
		fi
		cd data
		hadd signal_e1e1h.root ../rawdata/signal_e1e1h*
		hadd bhabha.root ../rawdata/bhabha*
		hadd e3e3.root ../rawdata/e3e3*
		hadd sze_l0mu.root ../rawdata/sze_l0mu*
		hadd sze_l0nunu.root ../rawdata/sze_l0nunu*
		hadd sze_l0tau.root ../rawdata/sze_l0tau*
		hadd szeorsw_l0l.root ../rawdata/szeorsw_l0l*
		hadd zz_l0taumu.root ../rawdata/zz_l0taumu*
	;;

	0.1.3) echo "Selecting events from signal and background samples..."
		if [ ! -d "presel" ]; then
			mkdir presel
		fi
		cd scripts
		python sel_events.py
	;;

	0.1.4) echo "Drawing plots of signal and background..."
		if [ ! -d "figs" ]; then
			mkdir figs
		fi
		cd scripts
		python plot_recoil_mass.py
	;;

esac

