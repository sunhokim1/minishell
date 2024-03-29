/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:58:03 by inskim            #+#    #+#             */
/*   Updated: 2023/04/04 22:18:41 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	args_count(t_separate_list *list, t_parse *parse)
{
	t_separate_cmd	*cmd;

	cmd = list->data;
	while (cmd)
	{
		if (cmd->str && cmd->str[0] == '|')
			parse = parse->next;
		else if (cmd->str && (cmd->str[0] == '<' || cmd->str[0] == '>'))
			parse->redir_count++;
		else if (cmd->str)
			parse->args_count++;
		cmd = cmd->next;
	}
}

void	parse_malloc(t_cmd *cmd, t_parse *parse)
{
	cmd->file_redirection = malloc(sizeof(char *) * (parse->redir_count + 1));
	if (!cmd->file_redirection)
		exit (1);
	cmd->file_redirection[parse->redir_count] = 0;
	cmd->args = malloc(sizeof(char *) * (parse->args_count + 1));
	if (!cmd->args)
		exit (1);
	cmd->args[parse->args_count] = 0;
}

void	parse_helper(t_separate_cmd *sep, t_cmd *cmd, \
		t_parse *parse, t_list *list)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (sep)
	{
		if (sep->str && sep->str[0] == '|')
		{
			cmd->file_redirection[y] = NULL;
			cmd->args[i] = NULL;
			i = 0;
			y = 0;
			add_cmd(list);
			cmd = cmd->next;
			parse = parse->next;
			parse_malloc(cmd, parse);
		}
		else if (sep->str && (sep->str[0] == '<' || sep->str[0] == '>'))
			cmd->file_redirection[y++] = ft_strdup(sep->str);
		else if (sep->str)
			cmd->args[i++] = ft_strdup(sep->str);
		sep = sep->next;
	}
}

void	parsing(t_list *list, t_separate_list *sep_list, t_parse *parse)
{
	t_separate_cmd	*sep;
	t_cmd			*cmd;

	add_first_cmd(list);
	cmd = list->data;
	sep = sep_list->data;
	parse_malloc(cmd, parse);
	parse_helper(sep, cmd, parse, list);
}
