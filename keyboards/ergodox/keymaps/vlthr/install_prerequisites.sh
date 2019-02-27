#!/bin/bash

sudo pacman -S avr-{binutils,gcc,libc} arm-none-eabi-{binutils,gcc,newlib} zenity
pacaur -S dfu-programmer
