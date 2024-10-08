# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/03 20:31:11 by anovio-c          #+#    #+#              #
#    Updated: 2024/07/23 18:16:57 by molasz-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Setup
NAME        = cub3D
LIBFT       = libs/libft/
LIBFT_A     = $(addprefix $(LIBFT), libft.a)
MLX_A       = build/libmlx42.a

# Detect OS
UNAME_S     := $(shell uname -s)

# Determine MLX flags based on OS
MLX			= libs/MLX42/
ifeq ($(UNAME_S), Linux)
	MLXFLAGS		= -Ilibs/MLX42/include -ldl -lglfw -pthread -lm
else ifeq ($(UNAME_S), Darwin)
	MLXFLAGS	=  -I/opt/homebrew/include -L/opt/homebrew/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit 
else
    $(error Unsupported OS: $(UNAME_S))
endif

# Commands and flags
CC          = gcc
INCLUDE     = includes/cub3d.h libs/libft/libft.h
CFLAGS      = -Wall -Wextra -Werror -MMD #-g -fsanitize=address
RM          = rm -rf

# Cub3d files
SRCS        =	main.c 						\
				parser_map/read_file.c 		\
				parser_map/checkers.c 		\
				parser_map/utils_parser.c 	\
				parser_map/fill_colors.c 	\
				parser_map/fill_textures.c 	\
				parser_map/fill_map.c 		\
				parser_map/player.c 		\
				controls/controls.c			\
				controls/move.c				\
				controls/cam.c				\
				render/draw.c				\
				render/render.c				\
				render/textures.c 			\
				minimap.c					\
				handle_errors.c

OBJS        = $(addprefix obj/, $(SRCS:%.c=%.o))
DEPS        = $(addprefix obj/, $(SRCS:%.c=%.d))

# Compile the main executable
all:       dir $(NAME)

# Link the main executable
$(NAME):    $(OBJS) $(LIBFT_A) $(MLX_A) Makefile
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -lft $(MLX_A) $(MLXFLAGS) -o $(NAME)
	@echo "\033[1;32m\033[1mSuccessfully built $(NAME).\033[0m"

# Compile libft library
$(LIBFT_A):
	@$(MAKE) -s -C $(LIBFT)
	@echo "\033[1;32m\033[1mCompiled $(LIBFT_A).\033[0m"

# Compile minilibx library
$(MLX_A):
	@cmake libs/MLX42 -B build
	@make -C build -j4
	@echo "\033[1;32m\033[1mCompiled $(MLX_A).\033[0m"

dir:
	@mkdir -p obj obj/parser_map obj/controls obj/render

obj/%.o:	src/%.c Makefile 
	@echo "\033[1mCompiling $<...\033[0m"
	$(CC) $(CFLAGS) -c $< -o $@

# Remove object files
clean:
	@echo "\033[1;31m\033[1mDeleting every object file\033[0m"
	@echo "\033[1mCleaning the object src files\033[0m"
	@$(RM) obj/
	@echo "\033[1mCleaning the libft object files\033[0m"
	@$(MAKE) clean -s -C $(LIBFT)
	@echo "\033[1mCleaning the mlx object files\033[0m"
	@$(RM) build/

# Remove object files and executables
fclean:     clean
	@echo "\033[1;31m\033[1mDeleting the executable file\033[0m"
	@$(RM) $(NAME)
	@echo "\033[1;31m\033[1mCleaning the libft executable file\033[0m"
	@$(MAKE) fclean -s -C $(LIBFT)
	@echo "\033[1;31m\033[1mCleaning the mlx executable file\033[0m"

# Rebuild the project from scratch
re:         fclean all

-include $(DEPS)

.PHONY:     all clean fclean re dir
