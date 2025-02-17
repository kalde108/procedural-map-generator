#ifndef MAP_H
# define MAP_H

# define PERLIN_NOISE 3

# define MAP_WIDTH 1024
# define MAP_HEIGHT 1024

class Map {
public:
	Map();
	~Map();

private:
	int		*temperature_map;
	int 	*humidity_map;
	int		*height_map;
};


#endif
