#!/bin/sh

GRIT=/c/msys64/opt/wonderful/thirdparty/blocksds/core/tools/grit/grit

$GRIT title.png -ftB -fh! -gT000000 -gt -gB8 -m!
$GRIT star.png -ftB -fh! -gT000000 -gt -gB8 -m!

mv *.pal *.img ../../nitrofiles/sprite/title

#$GRIT office.png -ftB -fh! -gt -gTFF00FF -gB8 -mR8 -mLs

#mv *.pal *.img *.map ../../nitrofiles/bg/office