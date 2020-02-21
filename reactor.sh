#! /usr/bin/env bash

USERDIR="/pnfs/dune/persistent/users/wbae/reactor"
#OUTDIR="/pnfs/dune/persistent/users/wbae/reactor"

source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh #grid
#jobsub_submit --group dune --role=Analysis -N 100 --OS=SL6 --expected-lifetime=8h --memory=2000MB --group=dune file:///nashome/w/wonseok/reactor.sh

#=============================================================================================================1. Input/Output Address + Run the Source setup.sh

rm -rf REACTOR-related
rm -f REACTOR-related.tar.gz
echo "step1. clean node"

#cd /pnfs/dune/persistent/users/wbae/reactor
ifdh cp /pnfs/dune/persistent/users/wbae/reactor/REACTOR-related.tar.gz .
echo "step2. copy compressed file"

chmod 777 REACTOR-related.tar.gz
tar -zxvf REACTOR-related.tar.gz 
echo "step3. release compressed file"

chmod -R 777 REACTOR-related
cd REACTOR-related
./app 0.002 0.002 NEOS
echo "step4. run"

ifdh cp *.root /pnfs/dune/persistent/users/wbae/reactor/REACTOR-related
cd ..
echo "step5. copy output files"

# Copy stuff from the local node to USERDIR
#cd ${USERDIR}
#rm -rf *
#echo "cleaning USERDIR"
#cd /nashome/w/wbae/reactor
#pwd

#chmod 777 REACTOR-related.tar.gz
#cp REACTOR-related.tar.gz ${USERDIR}
#echo "copy success"
 
#cd ${USERDIR}
#pwd
#ls

#chmod 777 REACTOR-related.tar.gz
#tar -zxvf REACTOR-related.tar.gz
#chmod -R 777 REACTOR-related
#echo "release compresssing success"

#===========================================================================================================2. Copy/Move tar file + Remove xml file
#cd REACTOR-related
#pwd
#ls
#g++ -std=c++11 -o app app.cc simple_DC.cc -lRooFit -lMinuit -lRooFitCore `root-config --cflags --glibs`
#echo "complie success"
#./app 0.002 0.002 NEOS
#echo "run success"

#cd /nashome/w/wbae/reactor
#pwd
#echo "come back"








#=============================================================================================================3. get Input data files + Chmod

# Add the location of the GNuMIFlux.xml to the GENIE xml path
# export GXMLPATH=${PWD}:${GXMLPATH}
# export GNUMIXML="GNuMIFlux.xml"

#=============================================================================================================4. Export output file

## Run GENIE and copy output file to dCache persistent

#gevgen_fnal \
#    -f local_flux_files/*.dk2nu.root,DUNEND \
#    -g ${GEOMETRY}.gdml \
#    -t ${TOPVOL} \
#    -m ${GEOMETRY}.${TOPVOL}.maxpl.xml \
#    -L cm -D g_cm3 \
#    ${NEVENTS} \
#    --seed ${RNDSEED} \
#    -r ${RNDSEED} \
#    -event-generator-list Default+CCMEC

#============================================================================================================5. Run the comfiled file
