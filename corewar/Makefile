# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynacache <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 10:53:49 by ynacache          #+#    #+#              #
#    Updated: 2018/02/10 17:46:14 by bcozic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

FILES = main.c\
		ft_is_int.c\
		parse_args.c\
		load_players.c\
		load_memory.c\
		lst_process.c\
		commands.c\
		init_command.c\
		load_value.c\
		write_value.c\
		instruc.c\
		operation.c\
		game_turn.c\
		ncurses/init.c\
		ncurses/color.c\
		ncurses/print.c\
		ncurses/free_nc.c\
		../../commun/srcs/op.c\

HFILES = includes/corewar.h \
		 ../commun/includes/op.h \
		 $(LIBFT_DIR)includes/libft.h \

LIBFT_DIR = ../libft/
LIBFT = $(LIBFT_DIR)libft.a
LIBFT_LIB = -L $(LIBFT_DIR) -lft

CC = gcc
CFLAGS = -Wall -Wextra -g#########Werror

OBJS_DIR = objs/
SRCS_DIR = srcs/

INC_DIR =	includes/ \
			../commun/includes/ \
			$(LIBFT_DIR)includes/

INC := $(addprefix -I , $(INC_DIR))
SRCS := $(addprefix $(SRCS_DIR), $(FILES))
OBJS := $(addprefix $(OBJS_DIR), $(FILES:.c=.o))

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

ARG = "ex.s -n"

START = @printf $(GREEN)$(BOLD)"COREWAR\n--------------------\n"$(NORMAL)
END = @printf $(GREEN)$(BOLD)"--------------------\n"$(NORMAL)

all:
	@make -C $(LIBFT_DIR)
	$(START)
	@make $(NAME)
	$(END)

$(NAME): $(OBJS_DIR) $(OBJS) $(LIBFT)
	@printf $(CYAN)"-> create program : $(NAME)\n"$(NORMAL)
	@$(CC) -o $(NAME) $(OBJS) $(INC) $(CFLAGS) $(LIBFT_LIB) -lncurses -lm

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HFILES)
	@printf $(YELLOW)"-> $<\n"$(NORMAL)
	@$(CC) -c $(INC) $< -o $@ $(CFLAGS)

$(OBJS_DIR):
	@mkdir -p $(dir $(OBJS))

clean:
	@make -C $(LIBFT_DIR) clean
	$(START)
	@printf $(RED)"-x remove .o files\n"$(NORMAL)
	@rm -rf $(OBJS_DIR)
	@rm -rf ../commun/srcs/op.o
	$(END)

fclean: clean
	@make -C $(LIBFT_DIR) cleanlib
	$(START)
	@printf $(RED)"-x remove $(NAME)\n"$(NORMAL)
	@rm -f $(NAME)
	$(END)

re: fclean
	@make

exec:
	@clear
	@make
	@printf $(MAGENTA)$(BOLD)"EXEC COREWAR\n--------------------\n"$(NORMAL)
	@./$(NAME) $(ARG)
	@printf $(MAGENTA)$(BOLD)"--------------------\n"$(NORMAL)

open:
	@vim +Line $(SRCS) $(HFILES) Makefile

norm:
	@printf $(BLUE)$(BOLD)"NORME COREWAR\n--------------------\n"$(NORMAL)
	@norminette $(SRCS) $(HFILES)
	@printf $(BLUE)$(BOLD)"--------------------\n"$(NORMAL)

.PHONY: all clean fclean re exec open
