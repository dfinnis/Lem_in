#### -- Print Header -- ####
printf "\E[H\E[2J"
echo "\x1b[1mLaunching Lem-in Performance Test...\x1B[0m\n"

#### -- unit_test() -- ####
unit_test()
{
	MAP=$1
	echo "\x1b[1m$MAP\x1B[0m"
	case=25
	count=0
	sum=0
	best=4242
	worst=-4242
	sum_time=0
	best_time=420000000000
	worst_time=-420000000000
	while [ $count -lt $case ]
	do
		target=$(./generator $MAP > 1 && cat 1 | grep "#Here" | cut -d ' ' -f 8 | head -n 1)
		start=$(gdate +%s%N)
		real=$(./lem-in -t < 1 | tail -n 2 | head -n 1 | cut -d ' ' -f 2)
		end=$(gdate +%s%N)

		## Time
		runtime=$( echo "($end - $start)" | bc -l )
		if [ $runtime -lt $best_time ]
		then
			best_time=$runtime
		fi
		if [ $runtime -gt $worst_time ]
		then
			worst_time=$runtime
		fi
		sum_time=$(($sum_time + $runtime))

		## Turns
		diff=$(($real - $target))
		if [ $diff -lt $best ]
		then
			best=$diff
		fi
		if [ $diff -gt $worst ]
		then
			worst=$diff
		fi
		sum=$(($sum + $diff))

		count=$(($count + 1))
		echo "\r\x1B[32mPassed: $count/$count\x1B[0m\c"
	done
	count=$(($count - 1))
	echo

	mean=$(($sum / $count))
	mean_time=$(($sum_time / $count))

	## Time decimal places
	mean_int=$( echo "scale=0; $mean_time / 1000000000" | bc -l )
	best_int=$( echo "scale=0; $best_time / 1000000000" | bc -l )
	worst_int=$( echo "scale=0; $worst_time / 1000000000" | bc -l )

	mean_time=$( echo "scale=3; $mean_time / 1000000000" | bc -l )
	best_time=$( echo "scale=3; $best_time / 1000000000" | bc -l )
	worst_time=$( echo "scale=3; $worst_time / 1000000000" | bc -l )

	## turns taken - required
	echo "Turns taken - required:"
	if [ $best -le "0" ]
	then
		echo "\x1B[32mbest:  $best\x1B[0m"
	else
		echo "\x1B[33mbest:  $best\x1B[0m"
	fi
	if [ $mean -le "0" ]
	then
		echo "\x1B[32mmean:  $mean\x1B[0m"
	else
		echo "\x1B[33mmean:  $mean\x1B[0m"
	fi
	if [ $worst -le "0" ]
	then
		echo "\x1B[32mworst: $worst\x1B[0m"
	else
		echo "\x1B[33mworst: $worst\x1B[0m"
	fi

	## Time
	echo "Time:"
	if [ $best_int -le "15" ]
	then
		echo "\x1B[32mbest:  $best_time s\x1B[0m"
	else
		echo "\x1B[33mbest:  $best_time\x1B[0m"
	fi
	if [ $mean_int -le "15" ]
	then
		echo "\x1B[32mmean:  $mean_time s\x1B[0m"
	else
		echo "\x1B[33mmean:  $mean_time\x1B[0m"
	fi
	if [ $worst_int -le "15" ]
	then
		echo "\x1B[32mworst: $worst_time s\x1B[0m"
	else
		echo "\x1B[33mworst: $worst_time\x1B[0m"
	fi
	echo

	rm 1
}

#### -- Maps -- ####
unit_test --flow-one
unit_test --flow-ten
unit_test --flow-thousand
unit_test --big
unit_test --big-superposition
