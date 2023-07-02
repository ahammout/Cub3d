/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:16:29 by verdant           #+#    #+#             */
/*   Updated: 2023/07/02 20:39:04 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"



// void	draw_minimap_cell(char dir_char, t_mlxVars *mlxVars, int x_pixel, int y_pixel)
// {
// 	const uint32_t colors[2] = {0xFF0000FF, 0x000000FF};
// 	u_int32_t		x;
// 	u_int32_t		y;
// 	int					idx;

// 	idx = assign_value(dir_char);
// 	if (!mlxVars)
// 		return ;
// 	x = 0;
// 	while (x <= CELL_SIZE)
// 	{
// 		y = 0;
// 		while (y <= CELL_SIZE)
// 		{
// 			if (y != CELL_SIZE - 1 && x != CELL_SIZE - 1)
// 				mlx_put_pixel(mlxVars->minimap_img, x + x_pixel, y + y_pixel, colors[idx]);
// 			else
// 				mlx_put_pixel(mlxVars->minimap_img, x + x_pixel, y + y_pixel, 0xFFFFFFF);
// 			y++;
// 		}
// 		x++;
// 	}
// }

// void draw_screen_player(t_mlxVars *mlxVars, t_player *p, uint32_t color)
// {
// 	u_int32_t	x;
// 	u_int32_t	y;
	
// 	x = 0;
// 	while (x < p->size)
// 	{
// 		y = 0;
// 		while (y < p->size)
// 		{
// 			mlx_put_pixel(mlxVars->minimap_img, x + p->x_pixel, y + p->y_pixel, color);
// 			y++;
// 		}
// 		x++;
// 	}
// }



// void print_map(char **map)
// {
// 	int x;
// 	int y;
	
// 	for (y = 0; map[y]; y++) {
// 		for (x = 0; map[y][x]; x++) {
// 			printf("%c", map[y][x]);
// 		}
// 		printf("|%d|", map[y][x]);
// 		printf("\n");
// 	}
// }

	// print_map(all->pars.map); // For debugging purposes


void draw_cell(int x_pixel, int y_pixel, uint32_t color, t_mlxVars mlx_vars)
{
	int x;
	int y;

	x = 0;
	while (x <= CELL_SIZE)
	{
		y = 0;
		while (y <= CELL_SIZE)
		{
			if (y != CELL_SIZE - 1 && x != CELL_SIZE - 1)
				mlx_put_pixel(mlx_vars.minimap_img, x + x_pixel, y + y_pixel, color);
			else
				mlx_put_pixel(mlx_vars.minimap_img, x + x_pixel, y + y_pixel, 0xFFFFFFF);
			y++;
		}
		x++;
	}
}

void draw_minimap(char **map, t_pars *pars, t_all *all)
{
	const uint32_t colors[2] = {0xFF0000FF, 0x000000FF};
	int	colunm;
	int	row;
	int x_pixel;
	int y_pixel;
	int	idx;

	colunm = 0;
	while (colunm < pars->map_height)
	{
		row = 0;
		while (row < pars->map_width)
		{
			idx = assign_value(map[colunm][row]);
			x_pixel = colunm * CELL_SIZE + xOFFSET;
			y_pixel = row * CELL_SIZE + yOFFSET;
			draw_cell(y_pixel, x_pixel, colors[idx], all->mlxVars);
			row++;
		}
		colunm++;
	}
}





















	
// Refactor this code
	// The problem is that the lines can be unequally long
	// So I need to find a way to count the longest line without segfaulting
	// Then I would like to redesign the function from the ground up
	// the whole draw_minimap / player_init / draw_player is a mess







// 		y_grid++;
// 	}
// 	all->player_drawn = true;
// }
// void	draw_minimap(t_all *data)
// {
// 	int	x_grid;
// 	int	y_grid;
// 	int	x_pixel;
// 	int	y_pixel;

// 	y_grid = 0;
// 	while (y_grid < GRID_HEIGHT)
// 	{
// 		x_grid = 0;
// 		while (x_grid < GRID_WIDTH)
// 		{
// 			x_pixel = x_grid * CELL_SIZE + xOFFSET;
// 			y_pixel = y_grid * CELL_SIZE + yOFFSET;
// 			draw_minimap_cell(data->world_grid[y_grid][x_grid], &data->mlxVars, x_pixel, y_pixel);
// 			if (!data->player_drawn && data->world_grid[y_grid][x_grid] > 1)
// 			{	
// 				data->player.x_grid = x_grid + 0.5;
// 				data->player.y_grid = y_grid + 0.5;
// 				init_player(data, x_pixel, y_pixel, data->world_grid[y_grid][x_grid] - 2);
// 			}
// 			x_grid++;
// 		}
// 		y_grid++;
// 	}
// }
