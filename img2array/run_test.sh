#!/bin/bash

rm img2array
rm array2img
rm *.o

gcc -c img2array.c
gcc -c array2img.c
gcc img2array.o -o img2array
gcc array2img.o -o array2img




