/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:19:14 by insub             #+#    #+#             */
/*   Updated: 2023/03/26 17:21:19 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_is_space(char *str)
{
    while (*str)
    {
        if (*str != ' ' && *str != '\t')
            return (0);
        str++;
    }
    return (1);
}