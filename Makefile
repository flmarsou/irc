# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/26 09:43:40 by flmarsou          #+#    #+#              #
#    Updated: 2025/06/03 13:24:00 by flmarsou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program Executable
EXE			:=	ircserv

# Files
VPATH		:=	src : src/commands

SRC			:=	main.cpp \
				Server.cpp \
				Client.cpp \
				commands.cpp \
				nick.cpp \
				pass.cpp

OBJ			:=	${addprefix obj/,${notdir $(SRC:.cpp=.o)}}

# Variables
CC			:=	c++
CFLAGS		:=	-Wall -Wextra -std=c++98 -Iincludes -Isrc # Add -Werror

# Makefile
all			:	${EXE}

${EXE}		:	${OBJ}
				${CC} ${CFLAGS} ${OBJ} -o ${EXE}

obj/%.o		:	%.cpp
				@mkdir -p obj
				$(CC) $(CFLAGS) -c $< -o $@

clean		:
				rm -rf ${OBJ} ${EXE}

fclean		:	clean
				rm -rf obj

re			:	clean all

.PHONY		:	all clean re
