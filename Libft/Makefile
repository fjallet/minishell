SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
 ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
  ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
  ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_strncpy.c ft_strcmp.c \
   ft_strcat.c ft_putstr.c ft_strcpy.c ft_strlcat.c ft_putchar.c\
   ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_strndup.c

CC = gcc

OBJ = $(SRC:%.c=./.build/%.o)

NAME = libft.a

RM = rm -rf

LIBC = ar -rc

CFLAGS = -Wall -Wextra -Werror

# COLORS
NONE			= \033[0m
CL_LINE			= \033[2K
B_RED			= \033[1;31m
B_GREEN			= \033[1;32m
B_MAGENTA 		= \033[1;35m
B_CYAN 			= \033[1;36m

./.build/%.o : %.c
	@$(CC) ${CFLAGS} -I. -o $@ -c $?
	@printf "${B_MAGENTA}Compilling $? ...\n${NONE}"

all :
	@mkdir -p .build
	@make ${NAME} --no-print-directory

${NAME} : $(OBJ)
	@${LIBC} -o ${NAME} ${OBJ}
	@printf "${B_GREEN}==>{${NAME}} LINKED SUCCESFULLY<==${NONE}\n"

clean :
	@${RM} .build
	@printf "${B_RED}XX{${NAME}} CLEANED SUCCESFULLY XX${NONE}\n"

fclean :	clean
	@${RM} ${NAME}
	@${RM} .build
	@printf "${B_RED}XX{${NAME}} FCLEAN SUCCESFULL XX${NONE}\n"

re :	fclean all