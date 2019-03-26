# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: squiquem <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/23 19:01:27 by squiquem          #+#    #+#              #
#    Updated: 2019/03/26 15:05:57 by qsebasti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY			:	all clean fclean re opti

NAME			=	wolf3d

SRC_DIR			=	./sources/

OBJ_DIR			=	./objects/

CPPFLAGS 		=	-I includes/

SRC_FILES		=	bullet.c \
					calc.c \
					calc_sprites.c \
					checkdoor.c \
					draw.c \
					draw_walls.c \
					end.c \
					enemies.c \
					hook.c \
					hook2.c \
					hud.c \
					init.c \
					main.c \
					map.c \
					mousehook.c \
					parsing.c \
					parsing2.c \
					sprites.c \
					textures.c \
					time.c \
					util.c

OBJ_FILES		=	$(SRC_FILES:.c=.o)

OBJ_D_FILES		=	$(SRC_FILES:.c=.d)

SRC				=	$(addprefix $(SRC_DIR)/,$(SRC_FILES))

OBJ				=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

OBJ_D			=	$(addprefix $(OBJ_DIR), $(OBJ_D_FILES))

LFT				=	-L libft/ -lft

MLX				=	-L minilibx/ -lmlx -framework OpenGL -framework AppKit

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror -MMD #-g3 -fsanitize=undefined
##CFLAGS			=	-Wall -Wextra -Werror -MMD -Ofast -flto -march=native

opti			:
	@make -j8 all

all				:
	@make all -C libft/
	@make all -C minilibx/
	@make $(NAME)
	@touch .gitignore
	@echo $(NAME) > .gitignore

$(NAME)			:	$(OBJ)
	@$(CC) $(CFLAGS) $(LFT) $(MLX) $(OBJ) -o $@ 
	@printf '\033[4m'
	@printf "\033[32m[ ✔ ] $(NAME)\n\033[0m"

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
	@mkdir $(OBJ_DIR) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@printf '\033[0m[ ✔ ] %s\n\033[0m' "$<"

clean			:
	@make clean -C libft/
	@make clean -C minilibx/
	@rm -f $(OBJ)
	@rm -f $(OBJ_D)
	@rm -rf $(OBJ_DIR) 2> /dev/null || true
	@printf '\033[4m'
	@echo "\033[31mWolf3d:\033[0m"
	@printf '\033[31m[ ✔ ] %s\n\033[0m' "Clean Object Files"

fclean			:	clean
	@make fclean -C libft/
	@rm -f $(NAME)
	@printf '\033[31m[ ✔ ] %s\n\033[0m' "Clean Binary File"

re				:	
	@make fclean
	@make opti

-include $(OBJ_D)
