
NAME=	WebServer.a

SRC=	HtmlRootElement.cpp		\
		Util.cpp				\
		HttpClient.cpp			\
		HttpRequest.cpp			\
		Session.cpp				\
		SessionManager.cpp		\
		SocketException.cpp		\
		WebServer.cpp			\
		Socket.cpp

OBJ=	$(SRC:.cpp=.o)

CXX=	g++ -W -Wall -Wextra -ansi -pedantic -std=c++11

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

all:	$(NAME)

clean:
	$(RM) $(NAME) $(OBJ)

re:	clean all

