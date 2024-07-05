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

/*void	clear_line(char *s)
{
	int len;
	
	len = ft_strlen(s);
	while (len && ft_isspace(s[len - 1]))
		--len;
	while (len && ft_isspace(*s) && *s++)
		--len;
	while (len--)
	{
		if (!ft_isspace(*s) || (*(s + 1) && !ft_isspace(*(s + 1))))
			write(1, s, 1);
		s++;
	}
}*/

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

char	*clear_input_line(char *str)
{
	char	*trimmed;
	char	*clean;
	//int		i;

	trimmed = ft_strtrim(str, " \n");
	clean = clean_spaces_str(trimmed);
	free(trimmed);
	return (clean);
}

