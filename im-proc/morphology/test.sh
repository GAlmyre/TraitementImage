#!/bin/bash

./dilatation 1 2 ../data/lena-gray.ppm a.ppm
./erosion 1 2 ../data/lena-gray.ppm b.ppm
./substract a.ppm b.ppm c.ppm
./substract d.ppm ../data/lena-gray.ppm e.ppm
./substract e.ppm ../data/lena-gray.ppm f.ppm
pvisu a.ppm b.ppm c.ppm d.ppm e.ppm f.ppm
