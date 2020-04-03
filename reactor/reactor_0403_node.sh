#! /usr/bin/env bash

USERDIR="/pnfs/dune/persistent/users/wbae/CAF2"
CP="ifdh cp"

source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh

setup genie v2_12_10c -q e15:prof
setup genie_xsec v2_12_10 -q DefaultPlusValenciaMEC
setup genie_phyopt v2_12_10 -q dkcharmtau
setup dk2nu v01_05_01b -q e15:prof
setup ifdhc

	PROCESS=1
	while((PROCESS <=400))
	do	
		for((ds=1; ds<=20; ds++))
		do
		echo dm : ${dm} ds : ${ds} PROCESS : ${PROCESS}
		dm=`echo $((  ${PROCESS}  /  20  ))`
		./app_noloop ${dm} ${ds} NEOSPROSPECT
		${CP} scan2Dnew_NEOSPROSPECT_fissionFree* ${USERDIR}/
		PROCESS=`echo $((PROCESS+1))`
		done
	done

#${CP} scan2Dnew_NEOSPROSPECT_fissionFree* ${USERDIR}/
