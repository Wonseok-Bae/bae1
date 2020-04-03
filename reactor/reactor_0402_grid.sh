#! /usr/bin/env bash

USERDIR="/pnfs/dune/persistent/users/wbae/CAF2"
CP="ifdh cp"

source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh

setup genie v2_12_10c -q e15:prof
setup genie_xsec v2_12_10 -q DefaultPlusValenciaMEC
setup genie_phyopt v2_12_10 -q dkcharmtau
setup dk2nu v01_05_01b -q e15:prof
setup ifdhc

${CP} ${USERDIR}/app2.tar.gz app2.tar.gz

tar -xzf app2.tar.gz
mv app2/* .

chmod +x app


ds=0

dm=`echo $((  ${PROCESS}  /  20  ))` #변수 정의 할 때 = 사이에 띄어 쓰기 있으면 안 됨
xx=`echo $((  ${PROCESS}  %  20  ))` 

if [  `expr $PROCESS % 20` -eq 0  ]
then
	ds=`echo $((0))`
fi
	
if [  `expr $xx % 2` -eq 0  ]
then
       	yy=2
else
       	yy=3
fi


ds=`echo $((ds+yy))` #값 대입할 때
echo dm : `echo $(( ${dm}+1 ))`
echo dsfrom : `echo $(( ${ds}-$yy ))` 
echo dsto : ${ds}
echo PROCESS : ${PROCESS}

./app `echo $(( ${dm}+1 ))` `echo $(( ${ds}-$yy ))` ${ds} NEOSPROSPECT
	
#${CP} scan2Dnew_NEOSPROSPECT_fissionFree_ISO0_SYST0_`echo $(( ${dm}+1 ))`_`echo $(( ${ds}-$yy ))`_${ds}.txt ${USERDIR}/scan2Dnew_NEOSPROSPECT_fissionFree_ISO0_SYST0_${PROCESS}.txt
${CP} scan2Dnew_NEOSPROSPECT_fissionFree_* ${USERDIR}/
