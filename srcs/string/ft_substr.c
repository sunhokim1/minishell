/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:21:34 by inskim            #+#    #+#             */
/*   Updated: 2023/04/02 18:03:15 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char *s, int start, int len)
{
	char	*sub;
	int		str_len;
	int		i;

	if (!s)
		return (0);
	str_len = ft_strlen(s);
	if (start > str_len)
		return (0);
	s = s + start;
	i = 0;
	while (s[i] && len-- > 0)
		i++;
	sub = (char *)malloc(sizeof(char) * (i + 1));
	if (!sub)
		exit(120);
	len = i;
	i = 0;
	while (len-- > 0)
	{
		sub[i] = s[i];
		i++;
	}
	sub[i] = 0;
	return (sub);
}
