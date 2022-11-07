SRC = main.c \
parsing.c \
env.c \
env2.c \
ft_dollar.c \
ft_check_syntax.c \
build_in.c \
cmd_management.c \
get_arg_cmd.c \
get_arg_token.c \
pipes_management.c \
redirections.c \
run_cmd.c \
run_pipes.c \
token_management.c \
utils.c \
utils2.c \
utils3.c \
utils4.c \
utils5.c \
wstatus.c \
built_in_exit.c \
built_in_unset.c \
built_in_export.c \
built_in_export2.c \
built_in_echo_pwd_env.c \
built_in_cd.c \
get_redir.c \
clean.c \
signals.c \
delimiters.c \
mini.c \
clean2.c \

CC = gcc

HEADER = minishell.h

OBJ = $(SRC:%.c=./.build/%.o)

NAME = minishell

RM = rm -rf

LIBC = ar -rc

CFLAGS = -Wall -Wextra -Werror

LIBFT = @printf "\n\t\t${B_CYAN}GENERATE libft library   ...\n\n --no-print-directory${NONE}" && cd Libft && make --no-print-directory

GNL = @printf "Generate Get-Next_Libe\n" && cd ./get_next_line && make --no-print-directory

# COLORS
NONE			= \033[0m
CL_LINE			= \033[2K
B_RED			= \033[1;31m
B_GREEN			= \033[1;32m
B_MAGENTA 		= \033[1;35m
B_CYAN 			= \033[1;36m

./.build/%.o : %.c
	@$(CC) -g3 -I. -o $@ -c $?
	@printf "${B_MAGENTA}Compilling $? ...\n${NONE}"

all :
	@mkdir -p .build
	@make ${NAME} --no-print-directory

${NAME} : $(OBJ)
	${LIBFT}
	${GNL}
	@${CC} -o ${NAME} ${OBJ} -lreadline ./Libft/libft.a ./get_next_line/get_next_line.a
	@printf "${B_GREEN}==>{${NAME}} LINKED SUCCESFULLY<==${NONE}\n"


clean :
	@${RM} .build
	@printf "${B_RED}XX{${NAME}} CLEANED SUCCESFULLY XX${NONE}\n"

fclean :	clean
	@${RM} ${NAME}
	@cd get_next_line && make fclean --no-print-directory
	@cd Libft && make fclean --no-print-directory
	@printf "${B_RED}XX{${NAME}} FCLEAN SUCCESFULL XX${NONE}\n"

re :	fclean all
