#! /usr/bin/env bash

x=0
xx=0
y=0
yy=0

while [ $x -le 50 ]
do
	while [ $y -le 50 ]
	do
            	./app $xx $yy NEOSPROSPECT
		y=$((y+1))
        	yy=`echo "$yy+1" | bc -l`

	done
	y=0
        yy=0
	x=$((x+1))
        xx=`echo "$xx+1" | bc -l`

done

cat scan2Dnew_NEOSPROSPECT_fissionFree_ISO0_SYST0_* > chi2.txt
rm  scan2Dnew_NEOSPROSPECT_fissionFree_ISO0_SYST0_*

