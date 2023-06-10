/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: verdant <verdant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:16:29 by verdant           #+#    #+#             */
/*   Updated: 2023/06/10 15:29:41 by verdant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

void	draw_minimap_cell(char dir_char, t_mlxVars *mlxVars, int x_pixel, int y_pixel)
{
	const uint32_t colors[2] = {0xFF0000FF, 0x000000FF};
	u_int32_t		x;
	u_int32_t		y;
	int					idx;

	idx = assign_value(dir_char);
	if (!mlxVars)
		return ;
	x = 0;
	while (x <= CELL_SIZE)
	{
		y = 0;
		while (y <= CELL_SIZE)
		{
			if (y != CELL_SIZE - 1 && x != CELL_SIZE - 1)
				mlx_put_pixel(mlxVars->minimap_img, x + x_pixel, y + y_pixel, colors[idx]);
			else
				mlx_put_pixel(mlxVars->minimap_img, x + x_pixel, y + y_pixel, 0xFFFFFFF);
			y++;
		}
		x++;
	}
}

void draw_screen_player(t_mlxVars *mlxVars, t_player *p, uint32_t color)
{
	u_int32_t	x;
	u_int32_t	y;
	
	x = 0;
	while (x < p->size)
	{
		y = 0;
		while (y < p->size)
		{
			mlx_put_pixel(mlxVars->minimap_img, x + p->x_pixel, y + p->y_pixel, color);
			y++;
		}
		x++;
	}
}


	

void	draw_minimap(t_all *all)
{
	int grid_width;
	int grid_height;

	grid_height = 0;
	grid_width = 0;

	while (all->pars.map[grid_height][grid_width])
		grid_width++;
	while (all->pars.map[grid_height])
		grid_height++;
	




	
	int	x_grid, y_grid, x_pixel, y_pixel;

	y_grid = 0;
	x_pixel = 0;
	y_pixel = 0;
	while (y_grid < grid_height)
	{
		x_grid = 0;
		while (x_grid < grid_width)
		{
			x_pixel = x_grid * CELL_SIZE + xOFFSET;
			y_pixel = y_grid * CELL_SIZE + yOFFSET;
			draw_minimap_cell(all->pars.map[y_grid][x_grid], &all->mlxVars, x_pixel, y_pixel);
			if (!all->player_drawn && incl_char(all->pars.map[y_grid][x_grid], "NESW"))
			{	
				all->player.x_grid = x_grid + 0.5;
				all->player.y_grid = y_grid + 0.5;
				init_player(all, x_pixel, y_pixel, all->pars.map[y_grid][x_grid]);
			}
			x_grid++;
		}

		y_grid++;
	}
	all->player_drawn = true;
}
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
