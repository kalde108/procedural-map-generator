#ifndef MINECRAFTNOISE_H
# define MINECRAFTNOISE_H

# include <stddef.h>
# include <vector>
# include "PerlinNoise.h"

class MinecraftNoise {
public:
	// Initialize with the reference values for the permutation vector
	MinecraftNoise(void);
	// Generate a new permutation vector based on the value of seed
	MinecraftNoise(unsigned int seed);
	MinecraftNoise(unsigned int seed, int firstOctave);
	MinecraftNoise(unsigned int seed, int firstOctave, double *amplitudes, size_t size);
	MinecraftNoise(unsigned int seed, int firstOctave, std::vector<double> &amplitudes);
	MinecraftNoise(unsigned int seed, int firstOctave, const std::vector<double>& amplitudes);
	
	// Get a noise value at point (x, y, z).
	// x, y, z are unbouded, and can be any large number.
	// The returned noise value is in the range [-1, 1]
	double noise(double x, double y, double z) const;
	double noise(double x, double y) const;
	double noise(double x) const;

private:
	static double fade(double t);
	static double lerp(double a, double b, double t);
	double grad(int ix, int iy, int iz, double x, double y, double z) const;

	void	pInit(unsigned int seed);
	void	stipAmplitude(void);

	// The permutation vector is simply a random jumble of all integers 0-255, duplicated to avoid wrapping
	std::vector<int> p;
	int startFrequency;
	std::vector<PerlinNoise> noises;
	std::vector<double> amplitudes;
	int	ampStrip;
};

// The frequency of a sub-noise at index (from 0) in the list is 2^(- firstOctave + index)
// , and the amplitude (the value of the sub-noise ranges from -amplitude to +amplitude) of this
// sub-noise is about 1.04 * doubleValueAtIndex * 2^(sizeOfThisList - index - 1) / (2^sizeOfThisList - 1)
// (assuming the range of 3D Improved Perlin Noise is ±1.04).
// 

#endif
