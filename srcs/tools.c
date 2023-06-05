/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:52:13 by ahammout          #+#    #+#             */
/*   Updated: 2023/06/05 18:48:28 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"

void    free_elements_lst(t_data *data)
{
    t_map   *tofree;

    if (data->lmap)
    {
        while (data->lmap)
        {
            tofree = data->lmap;
            free(data->lmap->line);
            data->lmap = data->lmap->next;
            free(tofree);
        }
    }
}

void    free_map(t_data *data)
{
    int i;

    i = 0;
    while (data->map[i])
    {
        free(data->map[i]);
        i++;
    }
    free(data->map);
}

void    free_data(t_data *data)
{
    free_elements_lst(data);
    free_map(data);
}

void exit_error(t_data *data, int fr, char *err)
{
    if (err)
        ft_putstr_fd(err, 2);
    if (fr)
        free_data(data);
     exit (EXIT_FAILURE);
}

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

void    add_node(t_data *data, int *index_ptr, t_map **ptr)
{
    t_map  *node;

    if (*index_ptr == 0)
    {
        data->map = NULL;
        data->lmap = malloc(sizeof(t_map));
        if (!data->lmap)
            exit_error(data, 0, "Cub3d: Allocation failed");
        data->lmap->index = *index_ptr;
        data->lmap->line = NULL;
        data->lmap->next = NULL;
        data->lmap->prev = NULL;
        *ptr = data->lmap;
    }
    else if (*index_ptr > 0)
    {
        node = malloc(sizeof(t_map));

        node->index = *index_ptr;
        node->line = NULL;
        node->next = NULL;
        data->lmap->next = node;
        data->lmap = data->lmap->next;
    } 
}

void    free_2darray(t_data *data)
{
    int i;

    i = 0;
    while (data->map[i])
    {
        free(data->map[i]);
        i++;
    }
    free(data->map);
    data->map = NULL;
    
}





int	empty_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]))
			return (0);
		i++;
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

void    display_list(t_map *list)
{
    int i;

    i = 0;
    printf ("\n/--------------- COMPS LIST -------------------/\n");
    while (list)
    {
        printf("NODE [%d]: %s\n", i, list->line);
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
        printf ("LINE [%d]: %s\n", i, table[i]);
        i++;
    }
    printf ("LINE [%d]: %s\n", i, table[i]);
    
}