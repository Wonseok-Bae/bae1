#! /usr/bin/env bash
#:<<"END"
echo ${PROCESS}
RUNNUMBER=${PROCESS}
echo $RUNNUMBER


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

chmod +x app_noloop_23free_log
#END

#RUNNUMBER=0
#for((i=1; i<=2601; i++))
#do

	
	dm=`echo $((  ${RUNNUMBER}  /  51  ))` #변수 정의 할 때 = 사이에 띄어 쓰기 있으면 안 됨
	ds=`echo $((  ${RUNNUMBER}  %  51  ))`

	#RUNNUMBER=`echo $((RUNNUMBER+1))`
	
	./app_noloop_23free_log `echo $(( ${dm} ))` `echo $(( ${ds} ))` NEOSPROSPECT
	#echo `echo $(( ${dm} ))` `echo $(( ${ds} ))` NEOSPROSPECT ${RUNNUMBER}
	${CP} scan2Dnew_NEOSPROSPECT_fissionFree_ISO0_SYST0_`echo $(( ${dm} ))`_`echo $(( ${ds} ))`.txt ${USERDIR}/scan2Dnew_NEOSPROSPECT_fissionFree_ISO0_SYST0_${RUNNUMBER}.txt

#done
