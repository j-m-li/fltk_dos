echo Making FLTK-UTF8 for 16bits DOS !!!
cd src
wmake _DOS=1 HAVE_XUTF8=1 -f makefile.dos %1
cd ..
cd dos
wmake _DOS=1 HAVE_XUTF8=1 -f makefile.dos %1
cd ..
cd test
rem rm -f  hello.exe 
wmake _DOS=1 HAVE_XUTF8=1 -f makefile.dos %1
rem rm -f  \cpp\hello.exe 
rem mv hello.exe \cpp\
cd ..
echo Done.
