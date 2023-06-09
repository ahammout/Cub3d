/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:57:53 by ahammout          #+#    #+#             */
/*   Updated: 2023/07/03 23:16:55 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdlib.h>
#include"../get_next_line/get_next_line.h"
#include"../libft/libft.h"

#define SO 'S'
#define WE 'W'
#define NO 'N'
#define EA 'E'

#define C 'C'
#define F 'F'

#define WL '1'
#define EM '0'

typedef struct  s_info
{
    char    **elem;
    int     type;
    int     index;
    struct  s_info *next;
    struct  s_info *prev;
}               t_info;


typedef struct  s_data
{
    t_info   *info;
    char    **map;
    int     p_x;
    int     p_y;
}               t_data;

bool    parser(char **av, t_data *data);

//---------------------- HANDLE ELEMENTS -------------------/


void    handle_file(int map_fd, t_data *data);
void    add_node(t_data *data, int *index_ptr, t_info **ptr);
int     handle_elements(char *line, t_data *data, t_info *ptr);
void	analyze_elements(t_data *data);
int     detect_directions(t_data *data, char *line);
int     is_direction(char c);
void    parse_directions(t_data *data, char *line, t_info *ptr);
int     check_path(char *line);
char    **get_element(t_data *data, int identifier);

void    parse_fc(t_data *data, char *line, t_info *ptr);
int     check_fc(t_data *data, char *line);
int     get_color(char *line);
int     find_comma(char *line);

//---------------------- HANDLE MAP -------------------/
int     is_wall(char *line);
void    handle_map(t_data *data, int map_fd, char *holder);
int     check_map(char *line);
void    analyze_map(t_data *data);
void    cut_empty_lines(t_data *data);
int     surrounded_map(t_data *data);

//---------------------- FREE TOOLS -------------------/
void    free_data(t_data *data);
void    free_map(t_data *data);
void    free_elements_lst(t_data *data);
void    free_2darray(t_data *data);
void    exit_error(t_data *data, int fr, char *err);


//---------------------- ADDITIONAL FUNCTIONS -------------------/
int     is_whitespace(char c);
int     empty_line(char *str);
int     all_isdigit(char *str);
int     ft_2dstrlen(char **str2d);

//---------------------- DISPLAY FUNCTIONS -------------------/
void    display_list(t_info *list);
void    display_table(char **table);

#endif