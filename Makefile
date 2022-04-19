# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mjiam <mjiam@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2021/10/12 15:11:16 by mjiam         #+#    #+#                  #
#    Updated: 2022/04/19 15:55:10 by mjiam         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# NAME		= 	ft_test std_test

NAME		=	ft_bin

ifdef STD
NAME		=	std_bin
VERS		=	-D IMPL=std
else
VERS		=	-D IMPL=ft
endif

COMPARE_BIN	=	compare

CC			= 	clang++

FLAGS		= 	-Wall -Wextra -Werror -std=c++98

ifdef QUICK
FLAGS		+=	-D QUICK=1
endif

ifdef SIMPLE
FLAGS		+=	-D SIMPLE=1
endif

ifdef DEBUG
FLAGS		+=	-fsanitize=address -fno-omit-frame-pointer -g
endif

CONTAINERS	= 	$(addprefix $(CONT_DIR)/, vector.hpp vector.ipp \
											set.hpp stack.hpp)

TEST_SRC	= 	main.cpp tester_helper.cpp test_stack.cpp test_vector.cpp \
				test_utils.cpp test_map.cpp test_set.cpp

COMPARE_SRC	=	$(addprefix $(TEST_DIR)/, compare.cpp)

OBJ			= 	$(addprefix $(OBJ_DIR)/, $(TEST_SRC:.cpp=.o))

SAVE_FILES	=	ft_output.txt std_output.txt

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

# clean is called so subsequent `make` calls recompile correct version.
$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $@
	@echo "Executable $(CYAN)$@$(RESET) made"
	@$(MAKE) quietclean

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

# compile_std: $(OBJ)
# 	@$(CC) $(FLAGS) $(OBJ) -o $@
# 	@echo "Executable $(CYAN)$(NAME)$(RESET) made"
# 	@$(MAKE) quietclean

# compile without stress test for quick run
quick:
	@$(MAKE) QUICK=1
	@echo "\n$(GREEN)Compiled without stress tests for quick run$(RESET)"

# simple comparison of output using diff, ignoring only performance times
run:
	@$(MAKE) QUICK=1
	@echo "\nRunning simple $(GREEN)diff$(RESET) test on compiled binaries."
	@echo "Run $(YELLOW)make compare$(RESET) for more detailed comparison."
	@bash -c "diff -I '^Duration.*' <(./ft_bin) <(./std_bin)"
	@echo "If nothing was printed, ft and std binary outputs are identical."

# detailed comparison that shows which test failed and expected vs. received output
compare:
	@$(MAKE) SIMPLE=1
	@echo "\n$(GREEN)Saved output to txt files. Running comparison program$(RESET)"
	@./ft_bin > $(word 1, $(SAVE_FILES))
	@./std_bin > $(word 2, $(SAVE_FILES))
	@$(CC) $(FLAGS) $(COMPARE_SRC) $(TEST_DIR)/tester_helper.cpp -o $(COMPARE_BIN)
	@./$(COMPARE_BIN)

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
	@rm -rf ft_bin std_bin $(SAVE_FILES) $(COMPARE_BIN)
	@echo "$(BLUE)Clean af$(RESET)"

re:
	@echo "$(BLUE)Once more from the top$(RESET)"
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all run debug clean fclean re compare
