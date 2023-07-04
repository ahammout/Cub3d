/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: verdant <verdant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:16:29 by verdant           #+#    #+#             */
/*   Updated: 2023/07/04 07:04:48 by verdant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

void draw_minimap_cell(char dir_char, t_mlxVars *mlxVars, int x_pixel, int y_pixel)
{
  const uint32_t colors[3] = {0xFF0000FF, 0x000000FF, 0xFFFF00FF};
  uint32_t x;
	uint32_t y;
  int idx = assign_value(dir_char);

  if (!mlxVars) 
		return;
	x = 0;
  while (x < CELL_SIZE)
  {
      y = 0;
      while (y < CELL_SIZE)
      {
          if (x == 0 || y == 0 || x == CELL_SIZE - 1 || y == CELL_SIZE - 1)
              mlx_put_pixel(mlxVars->minimap_img, x + x_pixel, y + y_pixel, 0xFFFFFFFF);
          else
              mlx_put_pixel(mlxVars->minimap_img, x + x_pixel, y + y_pixel, colors[idx]);
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
	p->size = 4;
	p->x_pixel = p->x_grid * CELL_SIZE;
	p->x_pixel += (CELL_SIZE / 2) - (p->size / 2);
	p->y_pixel = p->y_grid * CELL_SIZE;
	p->y_pixel += (CELL_SIZE / 2) - (p->size / 2);
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

void	get_dimension(char **map, t_pars *pars)
{
	if (pars->map_height != 0)
		return ;
	while(map[pars->map_height][pars->map_width])
		pars->map_width++;
	while(map[pars->map_height])
		pars->map_height++;
}
	
// Refactor this code
	// The problem is that the lines can be unequally long
	// So I need to find a way to count the longest line without segfaulting
	// Then I would like to redesign the function from the ground up
	// the whole draw_minimap / player_init / draw_player is a mess
void	draw_minimap(t_all *all, t_pars *pars, t_player *player)
{
	int	x_grid;
	int y_grid;
	int x_pixel;
	int y_pixel;
	get_dimension(pars->map, pars);

	y_grid = 0;
	x_pixel = 0;
	y_pixel = 0;
	while (y_grid < pars->map_height)
	{
		x_grid = 0;
		while (x_grid < pars->map_width)
		{
			x_pixel = x_grid * CELL_SIZE + xOFFSET;
			y_pixel = y_grid * CELL_SIZE + yOFFSET;
			draw_minimap_cell(pars->map[y_grid][x_grid], &all->mlxVars, x_pixel, y_pixel);
			x_grid++;
		}
		y_grid++;
	}
	draw_screen_player(&all->mlxVars, player, player->color); // Still someting wrong here
}

