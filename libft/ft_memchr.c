/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:34:42 by ahammout          #+#    #+#             */
/*   Updated: 2021/11/17 00:27:54 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			cont;
	unsigned char	*st;

	cont = 0;
	st = (unsigned char *)s;
	while (cont < n)
	{
		if (st[cont] == (unsigned char)c)
			return ((unsigned char *)st + cont);
		cont ++;
	}
	return (0);
}
