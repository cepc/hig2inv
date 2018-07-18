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
		bash run_sample
	;;

	0.1.2) echo "Synthetizing seperated ROOT files..."
		if [ ! -d "presel" ]; then
			mkdir presel
		fi
		cd job
		./hadd.sh
	;;

	0.1.3) echo "Drawing distributions of cut variables and calculate ratios of bachground over signal..."
		if [ ! -d "figs" ]; then
			mkdir figs
		fi
		if [ ! -d "logfiles" ]; then
			mkdir logfiles
		fi
		cd job
		hep_sub -g physics cut_variable_job -e job.err/ -o job.out/
	;;

	0.1.4) echo "Calculating cut flows of siganl and background samples..."
		if [ ! -d "sel" ]; then
			mkdir sel
		fi
		if [ ! -d "logfiles" ]; then
			mkdir logfiles
		fi
		cd job
		hep_sub -g physics cut_flow_job -e job.err/ -o job.out/
	;;

	0.1.5) echo "Drawing plots of signal and background..."
		if [ ! -d "figs" ]; then
			mkdir figs
		fi
		# python plot_recoil_mass.py
	;;

esac

