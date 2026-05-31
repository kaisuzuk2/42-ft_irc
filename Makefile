NAME		=	ircserv
CXX			=	c++
CXXFLAGS	=	-Wall -Werror -Wextra -std=c++98
INC			=	-Iincludes

SRCS		=	src/ft_ircd.cpp \
				src/SocketEngine.cpp \
				src/Client.cpp \
				src/ClientManager.cpp \
				src/CommandParser.cpp \
				src/Channel.cpp \
				src/ChannelManager.cpp \
				src/commands/ACommand.cpp \
				src/commands/CmdPass.cpp \
				src/commands/CmdNick.cpp \
				src/commands/CmdUser.cpp \
				src/commands/CmdJoin.cpp \
				src/commands/CmdPart.cpp \
				src/commands/CmdQuit.cpp \
				src/commands/CmdMessage.cpp \
				src/commands/CmdKick.cpp \
				src/commands/CmdInvite.cpp

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