#! /usr/bin/env bash

x=1
xx=0.0001
y=1
yy=0.01

while [ $x -le 10 ]
do
	while [ $y -le 50 ]
	do
            	./app $xx $yy NEOS
		y=$((y+1))
        	yy=`echo "$yy+0.01" | bc -l`

	done
	y=1
        yy=0.01
	x=$((x+1))
        xx=`echo "$xx+0.0001" | bc -l`

done

x=1
xx=0.001
y=1
yy=0.01

while [ $x -le 10 ]
do
        while [ $y -le 50 ]
        do
                ./app $xx $yy NEOS
                y=$((y+1))
                yy=`echo "$yy+0.01" | bc -l`

        done
        y=1
        yy=0.01
        x=$((x+1))
        xx=`echo "$xx+0.001" | bc -l`

done


x=1
xx=0.01
y=1
yy=0.01

while [ $x -le 10 ]
do
        while [ $y -le 50 ]
        do
                ./app $xx $yy NEOS
                y=$((y+1))
                yy=`echo "$yy+0.01" | bc -l`

        done
        y=1
        yy=0.01
        x=$((x+1))
        xx=`echo "$xx+0.01" | bc -l`

done



x=1
xx=0.1
y=1
yy=0.01

while [ $x -le 10 ]
do
        while [ $y -le 50 ]
        do
                ./app $xx $yy NEOS
                y=$((y+1))
                yy=`echo "$yy+0.01" | bc -l`

        done
        y=1
        yy=0.01
        x=$((x+1))
        xx=`echo "$xx+0.1" | bc -l`

done


x=1
xx=1
y=1
yy=0.01

while [ $x -le 10 ]
do
        while [ $y -le 50 ]
        do
                ./app $xx $yy NEOS
                y=$((y+1))
                yy=`echo "$yy+0.01" | bc -l`

        done
        y=1
        yy=0.01
        x=$((x+1))
        xx=`echo "$xx+1" | bc -l`

done


cat scan2Dnew_NEOS_fissionFree_ISO0_SYST0_* > chi2.txt
rm scan2Dnew_NEOS_fissionFree_ISO0_SYST0_*

