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
		utils/utils_2.c		\
		vec3/vec3_1.c		\
		vec3/vec3_2.c		\
		vec3/vec3_3.c		\
		vec3/vec3_4.c		\
		parser/parser_1.c	\
		parser/parser_2.c	\
		parser/parser_3.c	\
		parser/parser_util.c\
		parser/constructor.c\
		bvh/bvh.c			\
		bvh/comparator.c	\
		bvh/bvh_utils.c		\
		object/aabb.c		\
		object/sphere.c		\
		object/plane.c		\
		object/cylinder.c	\
		texture/color.c		\
		material/emit.c		\
		material/scatter.c	\
		camera.c			\
		ray.c				\

all : $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR)
	@test -d $(OBJ_DIR)utils || mkdir -p $(OBJ_DIR)utils
	@test -d $(OBJ_DIR)vec3 || mkdir -p $(OBJ_DIR)vec3
	@test -d $(OBJ_DIR)parser || mkdir -p $(OBJ_DIR)parser
	@test -d $(OBJ_DIR)bvh || mkdir -p $(OBJ_DIR)bvh
	@test -d $(OBJ_DIR)object || mkdir -p $(OBJ_DIR)object
	@test -d $(OBJ_DIR)material || mkdir -p $(OBJ_DIR)material
	@test -d $(OBJ_DIR)texture || mkdir -p $(OBJ_DIR)texture
	$(CC) $(CFLAG) -g -c $< -o $@ $(INC)

$(NAME) : $(OBJ)
	$(MAKE) -C ./mlx
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) $(CLIB) $(OBJ) -o $(NAME) $(INC)
	install_name_tool -change libmlx.dylib mlx/libmlx.dylib $(NAME)

clean :
	rm -rf obj

fclean : clean
	rm -rf	$(NAME)
	$(MAKE) -C ./mlx clean
	$(MAKE) -C ./libft fclean

re : fclean all

.PHONY : all clean fclean re bonus