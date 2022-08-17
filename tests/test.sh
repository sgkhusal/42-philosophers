# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/21 20:10:24 by sguilher          #+#    #+#              #
#    Updated: 2022/08/17 20:49:03 by sguilher         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

PHILO_PATH="../philo/philo"

# Run a specific test if the file name was specified
if [[ $1 ]]; then
	test_lists=(
		$1
	)
else
	test_lists=(
		"errors"
		"should_die"
		"should_not_die"
		"count_eat"
	)
fi

if [[ $1 == "bonus" ]]; then
	PHILO_PATH="../philo/philo_bonus"
fi

BOLD="\e[1m"
YELLOW="\033[0;33m"
GREY="\033[38;5;244m"
PURPLE="\033[1;35m"
BLUE="\033[1;34m"
LIGHT_BLUE="\033[0;36m"
GREEN="\033[38;5;83m"
GREEN2="\033[38;2;34;183;235m"
RED="\033[38;2;222;56;43m"
PINK="\033[38;5;212m"
END="\033[0m"

rm -rf ./outfiles
mkdir ./outfiles

printf $GREEN2
echo "                                                                                           ";
echo " ██████  ██   ██ ██ ██       ██████      ████████ ███████ ███████ ████████ ███████ ██████  ";
echo " ██   ██ ██   ██ ██ ██      ██    ██        ██    ██      ██         ██    ██      ██   ██ ";
echo " ██████  ███████ ██ ██      ██    ██        ██    █████   ███████    ██    █████   ██████  ";
echo " ██      ██   ██ ██ ██      ██    ██        ██    ██           ██    ██    ██      ██   ██ ";
echo " ██      ██   ██ ██ ███████  ██████         ██    ███████ ███████    ██    ███████ ██   ██ ";
echo "                                                                                           ";
echo "                                                                                           ";

for testfile in ${test_lists[*]}; do

	printf $LIGHT_BLUE
	echo "************************************************"
	echo "$testfile test"
	printf "\n$END"

	while read test; do
		((i++))

		printf $YELLOW
		printf "Test %2s: " $i

		$PHILO_PATH $test > ./outfiles/test$i

		if [[ $testfile == "errors" ]]; then
			ERROR=$(cat ./outfiles/test$i)
		else
			DIED_PRINTS=$(cat ./outfiles/test$i | grep died)
		fi
		if [[ $testfile == "count_eat" ]]; then
			EATING_PRINTS=$(cat ./outfiles/test$i | grep eating | wc -l)
			MUST_EAT=$(echo $test | awk '{print $1 * $5}')
		fi

		if [[ $testfile == "errors" ]]; then
			if [ "$ERROR" ]; then
				((ok++))
				printf ✅
				printf "$GREY ./philo $test \n$END"
				printf "error message:\n$ERROR\n"
			else
				printf ❌
				printf "$GREY ./philo $test \n$END"
				printf "$RED Missing error message\n$END"
			fi
		fi

		if [[ $testfile == "should_die" ]]; then
			if [ "$DIED_PRINTS" ]; then
				printf ✅
				((ok++))
			else
				printf ❌
			fi
			printf "$GREY ./philo $test \n$END"
			if [ "$DIED_PRINTS" ]; then
				printf "output:\n$DIED_PRINTS\n"
			fi
		fi

		if [[ $testfile == "should_not_die" ]]; then
			if [ "$DIED_PRINTS" ]; then
				printf ❌
			else
				printf ✅
				((ok++))
			fi
			printf "$GREY ./philo $test \n$END"
			if [ "$DIED_PRINTS" ]; then
				printf "output:\n$DIED_PRINTS\n"
			fi
		fi

		if [[ $testfile == "count_eat" ]]; then
			if [ "$EATING_PRINTS" -ge "$MUST_EAT" ]; then
				if [ "$DIED_PRINTS" ]; then
					printf ❌
					printf "$GREY ./philo $test \n$END"
					printf "output:\n$DIED_PRINTS\n"
				else
					printf ✅
					((ok++))
					printf "$GREY ./philo $test \n$END"
					printf "got:$GREEN $EATING_PRINTS$END eating messages\n"
				fi
			else
				printf ❌
				printf "$GREY ./philo $test \n$END"
				printf "expected at least$RED $MUST_EAT$END eating messages\n"
				printf "got:$RED $EATING_PRINTS$END\n"
				if [ "$DIED_PRINTS" ]; then
					printf "output:\n$DIED_PRINTS\n"
				fi
			fi
		fi
	done < $testfile
	printf "\n"
done

printf $PURPLE
printf $BOLD
echo   $ok/$i
printf $END

if [[ "$ok" == "$i" ]]; then
	echo "🎊 🎊 🎊"
	echo "😎 😎 😎"
	echo "🎉 🎉 🎉"
	exit 0
else
	echo "😭 😭 😭"
	exit 1
fi
