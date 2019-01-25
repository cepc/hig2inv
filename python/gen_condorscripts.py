#!/usr/bin/env python
"""
Generate Condor Scripts  
"""

__author__ = "Ryuta Kiuchi <kiuchi@ihep.ac.cn>"
__copyright__ = "Copyright (c) Ryta Kiuchi"
__created__ = "[2018-06-11 Mon 9:00]"

import sys
import os
import re


def usage():
    sys.stdout.write('''
NAME
    gen_condorscripts.py 

SYNOPSIS

    ./gen_condorscripts.py  [option] [input_dir] [output_dir] [flag]

option     : For Marling job ( option = 1 ) or Event selection ( option = 2 )
input_dir  : Directory of Marlin Steer Files (option=1) or analyzed root files (option=2)  
output_dir : Top directory for Condor jobs under where those generated scripts are going to be stored
flag       : To be passed (for the moment, sel_event.py )

AUTHOR 
    Ryuta Kiuchi <kiuchi@ihep.ac.cn> 

DATE
    June 2018 
\n''')


def main():
    args = sys.argv[1:]
    if len(args) < 4:
        return usage()

    opt = int(args[0])
    src = args[1]
    dst = args[2]
    pname = args[3]
    
    if src.startswith('.'):                    
        src = src[2:]
    if src.endswith('/'):                    
        src = src[:-1]

    if dst.startswith('.'):  
        dst = dst[2:]
    if dst.endswith('/'):                    
        dst = dst[:-1]


    cwd = os.getcwd()

    if not ( opt == 1 or opt == 2 ):
        sys.stdout.write('#########                                                               \n')
        sys.stdout.write('[Error]                                                                 \n')
        sys.stdout.write('    Option input value does not match. Please select one of following:  \n')
        sys.stdout.write('                                                                        \n')
        sys.stdout.write('    Marlin job execution  ( option = 1 ) or                             \n')
        sys.stdout.write('    Final event selection ( option = 2 )                                \n')
        sys.stdout.write('#########                                                               \n')
        sys.stdout.write('                                                                        \n')

        return usage()

    if( opt == 1 ):
  
        files=os.listdir(src)
        nfile=0
        for file in files:
            index = re.search('.xml', file)
            if index:            
                nfile = nfile + 1

                outname = './' + dst + '/script/marlin/condor_sub_marlin-' + str(nfile) + '.sh'
                
                fout_script = open(outname,'w')
                fout_script.write('#!/bin/bash          \n') 
                fout_script.write('                     \n') 
                fout_script.write('cd %s                \n' % cwd) 
                fout_script.write('                     \n') 
                fout_script.write('source setup.sh      \n')
                fout_script.write('                     \n') 
                fout_script.write('cd %s                \n' % src) 
                fout_script.write('                     \n') 
                fout_script.write('Marlin %s            \n' % file) 
                fout_script.write('                     \n') 
                fout_script.close()
                sys.stdout.write('Creating condor submit script %s \n'  % outname)

                os.chmod(outname, 0744)


        condor_submit_shell = './' + dst + '/condor_submit.sh'
        script_name= dst + '/script/marlin/condor_sub_marlin-${num}.sh'

        fout = open(condor_submit_shell,'w')
        fout.write('#!/bin/bash                                                                       \n') 
        fout.write('                                                                                  \n') 
        fout.write('Work_Dir=%s                                                                       \n' % cwd) 
        fout.write('                                                                                  \n') 
        fout.write('Log_Dir=${Work_Dir}/%s/log                                                        \n' % dst)
        fout.write('                                                                                  \n') 
        fout.write('month=$(date +\'%m\')                                                             \n') 
        fout.write('day=$(date +\'%d\')                                                               \n') 
        fout.write('hour=$(date +\'%H\')                                                              \n') 
        fout.write('minute=$(date +\'%M\')                                                            \n') 
        fout.write('second=$(date +\'%S\')                                                            \n') 
        fout.write('Time_Stamp=$month$day$hour$minute$second                                          \n')   
        fout.write('                                                                                  \n')         
        fout.write('mkdir ${Log_Dir}/${Time_Stamp}                                                    \n') 
        fout.write('                                                                                  \n') 
        fout.write('for num in {1..%s}                                                                \n' % nfile) 
        fout.write('do                                                                                \n') 
        fout.write('  Log_File=${Log_Dir}/${Time_Stamp}/log_${num}.txt                                \n') 
        fout.write('  eLog_File=${Log_Dir}/${Time_Stamp}/err_${num}.txt                               \n') 
        fout.write('                                                                                  \n') 
        fout.write('  script_name=%s                                                                  \n' % script_name) 
        fout.write('  source ${Work_Dir}/${script_name}   \n') 
        fout.write('done                                                                              \n') 
        fout.write('                                                                                  \n') 
        fout.close()
        sys.stdout.write('Creating condor submit script %s \n'  % condor_submit_shell)

        os.chmod(condor_submit_shell, 0744)
    
        print nfile


    if( opt == 2 ):
  
        files=os.listdir(src)
        nfile=0
        for file in files:
            index = re.search('.root', file)
            if index:            
                nfile = nfile + 1

                outname = './' + dst + '/script/eventsel/condor_sub_eventsel-' + str(nfile) + '.sh'
                
                file_tmp = file.split('.root')[0]
                src_tmp = src.split('ana')[0]

                root_in = cwd + '/' + src + '/' + file
#                root_scale_out = cwd + '/' + src_tmp + 'ana/' + file_tmp + '_scale.root'
                root_out = cwd + '/' + src_tmp + 'events/ana/' + file_tmp + '_event.root'
#                Select_name = 'e2E2h_invi'
                fout_script = open(outname,'w')
                fout_script.write('#!/bin/bash                      \n') 
                fout_script.write('                                 \n') 
                fout_script.write('cd %s                            \n' % cwd) 
                fout_script.write('                                 \n') 
                fout_script.write('source setup.sh                  \n')
                fout_script.write('                                 \n') 
#                fout_script.write('./python/chs_events.py %s %s %s\n' %(root_in, root_scale_out, Select_name))
                if pname == "ee":
                    fout_script.write('./python/sel_ee_events.py  %s %s \n' % (root_in, root_out )) 
                elif pname == "qq":
                    fout_script.write('./python/sel_qq_events.py  %s %s \n' % (root_in, root_out )) 
                else:
                    fout_script.write('./python/sel_mumu_events.py  %s %s \n' % (root_in, root_out ))
                fout_script.write('                                 \n') 
                fout_script.close()
                sys.stdout.write('Creating condor submit script %s \n'  % outname)

                os.chmod(outname, 0744)


        condor_submit_shell = './' + dst + '/condor_submit_eventsel.sh'
        script_name= dst + '/script/eventsel/condor_sub_eventsel-${num}.sh'

        fout = open(condor_submit_shell,'w')
        fout.write('#!/bin/bash                                                                       \n') 
        fout.write('                                                                                  \n') 
        fout.write('Work_Dir=%s                                                                       \n' % cwd) 
        fout.write('                                                                                  \n') 
        fout.write('Log_Dir=${Work_Dir}/%s/log/events                                                 \n' % dst)
        fout.write('                                                                                  \n') 
        fout.write('month=$(date +\'%m\')                                                             \n') 
        fout.write('day=$(date +\'%d\')                                                               \n') 
        fout.write('hour=$(date +\'%H\')                                                              \n') 
        fout.write('minute=$(date +\'%M\')                                                            \n') 
        fout.write('second=$(date +\'%S\')                                                            \n') 
        fout.write('Time_Stamp=$month$day$hour$minute$second                                          \n')   
        fout.write('                                                                                  \n')         
        fout.write('mkdir ${Log_Dir}/${Time_Stamp}                                                    \n') 
        fout.write('                                                                                  \n') 
        fout.write('for num in {1..%s}                                                                \n' % nfile) 
        fout.write('do                                                                                \n') 
        fout.write('  Log_File=${Log_Dir}/${Time_Stamp}/log_${num}.txt                                \n') 
        fout.write('  eLog_File=${Log_Dir}/${Time_Stamp}/err_${num}.txt                               \n') 
        fout.write('                                                                                  \n') 
        fout.write('  script_name=%s                                                                  \n' % script_name) 
        fout.write(' hep_sub -g physics -o ${Log_File} -e ${eLog_File} ${Work_Dir}/${script_name}   \n') 
        fout.write('done                                                                              \n') 
        fout.write('                                                                                  \n') 
        fout.close()
        sys.stdout.write('Creating condor submit script %s \n'  % condor_submit_shell)

        os.chmod(condor_submit_shell, 0744)
    
        print nfile


if __name__ == '__main__':
    main()
    
