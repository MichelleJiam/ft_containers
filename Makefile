# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mjiam <mjiam@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2021/10/12 15:11:16 by mjiam         #+#    #+#                  #
#    Updated: 2021/11/19 17:18:53 by mjiam         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= 	ft_test std_test

CC			= 	clang++

FLAGS		= 	-Wall -Wextra -Werror -std=c++98

HEADER		= 	$(addprefix $(CONT_DIR), vector.hpp vector.ipp \
											)

SRC_TEST	= 	newmain.cpp

OBJ			= 	$(addprefix $(OBJ_DIR)/, $(SRC_TEST:.cpp=.o))

ifdef DEBUG
FLAGS		+=	-fsanitize=address -fno-omit-frame-pointer -g
endif

# DIRECTORIES
TEST_DIR	=	test/
CONT_DIR	=	containers/
UTILS_DIR	=	utils/
OBJ_DIR		=	obj/

# COLORS
CYAN		= 	\033[0;36m
PURPLE		= 	\033[0;35m
BLUE		= 	\033[0;34m
GREEN		= 	\033[0;32m
RESET		= 	\033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(word 1, $(NAME))
	@echo "Executable $(CYAN)$(word 1, $(NAME))$(RESET) made"
	@$(CC) $(FLAGS) $(OBJ) -o $(word 2, $(NAME))
	@echo "Executable $(CYAN)$(word 2, $(NAME))$(RESET) made"

run:
	@$(MAKE)
	@./$(NAME)

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp $(HEADER)
	@echo "$(PURPLE)Compiling: $<$(RESET)"
	@$(CC) $(FLAGS) -I $(CONT_DIR) -c $< -o $@

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

debug: $(OBJ) $(HEADER)
	@echo "$(GREEN)Debug mode: compiling with address sanitizer$(RESET)"
	@$(MAKE) DEBUG=1

clean:
	@echo "$(BLUE)Cleaning$(RESET)"
	@rm -rf $(OBJ)
	@echo "$(BLUE)Removed: $(OBJ_DIR) folder$(RESET)"

fclean: clean
	@echo "$(BLUE)Removing: $(NAME)$(RESET)"
	@rm -rf $(NAME)
	@echo "$(BLUE)Clean af$(RESET)"

re:
	@echo "$(BLUE)Once more from the top$(RESET)"
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all run debug clean fclean re
