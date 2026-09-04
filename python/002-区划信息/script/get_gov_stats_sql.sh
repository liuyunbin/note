#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@";          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@"; exit -1; }

path_sql=$(pwd)/gov-stats-sql
path_csv=$(pwd)/gov-stats-csv

database_name=testdb # 需要在数据库中添加库 testdb

mkdir -p $path_sql &> /dev/null

cd $path_csv
for file_name_csv_tgz in *.csv.tgz; do
    year=${file_name_csv_tgz%%.*}
    file_name_csv=${file_name_csv_tgz%.*}
    file_name_sql=${file_name_csv/csv/sql}
    file_name_sql_tgz=${file_name_csv_tgz/csv/sql}
    file_name_sql_abs=$path_sql/$file_name_sql
    file_name_sql_tgz_abs=$path_sql/$file_name_sql_tgz

    log_info "handle $file_name_csv_tgz..."

    if [[ -f $file_name_sql_tgz_abs ]]; then
        log_info "$file_name_sql_tgz 已存在, 解压后存入数据库..."
        [[ -f $file_name_sql_abs ]] || tar xf $file_name_sql_tgz_abs -C $path_sql
        mysql -D $database_name < $file_name_sql_abs
        continue
    fi

    if [[ -f $file_name_sql_abs ]]; then
        log_info "$file_name_sql 已存在, 生成压缩文件, 存入数据库..."
        (cd $path_sql && tar acf $file_name_sql_tgz $file_name_sql)
        mysql -D $database_name < $file_name_sql_abs
        continue
    fi

    log_info "获取 $file_name_sql_tgz..."
    [[ -f $file_name_csv ]] || tar xf $file_name_csv_tgz

    cat > $file_name_sql_abs <<'EOF'
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
);

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
        ' $file_name_csv | sed 's/,$/;/' >> $file_name_sql_abs
    sed -i "s/gov_stats/gov_stats_$year/g" $file_name_sql_abs

    mysql -D $database_name < $file_name_sql_abs
    mysqldump $database_name gov_stats_$year > $file_name_sql_abs
    (cd $path_sql && tar acf $file_name_sql_tgz $file_name_sql)
done

log_info "完成"

