set IDIR=%1
set BASE=%IDIR%/%2
set OUT=%3/%2
ffmpeg -f image2 -framerate 30 -i %BASE%%%02d.png %OUT%.gif -y