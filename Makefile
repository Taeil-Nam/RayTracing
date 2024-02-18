NAME = RayTracing

CC = cc
CFLAGS = -Wall -Werror -Wextra
CLIB = -L./libft -lft -L./mlx -lmlx -framework OpenGL -framework Appkit

INC_DIR = ./inc/
INC_LIBFT = ./libft
INC_MLX = ./mlx

LIBFT = ./libft/libft.a
MLX = ./mlx/libmlx.dylib

SRCS =		src/main.c					\
			src/utils/utils_1.c			\
			src/utils/utils_2.c			\
			src/utils/err_utils.c		\
			src/utils/mlx_utils.c		\
			src/utils/memory_free.c		\
			src/vec3/vec3_1.c			\
			src/vec3/vec3_2.c			\
			src/vec3/vec3_3.c			\
			src/vec3/vec3_4.c			\
			src/vec3/vec3_5.c			\
			src/parser/constructor.c	\
			src/parser/init_hittable.c	\
			src/parser/init_camera.c 	\
			src/parser/init_world.c		\
			src/parser/init_mat.c		\
			src/parser/init_obj_1.c		\
			src/parser/init_obj_2.c		\
			src/parser/init_tex.c 		\
			src/parser/parser_minirt.c	\
			src/parser/parser_util1.c	\
			src/parser/parser_util2.c	\
			src/bvh/bvh.c				\
			src/bvh/comparator.c		\
			src/bvh/bvh_utils.c			\
			src/object/aabb.c			\
			src/object/sphere.c			\
			src/object/plane.c			\
			src/object/cylinder.c		\
			src/object/cone.c			\
			src/object/object_utils.c	\
			src/object/get_uv.c 		\
			src/texture/color.c			\
			src/material/emit.c			\
			src/material/scatter.c		\
			src/render/phong.c			\
			src/render/path.c			\
			src/render/render.c 		\
			src/render/ray.c			\
			src/render/aa.c				\
			src/thread/thread.c			\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./mlx
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) $(CLIB) $(OBJS) -o $(NAME)
	install_name_tool -change libmlx.dylib mlx/libmlx.dylib $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR) -I$(INC_LIBFT) -I$(INC_MLX)

clean:
	$(MAKE) -C ./mlx clean
	$(MAKE) -C ./libft fclean
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
