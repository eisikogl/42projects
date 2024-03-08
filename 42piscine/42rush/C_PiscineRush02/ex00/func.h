#ifndef FUNC_H
# define FUNC_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "check.h"
# include "numbers.h"

int	begin_func(int *len_s, char **str, char *file_name, char **mem);
int	end_func(int *len_s, char **str, char *fname, char **mem);
int	number_func(int line_s, char *str, char *file_name, char **mem);
int	control_func(char *arg, char *file_name, int len, char **mem);
int	putnbr(char *arg, char *file_name, int len);

#endif 
