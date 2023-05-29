/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:19:49 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/09 02:15:44 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*newstr;

	i = 0;
	j = 0;
	if (!s2)
		return ((char *)s1);
	newstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!newstr)
		return (0);
	while (s1[j])
	{
		newstr[j] = s1[j];
		j++;
	}
	while (i < ft_strlen(s2))
	{
		newstr[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	newstr[ft_strlen(s1) + i] = '\0';
	return (newstr);
}
