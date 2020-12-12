FLAGS = -Wall -Werror -Wextra

DIR_INC = ../../includes

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
		lexical_utils.c \
		lexical_utils1.c \
		op.c \
		utils.c

INCLUDES = 	$(DIR_INC)/assembler.h \
			$(DIR_INC)/op.h

OBJECTS =	$(patsubst %.c,%.o,$(SRCS))

NAME = 		../../my_asm


all: $(NAME)

$(NAME): $(OBJECTS)
	gcc $(FLAGS) -o $(NAME) $(SRCS) -I $(DIR_INC) ../../ft_printf/libftprintf.a

%.o: %.c $(INCLUDES)
	gcc $(FLAGS) -I $(DIR_INC) -I $(DIR_LIB) $< -c -o $@

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all