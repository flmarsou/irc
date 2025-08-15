# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flmarsou <flmarsou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/14 09:25:28 by flmarsou          #+#    #+#              #
#    Updated: 2025/08/15 12:53:02 by flmarsou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program Executable
EXE			:=	ircserv

# Files
VPATH		:=	src : src/commands

SRC			:=	main.cpp \
				Server.cpp \
				commands.cpp \
				pass.cpp \
				nick.cpp \
				user.cpp \
				Client.cpp \
				Channel.cpp \

OBJ			:=	${addprefix obj/,${notdir $(SRC:.cpp=.o)}}

# Variables
CC			:=	c++
CFLAGS		:=	-Wall -Werror -Wextra -O2 -std=c++98 -Iincludes -Isrc # Add -Werror

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
