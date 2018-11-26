#!/bin/bash

if [ $# -eq 0 ];
then
    echo "Usage: $0 <Files....>"
    echo "Require file to plot!"
    exit 1
fi


while (( $# )); do

INPUT="$1"
OUTPUT="${INPUT%.*}"

gnuplot << EOF
set terminal png enhance size 900,900
set output "$OUTPUT.png"

set border 0
set style line 101 lc rgb '#808080' lt 1 lw 1
unset xlabel
unset ylabel
set format x ''
set format y ''
set tics scale 0

set palette gray

set view map
set pm3d
splot "$INPUT" notitle
EOF
    
shift
done
