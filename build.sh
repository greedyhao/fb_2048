#!/bin/bash

arm-linux-gcc *.c -o 2048 -lpthread

sh ./upload.sh 2048
