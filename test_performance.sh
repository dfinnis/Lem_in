echo "performance test -> place the 'generator' in the root and run the script"
echo " "

#one
case=50
count=1
sum=0
while [ $count -lt $(expr $case + 1) ]
do
	echo "\r-- $count/$case --\c"
	arg1=$(./generator --flow-one > 1 && cat 1 | grep "#Here" | cut -d ' ' -f 8 | head -n 1)
	arg2=$(./lem-in -t < 1 | tail -n 2 | head -n 1 | cut -d ' ' -f 2)
	diff=$(($arg2 - $arg1))
	sum=$(($sum + $diff))
	count=$(($count + 1))
done
echo " "
echo "\x1b[1m--flow-one\x1B[0m"
echo "\x1B[32mavg moves diff: $(($sum / $(($count - 1))))\x1B[0m"

#time of one
echo "$(time ./lem-in -t < 1 | tail -n 1)"

#ten
case=50
count=1
sum=0
while [ $count -lt $(expr $case + 1) ]
do
	echo "\r-- $count/$case --\c"
	arg1=$(./generator --flow-ten > 1 && cat 1 | grep "#Here" | cut -d ' ' -f 8 | head -n 1)
	arg2=$(./lem-in -t < 1 | tail -n 2 | head -n 1 | cut -d ' ' -f 2)
	diff=$(($arg2 - $arg1))
	sum=$(($sum + $diff))
	count=$(($count + 1))
done
echo " "
echo "\x1b[1m--flow-ten\x1B[0m"
echo "\x1B[32mavg moves diff: $(($sum / $(($count - 1))))\x1B[0m"

#time of ten
echo "$(time ./lem-in -t < 1 | tail -n 1)"

#thousand
case=50
count=1
sum=0
while [ $count -lt $(expr $case + 1) ]
do
	echo "\r-- $count/$case --\c"
	arg1=$(./generator --flow-thousand > 1 && cat 1 | grep "#Here" | cut -d ' ' -f 8 | head -n 1)
	arg2=$(./lem-in -t < 1 | tail -n 2 | head -n 1 | cut -d ' ' -f 2)
	diff=$(($arg2 - $arg1))
	sum=$(($sum + $diff))
	count=$(($count + 1))
done
echo " "
echo "\x1b[1m--flow-thousand\x1B[0m"
echo "\x1B[32mavg moves diff: $(($sum / $(($count - 1))))\x1B[0m"

#time of thousand
echo "$(time ./lem-in -t < 1 | tail -n 1)"

#big
case=25
count=1
sum=0
while [ $count -lt $(expr $case + 1) ]
do
	echo "\r-- $count/$case --\c"
	arg1=$(./generator --big > 1 && cat 1 | grep "#Here" | cut -d ' ' -f 8 | head -n 1)
	arg2=$(./lem-in -t < 1 | tail -n 2 | head -n 1 | cut -d ' ' -f 2)
	diff=$(($arg2 - $arg1))
	sum=$(($sum + $diff))
	count=$(($count + 1))
done
echo " "
echo "\x1b[1m--big\x1B[0m"
echo "\x1B[32mavg moves diff: $(($sum / $(($count - 1))))\x1B[0m"

#time of big
echo "$(time ./lem-in -t < 1 | tail -n 1)"

#big-superposition
case=25
count=1
sum=0
while [ $count -lt $(expr $case + 1) ]
do
	echo "\r-- $count/$case --\c"
	arg1=$(./generator --big-superposition > 1 && cat 1 | grep "#Here" | cut -d ' ' -f 8 | head -n 1)
	arg2=$(./lem-in -t < 1 | tail -n 2 | head -n 1 | cut -d ' ' -f 2)
	diff=$(($arg2 - $arg1))
	sum=$(($sum + $diff))
	count=$(($count + 1))
done
echo " "
echo "\x1b[1m--big-superposition\x1B[0m"
echo "\x1B[32mavg moves dif: $(($sum / $(($count - 1))))\x1B[0m"

#time of big-superposition
echo "$(time ./lem-in -t < 1 | tail -n 1)"
