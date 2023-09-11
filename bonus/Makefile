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
		utils/err_utils.c	\
		utils/mlx_utils.c	\
		vec3/vec3_1.c		\
		vec3/vec3_2.c		\
		vec3/vec3_3.c		\
		vec3/vec3_4.c		\
		vec3/vec3_5.c		\
		parser/constructor.c\
		parser/initializer.c\
		parser/init_mat.c	\
		parser/init_obj.c	\
		parser/init_tex.c 	\
		parser/parser_minirt.c\
		parser/parser_world.c\
		parser/parser_util1.c\
		parser/parser_util2.c\
		bvh/bvh.c			\
		bvh/comparator.c	\
		bvh/bvh_utils.c		\
		object/aabb.c		\
		object/sphere.c		\
		object/plane.c		\
		object/cylinder.c	\
		object/cone.c		\
		object/object_utils.c\
		texture/color.c		\
		material/emit.c		\
		material/scatter.c	\
		render/phong.c		\
		render/path.c		\
		render/render.c 	\
		render/camera.c		\
		render/ray.c		\

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
	@test -d $(OBJ_DIR)render || mkdir -p $(OBJ_DIR)render
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