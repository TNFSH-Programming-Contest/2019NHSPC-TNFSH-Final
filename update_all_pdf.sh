#!/usr/bin/env bash

lstmp="$(mktemp)"
taskstmp="$(mktemp)"

(ls -l | grep ^d) > $lstmp

(awk -F" " '{print $9}' $lstmp) > $taskstmp

cat $taskstmp

cat $taskstmp | xargs -n1 ./compile_pdf.sh 

cat $taskstmp | xargs -I % -n1 cmsAddStatement -o % zh %/problem.pdf