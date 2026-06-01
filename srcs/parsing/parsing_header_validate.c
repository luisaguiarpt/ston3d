#include "../../incs/cub3d.h"

static const t_asset_spec	g_asset_specs[] = {
{"NO", ASSET_PATH, true},
{"SO", ASSET_PATH, true},
{"WE", ASSET_PATH, true},
{"EA", ASSET_PATH, true},
{"F", ASSET_RGB, true},
{"C", ASSET_RGB, true},
{NULL, 0, false}
};

bool	parse_rgb_triplet(char *line, int out[3])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < 3)
	{
		while (is_space(line[i]))
			i++;
		if (!ft_isdigit(line[i]))
			return (false);
		out[j] = 0;
		while (ft_isdigit(line[i]))
			out[j] = (out[j] * 10) + (line[i++] - '0');
		if (out[j] < 0 || out[j] > 255)
			return (false);
		while (is_space(line[i]))
			i++;
		if (j < 2)
		{
			if (line[i] != ',')
				return (false);
			i++;
		}
		j++;
	}
	while (is_space(line[i]))
		i++;
	return (line[i] == '\0');
}

static bool	validate_asset_value(t_asset_spec spec, char *value)
{
	int		rgb[3];
	int		i;

	if (spec.type == ASSET_PATH)
	{
		i = 0;
		while (value[i])
		{
			if (is_space(value[i]))
				return (false);
			i++;
		}
		return (is_xpm_file(value));
	}
	return (parse_rgb_triplet(value, rgb));
}

void	validate_header_assets(t_core *core, int map_fd, t_parse_ctx *ctx)
{
	int				i;
	t_asset_node	*node;
	char			msg[128];

	i = 0;
	while (g_asset_specs[i].key)
	{
		node = parse_dict_find(ctx, g_asset_specs[i].key);
		if (!node && g_asset_specs[i].required)
		{
			snprintf(msg, sizeof(msg), "missing required header key '%s'",
				g_asset_specs[i].key);
			parser_error(core, ctx, msg, map_fd);
		}
		if (node && !validate_asset_value(g_asset_specs[i], node->value))
		{
			snprintf(msg, sizeof(msg), "invalid value for key '%s' (line %d)",
				g_asset_specs[i].key, node->line_no);
			parser_error(core, ctx, msg, map_fd);
		}
		i++;
	}
}
