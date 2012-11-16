#! /bin/bash
if test $# -lt 1 ; then
echo "sc: no input files" ; exit ; fi
out="a.out"
if test $# -gt 1 ; then
out=$2 ; fi
echo "Translating into c++"
./parse $1 out.cpp
echo "Compiling.."
g++ out.cpp types.o -o $out >& out.log
rc=$?
if [[ $rc != 0 ]] ; then
    ./error out.log
    rm out.log
    exit $rc
fi
echo "Finalizing.."
rm -rf out.cpp
rm -rf out.log
echo "Done."
