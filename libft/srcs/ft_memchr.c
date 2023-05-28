/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:34:42 by ahammout          #+#    #+#             */
/*   Updated: 2023/02/23 15:13:51 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
