/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:52:13 by ahammout          #+#    #+#             */
/*   Updated: 2023/06/10 02:03:04 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"

int is_whitespace(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
    return (0);
}

int ft_2dstrlen(char **str2d)
{
    int i;

    i = 0;
    if (!str2d)
        return (i);
    while (str2d[i])
        i++;
    return (i);
}

void    free_2darray(t_data *data)
{
    int i;

    i = 0;
    if (data->map)
    {
        while (data->map[i])
        {
            free(data->map[i]);
            i++;
        }
        free(data->map);
    }
    data->map = NULL;
    
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

int all_isdigit(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

void    display_list(t_info *list)
{
    int i;
    int j;

    i = 0;
    printf ("\n/--------------- COMPS LIST -------------------/\n");
    while (list->next)
    {
        j = 0;
        while (list->elem[j])
        {
            printf("NODE [%d]   : ", i);
            printf("Type - %d -: %s\n", list->type, list->elem[j]);
            j++;
        }
        list = list->next;
        i++;
    }
}

void    display_table(char **table)
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