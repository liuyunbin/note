#!/bin/bash

set -ueo pipefail

mkdir -p code-name-gov-stats-json-all

cd code-name-gov-stats-json-all

echo "解压缩..."
if [[ -f *.tgz ]]; then
    for v in *.tgz; do
        tar xf $v
    done
fi

cd ..

./get_code_name_gov_stats_csv.py all_data

mkdir -p code-name-gov-stats-csv-all

echo "压缩..."
cd code-name-gov-stats-csv-all
if [[ -f *.csv ]]; then
    for v in *.csv; do
        tar acf $v.tgz $v
    done
fi

