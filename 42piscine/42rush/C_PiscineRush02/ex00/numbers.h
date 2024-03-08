#ifndef NUMBERS_H
# define NUMBERS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "func.h"
# include "check.h"

int		jump_to_dict(int len, int file_d);
void	initial_digits(char gb[4], char tp[4], int len, char *str);
int		jump_to_line(int len, char *str, int file_d);
int		write_number(int file_d, char **mem);
int		send_number(int ln, char *str, char *file_name, char **mem);

#endif 
