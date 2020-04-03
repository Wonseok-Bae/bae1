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

chmod +x app_noloop_1free


	xx=1
	while((xx <=400))
	do	
		#for((ds=1; ds<=20; ds++))
		#do
		echo dm : ${dm} ds : ${ds} PROCESS : ${xx}
		dm=`echo $((  ${xx}  /  20  ))`
		ds=`echo $((  ${xx}  %  20  ))`
		./app_noloop_1free ${dm} ${ds} NEOS
		#${CP} scan2Dnew_NEOSPROSPECT_fissionFree* ${USERDIR}/
		PROCESS=`echo $((xx+1))`
		#done
	done

${CP} scan2Dnew_* ${USERDIR}/
