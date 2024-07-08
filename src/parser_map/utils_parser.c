/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:31:18 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/05 12:00:32 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/libft/libft.h"

void	remove_newline(char *line)
{
	int	len;

	len = (int)ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == ' '
			|| line[len - 1] == '\t'))
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
	return (count);
}

static char	*clean_spaces_str(char *str)
{
	char	*res;
	int		i;
	int		j;
	int		flag;

	i = ft_count_word(str);
	res = malloc(i + 1);
	if (!res)
		return (NULL);
	res[i] = '\0';
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] <= 32 || str[i] == ',')
		{
			if (!flag)
			{
				flag = 1;
				res[j++] = ' ';
			}
		}
		else
		{
			flag = 0;
			res[j++] = str[i];
		}
		i++;
	}
	return (res);
}

char	*clear_input_line(char *str, int flag)
{
	char	*trimmed;
	char	*clean;

	trimmed = NULL;
	clean = NULL;
	if (flag == 0)
	{
		trimmed = ft_strtrim(str, " ");
		clean = clean_spaces_str(trimmed);
		free(trimmed);
		return (clean);
	}
	return (NULL);
}

void	test_print(t_data *data)
{
	int	i;

	printf("NO PATH => %s\n", data->no_path);
	printf("EA PATH => %s\n", data->ea_path);
	printf("SO PATH => %s\n", data->so_path);
	printf("WE PATH => %s\n", data->we_path);
	printf("FLOOR COLOR => %u\n", data->floor);
	printf("CEIL COLOR => %u\n", data->ceil);
	i = 0;
	if (data->map && data->map[0])
	{
		while (data->map[i])
		{
			printf("%s\n", data->map[i]);
			i++;
		}
	}
}


