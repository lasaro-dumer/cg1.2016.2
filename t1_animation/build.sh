#!/bin/bash
if [ -z "$3" ]; then
    echo usage: $0 input_dir file_name output_dir [width height]
    exit
fi
IDIR=$1
BASE=$IDIR/$2
ODIR=$3
W=1024
H=768
if [ -z "$4" ]; then
    echo auto resolution
else
    if [ -z "$5" ]; then
        echo usage: $0 input_dir file_name output_dir [width height]
        exit
    fi
    W=$4
    H=$5
fi
echo width=$W height=$H
povray $BASE.ini +I$BASE.pov +FN +O$BASE +W$W +H$H
ffmpeg -f image2 -framerate 30 -i $BASE%02d.png $ODIR/$2.gif -y
