#!/usr/bin/env python
"""
Generate Marlin Steer Files  
"""

__author__ = "Tanyh <tanyuhang@ihep.ac.cn>"
__copyright__ = "Copyright (c) Tanyh"
__created__ = "[2018-10-19 ]"

import sys
import os
from string import Template

GEAR_CEPC_V1 = '/workfs/bes/lig/config/ilcsoft/gear_cepc_v1.xml'
GEAR_CEPC_V4 = '/besfs/groups/higgs/data/SimReco/wo_BS/CEPC_v4/higgs/smart_final_states/GearOutput.xml'

ECMS_CEPC_V1 = 250.0
ECMS_CEPC_V4 = 240.0


def usage():
    sys.stdout.write('''
NAME
    gen_steerfiles.py 

SYNOPSIS

    ./gen_steerfiles.py  [MarlinTemplateSteerfile] [input_dir] [output_dir] [RootFileName]

MarlinTemplateSteerFile : Marlin Steer File (Template) 
input_dir               : directory where the files which list slcio samples, are stored 
output_dir              : directory where xml files generated by this script are going to be stored
RootFileName            : Marling job output rootfile name base, such as, run/h2zz.root, run/ana_slcio.root, etc. 

AUTHOR 
    Tanyh <tanyuhang@ihep.ac.cn> 

DATE
    June 2018 
\n''')


def main():
    args = sys.argv[1:]
    if len(args) < 4:
        return usage()

    tpl = args[0]
    src = args[1]
    dst = args[2]
    rootfname = args[3]

    if src.startswith('.'):                    
        src = src[2:]
        print(src)
    if src.endswith('/'):                    
        src = src[:-1]

    if dst.startswith('.'):  
        dst = dst[2:]
    if dst.endswith('/'):                    
        dst = dst[:-1]

    if rootfname.startswith('.'):  
        rootfname = rootfname[2:]
    if rootfname.endswith('/'):                    
        rootfname = rootfname[:-1]

    # Read Marlin XML Template
    tpl_file = open(tpl, 'r')
    xml_in = tpl_file.read() 
    tpl_file.close()

    nfile=0
    for root, dirs, files in os.walk(src):
        for f in files:
            
            # Read the slcio file lists
            fin = os.path.join(root, f)
            input_datalist = open(fin,'r')
            data1 = input_datalist.read() 
            input_datalist.close()

            # Name of Steer file to be generated
            head = 'steer_'
            f1 = f.split('.txt')[0]
            tail = '.xml'
            outname = './' + dst + '/' + head + f1 + tail

            # Set Marlin job's output rootfile name (in absolute path)
            cwd = os.getcwd()
            f2 = f1.split('G')[1]
            rname = rootfname.split('.')[0] 
            root_name = cwd + '/' + rname + f2 + '.root'

            # Replace Variables in XML Template
            t = Template(xml_in)
            lines = []
            lines.append( t.substitute( slcio_in_list=data1, max_event_num=-1, gear_xml=GEAR_CEPC_V4, 
                                        ecms=ECMS_CEPC_V4, output_rootfile=root_name ) )

            # Generate XML files
            fout = open(outname,'w')
            fout.writelines(lines) 
            fout.close()
            sys.stdout.write('Creating steer file %s \n'  % outname)
            
            nfile = nfile + 1
            
            # For run small samples 
            if nfile < 3 :        
                root_name = 'out_signal_test_' + str(nfile) + '.root'
                t = Template(xml_in)
                lines = []
                lines.append( t.substitute( slcio_in_list=data1, max_event_num=-1, gear_xml=GEAR_CEPC_V4, 
                                            ecms=ECMS_CEPC_V4, output_rootfile=root_name ) )


                outname = './' + dst + '/test/sample-' + str(nfile) + '.xml'
                fout = open(outname,'w')
                fout.writelines(lines) 
                fout.close()
                sys.stdout.write('Creating steer file %s \n'  % outname)


if __name__ == '__main__':
    main()

   
