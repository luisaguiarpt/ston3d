#include "../../incs/cub3d.h"

static void	parse_header_asset_line(t_core *core, int map_fd, t_parse_ctx *ctx, char *line)
{
	char	*key;
	char	*value;

	if (!lex_header_line(line, &key, &value))
		parser_error(core, ctx, "invalid header directive format", map_fd);
	if (!is_header_key(key))
	{
		free(key);
		free(value);
		parser_error(core, ctx, "unknown header directive", map_fd);
	}
	parse_dict_insert(core, ctx, key, value, map_fd);
}

void	parse_header(t_core *core, int map_fd, t_parse_ctx *ctx)
{
	char	*line;

	while (ctx->state == PARSER_IN_HEADER)
	{
		line = get_next_line(map_fd);
		if (!line)
			parser_error(core, ctx, "unexpected end of file while reading header", map_fd);
		ctx->line_no++;
		remove_newline(line);
		if (is_empty_line(line))
		{
			free(line);
			continue ;
		}
		if (is_map_start_line(line))
		{
			ctx->first_map_line = ft_strdup(line);
			free(line);
			if (!ctx->first_map_line)
				parser_error(core, ctx, "not enough memory", map_fd);
			ctx->state = PARSER_IN_MAP;
			break ;
		}
		parse_header_asset_line(core, map_fd, ctx, line);
		free(line);
	}
}
