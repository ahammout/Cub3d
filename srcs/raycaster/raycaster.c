/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: verdant <verdant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:41:43 by verdant           #+#    #+#             */
/*   Updated: 2023/06/26 10:11:42 by verdant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

void draw_line(mlx_image_t* image, int x1, int y1, int x2, int y2, uint32_t color)
{
		int dx = abs(x2 - x1);
		int dy = abs(y2 - y1);
		int sx = ft_tercenary((x1 < x2), 1, -1);
		int sy = ft_tercenary((y1 < y2), 1, -1);
		int err = (dx > dy ? dx : -dy) / 2;
		int e2;

		while (1) 
		{
				if (x1 < 0 || x1 > SCREEN_WIDTH || y1 < 0 || y1 > SCREEN_HEIGHT)
					break;
				mlx_put_pixel(image, x1, y1, color);
				if (x1 == x2 && y1 == y2)
						break;
				e2 = err;
				if (e2 > -dx) {
						err -= dy;
						x1 += sx;
				}
				if (e2 < dy) {
						err += dx;
						y1 += sy;
				}
		}
}

void	init_dda_vars(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x_grid - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->x_grid) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y_grid - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->y_grid) * ray->delta_dist_y;
	}
}



// In the function scan_grid_lines, the direction in which the ray hits the wall can be deduced from two pieces of information: ray->side (whether the ray hit a horizontal or vertical wall) and ray->step_x or ray->step_y (the direction in which the ray was moving along the x or y axis).

// If ray->side is HORIZONTAL:
// if ray->step_x is positive (1), the ray hit the EAST side of the wall,
// otherwise, if ray->step_x is negative (-1), the ray hit the WEST side of the wall.
// If ray->side is VERTICAL:
// if ray->step_y is positive (1), the ray hit the SOUTH side of the wall,
// otherwise, if ray->step_y is negative (-1), the ray hit the NORTH side of the wall.



void	scan_grid_lines(t_ray *ray, t_all *all, char **map)
{
	while (ray->hit == false)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = HORIZONTAL;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = VERTICAL;
		}
		if (map[ray->map_y][ray->map_x] == '1')
			ray->hit = true;
	}	
	if (ray->side == HORIZONTAL)
		ray->direction_tex = ft_tercenary((ray->step_x > 0), EAST, WEST);
	else
		ray->direction_tex = ft_tercenary((ray->step_y > 0), SOUTH, NORTH);	
	if(ray->side == HORIZONTAL) 
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
}


void	calc_draw_vars(t_draw *draw, t_ray *ray, t_player *player, t_all *all)
{
	const	int	half_screen_height = SCREEN_HEIGHT / 2;
	double		wall_x;
	
	draw->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	draw->celling_start = 0;
	draw->cube_start = half_screen_height - draw->line_height / 2;
	if (draw->cube_start < 0)
		draw->cube_start = 0;
	draw->floor_start = half_screen_height + draw->line_height / 2;
	if (draw->floor_start >= SCREEN_HEIGHT)
		draw->floor_start = SCREEN_HEIGHT - 1;
	draw->tex_height = all->pars.tex_arr[ray->direction_tex]->height;
	draw->tex_width = all->pars.tex_arr[ray->direction_tex]->width;
	if (ray->side == HORIZONTAL)
		wall_x = player->y_grid + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = player->x_grid + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	draw->tex_x = (int)(wall_x * (double)draw->tex_width);
	if (ray->side == HORIZONTAL && ray->ray_dir_x > 0)
		draw->tex_x = draw->tex_width - draw->tex_x - 1;
	if (ray->side == VERTICAL && ray->ray_dir_y < 0)
		draw->tex_x = draw->tex_width - draw->tex_x - 1;
	draw->step = 1.0 * draw->tex_height / draw->line_height;
	draw->tex_pos = (draw->cube_start - SCREEN_HEIGHT / 2 + draw->line_height / 2) * draw->step;
}

void	project_rays(t_ray *ray, t_mlxVars *imgs, t_all *all, int num_ray)
{	
	uint8_t		rgba[4];
	t_draw 		*draw;
	int				index;
	int 			i;
	
	draw = &all->draw;
	calc_draw_vars(draw, ray, &all->player, all);
	while (draw->celling_start < draw->cube_start)
		mlx_put_pixel(imgs->ray_img, num_ray, draw->celling_start++, all->pars.celling_color);
	while (draw->cube_start < draw->floor_start)
	{
		i = -1;
		draw->tex_y = (int)draw->tex_pos & (draw->tex_height - 1);
		draw->tex_pos += draw->step;
		draw->pixelData = all->pars.tex_arr[ray->direction_tex]->pixels;
		index = (draw->tex_y * draw->tex_width + draw->tex_x) * BPP;
		while (i++ < 3)
			rgba[i] = draw->pixelData[index + i];
		mlx_put_pixel(imgs->ray_img, num_ray, draw->cube_start, shift_col(rgba));
		draw->cube_start++;
	}
	while (draw->floor_start < SCREEN_HEIGHT)
		mlx_put_pixel(imgs->ray_img, num_ray, draw->floor_start++, all->pars.floor_color);	
}


/**
 * @brief 
 * 
 * @param data 
 * @param ray 
 * @param player 
 * @note Horizontal lines are represented by x, and vertical lines are represented by y.
 * @note The delta Distance variable is a fixed distance that a ray needs to travel from one grid line to the next.
 * @note The initial side Distance Variable is the distance between the player and the next grid line. It doesn't matter if the player is on a grid line or not.
 * @note We can then increment sideDis by deltaDis because as soon as we walked inital side Distance we then always increment from one grid line to the next
 * 
 * @note delta Dis is calculated using the Pytagorem Therom and the Thales theoreom
 */
void	cast_rays(t_all *all, t_ray *ray, t_player *player, t_mlxVars *mlxVars)
{
	int						num_ray;
	
	num_ray = 0;
	while (num_ray < SCREEN_WIDTH)
	{
		ray->hit = false;
		ray->cam_x = 2 * (num_ray) / (double)SCREEN_WIDTH -1;
		ray->ray_dir_x = player->dir_x + ray->plane_x * ray->cam_x;
		ray->ray_dir_y = player->dir_y + ray->plane_y * ray->cam_x;;
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);;
		ray->map_x = (int)player->x_grid;
		ray->map_y = (int)player->y_grid;
		init_dda_vars(ray, player);
		scan_grid_lines(ray, all, all->pars.map);
		// draw_line(mlxVars->minimap_img)
		draw_line(all->mlxVars.minimap_img, player->x_grid * CELL_SIZE, player->y_grid * CELL_SIZE, (player->x_grid * CELL_SIZE) + (ray->ray_dir_x * (ray->perp_wall_dist * CELL_SIZE)), (player->y_grid * CELL_SIZE) + (ray->ray_dir_y * (CELL_SIZE * ray->perp_wall_dist)), 0x00FF00FF);
		project_rays(ray, &all->mlxVars, all, num_ray);
		num_ray++;
	}
}
