#!/bin/bash

sorted_files=$(find . -type f -name "*.cc" | sort -t'k' -k2,2n)
i=1
for file in $sorted_files; do
  mpic++ -fopenmp -o "output_$i" "$file"
  i=$((i + 1))
done
