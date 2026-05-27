#include "../../incs/cub3d.h"

void	remove_newline(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

bool	is_cub_file(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len < 4)
		return (false);
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

	len = ft_strlen(line) - 1;
	if (len < 4)
		return (false);
	while (len > 0 && is_space(line[len]))
		len--;
	if (line[len - 3] != '.'
	 	|| line[len - 2] != 'x'
	 	|| line[len - 1] != 'p'
	 	|| line[len] != 'm')
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
