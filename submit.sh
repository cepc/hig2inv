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
		python sel_events.py ../data/signal_e1e1h.root ../presel/signal_e1e1h.root
		python sel_events.py ../data/bhabha.root ../presel/bhabha.root
		python sel_events.py ../data/e3e3.root ../presel/e3e3.root
		python sel_events.py ../data/sze_l0mu.root ../presel/sze_l0mu.root
		python sel_events.py ../data/sze_l0nunu.root ../presel/sze_l0nunu.root
		python sel_events.py ../data/sze_l0tau.root ../presel/sze_l0tau.root
		python sel_events.py ../data/szeorsw_l0l.root ../presel/szeorsw_l0l.root
		python sel_events.py ../data/zz_l0taumu.root ../presel/zz_l0taumu.root
	;;

	0.1.4) echo "Drawing plots of signal and background..."
		if [ ! -d "figs" ]; then
			mkdir figs
		fi
		cd scripts
		python plot_recoil_mass.py
	;;

esac

