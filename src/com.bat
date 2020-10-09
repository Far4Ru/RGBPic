@echo OFF
windres prog.rc -O coff -o icon.res
gcc -mwindows main.c icon.res -o ../RGBPic.exe
cd ..
RGBPic.exe
pause