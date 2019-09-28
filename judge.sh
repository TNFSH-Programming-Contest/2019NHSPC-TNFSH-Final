#!/usr/bin/env bash
cd $1/testdata
for input in *.in; do output=$(echo $input | cut -f1 -d.).out; echo $input; time ../../$2 < $input > /tmp/output && diff /tmp/output $output && echo ok; done
