/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:56:01 by ahammout          #+#    #+#             */
/*   Updated: 2023/05/29 00:59:05 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"

int main(int ac, char **av)
{
    if (ac == 2)
    {
        map_handler(av);
        printf ("The map name: %s\n", av[1]);
    }
    else
        return (printf("Error\n[USAGE]: ./Cub3d [map location]\n") , -1);
    return (0);
}