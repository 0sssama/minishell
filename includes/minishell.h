/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouadel <obouadel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 09:24:08 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/11 18:56:22 by obouadel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PIPE -1 // |
# define WILDCARD -2 // *
# define REDIN -4 // <
# define REDOUT -5 // >
# define APPEND -6 // >>
# define DELIMIT -7 // ' '
# define HEREDOC -9 // <<
# define QUOTE -10 // ' "
# define ENV_SIGN -11 // $
# define EXIT_STATUS -12 // $?

# define OUT_OF_MEM 12

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

/*		  COMMAND LINKED LISTS		*/
typedef struct s_cmd {
	char			*name;
	char			**args;
	char			*file;
	int				fd;
	int				token;
	char			*eof;
	unsigned int	num_of_args;
	struct s_cmd	*next;
}	t_cmd;

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
	t_env_var	*path;
	t_env_var	*home;
	t_env_var	*env;
	t_cmd		*cmd_tree;
	int			io[2];
	int			**fds;
	int			*pids;
	int			pipes;
	char		**envtab;
	char		*line;
	char		*pwd;
	char		*oldpwd;
	int			man_err;
	int			status;
	int			sig;
	int			pid;
}	t_state;

/*			EXITTING			*/
void			ft_free_exit(t_state *state, int status);
void			ft_free_matrix(char **matrix);
/*		 EXITTING - END			*/

/*			SIGNALS				*/
void			ft_handle_sigint_parent(int signal);
/*		 SIGNALS - END			*/

/*			PROMPT				*/
void			ft_prompt(t_state *state);
char			**ft_clean_args(t_state *state);
void			ft_free_split(char **array, size_t len);
char			**ft_split_args(char *s, char c);
/*		 PROMPT - END			*/

/*				EXECUTION			*/
void			ft_execute(t_state *state, t_cmd *current_cmd);
void			ft_execution(t_state *state);
char			*ft_check_path(t_state *state, char **paths, char **cmdarg);
char			*ft_check_relative(t_state *state, char *cmd);
void			ft_pipe_it(t_state *state, t_cmd *current_cmd, int i);
int				ft_get_pipes(t_cmd **cmd_tree);
void			ft_setup_pipe(t_state *state);
void			ft_exec_cmd(t_state *state, t_cmd *cmd);
void			ft_loop_pipe(t_state *state, t_cmd *current_node);
void			ft_save_io(t_state *state);
void			ft_reset_io(t_state *state);
void			ft_free_pipefds(t_state *state, int i);
void			ft_free_setup(t_state *state, int i);
/*			 EXECUTION - END		*/

/*				PARSING			*/
t_cmd			*ft_parse_tree(char **cmd);
t_cmd			*ft_free_tree(t_cmd **head);
char			**ft_check_tokens(char **cmd);
char			**ft_replace_wildcard(t_state *state, char **cmd);
char			**ft_wildcard(void);
char			*ft_token_to_str(char *tokenized_str);
char			*ft_put_exitcode(t_state *state, char *str);
int				ft_token(char *line);
int				ft_istoken(char c);
int				ft_contains_token(char *str);
int				ft_check_syntax(char **cmd, char *line);
int				ft_get_token(char *str);
int				ft_heredoc(char *eof);
int				ft_is_wildcard(char *str);
int				ft_is_literal_wildcard(char *str);
/*			 PARSING - END		*/

/*				ENV-VARIABLES			*/
t_env_var		*ft_setup_env(char **env);
t_env_var		*ft_lstnew(char **value);
t_env_var		*ft_lstlast(t_env_var *head);
t_env_var		*ft_get_env(t_env_var **head, char *name);
t_env_var		*ft_default_env(t_env_var *old_env);
unsigned int	ft_lstsize(t_env_var *head);
char			**ft_split_env(char *str, char c);
char			*ft_add_backslash(char *value);
char			**ft_update_envtab(t_state *state);
void			ft_lstadd_back(t_env_var **head, t_env_var *new);
void			ft_lstclear(t_env_var **head);
void			ft_setup_indexes(t_env_var *head);
void			ft_freenode(t_env_var *node);
void			ft_env_addfront(t_env_var **head, char **new);
void			ft_env_add(t_env_var **head, char **new);
void			ft_env_update(t_env_var **head, char **new);
void			ft_get_vars(t_state *state, int *i);
void			ft_add_shlvl(t_env_var **env_lst, unsigned int *i);
void			ft_update_env(t_state *state);
/*			 ENV-VARIABLES - END		*/

/*				BUILTINS			*/
void			ft_cd(t_state *state, t_cmd *current_cmd);
void			ft_echo(t_state *state, t_cmd *current_cmd);
void			ft_env(t_state *state, t_cmd *current_cmd);
void			ft_env_export(t_state *state, t_cmd *current_cmd);
void			ft_env_unset(t_state *state, t_cmd *current_cmd);
void			ft_pwd(t_state *state);
void			ft_exit(t_state *state, t_cmd *current_cmd);
/*			 BUILTINS - END			*/

/*				ARGS UTILS			*/
unsigned int	ft_args_len(char **args);
char			**ft_init_args(char *init);
char			**ft_add_arg(char **args, char *new_arg);
char			**ft_merge_args(char **args1, char **args2);
void			*ft_free_args_len(char **args, unsigned int len);
void			ft_free_matrixes(char **m1, char **m2);
void			ft_cpy_matrix(char **input, char **output, unsigned int *i);
/*			ARGS UTILS - END		*/

/*			 	UTILS				*/
char			*get_pwd(char *pwd);
void			ft_perror(t_state *state, char *str, int status);
int				ft_empty_line(char *str);
void			ft_put_error(char *name, char *error);
void			ft_close(t_state *state);
void			ft_free_temp(char **s1);
void			ft_free_childs(t_state *state, int status);
void			ft_handle_status(t_state *state);
/*			 UTILS - END			*/
#endif