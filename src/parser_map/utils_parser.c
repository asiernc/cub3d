/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:31:18 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/04 16:44:24 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/libft/libft.h"

void	clear_line(char *s)
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
}