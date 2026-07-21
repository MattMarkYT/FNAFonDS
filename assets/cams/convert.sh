#!/bin/sh

GRIT=/c/msys64/opt/wonderful/thirdparty/blocksds/core/tools/grit/grit

#$GRIT contnight.png -ftB -fh! -gT000000 -gt -gB8 -m!
#$GRIT version.png -ftB -fh! -gT000000 -gt -gB8 -m!

#mv *.pal *.img ../nitrofiles/sprite/title

$GRIT dining.png -ftB -fh! -gT000000 -gt -gB8 -mR8 -mLs
$GRIT e_hall_corner.png -ftB -fh! -gT000000 -gt -gB8 -mR8 -mLs
$GRIT e_hall.png -ftB -fh! -gT000000 -gt -gB8 -mR8 -mLs
$GRIT backstage.png -ftB -fh! -gT000000 -gt -gB8 -mR8 -mLs
$GRIT bathroom.png -ftB -fh! -gT000000 -gt -gB8 -mR8 -mLs
$GRIT showstage.png -ftB -fh! -gT000000 -gt -gB8 -mR8 -mLs
$GRIT supply.png -ftB -fh! -gT000000 -gt -gB8 -mR8 -mLs
$GRIT w_hall.png -ftB -fh! -gT000000 -gt -gB8 -mR8 -mLs
$GRIT w_hall_corner.png -ftB -fh! -gT000000 -gt -gB8 -mR8 -mLs
$GRIT p_cove.png -ftB -fh! -gT000000 -gt -gB8 -mR8 -mLs
$GRIT black.png -ftB -fh! -gT000000 -gt -gB8 -mR8 -mLs

mv *.pal *.img *.map ../../nitrofiles/bg/cams