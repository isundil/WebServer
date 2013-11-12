
NAME=	WebServer.a

SRC=	HtmlRootElement.cpp		\
		Util.cpp				\
		HttpClient.cpp			\
		HttpRequest.cpp			\
		Session.cpp				\
		SessionManager.cpp		\
		SocketException.cpp		\
		WebServer.cpp			\
		Socket.cpp				\
		HashGenerator.cpp		\
		Cookie.cpp				\
		Response.cpp			\
		AHtmlNode.cpp			\
		DirContentRootElem.cpp	\
		Anchor.cpp				\
		FileElement.cpp			\
		MappedDirectory.cpp		\
		JsonRootElement.cpp		\
		Meta.cpp				\
		Paragraph.cpp			\
		RawRootElem.cpp			\
		Link.cpp				\
		Form.cpp				\
		AInput.cpp				\
		BasicInput.cpp			\
		AWebPage.cpp			\
		HiddenField.cpp			\
		TextBox.cpp				\
		PasswordBox.cpp			\
		SubmitButton.cpp

OBJ=	$(SRC:.cpp=.o)

CXX=	g++ -W -Wall -Wextra -ansi -pedantic -std=c++11 -g3

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

all:	$(NAME)

clean:
	$(RM) $(NAME) $(OBJ)

re:	clean all

