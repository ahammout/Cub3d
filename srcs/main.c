/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:56:01 by ahammout          #+#    #+#             */
/*   Updated: 2023/07/10 05:29:28 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

// 1. Fix Minimap
// 2. Norm code
// 3. Ask chatgpt how to check for leaks
// 4. Ask chatgpt how to check for performance
// 5. Ready to eval

int	main(int argc, char **argv)
{
	t_data	parser_data;
	t_all	all;

	if (argc != 2)
		return (printf("Error\n[USAGE]: ./Cub3d [map location]\n"), -1);
	parser(argv, &parser_data);
	if (!init_structs(&all, &parser_data))
		return (EXIT_FAILURE);
	draw_minimap(&all, &all.pars, &all.player);
	cast_rays(&all, &all.ray, &all.player, &all.mlx_vars);
	mlx_loop_hook(all.mlx_vars.mlx, &key_hook, &all);
	mlx_loop(all.mlx_vars.mlx);
	free_data(&parser_data);
	return (0);
}
