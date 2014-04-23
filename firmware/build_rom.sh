#!/bin/sh


echo "Building Vicious ROM image: vicious"
cc65 -O -t replica1 main.c
cc65 -O -t replica1 vicilibc.c
cc65 -O -t replica1 sidfile.c
cc65 -O -t replica1 cffa1.c

ca65 main.s
ca65 viciliba.s
ca65 vicilibc.s
ca65 sidfile.s
ca65 cffa1.s
ca65 cffa1a.s

ld65 -o vicious -m vicious.map -C ld_rom.cfg main.o viciliba.o vicilibc.o sidfile.o cffa1.o cffa1a.o replica1.lib

rm -f vicious.map
rm -f main.s
rm -f vicilibc.s
rm -f cffa1.s

cp vicious /Applications/OpenEmulator.app/Contents/Resources/roms/Briel/vicious.bin
echo "Copied Vicious ROM image to OpenEmulator"

echo "Building romburner program: romburner"

cc65 -O -t replica1 romburner.c
ca65 romburner.s
ca65 romburnerio.s
ld65 -o romburner -m romburner.map -C ld_romburner.cfg romburnerio.o romburner.o replica1.lib

rm -f romburner.map
rm -f romburner.s

echo "Creating self burning installation app: VICIOUSPROMMER"
rm -f VICIOUSPROMMER
touch VICIOUSPROMMER
cat romburner > VICIOUSPROMMER
cat vicious >> VICIOUSPROMMER


rm -f *.o

declare -i f
f=`hexdump -v vicious | grep "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00" |wc -l`
declare -i t
t=`hexdump -v vicious |wc -l`
declare -i p
p=$f*100/$t

echo "ROM space free: $p%"
