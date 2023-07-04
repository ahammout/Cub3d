/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilsch <mwilsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:31:26 by verdant           #+#    #+#             */
/*   Updated: 2023/07/04 15:14:44 by mwilsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

/**
 * @brief Checks if a char exits inside of a string
 * 
 * @param c char of string
 * @param search_str the characters to compare c against
 */
bool	incl_char(char c, char *search_str)
{
	int	i;

	i = 0;
	if (!search_str)
		return (false);
	while (search_str[i])
	{
		if (c == search_str[i])
			return (true);
		i++;
	}
	return (false);
}

int	ft_tercenary(int condition, int a, int b)
{
	if (condition)
		return (a);
	return (b);
}

uint32_t	pack_color(char **array)
{
	uint8_t	rgb[3];
	int		i;

	if (!array || !array[0] || !array[1] || !array[2])
		return (0);
	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(array[i]);
		rgb[i] = ft_tercenary(rgb[i] < 0, 0, rgb[i]);
		rgb[i] = ft_tercenary(rgb[i] > 255, 255, rgb[i]);
		i++;
	}
	return ((rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 255);
}

int	assign_value(char direction)
{
	if (direction == 'N')
		return (NOR);
	if (direction == 'S')
		return (SOU);
	if (direction == 'E')
		return (EAS);
	if (direction == 'W')
		return (WES);
	if (direction == '0')
		return (0);
	if (direction == '1')
		return (1);
	if (direction == ' ')
		return (2);
	return (0);
}

uint32_t	shift_col(uint8_t rgba[])
{
	return (rgba[0] << 24 | rgba[1] << 16 | rgba[2] << 8 | rgba[3]);
}
