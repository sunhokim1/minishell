/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_char_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:18:18 by inskim            #+#    #+#             */
/*   Updated: 2023/04/02 18:02:44 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_char_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}
