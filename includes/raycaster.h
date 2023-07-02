/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:31:41 by verdant           #+#    #+#             */
/*   Updated: 2023/07/02 20:35:44 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include "parser.h"

typedef struct s_info t_info;
typedef struct s_data t_data;


#define SCREEN_WIDTH 1440
#define SCREEN_HEIGHT 900
#define CELL_SIZE 16
#define PADDING 1
#define xOFFSET 0
#define yOFFSET 0
#define NOR 0
#define SOU 1
#define EAS 2
#define WES 3
#define BPP 4

typedef enum e_movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	ROTATE_LEFT,
	ROTATE_RIGHT,
	NO_MOVEMENT
} t_move;

typedef enum e_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
} t_direction;

typedef enum e_side
{
	HORIZONTAL,
	VERTICAL
} t_side;

typedef struct s_mlxVars
{
	mlx_t				*mlx;
	mlx_image_t	*ray_img;
	mlx_image_t	*minimap_img;
	mlx_image_t	*texture_img;
} t_mlxVars;

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
	double	x_pixel;
	double	x_grid;
	double	y_pixel;
	double	y_grid;
	double			dir_x;
	double			dir_y;
	t_direction dir;
	u_int32_t	color;
	u_int32_t	size;
	double		rot_speed;
	double		move_speed;
} t_player;

typedef struct s_ray
{
	double		cam_x;
	double		plane_x;
	double		plane_y;
	double		ray_dir_x;
	double		ray_dir_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	int				line_height;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	t_side		side;
	bool			hit;
	double		perp_wall_dist;

	int				direction_tex;
	
} t_ray;


typedef struct s_pars
{
	uint32_t		celling_color;
	uint32_t		floor_color;
	mlx_image_t	*tex_arr[4];
	char				**map;
	int					map_width;
	int					map_height;
	int					dir_idx;
} t_pars;

typedef struct s_draw
{
	int line_height;
	int	celling_start;
	int cube_start;
	int floor_start;
	int tex_width;
	int tex_height;
	int	tex_x;
	int	tex_y;
	double	step;
	double	tex_pos;
	uint8_t	*pixelData;
} t_draw;

typedef struct s_all
{
	t_mlxVars	mlxVars;
	t_player	player;
	t_ray			ray;
	t_pars		pars;
	t_draw		draw;
	bool			player_drawn;
} t_all;




/*			Function to setup, use and clean the MLX relevant Funcs				*/

bool	init_mlx42(t_mlxVars *mlxVars);
bool	init_raycaster(t_ray *ray);
void	init_player(t_player *player, int dir, t_all *all);
bool	init_structs(t_all *data, t_data *parser_data);

/*			Functions to draw stuff				*/

// void	draw_minimap_cell(char dir_char, t_mlxVars *mlxVars, int x_pixel, int y_pixel);
// void	draw_screen_player(t_mlxVars *mlxVars, t_player *p, uint32_t color);
// void	draw_minimap(t_all *data);

void draw_minimap(char **map, t_pars *pars, t_all *all);

/*			Functions to handle events				*/

// bool	is_wall_in_world(t_player *player, int new_x, int new_y, t_all *data);
void	key_hook(void* param);

/*			Functions to cast Rays				*/

void	draw_line(mlx_image_t* image, int x1, int y1, int x2, int y2, uint32_t color);
void	init_dda_vars(t_ray *ray, t_player *player);
void	scan_grid_lines(t_ray *ray, t_all *data, char **map);
void	cast_rays(t_all *data, t_ray *ray, t_player *player, t_mlxVars *mlxVars);

/*			Main				*/


/*			Utils				*/

bool			incl_char(char c, char *search_str);
int				ft_tercenary(int condition, int a, int b);
uint32_t	pack_color(char **array);
int				assign_value(char direction);
uint32_t 	shift_col(uint8_t rgba[]);

# endif