
if [ $# -gt 0 ] ; then
	run_list=$*
else
	run_list=$(more +9 values_by_run.csv | awk -F',' '{print $1}')
fi

for run_num in ${run_list} ; do
	detector=$(awk -F, '$1==val{print $4}' val=${run_num} values_by_run.csv)
	signal=$(awk -F, '$1==val{print $7}' val=${run_num} values_by_run.csv)
	if [[ ${signal} == "-1" ]] ; then
		root -l "pmt_analyzer_pedestal.c(${run_num})"
	elif [[ ${signal} == "-2" ]] ; then
		continue
	elif [[ ${detector} == "sam" ]] ; then
		continue
	elif [[ ${detector} == "tandem" ]] ; then
		root -l "pmt_analyzer_tandem.c(${run_num})"
	elif [[ ${detector:3:4} == "s" ]] ; then 
		root -l "pmt_analyzer_stack.c(${run_num})"
	else
		root -l "pmt_analyzer.c(${run_num})"
	fi
	sleep 0.5
done