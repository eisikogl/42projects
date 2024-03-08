/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 00:43:44 by eisikogl          #+#    #+#             */
/*   Updated: 2024/03/08 16:23:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	echo_builtin(char **exec)
{
	int	i;

	i = 1;
	while (strcmp_eq(exec[i], "-n"))
		i++;
	while (exec[i] != NULL)
	{
		printf("%s", exec[i]);
		if (exec[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!strcmp_eq(exec[1], "-n"))
		printf("\n");
	return (0);
}
