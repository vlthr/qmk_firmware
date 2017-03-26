#!/bin/sh

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
