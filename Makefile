# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2021/11/30 02:05:25 by jcorneli          #+#    #+#             #
#   Updated: 2021/11/30 02:05:25 by jcorneli         ###   ########.fr       #
#                                                                            #
# ************************************************************************** #

NAME = 		philosopher
NO_BONUS =	philosopher.c
DO_BONUS =
SHARED =	parser.c \
			init.c \
			timing.c \
			utils.c

ifdef BONUS
SRC = $(DO_BONUS) $(SHARED)
else
SRC = $(NO_BONUS) $(SHARED)
endif

SRC_DIR =	src
OBJ_DIR	= 	$(SRC_DIR)/obj
INCL = 		-I$(SRC_DIR)/incl
C_FLAGS = 	-Wall -Wextra -Werror #-g -fsanitize=address

OBJ = 		$(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

bonus:
	$(MAKE) BONUS=1 all

$(NAME): $(OBJ)
	$(CC) $^ $(C_FLAGS) -o $@

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $< $(C_FLAGS) $(INCL) -c -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: clean all
