#! /usr/bin/env bash

source /grid/fermiapp/products/dune/setup_dune.sh
setup cmake v3_9_0
setup gcc v6_4_0
#source /cvmfs/larsoft.opensciencegrid.org/products/root/v6_10_08b/Linux64bit+2.6-2.12-e15-nu-prof/bin/thisroot.sh
source /cvmfs/larsoft.opensciencegrid.org/products/root/v6_12_06a/Linux64bit+2.6-2.12-e15-prof/bin/thisroot.sh
setup genie        v2_12_8c   -q e15:prof
setup genie_xsec   v2_12_8    -q DefaultPlusMECWithNC
setup genie_phyopt v2_12_8    -q dkcharmtau
setup dk2nu        v01_05_01b -q e15:prof
setup geant4 v4_10_3_p01b -q e15:prof
setup ifdhc
