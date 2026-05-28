#include "../../incs/cub3d.h"

bool	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	else 
		return (false);
}

bool	is_digit(char c)
{
	if (c < '0' || c > '9')
		return (false);
	else
		return (true);
}
