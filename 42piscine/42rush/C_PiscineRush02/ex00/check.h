#ifndef CHECK_H
# define CHECK_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "func.h"
# include "numbers.h"

int	ft_atoi(char *str, int n);
int	is_alpha(char c);
int	ft_strcmp(char *s1, char *s2, int n);
int	ft_strlen(char *str);

#endif
