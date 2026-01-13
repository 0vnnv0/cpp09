NAME = btc

SRC = main.cpp
CXX = c++

OBJDIR = objs
OBJS = $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))

CXXFLAGS = -Wall -Werror -Wextra -std=c++98

GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	@echo "$(YELLOW) Compiling $< ... $(RESET)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJS)
		@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
		@echo "$(GREEN) Executable $(NAME) created.$(RESET)"

clean:
		@echo "$(GREEN)Cleaning object files...$(RESET)"
		@rm -r $(OBJDIR)

fclean: clean
		@echo "$(GREEN)Removing executable ..."
		@rm -r $(NAME)

re: fclean all

.PHONY: all clean