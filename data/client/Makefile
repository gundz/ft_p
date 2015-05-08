#TYPE: LIB or PROGRAM
TYPE =			PROGAM

NAME =			../../client

SRCS =			\
				main.c \

CC =			gcc

CFLAGS =		-Wall -Werror -Wextra

LIB_NAMES =		-lftsocket -lft
LIB_PATH =		../libft/ ../libftsocket/

#LIB_SUPP =		-lm

SRC_PATH = 		./srcs/
INC_PATH = 		./includes/
OBJ_PATH =		./obj/

OBJ_NAME = $(SRCS:.c=.o)
SRC = $(addprefix $(SRC_PATH), $(SRCS))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIB = $(addprefix -I, $(addsuffix includes, $(LIB_PATH))) $(addprefix -L, $(LIB_PATH))
INC = $(addprefix -I, $(INC_PATH))
LDFLAGS = $(LIB) $(LIB_NAMES)
EMPTY =

all: libs name $(OBJ) done $(NAME)

name :
	@ echo "\033[4;7mCompiling Objects:\033[0m "

done :
	@ echo "\n\033[4m\033[95md\033[93mo\033[32mn\033[96me\033[0m \033[91m!\033[0m\n"

$(NAME): $(OBJ)
	@ echo "\033[4;7mCompiling:\033[0m [$(NAME)]"
ifeq ($(TYPE), LIB)
	@ ar -rc $(NAME) $(OBJ)
	@ ranlib $(NAME)
else
	@ $(CC) $(OBJ) $(LDFLAGS) $(LIB_SUPP) -o $(NAME)
endif
	@ echo "\033[4m\033[95md\033[93mo\033[32mn\033[96me\033[0m \033[91m!\033[0m\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@ echo -n "\033[37;7m+\033[0m"
	@ mkdir -p $(OBJ_PATH) 2> /dev/null
	@ $(CC) $(CFLAGS) $(LIB) $(INC) -c $< -o $@

ifeq ($(LIB_PATH), $(EMPTY))
else
libs:
	@ $(foreach lib, $(LIB_PATH), make -sC $(lib);)
endif

clean:
	@ rm -rf $(OBJ_PATH)
	@ echo "\033[4;7mCleaning:\033[0m [$(NAME)]\n\033[4m\033[95md\033[93mo\033[32mn\033[96me\033[0m \033[91m!\033[0m\n"
ifeq ($(LIB_PATH), $(EMPTY))
else
	@ $(foreach lib, $(LIB_PATH), make clean -sC $(lib);)
endif

fclean: clean
	@ rm -f $(NAME)
	@ echo "\033[4;7mFcleaning:\033[0m [$(NAME)]\033[0m\n\033[4m\033[95md\033[93mo\033[32mn\033[96me\033[0m \033[91m!\033[0m\n"
ifeq ($(LIB_PATH), $(EMPTY))
else
	@ $(foreach lib, $(LIB_PATH), make fclean -sC $(lib);)
endif

re: fclean all

.PHONY: all clean fclean re libs
