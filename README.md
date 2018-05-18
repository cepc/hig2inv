# hig2inv

Higgs Invisible Analysis

## Note

- Please extract ROOT files by command line or by submitting jobs to backstage in bash mode (by excuting "bash" in your command line if your default mode is tcshell).

- Set environment: source setup.sh(In bash mode)

- Build program: ./build.sh

- Run program: ./submit.sh X.X.X(find in submit.sh)

- Directories created by submit.sh: data/figs/presel/rawdata/steer.

## For developers

- Fork the code with your personal github ID. See [details](https://help.github.com/articles/fork-a-repo/)

> git clone git@github.com:cepc/hig2inv.git

- Make your change, commit and push

> git commit -a -m "Added feature A, B, C"

> git push

- Make a pull request. See [details](https://help.github.com/articles/using-pull-requests/)


## Some styles to follow 

- Minimize the number of main c++ files

- Keep functions length less than one screen

- Seperate hard-coded cuts into script file

- Use pull-request mode on git

- Document well the high-level bash file for work flow
