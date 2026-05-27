#include "../../incs/cub3d.h"

bool	is_cub_file(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 4] != '.'
	 	|| line[len - 3] != 'c'
	 	|| line[len - 2] != 'u'
	 	|| line[len - 1] != 'b')
		return (false);
	else
		return (true);
}

bool	is_xpm_file(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 4] != '.'
	 	|| line[len - 3] != 'x'
	 	|| line[len - 2] != 'p'
	 	|| line[len - 1] != 'm')
		return (false);
	else
		return (true);
}

bool	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	else 
		return (false);
}
