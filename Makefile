NAME = miniRT

CC = cc
CFLAGS = -Wall -Werror -Wextra
CLIB = -L./libft -lft -L./mlx -lmlx -framework OpenGL -framework Appkit

SRC_DIR = ./mandatory/src/
SRC_BONUS_DIR = ./bonus/src/

INC_DIR = ./mandatory/inc/
INC_BONUS_DIR = ./bonus/inc/
INC_LIBFT = ./libft
INC_MLX = ./mlx

LIBFT = ./libft/libft.a
MLX = ./mlx/libmlx.dylib

OBJ_DIR = ./obj/

FILE=	main.c					\
		utils/utils_1.c			\
		utils/utils_2.c			\
		utils/utils_3.c			\
		utils/mlx_utils.c		\
		utils/memory_free.c		\
		vec3/vec3_1.c			\
		vec3/vec3_2.c			\
		vec3/vec3_3.c			\
		vec3/vec3_4.c			\
		parser/parser_1.c		\
		parser/parser_2.c		\
		parser/parser_3.c		\
		parser/parser_util_1.c	\
		parser/parser_util_2.c	\
		parser/constructor.c	\
		bvh/bvh.c				\
		bvh/comparator.c		\
		bvh/bvh_utils.c			\
		object/aabb.c			\
		object/sphere.c			\
		object/plane.c			\
		object/cylinder.c		\
		object/object_utils.c	\
		texture/color.c			\
		material/emit.c			\
		material/scatter.c		\
		render/phong.c			\
		render/render.c 		\
		camera.c				\
		ray.c					\

BONUS_FILE=	main_bonus.c				\
			utils/utils_1_bonus.c		\
			utils/utils_2_bonus.c		\
			utils/err_utils_bonus.c		\
			utils/mlx_utils_bonus.c		\
			utils/memory_free_bonus.c	\
			vec3/vec3_1_bonus.c			\
			vec3/vec3_2_bonus.c			\
			vec3/vec3_3_bonus.c			\
			vec3/vec3_4_bonus.c			\
			vec3/vec3_5_bonus.c			\
			parser/constructor_bonus.c	\
			parser/init_hittable_bonus.c\
			parser/init_camera_bonus.c 	\
			parser/init_world_bonus.c	\
			parser/init_mat_bonus.c		\
			parser/init_obj_1_bonus.c	\
			parser/init_obj_2_bonus.c	\
			parser/init_tex_bonus.c 	\
			parser/parser_minirt_bonus.c\
			parser/parser_util1_bonus.c	\
			parser/parser_util2_bonus.c	\
			bvh/bvh_bonus.c				\
			bvh/comparator_bonus.c		\
			bvh/bvh_utils_bonus.c		\
			object/aabb_bonus.c			\
			object/sphere_bonus.c		\
			object/plane_bonus.c		\
			object/cylinder_bonus.c		\
			object/cone_bonus.c			\
			object/object_utils_bonus.c	\
			object/get_uv_bonus.c 		\
			texture/color_bonus.c		\
			material/emit_bonus.c		\
			material/scatter_bonus.c	\
			render/phong_bonus.c		\
			render/path_bonus.c			\
			render/render_bonus.c 		\
			render/ray_bonus.c			\
			render/aa_bonus.c			\
			thread/thread_bonus.c		\

SRCS = $(addprefix $(SRC_DIR), $(FILE))
BONUS_SRCS = $(addprefix $(SRC_BONUS_DIR), $(BONUS_FILE))
OBJS = $(addprefix $(OBJ_DIR), $(FILE:.c=.o))
BONUS_OBJS = $(addprefix $(OBJ_DIR), $(BONUS_FILE:.c=.o))

all: $(NAME)

$(NAME):
	$(MAKE) -C ./mlx
	$(MAKE) -C ./libft
	@make make_mandatory

bonus:
	$(MAKE) -C ./mlx
	$(MAKE) -C ./libft
	@make make_bonus

make_mandatory: $(OBJS)
	$(CC) $(CFLAGS) $(CLIB) $(OBJS) -o $(NAME)
	install_name_tool -change libmlx.dylib mlx/libmlx.dylib $(NAME)
	touch $@

make_bonus: $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(CLIB) $(BONUS_OBJS) -o $(NAME)
	install_name_tool -change libmlx.dylib mlx/libmlx.dylib $(NAME)
	touch $@

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR) -I$(INC_LIBFT) -I$(INC_MLX) -g

$(OBJ_DIR)%.o : $(SRC_BONUS_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_BONUS_DIR) -I$(INC_LIBFT) -I$(INC_MLX)

clean:
	$(MAKE) -C ./mlx clean
	$(MAKE) -C ./libft fclean
	rm -rf $(OBJ_DIR)
	rm -f make_bonus
	rm -f make_mandatory

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re bonus $(NAME)
