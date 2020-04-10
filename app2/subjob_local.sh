#!/bin/bash

for i in `ls shell/run-*.sh`
do
	source $i
done

