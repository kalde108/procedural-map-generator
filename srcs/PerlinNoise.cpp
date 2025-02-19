#include "PerlinNoise.h"

#include <numeric>
#include <random>
#include <algorithm>

PerlinNoise::PerlinNoise() {
	// Initialize the permutation vector with the reference values
	p = {
		6, 119, 52, 224, 161, 63, 89, 255, 93, 178, 68, 30, 236, 127, 183, 104, 86, 232, 133, 233,
		220, 41, 205, 144, 58, 67, 191, 149, 96, 231, 97, 209, 71, 49, 113, 2, 120, 235, 166, 223,
		46, 11, 216, 158, 15, 44, 112, 130, 27, 25, 136, 69, 196, 122, 8, 84, 227, 22, 143, 101, 3,
		51, 32, 64, 253, 13, 225, 56, 201, 230, 107, 140, 137, 204, 254, 74, 87, 19, 176, 165, 66,
		17, 207, 249, 197, 211, 54, 123, 128, 105, 202, 252, 239, 121, 181, 186, 40, 208, 146, 251,
		210, 92, 138, 79, 162, 29, 91, 83, 106, 43, 244, 21, 215, 141, 47, 95, 7, 73, 152, 241, 42,
		31, 134, 117, 156, 85, 237, 124, 172, 23, 175, 245, 33, 238, 90, 188, 203, 187, 1, 37, 38,
		14, 110, 200, 24, 229, 35, 234, 217, 16, 206, 214, 174, 60, 222, 154, 111, 116, 12, 212,
		102, 169, 177, 28, 228, 194, 147, 192, 242, 61, 193, 240, 168, 72, 213, 98, 45, 103, 114,
		53, 26, 62, 129, 248, 34, 247, 50, 153, 135, 226, 246, 88, 199, 151, 9, 65, 189, 157, 198,
		125, 132, 70, 173, 185, 180, 76, 221, 115, 81, 80, 219, 39, 145, 243, 150, 179, 148, 82,
		163, 100, 48, 160, 36, 164, 5, 118, 155, 99, 75, 170, 18, 131, 167, 139, 77, 190, 94, 195,
		218, 78, 57, 159, 4, 10, 109, 184, 182, 171, 250, 59, 142, 108, 20, 55, 126, 0
	};
	// Duplicate the permutation vector.
	p.insert(p.end(), p.begin(), p.end());
}

PerlinNoise::PerlinNoise(unsigned int seed) {
	p.resize(256);
	// Fill p with values from 0 to 255
	std::iota(p.begin(), p.end(), 0);
	// Initialize a random engine with seed
	std::default_random_engine engine(seed);
	// Suffle  using the random engine
	std::shuffle(p.begin(), p.end(), engine);
	// Duplicate the permutation vector
	p.insert(p.end(), p.begin(), p.end());
}

double PerlinNoise::noise(double x, double y, double z) const {
	// Find unit cube that contains point.
	int X = static_cast<int>(floor(x)) & 255;
	int Y = static_cast<int>(floor(y)) & 255;
	int Z = static_cast<int>(floor(z)) & 255;

	// Find relative x, y, z of point in cube.
	x -= floor(x);
	y -= floor(y);
	z -= floor(z);

	// Compute fade curves for each of x, y, z.
	double u = fade(x);
	double v = fade(y);
	double w = fade(z);

	// Hash coordinates of the 8 cube corners.
	int A  = p[X  ] + Y, AA = p[A] + Z, AB = p[A + 1] + Z;
	int B  = p[X+1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

	// And add blended results from 8 corners of cube.
	double gradAA = grad(AA, 0, 0, x, y, z);
	double gradBA = grad(BA, 0, 0, x - 1, y, z);
	double gradAB = grad(AB, 0, 0, x, y - 1, z);
	double gradBB = grad(BB, 0, 0, x - 1, y - 1, z);
	double gradAA1 = grad(AA + 1, 0, 0, x, y, z - 1);
	double gradBA1 = grad(BA + 1, 0, 0, x - 1, y, z - 1);
	double gradAB1 = grad(AB + 1, 0, 0, x, y - 1, z - 1);
	double gradBB1 = grad(BB + 1, 0, 0, x - 1, y - 1, z - 1);

	double lerpX1 = lerp(gradAA, gradBA, u);
	double lerpX2 = lerp(gradAB, gradBB, u);
	double lerpY1 = lerp(lerpX1, lerpX2, v);

	double lerpX3 = lerp(gradAA1, gradBA1, u);
	double lerpX4 = lerp(gradAB1, gradBB1, u);
	double lerpY2 = lerp(lerpX3, lerpX4, v);

	return lerp(lerpY1, lerpY2, w) * 1.04;
}

double PerlinNoise::noise(double x, double y) const {
	return noise(x, y, 0.0);
}

double PerlinNoise::noise(double x) const {
	return noise(x, 0.0, 0.0);
}

double PerlinNoise::octaveNoise(double x, double y, double z, int octaves, double persistence) const {
	double total = 0;
	double frequency = 1;
	double amplitude = 1;
	double maxValue = 0;  // Used for normalizing result to 0.0 - 1.0
	for (int i = 0; i < octaves; i++) {
		// total += noise(x * frequency, y * frequency, z * frequency + 52.5) * amplitude;
		total += noise(x * frequency, y * frequency, z * frequency) * amplitude;
		maxValue += amplitude;
		amplitude *= persistence;
		frequency *= 2;
	}
	return total / maxValue;
}

double PerlinNoise::octaveNoise(double x, double y, int octaves, double persistence) const {
	return octaveNoise(x, y, 0.0, octaves, persistence);
}

double PerlinNoise::octaveNoise(double x, int octaves, double persistence) const {
	return octaveNoise(x, 0.0, 0.0, octaves, persistence);
}

double PerlinNoise::fade(double t) {
	return t * t * t * (t * (t * 6 - 15) + 10);
}

double PerlinNoise::lerp(double a, double b, double t) {
	return a + t * (b - a);
}

double PerlinNoise::grad(int ix, int iy, int iz, double x, double y, double z) const {
	// Convert lower 4 bits of hash code into 12 gradient directions.
	int h = p[p[p[ix] + iy] + iz] & 15;
	double u = h < 8 ? x : y;
	double v = h < 4 ? y : (h == 12 || h == 14 ? x : z);
	// Depending on the hash, return a positive or negative contribution.
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}
