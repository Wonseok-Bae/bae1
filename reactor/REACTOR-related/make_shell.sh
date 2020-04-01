#!/bin/sh

workdir=`pwd`

#mkdir -p shell

source ~/my_setup.sh

for dm in `seq 0 50` ; do
    #for st in `seq 0 50`; do    
        #cat > shell/run-$dm-$st.sh <<EOF
    cat > shell/run-$dm.sh <<EOF

#!/bin/bash

source /home/gyang9/my_setup.sh
#export ATMPD_ROOT=$ATMPD_ROOT
#export SKOFL_ROOT=$SKOFL_ROOT
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH

source /disk01/usr5/gyang/REACTOR-related/makeApp
COUNTER=0

while [  \$COUNTER -lt 50 ]; do
  /disk01/usr5/gyang/REACTOR-related/app $dm \$COUNTER DYBNEOSPROSPECT
  #./app $dm $st
  let COUNTER=COUNTER+1
done

EOF
    
        #chmod +x shell/run-$dm-$st.sh
	chmod +x shell/run-$dm.sh
    #done
done
