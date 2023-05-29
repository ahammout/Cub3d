/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:06:31 by ahammout          #+#    #+#             */
/*   Updated: 2021/11/20 13:19:19 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*ptr;
	int				i;

	i = 0;
	ptr = (unsigned char *)s;
	while (ptr[i] != (unsigned char)c)
	{
		if (ptr[i] == '\0')
			return (0);
		i++;
	}
	return ((char *)ptr + i);
}
