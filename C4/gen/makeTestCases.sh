#!/bin/bash
ts=( 50 50 50 50 50 50 50   50  50  50  50  50   50  50   50   50   50   50   50     50  50   50   50   50   50   50   )
ns=( 6  6  6  6  6  6  6    10  10  10  10  10   80  80   80   80   80   80   80     150 150  150  150  150  150  150  )
ms=( 4  6  8  10 12 14 15   15  25  35  44  45   100 200  400  800  1600 3000 3159   500 1000 2000 4000 4900 4949 4950 )

for ((i=0; i<${#ns[@]}; i++)); do
  filename="testcases/"
  if [ $i -lt 10 ]; then
    filename="${filename}0"
  fi
  filename="${filename}$i.in"
  echo "./make_graph.exe -t ${ts[$i]} ${ns[$i]} ${ms[$i]} > $filename"
  ./make_graph.exe -t ${ts[$i]} ${ns[$i]} ${ms[$i]} > $filename
done
