/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:57:53 by ahammout          #+#    #+#             */
/*   Updated: 2023/05/29 17:38:43 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
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


typedef struct  s_list
{
    char    *line;
    int     type;
    int     index;
    struct  s_list *next;
    struct  s_list *prev;
}               t_list;

int **parser(char **av);


//////////////////////// Tools ////////////////////////////////
int     is_whitespace(char c);
int     white_check(char *str);
int     all_isdigit(char *str);

#endif