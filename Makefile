# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/06 19:11:27 by tnicolas          #+#    #+#              #
#    Updated: 2018/02/09 15:37:21 by tnicolas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@make -C asm
	@make -C corewar

clean:
	@make -C asm clean
	@make -C corewar clean

fclean:
	@make -C asm fclean
	@make -C corewar fclean

re:
	@make -C asm fclean
	@make -C corewar fclean
	@make -C asm
	@make -C corewar

exec: all
	@./test.sh

norm:
	@make -C libft norm
	@make -C asm norm
	@make -C corewar norm

.PHONY: all clean fclean re exec norm
