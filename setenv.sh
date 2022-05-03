#! /bin/bash

# set toolchain path
# export PATH=$PATH:/opt/xtensa-lx106-elf/bin
TOOLCHAIN=/home/wh/Project/03-toolChain
export PATH="$PATH:$TOOLCHAIN/xtensa-lx106-elf/bin"

# set IDF_PATH 
export IDF_PATH="$PWD/components/ESP8266_RTOS_SDK"
