source setup.sh 

make

fitScan -f ../workspace/out/workspace/cepc_5.root  -p ez4v=1_-5_5,mz4v=1_-5_5,qz4v=1_-5_5  --hesse 1 --minos 1 -o outs/singleFit_CEPC-in.root


