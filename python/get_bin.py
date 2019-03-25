import sys
import os
from string import Template
#Get all channels detail value echo step
def main(): 
    args = sys.argv[1]
    table = open(args , 'r' )
    processname = args.split('/')[1]
    event = [0]*10
    events = [0]*10
    n=0
    m=0
    k=[]
    g=[] 
    nm=[]
    for s_row in table :
        if not s_row.startswith('#'):
            l = [x.strip() for x in s_row.split(',')]
            d = l[0]
            k.append(l[9])
            g.append(l[1])
            nm.append(l[0])
#            if d == 'e1e1' or d == 'e2e2' or d == 'e3e3' or d == 'qq' :
#                event,n = two_f_bkg(l,event,n)
#            elif d == 'e2E2h_invi' :
#                continue
#            else:
#                events,m = four_f_bkg(l,events,m)
    detail_inf(k,g,nm,processname)           
def two_f_bkg(l,event,n):
    if n < 3:
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
        fout_script.write('$N_{\mu^+}=1,N_{\mu^-}=1,N_{charged}<3$ & %d  & %.3f \%% \\\ \n' %(event[1],(event[1]/event[0])*100))
        fout_script.write('$N_{\gamma}=0$ & %d & %.3f \%% \\\ \n' %(event[2],event[2]/event[0]*100))
        fout_script.write('$25GeV<P_{t}^{\mu^+\mu^-}<70GeV$ & %d & %.3f \%% \\\ \n'  %(event[3],(event[3]/event[0])*100))
        fout_script.write('$\\theta_{\mu^+\mu^-}<145$ & %d & %.3f \%% \\\ \n'  %(event[4],(event[4]/event[0])*100))
        fout_script.write('$100GeV<E_{visible}<110GeV$& %d & %.3f \%% \\\ \n' %(event[5],(event[5]/event[0])*100))
        fout_script.write('$86GeV<M_{\mu^+\mu^-}<97GeV$& %d & %.3f \%% \\\ \n'  %(event[6],(event[6]/event[0])*100))
        fout_script.write('$120GeV<M_{recoil}<140GeV$ & %d & %.3f \%% \\\ \n'  %(event[7],(event[7]/event[0])*100))
        fout_script.write('$ReM_{visdtau}<5$& %d & %.3f \%% \\\ \n'  %(event[8],(event[8]/event[0])*100))
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
    if m < 40:
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
        fout_script.write('$N_{\mu^+}=1,N_{\mu^-}=1,N_{charged}<3$ & %d  & %.3f \%% \\\ \n' %(event[1],(event[1]/event[0])*100))
        fout_script.write('$N_{\gamma}=0$ & %d & %.3f \%% \\\ \n' %(event[2],event[2]/event[0]*100))
        fout_script.write('$25GeV<P_{t}^{\mu^+\mu^-}<70GeV & %d & %.3f \%% \\\ \n'  %(event[3],(event[3]/event[0])*100))
        fout_script.write('$\\theta_{\mu^+\mu^-}<145$ & %d & %.3f \%% \\\ \n'  %(event[4],(event[4]/event[0])*100))
        fout_script.write(' $100GeV<E_{visible}<110GeV$& %d & %.3f \%% \\\ \n' %(event[5],(event[5]/event[0])*100))
        fout_script.write(' $86GeV<M_{\mu^+\mu^-}<97GeV$ & %d & %.3f \%% \\\ \n'  %(event[6],(event[6]/event[0])*100))
        fout_script.write('$120GeV<M_{recoil}<140GeV$ & %d & %.3f \%% \\\ \n'  %(event[7],(event[7]/event[0])*100))
        fout_script.write('$ReM_{visdtau}<5$ & %d & %.3f \%% \\\ \n'  %(event[8],(event[8]/event[0])*100))
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

def detail_inf(k,g,nm,processname):
    lenlist=len(nm)
    cwd = os.getcwd()
    src = 'detailinf'
    if processname == "mumuH":
        out_putname = cwd + '/table/mumuH/tfbin.txt' 
    elif processname == "eeH":
        out_putname = cwd + '/table/eeH/tfbin.txt'
    elif processname == "qqH":
        out_putname = cwd + '/table/qqH/tfbin.txt'
    else:
        print "This is wrong,please check this"
        sys.exit() 
    fout_script = open(out_putname,'a')
    fout_script.write(' \\begin{table}[hbtp] \n')
    fout_script.write(' \caption{The number of all channels after cuts ')
    fout_script.write('(Assume BR($H\\rightarrow inv.)$=50\\%)} \n')
    fout_script.write(' \label{tab:%s cut} \n'% src)
    fout_script.write('  \\footnotesize \n')
    fout_script.write(' \\begin{center} \n')
    fout_script.write(' \\renewcommand{\\arraystretch}{1.2}\n')
    fout_script.write(' \\begin{tabular}{cccccccccccccccccccccc} \n')
    fout_script.write(' \hline \n')
    fout_script.write(' \hline \n')

    for i in xrange(0,lenlist,6):
        print i
        fout_script.write('process&')
        for j in xrange(i,i+6):
            if j < lenlist:
                fout_script.write('%s'%nm[j])
                if j < i+5:
                    fout_script.write('&')	
        fout_script.write('\\\  \n')

        fout_script.write('event generate&')
        for j in xrange(i,i+6):
            if j < lenlist:
                fout_script.write('%s'%g[j])
                if j <i+5:
                    fout_script.write('&')	
        fout_script.write('\\\  \n')

        fout_script.write('after cuts&')
        for j in xrange(i,i+6):
            if j < lenlist:
                fout_script.write('%s'%k[j])
                if j < i+5:
                    fout_script.write('&')
        fout_script.write('\\\ \hline  \n')	
    fout_script.write('\\\ \hline \n')
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