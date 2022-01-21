# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mjiam <mjiam@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2021/10/12 15:11:16 by mjiam         #+#    #+#                  #
#    Updated: 2022/01/21 18:35:50 by mjiam         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# NAME		= 	ft_test std_test

NAME		=	ft_bin

CC			= 	clang++

FLAGS		= 	-Wall -Wextra -Werror

ifdef STD
NAME		=	std_bin
VERS		=	-D IMPL=std
else
VERS		=	-D IMPL=ft
endif

CONTAINERS	= 	$(addprefix $(CONT_DIR)/, vector.hpp vector.ipp \
											)

SRC_TEST	= 	main.cpp tester_helper.cpp test_vector.cpp test_utils.cpp

OBJ			= 	$(addprefix $(OBJ_DIR)/, $(SRC_TEST:.cpp=.o))

ifdef DEBUG
FLAGS		+=	-fsanitize=address -fno-omit-frame-pointer -g
endif

# DIRECTORIES
TEST_DIR	=	test2
CONT_DIR	=	containers
UTILS_DIR	=	utils
OBJ_DIR		=	obj

# COLORS
CYAN		= 	\033[0;36m
PURPLE		= 	\033[0;35m
BLUE		= 	\033[0;34m
YELLOW		=	\033[0;33m
GREEN		= 	\033[0;32m
RESET		= 	\033[0m

all: $(NAME) std

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $@
	@echo "Executable $(CYAN)$@$(RESET) made"
	@$(MAKE) quietclean

# clean is called so subsequent `make` calls recompile correct version.

ft:
	@$(MAKE) ft_bin

std:
	@$(MAKE) quietclean
	@$(MAKE) std_bin STD=1

# $(NAME): $(OBJ)
# 	@$(CC) $(FLAGS) $(OBJ) -o $(word 1, $(NAME))
# 	@echo "Executable $(CYAN)$(word 1, $(NAME))$(RESET) made"
# 	@$(CC) $(FLAGS)  $(OBJ) -o $(word 2, $(NAME))
# 	@echo "Executable $(CYAN)$(word 2, $(NAME))$(RESET) made"

compile_std: $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $@
	@echo "Executable $(CYAN)$(NAME)$(RESET) made"
	@$(MAKE) quietclean

run:
	@$(MAKE)
	@echo "Running $(GREEN)diff$(RESET) on binaries"
	@bash -c "diff <(./ft_bin) <(./std_bin)"

save:
	@$(MAKE) CFLAGS+=-DSAVE=1

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp $(CONTAINERS)
	@echo "$(PURPLE)Compiling: $<$(RESET)"
	@$(CC) $(FLAGS) $(VERS) -I $(CONT_DIR) -c $< -o $@

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

debug: $(OBJ) $(CONTAINERS)
	@echo "$(GREEN)Debug mode: compiling with address sanitizer$(RESET)"
	@$(MAKE) DEBUG=1

clean:
	@echo "$(BLUE)Cleaning$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)Removed: $(OBJ_DIR) folder$(RESET)"

quietclean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(BLUE)Removing: $(NAME)$(RESET)"
	@rm -rf ft_bin std_bin
	@echo "$(BLUE)Clean af$(RESET)"

re:
	@echo "$(BLUE)Once more from the top$(RESET)"
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all run debug clean fclean re
