#!/bin/bash

set -ueo pipefail

mkdir -p code-name-gov-stats-json-all

cd code-name-gov-stats-json-all

if [[ -f *.tgz ]]; then
    for v in *.tgz; do
        tar xf $v
    done
fi

cd ..

./get_code_name_gov_stats_json.py all_data
