NAME		=	ircserv
CXX			=	c++
CXXFLAGS	=	-Wall -Werror -Wextra -std=c++98
INC			=	-Iincludes

SRCS		=	src/ft_ircd.cpp \
				src/SocketEngine.cpp \
				src/Client.cpp \
				src/ClientManager.cpp \
				src/CommandParser.cpp \
				src/commands/AComamnd.cpp \
				src/commands/CmdPass.cpp

OBJS		=	$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INC) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re