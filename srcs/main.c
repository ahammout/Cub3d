/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: verdant <verdant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:56:01 by ahammout          #+#    #+#             */
/*   Updated: 2023/07/04 07:03:50 by verdant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void print_map(char **map)
{
		int i = 0;
		int j = 0;

		while (map[i])
		{
				j = 0;
				while (map[i][j])
				{
						printf("%c", map[i][j]);
						j++;
				}
				printf("|%d|", map[i][j]);
				printf("\n");
				i++;
		}
}

// !. Fix Minimap
// 2. Norm code
// 3. Ask chatgpt how to check for leaks
// 4. Ask chatgpt how to check for performance

int main(int argc, char **argv)
{
		t_data	parser_data;
		t_all		all;

		if (argc != 2)
				return (printf("Error\n[USAGE]: ./Cub3d [map location]\n") , -1);
		parser(argv, &parser_data);
		if (!init_structs(&all, &parser_data))
				return (EXIT_FAILURE);
		print_map(all.pars.map);
		/**/
		draw_minimap(&all, &all.pars, &all.player);
		// cast_rays(&all, &all.ray, &all.player, &all.mlxVars);
		mlx_loop_hook(all.mlxVars.mlx, &key_hook, &all);
		mlx_loop(all.mlxVars.mlx);
		/**/
		free_data(&parser_data);
		printf("Done\n");
		return (0);
} 