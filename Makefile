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

SHARED =	philosopher.c \
			parser.c \
			init.c \
			timing.c \
			act.c \
			talk.c \
			talk2.c \
			utils.c
DO_BONUS =	monitor.c \
			child.c
NO_BONUS =	threads.c

ifdef BONUS
SRC_DIR = src/philo_bonus
SRC = $(SHARED) $(DO_BONUS)
else
SRC = $(SHARED) $(NO_BONUS)
SRC_DIR = src/philo
$(info )
endif

OBJ_DIR	= 	$(SRC_DIR)/obj
INCL = 		-I$(SRC_DIR)/incl
C_FLAGS = 	-Wall -Wextra -Werror

OBJ = 		$(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)
	@echo
	@echo "\033[32mDone building Philosophers (no bonus)\033[0m"
	@echo
	@touch src/philo_bonus/philosopher.c

ball: $(NAME)
	@echo
	@echo "\033[32mDone building Philosophers (bonus)\033[0m"
	@echo
	@touch src/philo_bonus/philosopher.c

bonus:
	@$(MAKE) BONUS=1 ball
	@touch src/philo/philosopher.c

$(NAME): $(OBJ)
	@echo
	@echo "\033[36mLinking binary:          $@\033[0m"
	@$(CC) $^ $(C_FLAGS) -o $@

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "\033[34mCompiling object file:   $@\033[0m"
	@$(CC) $< $(C_FLAGS) $(INCL) -c -o $@

clean:
	@echo "\033[31mRemoving object files\033[0m"
	@echo
	@rm -rf src/philo/obj
	@rm -rf src/philo_bonus/obj

fclean: clean
	@echo "\033[31mRemoving binary\033[0m"
	@echo
	@rm -f $(NAME)

re: clean all
