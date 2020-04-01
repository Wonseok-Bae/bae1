#! /usr/bin/env bash

USERDIR="/pnfs/dune/persistent/users/wbae/CAF2"
CP="ifdh cp"

source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh

setup genie v2_12_10c -q e15:prof
setup genie_xsec v2_12_10 -q DefaultPlusValenciaMEC
setup genie_phyopt v2_12_10 -q dkcharmtau
setup dk2nu v01_05_01b -q e15:prof
setup ifdhc

# 1 trial
#${CP} ${USERDIR}/app.tar.gz app.tar.gz

#tar -xzf app.tar.gz
#mv app/* .

# 2 trial
${CP} ${USERDIR}/app2.tar.gz app2.tar.gz

tar -xzf app2.tar.gz
mv app2/* .

chmod +x app_3

./app_3 0 0 NEOSPROSPECT

${CP} scan2Dnew_NEOSPROSPECT_fissionFree_ISO0_SYST0_0_0_3.txt ${USERDIR}/scan2Dnew_NEOSPROSPECT_fissionFree_ISO0_SYST0_0_0_3.txt
