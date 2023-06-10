/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:56:01 by ahammout          #+#    #+#             */
/*   Updated: 2023/06/10 11:13:58 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"


// void    f()
// {
//     system("leaks Cub3d");
// }

int main(int ac, char **av)
{
    t_data  data;
    // atexit(f);
    if (ac == 2)
    {
        data.map = NULL;
        parser(av, &data);
    }
    else    
        return (printf("Error\n[USAGE]: ./Cub3d [map location]\n") , -1);
    // free_data(&data);
    return (0);
} 