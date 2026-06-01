#include "../../incs/cub3d.h"

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

bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line[i])
		return (true);
	while (line[i])
	{
		if (is_space(line[i]))
			i++;
		else
			return (false);
	}
	return (true);
}

bool	is_valid_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_space(line[i])
			&& line[i] != '0'
	  		&& line[i] != '1'
	  		&& line[i] != 'N'
	  		&& line[i] != 'S'
	  		&& line[i] != 'E'
	  		&& line[i] != 'W')
			return (false);
		i++;
	}
	return (true);
}

void	remove_newline(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

bool	lex_header_line(char *line, char **key, char **value)
{
	int		i;
	int		start;
	char	*trimmed;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (!line[i])
		return (false);
	start = i;
	while (line[i] && !is_space(line[i]))
		i++;
	*key = ft_substr(line, start, i - start);
	if (!*key)
		return (false);
	while (is_space(line[i]))
		i++;
	trimmed = ft_strtrim(line + i, " \t");
	if (!trimmed)
	{
		free(*key);
		return (false);
	}
	if (!trimmed[0])
	{
		free(*key);
		free(trimmed);
		return (false);
	}
	*value = trimmed;
	return (true);
}
