#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

//combs
//4 -> 1234
//2-1 -> 3214 | 3124
//3-1 -> 2314 | 1324
//3-2 -> 1243 | 2341 | 1342
//2-2 -> 3412 | 2413 | 1423
/*
void	combs(void)
{
	while(4 != 1234 && 21 != (3214 || 3124) && 31 != (2314 || 1324)
    && 32 != (1243 || 2341 || 1342) && 22 != (3412 || 2413 || 1423))
	{
}
void	takenum(char *ptr)
{	
	//ptr = (char*)malloc(31);
}

void findsolution()
{


}

void printsolution()
{

}

*/
int	main(void)
{
	int r=4, c=4, len=0;
    int *ptr, **field;
    int count = 0,i,j;
	int	k;
	int	i_c;
	int	kk;
	int	colup[4];
	int	coldown[4];
	int	rowleft[4];
	int	rowright[4];
	int	index;
	int	index2;

	len = sizeof(int *) * r + sizeof(int) * c * r;
	field = (int **)malloc(len);
	ptr = (int *)(field + r);
	i = 0;
	while (i < r)
	{
		field[i] = (ptr + c * i);
		i++;
	}
	char	str[] = "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2";
	index = 0;
	index2 = 0;
	while (str[index] != '\0')
	{	
		if (str[index] != ' ')
		{
			if (index2 > 3)
			{
				index2 = 0;
			}
			if (index < 6)
			{
				colup[index2] = str[index] - '0';
			}
			else if (index < 16)
			{
				coldown[index2] = str[index] - '0';
			}
			else if (index < 24)
			{
				rowleft[index2] = str[index] - '0';
			}
			else if (index < 32)
			{
				rowright[index2] = str[index] - '0';
			}
			index2++;
		}
		index++;
	}
	i = 0;
	kk = 0;
	while (i < 4)
	{
		if (colup[i] == 4)
		{
			field[0][i] = 1;
			field[1][i] = 2;
			field[2][i] = 3;
			field[3][i] = 4;
		}
		if (coldown[i] == 4)
		{
			field[3][i] = 1;
			field[2][i] = 2;
			field[1][i] = 3;
			field[0][i] = 4;
		}
		if (rowleft[i] == 4)
		{
			field[i][0] = 1;
			field[i][1] = 2;
			field[i][2] = 3;
			field[i][3] = 4;
		}
		if (rowright[i] == 4)
		{
			field[i][3] = 1;
			field[i][2] = 2;
			field[i][1] = 3;
			field[i][0] = 4;
		}
		i++;
	}
	j = 0;
	k = 0;
	while (j < 4)
	{
		k = 0;
		while (k < 4)
		{
			char	number;
			number = field[j][k] + '0';
			write(1, &number, 1);
			if (k < 3)
			{
				write (1, " ", 1);
			}
			k++;
		}
		if (j < 3)
			write (1, "\n", 1);
		j++;
	}
}
