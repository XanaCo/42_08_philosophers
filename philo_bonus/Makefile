# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 18:07:11 by ancolmen          #+#    #+#              #
#    Updated: 2023/06/23 10:15:28 by ancolmen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#######	VARIABLES #######

NAME		= philo_bonus

INC			= philo_bonus.h

SRC			=	main_bonus.c \
				check_and_stock_bonus.c \
				check_and_flag_bonus.c \
				create_bonus.c \
				routine_bonus.c \
				utils_bonus.c \
				exit_bonus.c 

OBJ			= ${SRC:.c=.o}

CC			= cc

CFLAGS		= -Wall -Wextra -Werror -pthread

RM			= rm -rf

LEAKS 	= valgrind

LF 		= --leak-check=full \
        	--show-leak-kinds=all \
    		--track-origins=yes \
    		--verbose \

#######	RULES #######

${NAME}: ${OBJ}
	@ echo "\033[97;4m🚧 philo in progress 🚧\033[0m\n"
	@ ${CC} ${CFLAGS} -o ${NAME} ${OBJ}
	@ echo "\033[32;1m✅ PHILOSOPHERS READY ✅\033[0m\n"

${OBJ}: ${SRC}
	@ echo "\n\033[97;4m🚧 creating object files 🚧\033[0m\n"
	@ ${CC} ${CFLAGS} -c -I ${INC} ${SRC}
	@ echo "\033[32;1m★ Objects OK ★\033[0m\n"

all: ${NAME}

bonus: all

clean:
	@ echo "\n\033[97;4m🚧 cleaning object files 🚧\033[0m\n"
	@ ${RM} ${OBJ}
	@ echo "\033[32;1m★ objects cleaned ★\033[0m\n"
	

fclean: clean
	@ ${RM} ${NAME}

re: fclean all

rebonus: fclean bonus

# leaks:
# 	${LEAKS} ${LF}

.PHONY: all clean fclean re bonus rebonus
