NAMES = libft.a

HEADER = libft.h

SRCS = ft_atoi.c ft_memset.c     ft_strlcpy.c \
ft_bzero.c      ft_putchar_fd.c ft_strlen.c \
ft_calloc.c     ft_putendl_fd.c ft_strmapi.c \
ft_isalnum.c    ft_putnbr_fd.c  ft_strncmp.c \
ft_isalpha.c    ft_putstr_fd.c  ft_strnstr.c \
ft_isascii.c    ft_split.c      ft_strrchr.c \
ft_isdigit.c    ft_strchr.c     ft_strtrim.c \
ft_isprint.c    ft_memchr.c     ft_strdup.c  \
ft_itoa.c       ft_memcmp.c     ft_striteri.c \
ft_memcpy.c     ft_strjoin.c    ft_toupper.c \
ft_memmove.c    ft_strlcat.c    ft_substr.c \
ft_tolower.c	get_next_line.c	ft_chrjoin.c \
ft_strcmp.c

BONUS_SRCS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
			ft_lstdelone.c   ft_lstiter.c      ft_lstlast.c \
			ft_lstmap.c      ft_lstnew.c       ft_lstsize.c \


OBJS = $(SRCS:.c=.o)

DS =	$(SRCS:%.c=%.d)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

CC = cc

RM = rm -f

FLAGS = -Wall -Wextra -Werror -MD

all: $(NAMES) 

$(NAMES): $(OBJS)
	ar rcs $(NAMES) $?

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@  

include 	$(wildcard $(DS))

bonus: 
		@make OBJS="$(BONUS_OBJS)" all 

clean:
		$(RM) $(OBJS) $(DS) $(BONUS_OBJS) 

fclean:	clean 
		$(RM) $(NAMES)

re: fclean all

.PHONY: all clean fclean re bonus
