#!/usr/bin/env python 
import sys,os,copy,re
import ROOT
from array import array 

def main():
    args = sys.argv[1]
    for root, dirs, files in os.walk(args):   
        for f in files:        
            event = []
            input_path = os.path.join(root,f)
#        print input_path
        event = get_bin_value(input_path)
        decay_name = args.split('/')[-1]
        print decay_name
        scale = get_decay_scale(decay_name,event)
        write_after_cut(input_path,event,scale)
        recode_information(input_path,event)

def get_bin_value(args):  
    sample = ROOT.TFile(args)
    h = sample.Get('hevtflw')
    event = []
    for i in range(1,10):
        event.append(h.GetBinContent(i))   
    return event

def get_decay_scale(decay_name,event):

    IntLum=5000
    event_gen=event[0]
    if decay_name=="hist":
        ffH_cross=203.66
        br_Hinv=0.5
        weight=IntLum*ffH_cross*br_Hinv/event_gen
    elif decay_name=="e1e1":
        e1e1_cross=24770.90
        weight=IntLum*e1e1_cross/event_gen
    elif decay_name=="e2e2":
        e2e2_cross=5332.71
        weight=IntLum*e2e2_cross/event_gen
        print event_gen
    elif decay_name=="e3e3":
        e3e3_cross=4752.89
        weight=IntLum*e3e3_cross/event_gen
    elif decay_name=="qq":
        qq_cross=54106.86
        weight=IntLum*qq_cross/event_gen
    elif decay_name=="sw_l":
        sw_l0mu=436.70
        sw_l0tau=435.93
        sw_l_cross=sw_l0mu+sw_l0tau
        weight=IntLum*sw_l_cross/event_gen
    elif decay_name=="sw_sl":
        sw_sl_cross=2612.62
        weight=IntLum*sw_sl_cross/event_gen
    elif decay_name=="sze_l":
        sze_l0e=78.49
        sze_l0mu=845.81
        sze_l0nunu=28.94
        sze_l0tau=147.28
        sze_l_cross=sze_l0e+sze_l0mu+sze_l0nunu+sze_l0tau
        weight=IntLum*sze_l_cross/event_gen
    elif decay_name=="sze_sl":
        sze_sl0dd=125.83
        sze_sl0uu=190.21
        sze_sl_cross=sze_sl0dd+sze_sl0uu
        weight=IntLum*sze_sl_cross/event_gen
    elif decay_name=="szeorsw_l":		
        szeorsw_l_cross=249.48
        weight=IntLum*szeorsw_l_cross/event_gen
    elif decay_name=="sznu_l":
        sznu_l0mumu=43.42
        sznu_l0tautau=14.57		
        sznu_l_cross=sznu_l0tautau+sznu_l0mumu
        weight=IntLum*sznu_l_cross/event_gen
    elif decay_name=="sznu_sl":
        sznu_sl0nu_down=90.03		
        sznu_sl0nu_up=55.59
        sznu_sl_cross=sznu_sl0nu_down+sznu_sl0nu_up
        weight=IntLum*sznu_sl_cross/event_gen	
    elif decay_name=="ww_h":
        ww_h0ccbs=5.89
        ww_h0ccds=170.18
        ww_h0cuxx=3478.89
        ww_h0uubd=0.05
        ww_h0uusd=170.45		
        ww_h_cross=ww_h0ccbs+ww_h0ccds+ww_h0cuxx+ww_h0uubd+ww_h0uusd
        weight=IntLum*ww_h_cross/event_gen
    elif decay_name=="ww_l0ll":		
        ww_l0ll_cross=403.66
        weight=IntLum*ww_l0ll_cross/event_gen
    elif decay_name=="ww_sl":		
        ww_sl0muq=2423.43
        ww_sl0tauq=2423.56
        ww_sl_cross=ww_sl0muq+ww_sl0tauq
        weight=IntLum*ww_sl_cross/event_gen
    elif decay_name=="zz_h":
        zz_h0cc_nots=98.97
        zz_h0dtdt=233.46
        zz_h0utut=85.68
        zz_h0uu_notd=98.56		
        zz_h_cross=zz_h0cc_nots+zz_h0dtdt+zz_h0utut+zz_h0uu_notd
        weight=IntLum*zz_h_cross/event_gen
    elif decay_name=="zz_l":
        zz_l04mu=15.56
        zz_l04tau=4.61
        zz_l0mumu=19.38
        zz_l0taumu=18.65
        zz_l0tautau=9.61		
        zz_l_cross=zz_l04mu+zz_l04tau+zz_l0mumu+zz_l0taumu+zz_l0tautau
        weight=IntLum*zz_l_cross/event_gen
    elif decay_name=="zz_sl":
        zz_sl0mu_down=136.14
        zz_sl0mu_up=87.39
        zz_sl0nu_down=139.71
        zz_sl0nu_up=84.38
        zz_sl0tau_down=67.31
        zz_sl0tau_up=41.56		
        zz_sl_cross=zz_sl0mu_down+zz_sl0mu_up+zz_sl0nu_down+zz_sl0nu_up+zz_sl0tau_down+zz_sl0tau_up
        weight=IntLum*zz_sl_cross/event_gen
    elif decay_name=="zzorww_h":
        zzorww_h0cscs=1607.55
        zzorww_h0udud=1610.32		
        zzorww_h_cross=zzorww_h0cscs+zzorww_h0udud
        weight=IntLum*zzorww_h_cross/event_gen
    elif decay_name=="zzorww_l":	
        zzorww_l0mumu=221.10
        zzorww_l0tautau=211.18
        zzorww_l_cross=zzorww_l0mumu+zzorww_l0tautau
        weight=IntLum*zzorww_l_cross/event_gen
    else:
        print "Sample name misses, please check that!"
        sys.exit()
    print weight
    return weight
    
def write_after_cut(args,event,scale):
    src = args.split('/')[3]
    if re.search('_',src) != None:
        nm1=src.split('_')[0]
        nm2=src.split('_')[1]
        fourf_bkg(src,nm1,nm2,event,scale)
    else:
        twof_bkg(src,event,scale)
def fourf_bkg(src,nm1,nm2,event,scale):
    for i in range(0,9):
        event[i]=event[i]*scale
    cwd = os.getcwd()
    out_putname = cwd + '/table/bin.txt'
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
    fout_script.write('$N_{\mu^+}\geq1$,$N_{\mu^-}\geq1$,$N_{charged}<3$ & %d  & %.3f \%% \\\ \n' %(event[1],(event[1]/event[0])*100))
    fout_script.write('$N_{\gamma}\leq1$ & %d & %.3f \%% \\\ \n' %(event[2],(event[2]/event[0])*100))
    fout_script.write('$10GeV<P_{t}^{\mu^+\mu^-}<70GeV$ & %d & %.3f \%% \\\ \n'  %(event[3],(event[3]/event[0])*100))
    fout_script.write('$|P_{z}^{\mu^+\mu^-}|<50GeV$ & %d & %.3f \%% \\\ \n'  %(event[4],(event[4]/event[0])*100))
    fout_script.write('$|cos\\theta_{\mu^+\mu^-}|<0.8$ & %d & %.3f \%% \\\ \n' %(event[5],(event[5]/event[0])*100))
    fout_script.write('$90GeV<E_{visible}<110GeV$  & %d & %.3f \%% \\\ \n'  %(event[6],(event[6]/event[0])*100))
    fout_script.write('$83GeV<M_{\mu^+\mu^-}<97GeV$ & %d & %.3f \%% \\\ \n'  %(event[7],(event[7]/event[0])*100))
    fout_script.write('$120GeV<M_{recoil}<150GeV$ & %d & %.3f \%% \\\ \n'  %(event[8],(event[8]/event[0])*100))
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

def twof_bkg(src,event,scale):
    for i in range(0,9):
        event[i]=event[i]*scale
    cwd = os.getcwd()
    out_putname = cwd + '/table/bin.txt' 
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
    fout_script.write('$N_{\mu^+}\geq1$,$N_{\mu^-}\geq1$,$N_{charged}<3$ & %d  & %.3f \%% \\\ \n' %(event[1],(event[1]/event[0])*100))
    fout_script.write('$N_{\gamma}\leq1$ & %d & %.3f \%% \\\ \n' %(event[2],(event[2]/event[0])*100))
    fout_script.write('$10GeV<P_{t}^{\mu^+\mu^-}<70GeV$ & %d & %.3f \%% \\\ \n'  %(event[3],(event[3]/event[0])*100))
    fout_script.write('$|P_{z}^{\mu^+\mu^-}|<50GeV$ & %d & %.3f \%% \\\ \n'  %(event[4],(event[4]/event[0])*100))
    fout_script.write('$|cos\\theta_{\mu^+\mu^-}|<0.8$ & %d & %.3f \%% \\\ \n' %(event[5],(event[5]/event[0])*100))
    fout_script.write('$90GeV<E_{visible}<110GeV$  & %d & %.3f \%% \\\ \n'  %(event[6],(event[6]/event[0])*100))
    fout_script.write('$83GeV<M_{\mu^+\mu^-}<97GeV$ & %d & %.3f \%% \\\ \n'  %(event[7],(event[7]/event[0])*100))
    fout_script.write('$120GeV<M_{recoil}<150GeV$ & %d & %.3f \%% \\\ \n'  %(event[8],(event[8]/event[0])*100))
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

def recode_information(args,event):
    src = args.split('/')[3]
    cwd = os.getcwd()
    out_putname = cwd + '/' + 'table/' + 'out_list.txt'
    fout_script = open(out_putname,'a')
    if src == 'e1e1':
        fout_script.write('#cuts information \n')
        fout_script.write('%-12s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s,%-12s\n'%('#processname','raw','N_mu','N_photo','Pt','Pz','costheta','visible','Mmumu','Mrecoil'))
    fout_script.write('%-12s,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d,%-12d\n'%(src,event[0],event[1],event[2],event[3],event[4],event[5],event[6],event[7],event[8]))
    fout_script.close()
    sys.stdout.write('Outputname %s \n'  % out_putname)
    os.chmod(out_putname, 0744)

if __name__ == '__main__':
    main()
