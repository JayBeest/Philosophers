# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: jcorneli <marvin@codam.nl>                 +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2021/11/30 02:05:25 by jcorneli          #+#    #+#             #
#   Updated: 202#   Updated: 2021/12/15 04:29:23 by jcorneli         ###   ########.fr       #                                                              #
# ************************************************************************** #

NAME = 	philo

SRC_NO_B =	philosopher.c \
			init.c \
			threads.c \
			act.c

SRC_BONUS =	philosopher_bonus.c \
			init_bonus.c \
			act_bonus.c \
			monitor.c \
			child.c

SRC_SHARE =	talk.c \
			talk2.c \
			utils.c \
			timing.c \
			parser.c 


SRC_DIR = src/philo
ifdef BONUS
SRC = $(SRC_BONUS) $(SRC_SHARE)
else
SRC = $(SRC_NO_B) $(SRC_SHARE)
endif

OBJ_DIR	= 	$(SRC_DIR)/obj
INCL = 		-I$(SRC_DIR)/incl
C_FLAGS = 	-Wall -Wextra -Werror -Ofast #-g -fsanitize=thread

OBJ = 		$(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)
	touch src/philo/philosopher_bonus.c

bonus:
	$(MAKE) BONUS=1 all
	touch src/philo/philosopher.c

$(NAME): $(OBJ)
	$(CC) $^ $(C_FLAGS) -o $@

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $< $(C_FLAGS) $(INCL) -c -o $@

clean:
	rm -rf src/philo/obj

fclean: clean
	rm -f $(NAME)

re: clean all
