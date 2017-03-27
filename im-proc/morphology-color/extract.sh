#!/bin/bash
path='../data/gear.ppm'

./opening 2 10 $path tmp.ppm
./substract $path tmp.ppm gear-final.ppm
./binarize 127 255 gear-final.ppm gear-final-bin.ppm
