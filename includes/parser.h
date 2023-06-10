/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: verdant <verdant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:57:53 by ahammout          #+#    #+#             */
/*   Updated: 2023/06/10 10:46:39 by verdant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdlib.h>

# include "../lib/libft/libft.h"
# include "get_next_line.h"

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
}               t_data;

bool    parser(char **av, t_data *data);
void    add_node(t_data *data, int *index_ptr, t_info **ptr);
int     is_wall (char *line);
void    handle_file(int map_fd, t_data *data);
void    handle_map(t_data *data, int map_fd, char *holder);
int     handle_elements(char *line, t_data *data, t_info *ptr);
void    parse_directions(t_data *data, char *line, t_info *ptr);
int     direction_identifier(t_data *data, char *line);
void    parse_fc(t_data *data, char *line, t_info *ptr);
int     check_fc(t_data *data, char *line);
int     check_path(char *line);
int     direction_handler(char *line);
int     check_map(char *line);
int     find_comma(char *line);
int     get_color(char *line);
void    build_map(t_data *data, char *line);
char    **get_element(t_data *data, int identifier);

int     surrounded_map(t_data *data);
char    **cut_last_lines(t_data *data);
void    analyze_map(t_data *data);

void    free_elements_lst(t_data *data);
void    free_map(t_data *data);
void    free_data(t_data *data);


//////////////////////// Tools ////////////////////////////////
void    exit_error(t_data *data, int fr, char *err);
int     find_char(char *str, char c);
int     is_whitespace(char c);
int     empty_line(char *str);
int     all_isdigit(char *str);
int     ft_2dstrlen(char **str2d);
void    free_2darray(t_data *data);
void    free_map_list(t_data *data);
void    display_list(t_info *list);
void    display_table(char **table);

#endif