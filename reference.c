
// void	get_texture_color(t_pars *textures, t_player *player, t_ray *ray,  t_all *all)
// {
// 	const int	tex_width = textures->tex_arr[0]->width;
// 	const int	tex_height = textures->tex_arr[0]->height;
// 	double 		wall_x;
// 	int				tex_x;
// 	int				tex_y;
// 	uint32_t	color;
// 	double		step;
// 	double		tex_pos;
	
// 	if (ray->side == HORIZONTAL)
// 		wall_x = player->y_grid + ray->perp_wall_dist * ray->ray_dir_y;
// 	else
// 		wall_x = player->x_grid + ray->perp_wall_dist * ray->ray_dir_x;
// 	wall_x -= floor(wall_x);
// 	tex_x = (int)(wall_x * (double)tex_width);
// 	if (ray->side == HORIZONTAL && ray->ray_dir_x > 0)
// 		tex_x = tex_width - tex_x - 1;
// 	if (ray->side == VERTICAL && ray->ray_dir_y < 0)
// 		tex_x = tex_width - tex_x - 1;
// 	step = 1.0 * tex_height / ray->line_height;
// 	tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2) * step;
	
// }


void	draw_3D_on_screen(t_ray *ray, mlx_image_t *ray_img, t_all *data, int num_ray)
{
	const int	line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	const	int	half_screen_height = SCREEN_HEIGHT / 2;
	int				celling_start;
	int				cube_start;
	int				floor_start;
	
	celling_start = 0;
	cube_start = half_screen_height - line_height / 2;
	if (cube_start < 0)
		cube_start = 0;
	floor_start = half_screen_height + line_height / 2;
	if (floor_start >= SCREEN_HEIGHT)
		floor_start = SCREEN_HEIGHT - 1;
	while (celling_start < cube_start)
		mlx_put_pixel(ray_img, num_ray, celling_start++, data->pars.celling_color);
	while (cube_start < floor_start)
		mlx_put_pixel(ray_img, num_ray, cube_start++, 0x00FF00FF);
	while (floor_start < SCREEN_HEIGHT)
		mlx_put_pixel(ray_img, num_ray, floor_start++, data->pars.floor_color);
}