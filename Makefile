# Program Executable
EXE			:=	ircserv

# Files
VPATH		:=	src : src/commands

SRC			:=	main.cpp \
				Server.cpp \
				Client.cpp \
				Channel.cpp \
				commands.cpp \
				pass.cpp \
				nick.cpp \
				user.cpp \
				join.cpp \
				privmsg.cpp \
				mode.cpp

OBJ			:=	${addprefix obj/,${notdir $(SRC:.cpp=.o)}}

# Variables
CC			:=	c++
CFLAGS		:=	-Wall -O2 -std=c++98 -Iincludes -Isrc

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
