#!/bin/bash

read -p "Broj procesa: " proc
read -p "Zadatak: " zad

if ! [[ $proc =~ ^[0-9]+$ ]]; then
    echo "Broj procesa mora biti broj veci od 0"
    exit 1
fi

echo

mpirun -np $proc ./output_$zad