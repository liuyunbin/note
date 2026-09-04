#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@";          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@"; exit -1; }

sql_path=$(pwd)/gov-mca-sql
csv_path=$(pwd)/gov-mca-csv

database_name=testdb # 需要在数据库中添加库 testdb

mkdir -p $sql_path &> /dev/null

cd $csv_path
for file_name_csv in *.csv; do
    log_info "handle $file_name_csv..."
    year=${file_name_csv/.*}
    file_name_sql=$sql_path/${file_name_csv/csv/sql}

    cat > $file_name_sql <<'EOF'
drop table if exists `gov_mca`;
create table `gov_mca` (
  `code` bigint      not null comment '区划代码',
  `name` varchar(40) not null comment '名称',
   primary key (`code`),
   index `name` (`name`)
);

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

    mysql -D $database_name < $file_name_sql
    mysqldump $database_name gov_mca_$year > $file_name_sql
done

log_info "完成"

