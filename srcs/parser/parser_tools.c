/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 04:51:17 by ahammout          #+#    #+#             */
/*   Updated: 2023/06/18 05:01:31 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

void	add_node(t_data *data, int *index_ptr, t_info **ptr)
{
	t_info	*node;

	if (*index_ptr == 0)
	{
		data->map = NULL;
		data->info = malloc(sizeof(t_info));
		if (!data->info)
			exit_error(data, 0, "Cub3d: Allocation failed");
		data->info->index = *index_ptr;
		data->info->elem = NULL;
		data->info->type = 0;
		data->info->next = NULL;
		*ptr = data->info;
	}
	else if (*index_ptr > 0)
	{
		node = malloc(sizeof(t_info));
		node->index = *index_ptr;
		node->elem = NULL;
		node->next = NULL;
		node->type = 0;
		data->info->next = node;
		data->info = data->info->next;
	}
}

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	if (data->map)
	{
		while (data->map[i])
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
}

void	free_elements_lst(t_data *data)
{
	t_info	*tofree;
	int		i;

	i = 0;
	if (data->info)
	{
		while (data->info)
		{
			tofree = data->info;
			if (data->info->elem)
			{
				while (data->info->elem[i])
				{
					free(data->info->elem[i]);
					i++;
				}
				free(data->info->elem);
			}
			data->info = data->info->next;
			free(tofree);
		}
	}
}

void	free_data(t_data *data)
{
	free_elements_lst(data);
	free_map(data);
}

void	exit_error(t_data *data, int fr, char *err)
{
	if (err)
		ft_putstr_fd(err, 2);
	if (fr)
		free_data(data);
	exit (EXIT_FAILURE);
}
