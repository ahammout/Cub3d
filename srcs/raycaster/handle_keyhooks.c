/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyhooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:27:51 by verdant           #+#    #+#             */
/*   Updated: 2023/07/09 17:10:03 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

bool	check_bounds(int x, int y)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
		return (true);
	return (false);
}

int	draw_safely(mlx_image_t *img, int x, int y, uint32_t color)
{
	if (check_bounds(x, y))
		mlx_put_pixel(img, x, y, color);
	return (y + 1);
}

void	move_player(t_player *player, t_move move, double speed, char **map)
{
	double			new_x;
	double			new_y;
	const int		arr[2] = {1, -1};

	new_x = 0;
	new_y = 0;
	if (move == FORWARD || move == BACKWARD)
	{
		new_x = player->x_grid + player->dir_x * speed * arr[move];
		new_y = player->y_grid + player->dir_y * speed * arr[move];
	}
	if (move == RIGHT)
	{
		new_x = player->x_grid - player->dir_y * speed;
		new_y = player->y_grid + player->dir_x * speed;
	}
	if (move == LEFT)
	{
		new_x = player->x_grid + player->dir_y * speed;
		new_y = player->y_grid - player->dir_x * speed;
	}
	if (map[(int)new_y][(int)new_x] == '1')
		return ;
	player->y_grid = new_y;
	player->x_grid = new_x;
}

/**
 * @brief 
 * 
 * @param p 
 * @param move 
 * @param sp Stands for the speed the player rotates
 * @param all 
 */
void	rotate_player(t_player *p, t_move move, double sp, t_ray *ray)
{
	double	old_dir_x;
	double	old_plane_x;

	if (move == ROTATE_LEFT)
	{
		old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(-sp) - p->dir_y * sin(-sp);
		p->dir_y = old_dir_x * sin(-sp) + p->dir_y * cos(-sp);
		old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(-sp) - ray->plane_y * sin(-sp);
		ray->plane_y = old_plane_x * sin(-sp) + ray->plane_y * cos(-sp);
	}
	else if (move == ROTATE_RIGHT)
	{
		old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(sp) - p->dir_y * sin(sp);
		p->dir_y = old_dir_x * sin(sp) + p->dir_y * cos(sp);
		old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(sp) - ray->plane_y * sin(sp);
		ray->plane_y = old_plane_x * sin(sp) + ray->plane_y * cos(sp);
	}
}

void	key_hook(void *param)
{
	t_mlxVars	*mlx_vars;
	t_player	*player;
	t_all		*all;

	all = (t_all *)param;
	mlx_vars = &all->mlx_vars;
	player = &all->player;
	if (mlx_is_key_down(mlx_vars->mlx, MLX_KEY_Q))
		return (mlx_close_window(all->mlx_vars.mlx));
	if (mlx_is_key_down(mlx_vars->mlx, MLX_KEY_W))
		move_player(player, FORWARD, player->move_speed, all->pars.map);
	if (mlx_is_key_down(mlx_vars->mlx, MLX_KEY_S))
		move_player(player, BACKWARD, player->move_speed, all->pars.map);
	if (mlx_is_key_down(mlx_vars->mlx, MLX_KEY_A))
		move_player(player, LEFT, player->move_speed, all->pars.map);
	if (mlx_is_key_down(mlx_vars->mlx, MLX_KEY_D))
		move_player(player, RIGHT, player->move_speed, all->pars.map);
	if (mlx_is_key_down(mlx_vars->mlx, MLX_KEY_LEFT))
		rotate_player(player, ROTATE_LEFT, player->rot_speed, &all->ray);
	if (mlx_is_key_down(mlx_vars->mlx, MLX_KEY_RIGHT))
		rotate_player(player, ROTATE_RIGHT, player->rot_speed, &all->ray);
	draw_minimap(all, &all->pars, &all->player);
	cast_rays(all, &all->ray, &all->player, &all->mlx_vars);
}
