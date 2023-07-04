/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:00:11 by mwilsch           #+#    #+#             */
/*   Updated: 2023/07/04 15:15:11 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

bool	init_mlx42(t_mlxVars *mlxVars)
{
	mlxVars->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cube3D", true);
	if (!mlxVars->mlx)
		return (false);
	mlxVars->ray_img = mlx_new_image(mlxVars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlxVars->minimap = mlx_new_image(mlxVars->mlx, 1024, 1024);
	if (!mlxVars->ray_img || !mlxVars->minimap)
		return (false);
	mlx_image_to_window(mlxVars->mlx, mlxVars->ray_img, 0, 0);
	mlx_image_to_window(mlxVars->mlx, mlxVars->minimap, 0, 0);
	mlx_set_instance_depth(mlxVars->minimap->instances, 1);
	return (true);
}

bool	init_player(t_player *player, t_data *data, t_all *all)
{
	const double	arr_fov[4] = {0.66, -0.66, 0.66, -0.66};
	const double	arr_dir[4] = {-1, 1, 1, -1};
	int				dir;

	player->x_grid = data->p_x + 0.5;
	player->y_grid = data->p_y + 0.5;
	dir = assign_value(data->map[data->p_y][data->p_x]);
	player->color = 0xFFFFFFFF;
	player->dir = dir;
	player->rot_speed = 0.03;
	player->move_speed = 0.1;
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
	return (true);
}

bool	init_raycaster(t_ray *ray, t_draw *draw)
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
	ray->d_dist_x = 0;
	ray->d_dist_y = 0;
	ray->perp_wall_dist = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->hit = false;
	draw->celling = 0;
	return (true);
}

bool	init_map_vars(t_data *parser, t_pars *map_vars, mlx_t *mlx, t_ray *ray)
{
	const char	dir_arr[4] = {'N', 'S', 'W', 'E'};
	char		**arr;
	xpm_t		*xpm;
	int			i;

	i = 0;
	while (i < 4)
	{
		arr = get_element(parser, dir_arr[i]);
		if (!arr || !arr[0])
			return (false);
		xpm = mlx_load_xpm42(arr[0]);
		if (!xpm)
			return (false);
		map_vars->tex_arr[i] = mlx_texture_to_image(mlx, &xpm->texture);
		if (!map_vars->tex_arr[i])
			return (false);
		i++;
	}
	ray->color_flo = pack_color(get_element(parser, F));
	ray->color_cil = pack_color(get_element(parser, C));
	map_vars->map = parser->map;
	map_vars->map_width = 0;
	map_vars->map_height = 0;
	return (true);
}

bool	init_structs(t_all *all, t_data *parser_data)
{
	t_pars		map_vars;
	t_draw		draw_vars;

	if (!init_mlx42(&all->mlx_vars))
		return (false);
	if (!init_map_vars(parser_data, &map_vars, all->mlx_vars.mlx, &all->ray))
		return (false);
	if (!init_raycaster(&all->ray, &draw_vars))
		return (false);
	if (!init_player(&all->player, parser_data, all))
		return (false);
	all->draw = draw_vars;
	all->pars = map_vars;
	return (true);
}
