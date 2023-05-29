/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:34:06 by ahammout          #+#    #+#             */
/*   Updated: 2023/04/01 23:37:15 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_free(size_t count_words, char **newtab)
{
	while (count_words != 0)
		free(newtab[--count_words]);
	free(newtab);
}

static	size_t	number_of_words(const char *s, char c)
{
	size_t	i;
	size_t	w;

	i = 0;
	w = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			w++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (w);
}

static	size_t	strlen_c(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*strdup_c(const char *s, char c)
{
	int		i;
	char	*s2;

	i = 0;
	s2 = (char *) malloc(sizeof(char) * strlen_c(s, c) + 1);
	if (!s2)
		return (0);
	while (s[i] && s[i] != c)
	{
		s2[i] = s[i];
		i ++;
	}
	s2[i] = '\0';
	return (s2);
}

char	**ft_split(char const *s, char c)
{
	char	**newtab;
	size_t	i;
	size_t	count_words;

	i = 0;
	count_words = 0;
	if (!s)
		return (0);
	newtab = malloc(sizeof(char *) * (number_of_words(s, c) + 1));
	if (!newtab)
		return (0);
	while (count_words < number_of_words(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			newtab[count_words] = strdup_c(s + i, c);
		if (!newtab[count_words])
			ft_free(count_words, newtab);
		count_words++;
		while (s[i] && s[i] != c)
			i++;
	}
	newtab[count_words] = 0;
	return (newtab);
}
