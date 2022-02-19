/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 09:24:08 by olabrahm          #+#    #+#             */
/*   Updated: 2022/02/19 16:40:44 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PIPE 1
# define AND 2
# define OR 3
# define REDIN 4
# define REDOUT 5
# define DELIMIT -7
# define QUOTE -8

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <signal.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

/*		  COMMAND LINKED LISTS		*/
typedef struct s_cmd {
	char			*name;
	char			**args;
	int				num_of_args;
	struct s_opp	*next_opp;
}	t_cmd;

typedef struct s_opp {
	int		token;
	t_cmd	*next_cmd;
}	t_opp;
/*		COMMAND LINKED LISTS - END		*/

/*		  ENV-VARIABLES LISTS		*/
typedef struct s_env_var {
	unsigned int		sort_index;
	unsigned int		index;
	char				*name;
	char				*value;
	char				**both;
	struct s_env_var	*next;
}	t_env_var;

/*		ENV-VARIABLES LISTS - END	*/
typedef struct s_state {
	t_cmd		current_cmd;
	int			man_err;
	char		*line;
	t_env_var	*path;
	int			pid;
	t_env_var	*home;
	t_env_var	*env;
	char		**envtab;
	int			status;
	char		*pwd;
	char		*oldpwd;
}	t_state;

/*			EXITTING			*/
void			ft_free_exit(t_state *state, int status);
void			ft_free_cmd(t_state *state);
void			ft_free_matrix(char **matrix);
void			ft_exit(t_state *state);
/*		 EXITTING - END			*/

/*			SIGNALS				*/
void			ft_handle_sigint(int signal);
void			ft_handle_sigquit(int signal);
/*		 SIGNALS - END			*/

/*			PROMPT				*/
void			ft_prompt(t_state *state);
char			**ft_clean_args(t_state *state);
void			ft_free_split(char **array, size_t len);
char			**ft_split_args(char const *s, char c);
/*		 PROMPT - END			*/

/*				EXECUTION			*/
void			ft_execute(t_state *state);
char			*ft_check_path(t_state *state, char **paths, char **cmdarg);

/*			 EXECUTION - END		*/

/*				ENV-VARIABLES			*/
t_env_var		*ft_setup_env(char **env);
t_env_var		*ft_lstnew(char **value);
t_env_var		*ft_lstlast(t_env_var *head);
t_env_var		*ft_get_env(t_env_var **head, char *name);
unsigned int	ft_lstsize(t_env_var *head);
char			**ft_split_env(char *str, char c);
void			ft_lstadd_back(t_env_var **head, t_env_var *new);
void			ft_lstclear(t_env_var **head);
void			ft_setup_indexes(t_env_var *head);
void			ft_freenode(t_env_var *node);
void			ft_env_addfront(t_env_var **head, char **new);
void			ft_env_add(t_env_var **head, char **new);
void			ft_env_update(t_env_var **head, char **new);
void			ft_get_vars(t_state *state, int *i);
/*			 ENV-VARIABLES - END		*/

/*				BUILTINS			*/
void			ft_cd(t_state *state);
void			ft_echo(t_state *state);
void			ft_env(t_state *state);
void			ft_env_export(t_state *state);
void			ft_env_unset(t_state *state);
void			ft_pwd(t_state *state);
/*			 BUILTINS - END			*/

/*			 	UTILS				*/
char			*get_pwd(char *pwd);
char			*ft_lowerstr(char *str);
void			ft_perror(t_state *state, char *str, int status);
int				ft_empty_line(char *str);
/*			 UTILS - END			*/
#endif