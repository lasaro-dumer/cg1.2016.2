#!/bin/bash
W=1024
H=768
FPS=30
IDIR=""
DIG=2
COMPILE=true
KEEP=false
GIF=false
while getopts ":p:i:o:w:h:f:s:k:g:" opt; do
  case $opt in
    p) POVFile="$OPTARG"
    ;;
    i) IDIR="$OPTARG"
    ;;
    o) ODIR="$OPTARG"
    ;;
    w) W="$OPTARG"
    ;;
    h) H="$OPTARG"
    ;;
    f) KFF="$OPTARG"
    ;;
    s) FPS="$OPTARG"
    ;;
    k) KEEP=true
    ;;
    g) GIF=true
    ;;
    \?) echo "Invalid option -$OPTARG" >&2
    ;;
  esac
done
if [ -z "$IDIR" ]; then
    echo Specify an input dir with '-i'
    exit
fi
if [ -z "$ODIR" ]; then
    echo Specify an output dir with '-o'
    exit
fi
if [ -z "$POVFile" ]; then
    echo Specify the .pov file name with '-p' \(without extension\)
    exit
fi
BASE=$IDIR/$POVFile
printf "Input dir is %s\n" "$IDIR"
printf "Output dir is %s\n" "$arg_1"
echo FPS is $FPS
echo width=$W height=$H
workdir=${PWD}          # to assign to a variable

rm -rf $BASE*.png
if [ -z "$KFF" ]; then
  povray $BASE.ini +I$BASE.pov +FN +O$BASE +W$W +H$H -GA -V -WL0 +L$workdir/lib +L$workdir
else
  echo Final frame is $KFF
  if [[ "$KFF" -eq 1 ]]; then
    COMPILE=false
  elif [[ "$KFF" -lt 10 ]]; then
    DIG=1
  elif [[ "$KFF" -lt 100 ]]; then
    DIG=2
  elif [[ "$KFF" -lt 1000 ]]; then
    DIG=3
  else
    echo Invalid max frames, the max is 999
    exit
  fi
  povray $BASE.ini +I$BASE.pov +FN +O$BASE +W$W +H$H +KFF$KFF -GA -V -WL0 +L$workdir/lib +L$workdir
fi
if [[ "$COMPILE" == true ]]; then
  if [[ "$GIF" == false ]]; then
    ffmpeg -framerate $FPS -i $BASE%0"$DIG"d.png -s:v "$W"x"$H" $ODIR/$POVFile.mp4 -y
  else
    ffmpeg -f image2 -framerate $FPS -i $BASE%0"$DIG"d.png $ODIR/$POVFile.gif -y
  fi
  if [[ "$KEEP" == false ]]; then
    rm -rf $BASE*.png
  fi
fi
