/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 00:49:26 by ahammout          #+#    #+#             */
/*   Updated: 2023/06/06 00:16:39 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"

int find_char(char *str, char c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (-1);
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

void    free_data(t_data *data)
{
    free_elements_lst(data);
    free_map(data);
}

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

void exit_error(t_data *data, int fr, char *err)
{
    if (err)
        ft_putstr_fd(err, 2);
    if (fr)
        free_data(data);
     exit (EXIT_FAILURE);
}
