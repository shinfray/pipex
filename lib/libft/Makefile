# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 16:37:12 by shinfray          #+#    #+#              #
#    Updated: 2023/06/28 13:18:53 by shinfray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DELETE_ON_ERROR:
.SILENT:

NAME:=	libft.a

SRCS_DIR:= src
BUILD_DIR:= build
INC_DIRS:= include

CFLAGS:= -Wall -Wextra -Werror -Wpedantic
ARFLAGS:= crs

EXT:=	.c

LIBFT_SRCS:=	ft_isalpha \
				ft_isdigit \
				ft_isalnum \
				ft_isascii \
				ft_isprint \
				ft_strlen \
				ft_memset \
				ft_bzero \
				ft_memcpy \
				ft_memmove \
				ft_strlcpy \
				ft_strlcat \
				ft_toupper \
				ft_tolower \
				ft_strchr \
				ft_strrchr \
				ft_strncmp \
				ft_memchr \
				ft_memcmp \
				ft_strnstr \
				ft_atoi \
				ft_calloc \
				ft_strdup \
				ft_substr \
				ft_strjoin \
				ft_strtrim \
				ft_split \
				ft_itoa \
				ft_strmapi \
				ft_striteri \
				ft_putchar_fd \
				ft_putstr_fd \
				ft_putendl_fd \
				ft_putnbr_fd \
				ft_lstnew_bonus \
				ft_lstadd_front_bonus \
				ft_lstsize_bonus \
				ft_lstlast_bonus \
				ft_lstadd_back_bonus \
				ft_lstdelone_bonus \
				ft_lstclear_bonus \
				ft_lstiter_bonus \
				ft_lstmap_bonus

FTPRINTF_SRCS:=	ft_printf \
				ft_printf_flags \
				ft_printf_hexa

GNL_SRCS:=	get_next_line_bonus \
			get_next_line_utils_bonus

SRCS:=	${addprefix ${SRCS_DIR}/libft/,${addsuffix ${EXT},${LIBFT_SRCS}}}
SRCS+=	${addprefix ${SRCS_DIR}/ft_printf/,${addsuffix ${EXT},${FTPRINTF_SRCS}}}
SRCS+=	${addprefix ${SRCS_DIR}/get_next_line/,${addsuffix ${EXT},${GNL_SRCS}}}

OBJS:=	${SRCS:%.c=${BUILD_DIR}/%.o}

DEPS:=	${OBJS:.o=.d}

CPPFLAGS:= ${addprefix -I,${INC_DIRS}} -MMD -MP

RM:=	rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	${AR} ${ARFLAGS} $@ ${OBJS}

${BUILD_DIR}/%.o: %.c
	mkdir -p $(dir $@)
	${CC} ${CPPFLAGS} ${CFLAGS} -c $< -o $@

clean:
	${RM} ${BUILD_DIR}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re

-include ${DEPS}
