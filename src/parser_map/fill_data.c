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

static char	*prepare_line(char *str)
{
	char	*trimmed;
	char	*clean;

	trimmed = NULL;
	clean = NULL;
	trimmed = ft_strtrim(str, " ");
	clean = clean_spaces_str(trimmed);
	if (trimmed)
		free(trimmed);
	return (clean);
}

int	fill_data(t_cub3d *cub3d, char *line)
{
	char	*clean_line;
	char	**split_line;
	int		i;

	clean_line = prepare_line(line);
	split_line = ft_split(clean_line, ' ');
	if (!split_line)
		ft_put_error("Malloc error", true);
	fill_textures(cub3d, split_line);
	fill_colors(cub3d, split_line);
	i = -1;
	while (split_line[++i])
		free(split_line[i]);
	free(split_line);
	free(clean_line);
	return (0);
}

static void	check_fill_textures(char **key, char *value)
{
	int	fd;

	if (*key)
		ft_put_error("Error. Duplicate same orientation.", true);
	if (!ft_strnstr_end(value, ".xpm"))
		ft_put_error("Error. Texture file type is not .cub.", true);
	fd = open(value, O_RDONLY, 0644);
	if (fd < 0)
		ft_put_error("Error. Open texture file error.", false);
	close(fd);
	*key = ft_strdup(value);
}

void	fill_textures(t_cub3d *cub3d, char **line)
{
	if (!line || !line[0])
		return ;
	if (!ft_strncmp(line[0], "NO", 3))
		check_fill_textures(&cub3d->data.no_path, line[1]);
	else if (!ft_strncmp(line[0], "SO", 3))
		check_fill_textures(&cub3d->data.so_path, line[1]);
	else if (!ft_strncmp(line[0], "WE", 3))
		check_fill_textures(&cub3d->data.we_path, line[1]);
	else if (!ft_strncmp(line[0], "EA", 3))
		check_fill_textures(&cub3d->data.ea_path, line[1]);
}

void	fill_colors(t_cub3d *cub3d, char **line)
{
	if (!line || !line[0])
		return ;
	if (!ft_strncmp(line[0], "F", 2))
		cub3d->data.floor = read_colors(line);
	if (!ft_strncmp(line[0], "C", 2))
		cub3d->data.ceil = read_colors(line);
}
