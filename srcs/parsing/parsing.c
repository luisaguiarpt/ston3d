#include "../../incs/cub3d.h"

void	parse_cub_file(t_core *core, char *map_path)
{
	int			map_fd;
	t_parse_ctx	ctx;
	
	if (!is_cub_file(map_path))
	{
		ft_printf("error: map must be a .cub file\n");
		exit(EXIT_FAILURE);
	}
	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
	{
		perror("Error loading map");
		exit(EXIT_FAILURE);
	}
	parse_ctx_init(&ctx);
	parse_header(core, map_fd, &ctx);
	validate_header_assets(core, map_fd, &ctx);
	materialize_header_assets(core, map_fd, &ctx);
	parse_map(core, map_fd, &ctx);
	parse_ctx_free(&ctx);
	close(map_fd);
}

void	error_parsing(t_core *core, char *message, int map_fd)
{
	ft_printf("Error\n%s\n", message);
	free_core(core);
	if (map_fd >= 0)
		close(map_fd);
	exit(EXIT_FAILURE);
}

void	parser_error(t_core *core, t_parse_ctx *ctx, char *message, int map_fd)
{
	parse_ctx_free(ctx);
	error_parsing(core, message, map_fd);
}
