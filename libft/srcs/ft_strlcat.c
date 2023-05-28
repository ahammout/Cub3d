/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 21:00:27 by ahammout          #+#    #+#             */
/*   Updated: 2023/02/23 15:15:07 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
