/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 21:34:40 by ahammout          #+#    #+#             */
/*   Updated: 2023/07/10 05:16:31 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

int	check_extension(char *path)
{
	int		i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '.')
		{
			if (ft_strcmp(path + i, ".cub") == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

int	is_whitespace(char c)
{
	if (!c || c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	ft_2dstrlen(char **str2d)
{
	int	i;

	i = 0;
	if (!str2d)
		return (i);
	while (str2d[i])
		i++;
	return (i);
}

int	empty_line(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (ft_isprint(str[i]))
				return (0);
			i++;
		}
	}
	return (1);
}

int	all_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	display_list(t_info *list)
{
	int	i;
	int	j;

	i = 0;
	printf ("\n/--------------- COMPS LIST -------------------/\n");
	while (list->next)
	{
		j = 0;
		while (list->elem[j])
		{
			printf("NODE [%d]	: ", i);
			printf("Type - %d -: %s\n", list->type, list->elem[j]);
			j++;
		}
		list = list->next;
		i++;
	}
}

void	display_table(char **table)
{
	int i;

	i = 0;
	printf ("\n/--------------- MAP ARRAY -------------------/\n");
	while (table[i])
	{
		printf ("%s\n", table[i]);
		i++;
	}	 
}