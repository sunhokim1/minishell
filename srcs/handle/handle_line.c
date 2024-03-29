/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 20:37:44 by insub             #+#    #+#             */
/*   Updated: 2023/04/05 05:58:34 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(int *pipe, char ***envp, int *status)
{
	char	c;

	close(pipe[1]);
	c = 0;
	read(pipe[0], &c, 1);
	if (c == 'M')
		add_env(pipe[0], envp);
	else if (c == 'D')
		delete_env(pipe[0], envp);
	else if (c == 'C')
		change_dir(pipe[0], envp, status);
	else if (c == 'E')
		exit(get_status(pipe[0]));
	close(pipe[0]);
}

void	wait_child(t_list *cmd_list, int *status, int *pipe, char ***envp)
{
	t_cmd	*node;
	int		pid;
	int		tmp;

	node = cmd_list->data;
	while (node)
	{
		pid = node->pid;
		if (pid)
			waitpid(-1, &tmp, 0);
		if (WIFEXITED(tmp))
			*status = WEXITSTATUS(tmp);
		else if (WIFSIGNALED(tmp))
			*status = WTERMSIG(tmp);
		else
			*status = 124;
		node = node->next;
	}
	set_env(pipe, envp, status);
}

void	separate_dup(t_separate_list *list)
{
	t_separate_cmd	*cmd;
	t_separate_cmd	*tmp;

	cmd = list->data;
	while (cmd)
	{
		if ((ft_strlen(cmd->str) == 1 && (cmd->str[0] == '<'
					|| cmd->str[0] == '>')) || (ft_strlen(cmd->str) == 2
				&& ((cmd->str[0] == '<' && cmd->str[1] == '<')
					|| (cmd->str[0] == '>' && cmd->str[1] == '>'))))
		{
			if (cmd->next->str[0] != '|' && cmd->next->str[0] != '<'
				&& cmd->next->str[0] != '>')
			{
				tmp = cmd->next->next;
				cmd->str = heredoc_strjoin(cmd->str, cmd->next->str);
				cmd->next->endline = 0;
				cmd->next->startline = 0;
				free(cmd->next->str);
				free(cmd->next);
				cmd->next = tmp;
			}
		}
		cmd = cmd->next;
	}
}

void	handle_line(char *line, char ***envp, int *status, struct termios *term)
{
	t_list			*cmd_list;
	t_separate_list	*separate_list;
	t_parse			*parse;
	int				std_fd[4];
	int				save_prev_status;

	save_prev_status = *status;
	*status = 0;
	separate_list = init_cmd_list();
	cmd_list = init_list();
	parse = init_parse();
	line = env_handle(ft_strdup(line), save_prev_status, *envp);
	ready_separate(separate_list, line, status);
	if (check_list_quote(separate_list, status))
		set_parse(cmd_list, separate_list, parse);
	set_cmd(cmd_list, std_fd);
	if (handle_heredoc(cmd_list, term, *envp) && !*status)
	{
		execute_cmd_list(cmd_list, *envp, std_fd, save_prev_status);
		wait_child(cmd_list, status, &(std_fd[2]), envp);
	}
	reset_handle(std_fd, parse, cmd_list, separate_list);
	free(line);
}
