#!/usr/bin/env bash

# Usage: ./newtask.sh [problem-id]

if [ -d "$1" ]; then
    echo "The task is exist."
    exit
fi 

mkdir "$1"
cd "$1"

mkdir "gen"
mkdir "solutions"
mkdir "testdata"
mkdir "validation"

problem_header="---
problemLabel: A
problemName: 題目標題
problemId: $1
---

#

"

(echo "$problem_header") > "problem.md"

scoretxt='GroupMin
[[10, 5], [20, 5], [30, 10], [40, 10]]

reference
https://cms.readthedocs.io/en/v1.4/Score%20types.html
#[[score1,t1],[score2,t2]]
'

(echo "$scoretxt") > "score.txt"

echo "Created"