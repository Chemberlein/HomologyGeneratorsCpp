#!/usr/bin/env sh

echo Hello and welcome!
echo This scrip allow you to compute persistance of topology features of point space and homology generators of this point space \(Read Simplicial_complex.pdf for more information\)
echo Give name of the file that contain information about point space that you want to use \(Read readme in order to get right format\)
echo Give file name :
read fileN
echo Modes:
echo 0 - compute persistence of topology features
echo 1 - compute homology generators to the D-rips complex chousen automaticly
echo 2 - compute homology generators for specific D-rips complex
read des
case $des in
    0)
        cd ComputationOfHomology\(cpp\)
        make
        ./main ../$fileN 0 0
        cd ..
    ;;
    1)
        cd ComputationOfHomology\(cpp\)
        make
        ./main ../$fileN 0 1
        cd ..
    ;;
    2)
        echo give distance
        read dist
        cd ComputationOfHomology\(cpp\)
        make
        ./main ../$fileN 0 2 $dist
        cd ..
    ;;
esac
i=0
while [ $i -eq 0 ]
do
    echo 0 - skip plot or exit plot
    echo 1 - plot Persistance diagram
    echo 2 - plot Homology generators
    read pltstep

    case $pltstep in
        0)
            echo Ok
            i=1
            ;;
        1)
            cd PlotOfResult\(python\)
            python3 plots.py ../$fileN 1
            cd ..
            ;;
        2)
            cd PlotOfResult\(python\)
            python3 plots2.py ../$fileN 1
         cd ..
         ;;
    esac
done
