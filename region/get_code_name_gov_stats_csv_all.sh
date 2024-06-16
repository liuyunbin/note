#!/bin/bash

set -ueo pipefail

cd code-name-gov-stats-json-all
for v in ./*.tgz:
    tar xf $v
cd ..

./get_code_name_gov_stats_json.py all_data

cd code-name-gov-stats-csv-all
for v in ./*.csv:
    tar acf $v.tgz $v

