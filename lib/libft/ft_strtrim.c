/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:22:53 by ahammout          #+#    #+#             */
/*   Updated: 2023/05/29 16:20:03 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_begin(char const *s1, char const *set)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s1);
	while (i < len)
	{
		if (ft_strchr(set, s1[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

int	ft_end(char const *s1, char const *set)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s1);
	while (i < len)
	{
		if (ft_strchr(set, s1[len - i - 1]) == 0)
			break ;
	i ++;
	}
	return (len - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		begin;
	int		end;
	char	*newstr;

	if (s1 == NULL)
		return (0);
	if (s1[0] == '\0')
		return (ft_strdup(""));
	if (set[0] == '\0' || set == NULL)
		return (ft_strdup(s1));
	begin = ft_begin(s1, set);
	end = ft_end(s1, set);
	if (begin >= end)
		return (ft_strdup(""));
	newstr = (char *) malloc((sizeof(char) * end - begin + 1));
	if (newstr == NULL)
		return (NULL);
	ft_strlcpy(newstr, &s1[begin], end - begin + 1);
	return (newstr);
}
