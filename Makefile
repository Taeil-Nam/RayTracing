NAME=miniRT

SRC_DIR=./src/
OBJ_DIR=./obj/

SRC=$(addprefix $(SRC_DIR), $(FILE))
OBJ=$(addprefix $(OBJ_DIR), $(FILE:.c=.o))


CC=cc
CFLAGS=-Wall -Werror -Wextra
CLIB=-Llibft -lft -Lmlx -lmlx -framework OpenGL -framework Appkit
INC=-Ilibft -Imlx -Iinc

FILE=	main.c				\
		utils/utils_1.c		\
		vec3/vec3_1.c		\
		vec3/vec3_2.c		\
		vec3/vec3_3.c		\
		vec3/vec3_4.c		\
		parser/parser_1.c	\
		parser/parser_2.c	\
		parser/parser_3.c	\
		parser/parser_util.c\
		parser/constructor.c\
		camera.c			\

all : $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(MAKE) -C ./mlx
	$(MAKE) -C ./libft
	@test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/utils
	mkdir -p $(OBJ_DIR)/vec3
	mkdir -p $(OBJ_DIR)/parser
	$(CC) $(CFLAG) -g -c $< -o $@ $(INC)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -g $(CLIB) $(SRC) -o $(NAME) $(INC)
	install_name_tool -change libmlx.dylib mlx/libmlx.dylib $(NAME)

clean :
	rm -rf obj

fclean : clean
	rm -rf	$(NAME)
	$(MAKE) -C ./mlx clean
	$(MAKE) -C ./libft fclean

re : fclean all

.PHONY : all clean fclean re bonus