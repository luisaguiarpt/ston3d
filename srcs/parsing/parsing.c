#include "../../incs/cub3d.h"

void	parse_cub_file(t_core *core, char *map_path)
{
	int		map_fd;
	
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
	parse_textures(core, map_fd);
	parse_map(core, map_path, map_fd);
	close(map_fd);
}

void	error_parsing(t_core *core, char *message, int map_fd)
{
	ft_printf("error: %s\n", message);
	free_core(core);
	if (map_fd)
		close(map_fd);
	exit(EXIT_FAILURE);
}
