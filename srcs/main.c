/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:56:01 by ahammout          #+#    #+#             */
/*   Updated: 2023/07/15 10:45:43 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	leaks(void)
{
	system("leaks -q Cub3D");
}

int	main(int argc, char **argv)
{
	t_data	parser_data;
	t_all	all;

	atexit(leaks);
	if (argc != 2)
		return (printf("Error\n[USAGE]: ./Cub3d [map location]\n"), -1);
	parser(argv, &parser_data);
	if (!init_structs(&all, &parser_data))
	{
		free_data(&parser_data);
		return (EXIT_FAILURE);
	}
	draw_minimap(&all, &all.pars, &all.player);
	cast_rays(&all, &all.ray, &all.player, &all.mlx_vars);
	mlx_loop_hook(all.mlx_vars.mlx, &key_hook, &all);
	mlx_loop(all.mlx_vars.mlx);
	free_data(&parser_data);
	return (0);
}
