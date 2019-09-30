#!/bin/bash

g++ -std=c++11 -Wall large.cpp -o large.exe
filename=($(ls testcases/ | tr ' ' '\n' | grep ".in" | sed 's/.in//g'))

for ((i=0; i<${#filename[@]}; i++)); do
  echo "./large.exe < testcases/${filename[$i]}.in > testcases/${filename[i]}.out"
  ./large.exe < testcases/${filename[$i]}.in > testcases/${filename[i]}.out
done
