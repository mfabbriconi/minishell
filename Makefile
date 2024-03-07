# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcalabre & mfabbric <marvin@42.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 18:41:13 by pcalabre &        #+#    #+#              #
#    Updated: 2024/02/28 19:47:27 by pcalabre &       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS=-L/Users/pcalabre/.brew/opt/readline/lib
IDFLAGS=-I/Users/pcalabre/.brew/opt/readline/include

PARSER_SRCS = $(wildcard parser/*.c)
BUILTINS_SRCS = $(wildcard builtins/*.c)
EXEC_SRCS = $(wildcard exec/*.c)
LIBFT_SRCS = $(wildcard libft/*.c)

SRCS = main.c utils.c signals.c logic.c $(LIBFT_SRCS) $(BUILTINS_SRCS) $(PARSER_SRCS) $(EXEC_SRCS)
OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))
BUILD_DIR = outputs

define rainbow_print
$(foreach char,$(1),printf "\033[42m$(char) \033[0m")
endef


lmao: $(NAME)
	@$(call rainbow_print,minishell)
	@$(call rainbow_print,COMPILED!)
	@$(call rainbow_print,🤯)
	@echo

all: lmao

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ -lreadline

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)/$(dir $<)
	$(CC) $(CFLAGS) $(IDFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
