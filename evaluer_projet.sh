#!/bin/bash
make clean
make
for file in ../pgm_de_test/*
do
    ./analyser $file >> resultats.csv
done
