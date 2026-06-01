#include "../../incs/cub3d.h"

void	parse_ctx_init(t_parse_ctx *ctx)
{
	ctx->assets = NULL;
	ctx->first_map_line = NULL;
	ctx->line_no = 0;
	ctx->state = PARSER_IN_HEADER;
}

void	parse_ctx_free(t_parse_ctx *ctx)
{
	t_asset_node	*tmp;

	while (ctx->assets)
	{
		tmp = ctx->assets->next;
		free(ctx->assets->key);
		free(ctx->assets->value);
		free(ctx->assets);
		ctx->assets = tmp;
	}
	if (ctx->first_map_line)
	{
		free(ctx->first_map_line);
		ctx->first_map_line = NULL;
	}
}

t_asset_node	*parse_dict_find(t_parse_ctx *ctx, const char *key)
{
	t_asset_node	*node;

	node = ctx->assets;
	while (node)
	{
		if (!ft_strcmp(node->key, key))
			return (node);
		node = node->next;
	}
	return (NULL);
}

bool	parse_dict_insert(t_core *core, t_parse_ctx *ctx, char *key, char *value, int map_fd)
{
	t_asset_node	*node;
	t_asset_node	*dup;
	char			msg[256];

	dup = parse_dict_find(ctx, key);
	if (dup)
	{
		snprintf(msg, sizeof(msg),
			"duplicate key '%s' at line %d (already defined at line %d)",
			key, ctx->line_no, dup->line_no);
		parser_error(core, ctx, msg, map_fd);
	}
	node = ft_calloc(1, sizeof(t_asset_node));
	if (!node)
		parser_error(core, ctx, "not enough memory", map_fd);
	node->key = key;
	node->value = value;
	node->line_no = ctx->line_no;
	node->next = ctx->assets;
	ctx->assets = node;
	return (true);
}
