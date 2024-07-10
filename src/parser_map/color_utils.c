/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:33:46 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/10 12:14:55 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/libft/libft.h"

static bool	check_more_letters(char **line)
{
	int	i;
	int	j;
	int	flag;

	i = -1;
	flag = 0;
	while (line[++i])
	{
		j = -1;
		while (line[i][++j])
		{
			if (ft_isalpha(line[i][j]))
				flag++;
			if (!ft_isalnum(line[i][j]))
				flag++;
		}
	}
	if (flag > 1)
		return (true);
	return (false);
}

static void	check_values_rgb(char **line)
{
	int	i;
	int	num;
	int	counter;

	i = 1;
	counter = 0;
	if (!line)
		return ;
	while (line[i])
	{
		num = ft_atoi(line[i]);
		if (num < 0 || num > 255)
			ft_put_error("Error. Color out of RGB range", true);
		counter++;
		i++;
	}
	if (counter != 3)
		ft_put_error("Error. Missing RGB color", true);
}

unsigned int	rgb_to_int(int red, int green, int blue)
{
	unsigned int		color;

	color = 0;
	color |= blue;
	color |= green << 8;
	color |= red << 16;
	return (color);
}

unsigned int	read_colors(char **line)
{
	int				color[3];
	int				i;
	int				j;

	if (check_more_letters(line) == true)
		ft_put_error("Error. Incorrect argument in color line", true);
	check_values_rgb(line);
	i = 1;
	j = 0;
	while (line[i] && j < 3)
	{
		color[j] = ft_atoi(line[i]);
		i++;
		j++;
	}
	return (rgb_to_int(color[0], color[1], color[2]));
}
