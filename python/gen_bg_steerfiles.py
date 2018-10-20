#!/usr/bin/env python
"""
Generate Marlin Steer Files for Background Samples
"""

__author__ = "Ryuta Kiuchi <kiuchi@ihep.ac.cn>"
__copyright__ = "Copyright (c) Ryta Kiuchi"
__created__ = "[2018-07-11 Wed 22:00]"

import sys
import os
from string import Template

GEAR_CEPC_V1 = '/workfs/bes/lig/config/ilcsoft/gear_cepc_v1.xml'
GEAR_CEPC_V4 = '/besfs/groups/higgs/data/SimReco/wo_BS/CEPC_v4/higgs/smart_final_states/GearOutput.xml'

ECMS_CEPC_V1 = 250.0
ECMS_CEPC_V4 = 240.0

def main():
    args = sys.argv[1:]

    tab = args[0]
    tpl = args[1]
    src = args[2]
    dst = args[3]
    rootfname = args[4]

    if src.startswith('.'):                    
        src = src[2:]
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


    # Read background sample list    
    table = open(tab , 'r' )
    for s_line in table :
        if not s_line.startswith('#'):
            l = [x.strip() for x in s_line.split(',')]
            dname    = l[0]
            detector_conf = l[5]

            output_dir = dst + '/' + dname
            os.makedirs( output_dir )

            test_dir = dst + '/' + dname + '/test'
            os.makedirs( test_dir )

            rootfile_dir = rootfname + '/' + dname
            os.makedirs( rootfile_dir )
        
            src_each = os.path.join(src, dname)

            nfile=0
            for root, dirs, files in os.walk(src_each):
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
                    outname = './' + output_dir + '/' + head + f1 + tail

                    # Set Marlin job's output rootfile name (in absolute path)
                    cwd = os.getcwd()
                    f2 = f1.split('G')[1]
                    root_name = cwd + '/' + rootfile_dir + '/ana_File' + f2 + '.root'

                    # Replace Variables in XML Template
                    t = Template(xml_in)
                    lines = []
                    if detector_conf == 'CEPC_V4':
                        lines.append( t.substitute( slcio_in_list=data1, max_event_num=-1, gear_xml=GEAR_CEPC_V4, 
                                                    ecms=ECMS_CEPC_V4, output_rootfile=root_name ) )
                    if detector_conf == 'V1':
                        lines.append( t.substitute( slcio_in_list=data1, max_event_num=-1, gear_xml=GEAR_CEPC_V1,
                                                    ecms=ECMS_CEPC_V1, output_rootfile=root_name ) )

                    # Generate XML files
                    fout = open(outname,'w')
                    fout.writelines(lines) 
                    fout.close()
                    sys.stdout.write('Creating steer file %s \n'  % outname)
            
                    nfile = nfile + 1

                    # For run small samples 
                    if nfile < 3 :        
                        root_name = 'ana_bg_test_' + str(nfile) + '.root'
                        t = Template(xml_in)
                        lines = []
                        if detector_conf == 'CEPC_V4':
                            lines.append( t.substitute( slcio_in_list=data1, max_event_num=100, gear_xml=GEAR_CEPC_V4, 
                                                        ecms=ECMS_CEPC_V4, output_rootfile=root_name ) )
                        if detector_conf == 'V1':
                            lines.append( t.substitute( slcio_in_list=data1, max_event_num=100, gear_xml=GEAR_CEPC_V1,
                                                        ecms=ECMS_CEPC_V1, output_rootfile=root_name ) )

                        outname = './' + output_dir + '/test/sample-' + str(nfile) + '.xml'
                        fout = open(outname,'w')
                        fout.writelines(lines) 
                        fout.close()
                        sys.stdout.write('Creating steer file %s \n'  % outname)


if __name__ == '__main__':
    main()
 