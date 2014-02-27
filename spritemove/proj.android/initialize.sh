#!/bin/bash

# ADD LIBS HERE:
LIBS[0]="$COCOS2DX_ROOT/cocos2dx/platform/android/java"
#LIBS[1]="$COCOS2DX_ROOT/"
#LIBS[2]="$COCOS2DX_ROOT/"
##

outfile="local.properties"

# remove $outfile, if exists
if [ -f $outfile ]
then
    rm $outfile
fi

# generate local.properties and configure build
android update project -p .

# add 'android.library.reference' libraries
if [[ ${#LIBS[*]} > 0 ]]
then
    echo >> $outfile

    i=0
    for each in ${LIBS[@]}
    do
        let "i++"

        relpath=$(python2 -c "import os.path; print os.path.relpath('$each','${2:-$PWD}')")

        echo "android.library.reference.$i=$relpath" >> $outfile
    done
fi
