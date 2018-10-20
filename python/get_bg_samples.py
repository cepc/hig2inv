#!/usr/bin/env python   
"""
Get background samples list 
"""

__author__ = "Ryuta Kiuchi <kiuchi@ihep.ac.cn>"
__copyright__ = "Copyright (c) Ryuta Kiuchi"
__created__ = "[2018-07-11 wed 20:19]"

import sys
import os
from tools import save_list_into_file, group_files_by_size


def main():
    args = sys.argv[1:]
    if len(args) < 2:
        return

    tab = args[0]
    dst = args[1]
    #sys.stdout.write('Scanning %s...\n' %src)

    table = open(tab , 'r' )

    ctime = os.path.getctime(args[0])
    print( ctime )

    for s_line in table :
        if not s_line.startswith('#'):
            l = [x.strip() for x in s_line.split(',')]
            dname = l[0]
            output_dir = dst + '/' + dname
            os.makedirs( output_dir )

            src = l[4]
            name_tag = l[6]
            file_list = []
            for root, dirs, files in os.walk(src):
                for f in files:
                    if f.startswith(name_tag):
                        if f.endswith('.slcio'):
                            file_time = os.path.getmtime(os.path.join(root, f)) 
                            diff_day = (ctime - file_time)/3600.0/24.0  
                            #if diff_day > 1.0 : ## to avoid access to generating slcio files
                            if diff_day > 0.0 :
                                file_list.append(os.path.join(root, f)) 
#                                print(file_list)                               

            fname = l[0]   ## filename = dirname for the moment !            
            if len(args) == 3:
                size = args[2]
                sys.stdout.write('Size limit per list: %s\n' %size)
                groups = group_files_by_size(file_list, size)
                dst_com = fname.split('.')[0] 

                dst_ext = 'txt'
                n = 0 
                for file_list in groups:
                    n = n+1 
                    new_dst = os.path.join(output_dir, '%s_%s-%s.%s' %
                                           (dst_com, size, n, dst_ext))
                    save_list_into_file(file_list, new_dst)
                   


if __name__ == '__main__':
    main()
