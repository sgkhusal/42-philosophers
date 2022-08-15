#!/bin/bash
# make -C philo_bonus && clear
# exe=./philo_bonus/philo_bonus
make -C ../philo && clear
exe=../philo/philo

tests=10
color1="\e[41;30m"
color2="\e[1;31m"
color3="\e[42;30m"
color4="\e[1;32m"
reset="\e[0m"

x=1
time=0.1
printf $color1
echo -e "2 100 200 200 should die"
printf $reset
while [ $x -le $tests ]
do
	printf $color2
    echo -e "Test: $x"
    printf $reset
	$exe 2 100 200 200 | grep die
	sleep $time
	x=$(( $x + 1 ))
done

echo

x=1
time=0.1
printf $color1
echo -e "2 150 360 100 should die"
printf $reset
while [ $x -le $tests ]
do
	printf $color2
    echo -e "Test: $x"
    printf $reset
	$exe 2 150 360 100 | grep die
	sleep $time
	x=$(( $x + 1 ))
done

echo

x=1
time=0.1
printf $color1
echo -e "2 150 200 100 should die"
printf $reset
while [ $x -le $tests ]
do
	printf $color2
    echo -e "Test: $x"
    printf $reset
	$exe 2 150 200 100 | grep die
	sleep $time
	x=$(( $x + 1 ))
done

echo

x=1
time=0.1
printf $color1
echo -e "1 400 100 100 7 should die"
printf $reset
while [ $x -le $tests ]
do
	printf $color2
    echo -e "Test: $x"
    printf $reset
	$exe 1 400 100 100 7 | grep die
	sleep $time
	x=$(( $x + 1 ))
done

echo

x=1
time=0.1
printf $color3
echo -e "4 210 100 100 7 not die"
printf $reset
while [ $x -le $tests ]
do
	printf $color4
    echo -e "Test: $x"
    printf $reset
	$exe 4 210 100 100 7 | grep die
	sleep $time
	x=$(( $x + 1 ))
done

echo

x=1
time=0.1
printf $color1
echo -e "1 800 200 200 7 should die"
printf $reset
while [ $x -le $tests ]
do
	printf $color2
    echo -e "Test: $x"
    printf $reset
	$exe 1 800 200 200 7 | grep die
	sleep $time
	x=$(( $x + 1 ))
done

echo

x=1
time=0.1
printf $color3
echo -e "5 800 200 200 7 not die"
printf $reset
while [ $x -le $tests ]
do
	printf $color4
    echo -e "Test: $x"
    printf $reset
	$exe 5 800 200 200 7 | grep die
	sleep $time
	x=$(( $x + 1 ))
done

echo

x=1
time=0.1
printf $color1
echo -e "4 310 200 100 7 should die"
printf $reset
while [ $x -le $tests ]
do
	printf $color2
    echo -e "Test: $x"
    printf $reset
	$exe 4 310 200 100 7 | grep die
	sleep $time
	x=$(( $x + 1 ))
done

echo

x=1
time=0.1
printf $color3
echo -e "5 400 100 100 7 not die"
printf $reset
while [ $x -le $tests ]
do
	printf $color4
    echo -e "Test: $x"
    printf $reset
	$exe 5 400 100 100 7 | grep die
	sleep $time
	x=$(( $x + 1 ))
done

echo

x=1
time=0.1
printf $color1
echo -e "5 200 100 100 7 should die"
printf $reset
while [ $x -le $tests ]
do
	printf $color2
    echo -e "Test: $x"
    printf $reset
	$exe 5 200 100 100 7 | grep die
	sleep $time
	x=$(( $x + 1 ))
done

echo

x=1
time=0.1
printf $color3
echo -e "3 400 100 100 7 not die"
printf $reset
while [ $x -le $tests ]
do
	printf $color4
    echo -e "Test: $x"
    printf $reset
	$exe 3 400 100 100 7 | grep die
	sleep $time
	x=$(( $x + 1 ))
done

echo

x=1
time=0.1
printf $color1
echo -e "3 200 100 100 7 should die"
printf $reset
while [ $x -le $tests ]
do
	printf $color2
    echo -e "Test: $x"
    printf $reset
	$exe 3 200 100 100 7 | grep die
	sleep $time
	x=$(( $x + 1 ))
done

echo

x=1
time=0.1
printf $color3
echo -e "4 410 200 200 7 not die"
printf $reset
while [ $x -le $tests ]
do
	printf $color4
    echo -e "Test: $x"
    printf $reset
	$exe 4 410 200 200 7 | grep die
	sleep $time
	x=$(( $x + 1 ))
done

echo

x=1
time=0.1
printf $color1
echo -e "4 399 200 200 7 should die"
printf $reset
while [ $x -le $tests ]
do
	printf $color2
    echo -e "Test: $x"
    printf $reset
	$exe 4 399 200 200 7 | grep die
	sleep $time
	x=$(( $x + 1 ))
done

echo

make -C ../philo fclean
make -C ../philo_bonus fclean