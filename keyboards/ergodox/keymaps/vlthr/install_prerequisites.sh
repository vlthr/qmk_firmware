#!/bin/bash

sudo pacman -S avr-{binutils,gcc,libc} arm-none-eabi-{binutils,gcc,newlib}
pacaur -S dfu-programmer
