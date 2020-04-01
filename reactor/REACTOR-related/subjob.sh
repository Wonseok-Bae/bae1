#!/bin/bash

QUEUE=ALL
QUEUE=atmpd
FOLDER=shell
count=0

for i in `ls $FOLDER/run-*.sh`

do
    echo $count
if [[ "$count" -lt "1000" ]]; then
    echo 'Submitting' $i 'to' $QUEUE 'queue...'
    qsub -eo -o /dev/null -q $QUEUE $i

else
    echo 'not loaded..'   
fi
((++count))


done

