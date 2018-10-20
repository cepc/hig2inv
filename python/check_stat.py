#!/usr/bin/env python
"""
Generate Marlin Steer Files  
"""

__author__ = "Ryuta Kiuchi <kiuchi@ihep.ac.cn>"
__copyright__ = "Copyright (c) Ryta Kiuchi"
__created__ = "[2018-07-12 Thr 20:42]"

import sys
import os


def main():
    args = sys.argv[1:]

    tab = args[0]
    src = args[1]

    table = open(tab , 'r' )
    ndir=0
    tot_nfile=0
    tot_nslcio=0
    for s_line in table :
        if not s_line.startswith('#'):
            ndir = ndir + 1
            l = [x.strip() for x in s_line.split(',')]
            dname    = l[0]
            src_each = os.path.join(src, dname)	

            nfile=0
            nslcio=0
            for root, dirs, files in os.walk(src_each):
                for f in files:
                    nfile = nfile + 1
                    num_lines = sum(1 for line in open(os.path.join(src_each, f)))
                    nslcio = nslcio + num_lines

            sys.stdout.write(' %+20s :  %+8s XML job files,  total %+8s slcio files  \n' % (dname, nfile, nslcio) )
            tot_nfile = tot_nfile + nfile
            tot_nslcio = tot_nslcio + nslcio

    sys.stdout.write(' \n' )
    sys.stdout.write(' Number of directory is %s \n' % (ndir) )
    sys.stdout.write(' Number of XML job file is %s \n' % (tot_nfile) )
    sys.stdout.write(' Number of slcio file is %s \n' % (tot_nslcio) )
    sys.stdout.write(' \n' )
    
if __name__ == '__main__':
    main()
