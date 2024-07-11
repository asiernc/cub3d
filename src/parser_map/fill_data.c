/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:31:18 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/11 15:11:33 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/libft/libft.h"

static char	*prepare_line(t_cub3d *cub3d, char *str)
{
	char	*trimmed;
	char	*clean;

	trimmed = NULL;
	clean = NULL;
	trimmed = ft_strtrim(str, " ");
	if (!trimmed)
		ft_put_error(cub3d, "Malloc error on trim", false);
	clean = clean_spaces_str(trimmed);
	free(trimmed);
	return (clean);
}

int	fill_data(t_cub3d *cub3d, char *line)
{
	char	*clean_line;
	char	**split_line;
	int		i;

	clean_line = prepare_line(cub3d, line);
	split_line = ft_split(clean_line, ' ');
	if (!split_line)
		ft_put_error(cub3d, "Malloc error on split", false);
	fill_textures(cub3d, split_line);
	fill_colors(cub3d, split_line);
	i = -1;
	while (split_line[++i])
		free(split_line[i]);
	free(split_line);
	free(clean_line);
	return (0);
}

static void	check_fill_textures(t_cub3d *cub3d, char **key, char *value)
{
	int	fd;

	if (*key)
		ft_put_error(cub3d, "Error. Duplicate same orientation.", true);
	if (!ft_strnstr_end(value, ".xpm"))
		ft_put_error(cub3d, "Error. Texture file type is not .xpm", true);
	fd = open(value, O_RDONLY, 0644);
	if (fd < 0)
		ft_put_error(cub3d, "Error. Open texture file error.", false);
	close(fd);
	*key = ft_strdup(value);
}

void	fill_textures(t_cub3d *cub3d, char **line)
{
	if (!line || !line[0] || !line[1])
		return ;
	if (!ft_strncmp(line[0], "NO", 3))
		check_fill_textures(cub3d, &cub3d->data.no_path, line[1]);
	else if (!ft_strncmp(line[0], "SO", 3))
		check_fill_textures(cub3d, &cub3d->data.so_path, line[1]);
	else if (!ft_strncmp(line[0], "WE", 3))
		check_fill_textures(cub3d, &cub3d->data.we_path, line[1]);
	else if (!ft_strncmp(line[0], "EA", 3))
		check_fill_textures(cub3d, &cub3d->data.ea_path, line[1]);
}

void	fill_colors(t_cub3d *cub3d, char **line)
{
	if (!line || !line[0])
		return ;
	if (!ft_strncmp(line[0], "F", 2))
		cub3d->data.floor = read_colors(cub3d, line);
	if (!ft_strncmp(line[0], "C", 2))
		cub3d->data.ceil = read_colors(cub3d, line);
}
