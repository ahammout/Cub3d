/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:56:01 by ahammout          #+#    #+#             */
/*   Updated: 2023/07/02 20:36:55 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	get_map_dimension(t_pars *pars, char **map, t_player *player, t_all *all)
{
	int		x_idx;
	int		tmp;

	while (map[pars->map_height])
	{
		x_idx = 0;
		tmp = 0;
		while (map[pars->map_height][x_idx])
		{
			if (map[pars->map_height][x_idx] != '\0')
				tmp++;
			if (incl_char(map[pars->map_height][x_idx], "NSEW"))
			{
				pars->dir_idx = assign_value(map[pars->map_height][x_idx]);
				init_player(player, pars->dir_idx, all);
			}
			x_idx++;
		}
		if (tmp > pars->map_width)
			pars->map_width = tmp;
		pars->map_height++;
	}
}

int main(int argc, char **argv)
{
		t_data	parser_data;
		t_all		all;

		parser_data.map = NULL;
		if (argc != 2)
				return (printf("Error\n[USAGE]: ./Cub3d [map location]\n") , -1);
		parser(argv, &parser_data);
		if (!init_structs(&all, &parser_data))
				return (EXIT_FAILURE);
		get_map_dimension(&all.pars, all.pars.map, &all.player, &all);
		// printf("map_width = %d\nmap_height = %d\n", all.pars.map_width, all.pars.map_height);
		draw_minimap(all.pars.map , &all.pars, &all);
		// cast_rays(&all, &all.ray, &all.player, &all.mlxVars);
		// mlx_loop_hook(all.mlxVars.mlx, &key_hook, &all);
		mlx_loop(all.mlxVars.mlx);
		free_data(&parser_data);
		return (0);
}
