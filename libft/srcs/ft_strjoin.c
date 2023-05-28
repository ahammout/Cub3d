/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:19:49 by ahammout          #+#    #+#             */
/*   Updated: 2023/02/23 15:15:04 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*word;
	size_t	i;
	size_t	ls1;
	size_t	ls2;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	word = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (word == NULL)
		return (NULL);
	ft_memcpy(word, s1, ls1);
	while (s2[i] && i < ls2)
	{
		word[ls1 + i] = s2[i];
		i++;
	}
	word[ls1 + i] = '\0';
	return (word);
}
