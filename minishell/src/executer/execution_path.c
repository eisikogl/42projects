/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:44:14 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	command_path_error(t_cmd *command, int error_code);
static void	check_accessability(t_cmd *command, char **path_list, char **path);
static char	*split_path(t_cmd *command);
static char	*three_str_cat(const char *s1, const char *s2, const char *s3);

char	*get_command_path(t_cmd *command)
{
	char	*path;

	if (!*command->exec)
		return (NULL);
	if (command->exec_path)
		free(command->exec_path);
	if (is_builtin_command(command))
		path = ft_strdup(command->exec[0]);
	else
	{
		path = split_path(command);
		if (!path)
		{
			if (!search_env_value("PATH"))
				command_path_error(command, 1);
			else
				command_path_error(command, 2);
			free(path);
		}
	}
	return (path);
}

static void	command_path_error(t_cmd *command, int error_code)
{
	if (error_code == 1)
	{
		g_minishell.exit_code = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command->exec[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		g_minishell.exit_code = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command->exec[0], 2);
		ft_putstr_fd(": Command not found\n", 2);
	}
}

static char	*three_str_cat(const char *s1, const char *s2, const char *s3)
{
	char	*res;
	size_t	s1_len;
	size_t	s2_len;
	size_t	s3_len;

	if (!s1 || !s2 || !s3)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3_len = ft_strlen(s3);
	res = malloc(s1_len + s2_len + s3_len + 1);
	if (res)
	{
		ft_memcpy(res, s1, s1_len);
		ft_memcpy(res + s1_len, s2, s2_len);
		ft_memcpy(res + s1_len + s2_len, s3, s3_len + 1);
	}
	res[s1_len + s2_len + s3_len + 1] = '\0';
	return (res);
}

static void	check_accessability(t_cmd *command, char **path_list, char **path)
{
	char	*temp;
	int		i;

	i = -1;
	while (path_list[++i])
	{
		temp = three_str_cat(path_list[i], "/", command->exec[0]);
		if (access(temp, F_OK) == 0)
		{
			*path = temp;
			break ;
		}
		free(temp);
	}
	free_path(path_list);
}

static char	*split_path(t_cmd *command)
{
	char	**path_list;
	char	*path;
	char	*temp;

	path_list = NULL;
	path = NULL;
	if (ft_strchr(command->exec[0], '/') != NULL)
	{
		path = ft_strdup(command->exec[0]);
		return (path);
	}
	temp = search_env_value("PATH");
	if (temp)
		path_list = ft_split(temp, ':');
	if (path_list)
		check_accessability(command, path_list, &path);
	if (!path && !access(command->exec[0], F_OK | X_OK))
		path = ft_strdup(command->exec[0]);
	return (path);
}
