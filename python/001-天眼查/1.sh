

for year in {2010..2030}; do
    echo -n "handle $year..."
    if [[ -f $year-*.csv ]]; then
        cat $year-*.csv | sort -k 1,3 >> $year.csv
        mv $year-*.csv old
        echo "done"
    else
        echo "skip"
    fi
done

