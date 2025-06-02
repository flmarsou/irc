# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/26 09:43:40 by flmarsou          #+#    #+#              #
#    Updated: 2025/06/02 12:43:44 by rothiery         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program Executable
EXE			:=	ircserv

VPATH		:=	src					\
				src/commands

# Files
SRC			:=	main.cpp \
				Server.cpp \
				Client.cpp \
				ServerCommands.cpp \
				ServerNick.cpp \

OBJ			:= ${addprefix obj/,${notdir $(SRC:.cpp=.o)}}

# Variables
CC			:=	c++
CFLAGS		:=	-Wall -Wextra -std=c++98 -I includes -I src # Add -Werror

# Makefile
all			:	${EXE}

${EXE}		:	${OBJ}
				${CC} ${CFLAGS} ${OBJ} -o ${EXE}

obj/%.o: %.cpp
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean		:
				rm -rf ${OBJ} ${EXE}

re			:	clean all

.PHONY		:	all clean re
