/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:00:34 by ahammout          #+#    #+#             */
/*   Updated: 2023/05/28 18:50:53 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"

// void    add_node(t_list map, int *new_node)
// {
//     t_list  node;

//     if (new_node == 0)
//     {
        
//     }
    
// }

void    check_line(char *line, t_list ptr)
{
    
}

t_list  file_to_list(int map_fd)
{
    t_list  map;
    t_list  ptr;
    char    *line;
    int     new_node;

    new_node = 0;
    line = ft_strdup("");
    ptr = map;
    while (line)
    {
        free(line);
        line = get_next_line(map_fd);
        check_line (line, ptr);
        add_node(map, &new_node);
        map.line = ft_strdup(line);
    }
    map = ptr;
    return (map);
}

char    **map_handler(char **av)
{
    t_list  map;
    int     **map_table;
    int     map_fd;

    map_fd = open(av[1], O_RDONLY);
    if (map_fd == -1)
    {
        perror("Cub3d");
        exit (EXIT_FAILURE);
    }
    map = file_to_list(map_fd);
    map_table = list_to_table(map);
    //-----------------------------
    return (map_table);
    
}