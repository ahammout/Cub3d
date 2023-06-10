/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:01:00 by ahammout          #+#    #+#             */
/*   Updated: 2021/11/17 15:36:08 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)

{
	int				len;
	unsigned char	*ptr;

	len = ft_strlen(s);
	ptr = (unsigned char *)s;
	if (c == '\0')
		return ((char *)&ptr[len]);
	while (ptr[len] != (unsigned char)c)
	{
		if (len == 0)
			return (NULL);
		len--;
	}
	return ((char *)&ptr[len]);
}
