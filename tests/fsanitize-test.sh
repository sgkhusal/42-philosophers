# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    fsanitize-test.sh                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/21 20:10:24 by sguilher          #+#    #+#              #
#    Updated: 2022/08/18 19:31:11 by sguilher         ###   ########.fr        #
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

printf $GREEN2
echo "                                                                                           ";
echo " ██████  ██   ██ ██ ██       ██████      ████████ ███████ ███████ ████████ ███████ ██████  ";
echo " ██   ██ ██   ██ ██ ██      ██    ██        ██    ██      ██         ██    ██      ██   ██ ";
echo " ██████  ███████ ██ ██      ██    ██        ██    █████   ███████    ██    █████   ██████  ";
echo " ██      ██   ██ ██ ██      ██    ██        ██    ██           ██    ██    ██      ██   ██ ";
echo " ██      ██   ██ ██ ███████  ██████         ██    ███████ ███████    ██    ███████ ██   ██ ";
echo "                                                                                           ";
echo "                                                                                           ";

printf $PINK
echo "Fsanitize test"
printf "\n$END"

rm -rf ./outfiles
mkdir ./outfiles

for testfile in ${test_lists[*]}; do

	printf $LIGHT_BLUE
	echo "************************************************"
	echo "$testfile test"
	printf "\n$END"

	while read test; do
		((i++))

		printf $YELLOW
		printf "Test %2s: $GREY ./philo $test \n$END" $i
		$PHILO_PATH $test > ./outfiles/test$i
		cat ./outfiles/test$i | grep -v "is sleeping" | grep -v "is eating" | grep -v "is thinking" | grep -v "has taken a fork"
	done < $testfile
	printf "\n"
done

printf $END

echo "🍽️  🍽️  🍽️"
echo "🧙 🧙 🧙"
echo "🍻 🍻 🍻"
echo "😴 😴 😴"
echo "🤔 🤔 🤔"

printf "\n"
