#!/bin/bash

#set -ueo pipefail

mkdir -p old

year=2025
echo "handle $year..."
cat $year-*.csv | sort -k 1,3 >> $year.csv
mv $year-*.csv old


#for year in {2010..2030}; do
#done

