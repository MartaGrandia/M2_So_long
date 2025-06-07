# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgrandia <mgrandia@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 16:16:34 by mgrandia          #+#    #+#              #
#    Updated: 2025/06/07 12:53:41 by mgrandia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ─────────────────────────────────────────────────────────────
# CONFIGURACIÓN GENERAL
# ─────────────────────────────────────────────────────────────
NAME = so_long
CC = cc
AR = ar rcs
RM = rm -f
FLAGS = -Wall -Wextra -Werror -g -Wunreachable-code -Ofast

# ─────────────────────────────────────────────────────────────
# COLORES
# ─────────────────────────────────────────────────────────────
GREEN = \033[38;5;114m   
SLATE = \033[38;5;145m 
TEAL = \033[38;5;123m 
RED = \033[0;31m
RESET = \033[0m

# ─────────────────────────────────────────────────────────────
# DIRECTORIOS
# ─────────────────────────────────────────────────────────────
DIR_INC = includes/ 
DIR_OBJS = objs/
DIR_SRC = src/

# ─────────────────────────────────────────────────────────────
# LIBRERÍAS
# ─────────────────────────────────────────────────────────────
LIBFT_DIR = ./lib/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBMLX = ./lib/MLX42
MLX_LIB = $(LIBMLX)/build/libmlx42.a

# ─────────────────────────────────────────────────────────────
# HEADERS Y LIBS
# ─────────────────────────────────────────────────────────────
HEADERS = -I$(DIR_INC) -I$(LIBMLX)/include -I$(LIBFT_DIR)
LIBS = $(MLX_LIB) $(LIBFT) -ldl -lglfw -pthread -lm

# ─────────────────────────────────────────────────────────────
# ARCHIVOS
# ─────────────────────────────────────────────────────────────
SRC = srcs/main.c srcs/free_utils.c srcs/map_reader.c srcs/map_valid.c srcs/utils.c srcs/draw_map.c
OBJS = $(addprefix $(DIR_OBJS), $(notdir $(SRC:%.c=%.o)))
DEP_FILES = $(OBJS:%.o=%.d)

# ─────────────────────────────────────────────────────────────
# REGLAS
# ─────────────────────────────────────────────────────────────
.PHONY: all clean fclean re libft libmlx

# ALL: construir libft y libmlx, luego el ejecutable
all: libft libmlx $(NAME)

# Regla phony para libft: siempre ejecuta make dentro de libft
libft:
	@echo "$(TEAL)📚 Compilando libft...$(RESET)"
	@make -C $(LIBFT_DIR)

# Regla phony para libmlx: compila MLX42 usando cmake
libmlx:
	@echo "$(TEAL)🎮 Compilando MLX42...$(RESET)"
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

# Compilar el ejecutable principal
$(NAME): $(DIR_OBJS) $(OBJS) $(LIBFT) $(MLX_LIB)
	@echo "$(GREEN)🔗 Enlazando $(NAME)...$(RESET)"
	@$(CC) $(FLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo
	@echo "$(GREEN)✅ Ejecutable $(NAME) creado correctamente!$(RESET)"
	@echo

# Crear carpeta objs si no existe
$(DIR_OBJS):
	@echo "$(SLATE)🛠️  Creando carpeta de objetos...$(RESET)"
	@mkdir -p $(DIR_OBJS)

# Compilar los archivos .c en .o con generación de dependencias .d
$(DIR_OBJS)%.o: $(DIR_SRC)%.c Makefile | $(DIR_OBJS)
	@echo "$(SLATE)⚙️  Compilando $< ...$(RESET)"
	@$(CC) $(FLAGS) -MD $(HEADERS) -c $< -o $@

# Limpiar objetos y limpiar librerías también
clean:
	@echo "$(SLATE)🧹 Limpiando objetos de so_long, libft y MLX42...$(RESET)"
	@$(RM) -r $(DIR_OBJS)
	@make clean -C $(LIBFT_DIR)
	@$(RM) -rf $(LIBMLX)/build
	@echo "$(SLATE)✅ Objetos limpiados.$(RESET)"

# Limpiar todo incluyendo ejecutable y librerías
fclean: clean
	@echo "$(SLATE)🗑️  Limpieza total: ejecutable y librerías...$(RESET)"
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@echo "$(SLATE)✅ Limpieza total completada.$(RESET)"

# Recompilación completa
re: fclean all
	@echo "$(GREEN)🎉 Recompilación completa!$(RESET)"

# Incluir dependencias automáticas
-include $(DEP_FILES)
