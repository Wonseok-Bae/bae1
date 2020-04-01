#! /usr/bin/env bash

x=1
xx=0.001
y=1
yy=0.01

while [ $x -le 10 ]
do
	while [ $y -le 10 ]
	do
            	./app $xx $yy NEOS
		y=$((y+1))
        	yy=`echo "$yy+0.05" | bc -l`

	done
	y=1
        yy=0.01
	x=$((x+1))
        xx=`echo "$xx+0.001" | bc -l`

done

cat scan2Dnew_NEOS_fissionFree_ISO0_SYST0_* > chi2.txt
rm scan2Dnew_NEOS_fissionFree_ISO0_SYST0_*

