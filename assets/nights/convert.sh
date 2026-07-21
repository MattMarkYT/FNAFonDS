#!/bin/sh

GRIT=/c/msys64/opt/wonderful/thirdparty/blocksds/core/tools/grit/grit

#$GRIT new0.png -ftB -fh! -gT000000 -gt -gB8 -m!

#mv *.pal *.img ../../nitrofiles/sprite/title

$GRIT night1.png -ftB -fh! -gT000000 -gt -gB8 -mR8 -mLs
$GRIT night2.png -ftB -fh! -gT000000 -gt -gB8 -mR8 -mLs
$GRIT night3.png -ftB -fh! -gT000000 -gt -gB8 -mR8 -mLs
$GRIT night4.png -ftB -fh! -gT000000 -gt -gB8 -mR8 -mLs
$GRIT night5.png -ftB -fh! -gT000000 -gt -gB8 -mR8 -mLs
$GRIT night6.png -ftB -fh! -gT000000 -gt -gB8 -mR8 -mLs
$GRIT night7.png -ftB -fh! -gT000000 -gt -gB8 -mR8 -mLs

mv *.pal *.img *.map ../../nitrofiles/bg/nights