# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/26 09:43:40 by flmarsou          #+#    #+#              #
#    Updated: 2025/05/28 11:42:35 by flmarsou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program Executable
EXE			:=	ircserv

# Files
SRC			:=	src/main.cpp \
				src/parser.cpp \
				src/Server.cpp \
				src/Client.cpp 

# Variables
CC			:=	c++
CFLAGS		:=	-Wall -Wextra -std=c++98 -Iincludes # Add -Werror

# Makefile
all			:	${EXE}

${EXE}		:	${SRC}
				${CC} ${CFLAGS} ${SRC} -o ${EXE}

clean		:
				rm -rf ${EXE}

re			:	clean all

.PHONY		:	all clean re
