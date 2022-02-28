# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 09:24:43 by olabrahm          #+#    #+#              #
#    Updated: 2022/02/26 14:08:42 by olabrahm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
FLAGS= -Wall -Wextra -Werror
FILES= 	src/main utils/ft_free_exit src/ft_prompt src/ft_execute utils/ft_cd \
		utils/ft_echo utils/ft_env utils/ft_env_export utils/ft_env_unset \
		utils/ft_pwd utils/ft_setup_env utils/ft_lstutils utils/ft_split_env utils/ft_clean_args \
		utils/ft_free_split_args utils/ft_split_args utils/ft_env_addfront \
		utils/ft_exit utils/ft_perror utils/ft_lowerstr utils/ft_get_vars \
		utils/ft_execute_path utils/ft_token utils/ft_parse_tree utils/ft_args/ft_args
OBJS= $(FILES:=.o)
NAME= minishell
INCLUDES=includes
READLINE=-lreadline
RM= rm -rf
LIBFT= libft.a
LIBFT_PATH= libft/libft.a

.PHONY: all re clean fclean gen 

%.o: %.c 
	@$(CC) $(FLAGS) -I $(INCLUDES) -c $? -o $@ $(CPPFLAGS)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) 
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT_PATH) -I $(INCLUDES) $(READLINE) $(LDFLAGS) -o $(NAME)
	@echo "\033[30;1m---> \033[0mMinishell V1.0 \033[32;1m [OK] \033[0m"

$(LIBFT): 
	@$(MAKE) -C libft

clean:
	@$(RM) $(OBJS)
	@$(MAKE) clean -C libft 
	@echo "\033[30;1m---> \033[0mObject files clean\033[32;1m [DONE] \033[0m"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C libft 
	@echo "\033[30;1m---> \033[0mBinary files clean\033[32;1m [DONE] \033[0m"

gen: fclean all
	clear
	@$(MAKE) clean
	@./minishell

val: all clean
	clear
	valgrind --leak-check=full ./minishell

re: fclean all
