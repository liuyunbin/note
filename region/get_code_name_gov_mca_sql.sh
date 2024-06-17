#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@";          }
function log_warn() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@";          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@"; exit -1; }

path_gcov_mca_sql=$(pwd)/code-name-gov-mca-sql/
mkdir -p $path_gcov_mca_sql

cd code-name-gov-mca-csv

for file_name_csv in *; do
    log_info "handle $file_name_csv"
    year=${file_name_csv::-4}
    file_name_sql=${path_gcov_mca_sql}${year}.sql

    cat > $file_name_sql <<'EOF'
drop table if exists `gov_mca`;
create table `gov_mca` (
  `code` bigint      not null comment '区划代码',
  `name` varchar(40) not null comment '名称',
   primary key (`code`),
   index `name` (`name`)
) engine=innodb default charset=utf8mb4 collate=utf8mb4_unicode_ci;

lock tables `gov_mca` write;
EOF

    awk -F, '
        BEGIN {
            str = "insert into `gov_mca` values "
        }

        {
            if (NR % 1000 == 0) {
                print(str)
                str = "insert into `gov_mca` values "
            }

            str = str"("$1",'\''"$2"'\''),"
        }
        END {
            print(str)
        }
        ' $file_name_csv | sed 's/,$/;/' >> $file_name_sql
    sed -i "s/gov_mca/gov_mca_$year/g" $file_name_sql

    mysql -D testdb < $file_name_sql
    mysqldump testdb gov_mca_$year > $file_name_sql
done

