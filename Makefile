CXX      = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++11 -I include

NAME     = computor

SRCDIR   = src
INCDIR   = include
OBJDIR   = obj

SRCS     = $(SRCDIR)/main.cpp \
           $(SRCDIR)/parser.cpp \
           $(SRCDIR)/reducer.cpp \
           $(SRCDIR)/solver.cpp

OBJS     = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I $(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re
