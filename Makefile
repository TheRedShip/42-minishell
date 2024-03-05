# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/24 14:17:35 by rgramati          #+#    #+#              #
#    Updated: 2024/03/06 00:31:24 by rgramati         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLACK		=	\033[30;49;3m
RED			=	\033[31;49;3m
GREEN		=	\033[32;49;3m
YELLOW		=	\033[33;49;3m
BLUE		=	\033[34;49;3m
MAGENTA		=	\033[35;49;3m
CYAN		=	\033[36;49;3m
WHITE		=	\033[37;49;3m

BBLACK		=	\033[30;49;3;1m
BRED		=	\033[31;49;3;1m
BGREEN		=	\033[32;49;3;1m
BYELLOW		=	\033[33;49;3;1m
BBLUE		=	\033[34;49;3;1m
BMAGENTA	=	\033[35;49;3;1m
BCYAN		=	\033[36;49;3;1m
BWHITE		=	\033[37;49;3;1m

RESET		=	\033[0m

LINE_CLR	=	\33[2K\r

FILE	=	$(shell ls -lR srcs/ | grep -F .c | wc -l)
CMP		=	1

NAME        := minishell

LFT_DIR 	:= ./libft

LFT			:= $(LFT_DIR)/libft.a

SRCS_DIR	:=	srcs

OBJS_DIR	:=	.objs


SRC_DATA	:=	data_structures/constructors.c		\
				data_structures/s_envvar.c			\
				data_structures/s_envvar_utils.c	\
				data_structures/s_token.c			\
				data_structures/s_node.c			\
				data_structures/s_command.c			\
				data_structures/s_pid.c				\
				data_structures/s_pipes.c			\
				data_structures/s_redir.c			\
				data_structures/s_executer.c

SRC_BUILTIN :=	builtins/ft_cd.c					\
				builtins/ft_echo.c					\
				builtins/ft_exit.c					\
				builtins/ft_pwd.c					\
				builtins/ft_env.c					\
				builtins/ft_export.c				\
				builtins/ft_unset.c					\
				builtins/ft_builtins_utils.c

SRC_PARSING	:=  parsing/ft_tree_build.c				\
				parsing/ft_parse_dollars.c			\
				parsing/ft_parse_quotes.c			\
				parsing/ft_parse_wildcards.c		\
				parsing/ft_token_auth.c				\
				parsing/ft_tokenizer.c				\
				parsing/ft_parsing_utils.c

SRC_EXEC	:=	execution/ft_manage_close.c			\
				execution/ft_manage_files.c			\
				execution/ft_manage_heredocs.c 		\
				execution/ft_manage_commands.c		\
				execution/ft_exec_binops.c			\
				execution/ft_exec_builtins.c		\
				execution/ft_exec_command.c			\
				execution/ft_exec_pipeline.c		\
				execution/ft_exec_utils.c

SRC_PROMPT	:=  prompt/prompt.c						\
				prompt/ft_manage_dquote.c			\
				prompt/ft_holder.c

SRC_SETUP	:=  utils/ft_setup_env.c				\
				utils/ft_handle_signals.c			\
				utils/ft_error_handling.c

ALL_SRCS	:=	$(SRC_DATA) 						\
				$(SRC_BUILTIN)						\
				$(SRC_PARSING)						\
				$(SRC_PROMPT)						\
				$(SRC_EXEC)							\
				$(SRC_SETUP)						\
				global.c							\
				minishell.c
				
SRCS		:=	$(ALL_SRCS:%=$(SRCS_DIR)/%)

OBJS		:=	$(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

HEADERS		:=	includes/minishell.h 				\
				includes/ft_enumerates.h			\
				includes/ft_data_structures.h 		\
				includes/ft_parsing.h				\
				includes/ft_builtins.h 				\
				includes/ft_file_manager.h			\
				includes/ft_execution.h

CC          := cc

CFLAGS      := -g -Wall -Wextra -Werror

IFLAGS	    := -I $(LFT_DIR)/includes -I ./includes


RM          := rm -rf

MAKEFLAGS   += --no-print-directory

DIR_DUP     = mkdir -p $(@D)

# RULES ********************************************************************** #

all: $(NAME)

$(NAME): $(LFT) $(OBJS) $(HEADERS)
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) $(LFT_DIR)/libft.a -o $(NAME) -lreadline
	@printf "$(LINE_CLR)  ⭐$(BWHITE) $(NAME):\t PROJECT READY !$(RESET)\n\n"

$(LFT):
	@make -C $(LFT_DIR)

$(OBJS_DIR)/%.o: %.c
	@$(DIR_DUP)
	if [ $(CMP) -eq '1' ]; then \
		printf "\n"; \
	fi;
	printf "$(LINE_CLR)$(WHITE)  🔄 $(NAME):\t$(CMP)/$(FILE) \t$(BWHITE)$<$(RESET) $(GREEN)compiling...$(RESET)"
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $^
	@$(eval CMP=$(shell echo $$(($(CMP)+1))))
	if [ $(CMP) -gt $(FILE) ]; then \
		printf "$(LINE_CLR)$(WHITE)  🔄 $(NAME): $$(($(CMP)-1))/$(FILE)\n$(LINE_CLR)$(BGREEN)  ✅ Compilation done !$(RESET)\n"; \
	fi \

clean:
	@printf "\n$(BWHITE)  🚫 $(NAME):\t$(BRED) .o files deleted.$(RESET)\n"
	@$(RM) $(OBJS)

dclean: clean
	@printf "$(BWHITE)  🚫 $(NAME):\t$(BRED) objs dir deleted.$(RESET)\n"
	@$(RM) $(OBJS_DIR)

fclean: dclean
	@printf "$(BWHITE)  🚫 $(NAME):\t$(BRED) binary deleted.$(RESET)\n"
	@$(RM) $(NAME)
	@$(MAKE) -C $(LFT_DIR) fclean

re:
	@$(MAKE) fclean
	@$(MAKE) all

# **************************************************************************** #

.PHONY: all clean fclean dclean re
.SILENT:
