#include "../../incs/cub3d.h"

static char	*asset_strdup(t_core *core, t_parse_ctx *ctx, int map_fd, char *value)
{
	char	*dup;

	dup = ft_strdup(value);
	if (!dup)
		parser_error(core, ctx, "not enough memory", map_fd);
	return (dup);
}

void	materialize_header_assets(t_core *core, int map_fd, t_parse_ctx *ctx)
{
	t_asset_node	*node;

	node = parse_dict_find(ctx, "NO");
	core->textures.north = asset_strdup(core, ctx, map_fd, node->value);
	node = parse_dict_find(ctx, "SO");
	core->textures.south = asset_strdup(core, ctx, map_fd, node->value);
	node = parse_dict_find(ctx, "WE");
	core->textures.west = asset_strdup(core, ctx, map_fd, node->value);
	node = parse_dict_find(ctx, "EA");
	core->textures.east = asset_strdup(core, ctx, map_fd, node->value);
	node = parse_dict_find(ctx, "F");
	if (!parse_rgb_triplet(node->value, core->textures.floor))
		parser_error(core, ctx, "invalid floor RGB value", map_fd);
	node = parse_dict_find(ctx, "C");
	if (!parse_rgb_triplet(node->value, core->textures.ceiling))
		parser_error(core, ctx, "invalid ceiling RGB value", map_fd);
}
