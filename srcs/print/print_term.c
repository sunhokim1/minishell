/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_term.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 22:45:17 by inskim            #+#    #+#             */
/*   Updated: 2023/03/26 17:40:30 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_term(char *str)
{
	printf("%s", str);
}

void	print_term_exit(char *str, int exit_code)
{
	printf("%s", str);
	exit(exit_code);
}
