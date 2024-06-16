#!/bin/bash

set -ueo pipefail

path_gcov_mca_sql=$(pwd)/code-name-gov-mca-sql/
mkdir -p $path_gcov_mca_sql

cd code-name-gov-mca-csv

for file_name_csv in *; do
    echo "handle $file_name_csv"
    year=${file_name_csv::-4}
    file_name_sql=${path_gcov_mca_sql}${year}.sql

    cat > $file_name_sql <<'EOF'
DROP TABLE IF EXISTS `gov_mca`;
CREATE TABLE `gov_mca` (
  `code`     bigint  unsigned NOT NULL COMMENT '区划代码',
  `name`     varchar(128)     NOT NULL COMMENT '名称',
   PRIMARY KEY (`code`),
           KEY `name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

LOCK TABLES `gov_mca` WRITE;
EOF

    awk -F, '
        BEGIN {
            str = "INSERT INTO `gov_mca` VALUES "
        }

        {
            if (NR % 1000 == 0) {
                print(str)
                str = "INSERT INTO `gov_mca` VALUES "
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

