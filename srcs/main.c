/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:56:01 by ahammout          #+#    #+#             */
/*   Updated: 2023/07/04 01:05:47 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"


int main(int argc, char **argv)
{
		t_data	parser_data;
		t_all		all;

		if (argc != 2)
				return (printf("Error\n[USAGE]: ./Cub3d [map location]\n") , -1);
		parser(argv, &parser_data);
		if (!init_structs(&all, &parser_data))
				return (EXIT_FAILURE);
		/**/
		draw_minimap(&all);
		cast_rays(&all, &all.ray, &all.player, &all.mlxVars);
		mlx_loop_hook(all.mlxVars.mlx, &key_hook, &all);
		mlx_loop(all.mlxVars.mlx);
		/**/
		free_data(&parser_data);
		printf("Done\n");
		return (0);
} 