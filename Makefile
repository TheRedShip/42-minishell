# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/24 14:17:35 by rgramati          #+#    #+#              #
#    Updated: 2024/01/27 16:11:09 by rgramati         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN	=	\033[38;5;76m
RED		=	\033[38;5;160m
YELLOW	=	\033[38;5;226m
ORANGE	=	\033[38;5;202m
PURPLE	=	\033[38;5;213m
LBLUE	=	\033[38;5;51m
BLUE	=	\033[38;5;117m
INDI	=	\033[38;5;99m
RESET	=	\033[00m

FILE	=	$(shell ls -lR srcs/ | grep -F .c | wc -l)
CMP		=	1

NAME        := minishell

SRCS_DIR	:=	srcs
OBJS_DIR	:=	.objs
LFT_DIR 	:= ./libft

SRC_DATA	:=	data_structures/s_envvar.c data_structures/s_token.c data_structures/s_node.c data_structures/s_command.c data_structures/constructors.c

SRC_BUILTIN :=	builtins/ft_cd.c builtins/ft_echo.c builtins/ft_exit.c builtins/ft_pwd.c builtins/ft_env.c builtins/ft_export.c builtins/ft_unset.c

SRC_PARSING	:=  parsing/parse_quotes.c parsing/logical_parsing.c parsing/utils.c parsing/parse_dollar.c

SRC_PROMPT	:=  prompt/prompt.c prompt/ft_dquotes.c

SRC_SETUP	:=  setup/ft_setup_env.c setup/setup_signals.c

ALL_SRCS	:=	$(SRC_DATA) $(SRC_BUILTIN) $(SRC_PARSING) $(SRC_PROMPT) $(SRC_SETUP) global.c minishell.c
SRCS		:=	$(ALL_SRCS:%=$(SRCS_DIR)/%)

OBJS		:=	$(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

HEADERS		:=	includes/builtins.h includes/minishell.h includes/data_structures.h

CC          := gcc
CFLAGS      := -Wall -Wextra -Werror -g
IFLAGS	    := -I $(LFT_DIR)/includes -I ./includes

RM          := rm -rf
MAKEFLAGS   += --no-print-directory
DIR_DUP     = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) $(LFT_DIR)/libft.a -o $(NAME) -lreadline
	@printf "\r                                                                                       \r"
	@printf "\r$(LBLUE)$(NAME)$(RESET) [ $(LBLUE)$(NAME)$(RESET)      $(GREEN)DONE $(LBLUE)$(RESET)]$(RESET)\n"

$(OBJS_DIR)/%.o: %.c
	@$(DIR_DUP)
	@make -C $(LFT_DIR)
	@printf "$(LBLUE)[$(CMP)$(LBLUE)] $(RESET)Compilation in progress... $(GREEN)$<$(BLUE) [$(RESET)$(CMP)$(BLUE)/$(RESET)$(FILE)$(BLUE)]$(RESET)                        \r"
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $^
	@$(eval CMP=$(shell echo $$(($(CMP)+1))))

clean:
	@printf "\r$(LBLUE)$(NAME)$(RESET) [$(LBLUE) objs files  $(RED)deleted$(RESET) ]$(RESET)\n"
	@$(RM) $(OBJS)

fclean: dclean
	@printf "\r$(LBLUE)$(NAME)$(RESET) [$(LBLUE) $(NAME)   $(RED)deleted$(RESET) ]$(RESET)\n"
	@make -C $(LFT_DIR) fclean
	@$(RM) $(NAME)

dclean: clean
	@printf "\r$(LBLUE)$(NAME)$(RESET) [$(LBLUE) objs dir    $(RED)deleted$(RESET) ]$(RESET)\n"
	@$(RM) $(OBJS_DIR)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean dclean re
.SILENT: