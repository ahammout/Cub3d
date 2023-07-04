/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:56:01 by ahammout          #+#    #+#             */
/*   Updated: 2023/06/27 23:45:48 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"

int main(int argc, char **argv)
{
		t_data	parser_data;

		parser_data.map = NULL;
		if (argc != 2)
				return (printf("Error\n[USAGE]: ./Cub3d [map location]\n") , -1);
		parser(argv, &parser_data);
		free_data(&parser_data);
		printf("Done\n");
		return (0);
} 