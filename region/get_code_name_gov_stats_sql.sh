#!/bin/bash

set -ueo pipefail

path_gcov_stats_sql=$(pwd)/code-name-gov-stats-sql/
mkdir -p $path_gcov_stats_sql

cd code-name-gov-stats-csv

for file_name_csv in *; do
    echo "handle $file_name_csv"
    year=${file_name_csv::-4}
    file_name_sql=${path_gcov_stats_sql}${year}.sql

    cat > $file_name_sql <<'EOF'
DROP TABLE IF EXISTS `gov_stats`;
CREATE TABLE `gov_stats` (
  `code`     bigint  unsigned NOT NULL COMMENT '区划代码',
  `name`     varchar(128)     NOT NULL COMMENT '名称',
  `level`    tinyint          NOT NULL COMMENT '级别1-5,省市县镇村',
  `pcode`    bigint           NOT NULL COMMENT '父级区划代码',
   PRIMARY KEY (`code`),
           KEY `name` (`name`),
           KEY `level` (`level`),
           KEY `pcode` (`pcode`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

LOCK TABLES `gov_stats` WRITE;
EOF

    awk -F, '
        BEGIN {
            str = "INSERT INTO `gov_stats` VALUES "
        }

        {
            if (NR % 1000 == 0) {
                print(str)
                str = "INSERT INTO `gov_stats` VALUES "
            }

            str = str"("$1",'\''"$2"'\'',"$3","$4"),"
        }
        END {
            print(str)
        }
        ' $file_name_csv | sed 's/,$/;/' >> $file_name_sql
    sed -i "s/gov_stats/gov_stats_$year/g" $file_name_sql

    mysql -D testdb < $file_name_sql
    mysqldump testdb gov_stats_$year > $file_name_sql
done

