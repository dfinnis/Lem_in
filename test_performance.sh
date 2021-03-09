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
	while [ $count -lt $case ]
	do
		target=$(./generator $MAP > 1 && cat 1 | grep "#Here" | cut -d ' ' -f 8 | head -n 1)
		real=$(./lem-in -t < 1 | tail -n 2 | head -n 1 | cut -d ' ' -f 2)
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

	# echo $sum
	# echo $count
	mean=$(($sum / $count))

	echo "turns taken - required:"
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
	echo

	# echo "$(time ./lem-in -t < 1 | tail -n 1)"
	rm 1
}

#### -- Maps -- ####
unit_test --flow-one
unit_test --flow-ten
unit_test --flow-thousand
unit_test --big
unit_test --big-superposition
