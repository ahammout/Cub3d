/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:38:24 by ahammout          #+#    #+#             */
/*   Updated: 2023/07/10 04:26:16 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parser.h"

int	fetch_rgb(t_data *data)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!data->info->elem[i])
			return (ft_putstr_fd("Cub3d: bad RGB value\n", 2), -1);
		i++;
	}
	return (0);
}

int	fetch_info(t_data *data, int identifier)
{
	t_info	*ptr;
	int		e_exist;

	ptr = data->info;
	e_exist = 0;
	while (data->info)
	{
		if (data->info->type == identifier)
			e_exist++;
		if (data->info->type == C || data->info->type == F)
		{
			if (fetch_rgb(data) == -1)
			{
				data->info = ptr;
				exit_error(data, 1, NULL);
			}
		}
		data->info = data->info->next;
	}
	data->info = ptr;
	if (e_exist == 0 || e_exist > 1)
		return (-1);
	return (0);
}

void	analyze_elements(t_data *data)
{
	if (fetch_info(data, SO) == -1 || fetch_info(data, WE) == -1 \
		|| fetch_info(data, NO) == -1 || fetch_info(data, EA) == -1 \
		|| fetch_info(data, C) == -1 || fetch_info(data, F) == -1)
		exit_error(data, 1, "Cub3d: identifier missing!\n");
}
