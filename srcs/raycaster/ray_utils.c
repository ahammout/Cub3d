/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:48:15 by mwilsch           #+#    #+#             */
/*   Updated: 2023/07/09 17:08:00 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

void	calc_cube_vars(t_draw *draw, t_ray *ray)
{
	const int	half_screen_height = SCREEN_HEIGHT / 2;

	draw->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	draw->celling = 0;
	draw->cube_start = half_screen_height - draw->line_height / 2;
	if (draw->cube_start < 0)
		draw->cube_start = 0;
	draw->floor = half_screen_height + draw->line_height / 2;
	if (draw->floor >= SCREEN_HEIGHT)
		draw->floor = SCREEN_HEIGHT - 1;
}

void	calc_tex_vars(t_draw *draw, t_ray *ray, t_player *player, t_all *all)
{
	double		wall_x;

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
	draw->tex_pos = (draw->cube_start - SCREEN_HEIGHT / 2
			+ draw->line_height / 2) * draw->step;
}
