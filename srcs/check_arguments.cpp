#include <stdio.h>
#include <string.h>

int check_arguments(int ac, char **av)
{
	return (0);
	if (ac != 2)
	{
		printf("Usage: %s <map_file>\n", av[0]);
		return (1);
	}
	if (strrchr(av[1], '.') == NULL || strcmp(strrchr(av[1], '.'), ".mfa") != 0)
	{
		printf("Error: %s is not a valid map file\n", av[1]);
		return (1);
	}
	return (0);
}