/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:56:01 by ahammout          #+#    #+#             */
/*   Updated: 2023/06/03 18:50:04 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"

int main(int ac, char **av)
{
    t_data  data;

    if (ac == 2)
    {
        data.map = NULL;
        parser(av, &data);
        printf ("The map name: %s\n", av[1]);
    }
    else
        return (printf("Error\n[USAGE]: ./Cub3d [map location]\n") , -1);
    return (0);
}