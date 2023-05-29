/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:04:22 by ahammout          #+#    #+#             */
/*   Updated: 2021/11/12 14:16:29 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ds;
	unsigned char	*sr;

	ds = (unsigned char *)dst;
	sr = (unsigned char *)src;
	if (!sr && !ds)
		return (0);
	i = 0;
	while (i < n)
	{
		ds[i] = sr[i];
		i++;
	}
	return (dst);
}
