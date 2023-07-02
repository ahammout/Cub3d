void	draw_minimap(t_all *all)
{
	int grid_width;
	int grid_height;

	grid_height = 0;
	grid_width = 0;

	while (all->pars.map[grid_height][grid_width])
		grid_width++;
	while (all->pars.map[grid_height])
		grid_height++;

	int	x_grid, y_grid, x_pixel, y_pixel;

	y_grid = 0;
	x_pixel = 0;
	y_pixel = 0;
	while (y_grid < grid_height)
	{
		x_grid = 0;
		while (x_grid < grid_width)
		{
			x_pixel = x_grid * CELL_SIZE + xOFFSET;
			y_pixel = y_grid * CELL_SIZE + yOFFSET;
			draw_minimap_cell(all->pars.map[y_grid][x_grid], &all->mlxVars, x_pixel, y_pixel);
			x_grid++;
		}
		y_grid++;
	}
}
