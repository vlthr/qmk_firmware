#!/bin/sh
# HOW TO:
# 1. Start script to see if it compiles
# 2. Once it prompts you to continue, press FN_x+(top right button on keyboard) to flash the left side (FN_x is the bottom left modifier)
# 3. Once finished, press FN_x+(top left button on keyboard) to flash the right side. (FN_x is the bottom right modifier)

flags=""
if [ ! -z $1 ]; then
	flags="MASTER=right"
fi

sudo echo "Got root..."
make -C ../../../../ ergodox-infinity-vlthr $flags
if [ $? != 0 ]; then
    exit 1
fi
echo "Flashing left hand, Press enter key to continue"
read x
sudo make -C ../../../../ ergodox-infinity-vlthr-dfu-util $flags


make -C ../../../../ ergodox-infinity-vlthr MASTER=right
if [ $? != 0 ]; then
    exit 1
fi
echo "Flashing right hand, Press enter key to continue"
read x
sudo make -C ../../../../ ergodox-infinity-vlthr-dfu-util MASTER=right
