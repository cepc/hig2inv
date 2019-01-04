import sys
import os
from string import Template
import math
#Get all channels detail value echo step
def main(): 
    args = sys.argv[1]
    table = open(args , 'r' )
    pname =sys.argv[2]
    event = [0]*11
    events = [0]*11
    n=0
    m=0
    for i in range(0,11):
        exec 'k%d = []' %i

    for s_row in table :
        if not s_row.startswith('#'):
            l = [x.strip() for x in s_row.split(',')] 
            for i in range(0,10):
                exec 'k%d.append(l[%d])'%(i,i)
    if pname == "mumuH":
        detail_mumu_inf(k0,k1,k2,k3,k4,k5,k6,k7,k8,k9)  
    elif pname == "eeH":
        detail_ee_inf(k0,k1,k2,k3,k4,k5,k6,k7,k8,k9)
    elif pname == "qqH":
        detail_qq_inf(k0,k1,k2,k3,k4,k5,k6,k7,k8,k9)
    else:
        print "This is  wrong. Please check it" 
        sys.exit()  				        
def detail_mumu_inf(k0,k1,k2,k3,k4,k5,k6,k7,k8,k9):  
        for i in range(1,10):
            exec 'k%d= [ int(x) for x in k%d ]'%(i,i)  
        cwd = os.getcwd()
        src = 'all channel are grouped '
        out_putname = cwd + '/table/mumuH/tfbin_b.txt' 
        fout_script = open(out_putname,'a')
    #	fout_script.write('scale=%f \n'%scale)
        fout_script.write(' \\begin{table}[hbtp] \n')
        fout_script.write(' \caption{Yields for backgrounds and signals at the CEPC' )
        fout_script.write('(Assume BR($H\\rightarrow inv.)$=50\\%)} \n')
        fout_script.write(' \label{tab:%s cut} \n'% src)
        fout_script.write(' \\tiny\n')
        fout_script.write(' \\begin{center} \n')
        fout_script.write(' \\renewcommand{\\arraystretch}{1.2}\n')
        fout_script.write(' \\begin{tabular}{ccccccccccc} \n')
        fout_script.write(' \hline \n')
        fout_script.write(' \hline \n')
        fout_script.write(' Process&  %s &%s &%s &%s &%s &%s &%s &%s &%s&$\\frac{\sqrt{S+B}}{S}$ \\\ \hline \n' % (k0[0],k0[1],k0[2],k0[3],k0[4],k0[5],k0[6],k0[7],k0[8]))
        fout_script.write('Total generate & %s &%s &%s &%s &%s &%s &%s &%s&%s&   \\\ \n'% (k1[0],k1[1],k1[2],k1[3],k1[4],k1[5],k1[6],k1[7],k1[8]))
        fout_script.write('$N_{\mu^{+}}=1,N_{\mu^{-}}=1$ & %s &%s &%s &%s &%s &%s &%s &%s&%s& %.3f \%%   \\\ \n'%(k2[0],k2[1],k2[2],k2[3],k2[4],k2[5],k2[6],k2[7],k2[8],float(math.sqrt(k2[0]+k2[8])/k2[0]*100))) 
        fout_script.write('$120GeV<M_{Recoil}<150GeV$ & %s &%s &%s &%s &%s &%s &%s &%s&%s& %.3f \%%    \\\ \n' %(k3[0],k3[1],k3[2],k3[3],k3[4],k3[5],k3[6],k3[7],k3[8],float(math.sqrt(k3[0]+k3[8])/k3[0]*100)))
        fout_script.write('$85GeV<M_{\mu^{+}\mu^{-}}<97GeV$ & %s &%s &%s &%s &%s &%s &%s &%s &%s& %.3f \%%   \\\ \n' %(k4[0],k4[1],k4[2],k4[3],k4[4],k4[5],k4[6],k4[7],k4[8],float(math.sqrt(k4[0]+k4[8])/k4[0]*100)))
        fout_script.write('$12GeV<P_{t}^{\mu^{+}\mu^{-}}$ & %s &%s &%s &%s &%s &%s &%s &%s&%s& %.3f \%%    \\\ \n'  %(k5[0],k5[1],k5[2],k5[3],k5[4],k5[5],k5[6],k5[7],k5[8],float(math.sqrt(k5[0]+k5[8])/k5[0]*100)))
        fout_script.write('$\Delta\phi<175$\degree & %s &%s &%s &%s &%s &%s &%s &%s&%s& %.3f \%%    \\\ \n' %(k6[0],k6[1],k6[2],k6[3],k6[4],k6[5],k6[6],k6[7],k6[8],float(math.sqrt(k6[0]+k6[8])/k6[0]*100)))
        fout_script.write('$|P_{t}^{\mu^{+}\mu^{-}}|<50GeV$ & %s &%s &%s &%s &%s &%s &%s &%s &%s& %.3f \%%   \\\ \n'  %(k7[0],k7[1],k7[2],k7[3],k7[4],k7[5],k7[6],k7[7],k7[8],float(math.sqrt(k7[0]+k7[8])/k7[0]*100)))
        fout_script.write('$102GeV<Visible Energy<107GeV$ & %s &%s &%s &%s &%s &%s &%s &%s&%s& %.3f \%%     \\\ \n' %(k8[0],k8[1],k8[2],k8[3],k8[4],k8[5],k8[6],k8[7],k8[8],float(math.sqrt(k8[0]+k8[8])/k8[0]*100)))
        fout_script.write('$\\frac{E}{P}<2.4$ & %s &%s &%s &%s &%s &%s &%s &%s  &%s & %.3f \%% \\\ \n'  %(k9[0],k9[1],k9[2],k9[3],k9[4],k9[5],k9[6],k9[7],k9[8],float(math.sqrt(k9[0]+k9[8])/k9[0]*100)))
#        fout_script.write('$120GeV<M_{recoil}<140GeV$ & %s &%s &%s &%s &%s &%s &%s &%s  &%s  & %.3f \%%\\\ \n'  %(k10[0],k10[1],k10[2],k10[3],k10[4],k10[5],k10[6],k10[7],k10[8],float(math.sqrt(k10[0]+k10[8])/k10[0]*100)))
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

def detail_ee_inf(k0,k1,k2,k3,k4,k5,k6,k7,k8,k9):  
        for i in range(1,10):
            exec 'k%d= [ int(x) for x in k%d ]'%(i,i)  
        cwd = os.getcwd()
        src = 'all channel are grouped '
        out_putname = cwd + '/table/eeH/tfbin_b.txt' 
        fout_script = open(out_putname,'a')
    #	fout_script.write('scale=%f \n'%scale)
        fout_script.write(' \\begin{table}[hbtp] \n')
        fout_script.write(' \caption{Yields for backgrounds and signals at the CEPC' )
        fout_script.write('(Assume BR($H\\rightarrow inv.)$=50\\%)} \n')
        fout_script.write(' \label{tab:%s cut} \n'% src)
        fout_script.write('  \\tiny \n')
        fout_script.write(' \\begin{center} \n')
        fout_script.write(' \\renewcommand{\\arraystretch}{1.2}\n')
        fout_script.write(' \\begin{tabular}{ccccccccccc} \n') 
        fout_script.write(' \hline \n')
        fout_script.write(' \hline \n')
        fout_script.write(' Process&  %s &%s &%s &%s &%s &%s &%s &%s &%s&$\\frac{\sqrt{S+B}}{S}$ \\\ \hline \n' % (k0[0],k0[1],k0[2],k0[3],k0[4],k0[5],k0[6],k0[7],k0[8]))
        fout_script.write('Total generate & %s &%s &%s &%s &%s &%s &%s &%s&%s&   \\\ \n'% (k1[0],k1[1],k1[2],k1[3],k1[4],k1[5],k1[6],k1[7],k1[8]))
        fout_script.write('$N_{e^{+}}==1,N_{e^{-}}==1$ & %s &%s &%s &%s &%s &%s &%s &%s&%s& %.3f \%%   \\\ \n'%(k2[0],k2[1],k2[2],k2[3],k2[4],k2[5],k2[6],k2[7],k2[8],float(math.sqrt(k2[0]+k2[8])/k2[0]*100))) 
        fout_script.write('$120GeV<M_{recoil}<160GeV$ & %s &%s &%s &%s &%s &%s &%s &%s&%s& %.3f \%%    \\\ \n' %(k3[0],k3[1],k3[2],k3[3],k3[4],k3[5],k3[6],k3[7],k3[8],float(math.sqrt(k3[0]+k3[8])/k3[0]*100)))
        fout_script.write('$71GeV<M_{e^{+}e^{-}}<99GeV$ & %s &%s &%s &%s &%s &%s &%s &%s &%s& %.3f \%%   \\\ \n' %(k4[0],k4[1],k4[2],k4[3],k4[4],k4[5],k4[6],k4[7],k4[8],float(math.sqrt(k4[0]+k4[8])/k4[0]*100)))
        fout_script.write('$12GeV<P_{t}^{e^{+}e^{-}}<55GeV$ & %s &%s &%s &%s &%s &%s &%s &%s&%s& %.3f \%%    \\\ \n'  %(k5[0],k5[1],k5[2],k5[3],k5[4],k5[5],k5[6],k5[7],k5[8],float(math.sqrt(k5[0]+k5[8])/k5[0]*100)))
        fout_script.write('$\Delta\phi<176$\degree & %s &%s &%s &%s &%s &%s &%s &%s&%s& %.3f \%%    \\\ \n' %(k6[0],k6[1],k6[2],k6[3],k6[4],k6[5],k6[6],k6[7],k6[8],float(math.sqrt(k6[0]+k6[8])/k6[0]*100)))
        fout_script.write('$103GeV<Visible Energy<120GeV$  & %s &%s &%s &%s &%s &%s &%s &%s &%s& %.3f \%%   \\\ \n'  %(k7[0],k7[1],k7[2],k7[3],k7[4],k7[5],k7[6],k7[7],k7[8],float(math.sqrt(k7[0]+k7[8])/k7[0]*100)))
        fout_script.write('$1.8<\\frac{E_{e^+e^-}}{P_{e^+e^-}}<2.4$ & %s &%s &%s &%s &%s &%s &%s &%s&%s& %.3f \%%     \\\ \n' %(k8[0],k8[1],k8[2],k8[3],k8[4],k8[5],k8[6],k8[7],k8[8],float(math.sqrt(k8[0]+k8[8])/k8[0]*100)))
        fout_script.write('$|P_{z}^{e^{+}e^{-}}|<55GeV$ & %s &%s &%s &%s &%s &%s &%s &%s  &%s& %.3f \%%  \\\ \n'  %(k9[0],k9[1],k9[2],k9[3],k9[4],k9[5],k9[6],k9[7],k9[8],float(math.sqrt(k9[0]+k9[8])/k9[0]*100)))
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
def detail_qq_inf(k0,k1,k2,k3,k4,k5,k6,k7,k8,k9):  
        for i in range(1,10):
            exec 'k%d= [ int(x) for x in k%d ]'%(i,i)  
        cwd = os.getcwd()
        src = 'all channel are grouped '
        out_putname = cwd + '/table/qqH/tfbin_b.txt' 
        fout_script = open(out_putname,'a')
    #	fout_script.write('scale=%f \n'%scale)
        fout_script.write(' \\begin{table}[hbtp] \n')
        fout_script.write(' \caption{Yields for backgrounds and signals at the CEPC' )
        fout_script.write('(Assume BR($H\\rightarrow inv.)$=50\\%)} \n')
        fout_script.write(' \label{tab:%s cut} \n'% src)
        fout_script.write('  \\tiny \n')
        fout_script.write(' \\begin{center} \n')
        fout_script.write(' \\renewcommand{\\arraystretch}{1.2}\n')
        fout_script.write(' \\begin{tabular}{ccccccccccc} \n') 
        fout_script.write(' \hline \n')
        fout_script.write(' \hline \n')
        fout_script.write(' Process&  %s &%s &%s &%s &%s &%s &%s &%s &%s&$\\frac{\sqrt{S+B}}{S}$ \\\ \hline \n' % (k0[0],k0[1],k0[2],k0[3],k0[4],k0[5],k0[6],k0[7],k0[8]))
        fout_script.write('Total generate & %s &%s &%s &%s &%s &%s &%s &%s&%s&   \\\ \n'% (k1[0],k1[1],k1[2],k1[3],k1[4],k1[5],k1[6],k1[7],k1[8]))
        fout_script.write('$N_{jet}=2$ & %s &%s &%s &%s &%s &%s &%s &%s&%s& %.3f \%%   \\\ \n'%(k2[0],k2[1],k2[2],k2[3],k2[4],k2[5],k2[6],k2[7],k2[8],float(math.sqrt(k2[0]+k2[8])/k2[0]*100))) 
        fout_script.write('$100GeV<M_{recolil}^{dijet}<140GeV$ & %s &%s &%s &%s &%s &%s &%s &%s&%s& %.3f \%%    \\\ \n' %(k3[0],k3[1],k3[2],k3[3],k3[4],k3[5],k3[6],k3[7],k3[8],float(math.sqrt(k3[0]+k3[8])/k3[0]*100)))
        fout_script.write('$30GeV<P_{t}^{dijet}<60GeV$ & %s &%s &%s &%s &%s &%s &%s &%s &%s& %.3f \%%   \\\ \n' %(k4[0],k4[1],k4[2],k4[3],k4[4],k4[5],k4[6],k4[7],k4[8],float(math.sqrt(k4[0]+k4[8])/k4[0]*100)))
        fout_script.write('$20GeV<P_{dijet}<58GeV$ & %s &%s &%s &%s &%s &%s &%s &%s&%s& %.3f \%%    \\\ \n'  %(k5[0],k5[1],k5[2],k5[3],k5[4],k5[5],k5[6],k5[7],k5[8],float(math.sqrt(k5[0]+k5[8])/k5[0]*100)))
        fout_script.write('$85GeV<M_{dijet}<102GeV $& %s &%s &%s &%s &%s &%s &%s &%s&%s& %.3f \%%    \\\ \n' %(k6[0],k6[1],k6[2],k6[3],k6[4],k6[5],k6[6],k6[7],k6[8],float(math.sqrt(k6[0]+k6[8])/k6[0]*100)))
        fout_script.write('98GeV$<$Energy of dijet$<$115GeV  & %s &%s &%s &%s &%s &%s &%s &%s &%s& %.3f \%%   \\\ \n'  %(k7[0],k7[1],k7[2],k7[3],k7[4],k7[5],k7[6],k7[7],k7[8],float(math.sqrt(k7[0]+k7[8])/k7[0]*100)))
        fout_script.write('$\Delta\phi_{dijet}<175$\degree & %s &%s &%s &%s &%s &%s &%s &%s&%s& %.3f \%%     \\\ \n' %(k8[0],k8[1],k8[2],k8[3],k8[4],k8[5],k8[6],k8[7],k8[8],float(math.sqrt(k8[0]+k8[8])/k8[0]*100)))
#        fout_script.write('$$ & %s &%s &%s &%s &%s &%s &%s &%s  &%s& %.3f \%%  \\\ \n'  %(k9[0],k9[1],k9[2],k9[3],k9[4],k9[5],k9[6],k9[7],k9[8],float(math.sqrt(k9[0]+k9[8])/k9[0]*100)))
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