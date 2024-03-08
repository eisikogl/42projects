/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 06:08:23 by eisikogl          #+#    #+#             */
/*   Updated: 2022/12/30 14:38:25 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

size_t	ft_getlinelen(char *temp)
{
	size_t	len;

	len = 0;
	while (temp[len] && temp[len] != '\n')
		len++;
	return (len);
}

char	*ft_getline(char *save)
{
	int		i;
	char	*line;

	i = 0;
	if (!save[i])
		return (NULL);
	line = (char *)malloc(sizeof(char) * (ft_getlinelen(save) + 2));
	if (!line)
		return (NULL);
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_save(char *save)
{
	char	*s;
	size_t	len;
	int		i;

	i = 0;
	len = ft_getlinelen(save);
	if (!save[len])
	{
		free(save);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ftg_strlen(save) - len + 1));
	if (!s)
		return (NULL);
	len++;
	while (save[len])
		s[i++] = save[len++];
	s[i] = '\0';
	free(save);
	return (s);
}

char	*ft_read(int fd, char *str)
{
	char	*buff;
	int		read_file;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	read_file = 1;
	while (!ftg_strchr(str, '\n') && read_file != 0)
	{
		read_file = read(fd, buff, BUFFER_SIZE);
		if (read_file == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_file] = '\0';
		str = ftg_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	save = ft_read(fd, save);
	if (!save)
		return (NULL);
	line = ft_getline(save);
	save = ft_save(save);
	return (line);
}
