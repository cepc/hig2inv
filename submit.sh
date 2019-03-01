
#!/usr/bin/env bash        

# Main driver to submit jobs   
# Author SHI Xin <shixin@ihep.ac.cn>  
# Created [2016-08-16 Tue 08:29]  
#mumuH_inv
usage() {
    printf "NAME\n\tsubmit.sh - Main driver to submit jobs\n"
    printf "\nSYNOPSIS\n"
    printf "\n\t%-5s\n" "./submit.sh [OPTION]" 
    printf "\nOPTIONS\n"    
    printf "\n\t%-9s  %-40s"  "0.1"      "[run data sample for mumuH_inv->Maoqiang Jing]" 
    printf "\n\t%-9s  %-40s"  "0.2"      "[run data sample for mumuH_inv->Tanyuhang]"  
    printf "\n\t%-9s  %-40s"  "0.3"      "[run data sample for background of mumuH_inv]" 
    printf "\n\t%-9s  %-40s"  "0.4"      "[run data sample for eeH_inv]" 
    printf "\n\t%-9s  %-40s"  "0.5"      "[run data sample for qqH_inv]"
    printf "\n\n" 
}
usage_0_1() { 
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
}
 usage_0_2() {        
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
}
usage_0_3() {         
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
    printf "\n\t%-5s  %-40s\n"  "0.3.18"   "Get background and signal number after different cuts" 
    printf "\n\t%-5s  %-40s\n"  "0.3.19"   "Get Shorthand channel detail information"   
}
#eeH_inv(memo 0.4.3)
usage_0_4(){
    printf "NAME\n\tsubmit.sh - eeH_inv\n"
    printf "\nSYNOPSIS\n"
    printf "\n\t%-5s\n" "./submit.sh [OPTION]" 
    printf "\nOPTIONS\n" 
    #0.4 #eeH_invisible
    printf "\n\t%-5s  %-40s\n"  "0.4.1"    "Split signal sample with each group 0.5G..."  
    printf "\n\t%-5s  %-40s\n"  "0.4.2"    "Generate XML input files for Marlin job..."
    printf "\n\t%-5s  %-40s\n"  "0.4.3"    "Run with a few events" 
    printf "\n\t%-5s  %-40s\n"  "0.4.4"    "Generate Condor job scripts..." 
    printf "\n\t%-5s  %-40s\n"  "0.4.5"    "Submit Condor jobs for pre-selection on signal..."
    printf "\n\t%-5s  %-40s\n"  "0.4.6"    "Select events on signal (with a small sample)..."
    printf "\n\t%-5s  %-40s\n"  "0.4.7"    "Generate Condor job scripts for event selection..."
    printf "\n\t%-5s  %-40s\n"  "0.4.8"    "Submit Condor jobs for event selection on signal..."
    printf "\n\t%-5s  %-40s\n"  "0.4.9"    "Merge event root files..."         
    #0.4 #background
    printf "\n\t%-5s  %-40s\n"  "0.4.10"    "Split background sample with each group 20G..."  
    printf "\n\t%-5s  %-40s\n"  "0.4.11"    "Generate XML input files for Marlin job..."
    printf "\n\t%-5s  %-40s\n"  "0.4.12"    "Check statistics : print the number of files..." 
    printf "\n\t%-5s  %-40s\n"  "0.4.13"    "GRun with a few events ..." 
    printf "\n\t%-5s  %-40s\n"  "0.4.14"    "Generate Condor job scripts..."
    printf "\n\t%-5s  %-40s\n"  "0.4.15"    "Submit Condor jobs for pre-selection on background sample..."
    printf "\n\t%-5s  %-40s\n"  "0.4.16"    "Select events on background (with a small sample)..."
    printf "\n\t%-5s  %-40s\n"  "0.4.17"    "Generate Condor job scripts for event selection..."
    printf "\n\t%-5s  %-40s\n"  "0.4.18"    "Submit Condor jobs for pre-selection on background sample..." 
    printf "\n\t%-5s  %-40s\n"  "0.4.19"    "Merge event root files..." 
    printf "\n\t%-5s  %-40s\n"  "0.4.20"    "Scale event..." 
    printf "\n\t%-5s  %-40s\n"  "0.4.21"    "Plot signal and background cut distribution"
    printf "\n\t%-5s  %-40s\n"  "0.4.22"    "Plot before cut and after cut distribution" 
    printf "\n\t%-5s  %-40s\n"  "0.4.23"    "Expand the background two times" 
    printf "\n\t%-5s  %-40s\n"  "0.4.24"    "Applying BDT cut..."
    printf "\n\t%-5s  %-40s\n"  "0.4.25"    "Synthetizing signal and background ROOT files..."
    printf "\n\t%-5s  %-40s\n"  "0.4.26"    "Calculating upper limit of branch ratio..."
    printf "\n\t%-5s  %-40s\n"  "0.4.27"    "Get background and signal number after different cuts"	
    printf "\n\t%-5s  %-40s\n"  "0.4.28"    "Get Shorthand channel detail information"
}

usage_0_5(){
    printf "NAME\n\tsubmit.sh - qqH_inv\n"
    printf "\nSYNOPSIS\n"
    printf "\n\t%-5s\n" "./submit.sh [OPTION]" 
    printf "\nOPTIONS\n" 
    #0.5 #qqH_invisible
    printf "\n\t%-5s  %-40s\n"  "0.5.1"    "Split signal sample with each group 0.5G..."  
    printf "\n\t%-5s  %-40s\n"  "0.5.2"    "Generate XML input files for Marlin job..."
    printf "\n\t%-5s  %-40s\n"  "0.5.3"    "Run with a few events" 
    printf "\n\t%-5s  %-40s\n"  "0.5.4"    "Generate Condor job scripts..." 
    printf "\n\t%-5s  %-40s\n"  "0.5.5"    "Submit Condor jobs for pre-selection on signal..."
    printf "\n\t%-5s  %-40s\n"  "0.5.6"    "Select events on signal (with a small sample)..."
    printf "\n\t%-5s  %-40s\n"  "0.5.7"    "Generate Condor job scripts for event selection..."
    printf "\n\t%-5s  %-40s\n"  "0.5.8"    "Submit Condor jobs for event selection on signal..."
    printf "\n\t%-5s  %-40s\n"  "0.5.9"    "Merge event root files..."         
    #0.5 #background
    printf "\n\t%-5s  %-40s\n"  "0.5.10"    "Split background sample with each group 20G..."  
    printf "\n\t%-5s  %-40s\n"  "0.5.11"    "Generate XML input files for Marlin job..."
    printf "\n\t%-5s  %-40s\n"  "0.5.12"    "Check statistics : print the number of files..." 
    printf "\n\t%-5s  %-40s\n"  "0.5.13"    "GRun with a few events ..." 
    printf "\n\t%-5s  %-40s\n"  "0.5.14"    "Generate Condor job scripts..."
    printf "\n\t%-5s  %-40s\n"  "0.5.15"    "Submit Condor jobs for pre-selection on background sample..."
    printf "\n\t%-5s  %-40s\n"  "0.5.16"    "Select events on background (with a small sample)..."
    printf "\n\t%-5s  %-40s\n"  "0.5.17"    "Generate Condor job scripts for event selection..."
    printf "\n\t%-5s  %-40s\n"  "0.5.18"    "Submit Condor jobs for pre-selection on background sample..." 
    printf "\n\t%-5s  %-40s\n"  "0.5.19"    "Merge event root files..." 
    printf "\n\t%-5s  %-40s\n"  "0.5.20"    "Scale event..."
    printf "\n\t%-5s  %-40s\n"  "0.5.21"    "Plot signal and background cut distribution"
    printf "\n\t%-5s  %-40s\n"  "0.5.22"    "Plot before cut and after cut distribution" 
    printf "\n\t%-5s  %-40s\n"  "0.5.23"    "Get background and signal number after different cuts"	
    printf "\n\t%-5s  %-40s\n"  "0.5.24"    "Get Shorthand channel detail information"
}
usage_0_6(){
    printf "NAME\n\tsubmit.sh - fit and calculate upperlimit\n"
    printf "\nSYNOPSIS\n"
    printf "\n\t%-5s\n" "./submit.sh [OPTION]" 
    printf "\nOPTIONS\n" 
    printf "\n\t%-5s  %-40s\n"  "0.6.1"    "Get the information from mumuH" 
	printf "\n\t%-5s  %-40s\n"  "0.6.2"    "Get the information from eeH" 
	printf "\n\t%-5s  %-40s\n"  "0.6.3"    "Get the information from qqH"
	printf "\n\t%-5s  %-40s\n"  "0.6.4"    "move data to one file"  
	printf "\n\t%-5s  %-40s\n"  "0.6.5"    "fit and generate Asimovdata"  	   
}

signal_slcio_dir=/cefs/data/DstData/CEPC240/CEPC_v4/higgs/smart_final_states/E240.Pffh_invi.e0.p0.whizard195/

sel_all=0
sel_signal=1
sel_bg=2

if [[ $# -eq 0 ]]; then
    usage
    echo "Please enter your option: "
    read option
else
    option=$1    
fi




sub_0_1(){
case $option in 

    0.1.1) echo "Running on signal and background samples..."
        if [ ! -d "steer" ]; then
            mkdir steer -
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
    
    esac
}
 

sub_0_2(){   
case $option in 
#example e2E2h_invisible 
    0.2.1) echo "Split signal sample with each group 0.5G..."
        
            mkdir -p ./run/mumuH/e2E2h_invi/samples
            ./python/get_samples.py ${signal_slcio_dir} ./run/mumuH/e2E2h_invi/samples/E240_Pffh_invi.txt 0.5G
        ;;       
           
    0.2.2) echo "Generate XML input files for Marlin job..."
                
            mkdir -p   ./run/mumuH/e2E2h_invi/steers
            mkdir -p   ./run/mumuH/e2E2h_invi/steers/test
            mkdir -p   ./run/mumuH/e2E2h_invi/ana/test       
                              
            ./python/get_steerfiles.py ./table/template_jobfile.xml ./run/mumuH/e2E2h_invi/samples ./run/mumuH/e2E2h_invi/steers ./run/mumuH/e2E2h_invi/ana/ana_File.root muon   
    
        ;;
           
    0.2.3) echo "Run with a few events"
                   
            source setup.sh
#           ./build.sh
            Marlin run/mumuH/e2E2h_invi/steers/test/sample-1.xml
            
        ;;

    0.2.4) echo "Generate Condor job scripts..."

            mkdir -p   ./run/mumuH/e2E2h_invi/condor/script/marlin
           ./python/gen_condorscripts.py  1  ./run/mumuH/e2E2h_invi/steers ./run/mumuH/e2E2h_invi/condor  ${sel_signal}
           
        ;;

    0.2.5) echo "Submit Condor jobs for pre-selection on signal..."
                    
            cd ./run/mumuH/e2E2h_invi/condor
            mkdir -p log
            ./condor_submit.sh

        ;;

    0.2.6) echo "Select events on signal (with a small sample)..."  
#            mkdir -p   ./run/e2E2h_invi/events/ana
            mkdir -p   ./run/mumuH/e2E2h_invi/events/ana/
            ./python/sel_mumu_events.py  ./run/mumuH/e2E2h_invi/ana/ana_File-2.root  ana_File-2_test.root 
            
        ;; 

    0.2.7) echo "Generate Condor job scripts for event selection..."

            mkdir -p   ./run/mumuH/e2E2h_invi/events/ana
            mkdir -p   ./run/mumuH/e2E2h_invi/condor/script/eventsel
            ./python/gen_condorscripts.py  2  ./run/mumuH/e2E2h_invi/ana ./run/mumuH/e2E2h_invi/condor  muon

        ;;
    
    0.2.8) echo "Submit Condor jobs for event selection on signal..."

            cd ./run/mumuH/e2E2h_invi/condor
            mkdir -p log/events
            ./condor_submit_eventsel.sh

  
        ;;

    0.2.9) echo  "Merge event root files..."
           
            mkdir -p   ./run/mumuH/e2E2h_invi/hist

            ./python/mrg_rootfiles.py  ./run/mumuH/e2E2h_invi/events/ana  ./run/mumuH/e2E2h_invi/hist/e2E2h_invi 

        esac
}

sub_0_3(){

    #background information 
case $option in    
    0.3.1) echo "Split background sample with each group 20G..."
          
            mkdir -p   ./run/mumuH/bg/samples
            ./python/get_bg_samples.py ./table/bg_sample_list.txt ./run/mumuH/bg/samples 20G           

        ;;           
    0.3.2) echo "Generate XML input files for Marlin job..."  

            mkdir -p   ./run/mumuH/bg/steers 
            mkdir -p   ./run/mumuH/bg/ana

            ./python/gen_bg_steerfiles.py ./table/bg_sample_list.txt ./table/template_jobfile.xml  ./run/mumuH/bg/samples  ./run/mumuH/bg/steers  ./run/mumuH/bg/ana  BKGM
        
        ;;
               
    0.3.3) echo "Check statistics : print the number of files..."
        
            ./python/check_stat.py  ./table/bg_sample_list.txt ./run/mumuH/bg/samples 
        
       ;;

    0.3.4) echo "Run with a few events ..."
#	   source setup.sh
#	   ./build.sh
            cd ./run/mumuH/bg/steers/

            for dir in *            
            do
                mkdir -p ../ana/$dir
                cd ${dir}/test
                Marlin sample-1.xml
                cd ../../
            done

        ;;

    0.3.5) echo "Generate Condor job scripts..."

             mkdir -p   ./run/mumuH/bg/condor
            cd ./run/mumuH/bg/
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

            cd ../../../../
            ./python/gen_bg_condorscripts.py  1  ./run/mumuH/bg/steers ./run/mumuH/bg/condor muon

        
        ;;
    
    0.3.6) echo "Submit Condor jobs for pre-selection on background sample..."
           echo " ---- "
           echo "Please enter the number of jobs for each backgrond (default: 1000)"  

            njob=1000    
            cd ./run/mumuH/bg/condor
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
            mkdir -p   ./run/mumuH/bg/events/ana/

            ./python/sel_mumu_events.py  run/mumuH/bg/steers/e2e2/test/ana_bg_test_1.root  ./run/mumuH/bg/steers/e2e2/test/ana_bg_test_1_event.root

           ;;

    0.3.8) echo "Generate Condor job scripts for event selection..."
   
             mkdir -p   ./run/mumuH/bg/events/ana
        
            cd ./run/mumuH/bg
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
       
            cd ../../../../
            ./python/gen_bg_condorscripts.py  2  ./run/mumuH/bg/ana ./run/mumuH/bg/condor   muon

        ;;

    0.3.9) echo "Submit Condor jobs for pre-selection on background sample..."

            cd ./run/mumuH/bg/condor
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
            mkdir -p ./run/mumuH/bg/hist
            mkdir -p ./run/mumuH/bg/plot
            cd ./run/mumuH/bg/scale/ana
            for dir in *
            do
            mkdir -p ../../hist/$dir
            mkdir -p ../../plot/$dir
               cd ../../../../../
               #Merge data before scale
               ./python/mrg_rootfiles.py  ./run/mumuH/bg/events/ana/$dir ./run/mumuH/bg/plot/$dir
               cd ./run/mumuH/bg/scale/ana	       
           done
          ;; 

    0.3.11) echo "Scale event..."
            cd ./run/mumuH/bg/condor
            for dir in *
            do  
 #               if [$dir != test]; then                 
                cd ../../../..

                ./run/mumuH/bg/condor/$dir/condor_scale_eventsel.sh 
                cd run/mumuH/bg/condor
#                fi
            done
    ;; 
    0.3.12) echo "Plot signal and background cut distribution"
            mkdir -p ./run/mumuH/total/hist 
            mkdir -p ./run/mumuH/total/plot
            rm ./run/mumuH/total/bkg_add_sig.root -rf
            rm ./run/mumuH/bg/hist/all_bkg_merge.root -rf
            rm ./run/mumuH/bg/plot/all_bkg_merge.root -rf
            #merge all backgrounds;merge backgrounds and signal 
            ./python/scale_events.py ./run/mumuH/e2E2h_invi/hist/e2E2h_invi/ana_File_merged_1.root ./run/mumuH/e2E2h_invi/hist/e2E2h_invi/ana_File_merged_scale_1.root e2E2h_inv table/bg_sample_list.txt
            ./job/merge.sh 0
            cp run/mumuH/e2E2h_invi/hist/e2E2h_invi/ana_File_merged_scale_1.root  run/mumuH/total/hist/mumuH_inv.root
       ;;

    0.3.13) echo "Plot before cut and after cut distribution" 
            mkdir -p fig/mumuH/after
            mkdir -p fig/mumuH/before           
            ./python/plt_before_summary.py mumuH signal ZZ WW single_z single_w zzorww 2f ZH_visible
            ./python/plt_after_summary.py mumuH  signal ZZ WW single_z single_w zzorww 2f ZH_visible

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
            rm table/mumuH/bin.txt 
            rm table/mumuH/out_list.txt
            rm table/mumuH/tfbin.txt
            mkdir table/mumuH

            cd ./run/mumuH/bg/events/ana
            for dir in *
            do 
                cd ../../../../../
                python python/gen_bin.py run/mumuH/bg/plot/$dir table/bg_sample_list.txt    mumuH            
                cd ./run/mumuH/bg/events/ana
            done 
            cd ../../../../../
            python python/gen_bin.py run/mumuH/e2E2h_invi/hist/e2E2h_invi table/bg_sample_list.txt mumuH
               
            python python/get_bin.py table/mumuH/out_list.txt
        ;;
    0.3.19) echo "Get Shorthand channel detail information"

           rm table/mumuH/out_list_b.txt
           rm table/mumuH/tfbin_b.txt
           python  python/gen_binb.py  table/mumuH/out_list.txt  mumuH
#           python  python/get_binb.py table/mumuH/out_list_b.txt mumuH
    ;;
    0.3.20) echo " Optimize the cut conditions"
            rm preliminary/mumuH/*
            cd ./run/mumuH/total/hist
            for dir in *
            do 
                cd ../../../../
                ./python/sel_eventsm.py run/mumuH/total/hist/$dir preliminary/mumuH/$dir
                cd ./run/mumuH/total/hist
            done
esac    
}

sub_0_4(){

case $option in
    #example eeH_invisible 
 
    0.4.1) echo "Split signal sample with each group 0.5G..."
        
            mkdir -p ./run/eeH/eeh_invi/samples
            ./python/get_samples.py ${signal_slcio_dir} ./run/eeH/eeh_invi/samples/E240_Pffh_invi.txt 0.5G
        ;;       
           
    0.4.2) echo "Generate XML input files for Marlin job..."
                
            mkdir -p   ./run/eeH/eeh_invi/steers
            mkdir -p   ./run/eeH/eeh_invi/steers/test
            mkdir -p   ./run/eeH/eeh_invi/ana/test       
                              
            ./python/get_steerfiles.py ./table/template_jobfile.xml ./run/eeH/eeh_invi/samples ./run/eeH/eeh_invi/steers ./run/eeH/eeh_invi/ana/ana_File.root ee   
    
        ;;
           
    0.4.3) echo "Run with a few events"
                   
            source setup.sh
#           ./build.sh
            Marlin run/eeH/eeh_invi/steers/test/sample-1.xml
            
        ;;

    0.4.4) echo "Generate Condor job scripts..."

            mkdir -p   ./run/eeH/eeh_invi/condor/script/marlin
           ./python/gen_condorscripts.py  1  ./run/eeH/eeh_invi/steers ./run/eeH/eeh_invi/condor  ${sel_signal}
           
        ;;

    0.4.5) echo "Submit Condor jobs for pre-selection on signal..."
                    
            cd ./run/eeH/eeh_invi/condor
            mkdir -p log
            ./condor_submit.sh 

        ;;

    0.4.6) echo "Select events on signal (with a small sample)..."  
#            mkdir -p   ./run/eeh_invi/events/ana
            mkdir -p   ./run/eeH/eeh_invi/events/ana/
            ./python/sel_ee_events.py  ./run/eeH/eeh_invi/ana/ana_File-2.root  ana_File-2_test.root 
            
        ;; 

    0.4.7) echo "Generate Condor job scripts for event selection..."

            mkdir -p   ./run/eeH/eeh_invi/events/ana
            mkdir -p   ./run/eeH/eeh_invi/condor/script/eventsel
            ./python/gen_condorscripts.py  2  ./run/eeH/eeh_invi/ana ./run/eeH/eeh_invi/condor  ee

        ;;
    
    0.4.8) echo "Submit Condor jobs for event selection on signal..."

            cd ./run/eeH/eeh_invi/condor
            mkdir -p log/events
            ./condor_submit_eventsel.sh

  
        ;;

    0.4.9) echo  "Merge event root files..."
           
            mkdir -p   ./run/eeH/eeh_invi/hist

            ./python/mrg_rootfiles.py  ./run/eeH/eeh_invi/events/ana  ./run/eeH/eeh_invi/hist/eeh_invi 

        ;;
    #background information 

    0.4.10) echo "Split background sample with each group 20G..."
          
            mkdir -p   ./run/eeH/bg/samples
            ./python/get_bg_samples.py ./table/bg_sample_list.txt ./run/eeH/bg/samples 20G           

        ;;           
    0.4.11) echo "Generate XML input files for Marlin job..."  

            mkdir -p   ./run/eeH/bg/steers 
            mkdir -p   ./run/eeH/bg/ana

            ./python/gen_bg_steerfiles.py ./table/bg_sample_list.txt ./table/template_jobfile.xml  ./run/eeH/bg/samples  ./run/eeH/bg/steers  ./run/eeH/bg/ana BKGE
        
        ;;
               
    0.4.12) echo "Check statistics : print the number of files..."
        
            ./python/check_stat.py  ./table/bg_sample_list.txt ./run/eeH/bg/samples 
        
       ;;

    0.4.13) echo "Run with a few events ..."
#	   source setup.sh
#	   ./build.sh
            cd ./run/eeH/bg/steers/

            for dir in *            
            do
                mkdir -p ../ana/$dir
                cd ${dir}/test
                Marlin sample-1.xml
                cd ../../
            done

        ;;

    0.4.14) echo "Generate Condor job scripts..."

            mkdir -p   ./run/eeH/bg/condor
            cd ./run/eeH/bg/ana/
            for dir in *
            do
                mkdir -p ../condor/$dir
            done

            cd ../condor/
            for dir in *
            do
                cd $dir
                rm -rf log/marlin
                rm -rf script/marlin
                mkdir -p log/marlin
                mkdir -p script/marlin
                cd ../
            done

            cd ../../../../
            ./python/gen_bg_condorscripts.py  1  ./run/eeH/bg/steers ./run/eeH/bg/condor ee

        ;;
    
    0.4.15) echo "Submit Condor jobs for pre-selection on background sample..."
           echo " ---- "
           echo "Please enter the number of jobs for each backgrond (default: 1000)"  

            njob=1000    
            cd ./run/eeH/bg/condor
            for dir in *
            do
                cd $dir
                echo `pwd`
                ./condor_submit.sh $njob
                cd ../
            done 
           ;;
            
    0.4.16) echo "Select events on background (with a small sample)..."
#            python python/check.py ./run/bg/log/marlin   0        
            mkdir -p   ./run/eeH/bg/events/ana/

            ./python/sel_ee_events.py  run/eeH/bg/steers/e2e2/test/ana_bg_test_1.root  ./run/eeH/bg/steers/e2e2/test/ana_bg_test_1_event.root  

           ;;

    0.4.17) echo "Generate Condor job scripts for event selection..."
   
            mkdir -p   ./run/eeH/bg/events/ana
        
            cd ./run/eeH/bg/condor

            for dir in *
            do
                mkdir -p   ../scale/ana/$dir
                mkdir -p ../events/ana/$dir
                cd $dir
                rm -rf log/events
                rm -rf script/eventsel
                rm -rf script/scalesel
                mkdir -p log/events
                mkdir -p script/eventsel
                mkdir -p script/scalesel
                cd ../
            done
       
            cd ../../../../
            ./python/gen_bg_condorscripts.py  2  ./run/eeH/bg/ana ./run/eeH/bg/condor ee  

        ;;

    0.4.18) echo "Submit Condor jobs for pre-selection on background sample..."

            cd ./run/eeH/bg/condor
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
    0.4.19) echo  "Merge event root files..."
#            python python/check.py ./run/bg/log/events 1
            mkdir -p ./run/eeH/bg/hist
            mkdir -p ./run/eeH/bg/plot
            cd ./run/eeH/bg/ana/
            for dir in *
            do
            mkdir -p ../hist/$dir
            mkdir -p ../plot/$dir
               cd ../../../../
               #Merge data before scale
               ./python/mrg_rootfiles.py  ./run/eeH/bg/events/ana/$dir ./run/eeH/bg/plot/$dir
               cd ./run/eeH/bg/ana	       
           done
          ;; 

    0.4.20) echo "Scale event..."
            cd ./run/eeH/bg/condor
            for dir in *
            do
 #               if [$dir != test]; then  
                echo `pwd`               
                cd ../../../../
                ./run/eeH/bg/condor/$dir/condor_scale_eventsel.sh 
                cd run/eeH/bg/condor
#                fi
            done
    ;; 
    0.4.21) echo "Plot signal and background cut distribution"
            mkdir -p ./run/eeH/total/hist
            mkdir -p ./run/eeH/total/plot
            rm ./run/eeH/total/bkg_add_sig.root -rf
            rm ./run/eeH/bg/hist/all_bkg_merge.root -rf
            rm ./run/eeH/bg/plot/all_bkg_merge.root -rf
            #merge all backgrounds;merge backgrounds and signal 
            ./python/scale_events.py ./run/eeH/eeh_invi/hist/eeh_invi/ana_File_merged_1.root ./run/eeH/eeh_invi/hist/eeh_invi/ana_File_merged_scale_1.root eeh_inv table/bg_sample_list.txt
            ./job/merge.sh 1
            cp run/eeH/eeh_invi/hist/eeh_invi/ana_File_merged_scale_1.root  run/eeH/total/hist/eeH_inv.root
       ;;

    0.4.22) echo "Plot before cut and after cut distribution" 
            mkdir -p fig/eeH/after
            mkdir -p fig/eeH/before           
            ./python/plt_before_summary.py  eeH signal ZZ WW single_z single_w zzorww  2f ZH_visible
            ./python/plt_after_summary.py eeH  signal ZZ WW single_z single_w zzorww  2f ZH_visible

            ;;
    0.4.23) echo "Applying BDT cut..."
            if [ ! -d "BDT_output" ]; then
                mkdir BDT_output
            fi
            cd BDT
            if [ ! -f "../BDT_output/bkg_e2e2h.root" ]; then
                echo "Samples are about to be trained, after that please check the distribution to get BDT cut and run ./submit 0.2.12 again to apply that!"
                root -l Hinv.C
            else
                echo "BDT cut is about to be applied!"
                root -l -q HinvApplication.C
            fi
    ;;

    0.4.24) echo "Synthetizing signal and background ROOT files..."
    
            rm ./BDT_output/Hinv_bkg_eeh_selected_BDT.root -rf
            # Expand background 62 times,make background and signal have the same scale.
            python ./python/scale_bkg_events.py ./BDT_output/Hinv_sig_eeh_BDT.root ./BDT_output/Hinv_sig_eeh_selected_BDT.root all_bkg

            rm  ./run/total/bkg_add_sig_BDT.root

            hadd ./run/total/bkg_add_sig_BDT.root ./BDT_output/Hinv_sig_eeh_selected_BDT.root ./BDT_output/Hinv_bkg_eeh_BDT.root
     
    ;;

    0.4.25) echo "Fitting higgs mass spectra(recoilling mass of Z boson)..."

            root ./src/fitsigbkg.cxx
    ;;

    0.4.26) echo "Calculating upper limit of branch ratio..."
            
            python ./python/cal_upperlimit_BDT.py
    ;;
    0.4.27) echo "Get background and signal number after different cuts"
            rm table/eeH/bin.txt 
            rm table/eeH/out_list.txt
            rm table/eeH/tfbin.txt
            mkdir table/eeH
            cd ./run/eeH/bg/events/ana
            for dir in *
            do 
                cd ../../../../../
                python python/gen_bin.py run/eeH/bg/plot/$dir table/bg_sample_list.txt  eeH              
                cd ./run/eeH/bg/events/ana
            done 
            cd ../../../../../
            python python/gen_bin.py run/eeH/eeh_invi/hist/eeh_invi table/bg_sample_list.txt eeH
               
            python python/get_bin.py table/eeH/out_list.txt
        ;;
    0.4.28) echo "Get Shorthand channel detail information"
#           cp run/eeh_invi/hist/eeh_invi/ana_File_merged_scale_1.root  run/total/hist/ffH_inv.root
           rm table/eeH/out_list_b.txt
           rm table/eeH/tfbin_b.txt
           python  python/gen_binb.py  table/eeH/out_list.txt eeH
#           python  python/get_binb.py table/eeH/out_list_b.txt eeH
    ;;
    0.4.29) echo " Optimize the cut conditions"
            rm preliminary/eeH/*
#			mkdir preliminary/eeH/
#            ./test.py
#            hep_sub -g physics -o out/ -e out/  test.sh   
            cd ./run/eeH/total/hist 
            for dir in *
            do 
                cd ../../../../
                ./python/sel_eventsm.py run/eeH/total/hist/$dir preliminary/eeH/$dir
                cd ./run/eeH/total/hist
            done
#            ./python/sel_eventsm.py  run/total/hist/ffH_inv.root  preliminary/ffH_inv.root
#            ./python/sel_eventsm.py  run/total/hist/total_bkg.root  preliminary/total_bkg.root
esac    
}



sub_0_5(){

case $option in
    #example qqH_invisible 
 
    0.5.1) echo "Split signal sample with each group 0.5G..."
        
            mkdir -p ./run/qqH/qqh_invi/samples
            ./python/get_samples.py ${signal_slcio_dir} ./run/qqH/qqh_invi/samples/E240_Pffh_invi.txt 0.5G
        ;;       
           
    0.5.2) echo "Generate XML input files for Marlin job..."
                
            mkdir -p   ./run/qqH/qqh_invi/steers
            mkdir -p   ./run/qqH/qqh_invi/steers/test
            mkdir -p   ./run/qqH/qqh_invi/ana/test       
                              
            ./python/get_steerfiles.py ./table/template_jobfile.xml ./run/qqH/qqh_invi/samples ./run/qqH/qqh_invi/steers ./run/qqH/qqh_invi/ana/ana_File.root qq   
    
        ;;
           
    0.5.3) echo "Run with a few events"
                   
            source setup.sh
#           ./build.sh
            Marlin run/qqH/qqh_invi/steers/test/sample-1.xml
            
        ;;

    0.5.4) echo "Generate Condor job scripts..."

            mkdir -p   ./run/qqH/qqh_invi/condor/script/marlin
           ./python/gen_condorscripts.py  1  ./run/qqH/qqh_invi/steers ./run/qqH/qqh_invi/condor  ${sel_signal}
           
        ;;

    0.5.5) echo "Submit Condor jobs for pre-selection on signal..."
                    
            cd ./run/qqH/qqh_invi/condor
            mkdir -p log
            ./condor_submit.sh 

        ;;

    0.5.6) echo "Select events on signal (with a small sample)..."  
#            mkdir -p   ./run/eeh_invi/events/ana
            mkdir -p   ./run/qqH/qqh_invi/events/ana/
            ./python/sel_qq_events.py  ./run/qqH/qqh_invi/ana/ana_File-2.root  ana_File-2_test.root 
            
        ;; 

    0.5.7) echo "Generate Condor job scripts for event selection..."

            mkdir -p   ./run/qqH/qqh_invi/events/ana
            mkdir -p   ./run/qqH/qqh_invi/condor/script/eventsel
            ./python/gen_condorscripts.py  2  ./run/qqH/qqh_invi/ana ./run/qqH/qqh_invi/condor  qq

        ;;
    
    0.5.8) echo "Submit Condor jobs for event selection on signal..."

            cd ./run/qqH/qqh_invi/condor
            mkdir -p log/events
            ./condor_submit_eventsel.sh 

  
        ;;

    0.5.9) echo  "Merge event root files..."
           
            mkdir -p   ./run/qqH/qqh_invi/hist

            ./python/mrg_rootfiles.py  ./run/qqH/qqh_invi/events/ana  ./run/qqH/qqh_invi/hist/qqh_invi 

        ;;
    #background information 

    0.5.10) echo "Split background sample with each group 20G..."
          
            mkdir -p   ./run/qqH/bg/samples
            ./python/get_bg_samples.py ./table/bg_sample_list.txt ./run/qqH/bg/samples 20G           

        ;;           
    0.5.11) echo "Generate XML input files for Marlin job..."  

            mkdir -p   ./run/qqH/bg/steers 
            mkdir -p   ./run/qqH/bg/ana

            ./python/gen_bg_steerfiles.py ./table/bg_sample_list.txt ./table/template_jobfile.xml  ./run/qqH/bg/samples  ./run/qqH/bg/steers  ./run/qqH/bg/ana BKGQ
        
        ;;
               
    0.5.12) echo "Check statistics : print the number of files..."
        
            ./python/check_stat.py  ./table/bg_sample_list.txt ./run/qqH/bg/samples 
        
       ;;

    0.5.13) echo "Run with a few events ..."
#	   source setup.sh
#	   ./build.sh
            cd ./run/qqH/bg/steers/

            for dir in *            
            do
                mkdir -p ../ana/$dir
                cd ${dir}/test
                Marlin sample-1.xml
                cd ../../
            done

        ;;

    0.5.14) echo "Generate Condor job scripts..."

            mkdir -p   ./run/qqH/bg/condor
            cd ./run/qqH/bg/ana/
            for dir in *
            do
                mkdir -p ../condor/$dir
            done

            cd ../condor/
            for dir in *
            do
                cd $dir
                rm -rf log/marlin
                rm -rf script/marlin
                mkdir -p log/marlin
                mkdir -p script/marlin
                cd ../
            done

            cd ../../../../
            ./python/gen_bg_condorscripts.py  1  ./run/qqH/bg/steers ./run/qqH/bg/condor qq

        ;;
    
    0.5.15) echo "Submit Condor jobs for pre-selection on background sample..."
           echo " ---- "
           echo "Please enter the number of jobs for each backgrond (default: 1000)"  

            njob=1000    
            cd ./run/qqH/bg/condor
            for dir in *
            do
                cd $dir
                echo `pwd`
                ./condor_submit.sh $njob
                cd ../
            done 
           ;;
            
    0.5.16) echo "Select events on background (with a small sample)..."
#            python python/check.py ./run/bg/log/marlin   0        
            mkdir -p   ./run/qqH/bg/events/ana/

            ./python/sel_qq_events.py  run/qqH/bg/steers/qq/test/ana_bg_test_1.root  ./run/qqH/bg/steers/qq/test/ana_bg_test_1_event.root  

           ;;

    0.5.17) echo "Generate Condor job scripts for event selection..."
   
            mkdir -p   ./run/qqH/bg/events/ana
        
            cd ./run/qqH/bg/condor

            for dir in *
            do
                mkdir -p   ../scale/ana/$dir
                mkdir -p ../events/ana/$dir
                cd $dir
                rm -rf log/events
                rm -rf script/eventsel
                rm -rf script/scalesel
                mkdir -p log/events
                mkdir -p script/eventsel
                mkdir -p script/scalesel
                cd ../
            done
       
            cd ../../../../
            ./python/gen_bg_condorscripts.py  2  ./run/qqH/bg/ana ./run/qqH/bg/condor qq  

        ;;

    0.5.18) echo "Submit Condor jobs for pre-selection on background sample..."

            cd ./run/qqH/bg/condor
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
    0.5.19) echo  "Merge event root files..."
#            python python/check.py ./run/bg/log/events 1
            mkdir -p ./run/qqH/bg/hist
            mkdir -p ./run/qqH/bg/plot
            cd ./run/qqH/bg/ana/
            for dir in *
            do
            mkdir -p ../hist/$dir
            mkdir -p ../plot/$dir
               cd ../../../../
               #Merge data before scale
               ./python/mrg_rootfiles.py  ./run/qqH/bg/events/ana/$dir ./run/qqH/bg/plot/$dir
               cd ./run/qqH/bg/ana	       
           done
          ;; 

    0.5.20) echo "Scale event..."
            cd ./run/qqH/bg/condor
            for dir in *
            do
 #               if [$dir != test]; then  
                echo `pwd`               
                cd ../../../../
                ./run/qqH/bg/condor/$dir/condor_scale_eventsel.sh 
                cd run/qqH/bg/condor
#                fi
            done
    ;; 
    0.5.21) echo "Plot signal and background cut distribution"
            rm -rf ./run/qqH/total/
            mkdir -p ./run/qqH/total/hist
            mkdir -p ./run/qqH/total/plot 
            #merge all backgrounds;merge backgrounds and signal 
            ./python/scale_qq_events.py ./run/qqH/qqh_invi/hist/qqh_invi/ana_File_merged_1.root ./run/qqH/qqh_invi/hist/qqh_invi/ana_File_merged_scale_1.root qqh_inv table/bg_sample_list.txt
            ./job/merge.sh 2
            cp run/qqH/qqh_invi/hist/qqh_invi/ana_File_merged_scale_1.root  run/qqH/total/hist/qqH_inv.root
       ;;

    0.5.22) echo "Plot before cut and after cut distribution" 
            mkdir -p fig/qqH/after
            mkdir -p fig/qqH/before           
            ./python/plt_before_summary.py  qqH signal ZZ WW single_z single_w zzorww  2f  ZH_visible
            ./python/plt_after_summary.py qqH signal ZZ WW single_z single_w zzorww   2f   ZH_visible

            ;;
    0.5.23) echo "Get background and signal number after different cuts"
            rm table/qqH/bin.txt 
            rm table/qqH/out_list.txt 
            rm table/qqH/tfbin.txt
            mkdir table/qqH
            cd ./run/qqH/bg/events/ana
            for dir in *
            do 
                cd ../../../../../
                python python/gen_bin.py run/qqH/bg/plot/$dir table/bg_sample_list.txt  qqH              
                cd ./run/qqH/bg/events/ana 
            done 
            cd ../../../../../
            python python/gen_bin.py run/qqH/qqh_invi/hist/qqh_invi table/bg_sample_list.txt qqH
               
            python python/get_bin.py table/qqH/out_list.txt
        ;;
 
    0.5.24) echo "Get Shorthand channel detail information"
#           cp run/eeh_invi/hist/eeh_invi/ana_File_merged_scale_1.root  run/total/hist/ffH_inv.root
           rm table/qqH/out_list_b.txt 
           rm table/qqH/tfbin_b.txt
           python  python/gen_binb.py  table/qqH/out_list.txt  qqH

#           python  python/get_binb.py table/qqH/out_list_b.txt qqH
    ;;
    0.5.25) echo " Optimize the cut conditions"
#            rm preliminary/qqH/*
#			mkdir preliminary/qqH/
#            ./test.py
#            hep_sub -g physics -o out/ -e out/  test.sh    
            cd ./run/qqH/total/hist 
            for dir in *
            do 
                cd ../../../../
                python ./python/sel_qq_eventsm.py run/qqH/total/hist/$dir preliminary/qqH/$dir
                cd ./run/qqH/total/hist
            done
#            ./python/sel_eventsm.py  run/total/hist/ffH_inv.root  preliminary/ffH_inv.root
#            ./python/sel_eventsm.py  run/total/hist/total_bkg.root  preliminary/total_bkg.root
esac    
}

sub_0_6(){

case $option in
   #before use 0_6 you should source calculate/setupATLAS.sh
	0.6.1) echo "Get the information from mumuH"
           cp run/mumuH/total/hist/* calculate/mz4v/	
		   cp run/qqH/total/hist/* calculate/qz4v/
		   cp run/eeH/total/hist/* calculate/ez4v/
           cd  calculate/mz4v/
           root -l mz4v.cxx
	;;
	0.6.2) echo "Get the information from eeH"
           cd  calculate/ez4v/
           root -l ez4v.cxx
	;;
	0.6.3) echo "Get the information from qqH"
           cd  calculate/qz4v/
           root -l qz4v.cxx
	;;
	0.6.4) echo "move data to one file"
           cp calculate/mz4v/mz4v* calculate/workspace/data/hinvi/
           cp calculate/ez4v/ez4v* calculate/workspace/data/hinvi/
           cp calculate/qz4v/qz4v* calculate/workspace/data/hinvi/
	;;	
	0.6.5) echo "fit and generate Asimovdata"
	       mkdir fig/mz4v -p
	       mkdir fig/ez4v -p
	       mkdir fig/qz4v -p		   
           cd calculate/workspace
		   ./job/run.sh		
#		   mv mz4v* ../workspace/data/hinvi
esac
}

case $option in 
# sample: 0.1 is print detail information about each step and then you can run the step you want.
#         0.1.* is directly running the step. 
    # --------------------------------------------------------------------------
    #  Data  
    # --------------------------------------------------------------------------
    0.1) echo "mumuH_inv analysis...  -> Maoqiang Jing"
        usage_0_1
        echo "Please enter your option: " 
        read option 
        sub_0_1 option 
        ;;
    0.1.*) echo "mumuH_inv analysis...  -> Maoqiang Jing"
        sub_0_1 option
        ;;
        
    0.2) echo "mumuH_inv analysis..."
           usage_0_2
           echo "mumuH_inv analysis... " 
           read option  
        sub_0_2 option 
        ;;
    0.2.*) echo "mumuH_inv analysis..."
        sub_0_2 option 
        ;;

    0.3) echo "The backgroud of mumuH_inv analysis..." 
        usage_0_3
        echo "Please enter your option: " 
        read option 
        sub_0_3 option 
        ;;
    0.3.*) echo "The backgroud of mumuH_inv analysis..."
        sub_0_3 option 
        ;;

    0.4) echo "eeH_inv analysis..."
        usage_0_4
        echo "Please enter your option: " 
        read option
        sub_0_4 option 
        ;;
        
    0.4.*) echo "eeH_inv analysis..."
        sub_0_4 option 
        ;; 	

    0.5) echo "qqH_inv analysis..."
        usage_0_5
        echo "Please enter your option: " 
        read option
        sub_0_5 option 
        ;;
        
    0.5.*) echo "qqH_inv analysis..."
        sub_0_5 option 
        ;; 	

    0.6) echo "fit and calculate upperlimit"
        usage_0_6
        echo "Please enter your option: " 
        read option
        sub_0_6 option 
        ;;

    0.6.*) echo "fit and calculate upperlimit"
        sub_0_6 option 
        ;; 	

esac