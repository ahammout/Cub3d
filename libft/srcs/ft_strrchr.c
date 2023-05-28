/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:01:00 by ahammout          #+#    #+#             */
/*   Updated: 2023/02/23 15:15:38 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
