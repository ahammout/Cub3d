/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:25:26 by ahammout          #+#    #+#             */
/*   Updated: 2023/02/23 15:14:08 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memset(void *dest, int c, size_t len)

{
	unsigned char	*ptr;
	int				i;

	i = 0;
	ptr = dest;
	while (len-- > 0)
	{
		ptr[i] = c;
		i++;
	}
	return (ptr);
}
