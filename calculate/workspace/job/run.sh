export LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH
make clean
mkdir -vp out/log/
#mkdir -vp out/plots/part
mkdir -vp out/workspace/part
 
make shapeFit
./bin/shapeFit  > out/log/workspace_`date +%Y%m%d%H%M`


