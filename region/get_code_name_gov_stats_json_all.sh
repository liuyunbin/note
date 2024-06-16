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

./get_code_name_gov_stats_json.py all_data

echo "压缩..."
cd code-name-gov-stats-json-all
if [[ -f *.json ]]; then
    for v in *.json; do
        tar acf $v.tgz $v
    done
fi

