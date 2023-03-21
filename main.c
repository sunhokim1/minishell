/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:53:16 by inskim            #+#    #+#             */
/*   Updated: 2023/03/21 21:39:53 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	//make bulletin commands
	//register signal handler
	char	*line;
	
	while (1)
	{
		line = readline("minishell> ");
		if (line)
		{
			add_history(line);
			handle_line(line);
			free(line);
		}
	}
	return (0);
}
