# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 09:24:43 by olabrahm          #+#    #+#              #
#    Updated: 2022/03/03 09:23:51 by olabrahm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
FLAGS= -Wall -Wextra -Werror
FILES= 	src/main utils/exits/ft_free_exit src/ft_prompt src/ft_execute utils/implement/ft_cd \
		utils/implement/ft_echo utils/env/ft_env utils/env/ft_env_export utils/env/ft_env_unset \
		utils/implement/ft_pwd utils/env/ft_setup_env utils/env/ft_lstutils utils/env/ft_split_env utils/parsing/ft_clean_args \
		utils/exits/ft_free_split_args utils/parsing/ft_split_args utils/env/ft_env_addfront \
		utils/exits/ft_exit utils/exits/ft_perror utils/env/ft_get_vars utils/execution/ft_execute_path \
		utils/execution/ft_save_io utils/execution/ft_execution utils/execution/ft_pipe \
		utils/parsing/ft_token utils/parsing/ft_parse_tree utils/args/ft_args \
		utils/parsing/ft_check_tokens utils/parsing/ft_check_syntax

OBJS= $(FILES:=.o)
NAME= minishell
INCLUDES=includes
READLINE=-lreadline
RM= rm -rf
LIBFT= libft.a
LIBFT_PATH= libft/libft.a

.PHONY: all re clean fclean gen val

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
