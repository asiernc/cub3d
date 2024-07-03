# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/03 20:31:11 by anovio-c          #+#    #+#              #
#    Updated: 2024/07/03 20:31:08 by anovio-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Setup
NAME        = cub3d
LIBFT       = libft/
MLX         = minilibx/
LIBFT_A     = $(addprefix $(LIBFT), libft.a)
MLX_A       = $(addprefix $(MLX), libmlx.a)

# Detect OS
UNAME_S     := $(shell uname -s)

# Determine MLX flags based on OS
ifeq ($(UNAME_S), Linux)
    MXFLAGS     = -L$(MLX) -lmlx -lXext -lX11 -lm -lz
else ifeq ($(UNAME_S), Darwin)
    MXFLAGS     = -L$(MLX) -lmlx -framework OpenGL -framework AppKit -lm
else
    $(error Unsupported OS: $(UNAME_S))
endif

# Commands and flags
CC          = gcc
INCLUDE     = includes
CFLAGS      = -Wall -Wextra -Werror -I$(INCLUDE)
MLX_CFLAGS  = -Wall -Wextra
RM          = rm -rf

# Cub3d files
SRCS        = src/main.c

OBJS        = $(SRCS:%.c=%.o)

# Compile the main executable
all:        $(NAME)

# Link the main executable
$(NAME):    $(OBJS) $(LIBFT_A) $(MLX_A) includes/cub3d.h includes/libft.h includes/mlx.h
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -lft $(MXFLAGS) -o $(NAME)
	@echo "\033[1;32m\033[1mSuccessfully built $(NAME).\033[0m"

# Compile libft library
$(LIBFT_A):
	@$(MAKE) -s -C $(LIBFT)
	@echo "\033[1;32m\033[1mCompiled $(LIBFT_A).\033[0m"

# Compile minilibx library
$(MLX_A):
	@$(MAKE) -s -C $(MLX)
	@echo "\033[1;32m\033[1mCompiled $(MLX_A).\033[0m"

.c.o:
	@echo "\033[1mCompiling $<...\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

# Remove object files
clean:
	@echo "\033[1;31m\033[1mDeleting every object file\033[0m"
	@echo "\033[1mCleaning the object src files\033[0m"
	@$(RM) $(OBJS)
	@echo "\033[1mCleaning the libft object files\033[0m"
	@$(MAKE) clean -s -C $(LIBFT)
	@echo "\033[1mCleaning the mlx object files\033[0m"
	@$(MAKE) clean -s -C $(MLX)

# Remove object files and executables
fclean:     clean
	@echo "\033[1;31m\033[1mDeleting the executable file\033[0m"
	@$(RM) $(NAME)
	@echo "\033[1;31m\033[1mCleaning the libft executable file\033[0m"
	@$(MAKE) fclean -s -C $(LIBFT)
	@echo "\033[1;31m\033[1mCleaning the mlx executable file\033[0m"
	@$(MAKE) clean -s -C $(MLX)

# Rebuild the project from scratch
re:         fclean all

.PHONY:     all clean fclean re