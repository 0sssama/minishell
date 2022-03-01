/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 19:48:56 by olabrahm          #+#    #+#             */
/*   Updated: 2022/03/01 16:26:13 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_istoken(char c)
{
	return (c == PIPE || c == REDIN || c == REDOUT
		|| c == APPEND || c == HEREDOC);
}

/*
	This function checks if there is a token '<', '>', '|'..
	inside of a given string.
*/
int	ft_contains_token(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (ft_istoken(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	ft_str_istoken(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_istoken(str[i]))
			return (0);
		i++;
	}
	return (str[i - 1]);
}

t_cmd	*ft_free_tree(t_cmd **head)
{
	t_cmd	*current_node;
	t_cmd	*tmp;

	if (!head || !(*head))
		return (NULL);
	current_node = *head;
	while (current_node)
	{
		free(current_node->name);
		current_node->name = NULL;
		free(current_node->file);
		current_node->file = NULL;
		if (current_node->fd)
			close(current_node->fd);
		ft_free_matrix(current_node->args);
		tmp = current_node->next;
		free(current_node);
		current_node = tmp;
	}
	return (NULL);
}

char	ft_token_to_char(char token)
{
	if (token == PIPE)
		return ('|');
	if (token == REDIN || token == HEREDOC)
		return ('<');
	if (token == REDOUT || token == APPEND)
		return ('>');
	return (token);
}

char	*ft_token_to_str(char *tokenized_str)
{
	unsigned int	i;
	char			*output;
	unsigned int	size;

	if (!tokenized_str)
		return (NULL);
	i = 0;
	size = ft_strlen(tokenized_str);
	output = (char *) malloc((size + 1) * sizeof(char));
	while (tokenized_str[i])
	{
		output[i] = ft_token_to_char(tokenized_str[i]);
		i++;
	}
	return (output);
}

t_cmd	*ft_parse_tree(char **cmd)
{
	unsigned int	i;
	t_cmd			*previous_node;
	t_cmd			*current_node;
	t_cmd			*head;
	int				inside_cmd;
	int				file[2];
	t_cmd			*last_cmd;
	char			*tmp;

	i = 0;
	inside_cmd = 0;
	file[0] = 0; // means we passed a file, and need to add args to last cmd
	file[1] = 0; // means we expect a file in the next arg
	previous_node = NULL;
	head = NULL;
	current_node = NULL;
	while (cmd[i])
	{
		if (ft_str_istoken(cmd[i]) == 0)
		{
			if (inside_cmd)
			{
				if (file[0]) // means we just passed a file, and need to add args to previous cmd
				{
					last_cmd->args = ft_add_arg(last_cmd->args, cmd[i]);
					(last_cmd->num_of_args)++;
				}
				else if (file[1]) // means we found a file
				{
					current_node->file = ft_strdup(cmd[i]);
					file[0] = 1;
					current_node->fd = open(current_node->file, O_CREAT | O_RDWR);
				}
				else
				{
					// we are inside cmd, add to args
					current_node->args = ft_add_arg(current_node->args, cmd[i]);
					(current_node->num_of_args)++;
				}
			}
			else
			{
				// found new command, create new node with cmd name and args
				previous_node = current_node;
				current_node = (t_cmd *) malloc(sizeof(t_cmd));
				if (previous_node)
					previous_node->next = current_node;
				if (!current_node)
					return (ft_free_tree(&head));
				if (i == 0)
					head = current_node;
				inside_cmd = 1;
				current_node->name = ft_strdup(ft_lowerstr(cmd[i]));
				current_node->num_of_args = 1;
				current_node->args = ft_init_args(cmd[i]);
				current_node->file = NULL;
				current_node->fd = 0;
				current_node->token = 0;
				current_node->next = NULL;
				last_cmd = current_node;
			}
		}
		else {
			if (inside_cmd)
			{
				// found token, create new node with it.
				previous_node = current_node;
				current_node = (t_cmd *) malloc(sizeof(t_cmd));
				previous_node->next = current_node;
				if (!current_node)
					return (ft_free_tree(&head));
				current_node->name = NULL;
				current_node->args = NULL;
				current_node->num_of_args = 0;
				current_node->next = NULL;
				current_node->file = NULL;
				current_node->fd = 0;
				current_node->token = ft_str_istoken(cmd[i]);
				inside_cmd = ft_str_istoken(cmd[i]) == REDOUT;
				file[0] = 0;
				// means if we found a REDOUT, we expect next arg to be file.
				file[1] = ft_str_istoken(cmd[i]) == REDOUT;
			}
			else
			{
				tmp = ft_token_to_str(cmd[i]);
				ft_put_error(NULL, "syntax error near unexpected token `");
				ft_putstr_fd(tmp, 2);
				ft_putstr_fd("`\n", 2);
				free(tmp);
				tmp = NULL;
				ft_free_matrix(cmd);
				return (ft_free_tree(&head));
			}
		}
		i++;
	}
	ft_free_matrix(cmd);
	return (head);
}
