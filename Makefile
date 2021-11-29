NAME = 		philosopher
NO_BONUS =	philosopher.c
DO_BONUS =	pipex_bonus.c
SHARED =	utils.c \
			parser.c

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
