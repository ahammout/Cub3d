/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:57:53 by ahammout          #+#    #+#             */
/*   Updated: 2023/06/02 11:29:48 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include <stdbool.h>
#include"../get_next_line/get_next_line.h"
#include"../libft/libft.h"

#define SO "SO"
#define WE "WE"
#define NO "NO"
#define EA "EA"

#define C 'C'
#define F 'F'

#define WL '1'
#define EM '0'

typedef struct  s_map
{
    char    *line;
    int     type;
    int     index;
    struct  s_list *next;
    struct  s_list *prev;
}               t_map;


typedef struct  s_data
{
    t_map   lmap;
    int     **map;
}               t_data;

bool    parser(char **av, t_data *data);


//////////////////////// Tools ////////////////////////////////
int     is_whitespace(char c);
int     white_check(char *str);
int     all_isdigit(char *str);

#endif