NAME		=	ircserv
CXX			=	c++
CXXFLAGS	=	-Wall -Werror -Wextra -std=c++98
INC			=	-Iincludes

SRCS 		=	$(addprefix src/,\
					ft_ircd.cpp \
					SocketEngine.cpp \
					Client.cpp \
					ClientManager.cpp \
					CommandParser.cpp \
					Channel.cpp \
					ChannelManager.cpp \
					NumericReply.cpp \
					NumericHelper.cpp \
					$(addprefix commands/,\
						ACommand.cpp \
						CmdPass.cpp \
						CmdNick.cpp \
						CmdUser.cpp \
						CmdJoin.cpp \
						CmdPart.cpp \
						CmdQuit.cpp \
						CmdMessage.cpp \
						CmdKick.cpp \
						CmdInvite.cpp \
						CmdTopic.cpp \
						CmdMode.cpp \
						CmdMotd.cpp \
						CmdList.cpp \
				))

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