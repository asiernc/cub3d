/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:31:18 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/26 15:40:40 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/libft/libft.h"

char	*prepare_line(t_cub3d *cub3d, char *str)
{
	char	*trimmed;
	char	*clean;

	trimmed = ft_strtrim(str, " ");
	if (!trimmed)
		ft_put_error(cub3d, "Malloc error on trim", false);
	clean = clean_spaces_str(trimmed);
	free(trimmed);
	return (clean);
}

void	remove_newline(char *line)
{
	int	len;

	len = (int)ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n'
			|| line[len - 1] == ' ' || line[len - 1] == '\t'))
	{
		line[len - 1] = '\0';
		len--;
	}
}

static int	ft_count_word(char *str)
{
	int	i;
	int	count;
	int	flag;

	count = 0;
	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] <= 32 || str[i] == ',')
		{
			if (!flag)
			{
				flag = 1;
				count++;
			}
		}
		else
		{
			flag = 0;
			count++;
		}
		i++;
	}
	return (count + 1);
}

char	*clean_spaces_str(char *str)
{
	char	*res;
	int		i;
	int		j;
	int		flag;

	res = ft_calloc(ft_count_word(str), sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if ((str[i] <= 32 || str[i] == ',') && !flag)
		{
			flag = 1;
			res[j++] = ' ';
		}
		if (!(str[i] <= 32 || str[i] == ','))
		{
			flag = 0;
			res[j++] = str[i];
		}
	}
	return (res);
}

void	init_parser_struct(t_data *data)
{
	data->map = NULL;
	data->height = 0;
	data->width = 0;
	data->no_path = NULL;
	data->ea_path = NULL;
	data->so_path = NULL;
	data->we_path = NULL;
	data->map_file_path = NULL;
	data->ceil = -1;
	data->floor = -1;
	data->flag_map = 0;
	data->flag_complete = 0;
}
