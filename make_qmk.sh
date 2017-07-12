#!/bin/bash
docker run -e keymap=vlthr -e subproject=infinity -e keyboard=ergodox --rm -v $('pwd'):/qmk:rw edasque/qmk_firmware
