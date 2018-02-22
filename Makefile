# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnicolas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/06 19:11:27 by tnicolas          #+#    #+#              #
#    Updated: 2018/02/19 16:10:36 by tnicolas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror

NORMAL = "\x1B[0m"
RED = "\x1B[31m"
GREEN = "\x1B[32m"
YELLOW = "\x1B[33m"
BLUE = "\x1B[34m"
MAGENTA = "\x1B[35m"
CYAN = "\x1B[36m"
WHITE = "\x1B[37m"
BOLD = "\e[1m"
LIGHT = "\e[2m"
ITALIC = "\e[3m"
ULINE = "\e[4m"

COR_FILES = **/*.cor

all:
	@make -C asm CFLAGS="$(CFLAGS)"
	@make -C corewar CFLAGS="$(CFLAGS)"

clean:
	@make -C asm clean
	@make -C corewar clean

fclean:
	@make -C asm fclean
	@make -C corewar fclean
	@printf $(GREEN)$(BOLD)"ALL\n--------------------\n"$(NORMAL)
	@printf $(RED)"-x remove *.cor\n"$(NORMAL)
	@rm -rf $(COR_FILES)
	@printf $(GREEN)$(BOLD)"--------------------\n"$(NORMAL)

re:
	@make -C asm fclean
	@make -C corewar fclean
	@make -C asm CFLAGS="$(CFLAGS)"
	@make -C corewar CFLAGS="$(CFLAGS)"

exec: all
	@./test.sh

norm:
	@make -C libft norm
	@make -C asm norm
	@make -C corewar norm

.PHONY: all clean fclean re exec norm
