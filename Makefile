NAME = cub69d

CXXFLAGS = -Wall -Werror -Wextra -g
CFLAGS = -Imlx -I includes ${CXXFLAGS}

UTILS = ${addprefix utils/, map_maker blayer movements mini_libft event_handler \
			cast_rays window}
SAUCE = ${addprefix sauce/, ${addsuffix .c, main ${UTILS}}}
OBJS = ${SAUCE:c=o}

# # linux obj files
# %.o: %.c
# 	$(CC) -Wall -Wextra -Werror -I include -Imlx_linux -03 -c $< -o $@

# # linux executable!
# $(NAME): $(OBJ)
# 	$(CC) $(OBJ) -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

${NAME}: ${OBJS}
	${CC} ${OBJS} -Lmlx -lmlx -framework OpenGL -framework AppKit -lm -o ${NAME}

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re