
NAME=	test

SRC=	Source.cpp

OBJ=	$(SRC:.cpp=.o)

CXX=	g++ -W -Wall -Wextra -ansi -pedantic -std=c++11 -g3

$(NAME):	all

all:	$(OBJ)
	$(CXX) $(OBJ) ../WebServer/WebServer.a -o $(NAME)

clean:
	$(RM) $(NAME) $(OBJ)

re:	clean all

