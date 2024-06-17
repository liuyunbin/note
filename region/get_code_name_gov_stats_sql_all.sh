#!/bin/bash

set -ueo pipefail

function log_info() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_warn() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty;          }
function log_erro() { echo -e "$(date +'%Y-%m-%d %H:%M:%S %z') $@" > /dev/tty; exit -1; }

path_gcov_stats_sql=$(pwd)/code-name-gov-stats-sql-all/
mkdir -p $path_gcov_stats_sql

cd code-name-gov-stats-csv-all

log_info "解压缩..."
for v in *; do
    [[ "$v" =~ ^.*\.tgz$ ]] && tar xf $v || true
done

for file_name_csv in *.csv; do
    log_info "handle $file_name_csv..."
    year=${file_name_csv::-4}
    file_name_sql=${path_gcov_stats_sql}${year}.sql

    cat > $file_name_sql <<'EOF'
DROP TABLE IF EXISTS `gov_stats_all`;
CREATE TABLE `gov_stats_all` (
  `code`     bigint  unsigned NOT NULL COMMENT '区划代码',
  `name`     varchar(128)     NOT NULL COMMENT '名称',
  `level`    tinyint          NOT NULL COMMENT '级别1-5,省市县镇村',
  `pcode`    bigint           NOT NULL COMMENT '父级区划代码',
  `category` int              NOT NULL COMMENT '城乡分类',
   PRIMARY KEY (`code`),
           KEY `name` (`name`),
           KEY `level` (`level`),
           KEY `pcode` (`pcode`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

LOCK TABLES `gov_stats_all` WRITE;
EOF

    awk -F, '
        BEGIN {
            str = "INSERT INTO `gov_stats_all` VALUES "
        }

        {
            if (NR % 1000 == 0) {
                print(str)
                str = "INSERT INTO `gov_stats_all` VALUES "
            }

            str = str"("$1",'\''"$2"'\'',"$3","$4","$5"),"
        }
        END {
            print(str)
        }
        ' $file_name_csv | sed 's/,$/;/' >> $file_name_sql
    sed -i "s/gov_stats_all/gov_stats_all_$year/g" $file_name_sql

    mysql -D testdb < $file_name_sql
    mysqldump testdb gov_stats_all_$year > $file_name_sql
done

log_info "压缩..."
cd $path_gcov_stats_sql
if [[ -f *.sql ]]; then
    for v in *.sql; do
        tar acf $v.tgz $v
    done
fi

for v in *; do
    [[ $v =~ ^.*\.sql$ ]] && tar acf $v.tgz $v || true
done

