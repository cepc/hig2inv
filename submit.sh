#!/usr/bin/env bash        

# Main driver to submit jobs 
# Author SHI Xin <shixin@ihep.ac.cn> 
# Created [2016-08-16 Tue 08:29] 
 
<<<<<<< HEAD
usage() { 
=======
usage() {
>>>>>>> cepc/master
    printf "NAME\n\tsubmit.sh - Main driver to submit jobs\n"
    printf "\nSYNOPSIS\n"
    printf "\n\t%-5s\n" "./submit.sh [OPTION]" 
    printf "\nOPTIONS\n" 
    printf "\n\t%-5s  %-40s\n"  "0.1.1"    "Run on signal and background samples" 
    printf "\n\t%-5s  %-40s\n"  "0.1.2"    "Synthetize seperated ROOT files" 
    printf "\n\t%-5s  %-40s\n"  "0.1.3"    "Draw distributions of cut variables and calculate ratios of bachground over signal" 
    printf "\n\t%-5s  %-40s\n"  "0.1.4"    "Calculate cut flows of siganl and background samples" 
    printf "\n\t%-5s  %-40s\n"  "0.1.5"    "Apply BDT cut"
    printf "\n\t%-5s  %-40s\n"  "0.1.6"    "Synthetize signal and background ROOT files"
    printf "\n\t%-5s  %-40s\n"  "0.1.7"    "Fit higggs mass spectra(recoilling mass of Z boson)"
    printf "\n\t%-5s  %-40s\n"  "0.1.8"    "Calculate upper limmits of branch ratio"
        
    #0.2 #mumuH_invisible
    printf "\n\t%-5s  %-40s\n"  "0.2"      "Runing signal samples..."
    printf "\n\t%-5s  %-40s\n"  "0.2.1"    "Split signal sample with each group 0.5G..."  
    printf "\n\t%-5s  %-40s\n"  "0.2.2"    "Generate XML input files for Marlin job..."
    printf "\n\t%-5s  %-40s\n"  "0.2.3"    "Run with a few events" 
    printf "\n\t%-5s  %-40s\n"  "0.2.4"    "Generate Condor job scripts..." 
    printf "\n\t%-5s  %-40s\n"  "0.2.5"    "Submit Condor jobs for pre-selection on signal..."
    printf "\n\t%-5s  %-40s\n"  "0.2.6"    "Select events on signal (with a small sample)..."
    printf "\n\t%-5s  %-40s\n"  "0.2.7"    "Generate Condor job scripts for event selection..."
    printf "\n\t%-5s  %-40s\n"  "0.2.8"    "Submit Condor jobs for event selection on signal..."
    printf "\n\t%-5s  %-40s\n"  "0.2.9"    "Merge event root files..."         
    #0.3 #background
    printf "\n\t%-5s  %-40s\n"  "0.3"      "Running on background sample...."
    printf "\n\t%-5s  %-40s\n"  "0.3.1"    "Split background sample with each group 20G..."  
    printf "\n\t%-5s  %-40s\n"  "0.3.2"    "Generate XML input files for Marlin job..."
    printf "\n\t%-5s  %-40s\n"  "0.3.3"    "Check statistics : print the number of files..." 
    printf "\n\t%-5s  %-40s\n"  "0.3.4"    "GRun with a few events ..." 
    printf "\n\t%-5s  %-40s\n"  "0.3.5"    "Generate Condor job scripts..."
    printf "\n\t%-5s  %-40s\n"  "0.3.6"    "Submit Condor jobs for pre-selection on background sample..."
    printf "\n\t%-5s  %-40s\n"  "0.3.7"    "Select events on background (with a small sample)..."
    printf "\n\t%-5s  %-40s\n"  "0.3.8"    "Generate Condor job scripts for event selection..."
    printf "\n\t%-5s  %-40s\n"  "0.3.9"    "Submit Condor jobs for pre-selection on background sample..." 
    printf "\n\t%-5s  %-40s\n"  "0.3.10"   "Merge event root files..." 
    printf "\n\t%-5s  %-40s\n"  "0.3.11"   "Scale event..."
    printf "\n\t%-5s  %-40s\n"  "0.3.12"   "Plot signal and background cut distribution"
    printf "\n\t%-5s  %-40s\n"  "0.3.13"   "Plot before cut and after cut distribution" 
    printf "\n\t%-5s  %-40s\n"  "0.3.14"   "Expand the background two times" 
    printf "\n\t%-5s  %-40s\n"  "0.3.15"   "Applying BDT cut..."
    printf "\n\t%-5s  %-40s\n"  "0.3.16"   "Synthetizing signal and background ROOT files..."
    printf "\n\t%-5s  %-40s\n"  "0.3.17"   "Fitting higgs mass spectra(recoilling mass of Z boson)..."
    printf "\n\t%-5s  %-40s\n"  "0.3.18"   "Calculating upper limmit of branch ratio..."


    printf "\nDATE\n"
    printf "\n\t%-5s\n" "AUGUST 2016"     
}


if [[ $# -eq 0 ]]; then
    usage
fi

signal_slcio_dir=/cefs/data/DstData/CEPC240/CEPC_v4/higgs/smart_final_states/E240.Pffh_invi.e0.p0.whizard195/

sel_all=0
sel_signal=1
sel_bg=2


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
        hep_sub -g physics cut_variable_job -e job.err -o job.out
    ;;

    0.1.4) echo "Calculating cut flows of siganl and background samples..."
        if [ ! -d "sel" ]; then
            mkdir sel
        fi
        if [ ! -d "logfiles" ]; then
            mkdir logfiles
        fi
        cd job
        hep_sub -g physics cut_flow_job -e job.err -o job.out
    ;;

    0.1.5) echo "Applying BDT cut..."
        if [ ! -d "BDT_output" ]; then
            mkdir BDT_output
        fi
        cd BDT
        if [ ! -f "../BDT_output/bkg_e2e2h.root" ]; then
            echo "Samples are about to be trained, after that please check the distribution to get BDT cut and run ./submit 0.1.5 again to apply that!"
            root -l Hinv.C
        else
            echo "BDT cut is about to be applied!"
            root -l -q HinvApplication.C
        fi
    ;;

    0.1.6) echo "Synthetizing signal and background ROOT files..."
        cd python
        rm ../BDT_output/Hinv_sig_e2e2h_selected_BDT.root -rf
        python chs_events.py ../BDT_output/Hinv_sig_e2e2h_2fermions_BDT.root ../BDT_output/Hinv_sig_e2e2h_selected_BDT.root signal_e2e2h
        cd ../BDT_output
        rm ../sel/sig_bkg_e2e2h.root -rf
        hadd ../sel/sig_bkg_e2e2h.root Hinv_bkg_e2e2h_2fermions_BDT.root Hinv_bkg_e2e2h_4fermions_BDT.root Hinv_sig_e2e2h_selected_BDT.root
    ;;

    0.1.7) echo "Fitting higgs mass spectra(recoilling mass of Z boson)..."
        cd src
        root fithiggs.cxx
    ;;

    0.1.8) echo "Calculating upper limmit of branch ratio..."
        cd python
        python cal_upperlimit.py
    ;;

    #example e2E2h_invisible 

   
    0.2)   echo "Runing signal samples..."
   
        ;;
 
    0.2.1) echo "Split signal sample with each group 0.5G..."
        
            mkdir -p ./run/e2E2h_invi/samples
            ./python/get_samples.py ${signal_slcio_dir} ./run/e2E2h_invi/samples/E240_Pffh_invi.txt 0.5G
        ;;       
           
    0.2.2) echo "Generate XML input files for Marlin job..."
                
            mkdir -p   ./run/e2E2h_invi/steers
            mkdir -p   ./run/e2E2h_invi/steers/test
            mkdir -p   ./run/e2E2h_invi/ana/test       
                              
            ./python/get_steerfiles.py ./table/template_jobfile.xml ./run/e2E2h_invi/samples ./run/e2E2h_invi/steers ./run/e2E2h_invi/ana/ana_File.root    
    
        ;;
           
    0.2.3) echo "Run with a few events"
                   
            source setup.sh
#           ./build.sh
            Marlin run/e2E2h_invi/steers/test/sample-1.xml
            
        ;;

    0.2.4) echo "Generate Condor job scripts..."

            mkdir -p   ./run/e2E2h_invi/condor/script/marlin
           ./python/gen_condorscripts.py  1  ./run/e2E2h_invi/steers ./run/e2E2h_invi/condor  ${sel_signal}
           
        ;;

    0.2.5) echo "Submit Condor jobs for pre-selection on signal..."
                    
            cd ./run/e2E2h_invi/condor
            mkdir -p log
            ./condor_submit.sh

        ;;

    0.2.6) echo "Select events on signal (with a small sample)..."  
#            mkdir -p   ./run/e2E2h_invi/events/ana
            mkdir -p   ./run/e2E2h_invi/events/ana/
            ./python/sel_events.py  ./run/e2E2h_invi/ana/ana_File-2.root  ana_File-2_test.root 
            
        ;; 

    0.2.7) echo "Generate Condor job scripts for event selection..."

            mkdir -p   ./run/e2E2h_invi/events/ana
            mkdir -p   ./run/e2E2h_invi/condor/script/eventsel
            ./python/gen_condorscripts.py  2  ./run/e2E2h_invi/ana ./run/e2E2h_invi/condor  

        ;;
    
    0.2.8) echo "Submit Condor jobs for event selection on signal..."

            cd ./run/e2E2h_invi/condor
            mkdir -p log/events
            ./condor_submit_eventsel.sh

  
        ;;

    0.2.9) echo  "Merge event root files..."
           
            mkdir -p   ./run/e2E2h_invi/hist

            ./python/mrg_rootfiles.py  ./run/e2E2h_invi/events/ana  ./run/e2E2h_invi/hist/e2E2h_invi 

        ;;
    #background information 

    0.3) echo "Running on background sample...."

        ;;

    0.3.1) echo "Split background sample with each group 20G..."
          
            mkdir -p   ./run/bg/samples
            ./python/get_bg_samples.py ./table/bg_sample_list.txt ./run/bg/samples 20G           

        ;;           
    0.3.2) echo "Generate XML input files for Marlin job..."  

            mkdir -p   ./run/bg/steers 
            mkdir -p   ./run/bg/ana

            ./python/gen_bg_steerfiles.py ./table/bg_sample_list.txt ./table/template_jobfile.xml  ./run/bg/samples  ./run/bg/steers  ./run/bg/ana
        
        ;;
               
    0.3.3) echo "Check statistics : print the number of files..."
        
            ./python/check_stat.py  ./table/bg_sample_list.txt ./run/bg/samples 
        
       ;;

    0.3.4) echo "Run with a few events ..."
#	   source setup.sh
#	   ./build.sh
            cd ./run/bg/steers/

            for dir in *            
            do
                mkdir -p ../ana/$dir
                cd ${dir}/test
                Marlin sample-1.xml
                cd ../../
            done

        ;;

    0.3.5) echo "Generate Condor job scripts..."

             mkdir -p   ./run/bg/condor
            cd ./run/bg/
                rm -rf log/marlin
                mkdir -p log/marlin			
			cd ./ana/
            for dir in *
            do
                mkdir -p ../condor/$dir
            done

            cd ../condor/
            for dir in *
            do
                cd $dir
                rm -rf script/marlin
                mkdir -p script/marlin
                cd ../
            done

            cd ../../../
            ./python/gen_bg_condorscripts.py  1  ./run/bg/steers ./run/bg/condor 

        
        ;;
    
    0.3.6) echo "Submit Condor jobs for pre-selection on background sample..."
           echo " ---- "
           echo "Please enter the number of jobs for each backgrond (default: 1000)"  

            njob=1000    
            cd ./run/bg/condor
            for dir in *
            do
                cd $dir
                echo `pwd`
                ./condor_submit.sh $njob
                cd ../
            done 
           ;;
            
    0.3.7) echo "Select events on background (with a small sample)..."
#            python python/check.py ./run/bg/log/marlin   0        
            mkdir -p   ./run/bg/events/ana/

            ./python/sel_events.py  run/bg/steers/e2e2/test/ana_bg_test_1.root  ./run/bg/steers/e2e2/test/ana_bg_test_1_event.root

           ;;

    0.3.8) echo "Generate Condor job scripts for event selection..."
   
             mkdir -p   ./run/bg/events/ana
        
            cd ./run/bg
            rm -rf log/events
			mkdir -p log/events			
			cd ./condor

            for dir in *
            do
                mkdir -p   ../scale/ana/$dir
                mkdir -p ../events/ana/$dir
                cd $dir
                rm -rf script/eventsel
                rm -rf script/scalesel
                mkdir -p script/eventsel
                mkdir -p script/scalesel
                cd ../
            done
       
            cd ../../../
            ./python/gen_bg_condorscripts.py  2  ./run/bg/ana ./run/bg/condor   

        ;;

    0.3.9) echo "Submit Condor jobs for pre-selection on background sample..."

            cd ./run/bg/condor
            for dir in *
            do
 #               if [$dir != test]; then                 
                cd $dir
                echo `pwd`
                ./condor_submit_eventsel.sh 
                cd ../
#                fi
            done

        ;;
    0.3.10) echo  "Merge event root files..."
#            python python/check.py ./run/bg/log/events 1
            mkdir -p ./run/bg/hist
            mkdir -p ./run/bg/plot
            cd ./run/bg/scale/ana
            for dir in *
            do
            mkdir -p ../../hist/$dir
            mkdir -p ../../plot/$dir
               cd ../../../../
               #Merge data before scale
               ./python/mrg_rootfiles.py  ./run/bg/events/ana/$dir ./run/bg/plot/$dir
               cd ./run/bg/scale/ana	       
           done
          ;; 

    0.3.11) echo "Scale event..."
            cd ./run/bg/condor
            for dir in *
            do
 #               if [$dir != test]; then                 
                cd ../../..

                ./run/bg/condor/$dir/condor_scale_eventsel.sh 
                cd run/bg/condor
#                fi
            done
    ;; 
    0.3.12) echo "Plot signal and background cut distribution"
            mkdir -p ./run/total/hist
            mkdir -p ./run/total/plot
            rm ./run/total/bkg_add_sig.root -rf
            rm ./run/bg/hist/all_bkg_merge.root -rf
            rm ./run/bg/plot/all_bkg_merge.root -rf
<<<<<<< HEAD
            #merge all backgrounds;merge backgrounds and signal 
=======
            #merge all backgrounds;merge backgrounds and signal
>>>>>>> cepc/master
            ./python/scale_events.py ./run/e2E2h_invi/hist/e2E2h_invi/ana_File_merged_1.root ./run/e2E2h_invi/hist/e2E2h_invi/ana_File_merged_scale_1.root e2E2h_invi table/bg_sample_list.txt
            ./job/merge.sh
            cp run/e2E2h_invi/hist/e2E2h_invi/ana_File_merged_scale_1.root  run/total/hist/ffH_inv.root
       ;;

    0.3.13) echo "Plot before cut and after cut distribution" 
            mkdir -p fig/after
            mkdir -p fig/before           
            ./python/plt_before_summary.py  signal ZZ WW single_z single_w zzorww zorw 2f
            ./python/plt_after_summary.py sig+bkg signal ZZ WW single_z single_w zzorww zorw  2f

            ;;
    0.3.14) echo "Applying BDT cut..."
            if [ ! -d "BDT_output" ]; then
                mkdir BDT_output
            fi
            cd BDT
            if [ ! -f "../BDT_output/bkg_e2e2h.root" ]; then
                echo "Samples are about to be trained, after that please check the distribution to get BDT cut and run ./submit 0.3.12 again to apply that!"
                root -l Hinv.C
            else
                echo "BDT cut is about to be applied!"
                root -l -q HinvApplication.C
            fi
    ;;

    0.3.15) echo "Synthetizing signal and background ROOT files..."
    
            rm ./BDT_output/Hinv_bkg_e2e2h_selected_BDT.root -rf
            # Expand background 62 times,make background and signal have the same scale.
            python ./python/scale_bkg_events.py ./BDT_output/Hinv_sig_e2e2h_BDT.root ./BDT_output/Hinv_sig_e2e2h_selected_BDT.root all_bkg

            rm  ./run/total/bkg_add_sig_BDT.root

            hadd ./run/total/bkg_add_sig_BDT.root ./BDT_output/Hinv_sig_e2e2h_selected_BDT.root ./BDT_output/Hinv_bkg_e2e2h_BDT.root
     
    ;;

    0.3.16) echo "Fitting higgs mass spectra(recoilling mass of Z boson)..."

            root ./src/fitsigbkg.cxx
    ;;

    0.3.17) echo "Calculating upper limit of branch ratio..."
            
            python ./python/cal_upperlimit_BDT.py
    ;;
    0.3.18) echo "Get background and signal number after different cuts"
            rm table/bin.txt 
            rm table/out_list.txt
            rm table/tfbin.txt
            cd ./run/bg/events/ana
            for dir in *
            do 
                cd ../../../../
                python python/gen_bin.py run/bg/plot/$dir table/bg_sample_list.txt                
                cd ./run/bg/events/ana
            done 
            cd ../../../../
            python python/gen_bin.py run/e2E2h_invi/hist/e2E2h_invi table/bg_sample_list.txt
               
            python python/get_bin.py table/out_list.txt
        ;;
    0.3.19) echo "Get Shorthand channel detail information"
<<<<<<< HEAD
#           cp run/e2E2h_invi/hist/e2E2h_invi/ana_File_merged_scale_1.root  run/total/hist/ffH_inv.root
           rm table/out_list_b.txt
           rm table/tfbin_b.txt
           python  python/gen_binb.py  run/total/hist
#           python  python/get_binb.py table/out_list_b.txt 
    ;;
    0.3.20) echo " Optimize the cut conditions"
            rm preliminary/*
            cd ./run/total/hist
            for dir in *
            do 
                cd ../../../
                ./python/sel_eventsm.py run/total/hist/$dir preliminary/$dir
                cd ./run/total/hist
            done
=======
           cp run/e2E2h_invi/hist/e2E2h_invi/ana_File_merged_scale_1.root  run/total/hist/signal.root
           rm table/out_list_b.txt
           rm table/tfbin_b.txt
           python  python/gen_binb.py  run/total/hist
           python  python/get_binb.py table/out_list_b.txt 

>>>>>>> cepc/master

 
esac    

