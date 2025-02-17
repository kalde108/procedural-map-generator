
#ifndef PERLINNOISE_H
# define PERLINNOISE_H

# include <vector>

class PerlinNoise {
public:
	// Initialize with the reference values for the permutation vector
	PerlinNoise();
	// Generate a new permutation vector based on the value of seed
	PerlinNoise(unsigned int seed);
	
	// Get a noise value at point (x, y, z).
	// x, y, z are unbouded, and can be any large number.
	// The returned noise value is in the range [-1, 1]
	double noise(double x, double y, double z) const;
	double noise(double x, double y) const;
	double noise(double x) const;

	double octaveNoise(double x, double y, double z, int octaves, double persistence) const;
	double octaveNoise(double x, double y, int octaves, double persistence) const;
	double octaveNoise(double x, int octaves, double persistence) const;

private:
	static double fade(double t);
	static double lerp(double a, double b, double t);
	double grad(int ix, int iy, int iz, double x, double y, double z) const;

	// The permutation vector is simply a random jumble of all integers 0-255, duplicated to avoid wrapping
	std::vector<int> p;
};

#endif
