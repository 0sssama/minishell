/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 09:24:08 by olabrahm          #+#    #+#             */
/*   Updated: 2022/01/17 17:24:28 by obouadel         ###   ########.fr       */
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
# include <signal.h>
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
	char		*path;
	int			pid;
	char		*home;
	t_env_var	*env;
	char		**envtab;
}	t_state;

/*			EXITTING			*/
void			ft_free_exit(t_state *state, int status);
void			ft_free_cmd(t_state *state);
void			ft_free_matrix(char **matrix);
/*		 EXITTING - END			*/

/*			SIGNALS				*/
void			ft_handle_sigint(int signal);
void			ft_handle_sigkill(int signal);
/*		 SIGNALS - END			*/

/*			PROMPT				*/
void			ft_prompt(t_state *state);
char			**ft_clean_args(t_state *state);
/*		 PROMPT - END			*/

/*				EXECUTION			*/
void			ft_execute(t_state *state);
/*			 EXECUTION - END		*/

/*				ENV-VARIABLES			*/
t_env_var		*ft_setup_env(char **env);
t_env_var		*ft_lstnew(char **value);
t_env_var		*ft_lstlast(t_env_var *head);
unsigned int	ft_lstsize(t_env_var *head);
char			**ft_split_env(char *str, char c);
void			ft_lstadd_back(t_env_var **head, t_env_var *new);
void			ft_lstclear(t_env_var **head);
void			ft_setup_indexes(t_env_var *head);
void			ft_freenode(t_env_var *node);
t_env_var		*ft_get_env(t_env_var **head, char *name);
/*			 ENV-VARIABLES - END		*/

/*				BUILTINS			*/
void			ft_cd(t_state *state);
void			ft_echo(t_state *state);
void			ft_env(t_state *state);
void			ft_env_export(t_state *state);
void			ft_env_unset(t_state *state);
void			ft_pwd(t_state *state);
/*			 BUILTINS - END			*/

#endif