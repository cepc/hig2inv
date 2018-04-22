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
	printf "\n\t%-5s  %-40s\n"  "0.1.2"    "Select candidates from signal and background samples" 
	printf "\n\t%-5s  %-40s\n"  "0.1.3"    "Draw plots of signal and background" 
	printf "\nDATE\n"
	printf "\n\t%-5s\n" "AUGUST 2016"     
}


if [[ $# -eq 0 ]]; then
	usage
fi


option=$1

case $option in 
	0.1.1) echo "Running on signal and background samples..."
		unset MARLIN_DLL
		export MARLIN_DLL=./lib/libhig2inv.so
		rm rawdata -rf
		mkdir rawdata
		Marlin steer/signal.steer 
		# Marlin steer/bkg.steer 
	;;

0.1.2) echo "Selecting events from signal and background samples..."
	if [ ! -d "presel" ]; then
		mkdir presel
	fi
	python scripts/sel_events.py rawdata/signal.root presel/signal.root
	;;
   
esac

