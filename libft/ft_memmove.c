/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:39:49 by ahammout          #+#    #+#             */
/*   Updated: 2021/11/12 14:17:25 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)

{
	unsigned char	*ds;
	unsigned char	*sr;

	ds = (unsigned char *)dst;
	sr = (unsigned char *)src;
	if (!sr && ! ds)
		return (0);
	if (ds < sr)
		ft_memcpy(dst, src, len);
	else
	{
		while (len--)
			ds[len] = sr[len];
	}
	return (ds);
}
