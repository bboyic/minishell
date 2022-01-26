NAME 		=		minishell

# NAME_B	=		checker

HEAD 		=		minishell.h

# HEAD_B	=		push_swap_checker.h

SRC 		= 		minishell.c		parser.c		pre_arguments.c	\
					pre_command.c	pre_redirect.c	pre_utils.c		\
					gen_parser.c	gen_utils.c		gen_checker.c	\
					printer.c		build/cd.c		build/echo.c	\
					build/env.c			\
					build/pwd.c		build/utils.c	build/build.c

# SRC_B 	= 		push_swap_ops_1.c	push_swap_ops_2.c		push_swap_checker.c

OBJ 		=		$(SRC:%.c=%.o)

# OBJ_B		=		$(SRC_B:%.c=%.o)

D 			=		$(SRC:%.c=%.d)

# D_B 		=		$(SRC_B:%.c=%.d)

LIBDIR		= 		./libft/

LIBFT		= 		libft.a

CFLAGS 		= 		-MD -g 
#					-fsanitize=address
# 					-Wall -Werror -Wextra 

CC 			= 		gcc

RM 			= 		rm -f

all 		: 		libmake $(NAME)

$(NAME) 	: 		$(OBJ)
					@cp $(LIBDIR)$(LIBFT) .
					$(CC) $(CFLAGS) $(OBJ) libft.a -lreadline -o $@
 
libmake :
					@make -C $(LIBDIR)

%.o 		: 		%.c
					$(CC) $(CFLAGS) -I $(HEAD) -c $< -o $@

include 			$(wildcard $(D))
# $(D_B)

# bonus		:		
# 					@make OBJ="$(OBJ_B)" HEAD="$(HEAD_B)" NAME="$(NAME_B)" all

clean		:
					@$(RM) $(OBJ) $(D) 
# 					$(OBJ_B) $(D_B) 

fclean		: 		clean
					@$(RM) $(NAME) $(LIBFT)
# 					$(NAME_B)

re			: 		fclean all

.PHONY		: 		all clean fclean re bonus
