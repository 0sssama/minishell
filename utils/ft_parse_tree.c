/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrahm <olabrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 19:48:56 by olabrahm          #+#    #+#             */
/*   Updated: 2022/02/26 16:14:09 by olabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_istoken(char c)
{
	return (c == PIPE || c == REDIN || c == REDOUT
		|| c == APPEND || c == HEREDOC);
}

// /*
// 	This function checks if there is a token '<', '>', '|'..
// 	inside of a given string.
// */
// static int	ft_contains_token(char *str)
// {
// 	unsigned int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (ft_istoken(str[i]))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

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

	i = 0;
	inside_cmd = 0;
	previous_node = NULL;
	head = NULL;
	current_node = NULL;
	while (cmd[i])
	{
		if (ft_str_istoken(cmd[i]) == 0)
		{
			if (inside_cmd)
			{
				// we are inside cmd, add to args
				current_node->args = ft_add_arg(current_node->args, cmd[i]);
				(current_node->num_of_args)++;
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
				current_node->token = 0;
				current_node->next = NULL;
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
				current_node->next = NULL;
				current_node->token = ft_str_istoken(cmd[i]);
				inside_cmd = 0;
			}
			else
			{
				ft_put_error(NULL, "syntax error near unexpected token `");
				ft_putstr_fd(ft_token_to_str(cmd[i]), 2);
				ft_putstr_fd("`\n", 2);
				return (ft_free_tree(&head));
			}
		}
		i++;
	}
	ft_free_matrix(cmd);
	return (head);
}
