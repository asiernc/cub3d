/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:31:18 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/23 16:36:22 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/libft/libft.h"

int	ft_strlen_map(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			flag++;
		i++;
	}
	i += flag * 3;
	return (i);
}

static char	*dup_map_line(char *str, int witdh)
{
	char	*cpy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	cpy = ft_calloc((witdh + 1), sizeof(char));
	if (!cpy)
		return (NULL);
	ft_memset(cpy, ' ', witdh);
	cpy[witdh] = '\0';
	while (str[i] != '\0')
	{
		if (str[i] == '\t')
			j += 3;
		else
			cpy[j] = str[i];
		i++;
		j++;
	}
	return (cpy);
}

void	fill_map(t_cub3d *cub3d, char *line, int i)
{
	if (i == 0)
		check_required_data_for_map(cub3d);
	if (i == cub3d->data.height - 1)
		cub3d->data.flag_complete = 1;
	cub3d->data.map[i] = dup_map_line(line, cub3d->data.width);
}
