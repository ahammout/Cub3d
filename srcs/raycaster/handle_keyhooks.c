/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyhooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:27:51 by verdant           #+#    #+#             */
/*   Updated: 2023/07/04 13:18:00 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

/**
 * @brief 
 * 
 * @param player 
 * @param new_x 
 * @param new_y 
 * @param data 
 * @note I'm checking every corner of the player against the world_grid
 */
// bool is_wall_in_world(t_player *player, int new_x, int new_y, t_all *data)
// {
// 		int	grid_x_min;
// 		int	grid_y_min;
// 		int	grid_x_max;
// 		int	grid_y_max;

//  		grid_x_min = new_x / CELL_SIZE;
//  		grid_y_min = new_y / CELL_SIZE;
//  		grid_x_max = (new_x + player->size - 1) / CELL_SIZE;
//  		grid_y_max = (new_y + player->size - 1) / CELL_SIZE;
// 		if (data->world_grid[grid_y_min][grid_x_min] == 1) 
// 			return true;
// 		if (data->world_grid[grid_y_min][grid_x_max] == 1) 
// 			return true;
// 		if (data->world_grid[grid_y_max][grid_x_min] == 1) 
// 			return true;
// 		if (data->world_grid[grid_y_max][grid_x_max] == 1) 
// 			return true;
// 		return false;
// }


void move_player(t_player *player, t_move move, double move_speed, char **map)
{
	const		int arr[2] = {1, -1};
	double	new_x;
	double	new_y;

	new_x = 0;
	new_y = 0;
	if (move == FORWARD || move == BACKWARD)
	{
		new_x = player->x_grid + player->dir_x * move_speed * arr[move];
		new_y = player->y_grid + player->dir_y * move_speed * arr[move];
	}
	if (move == LEFT)
	{
		new_x = player->x_grid - player->dir_y * move_speed;
		new_y = player->y_grid + player->dir_x * move_speed;
	}
	if (move == RIGHT)
	{
		new_x = player->x_grid + player->dir_y * move_speed;
		new_y = player->y_grid - player->dir_x * move_speed;
	}
	if (map[(int)new_y][(int)new_x] == '1')
		return ;
	player->y_grid = new_y;
	player->x_grid = new_x;
}


void	rotate_player(t_player *player, t_move move, double rot_speed,  t_all *all)
{
	if (move == ROTATE_LEFT)
	{
		double oldDirX = player->dir_x;
		player->dir_x = player->dir_x * cos(-rot_speed) - player->dir_y * sin(-rot_speed);
		player->dir_y = oldDirX * sin(-rot_speed) + player->dir_y * cos(-rot_speed);
		double old_plane_x = all->ray.plane_x; 
		all->ray.plane_x = all->ray.plane_x * cos(-rot_speed) - all->ray.plane_y * sin(-rot_speed);
		all->ray.plane_y = old_plane_x * sin(-rot_speed) + all->ray.plane_y * cos(-rot_speed);
	}
	if (move == ROTATE_RIGHT)
	{
		double oldDirX = player->dir_x;
		player->dir_x = player->dir_x * cos(rot_speed) - player->dir_y * sin(rot_speed);
		player->dir_y = oldDirX * sin(rot_speed) + player->dir_y * cos(rot_speed);
		double old_plane_x = all->ray.plane_x;
		all->ray.plane_x = all->ray.plane_x * cos(rot_speed) - all->ray.plane_y * sin(rot_speed);
		all->ray.plane_y = old_plane_x * sin(rot_speed) + all->ray.plane_y * cos(rot_speed);
	}
}

void	key_hook(void* param)
{
	t_all			*all;
	t_mlxVars	*mlxVars;
	t_player	*player;

	all = (t_all *)param;
	mlxVars = &all->mlxVars;
	player = &all->player;
	if (mlx_is_key_down(mlxVars->mlx, MLX_KEY_Q))
		return (mlx_close_window(all->mlxVars.mlx));
	if (mlx_is_key_down(mlxVars->mlx, MLX_KEY_W))
		move_player(player, FORWARD, player->move_speed, all->pars.map);
	if (mlx_is_key_down(mlxVars->mlx, MLX_KEY_S))
		move_player(player, BACKWARD, player->move_speed,all->pars.map);
	if (mlx_is_key_down(mlxVars->mlx, MLX_KEY_A))
		move_player(player, LEFT, player->move_speed, all->pars.map);	
	if (mlx_is_key_down(mlxVars->mlx, MLX_KEY_D))
		move_player(player, RIGHT, player->move_speed, all->pars.map);
	if (mlx_is_key_down(mlxVars->mlx, MLX_KEY_LEFT))
		rotate_player(player, ROTATE_LEFT,player->rot_speed, all);
	if (mlx_is_key_down(mlxVars->mlx, MLX_KEY_RIGHT))
		rotate_player(player, ROTATE_RIGHT,player->rot_speed, all);
	draw_minimap(all, &all->pars, &all->player);
	cast_rays(all, &all->ray, &all->player, &all->mlxVars);
}
