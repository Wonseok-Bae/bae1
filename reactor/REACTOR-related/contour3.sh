#! /usr/bin/env bash

x=1
xx=0.001
y=1
yy=0.001

while [ $x -le 20 ]
do
	while [ $y -le 20 ]
	do
            	./app $xx $yy NEOSPROSPECT
		y=$((y+1))
        	yy=`echo "$yy+0.02" | bc -l`

	done
	y=1
        yy=0.02
	x=$((x+1))
        xx=`echo "$xx+0.02" | bc -l`

done

cat scan2Dnew* > chi2.txt
rm scan2Dnew*

