#!/bin/bash

ROOTfile=$1

echo "OK0"
echo $ROOTfile
#aliroot -b -l -q fitZNC.cpp($ROOTfile)


#before I had always used aliroot -b -l -q , but it doesn't seem to work...
aliroot -b -l <<EOF
.L fitFinal/fitZNC.cpp
fitZNC("$ROOTfile");
EOF

echo "OK1"

aliroot -b -l <<EOF
.L fitFinal/fitZNA.cpp
fitZNA("$ROOTfile");
EOF

echo "OK2"

aliroot -b -l <<EOF
.L fitFinal/fitPROPER.cpp
fitROOFit("$ROOTfile", 0);
EOF

echo "OK3"

aliroot -b -l <<EOF
.L fitFinal/fitPROPER.cpp
fitROOFit("$ROOTfile", 1);
EOF

echo "OK4"

aliroot -b -l <<EOF
.L fitFinal/fitPROPER.cpp
fitROOFit("$ROOTfile", 2);
EOF

aliroot -b -l <<EOF
.L fitFinal/fitExponentialBkg.cpp
fitROOFit("$ROOTfile", 0);
EOF

echo "OK5"

aliroot -b -l <<EOF
.L fitFinal/fitExponentialBkg.cpp
fitROOFit("$ROOTfile", 1);
EOF

echo "OK6"

aliroot -b -l <<EOF
.L fitFinal/fitExponentialBkg.cpp
fitROOFit("$ROOTfile", 2);
EOF


var1=$(aliroot -b -l <<EOF
.L fitFinal/fitSuppressedNjpsi.cpp
fitROOFit("$ROOTfile", 0);
EOF)

echo "OK5"

var2=$(aliroot -b -l <<EOF
.L fitFinal/fitSuppressedNjpsi.cpp
fitROOFit("$ROOTfile", 1);
EOF)

echo "OK6"

var3=$(aliroot -b -l <<EOF
.L fitFinal/fitSuppressedNjpsi.cpp
fitROOFit("$ROOTfile", 2);
EOF)

echo "$var1" > outputSuppressedSelFlag0.txt
echo "$var2" > outputSuppressedSelFlag1.txt
echo "$var3" > outputSuppressedSelFlag2.txt


echo "OK7"

var=$(aliroot -b -l <<EOF
.L fitFinal/readHisto.cpp
readHisto("$ROOTfile");
EOF)

echo "$var" > output.txt

echo "OK8"

echo "These are the results of: $ROOTfile" > ReadMeAnalysisResults.md
sort -n output.txt > outputSorted.txt

rm output.txt

if [ -d "pngResults/$(date +%F)" ]; then rm -rf pngResults/$(date +%F); fi
mkdir -p pngResults/$(date +%F)

mv ReadMeAnalysisResults.md     pngResults/$(date +%F)
mv outputSorted.txt             pngResults/$(date +%F)
mv outputSuppressedSelFlag0.txt pngResults/$(date +%F)
mv outputSuppressedSelFlag1.txt pngResults/$(date +%F)
mv outputSuppressedSelFlag2.txt pngResults/$(date +%F)
mv test*.root                   pngResults/$(date +%F)
mv pngResults/*.png             pngResults/$(date +%F)
