#!/bin/sh

GRIT=/c/msys64/opt/wonderful/thirdparty/blocksds/core/tools/grit/grit

#$GRIT leftButts.png -ftB -fh! -gTFF00FF -gt -gB8 -m!
#$GRIT rightButts.png -ftB -fh! -gTFF00FF -gt -gB8 -m!

#mv *.pal *.img ../../nitrofiles/sprite/office

$GRIT office.png -ftB -fh! -gt -gTFF00FF -gB8 -mR8 -mLs
$GRIT office_doors.png -ftB -fh! -gt -gB8 -mR8 -mLs
$GRIT office_LLight.png -ftB -fh! -gt -gB8 -mR8 -mLs
$GRIT office_LBonnie.png -ftB -fh! -gt -gB8 -mR8 -mLs
$GRIT office_RLight.png -ftB -fh! -gt -gB8 -mR8 -mLs
$GRIT office_RChica.png -ftB -fh! -gt -gB8 -mR8 -mLs

mv *.pal *.img *.map ../../nitrofiles/bg/office