/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 20:25:53 by ahammout          #+#    #+#             */
/*   Updated: 2021/11/21 11:57:51 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)

{
	size_t	i;
	size_t	k;
	char	*str;
	size_t	needle_len;

	i = 0;
	str = (char *)haystack;
	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return (str);
	while (str[i] != '\0' && i < len)
	{
		k = 0;
		while (needle[k] != '\0' && str[i + k] != '\0'
			&& str[i + k] == needle[k] && i + k < len)
			k++;
		if (k == needle_len)
			return (str + i);
		i++;
	}
	return (0);
}
