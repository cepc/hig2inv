#!/usr/bin/env python 
#get all channels are ground to 2f, single_w signle_z ww zorw zzorww ZZ

__author__ = "Tan Yuhang <tanyuhang@ihep.ac.cn>"
__copyright__ = "Copyright (c) Tanyuhang"
__created__ = "[2018-09-18 ]"


import sys
import os
import copy
import re
import ROOT
from array import array 


def main():
    args = sys.argv[1:]
    inputfile = args[0]
    pname=[]
    for root, dirs, files in os.walk(inputfile):   
        for f in files:        
            event = []
            processname = f.split('.root')[0]
#			pname.append(processname)
            input_path = os.path.join(root,f)
            print input_path
#        print input_path
            event = get_bin_value(input_path)


            recode_information(processname,event)

def get_bin_value(inputfile):  
    sample = ROOT.TFile(inputfile)
    h = sample.Get('hevtflw')
    event = []
    for i in range(1,10):
        event.append(h.GetBinContent(i))  
    return event

    

def recode_information(src,event):
    cwd = os.getcwd() 
    out_putname = cwd + '/' + 'table/' + 'out_list_b.txt'
    fout_script = open(out_putname,'a')
    print src
    if src == 'zorw':
        fout_script.write('#cuts information by ground \n')
        fout_script.write('%-15s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s\n'%('#processname','raw','N_mu','Mrecoil','Mmumu','Pt','phi','Pz','visible','ratio'))
    fout_script.write('%-15s,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d\n'%(src,event[0],event[1],event[2],event[3],event[4],event[5],event[6],event[7],event[8]))
    fout_script.close()
    sys.stdout.write('Outputname %s \n'  % out_putname)
    os.chmod(out_putname, 0744)

if __name__ == '__main__':
    main()
