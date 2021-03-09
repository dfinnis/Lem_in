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
	while [ $count -lt $(expr $case + 1) ]
	do
		echo "\r-- $count/$case --\c"
		arg1=$(./generator $MAP > 1 && cat 1 | grep "#Here" | cut -d ' ' -f 8 | head -n 1)
		arg2=$(./lem-in -t < 1 | tail -n 2 | head -n 1 | cut -d ' ' -f 2)
		diff=$(($arg2 - $arg1))
		# echo $diff ##########################
		sum=$(($sum + $diff))
		count=$(($count + 1))
	done
	count=$(($count - 1))
	echo

	# echo $sum
	# echo $count
	mean=$(($sum / $count))
	# echo "\x1B[32mavg moves diff: $mean\x1B[0m"

	if [ $mean -le "0" ]
	then
		echo "\x1B[32mavg moves diff: $mean\x1B[0m"
	else
		echo "\x1B[33mavg moves diff: $mean\x1B[0m"
	fi

	time
	echo "$(time ./lem-in -t < 1 | tail -n 1)"
	rm 1
}

#### -- Maps -- ####
unit_test --flow-one
unit_test --flow-ten
unit_test --flow-thousand
unit_test --big
unit_test --big-superposition
