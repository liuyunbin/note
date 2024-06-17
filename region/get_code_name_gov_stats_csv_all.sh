#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@";          }
function log_warn() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@";          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@"; exit -1; }

mkdir -p code-name-gov-stats-json-all

cd code-name-gov-stats-json-all

log_info "解压缩..."
for v in *; do
    [[ "$v" =~ ^.*\.tgz$ ]] && tar xf $v || true
done

cd ..

./get_code_name_gov_stats_csv.py all_data || true

mkdir -p code-name-gov-stats-csv-all

log_info "压缩..."
cd code-name-gov-stats-csv-all
for v in *; do
    [[ $v =~ ^.*\.csv$ ]] && tar acf $v.tgz $v || true
done

