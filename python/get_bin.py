import sys
import os
from string import Template

def main(): 
    args = sys.argv[1]
    table = open(args , 'r' )
    event = [0]*9
    events = [0]*9
    n=0
    m=0
    k=[]
    g=[]
    for s_row in table :
        if not s_row.startswith('#'):
            l = [x.strip() for x in s_row.split(',')]
            d = l[0]
            k.append(l[9])
            g.append(l[1])
            if d == 'e1e1' or d == 'e2e2' or d == 'e3e3' or d == 'qq':
                event,n = two_f_bkg(l,event,n)
            else:
                events,m = four_f_bkg(l,events,m)
    detail_inf(k,g)
def two_f_bkg(l,event,n):
    if n <3:
        for i in xrange(1,10):
            event[i-1] = event[i-1] + int(l[i])
        n+=1
    else:
        for i in xrange(1,10):
            event[i-1]=event[i-1] + int(l[i])  
            event[i-1]=float(event[i-1])           
        cwd = os.getcwd()
        src = '2fbackground'
        out_putname = cwd + '/table/tfbin.txt' 
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
        fout_script.write('$N_{\gamma}\leq1$ & %d & %.3f \%% \\\ \n' %(event[2],event[2]/event[0]))
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
    return event,n

def four_f_bkg(l,event,m):
    if m <14:
        for i in xrange(1,10):
            event[i-1] = event[i-1] + int(l[i])
        m+=1
    else:
        for i in xrange(1,10):
            event[i-1]=event[i-1] + int(l[i]) 
            event[i-1]=float(event[i-1])
        cwd = os.getcwd()
        src = '4fbackground'
        out_putname = cwd + '/table/tfbin.txt' 
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
        fout_script.write('$N_{\gamma}\leq1$ & %d & %.3f \%% \\\ \n' %(event[2],event[2]/event[0]))
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
    return event,m
def detail_inf(k,g):
    for i in range(0,20): 
        print g[i]
    cwd = os.getcwd()
    src = 'detailinf'
    out_putname = cwd + '/table/tfbin.txt' 
    fout_script = open(out_putname,'a')
    fout_script.write(' \\begin{table}[hbtp] \n')
    fout_script.write(' \caption{The number of all channels after cuts ')
    fout_script.write('(Assume BR($H\\rightarrow inv.)$=50\\%)} \n')
    fout_script.write(' \label{tab:%s cut} \n'% src)
    fout_script.write(' \small \n')
    fout_script.write(' \\begin{center} \n')
    fout_script.write(' \\renewcommand{\\arraystretch}{1.2}\n')
    fout_script.write(' \\begin{tabular}{cccccccccccccccccccccc} \n')
    fout_script.write(' \hline \n')
    fout_script.write(' \hline \n')
    fout_script.write('process&e1e1&e2e2&e3e3&qq&sw\_l&sw\_sl&sze\_l&szeorsw\_l&sze\_sl&sznu\_l \\\ \hline \n')
    fout_script.write('event generate& %s & %s & %s & %s & %s & %s & %s & %s & %s & %s  \\\ \hline  \n' %(g[0],g[1],g[2],g[3],g[4],g[5],g[6],g[7],g[8],g[9]))
    fout_script.write('after cuts& %s & %s & %s & %s & %s & %s & %s & %s & %s & %s  \\\ \hline \hline \n' %(k[0],k[1],k[2],k[3],k[4],k[5],k[6],k[7],k[8],k[9]))
    fout_script.write('process&sznu\_sl&ww\_h&ww\_l0ll&ww\_sl&zz\_h&zz\_l&zzorww\_h&zzorww\_l&zz\_sl&signal \\\ \hline \n')
    fout_script.write('event generate& %s & %s & %s & %s & %s & %s & %s & %s & %s & %s  \\\ \hline \n' %(g[10],g[11],g[12],g[13],g[14],g[15],g[16],g[17],g[18],g[19]))
    fout_script.write('after cuts& %s & %s & %s & %s & %s & %s & %s & %s & %s & %s \\\ \n' % (k[10],k[11],k[12],k[13],k[14],k[15],k[16],k[17],k[18],k[19]))
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
if __name__ == '__main__':
    main()