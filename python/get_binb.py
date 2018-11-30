import sys
import os
from string import Template
#Get all channels detail value echo step
def main(): 
    args = sys.argv[1]
    table = open(args , 'r' )
    event = [0]*9
    events = [0]*9
    n=0
    m=0
    for i in range(0,10):
        exec 'k%d = []' %i

    for s_row in table :
        if not s_row.startswith('#'):
            l = [x.strip() for x in s_row.split(',')] 
            for i in range(0,10):
                exec 'k%d.append(l[%d])'%(i,i)
    detail_inf(k0,k1,k2,k3,k4,k5,k6,k7,k8,k9)           
def detail_inf(k0,k1,k2,k3,k4,k5,k6,k7,k8,k9):         
        cwd = os.getcwd()
        src = 'all channel are grouped '
        out_putname = cwd + '/table/tfbin_b.txt' 
        fout_script = open(out_putname,'a')
    #	fout_script.write('scale=%f \n'%scale)
        fout_script.write(' \\begin{table}[hbtp] \n')
        fout_script.write(' \caption{Yields for backgrounds and signals at the CEPC' )
        fout_script.write('(Assume BR($H\\rightarrow inv.)$=50\\%)} \n')
        fout_script.write(' \label{tab:%s cut} \n'% src)
        fout_script.write(' \scriptsize \n')
        fout_script.write(' \\begin{center} \n')
        fout_script.write(' \\renewcommand{\\arraystretch}{1.2}\n')
        fout_script.write(' \\begin{tabular}{cccccccccc} \n')
        fout_script.write(' \hline \n')
        fout_script.write(' \hline \n')
        fout_script.write(' Process&  %s &%s &%s &%s &%s &%s &%s &%s &%s  \\\ \hline \n' % (k0[0],k0[1],k0[2],k0[3],k0[4],k0[5],k0[6],k0[7],k0[8]))
        fout_script.write('Total generate & %s &%s &%s &%s &%s &%s &%s &%s&%s  \\\ \n'% (k1[0],k1[1],k1[2],k1[3],k1[4],k1[5],k1[6],k1[7],k1[8]))
        fout_script.write('$N_{\mu^+}=1,N_{\mu^-}=1,N_{charged}<3$ & %s &%s &%s &%s &%s &%s &%s &%s&%s   \\\ \n'%(k2[0],k2[1],k2[2],k2[3],k2[4],k2[5],k2[6],k2[7],k2[8])) 
        fout_script.write('$N_{\gamma}=0$ & %s &%s &%s &%s &%s &%s &%s &%s&%s    \\\ \n' %(k3[0],k3[1],k3[2],k3[3],k3[4],k3[5],k3[6],k3[7],k3[8]))
        fout_script.write('$25GeV<P_{t}^{\mu^+\mu^-}<70GeV$ & %s &%s &%s &%s &%s &%s &%s &%s &%s   \\\ \n' %(k4[0],k4[1],k4[2],k4[3],k4[4],k4[5],k4[6],k4[7],k4[8]))
        fout_script.write('$|P_{z}^{\mu^+\mu^-}|<50GeV$ & %s &%s &%s &%s &%s &%s &%s &%s&%s    \\\ \n'  %(k5[0],k5[1],k5[2],k5[3],k5[4],k5[5],k5[6],k5[7],k5[8]))
        fout_script.write('$\\theta_{\mu^+\mu^-}<145$ & %s &%s &%s &%s &%s &%s &%s &%s&%s    \\\ \n' %(k6[0],k6[1],k6[2],k6[3],k6[4],k6[5],k6[6],k6[7],k6[8]))
        fout_script.write('$100GeV<E_{visible}<110GeV$  & %s &%s &%s &%s &%s &%s &%s &%s &%s   \\\ \n'  %(k7[0],k7[1],k7[2],k7[3],k7[4],k7[5],k7[6],k7[7],k7[8]))
        fout_script.write('$86GeV<M_{\mu^+\mu^-}<97GeV$ & %s &%s &%s &%s &%s &%s &%s &%s&%s    \\\ \n' %(k8[0],k8[1],k8[2],k8[3],k8[4],k8[5],k8[6],k8[7],k8[8]))
        fout_script.write('$120GeV<M_{recoil}<140GeV$ & %s &%s &%s &%s &%s &%s &%s &%s  &%s  \\\ \n'  %(k9[0],k9[1],k9[2],k9[3],k9[4],k9[5],k9[6],k9[7],k9[8]))
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