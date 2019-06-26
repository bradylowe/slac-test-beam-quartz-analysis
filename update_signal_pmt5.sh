

cp signal_by_hv_and_pmt.csv signal_by_hv_and_pmt.csv.backup
while read line ; do
	if [ $(echo ${line} | awk -F, '$1==5') ] ; then
		voltage=$(echo ${line} | awk -F, '{print $2}')
		old_val=$(echo ${line} | awk -F, '{print $3}')
		new_val=$(root -l -b -q "pmt5_signal.c(${voltage})")
		new_val=$(echo ${new_val} | awk '{print $NF}')
		sed -i "s/5,${voltage},${old_val}/5,${voltage},${new_val}/" signal_by_hv_and_pmt.csv
	fi
done < signal_by_hv_and_pmt.csv

sed -i "s/f//" signal_by_hv_and_pmt.csv
