# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcozic <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/10 12:19:55 by bcozic            #+#    #+#              #
#    Updated: 2018/02/06 10:37:21 by bcozic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM = asm

CFLAGS = -Wall -Wextra -Werror -Weverything -g

SRC = main.c

OBJ = $(SRC:.c=.o)

SOBJ = $(addprefix obj/, $(OBJ))

LIBFT = ../libft/libft.a

all : obj $(LIBFT) $(ASM)

obj :
	@mkdir obj

$(LIBFT) :
	@make -C ../libft

obj/%.o: srcs/%.c
	@gcc $(CFLAGS) -c $< -o $@ -I ../libft/includes -I includes

$(ASM) : $(SOBJ)
	@gcc -o $(ASM) $(SOBJ) $(LIBFT)
	@echo "ASM OK"

clean : clean_libft
	@rm -f $(SOBJ)
	@echo "Obj deleted"

clean_libft :
	@make -C ../libft clean

fclean_libft : clean_libft
	@rm -f $(LIBFT)

fclean : clean
	@rm -f $(LIBFT)
	@rm -f $(ASM)
	@echo "exe deleted"

re : fclean all
	
.PHONY : all clean clean_libft fclean_libft fclean re
