#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@";          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@"; exit -1; }

for file_name_csv in ./gov-stats-*.csv; do
    log_info "handle $file_name_csv..."
    year=${file_name_csv:12:4}
    file_name_sql=${file_name_csv/csv/sql}

    cat > $file_name_sql <<'EOF'
drop table if exists `gov_stats`;
create table `gov_stats` (
  `code`     bigint      not null comment '区划代码',
  `name`     varchar(40) not null comment '名称',
  `level`    tinyint     not null comment '级别1-5,省市县镇村',
  `province` bigint      not null comment '省代码',
  `city`     bigint      not null comment '市代码',
  `county`   bigint      not null comment '区县代码',
  `town`     bigint      not null comment '乡镇代码',
  `category` int         not null comment '城乡分类',
   primary key (`code`),
   index `name`     (`name`),
   index `level`    (`level`),
   index `province` (`province`),
   index `city`     (`city`),
   index `county`   (`county`),
   index `town`     (`town`),
   index `category` (`category`)
) engine=innodb default charset=utf8mb4 collate=utf8mb4_unicode_ci;

lock tables `gov_stats` write;
EOF

    awk -F, '
        BEGIN {
            str = "insert into `gov_stats` values "
        }

        {
            if (NR % 1000 == 0) {
                print(str)
                str = "insert into `gov_stats` values "
            }

            str = str"("$1",'\''"$2"'\'',"$3","$4","$5","$6","$7","$8"),"
        }
        END {
            print(str)
        }
        ' $file_name_csv | sed 's/,$/;/' >> $file_name_sql
    sed -i "s/gov_stats/gov_stats_$year/g" $file_name_sql

    mysql -D testdb < $file_name_sql
    mysqldump testdb gov_stats_$year > $file_name_sql
done

