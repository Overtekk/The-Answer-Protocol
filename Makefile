# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/14 10:15:36 by roandrie          #+#    #+#              #
#    Updated: 2026/09/15 09:41:19 by roandrie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --------------- #
#    VARIABLES    #
# --------------- #

SERVER_NAME	=	tap_server
CLI_CLIENT	=	tap_cli_client
GUI_CLIENT	=	tap_gui_client

BUILD_DIR = build

SUBMODULE_DIRS	= libraries/raylib libraries/yaml-cpp libraries/json

# --------------- #
#      RULES      #
# --------------- #

.PHONY:		all server cli_client gui_client clean fclean re
.SILENT:

all:	git_absolute $(SERVER_NAME) $(CLI_CLIENT) $(GUI_CLIENT)

server:	fclean git_absolute $(SERVER_NAME)

cli_client:	fclean git_absolute $(CLI_CLIENT)

gui_client:	fclean git_absolute $(GUI_CLIENT)

git_absolute:
			@missing=0; \
			for dir in $(SUBMODULE_DIRS); do \
				if [ ! -f "$$dir/CMakeLists.txt" ]; then \
					missing=1; \
					break; \
				fi; \
			done; \
			if [ $$missing -eq 1 ]; then \
				echo "$(BRED)Downloading missing libraries...$(RESET)"; \
				git submodule update --init --recursive; \
			else \
				echo "$(BLUE)All libraries found$(RESET)"; \
			fi

$(BUILD_DIR)/build.ninja	$(BUILD_DIR)/Makefile:
				@mkdir -p $(BUILD_DIR)
				@echo "$(YELLOW)Configuring CMake in $(BUILD_DIR)...$(RESET)"
				cmake -B $(BUILD_DIR) -S .

$(SERVER_NAME):	$(BUILD_DIR)/Makefile
				@echo "$(CYAN)Building $(SERVER_NAME)...$(RESET)"
				cmake --build $(BUILD_DIR) --target $(SERVER_NAME) -- --no-print-directory
				@echo "$(BGREEN)$(SERVER_NAME) Done!$(RESET)"

$(CLI_CLIENT):	$(BUILD_DIR)/Makefile
				@echo "$(CYAN)Building $(CLI_CLIENT)...$(RESET)"
				cmake --build $(BUILD_DIR) --target $(CLI_CLIENT) -- --no-print-directory
				@echo "$(BGREEN)$(CLI_CLIENT) Done!$(RESET)"

$(GUI_CLIENT):	$(BUILD_DIR)/Makefile
				@echo "$(CYAN)Building $(GUI_CLIENT)...$(RESET)"
				cmake --build $(BUILD_DIR) --target $(GUI_CLIENT) -- --no-print-directory
				@echo "$(BGREEN)$(GUI_CLIENT) Done!$(RESET)"

clean:
			@if [ -d "$(BUILD_DIR)" ]; then \
				echo "$(MAGENTA)Cleaning build artifacts...$(RESET)"; \
				cmake --build $(BUILD_DIR) --target clean 2>/dev/null -- --no-print-directory || true; \
			fi

fclean:	clean
		@echo "$(BRED)Full cleanup (removing $(BUILD_DIR) and binaries)...$(RESET)"
		rm -rf $(BUILD_DIR)
		rm -f $(SERVER_NAME) $(CLI_CLIENT) $(GUI_CLIENT)
		@echo "$(GREEN)Clean complete.$(RESET)"

re:		fclean all

# --------------- #
#     COLORS      #
# --------------- #

BLUE		=		\033[96m
MAGENTA		=		\033[35m
GREEN		=		\033[32m
CYAN		=		\033[36m
YELLOW		=		\033[93m
BOLD		=		\033[1m
BGREEN		=		\033[92m
BRED		=		\033[91m
BMAGENTA	=		\033[95m
UNDERLINE	=		\033[4m
ITALIC		=		\033[3m
RESET		=		\033[0m
