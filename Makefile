# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 17:10:39 by shinfray          #+#    #+#              #
#    Updated: 2023/07/04 23:46:00 by shinfray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DELETE_ON_ERROR:
.SILENT:

NAME:=	pipex
B_NAME:=

SRCS_DIR:= src
BUILD_DIR:= build
INC_DIRS:= include lib/libft/include

LDLIBS:= -lft
LIBFT:=	lib/libft/libft.a
LIB_DIRS:= lib/libft

CFLAGS:= -Wall -Wextra -Werror -Wpedantic \
			-Wpedantic -pedantic-errors \
			-std=c17 \
			-O3 \
			-Wcast-qual \
			-Wconversion \
			-Wdouble-promotion \
			-Wfloat-equal \
			-Wformat=2 \
			-Winit-self \
			-Wmissing-declarations \
			-Wmissing-declarations \
			-Wstrict-prototypes \
			-Wmissing-prototypes \
			-Wpadded \
			-Wshadow \
			-Wundef \
			-Wunused-macros \
			-Wwrite-strings

#			-Walloc-zero \
			-Wduplicated-branches \
			-Wduplicated-cond \
			-Wformat-signedness \
			-Wlogical-op \

EXT:=	.c

SRCS_FILES:=	main \
				exec \
				here_doc \
				parse \
				set_pipex \
				utils

B_SRCS_FILES:=

SRCS:=	${addprefix ${SRCS_DIR}/,${addsuffix ${EXT},${SRCS_FILES}}}
B_SRCS:= ${addprefix ${SRCS_DIR}/,${addsuffix ${EXT},${B_SRCS_FILES}}}

OBJS:=	${SRCS:%.c=${BUILD_DIR}/%.o}
B_OBJS:= ${B_SRCS:%.c=${BUILD_DIR}/%.o}

DEPS:=	${OBJS:.o=.d}
B_DEPS:= ${B_OBJS:.o=.d}

CPPFLAGS:= ${addprefix -I,${INC_DIRS}} -MMD -MP

LDFLAGS:= ${addprefix -L,${LIB_DIRS}}

RM:=	rm -rf

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT}
	${CC} ${LDFLAGS} ${OBJS} ${LDLIBS} -o $@

bonus: ${NAME}

${B_NAME}: ${B_OBJS} ${LIBFT}
	${CC} ${LDFLAGS} ${B_OBJS} ${LDLIBS} -o $@

${LIBFT}:
	${MAKE} -C ${dir ${LIBFT}}

${BUILD_DIR}/%.o: %.c
	mkdir -p $(dir $@)
	${CC} ${CPPFLAGS} ${CFLAGS} -c $< -o $@

clean:
	${MAKE} clean -C ${dir ${LIBFT}}
	${RM} ${BUILD_DIR}

fclean: clean
	${RM} ${LIBFT}
	${RM} ${NAME} ${B_NAME}

re: fclean all

.PHONY:	all clean fclean re bonus

-include ${DEPS}
-include ${B_DEPS}
