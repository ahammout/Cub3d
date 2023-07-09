/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:16:29 by verdant           #+#    #+#             */
/*   Updated: 2023/07/09 16:55:38 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

/**
 * @brief 
 * 
 * @param mlxVars 
 * @param p 
 * @param color 
 * @note dx and dy stand for draw_x and draw_y
 */
void	draw_player(t_mlxVars *mlxVars, t_player *p, uint32_t color)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	c_size;

	x = 0;
	c_size = mlxVars->c_size;
	p->size = 2;
	p->x_pixel = (p->x_grid - 0.5) * c_size;
	p->x_pixel += (c_size / 2) - (p->size / 2);
	p->y_pixel = (p->y_grid - 0.5) * c_size;
	p->y_pixel += (c_size / 2) - (p->size / 2);
	dx = p->x_pixel;
	dy = p->y_pixel;
	while (x < p->size)
	{
		y = 0;
		while (y < p->size)
		{
			mlx_put_pixel(mlxVars->minimap, x + dx, y + dy, color);
			y++;
		}
		x++;
	}
}

void	draw_cell(char dir, t_mlxVars *mlx, int x_pix, int y_pix)
{
	int						x;
	int						y;
	int						idx;
	int						c_size;
	const uint32_t			colors[3] = {0xFF0000FF, 0x000000FF, 0xFFFFFFFF};

	idx = assign_value(dir);
	c_size = mlx->c_size;
	if (!mlx)
		return ;
	x = 0;
	while (x < c_size)
	{
		y = 0;
		while (y < c_size)
		{
			if (x == 0 || y == 0 || x == c_size - 1 || y == c_size - 1)
				mlx_put_pixel(mlx->minimap, x + x_pix, y + y_pix, 0xFFFFFFFF);
			else
				mlx_put_pixel(mlx->minimap, x + x_pix, y + y_pix, colors[idx]);
			y++;
		}
		x++;
	}
}

void	get_dimension(char **map, t_pars *pars, t_mlxVars *mlx)
{
	const int	width = mlx->minimap->width;
	const int	height = mlx->minimap->height;
	
	if (pars->map_height != 0)
		return ;
	while (map[pars->map_height][pars->map_width])
		pars->map_width++;
	while (map[pars->map_height])
		pars->map_height++;
	while (pars->map_width * mlx->c_size > width)
		mlx->c_size--;
	while (pars->map_height * mlx->c_size > height)
		mlx->c_size--;
}

void	draw_minimap(t_all *all, t_pars *pars, t_player *player)
{
	int	x_grid;
	int	y_grid;
	int	x_pix;
	int	y_pix;

	get_dimension(pars->map, pars, &all->mlx_vars);
	y_grid = 0;
	x_pix = 0;
	y_pix = 0;
	while (y_grid < pars->map_height)
	{
		x_grid = 0;
		while (x_grid < pars->map_width)
		{
			x_pix = x_grid * all->mlx_vars.c_size + XOFFSET;
			y_pix = y_grid * all->mlx_vars.c_size + YOFFSET;
			draw_cell(pars->map[y_grid][x_grid], &all->mlx_vars, x_pix, y_pix);
			x_grid++;
		}
		y_grid++;
	}
	draw_player(&all->mlx_vars, player, player->color);
}
