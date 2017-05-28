#!/bin/sh
# HOW TO:
# 1. Start script to see if it compiles
# 2. Once it prompts you to continue, press FN_x+(top right button on keyboard) to flash the left side (FN_x is the bottom left modifier)
# 3. Once finished, press FN_x+(top left button on keyboard) to flash the right side. (FN_x is the bottom right modifier)


sudo echo "Got root..."
cd ../../../../ 
docker run -e keymap=vlthr -e subproject=infinity -e keyboard=ergodox --rm -v $('pwd'):/qmk:rw edasque/qmk_firmware
if [ $? != 0 ]; then
    exit 1
fi
echo "Flashing left hand..."
if zenity --question --text "Are you ready to flash the left hand?"; then
    sudo dfu-util -D ergodox_infinity_vlthr.hex
fi

docker run -e keymap=vlthr -e subproject=infinity -e keyboard=ergodox -e MASTER=right --rm -v $('pwd'):/qmk:rw edasque/qmk_firmware
if [ $? != 0 ]; then
    exit 1
fi
echo "Flashing right hand..."
if zenity --question --text "Are you ready to flash the right hand?"; then
    sudo dfu-util -D ergodox_infinity_vlthr.hex
fi
