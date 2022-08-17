# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    socrates.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/17 21:33:34 by sguilher          #+#    #+#              #
#    Updated: 2022/08/17 21:54:37 by sguilher         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

cd ../
git clone https://github.com/nesvoboda/socrates
cd socrates
#pip3 install -r requirements.txt
python3 socrates.py ../
python3 delay_o_meter.py
