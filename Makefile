# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2021/11/30 02:05:25 by jcorneli          #+#    #+#             #
#   Updated: 202#   Updated: 2021/12/07 02:30:31 by jcorneli         ###   ########.fr       #                                                              #
# ************************************************************************** #

NAME = 	philo
SRC =	philosopher.c \
		parser.c \
		init.c \
		timing.c \
		threads.c \
		act.c \
		talk.c \
		talk2.c \
		utils.c

ifdef BONUS
SRC_DIR = src/philo_bonus
else
SRC_DIR = src/philo
endif

OBJ_DIR	= 	$(SRC_DIR)/obj
INCL = 		-I$(SRC_DIR)/incl
C_FLAGS = 	-Wall -Wextra -Werror -fsanitize=thread

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
	rm -rf src/philo/obj
	rm -rf src/philo_bonus/obj

fclean: clean
	rm -f $(NAME)

re: clean all
