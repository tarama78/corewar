# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/06 19:11:27 by tnicolas          #+#    #+#              #
#    Updated: 2018/02/08 18:03:44 by tnicolas         ###   ########.fr        #
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

exec: all
	@./test.sh

norm:
	@make -C libft norm
	@make -C asm norm
