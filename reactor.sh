#! /usr/bin/env bash

USERDIR="/pnfs/dune/persistent/users/wbae/CAF2"
CP="ifdh cp"

source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh

setup genie v2_12_10c -q e15:prof
setup genie_xsec v2_12_10 -q DefaultPlusValenciaMEC
setup genie_phyopt v2_12_10 -q dkcharmtau
setup dk2nu v01_05_01b -q e15:prof
setup ifdhc


${CP} ${USERDIR}/app.tar.gz app.tar.gz

tar -xzf app.tar.gz
mv app/* .
chmod +x app

./app

${CP} scan2Dnew_NEOSPROSPECT_fissionFree_ISO0_SYST0_0_0.txt ${USERDIR}/scan2Dnew_NEOSPROSPECT_fissionFree_ISO0_SYST0_0_0.txt
