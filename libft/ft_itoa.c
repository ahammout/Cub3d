/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:25:51 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/09 02:11:40 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrlen(int nbr)
{
	int	size;

	size = 0;
	if (nbr <= 0)
		size++;
	while (nbr)
	{
		size++;
		nbr /= 10;
	}
	return (size);
}

char	*ft_itoa(int nbr)
{
	int		size;
	char	*str;

	size = ft_nbrlen(nbr);
	str = malloc(sizeof(char) * size + 1);
	str[size--] = '\0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	if (nbr == 0)
		str[size] = '0';
	while (nbr)
	{
		str[size--] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (str);
}

// static	size_t	ft_intlen(int n)
// {
// 	size_t	len;

// 	len = 0;
// 	if (n <= 0)
// 		len = 1;
// 	while (n != 0)
// 	{
// 		len ++;
// 		n = n / 10;
// 	}
// 	return (len);
// }

// static	char	*ft_convert_n(char *n_str, size_t num, size_t len)
// {
// 	while (num > 0)
// 	{
// 		n_str[len--] = (num % 10) + '0';
// 		num = num / 10;
// 	}
// 	return (n_str);
// }

// char	*ft_itoa(int n)
// {
// 	char	*n_str;
// 	size_t	len;
// 	long	num;

// 	num = n;
// 	len = ft_intlen(n);
// 	n_str = malloc(sizeof(char) * (len + 1));
// 	if (!n_str)
// 		return (NULL);
// 	n_str[len--] = '\0';
// 	if (n == 0)
// 		n_str[0] = '0';
// 	if (n < 0)
// 	{
// 		num = num * (-1);
// 		n_str[0] = '-';
// 		n_str = ft_convert_n(n_str, num, len);
// 	}
// 	else
// 	{
// 		n_str = ft_convert_n(n_str, num, len);
// 	}
// 	return (n_str);
// }
