#!/bin/bash

read -p "Broj procesa: " proc
read -p "Zadatak: " zad
echo

mpirun -np $proc ./output_$zad