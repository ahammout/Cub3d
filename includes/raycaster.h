/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:31:41 by verdant           #+#    #+#             */
/*   Updated: 2023/07/09 16:55:44 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include "parser.h"

typedef struct s_info	t_info;
typedef struct s_data	t_data;

# define SCREEN_WIDTH 1440
# define SCREEN_HEIGHT 900
# define PADDING 1
# define XOFFSET 0
# define YOFFSET 0
# define NOR 0
# define SOU 1
# define EAS 2
# define WES 3
# define BPP 4

typedef enum e_movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	ROTATE_LEFT,
	ROTATE_RIGHT,
	NO_MOVEMENT
}	t_move;

typedef enum e_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_direction;

typedef enum e_side
{
	HORIZONTAL,
	VERTICAL
}	t_side;

typedef struct s_mlxVars
{
	mlx_image_t	*ray_img;
	mlx_image_t	*minimap;
	mlx_image_t	*texture_img;
	mlx_t		*mlx;
	int			c_size;
}	t_mlxVars;

/**
 * @brief Structure to hold the player's position and direction
 * 
 * @param size	Size of the player in pixels
 * @param x			Starting X position of the player
 * @param y			Starting Y position of the player
 * @param dir_x	x component of the player's direction vector
 * @param dir_y	y component of the player's direction vector
 * @param color	Color of the player
 * @param arr_dir	Array of directions
 */
typedef struct s_player
{
	t_direction	dir;
	u_int32_t	color;
	double		x_pixel;
	double		x_grid;
	double		y_pixel;
	double		y_grid;
	double		dir_x;
	double		dir_y;
	double		rot_speed;
	double		move_speed;
	int			size;
}	t_player;

typedef struct s_ray
{
	uint32_t		color_cil;
	uint32_t		color_flo;
	double			cam_x;
	double			plane_x;
	double			plane_y;
	double			ray_dir_x;
	double			ray_dir_y;
	double			d_dist_x;
	double			d_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	double			perp_wall_dist;
	t_side			side;
	bool			hit;
	int				line_height;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				direction_tex;
	int				num_ray;
}	t_ray;

typedef struct s_pars
{
	mlx_image_t			*tex_arr[4];
	uint32_t			celling_col;
	uint32_t			floor_color;
	char				**map;
	int					map_width;
	int					map_height;
	int					dir_idx;
}	t_pars;

typedef struct s_draw
{
	uint8_t		*pixel_data;
	double		step;
	double		tex_pos;
	int			line_height;
	int			celling;
	int			cube_start;
	int			floor;
	int			tex_width;
	int			tex_height;
	int			tex_x;
	int			tex_y;
}	t_draw;

typedef struct s_line
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	err_2;
}	t_line;
typedef struct s_all
{
	t_mlxVars		mlx_vars;
	t_player		player;
	t_pars			pars;
	t_draw			draw;
	t_ray			ray;
}	t_all;

/*			Function to setup, use and clean the MLX funcs				*/

bool			init_structs(t_all *data, t_data *parser_data);

/*			Functions to draw stuff				*/

void			draw_cell(char dir, t_mlxVars *mlx, int x_pix, int y_pix);
void			draw_player(t_mlxVars *mlx, t_player *p, uint32_t col);
void			draw_minimap(t_all *all, t_pars *pars, t_player *player);

/*			Functions to handle events				*/

void			key_hook(void *param);

/*			Utiliy functions for casting rays			*/

void			calc_cube_vars(t_draw *draw, t_ray *ray);
void			calc_tex_vars(t_draw *d, t_ray *r, t_player *p, t_all *a);

/*			Functions to cast Rays				*/

void			draw_line(mlx_image_t *img, t_line line, uint32_t color);
void			init_dda_vars(t_ray *ray, t_player *player);
void			scan_grid_lines(t_ray *ray, char **map);
void			cast_rays(t_all *data, t_ray *ray, t_player *p, t_mlxVars *mlx);

/*			Utils				*/

uint32_t		pack_color(char **array);
uint32_t		shift_col(uint8_t rgba[]);
bool			incl_char(char c, char *search_str);
int				ft_tercenary(int condition, int a, int b);
int				assign_value(char direction);

#endif