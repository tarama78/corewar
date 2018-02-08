# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynacache <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 10:53:49 by ynacache          #+#    #+#              #
#    Updated: 2018/02/08 18:04:12 by tnicolas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

FILES = main.c\
		ft_parse_file.c\
		ft_handle_line.c\
		ft_label.c\
		ft_lst_add_end.c\
		free_content.c\
		binary.c\
		ft_error.c\
		op.c

HFILES = includes/corewar.h \
		 includes/op.h \
		 $(LIBFT_DIR)includes/libft.h \

LIBFT_DIR = ../libft/
LIBFT = $(LIBFT_DIR)libft.a
LIBFT_LIB = -L $(LIBFT_DIR) -lft

CC = gcc
CFLAGS = -Wall -Wextra -g#########Werror

OBJS_DIR = objs/
SRCS_DIR = srcs/

INC_DIR =	includes/ \
			$(LIBFT_DIR)includes/ \

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

ARG = "ex.s"

START = @printf $(GREEN)$(BOLD)"ASM\n--------------------\n"$(NORMAL)
END = @printf $(GREEN)$(BOLD)"--------------------\n"$(NORMAL)

all:
	@make -C $(LIBFT_DIR)
	$(START)
	@make $(NAME)
	$(END)

$(NAME): $(OBJS_DIR) $(OBJS) $(LIBFT)
	@printf $(CYAN)"-> create program : $(NAME)\n"$(NORMAL)
	@$(CC) -o $(NAME) $(OBJS) $(INC) $(CFLAGS) $(LIBFT_LIB)

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
	@printf $(MAGENTA)$(BOLD)"EXEC ASM\n--------------------\n"$(NORMAL)
	@printf $(ARG)":\n"$(BLUE)$(BOLD)
	@cat $(ARG)
	@printf $(NORMAL)"\nresult:\n"
	@./$(NAME) $(ARG)
	@printf $(MAGENTA)$(BOLD)"--------------------\n"$(NORMAL)

open:
	@vim +Line $(SRCS) $(HFILES) Makefile

norm:
	@printf $(BLUE)$(BOLD)"NORME ASM\n--------------------\n"$(NORMAL)
	@norminette $(SRCS) $(HFILES)
	@printf $(BLUE)$(BOLD)"--------------------\n"$(NORMAL)

.PHONY: all clean fclean re exec open
