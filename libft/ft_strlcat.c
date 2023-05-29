/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 21:00:27 by ahammout          #+#    #+#             */
/*   Updated: 2021/11/12 14:31:47 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	ldst;
	size_t	lsrc;

	i = 0;
	ldst = ft_strlen(dst);
	lsrc = ft_strlen(src);
	if (dstsize <= ldst)
		return (dstsize + lsrc);
	while (src[i] && ldst + i < dstsize - 1)
	{
		dst[ldst + i] = src[i];
		i ++;
	}
	dst[ldst + i] = '\0';
	return (ldst + lsrc);
}
