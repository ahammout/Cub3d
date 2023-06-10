
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: verdant <verdant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:52:47 by verdant           #+#    #+#             */
/*   Updated: 2023/05/22 10:54:03 by verdant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

bool	init_mlx42(t_mlxVars *mlxVars)
{
	const uint32_t color = 0xFFFFFFFF; // Blue
	mlxVars->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cube3D", true);
	if (!mlxVars->mlx)
		return (false);
	mlxVars->ray_img = mlx_new_image(mlxVars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlxVars->minimap_img = mlx_new_image(mlxVars->mlx, 1024, 1024);
	if (!mlxVars->ray_img || !mlxVars->minimap_img)
		return (false);
	mlx_image_to_window(mlxVars->mlx, mlxVars->ray_img, 0, 0);
	mlx_image_to_window(mlxVars->mlx, mlxVars->minimap_img, 0, 0);
	mlx_set_instance_depth(mlxVars->minimap_img->instances, 1);
	return (true);
}

// Refactor this as soon as I have the parser
void	init_player(t_all *all, int xDraw, int yDraw, char dir_char)
{
	const		double 	arr_fov[4] = {0.66, -0.66, 0.66, -0.66};
	const		double 	arr_dir[4] = {-1, 1, 1, -1};
	const 	int			dir = assign_value(dir_char);
	t_player	*player;

	player = &all->player;
	player->size = 4;
	player->x_pixel = (CELL_SIZE / 2) - (player->size / 2) + xDraw;
	player->y_pixel = (CELL_SIZE / 2) - (player->size / 2) + yDraw;
	player->color = 0xFFFF00FF; // Yellow
	player->dir = dir;
	player->rot_speed = 0.1;
	player->move_speed = 0.1;
	draw_screen_player(&all->mlxVars, player, player->color);
	player->dir_x = 0;
	player->dir_y = 0;
	if (dir == NORTH || dir == SOUTH)
		player->dir_y = arr_dir[dir];
	if (dir == EAST || dir == WEST)
		player->dir_x = arr_dir[dir];
	if (player->dir == NORTH || player->dir == SOUTH)
		all->ray.plane_x = arr_fov[dir];
	if (player->dir == EAST || player->dir == WEST)
		all->ray.plane_y = arr_fov[dir];
}

bool	init_raycaster(t_ray *ray)
{
	ray->cam_x = 0;
	ray->ray_dir_x = 0;
	ray->ray_dir_y = 0;
	ray->plane_x = 0;
	ray->plane_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->delta_dist_x = 0;
	ray->delta_dist_y = 0;
	ray->perp_wall_dist = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->hit = false;
	return (true);
}

bool	init_map_vars(t_data *parser_data, t_pars *map_vars, mlx_t *mlx)
{
	const char dir_arr[4] = {'N', 'S', 'W', 'E'};
	int	i;
	char **arr;

	i = 0;
	while (i < 3)
	{
		arr = get_element(parser_data, dir_arr[i]);
		if (!arr || !arr[0])
			return (false);
		xpm_t *xpm = mlx_load_xpm42(arr[0]);
		if (!xpm)
			return (false);
		map_vars->tex_arr[i] = mlx_texture_to_image(mlx, &xpm->texture);
		if (!map_vars->tex_arr[i])
			return (false);
		i++;
	}
	map_vars->floor_color = pack_color(get_element(parser_data, F));
	map_vars->celling_color = pack_color(get_element(parser_data, C));
	map_vars->map = parser_data->map;
	return (true);
}

// Refactor grid variable this as soon as I have the parser from my partner
bool init_structs(t_all *all, t_data *parser_data)
{
	t_pars		map_vars;

	if (!init_mlx42(&all->mlxVars) || !init_raycaster(&all->ray))
		return (false);
	if (!init_map_vars(parser_data, &map_vars, all->mlxVars.mlx))
		return (false);
	all->pars = map_vars;
	all->player_drawn = false;
	return (true);
}



