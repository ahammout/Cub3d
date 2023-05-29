/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:29:23 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/03 02:29:38 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	size_t	i;

	mem = malloc(count * size);
	if (!mem)
		return (mem);
	i = 0;
	while (i < (count * size))
	{
		mem[i] = 0;
		i++;
	}
	return (mem);
}
