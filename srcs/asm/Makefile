# LIB     = ../../ft_printf/libft/

# NAME    = asm

# CFLAGS  = -Wall -Wextra -Werror

# CC      = gcc

# SRC_DIR	= srcs/asm/

# SRCS    = $(shell find . | awk -F '/' '/.c$$/{print $$NF}')
# HEADER  = includes/
# OBJS    = $(SRCS:.c=.o)
# OBJ_DIR = obj/

# all: lib $(NAME)

# $(NAME): $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(OBJS)) $(HEADER)
# 	@gcc $(CFLAGS) $(addprefix $(OBJ_DIR), $(OBJS)) -I $(HEADER) -L libft $(LIB)libft.a -o $(NAME)
# 	@echo "\033[103;33masm DONE\033[0m"

# lib:
# 	@make -C $(LIB)

# $(OBJ_DIR):
# 	@mkdir obj

# $(OBJ_DIR)%.o:$(SRC_DIR)%.c includes/assembler.h
# 	gcc $(CFLAGS) -c -I./$(HEADER) $< -o $@

# clean:
# 	@rm -rf $(OBJ_DIR)
# 	@make -C $(LIB) clean

# fclean: clean
# 	@rm -rf $(NAME)
# 	@make -C $(LIB) fclean

# re: fclean all

DIR_INC = ../../includes/

DIR_LIB = ../../ft_printf/libft

SRCS = 	assemble.c \
		assemble1.c \
		assemble2.c \
		assembler.c \
		assembler1.c \
		file_utils.c \
		header_parse.c \
		header_parse1.c \
		lexical_analysis.c \
		lexical_analysis.c \
		lexical_utils.c \
		lexical_utils1.c \
		op.c \
		utils.c \

INCLUDES = 	$(DIR_INC)/assembler.h

OBJECTS =	$(patsubst %.c,%.o,$(SRCS))

NAME = 		huevina_dva



all: $(NAME)

$(NAME): $(OBJECTS)
	gcc $(FLAGS) -o $(NAME) $(SRCS) -I $(DIR_INC) -L ../../ft_printf ../../ft_printf/libftprintf.a

%.o: %.c $(INCLUDES)
	gcc $(FLAGS) -I $(DIR_INC) -I $(DIR_LIB) $< -c -o $@

clean:
	rm -rf *.o