# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/14 10:15:36 by roandrie          #+#    #+#              #
#    Updated: 2026/09/14 10:57:22 by roandrie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

/ --------------- \
/    VARIABLES    \
/ --------------- \

SERVER_NAME	=	tap_server
CLI_CLIENT	=	tap_cli_client
GUI_CLIENT	=	tap_gui_client

BUILD_DIR = build
cmake -B $(BUILD_DIR) -S .

/ --------------- \
/      RULES      \
/ --------------- \

.PHONY:		all clean fclean re
.SILENT:

all:	$(SERVER_NAME) $(CLI_CLIENT) $(GUI_CLIENT)

$(SERVER_NAME):
				cmake --build $(BUILD_DIR) --target $(SERVER_NAME)

$(CLI_CLIENT):
				cmake --build $(BUILD_DIR) --target $(CLI_CLIENT)

$(GUI_CLIENT):
				cmake --build $(BUILD_DIR) --target $(GUI_CLIENT)

clean:
		cmake --build $(BUILD_DIR) --target clean

fclean:	clean
		rm -rf $(BUILD_DIR)
		rm -f $(SERVER_NAME) $(CLI_CLIENT) $(GUI_CLIENT)

/ --------------- \
/     COLORS      \
/ --------------- \

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
