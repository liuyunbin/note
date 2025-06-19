
year=2024

cat $year-*.csv | sort -k 1,3 > $year.csv

mv $year-*.csv old
