#!/bin/bash

set -ueo pipefail

mkdir -p code-name-gov-stats-json-all

cd code-name-gov-stats-json-all
for v in ./*.tgz:
    tar xf $v
cd ..

./get_code_name_gov_stats_json.py all_data
