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

    args = sys.argv[1]
    table = open(args , 'r' )
    pname =sys.argv[2]
#calculate twofevent
    cutnumber = 9
    for i in range(0,11):
        exec 'k%d = 0 ' %i
    for s_row in table :
        if not s_row.startswith('#'):
            l = [x.strip() for x in s_row.split(',')] 
            if (l[0] == "e1e1" or l[0] == "e2e2" or l[0] == "e3e3" or l[0] == "qq" or l[0] == "n1n1" or l[0] == "n2n2" or l[0] == "n3n3" ):
                print l[1]
                for i in range(0,cutnumber):
                    exec 'k%d += int(l[%d])'%(i,i+1)
    twofevent = []
    for i in range (0,cutnumber):
        exec 'twofevent.append(k%d)'%(i)

#calculate single_w
    table = open(args , 'r' )
    for i in range(0,11):
        exec 'k%d = 0 ' %i
    for s_row in table :
        if  s_row.startswith('sw_'):
            l = [x.strip() for x in s_row.split(',')]                
            for i in range(0,cutnumber):
                exec 'k%d += int(l[%d])'%(i,i+1)
    single_w = []
    for i in range (0,cutnumber):
        exec 'single_w.append(k%d)'%(i) 
      

    #calculate single_z
    table = open(args , 'r' )
    for i in range(0,11):
        exec 'k%d = 0 ' %i
    for s_row in table :
        if  s_row.startswith('sze_') or s_row.startswith('sznu') :
            l = [x.strip() for x in s_row.split(',')]   
            print l[0]            
            for i in range(0,cutnumber):
                exec 'k%d += int(l[%d])'%(i,i+1)
    single_z = []
    for i in range (0,cutnumber):
        exec 'single_z.append(k%d)'%(i) 


    #calculate zz
    table = open(args , 'r' )
    for i in range(0,11):
        exec 'k%d = 0 ' %i
    for s_row in table :
        if  s_row.startswith('zz_'):
            l = [x.strip() for x in s_row.split(',')]   
            
            for i in range(0,cutnumber):
                exec 'k%d += int(l[%d])'%(i,i+1)
    zz = []
    for i in range (0,cutnumber):
        exec 'zz.append(k%d)'%(i) 
 
    #calculate ww
    table = open(args , 'r' )
    for i in range(0,11):
        exec 'k%d = 0 ' %i
    for s_row in table :
        if  s_row.startswith('ww_'):
            l = [x.strip() for x in s_row.split(',')]   
                         
            for i in range(0,cutnumber):
                exec 'k%d += int(l[%d])'%(i,i+1)
    ww = []
    for i in range (0,cutnumber):
        exec 'ww.append(k%d)'%(i) 
        

    #calculate zzorww
    table = open(args , 'r' )
    for i in range(0,11):
        exec 'k%d = 0 ' %i
    for s_row in table :
        if  s_row.startswith('zzorww_'):
            l = [x.strip() for x in s_row.split(',')]   
            
            for i in range(0,cutnumber):
                exec 'k%d += int(l[%d])'%(i,i+1)
    zzorww = []
    for i in range (0,cutnumber):
        exec 'zzorww.append(k%d)'%(i) 

    #calculate zorw
    table = open(args , 'r' )
    for i in range(0,11):
        exec 'k%d = 0 ' %i
    for s_row in table :
        if  s_row.startswith('szeorsw'):
            l = [x.strip() for x in s_row.split(',')]   
            
            for i in range(0,cutnumber):
                exec 'k%d += int(l[%d])'%(i,i+1)
    szorsw = []
    for i in range (0,cutnumber):
        exec 'szorsw.append(k%d)'%(i)
#calculate total_bkg
    table = open(args , 'r' )
    for i in range(0,11):
        exec 'k%d = 0 ' %i
    for s_row in table :
        if  not s_row.startswith('#'):
            l = [x.strip() for x in s_row.split(',')]                 
            for i in range(0,cutnumber):
                exec 'k%d += int(l[%d])'%(i,i+1)
    total_bkg = []
    for i in range (0,cutnumber):
        exec 'total_bkg.append(k%d)'%(i) 

    #calculate ZH_visible
    table = open(args , 'r' )
    for i in range(0,11):
        exec 'k%d = 0 ' %i
    for s_row in table :
        if  s_row.startswith('Z_'):
            l = [x.strip() for x in s_row.split(',')]   
                         
            for i in range(0,cutnumber):
                exec 'k%d += int(l[%d])'%(i,i+1)
    ZH_visible = []
    for i in range (0,cutnumber):
        exec 'ZH_visible.append(k%d)'%(i) 
    record_bkg_information( twofevent, single_w, single_z, zz, ww,szorsw, zzorww,ZH_visible, total_bkg ,pname )  
#            j=j+1                
#           exec 'k%d.append(l[%d])'%(i,i)
#            if pname  == "mumuH": 
#                recode_mumu_information(processname,event)
#            elif pname == "eeH":
#                recode_ee_information(processname,event)
#            elif pname == "qqH":
#                recode_qq_information(processname,event) 
#                print 1   
#            else:
#                print "This is  wrong. Please check it" 
#                sys.exit()           
def record_bkg_information( twofevent, single_w, single_z, zz, ww, szorsw,zzorww,ZH_visible, total_bkg ,pname):
    
    cwd = os.getcwd()
    if pname == "qqH":
        out_putname = cwd + '/' + 'table/qqH/' + 'out_list_b.txt'
    elif pname == "eeH":
        out_putname = cwd + '/' + 'table/eeH/' + 'out_list_b.txt'
    else:
        out_putname = cwd + '/' + 'table/mumuH/' + 'out_list_b.txt'		
    fout_script = open(out_putname,'a')
    fout_script.write('%-15s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s\n'%('#processname','raw','N_mu','Mrecoil','mmdie','pt','#phi','visible','E/P','cut'))
    fout_script.write('%-15s,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d\n'%('2f',twofevent[0],twofevent[1],twofevent[2],twofevent[3],twofevent[4],twofevent[5],twofevent[6],twofevent[7],twofevent[8]))
    fout_script.write('%-15s,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d\n'%('single_w',single_w[0],single_w[1],single_w[2],single_w[3],single_w[4],single_w[5],single_w[6],single_w[7],single_w[8]))
    fout_script.write('%-15s,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d\n'%('single_z',single_z[0],single_z[1],single_z[2],single_z[3],single_z[4],single_z[5],single_z[6],single_z[7],single_z[8]))
    fout_script.write('%-15s,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d\n'%('szorsw',szorsw[0],szorsw[1],szorsw[2],szorsw[3],szorsw[4],szorsw[5],szorsw[6],szorsw[7],szorsw[8]))
    fout_script.write('%-15s,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d\n'%('zz',zz[0],zz[1],zz[2],zz[3],zz[4],zz[5],zz[6],zz[7],zz[8]))
    fout_script.write('%-15s,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d\n'%('ww',ww[0],ww[1],ww[2],ww[3],ww[4],ww[5],ww[6],ww[7],ww[8]))
    fout_script.write('%-15s,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d\n'%('zzorww',zzorww[0],zzorww[1],zzorww[2],zzorww[3],zzorww[4],zzorww[5],zzorww[6],zzorww[7],zzorww[8]))
    fout_script.write('%-15s,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d\n'%('ZH_visible',ZH_visible[0],ZH_visible[1],ZH_visible[2],ZH_visible[3],ZH_visible[4],ZH_visible[5],ZH_visible[6],ZH_visible[7],ZH_visible[8]))
    fout_script.write('%-15s,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d\n'%('total_bkg',total_bkg[0],total_bkg[1],total_bkg[2],total_bkg[3],total_bkg[4],total_bkg[5],total_bkg[6],total_bkg[7],total_bkg[8]))
    fout_script.close()
    sys.stdout.write('Outputname %s \n'  % out_putname)
    os.chmod(out_putname, 0744)
if __name__ == '__main__':
    main()
