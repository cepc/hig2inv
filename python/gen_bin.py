#!/usr/bin/env python 
#get all channels detail  value each step
__author__ = "Tan Yuhang <tanyuhang@ihep.ac.cn>"
__copyright__ = "Copyright (c) Tanyuhang"
__created__ = "[2018-09-18 ]"
import sys,os,copy,re
import ROOT
from array import array 

def main():
    args = sys.argv[1:]
    inputfile = args[0]
    table_list = args[1]
    Pname = args[2]
    for root, dirs, files in os.walk(inputfile):   
        for f in files:        
            event = []
            input_path = os.path.join(root,f)
#        print input_path
        event = get_bin_value(input_path)
        decay_name = inputfile.split('/')[-1]
        scale = get_decay_scale(decay_name,event,table_list)
        if Pname == "mumuH":  
            write_mumu_after_cut(input_path,event,scale)
            record_mumu_information(input_path,event)
        elif Pname == "eeH":
            write_ee_after_cut(input_path,event,scale)
            record_ee_information(input_path,event)
        elif Pname == "qqH":
            write_qq_after_cut(input_path,event,scale)
            record_qq_information(input_path,event)
        else:
            print "Sample name misses, please check that 1 !"
            sys.exit() 			

def get_bin_value(inputfile):  
    sample = ROOT.TFile(inputfile)
    h = sample.Get('hevtflw')
    event = []
    for i in range(1,10):
        event.append(h.GetBinContent(i))   
    return event

def get_decay_scale(processname,event,table_list):

    IntLum=5000
    event_gen=event[0]
    table = open(table_list , 'r' )
    cross_section=0.
    for s_line in table :
        if not s_line.startswith('#'):
            l = [x.strip() for x in s_line.split(',')] 
            process=l[0]            
            if processname == process:
                cross_section=l[2]
                print cross_section
    if processname=="e2E2h_invi":
        e2e2H_cross=6.77
        br_Hinv=0.5
        weight=IntLum*e2e2H_cross*br_Hinv/event_gen
    elif processname=="eeh_invi":
        eeH_cross=7.04
        br_Hinv=0.5
        weight=IntLum*eeH_cross*br_Hinv/event_gen
    elif processname=="qqh_invi":
        qqH_cross=136.81
        br_Hinv=0.5
        weight=IntLum*qqH_cross*br_Hinv/event_gen
    elif cross_section==0.:
        print "Sample name misses, please check that 2 !"
        sys.exit() 
    else: 
        cs = float(cross_section)
        weight=IntLum*cs/event_gen
    print processname,weight
    return weight
#mumuH_inv    
def write_mumu_after_cut(inputfile,event,scale):
    src = inputfile.split('/')[4]
    print src
    if re.search('_',src) != None:
        nm1=src.split('_')[0]
        nm2=src.split('_')[1]
        fourf_mumu_bkg(src,nm1,nm2,event,scale)
    else:
        twof_mumu_bkg(src,event,scale)
def fourf_mumu_bkg(src,nm1,nm2,event,scale):
    for i in range(0,9):
        event[i]=event[i]*scale
    cwd = os.getcwd()
    out_putname = cwd + '/table/mumuH/bin.txt'
    fout_script = open(out_putname,'a')
#	fout_script.write('scale=%f \n'%scale)
    fout_script.write(' \\begin{table}[hbtp] \n')
    fout_script.write(' \caption{$e^{+}e^{-}\\to %s\_%s $ cuts information ' % (nm1,nm2))
    fout_script.write('(Assume BR($H\\rightarrow inv.)$=50\\%)} \n')
    fout_script.write(' \label{tab:%s%s cut} \n' % (nm1,nm2))
    fout_script.write(' \small \n')
    fout_script.write(' \\begin{center} \n')
    fout_script.write(' \\renewcommand{\\arraystretch}{1.2} \n')
    fout_script.write(' \\begin{tabular}{ccc} \n')
    fout_script.write(' \hline \n')
    fout_script.write(' \hline \n')
    fout_script.write(' & The number of %s\_%s & Effectiveness \\\ \hline \n'  % (nm1,nm2))
    fout_script.write('Total generate & %d & %.3f \%% \\\ \n' %(event[0],(event[0]/event[0])*100))
    fout_script.write('$N_{\mu^{+}}\geq1$$N_{\mu^{-}}\geq1$ & %d  & %.3f \%% \\\ \n' %(event[1],(event[1]/event[0])*100))
    fout_script.write('$120GeV<M_{Recoil}<150GeV$& %d & %.3f \%% \\\ \n' %(event[2],(event[2]/event[0])*100))
    fout_script.write('$85GeV<M_{\mu^{+}\mu^{-}}<97GeV$ & %d & %.3f \%% \\\ \n'  %(event[3],(event[3]/event[0])*100))
    fout_script.write('$12GeV<P_{t}^{\mu^{+}\mu^{-}}$& %d & %.3f \%% \\\ \n'  %(event[4],(event[4]/event[0])*100))
    fout_script.write('$\Delta\phi<175$\degree & %d & %.3f \%% \\\ \n' %(event[5],(event[5]/event[0])*100))
    fout_script.write('$|P_{t}^{\mu^{+}\mu^{-}}|<50GeV$  & %d & %.3f \%% \\\ \n'  %(event[6],(event[6]/event[0])*100))
    fout_script.write('$102GeV<Visible Energy<107GeV$ & %d & %.3f \%% \\\ \n'  %(event[7],(event[7]/event[0])*100))
    fout_script.write('$\\frac{E}{P}<2.4$ & %d & %.3f \%% \\\ \n'  %(event[8],(event[8]/event[0])*100))
    fout_script.write(' \hline \n')
    fout_script.write(' \hline \n')
    fout_script.write(' \end{tabular} \n')
    fout_script.write(' \end{center} \n')
    fout_script.write(' \end{table} \n')
    fout_script.write('  \n')
    fout_script.write('  \n')
    fout_script.write('  \n')
    fout_script.close()
    sys.stdout.write('Outputname %s \n'  % out_putname)
    os.chmod(out_putname, 0744)

def twof_mumu_bkg(src,event,scale):
    for i in range(0,9):
        event[i]=event[i]*scale
    cwd = os.getcwd()
    out_putname = cwd + '/table/mumuH/bin.txt' 
    fout_script = open(out_putname,'a')
#	fout_script.write('scale=%f \n'%scale)
    fout_script.write(' \\begin{table}[hbtp] \n')
    fout_script.write(' \caption{$e^{+}e^{-}\\to %s  $ cuts information ' % src)
    fout_script.write('(Assume BR($H\\rightarrow inv.)$=50\\%)} \n')
    fout_script.write(' \label{tab:%s cut} \n'% src)
    fout_script.write(' \small \n')
    fout_script.write(' \\begin{center} \n')
    fout_script.write(' \\renewcommand{\\arraystretch}{1.2}\n')
    fout_script.write(' \\begin{tabular}{ccc} \n')
    fout_script.write(' \hline \n')
    fout_script.write(' \hline \n')
    fout_script.write(' & The number of %s & Effectiveness \\\ \hline \n' % src)
    fout_script.write('Total generate & %d & %.3f \%% \\\ \n' %(event[0],(event[0]/event[0])*100))
    fout_script.write('$N_{\mu^{+}}\geq1,N_{\mu^{-}}\geq1$& %d  & %.3f \%% \\\ \n' %(event[1],(event[1]/event[0])*100))
    fout_script.write('$120GeV<M_{Recoil}<150GeV$& %d & %.3f \%% \\\ \n' %(event[2],(event[2]/event[0])*100))
    fout_script.write('$85GeV<M_{\mu^{+}\mu^{-}}<97GeV$  & %d & %.3f \%% \\\ \n'  %(event[3],(event[3]/event[0])*100))
    fout_script.write('$12GeV<P_{t}^{\mu^{+}\mu^{-}}$ & %d & %.3f \%% \\\ \n'  %(event[4],(event[4]/event[0])*100))
    fout_script.write('$\Delta\phi<175$\degree & %d & %.3f \%% \\\ \n' %(event[5],(event[5]/event[0])*100))
    fout_script.write('$|P_{t}^{\mu^{+}\mu^{-}}|<50GeV$  & %d & %.3f \%% \\\ \n'  %(event[6],(event[6]/event[0])*100))
    fout_script.write('$102GeV<Visible Energy<107GeV$ & %d & %.3f \%% \\\ \n'  %(event[7],(event[7]/event[0])*100))
    fout_script.write('$\\frac{E}{P}<2.4$ & %d & %.3f \%% \\\ \n'  %(event[8],(event[8]/event[0])*100))
    fout_script.write(' \hline \n')
    fout_script.write(' \hline \n')
    fout_script.write(' \end{tabular} \n')
    fout_script.write(' \end{center} \n')
    fout_script.write(' \end{table} \n')
    fout_script.write('  \n')
    fout_script.write('  \n') 
    fout_script.write('  \n')
    fout_script.close()
    sys.stdout.write('Outputname %s \n'  % out_putname) 
    os.chmod(out_putname, 0744)

def record_mumu_information(inputfile,event):
    src = inputfile.split('/')[4]
    cwd = os.getcwd()
    out_putname = cwd + '/' + 'table/mumuH/' + 'out_list.txt'
    fout_script = open(out_putname,'a')
    if src == 'e1e1':
        fout_script.write('#cuts information \n')
        fout_script.write('%-15s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s\n'%('#processname','raw','N_mu','Mrecoil','Mmumu','Pt','phi','Pz','visible','E/P'))
    fout_script.write('%-15s,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d\n'%(src,event[0],event[1],event[2],event[3],event[4],event[5],event[6],event[7],event[8]))
    fout_script.close()
    sys.stdout.write('Outputname %s \n'  % out_putname)
    os.chmod(out_putname, 0744)

#eeH_inv

def write_ee_after_cut(inputfile,event,scale):
    src = inputfile.split('/')[4]
    if re.search('_',src) != None:
        nm1=src.split('_')[0]
        nm2=src.split('_')[1]
        fourf_ee_bkg(src,nm1,nm2,event,scale)
    else:
        twof_ee_bkg(src,event,scale)
def fourf_ee_bkg(src,nm1,nm2,event,scale):
    for i in range(0,9):
        event[i]=event[i]*scale
    cwd = os.getcwd()
    out_putname = cwd + '/table/eeH/bin.txt'
    fout_script = open(out_putname,'a')
#	fout_script.write('scale=%f \n'%scale)
    fout_script.write(' \\begin{table}[hbtp] \n')
    fout_script.write(' \caption{$e^{+}e^{-}\\to %s\_%s $ cuts information ' % (nm1,nm2))
    fout_script.write('(Assume BR($H\\rightarrow inv.)$=50\\%)} \n')
    fout_script.write(' \label{tab:%s%s cut} \n' % (nm1,nm2))
    fout_script.write(' \small \n')
    fout_script.write(' \\begin{center} \n')
    fout_script.write(' \\renewcommand{\\arraystretch}{1.2} \n')
    fout_script.write(' \\begin{tabular}{ccc} \n')
    fout_script.write(' \hline \n')
    fout_script.write(' \hline \n')
    fout_script.write(' & The number of %s\_%s & Effectiveness \\\ \hline \n'  % (nm1,nm2))
    fout_script.write('Total generate & %d & %.3f \%% \\\ \n' %(event[0],(event[0]/event[0])*100))
    fout_script.write('$N_{jet}$ & %d  & %.3f \%% \\\ \n' %(event[1],(event[1]/event[0])*100))
    fout_script.write('$10GeV<P_{t}^{dijet}<55GeV$& %d & %.3f \%% \\\ \n' %(event[2],(event[2]/event[0])*100))
    fout_script.write('$71GeV<M_{e^{+}e^{-}}<99GeV$& %d & %.3f \%% \\\ \n'  %(event[3],(event[3]/event[0])*100))
    fout_script.write('$ & %d & %.3f \%% \\\ \n'  %(event[4],(event[4]/event[0])*100))
    fout_script.write('$\Delta\phi<176$\degree & %d & %.3f \%% \\\ \n' %(event[5],(event[5]/event[0])*100))
    fout_script.write('$103GeV<Visible Energy<120GeV$  & %d & %.3f \%% \\\ \n'  %(event[6],(event[6]/event[0])*100))
    fout_script.write('$1.8<\\frac{E_{e^+e^-}}{P_{e^+e^-}}<2.4$ & %d & %.3f \%% \\\ \n'  %(event[7],(event[7]/event[0])*100))
    fout_script.write('$|P_{z}^{e^{+}e^{-}}|<55GeV$ & %d & %.3f \%% \\\ \n'  %(event[8],(event[8]/event[0])*100))
    fout_script.write(' \hline \n')
    fout_script.write(' \hline \n')
    fout_script.write(' \end{tabular} \n')
    fout_script.write(' \end{center} \n')
    fout_script.write(' \end{table} \n')
    fout_script.write('  \n')
    fout_script.write('  \n')
    fout_script.write('  \n')
    fout_script.close()
    sys.stdout.write('Outputname %s \n'  % out_putname)
    os.chmod(out_putname, 0744)

def twof_ee_bkg(src,event,scale):
    for i in range(0,9):
        event[i]=event[i]*scale
    cwd = os.getcwd()
    out_putname = cwd + '/table/eeH/bin.txt' 
    fout_script = open(out_putname,'a')
#	fout_script.write('scale=%f \n'%scale)
    fout_script.write(' \\begin{table}[hbtp] \n')
    fout_script.write(' \caption{$e^{+}e^{-}\\to %s  $ cuts information ' % src)
    fout_script.write('(Assume BR($H\\rightarrow inv.)$=50\\%)} \n')
    fout_script.write(' \label{tab:%s cut} \n'% src)
    fout_script.write(' \small \n')
    fout_script.write(' \\begin{center} \n')
    fout_script.write(' \\renewcommand{\\arraystretch}{1.2}\n')
    fout_script.write(' \\begin{tabular}{ccc} \n')
    fout_script.write(' \hline \n')
    fout_script.write(' \hline \n')
    fout_script.write(' & The number of %s & Effectiveness \\\ \hline \n' % src)
    fout_script.write('Total generate & %d & %.3f \%% \\\ \n' %(event[0],(event[0]/event[0])*100))
    fout_script.write('$N_{e^{+}}==1,N_{e^{-}}==1$ & %d  & %.3f \%% \\\ \n' %(event[1],(event[1]/event[0])*100))
    fout_script.write('$120GeV<M_{recoil}<160GeV$& %d & %.3f \%% \\\ \n' %(event[2],(event[2]/event[0])*100))
    fout_script.write('$71GeV<M_{e^{+}e^{-}}<99GeV$& %d & %.3f \%% \\\ \n'  %(event[3],(event[3]/event[0])*100))
    fout_script.write('$12GeV<P_{t}^{e^{+}e^{-}}<55GeV$ & %d & %.3f \%% \\\ \n'  %(event[4],(event[4]/event[0])*100))
    fout_script.write('$\Delta\phi<176$\degree & %d & %.3f \%% \\\ \n' %(event[5],(event[5]/event[0])*100))
    fout_script.write('$103GeV<Visible Energy<120GeV$ & %d & %.3f \%% \\\ \n'  %(event[6],(event[6]/event[0])*100))
    fout_script.write('$1.8<\\frac{E_{e^+e^-}}{P_{e^+e^-}}<2.4$ & %d & %.3f \%% \\\ \n'  %(event[7],(event[7]/event[0])*100))
    fout_script.write('$|P_{z}^{e^{+}e^{-}}|<55GeV$& %d & %.3f \%% \\\ \n'  %(event[8],(event[8]/event[0])*100))
    fout_script.write(' \hline \n')
    fout_script.write(' \hline \n')
    fout_script.write(' \end{tabular} \n')
    fout_script.write(' \end{center} \n')
    fout_script.write(' \end{table} \n')
    fout_script.write('  \n')
    fout_script.write('  \n') 
    fout_script.write('  \n')
    fout_script.close() 
    sys.stdout.write('Outputname %s \n'  % out_putname) 
    os.chmod(out_putname, 0744)

def record_ee_information(inputfile,event):
    src = inputfile.split('/')[4]
    cwd = os.getcwd()
    out_putname = cwd + '/' + 'table/eeH/' + 'out_list.txt'
    fout_script = open(out_putname,'a')
    if src == 'e1e1':
        fout_script.write('#cuts information \n')
        fout_script.write('%-15s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s\n'%('#processname','raw','N_mu','Mrecoil','mmdie','pt','#phi','visible','E/P','Pz'))
    fout_script.write('%-15s,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d\n'%(src,event[0],event[1],event[2],event[3],event[4],event[5],event[6],event[7],event[8]))
    fout_script.close()
    sys.stdout.write('Outputname %s \n'  % out_putname)
    os.chmod(out_putname, 0744)


#qqH_inv
def write_qq_after_cut(inputfile,event,scale):
    src = inputfile.split('/')[4]
    if re.search('_',src) != None:
        nm1=src.split('_')[0]
        nm2=src.split('_')[1]
        fourf_qq_bkg(src,nm1,nm2,event,scale)
    else:
        twof_qq_bkg(src,event,scale)

def fourf_qq_bkg(src,nm1,nm2,event,scale):
    for i in range(0,9):
        event[i]=event[i]*scale
    cwd = os.getcwd()
    out_putname = cwd + '/table/qqH/bin.txt'
    fout_script = open(out_putname,'a')
#	fout_script.write('scale=%f \n'%scale)
    fout_script.write(' \\begin{table}[hbtp] \n')
    fout_script.write(' \caption{$e^{+}e^{-}\\to %s\_%s $ cuts information ' % (nm1,nm2))
    fout_script.write('(Assume BR($H\\rightarrow inv.)$=50\\%)} \n')
    fout_script.write(' \label{tab:%s%s cut} \n' % (nm1,nm2))
    fout_script.write(' \small \n')
    fout_script.write(' \\begin{center} \n')
    fout_script.write(' \\renewcommand{\\arraystretch}{1.2} \n')
    fout_script.write(' \\begin{tabular}{ccc} \n')
    fout_script.write(' \hline \n')
    fout_script.write(' \hline \n')
    fout_script.write(' & The number of %s\_%s & Effectiveness \\\ \hline \n'  % (nm1,nm2))
    fout_script.write('Total generate & %d & %.3f \%% \\\ \n' %(event[0],(event[0]/event[0])*100))
    fout_script.write('$N_{jet}=2$ & %d  & %.3f \%% \\\ \n' %(event[1],(event[1]/event[0])*100))
    fout_script.write('$100GeV<M_{recolil}^{dijet}<140GeV$& %d & %.3f \%% \\\ \n' %(event[2],(event[2]/event[0])*100))
    fout_script.write('$30GeV<P_{t}^{dijet}<60GeV$& %d & %.3f \%% \\\ \n'  %(event[3],(event[3]/event[0])*100))
    fout_script.write('$20GeV<P_{dijet}<58GeV$& %d & %.3f \%% \\\ \n'  %(event[4],(event[4]/event[0])*100))
    fout_script.write('$85GeV<M_{dijet}<102GeV$ & %d & %.3f \%% \\\ \n' %(event[5],(event[5]/event[0])*100))
    fout_script.write('98GeV$<$Energy of dijet$<$115GeV  & %d & %.3f \%% \\\ \n'  %(event[6],(event[6]/event[0])*100))
    fout_script.write('$\Delta\phi_{dijet}<175$\degree & %d & %.3f \%% \\\ \n'  %(event[7],(event[7]/event[0])*100))
    fout_script.write('$\Delta\phi_{dijet}<175$\degree & %d & %.3f \%% \\\ \n'  %(event[8],(event[8]/event[0])*100))
    fout_script.write(' \hline \n')
    fout_script.write(' \hline \n')
    fout_script.write(' \end{tabular} \n')
    fout_script.write(' \end{center} \n')
    fout_script.write(' \end{table} \n')
    fout_script.write('  \n')
    fout_script.write('  \n')
    fout_script.write('  \n')
    fout_script.close()
    sys.stdout.write('Outputname %s \n'  % out_putname)
    os.chmod(out_putname, 0744)

def twof_qq_bkg(src,event,scale):
    for i in range(0,9):
        event[i]=event[i]*scale
    cwd = os.getcwd()
    out_putname = cwd + '/table/qqH/bin.txt' 
    fout_script = open(out_putname,'a')
#	fout_script.write('scale=%f \n'%scale)
    fout_script.write(' \\begin{table}[hbtp] \n')
    fout_script.write(' \caption{$e^{+}e^{-}\\to %s  $ cuts information ' % src)
    fout_script.write('(Assume BR($H\\rightarrow inv.)$=50\\%)} \n')
    fout_script.write(' \label{tab:%s cut} \n'% src)
    fout_script.write(' \small \n')
    fout_script.write(' \\begin{center} \n')
    fout_script.write(' \\renewcommand{\\arraystretch}{1.2}\n')
    fout_script.write(' \\begin{tabular}{ccc} \n')
    fout_script.write(' \hline \n')
    fout_script.write(' \hline \n')
    fout_script.write(' & The number of %s & Effectiveness \\\ \hline \n' % src)
    fout_script.write('Total generate & %d & %.3f \%% \\\ \n' %(event[0],(event[0]/event[0])*100))
    fout_script.write('$N_{jet}=2$ & %d  & %.3f \%% \\\ \n' %(event[1],(event[1]/event[0])*100))
    fout_script.write('$100GeV<M_{recolil}^{dijet}<140GeV$& %d & %.3f \%% \\\ \n' %(event[2],(event[2]/event[0])*100))
    fout_script.write('$30GeV<P_{t}^{dijet}<60GeV$& %d & %.3f \%% \\\ \n'  %(event[3],(event[3]/event[0])*100))
    fout_script.write('$20GeV<P_{dijet}<58GeV$ & %d & %.3f \%% \\\ \n'  %(event[4],(event[4]/event[0])*100))
    fout_script.write('$85GeV<M_{dijet}<102GeV$& %d & %.3f \%% \\\ \n' %(event[5],(event[5]/event[0])*100))
    fout_script.write('$98GeV< Energy of dijet <115GeV$ & %d & %.3f \%% \\\ \n'  %(event[6],(event[6]/event[0])*100))
    fout_script.write('$\Delta\phi_{dijet}<175$\degree & %d & %.3f \%% \\\ \n'  %(event[7],(event[7]/event[0])*100))
    fout_script.write('$\Delta\phi_{dijet}<175$\degree& %d & %.3f \%% \\\ \n'  %(event[8],(event[8]/event[0])*100))
    fout_script.write(' \hline \n')
    fout_script.write(' \hline \n')
    fout_script.write(' \end{tabular} \n')
    fout_script.write(' \end{center} \n')
    fout_script.write(' \end{table} \n')
    fout_script.write('  \n')
    fout_script.write('  \n') 
    fout_script.write('  \n')
    fout_script.close() 
    sys.stdout.write('Outputname %s \n'  % out_putname) 
    os.chmod(out_putname, 0744)

def record_qq_information(inputfile,event):
    src = inputfile.split('/')[4]
    cwd = os.getcwd()
    out_putname = cwd + '/' + 'table/qqH/' + 'out_list.txt'
    fout_script = open(out_putname,'a')
    if src == 'e1e1':
        fout_script.write('#cuts information \n')
        fout_script.write('%-15s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s\n'%('#processname','raw','N_mu','Mrecoil','mmdie','pt','#phi','visible','E/P','Pz'))
    fout_script.write('%-15s,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d\n'%(src,event[0],event[1],event[2],event[3],event[4],event[5],event[6],event[7],event[8]))
    fout_script.close()
    sys.stdout.write('Outputname %s \n'  % out_putname)
    os.chmod(out_putname, 0744)
if __name__ == '__main__':
    main()
