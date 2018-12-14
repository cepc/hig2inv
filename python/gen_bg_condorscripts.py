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
    July 2018 
\n''')


def main():
    args = sys.argv[1:]
    if len(args) < 3:
        return usage()

    opt = int(args[0])
    src = args[1]
    dst = args[2]
#    flag = args[3]
    
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
        
        # get directory name
        files = os.listdir(src)
        files_dir = [f for f in files if os.path.isdir(os.path.join(src, f))]
        print(files_dir)

        # create directory for condor scripts
        for dname in files_dir:
            output_dir = dst + '/' + dname + '/script/marlin'
            #os.makedirs( output_dir )
            outlogname = dst.split('/condor')[0]
            outlog_dir = outlogname + '/log/marlin/'+dname
            #os.makedirs( outlog_dir )

            src_each = os.path.join(src, dname)

            files=os.listdir(src_each)
            nfile=0 
            for f in files:
                index = re.search('.xml', f)
                if index:            
                    nfile = nfile + 1

                    outname = './' + dst + '/' + dname + '/script/marlin/condor_sub_' + dname + \
                        '_marlin-' + str(nfile) + '.sh'
                
                    fout_script = open(outname,'w')
                    fout_script.write('#!/bin/bash          \n') 
                    fout_script.write('                     \n') 
                    fout_script.write('cd %s                \n' % cwd) 
                    fout_script.write('                     \n') 
                    fout_script.write('source setup.sh      \n')
                    fout_script.write('                     \n') 
                    fout_script.write('cd %s                \n' % src_each) 
                    fout_script.write('                     \n') 
                    fout_script.write('Marlin %s            \n' % f) 
                    fout_script.write('                     \n') 
                    fout_script.close()
                    sys.stdout.write('Creating condor submit script %s \n'  % outname)

                    os.chmod(outname, 0744)

            condor_submit_shell = './' + dst + '/' + dname + '/condor_submit.sh'
            script_name= dst + '/' + dname + '/script/marlin/condor_sub_' + dname + '_marlin-${num}.sh'

            fout = open(condor_submit_shell,'w')
            fout.write('#!/bin/bash                                                                       \n') 
            fout.write('                                                                                  \n') 
            fout.write('Work_Dir=%s                                                                       \n' % cwd) 
            fout.write('                                                                                  \n') 
            fout.write('Log_Dir=${Work_Dir}/%s                                                            \n' % outlog_dir)
            fout.write('                                                                                  \n') 
            fout.write('month=$(date +\'%m\')                                                             \n') 
            fout.write('day=$(date +\'%d\')                                                               \n') 
            fout.write('hour=$(date +\'%H\')                                                              \n') 
            fout.write('minute=$(date +\'%M\')                                                            \n') 
            fout.write('second=$(date +\'%S\')                                                            \n') 
            fout.write('Time_Stamp=$month$day$hour$minute$second                                          \n')   
            fout.write('                                                                                  \n')         
            fout.write('mkdir -p ${Log_Dir}/${Time_Stamp}                                                    \n') 
            fout.write('                                                                                  \n') 
            fout.write('all_files=%s                                                                      \n' % nfile)
            fout.write('if [[ "$1" -le $all_files ]]; then                                                \n')  
            fout.write('    max_num=$1                                                                    \n') 	
            fout.write('else                                                                              \n') 
            fout.write('    max_num=$all_files                                                            \n') 
            fout.write('fi                                                                                \n') 
            fout.write('                                                                                  \n') 
            fout.write('for num in `seq ${max_num}`                                                       \n') 
            fout.write('do                                                                                \n') 
            fout.write('  Log_File=${Log_Dir}/${Time_Stamp}/log_${num}.txt                                \n') 
            fout.write('  eLog_File=${Log_Dir}/${Time_Stamp}/err_${num}.txt                               \n') 
            fout.write('                                                                                  \n') 
            fout.write('  script_name=%s                                                                  \n' % script_name) 
            fout.write('  hep_sub -g physics -o ${Log_File} -e ${eLog_File}  ${Work_Dir}/${script_name}   \n') 
            fout.write('done                                                                              \n') 
            fout.write('                                                                                  \n') 
            fout.close()
            sys.stdout.write('Creating condor submit script %s \n'  % condor_submit_shell)
            
            os.chmod(condor_submit_shell, 0744)
    
            print nfile

    if( opt == 2 ):

        # get directory name
        files = os.listdir(src)
        files_dir = [f for f in files if os.path.isdir(os.path.join(src, f))]
        #print(files_dir)

        # create directory for condor scripts
        for dname in files_dir:
            output_dir = dst + '/' + dname + '/script/eventsel'
            #os.makedirs( output_dir )
            outlogname = dst.split('/condor')[0]
            outlog_dir = outlogname + '/log/events'+'/'+dname
            #os.makedirs( outlog_dir )

            src_tmp = src.split('ana')[0]
            rootout_dir = src_tmp + 'events/ana/' + dname 

            #os.makedirs( rootout_dir )

            src_each = os.path.join(src, dname)

            files=os.listdir(src_each)
            nfile=0 
            for f in files:
                index = re.search('.root', f)
                if index:            
                    nfile = nfile + 1

                    outname = './' + dst + '/' + dname + '/script/eventsel/condor_sub_' + dname + \
                        '_eventsel-' + str(nfile) + '.sh'


                    file_tmp = f.split('.root')[0]
                    #src_tmp = src.split('ana')[0]

                    root_in = cwd + '/' + src + '/' + dname + '/' + f
                    root_out = cwd + '/' + rootout_dir + '/' + file_tmp + '_event.root'
                    

                    fout_script = open(outname,'w')
                    fout_script.write('#!/bin/bash                      \n') 
                    fout_script.write('                                 \n') 
                    fout_script.write('cd %s                            \n' % cwd) 
                    fout_script.write('                                 \n') 
                    fout_script.write('source setup.sh                  \n')
                    fout_script.write('                                 \n')
                    fout_script.write('./python/sel_events.py  %s %s \n' % ( root_in, root_out ) )
                    fout_script.close()
                    sys.stdout.write('Creating condor submit script %s \n'  % outname)

                    os.chmod(outname, 0744)

            condor_submit_shell = './' + dst + '/' + dname + '/condor_submit_eventsel.sh'
            script_name= dst + '/' + dname + '/script/eventsel/condor_sub_' + dname + '_eventsel-${num}.sh'

            fout = open(condor_submit_shell,'w')
            fout.write('#!/bin/bash                                                                       \n') 
            fout.write('                                                                                  \n') 
            fout.write('Work_Dir=%s                                                                       \n' % cwd) 
            fout.write('                                                                                  \n') 
            fout.write('Log_Dir=${Work_Dir}/%s                                                            \n' % outlog_dir)
            fout.write('                                                                                  \n') 
            fout.write('month=$(date +\'%m\')                                                             \n') 
            fout.write('day=$(date +\'%d\')                                                               \n') 
            fout.write('hour=$(date +\'%H\')                                                              \n') 
            fout.write('minute=$(date +\'%M\')                                                            \n') 
            fout.write('second=$(date +\'%S\')                                                            \n') 
            fout.write('Time_Stamp=$month$day$hour$minute$second                                          \n')   
            fout.write('                                                                                  \n')         
            fout.write('mkdir -p ${Log_Dir}/${Time_Stamp}                                          \n') 
            fout.write('                                                                                  \n') 
            fout.write('for num in {1..%s}                                                                \n' % nfile) 
            fout.write('do                                                                                \n') 
            fout.write('  Log_File=${Log_Dir}/${Time_Stamp}/log_${num}.txt                                \n') 
            fout.write('  eLog_File=${Log_Dir}/${Time_Stamp}/err_${num}.txt                               \n') 
            fout.write('                                                                                  \n') 
            fout.write('  script_name=%s                                                                  \n' % script_name) 
            fout.write(' hep_sub -g physics -o ${Log_File} -e ${eLog_File}  ${Work_Dir}/${script_name}   \n') 
            fout.write('done                                                                              \n') 
            fout.write('                                                                                  \n') 
            fout.close()
            sys.stdout.write('Creating condor submit script %s \n'  % condor_submit_shell)
            os.chmod(condor_submit_shell, 0744)
            
            print nfile 


            #Generate scale script
            outname = './' + dst + '/' + dname + '/script/scalesel/condor_sub_' + dname + \
                '_scalesel-1'  + '.sh'

            file_tmp = f.split('.root')[0]
            #src_tmp = src.split('ana')[0]

            root_scale_in = cwd + '/' + 'run/bg/plot/'+dname+'/ana_File_merged_1.root'
            root_scale_out = cwd + '/' + 'run/bg/hist/'+dname+'/ana_File_merged_1.root'
            table_list ='table/bg_sample_list.txt'
            fout_script = open(outname,'w')
            fout_script.write('#!/bin/bash                      \n') 
            fout_script.write('                                 \n') 
            fout_script.write('cd %s                            \n' % cwd) 
            fout_script.write('                                 \n') 
            fout_script.write('source setup.sh                  \n')
            fout_script.write('                                 \n')
            fout_script.write('./python/scale_events.py  %s %s %s %s\n' % ( root_scale_in, root_scale_out,dname,table_list ) )                     
            fout_script.write('                                 \n') 
            fout_script.close()
            sys.stdout.write('Creating condor submit script %s \n'  % outname)

            os.chmod(outname, 0744)

            condor_scale_shell = './' + dst + '/' + dname + '/condor_scale_eventsel.sh'
            script_name= dst + '/' + dname + '/script/scalesel/condor_sub_' + dname + '_scalesel-1.sh'
            outlog_dir = outlogname + '/log/scalevent/'+dname
            fout = open(condor_scale_shell,'w')
            fout.write('#!/bin/bash                                                                       \n') 
            fout.write('                                                                                  \n') 
            fout.write('Work_Dir=%s                                                                       \n' % cwd) 
            fout.write('                                                                                  \n') 
            fout.write('Log_Dir=${Work_Dir}/%s                                                            \n' % outlog_dir)
            fout.write('                                                                                  \n') 
            fout.write('month=$(date +\'%m\')                                                             \n') 
            fout.write('day=$(date +\'%d\')                                                               \n') 
            fout.write('hour=$(date +\'%H\')                                                              \n') 
            fout.write('minute=$(date +\'%M\')                                                            \n') 
            fout.write('second=$(date +\'%S\')                                                            \n') 
            fout.write('Time_Stamp=$month$day$hour$minute$second                                          \n')   
            fout.write('                                                                                  \n')         
            fout.write('mkdir -p ${Log_Dir}/                                                  \n') 
            fout.write('                                                                                  \n') 
            fout.write('  Log_File=${Log_Dir}/                                \n') 
            fout.write('  eLog_File=${Log_Dir}/                               \n') 
            fout.write('                                                                                  \n') 
            fout.write('  script_name=%s                                                                  \n' % script_name) 
            fout.write('  ./${script_name}   \n') 
            fout.write('                                                                                  \n') 
            fout.close()
            sys.stdout.write('Creating condor submit script %s \n'  % condor_scale_shell)
            
            os.chmod(condor_scale_shell, 0744)


if __name__ == '__main__':
    main()
