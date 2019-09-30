#!/usr/bin/env bash

# Usage: ./compile_pdf.sh [problem-id]

contestName="2019臺南一中上學期校內複選"

cd "$1"

echo "Compiling $1"

pandoc -M contestName="$contestName" -T "" problem.md -o problem.pdf --template ../template.tex -f markdown -t latex -s --latex-engine=xelatex

echo "Compile Finish"