/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:43:21 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	error_msg_cd(char *str, char *msg);
static int	check_is_dir_cd(t_cmd *command);
static void	change_dir(char *dir);
static void	change_dir_old_pwd(void);

int	cd_builtin(t_cmd *command)
{
	if (command->exec[1] && command->exec[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		g_minishell.exit_code = EXIT_FAILURE;
		return (g_minishell.exit_code);
	}
	if (strcmp_eq(command->exec[1], "-"))
		change_dir_old_pwd();
	else if (command->exec[1] == NULL || strcmp_eq(command->exec[1], "~")
		|| strcmp_eq(command->exec[1], "~/"))
		change_dir(getenv("HOME"));
	else if (check_is_dir_cd(command))
		change_dir(command->exec[1]);
	return (0);
}

static void	error_msg_cd(char *str, char *msg)
{
	ft_putstr_fd("-minishell: ", 2);
	ft_putstr_fd("cd: ", 2);
	put_msg(str, msg, 2);
	g_minishell.exit_code = 1;
}

static int	check_is_dir_cd(t_cmd *command)
{
	DIR	*dir;

	dir = opendir(command->exec[1]);
	if (!dir && access(command->exec[1], 0) == -1)
	{
		error_msg_cd(command->exec[1], "No such file or directory");
		return (0);
	}
	if (access(command->exec[1], 0) == 0 && !dir)
	{
		error_msg_cd(command->exec[1], "Not a directory");
		return (0);
	}
	closedir(dir);
	return (1);
}

static void	change_dir(char *dir)
{
	char	*new_pwd;
	char	cwd[1024];
	char	*old_pwd;
	char	old_cwd[1024];

	old_pwd = ft_strcat("OLDPWD=", getcwd(old_cwd, 1024));
	chdir(dir);
	new_pwd = ft_strcat("PWD=", getcwd(cwd, 1024));
	save_env_var(new_pwd, 1);
	save_env_var(old_pwd, 1);
	free(new_pwd);
	free(old_pwd);
}

static void	change_dir_old_pwd(void)
{
	char	*old_pwd;

	old_pwd = search_env_value("OLDPWD");
	if (old_pwd == NULL)
	{
		ft_putstr_fd("-minishell: cd: OLDPWD not set\n", 2);
		g_minishell.exit_code = 1;
	}
	else
	{
		printf("%s\n", old_pwd);
		change_dir(old_pwd);
	}
}
