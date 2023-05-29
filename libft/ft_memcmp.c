/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:24:30 by ahammout          #+#    #+#             */
/*   Updated: 2021/11/12 14:11:25 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)

{
	size_t				i;
	const unsigned char	*str1;
	const unsigned char	*str2;

	i = 0;
	str1 = (const void *)s1;
	str2 = (const void *)s2;
	if (n == 0)
		return (0);
	while (i < n - 1 && str1[i] == str2[i])
			i++;
	return (str1[i] - str2[i]);
}
