/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:41:43 by verdant           #+#    #+#             */
/*   Updated: 2023/07/09 17:12:41 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

void	draw_line(mlx_image_t *img, t_line line, uint32_t color)
{
	line.dx = abs(line.x2 - line.x1);
	line.dy = abs(line.y2 - line.y1);
	line.sx = ft_tercenary((line.x1 < line.x2), 1, -1);
	line.sy = ft_tercenary((line.y1 < line.y2), 1, -1);
	line.err = ft_tercenary(line.dx > line.dy, line.dx, -line.dy) / 2;
	while (1)
	{
		if (line.x1 < 0 || line.x1 > SCREEN_WIDTH
			|| line.y1 < 0 || line.y1 > SCREEN_HEIGHT)
			break ;
		mlx_put_pixel(img, line.x1, line.y1, color);
		if (line.x1 == line.x2 && line.y1 == line.y2)
			break ;
		line.err_2 = line.err;
		if (line.err_2 > -line.dx)
		{
			line.err -= line.dy;
			line.x1 += line.sx;
		}
		if (line.err_2 < line.dy)
		{
			line.err += line.dx;
			line.y1 += line.sy;
		}
	}
}

void	init_dda_vars(t_ray *ray, t_player *player)
{
	ray->map_x = (int)player->x_grid;
	ray->map_y = (int)player->y_grid;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x_grid - ray->map_x) * ray->d_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->x_grid) * ray->d_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y_grid - ray->map_y) * ray->d_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->y_grid) * ray->d_dist_y;
	}
}

/**
 * @brief Scan the grid lines to find the first wall hit
 * 
 * @param ray Ray struct
 * @param map Map
 * 
 * @note
 * If ray->side is VERTICAL:
 * if ray->step_x is positive (1), the ray hit the EAST side of the wall,
 * if ray->step_x is negative (-1), the ray hit the WEST side of the wall.
 * If ray->side is HORIZONTAL:
 * if ray->step_y is positive (1), the ray hit the SOUTH side of the wall,
 * if ray->step_y is negative (-1), the ray hit the NORTH side of the wall.
 */
void	scan_grid_lines(t_ray *ray, char **map)
{
	while (ray->hit == false)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->d_dist_x;
			ray->map_x += ray->step_x;
			ray->side = HORIZONTAL;
		}
		else
		{
			ray->side_dist_y += ray->d_dist_y;
			ray->map_y += ray->step_y;
			ray->side = VERTICAL;
		}
		if (map[ray->map_y][ray->map_x] == '1')
			ray->hit = true;
	}	
	if (ray->side == VERTICAL)
		ray->direction_tex = ft_tercenary((ray->step_y > 0), SOUTH, NORTH);
	else
		ray->direction_tex = ft_tercenary((ray->step_x > 0), EAST, WEST);
	if (ray->side == VERTICAL)
		ray->perp_wall_dist = (ray->side_dist_y - ray->d_dist_y);
	else
		ray->perp_wall_dist = (ray->side_dist_x - ray->d_dist_x);
}

void	project_rays(t_ray *ray, mlx_image_t *img, t_all *all, t_draw *d)
{
	uint8_t		rgba[4];
	int			index;
	int			i;

	calc_cube_vars(d, ray);
	calc_tex_vars(d, ray, &all->player, all);
	while (d->celling < d->cube_start)
		d->celling = draw_safely(img, ray->num_ray, d->celling, ray->color_cil);
	while (d->cube_start < d->floor)
	{
		if (check_bounds(ray->num_ray, d->cube_start))
		{
			i = -1;
			d->tex_y = (int)d->tex_pos & (d->tex_height - 1);
			d->tex_pos += d->step;
			d->pixel_data = all->pars.tex_arr[ray->direction_tex]->pixels;
			index = (d->tex_y * d->tex_width + d->tex_x) * BPP;
			while (i++ < 3)
				rgba[i] = d->pixel_data[index + i];
			mlx_put_pixel(img, ray->num_ray, d->cube_start, shift_col(rgba));
		}
		d->cube_start++;
	}
	while (d->floor < SCREEN_HEIGHT)
		d->floor = draw_safely(img, ray->num_ray, d->floor, ray->color_flo);
}

/**
 * @brief 
 * 
 * @param data 
 * @param ray 
 * @param player 
 * @note Horizontal lines are represented by x, and vertical lines 
 * are represented by y.
 * @note The delta Distance variable is a fixed distance 
 * that a ray needs to travel 
 * from one grid line to the next.
 * @note The initial side Distance Variable is the distance between the player 
 * and the next grid line. 
 * @note doesn't matter if the player is on a grid line or not.
 * @note We can then increment sideDis by deltaDis because as soon as 
 * we walked inital side Distance we then 
 * always increment from one grid line to the next
 * @note delta Dis is calculated using the 
 * Pytagorem Therom and the Thales theoreom
 */
void	cast_rays(t_all *all, t_ray *ray, t_player *player, t_mlxVars *mlx)
{
	t_line				line;

	ray->num_ray = 0;
	while (ray->num_ray < SCREEN_WIDTH)
	{
		ray->hit = false;
		ray->cam_x = 2 * (ray->num_ray) / (double)SCREEN_WIDTH -1;
		ray->ray_dir_x = player->dir_x + ray->plane_x * ray->cam_x;
		ray->ray_dir_y = player->dir_y + ray->plane_y * ray->cam_x;
		ray->d_dist_x = fabs(1 / ray->ray_dir_x);
		ray->d_dist_y = fabs(1 / ray->ray_dir_y);
		init_dda_vars(ray, player);
		scan_grid_lines(ray, all->pars.map);
		line.x1 = player->x_grid * mlx->c_size;
		line.y1 = player->y_grid * mlx->c_size;
		line.x2 = (player->x_grid * mlx->c_size);
		line.x2 += (ray->ray_dir_x * (mlx->c_size * ray->perp_wall_dist));
		line.y2 = (player->y_grid * mlx->c_size);
		line.y2 += (ray->ray_dir_y * (mlx->c_size * ray->perp_wall_dist));
		draw_line(mlx->minimap, line, 0x00FF00FF);
		project_rays(ray, mlx->ray, all, &all->draw);
		ray->num_ray++;
	}
}
