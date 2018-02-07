# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/06 19:11:27 by tnicolas          #+#    #+#              #
#    Updated: 2018/02/07 21:26:42 by tnicolas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@make -C asm

clean:
	@make -C asm clean

fclean:
	@make -C asm fclean

re:
	@make -C asm re

exec:
	@./test.sh
