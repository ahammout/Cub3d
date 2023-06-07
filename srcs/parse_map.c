/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:08:38 by ahammout          #+#    #+#             */
/*   Updated: 2023/06/07 15:38:47 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"

void    build_map(t_data *data, char *line)
{
    int i;
    int j;
    int s;

    i = 0;
    s = 0;
    j = 0;
    while (line[i])
    {
        if (line[i] == '\n')
            s++;
        i++;
    }
    i = 0;
    data->map = malloc(sizeof(char *) * s + 1);
    while(line[i])
    {
        data->map[j] = ft_substr(line + i, 0, find_char(line + i, '\n'));
        i += (find_char(line + i, '\n') + 1);
        j++;
    }
    data->map[j] = NULL;
    //// ADD A FUNCTION THAT ADDS THE SPACES AT THE END OF EACH LINE
}

int check_map(char *line)
{
    char    *comps;
    int     i;
    int     j;

    i = 0;
    if (!line)
        return (0);
    comps = ft_strdup("\nSWNE01 ");
    if (empty_line(line))
        return (ft_putstr_fd("Cub3d: Impty line inside the map", 2), -1);
    while (line[i])
    {
        j = 0;
        while (comps[j])
        {
            if (line[i] == comps[j])
                break;
            j++;
        }
        if (!comps[j])
            return (ft_putstr_fd("Cub3d: Invalid comp", 2), -1);
        i++;
    }
    return (0);
}

/// ADD ANGLE 
int one_player(char *line, int *player)
{
    int i;

    i = 0;
    if (line)
    {
        while (line[i])
        {
            if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
                *player += 1;
            i++;
        }
        if (*player > 1)
            return (ft_putstr_fd("Cub3d: Multiple players inside the map", 2), -1);
    }
    return (0);
}

int surrounded_map(t_data *data)
{
    int x;
    int y;

    y = 1;
    // CHECK SIDES LEFT RIGHT 
    // CHECK INSIDE
    printf("GET INTO SURROUNDED MAP\n");
    while (data->map[y + 1])
    {
        x = 0;
        while (data->map[y][x + 1])
        {
            if (data->map[y][x] == '0' || data->map[y][x] == 'E' || data->map[y][x] == 'S' || data->map[y][x] == 'N' || data->map[y][x] == 'W')
            {
                // printf("line {%d}\n Up : %c\n down : %c\n left : %c\n Right : %c\n", y, data->map[y - 1][x], data->map[y + 1][x], data->map[y][x - 1], data->map[y][x + 1]);
                if (data->map[y - 1][x] == ' ' || data->map[y - 1][x] == '\t' \
                    || data->map[y + 1][x] == ' ' || data->map[y + 1][x] == '\t' \
                    || data->map[y][x + 1] == ' ' || data->map[y][x + 1] == '\t' \
                    || data->map[y][x - 1] == ' ' || data->map[y][x - 1] == '\t')
                    return (ft_putstr_fd("Cub3d: Map must be souronded by Walls", 2), -1);
            }
            x++;
        }
        y++;
    }
    return (0);
}

void handle_map(t_data *data, int map_fd, char *holder)
{
    char    *line;
    int     player;
    char    *to_free;
    int     i;

    line = ft_strdup("");
    i = 0;
    player = 0;
    while (line)
    {
        free(line);
        line = get_next_line(map_fd);
        if (check_map(line) == -1 || one_player(line, &player) == -1)
            exit_error(data, 1, NULL);
        to_free = holder;
        holder = ft_strjoin(holder, line);
        if (line)
            free(to_free);
        i++;
    }
    build_map(data, holder);
    if (!is_wall(data->map[ft_2dstrlen(data->map) - 1]) || surrounded_map(data) == -1)
        exit_error(data, 1, "Cub3d: Map must be souronded by Walls");
}