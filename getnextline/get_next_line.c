/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 06:08:23 by eisikogl          #+#    #+#             */
/*   Updated: 2022/04/09 06:09:07 by eisikogl         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	if (save[i] == '\n')
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
	s = (char *)malloc(sizeof(char) * (ft_strlen(save) - len + 1));
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
	while (!ft_strchr(str, '\n') && read_file != 0)
	{
		read_file = read(fd, buff, BUFFER_SIZE);
		if (read_file == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_file] = '\0';
		str = ft_strjoin(str, buff);
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

/*
int main()
{
	int fd;
//	int i = 0;
	fd = open("Hello.txt", O_RDONLY);
	char *line;
	line = get_next_line(fd);
	//line = get_next_line(fd);
	//line = get_next_line(fd);
	printf("%s \n", line);
}
*/
