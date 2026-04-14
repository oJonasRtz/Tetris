NAME=Tetris

#	== Colours ==
RESET=\033[0m
GREEN=\033[32m
YELLOW=\033[33m
RED=\033[31m

# 	== Sources ==
INCLUDE_DIRS=include
SRCS=$(shell find src -name "*.cpp")
OBJS=$(SRCS:.cpp=.o)
LSDFlags = -lSDL2 -lSDL2_ttf

# 	== Build rules ==
CC = c++
CXXFLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIRS)

# == Rules ==
all: $(NAME) clean

$(NAME): $(OBJS)
	@$(CC) $(CXXFLAGS) -o $@ $^ $(LSDFlags)
	@echo "${GREEN}Build complete: $(NAME)${RESET}"

clean:
	rm -f $(OBJS)
	@echo "${YELLOW}Cleaned object files.${RESET}"

fclean: clean
	rm -f $(NAME)
	@echo "${RED}Cleaned executable: $(NAME)${RESET}"

re: fclean all

.PHONY: all clean fclean re
