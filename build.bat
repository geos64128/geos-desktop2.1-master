cls
del /S/Q target
rd target
md target

cd src

cl65 -t geos-cbm -O -o ..\target\desktop.cvt desktop-res.grc desktop.c

del *.o
cd ..\target

c1541 -format "desktop,sh" d64 desktop.d64
c1541 -attach desktop.d64 -write desktop.cvt desktop.cvt

cd ..
