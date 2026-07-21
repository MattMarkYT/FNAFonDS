#!/bin/sh

GRIT=/c/msys64/opt/wonderful/thirdparty/blocksds/core/tools/grit/grit

#$GRIT contnight.png -ftB -fh! -gT000000 -gt -gB8 -m!
#$GRIT version.png -ftB -fh! -gT000000 -gt -gB8 -m!

#mv *.pal *.img ../nitrofiles/sprite/title

$GRIT /cams -ftB -fh! -gT000000 -gt -gB8 -mR8 -mLs

mv *.pal *.img *.map ../nitrofiles/bg/cams