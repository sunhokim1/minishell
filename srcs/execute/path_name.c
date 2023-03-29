/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 22:42:26 by inskim            #+#    #+#             */
/*   Updated: 2023/03/29 22:02:31 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char	*cmd_strjoin(char *s1, char *s2)
{
	int		len;
	char	*p;
	int		i;

	if (!s1 || !s2)
		exit(127);
	len = ft_strlen(s1) + ft_strlen(s2);
	p = (char *)malloc(sizeof(char) * (len + 2));
	if (!p)
		exit(127);
	i = 0;
	while (*s1)
		p[i++] = *s1++;
	p[i++] = '/';
	while (*s2)
		p[i++] = *s2++;
	p[i] = 0;
	return (p);
}

char	**get_path_variable(char **envp)
{
	if (!envp)
		return (0);
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
			return (ft_split(&((*envp)[5]), ':'));
		envp++;
	}
	return (0);
}

char	*get_pathname(char *command, char **envp)
{
	char	*pathname;
	char	**envp_path;
	
	envp_path = get_path_variable(envp);
	pathname = 0;
	while (*envp_path)
	{
		pathname = cmd_strjoin(*envp_path++, command);
		if (!access((const char *)pathname, F_OK | X_OK))
			break ;
		free(pathname);
		pathname = 0;
	}
	if (pathname)
		return (pathname);
	else if (!access((const char *)command, F_OK | X_OK))
		return (command);
	print_term("./srcs/: is a directory\n");//126
	print_term("./ssss: No such file or directory\n");//127
	print_term("./minishell: Permission denied\n");//126
	return (0);
}